#include "StdAfx.h"

#include "GameEngine.h"
#include "Input.h"
#include "Render2d.h"
#include "FileReader.h"
#include "View.h"
#include "DebugPrint.h"
#include "World.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "CameraManager.h"
#include "ReflectableEditor.h"
#include "Level.h"
#include "Reflectable.h"
#include "TileSet.h"
#include "TileMap.h"
#include "GameSettings.h"
#include "SpriteInfo.h"

#define ID_CONTROLLER_XBOX              40044
#define ID_CONTROLLER_PS3               40045
#define ID_CONTROLLER_PS4               40046

CGameEngine* CGameEngine::m_pInstance = NULL;

CGameEngine::CGameEngine() :
	m_pInput(NULL)
{
}

void CGameEngine::ReflectEngineObjects()
{
	INIT_REFLECT( CActorDescription );
	INIT_REFLECT( CLevel );
	INIT_REFLECT( CTileProperties );
	INIT_REFLECT( CSpriteInfo );
}

BOOL CGameEngine::Init( const CHAR* pTitle, INT nWidth, INT nHeight, INT nMenuId )
{
	ReflectEngineObjects();

	m_bQuit = FALSE;
	m_bActive = TRUE;
	m_pNextGameMode = NULL;
	m_pCurrentGameMode = NULL;
	m_nStoredFrameTimeCnt = 0;
	m_fTotalTime = 0;
	m_bDrawBoundingBoxes = FALSE;
	m_bDebugPause = FALSE;
	m_bShowEditorVisibleObjects = FALSE;
    m_bDisableBackspaceQuit = FALSE;

	for ( INT i = 0; i < NUM_FRAME_TIMES; i++ )
	{
		m_StoredFrameTimes[i] = 1.0f / 60.0f;
	}

	m_pView = new CViewer();
	if ( !m_pView->Init( pTitle, nWidth, nHeight, nMenuId ) )
	{
		return FALSE;
	}

	m_pInput = new CInput();
	m_pInput->Init();

	m_pDebugPrint = new CDebugPrint();
	m_pDebugPrint->Init();

	m_pWorld = new CWorld();
	m_pWorld->Init();

	m_pTextureManager = new CTextureManager();
	m_pTextureManager->Init();

	m_pSpriteManager = new CSpriteManager();
	m_pSpriteManager->Init();

	m_pCameraManager = new CCameraManager();
	m_pCameraManager->Init();

	m_pReflectableEditor = new CReflectableEditor();
	m_pReflectableEditor->Init();

	m_pGameSettings = new CGameSettings();
	m_pGameSettings->Init();

	CRender2d::BuildFont( m_pView->GetHDC() );

	VECTOR vSize = m_pView->GetViewSize();
	INT nYOffset = 44;
	SetWindowPos( m_pView->GetHWnd(), 0, 0, 0, (INT)vSize.x, (INT)vSize.y + nYOffset, SWP_NOMOVE | SWP_NOZORDER );

	DragAcceptFiles( m_pView->GetHWnd(), TRUE );

	return TRUE;
}

void	CGameEngine::Term()
{
	m_MenuCallbacks.clear();
	m_DragDropCallbacks.clear();
	
	CRender2d::KillFont();

	m_pView->Term();
	m_pTextureManager->Term();
	m_pSpriteManager->Term();
	m_pInput->Term();
	m_pDebugPrint->Term();
	m_pWorld->Term();
	m_pCameraManager->Term();
	m_pReflectableEditor->Term();
	m_pGameSettings->Term();
	
	delete m_pView;
	delete m_pTextureManager;
	delete m_pSpriteManager;
	delete m_pInput;
	delete m_pDebugPrint;
	delete m_pWorld;
	delete m_pCameraManager;
	delete m_pReflectableEditor;
	delete m_pGameSettings;
}

void	CGameEngine::Run( CGameMode* pGameMode )
{
	m_nPreviousTime = 0;

	m_pCurrentGameMode = pGameMode;
	m_pCurrentGameMode->Init();

	while( !m_bQuit )					
	{
		// Switch game mode
		if ( m_pNextGameMode )
		{
			m_pCurrentGameMode->Term();
			delete m_pCurrentGameMode;

			m_pCurrentGameMode = m_pNextGameMode;
			m_pCurrentGameMode->Init();
			m_pNextGameMode = NULL;
		}


		// Calculate frame time
		INT nTime = clock();
		FLOAT fFrameTime = (FLOAT)(nTime - m_nPreviousTime) / 1000.0f;
		
		if ( fFrameTime == 0.0f ) continue; // too fast, busy wait

		fFrameTime = Math::Min( fFrameTime, 0.080f );
		GetDebugPrint()->Printf( "FPS %0.2f\n", 1.0f / fFrameTime );
		m_nPreviousTime = nTime;

		m_StoredFrameTimes[m_nStoredFrameTimeCnt++] = fFrameTime;
		if ( m_nStoredFrameTimeCnt >= NUM_FRAME_TIMES )
		{
			m_nStoredFrameTimeCnt = 0;
		}

		// Calculate average frame time over past few frames
		FLOAT fAvg = 0.0f;
		for ( INT i = 0; i < NUM_FRAME_TIMES; i++ )
		{
			fAvg += m_StoredFrameTimes[i];
		}
		fAvg /= NUM_FRAME_TIMES;
		m_fFrameTime = fAvg;

		if ( m_bDebugPause )
		{
			CKeyboard* pKey = GetInput()->GetKeyboard();
			if ( pKey->IsKeyTriggered( EKbKey_RIGHT ) )
			{
				m_fFrameTime = 1.0f / 60.0f;
			}
			else
			{
				m_fFrameTime = 0.0f;
			}
		}

		m_fTotalTime += m_fFrameTime;

		UpdateGame( m_pCurrentGameMode );
		RenderGame( m_pCurrentGameMode );

		m_pView->Sync();
	}

	m_pCurrentGameMode->Term();
	delete m_pCurrentGameMode;
}

void CGameEngine::SwitchGameMode( CGameMode* pGameMode )
{
	m_pNextGameMode = pGameMode;
}

void CGameEngine::UpdateGame( CGameMode* pGameMode )
{
	HandleWinMessages();

	m_pInput->Update();
	m_pDebugPrint->Update( m_fFrameTime );

	pGameMode->Update( m_fFrameTime );
	m_pWorld->Update( m_fFrameTime );

	m_pCameraManager->Update( m_fFrameTime );
	m_pReflectableEditor->Update( m_fFrameTime );
	m_pSpriteManager->Update( m_fFrameTime );
	
}

void CGameEngine::RenderGame( CGameMode* pGameMode )
{
	CRender2d::ClearScreen( GetWorld()->GetLevel()->GetClearColour() );

	m_pView->Start2DRender();
	m_pView->PushCameraMatrix();
	m_pWorld->Render();
	m_pView->PopCameraMatrix();

	CKeyboard* pKey = GetGameEngine()->GetInput()->GetKeyboard();
	if ( pKey->IsKeyDown( EKbKey_TAB ) )
	{
		m_pView->PushCameraMatrix();
		m_pWorld->RenderEditorSelection();
		m_pView->PopCameraMatrix();
	}

	pGameMode->Render();

	if ( m_bDrawBoundingBoxes )
	{
		m_pView->PushCameraMatrix();
		m_pWorld->DebugDrawActors();
		m_pView->PopCameraMatrix();
	}

	m_pDebugPrint->Render();
}

void CGameEngine::HandleWinMessages()
{
	MSG		msg;
	while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
	{
		if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
		{
			m_bQuit = TRUE;
		}
		else									// If Not, Deal With Window Messages
		{
			TranslateMessage(&msg);				// Translate The Message
			DispatchMessage(&msg);				// Dispatch The Message
		}
	}
}

BOOL CGameEngine::WndProcCallback( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNUSED(hWnd);
	switch (uMsg)									// Check For Windows Messages
	{

		case WM_CREATE:
		{
			return TRUE;
		}
		
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				m_bActive=TRUE;						// Program Is Active
				if ( GetInput() )
				{
					GetInput()->GetGamepad(0)->Acquire();
					GetInput()->GetGamepad(1)->Acquire();
				}
			}
			else
			{
				m_bActive=FALSE;						// Program Is No Longer Active
			}

			return TRUE;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return TRUE;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			if ( m_pCurrentGameMode )
			{
				m_pCurrentGameMode->OnClose();
			}
			PostQuitMessage(0);						// Send A Quit Message
			return TRUE;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			m_pInput->GetKeyboard()->KeyDownCallback( wParam );
			return TRUE;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			m_pInput->GetKeyboard()->KeyUpCallback( wParam );
			return TRUE;								// Jump Back
		}

		case WM_LBUTTONDOWN:
		{
			INT xPos = GET_X_LPARAM(lParam); 
			INT yPos = GET_Y_LPARAM(lParam); 

			m_pInput->GetMouse()->MouseDownCallback( EMouseButton_Left, VECTOR( xPos, yPos ) );

			return TRUE;
		}

		case WM_LBUTTONUP:
		{
			INT xPos = GET_X_LPARAM(lParam); 
			INT yPos = GET_Y_LPARAM(lParam); 

			m_pInput->GetMouse()->MouseUpCallback( EMouseButton_Left, VECTOR( xPos, yPos ) );

			return TRUE;
		}

		case WM_RBUTTONDOWN:
		{
			INT xPos = GET_X_LPARAM(lParam); 
			INT yPos = GET_Y_LPARAM(lParam); 

			m_pInput->GetMouse()->MouseDownCallback( EMouseButton_Right, VECTOR( xPos, yPos ) );

			return TRUE;
		}

		case WM_RBUTTONUP:
		{
			INT xPos = GET_X_LPARAM(lParam); 
			INT yPos = GET_Y_LPARAM(lParam); 

			m_pInput->GetMouse()->MouseUpCallback( EMouseButton_Right, VECTOR( xPos, yPos ) );

			return TRUE;
		}

		case WM_MBUTTONDOWN:
		{
			INT xPos = GET_X_LPARAM(lParam); 
			INT yPos = GET_Y_LPARAM(lParam); 

			m_pInput->GetMouse()->MouseDownCallback( EMouseButton_Middle, VECTOR( xPos, yPos ) );

			return TRUE;
		}

		case WM_MBUTTONUP:
		{
			INT xPos = GET_X_LPARAM(lParam); 
			INT yPos = GET_Y_LPARAM(lParam); 

			m_pInput->GetMouse()->MouseUpCallback( EMouseButton_Middle, VECTOR( xPos, yPos ) );

			return TRUE;
		}

		case WM_MOUSEMOVE:
		{
			INT xPos = GET_X_LPARAM(lParam); 
			INT yPos = GET_Y_LPARAM(lParam); 

			m_pInput->GetMouse()->MouseMoveCallback( VECTOR( xPos, yPos ) );

			return TRUE;
		}

		case WM_MOUSEWHEEL:
		{
			INT zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			INT nMove = zDelta / WHEEL_DELTA;

			if ( nMove > 0 )
			{
				GetView()->DecreaseZoom();
			}
			else
			{
				GetView()->IncreaseZoom();
			}

			return TRUE;
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			m_pView->Resize(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return TRUE;								// Jump Back
		}

		
		case WM_COMMAND:
		{
			std::list<CMenuCallback*>::iterator it;
			for ( it = m_MenuCallbacks.begin() ; it != m_MenuCallbacks.end(); it++ )
			{
				(*it)->MenuSelected( LOWORD(wParam) );
			}

			switch( LOWORD(wParam) )
			{
				case ID_CONTROLLER_XBOX:
				{
					m_pGameSettings->SetKeyConfig( EKeyConfig_Xbox );
				}
				break;

				case ID_CONTROLLER_PS3:
				{
					m_pGameSettings->SetKeyConfig( EKeyConfig_PS3 );
				}
				break;

				case ID_CONTROLLER_PS4:
				{
					m_pGameSettings->SetKeyConfig( EKeyConfig_TimSpecial );
				}
				break;
			}
		}
		break;

		case WM_DROPFILES:
		{
			std::vector< std::string > Files;

			HDROP hDrop = (HDROP)wParam;
			INT nNumFiles = DragQueryFile( hDrop, 0xFFFFFFFF, 0, 0 );

			for (INT i = 0; i < nNumFiles; i++)
			{
				CHAR Buf[MAX_PATH];
				DragQueryFile( hDrop, i, Buf, MAX_PATH );

				std::string strFile = Buf;
				UINT nPos = strFile.rfind( "Data\\" );
				if ( nPos < strFile.size() )
				{
					strFile = strFile.substr( nPos + 5, strFile.size() - 1 );
				}
				Files.push_back( strFile );
			}

			std::list<CDragDropCallback*>::iterator it;
			for ( it = m_DragDropCallbacks.begin() ; it != m_DragDropCallbacks.end(); it++ )
			{
				(*it)->DragDropFiles( Files );
			}
		}
		break;

		default:
		{
			//TRACE( "msg %d\n", uMsg );
		}
	}

	return FALSE;
}
