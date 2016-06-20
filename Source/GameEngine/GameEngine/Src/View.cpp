
#include "StdAfx.h"
#include "View.h"
#include "Render2d.h"
#include "GameEngine.h"
#include "Camera.h"
#include "Input.h"
#include "CameraManager.h"

static const FLOAT	ASPECT_RATIO_STANDARD = 4.0f / 3.0f;
static const FLOAT	ASPECT_RATIO_WIDESCREEN = 16.0f / 9.0f;

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( GetGameEngine()->WndProcCallback( hWnd, uMsg, wParam, lParam ) )
	{
		return 0;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

BOOL CViewer::Init( const CHAR* pTitle, INT nWidth, INT nHeight, INT nMenuId )
{
	m_bWidescreen = TRUE;
	m_hDC = NULL;	
	hRC = NULL;	
	hWnd = NULL;	
	m_fViewHeight = (FLOAT)nHeight;
	m_vViewSize.x = m_fViewHeight * ASPECT_RATIO_WIDESCREEN;
	m_vViewSize.y = m_fViewHeight;
	m_fZoom = 1.0f;
	m_fDBAddZoom = 0.0f;

	// Create Our OpenGL Window
	if (!CreateGLWindow( pTitle, (INT)m_vViewSize.x, (INT)m_vViewSize.y, 16, nMenuId))
	{
		return FALSE;
	}

	return TRUE;
}

void CViewer::Term()
{
	// Shutdown
	KillGLWindow();	
}

void CViewer::Sync()
{
	SwapBuffers(m_hDC);
}

void CViewer::Resize( INT nWidth, INT nHeight )
{
	ReSizeGLScene( nWidth, nHeight );
}

GLvoid CViewer::ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}
	m_vWindowSize.Set( width, height );

	FLOAT fAspect = ASPECT_RATIO_STANDARD;
	if ( m_bWidescreen )
	{
		fAspect = ASPECT_RATIO_WIDESCREEN;
	}

	FLOAT fWidth = (FLOAT)width;
	FLOAT fHeight = fWidth / fAspect;

	if ( fHeight < (FLOAT)height )
	{
		FLOAT fBorder = ( (FLOAT)height - fHeight ) * 0.5f;
	
		glViewport( 0, (INT)fBorder, (INT)fWidth, (INT)fHeight );
		
		m_vBorderSize.Set( 0.0f, fBorder );
	}
	else
	{
		fHeight = (FLOAT)height;
		fWidth = fHeight * fAspect;

		FLOAT fBorder = ( (FLOAT)width - fWidth ) * 0.5f;

		glViewport( (INT)fBorder, 0, (INT)fWidth, (INT)fHeight );

		m_vBorderSize.Set( fBorder, 0.0f );
	}

	Start2DRender();
}

int CViewer::InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	Start2DRender();

	return TRUE;										// Initialization Went OK
}

void CViewer::Start2DRender()
{
	CRender2d::Init2dRender( m_vViewSize );
}

void CViewer::PushCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	VECTOR vScroll = GetGameEngine()->GetCameraManager()->GetCurrentScroll();
	m_fZoom = GetGameEngine()->GetCameraManager()->GetCurrentZoom();

	FLOAT fZoom = m_fZoom;
	fZoom += m_fDBAddZoom;
	glScalef( 1.0f / fZoom, 1.0f / fZoom, 1.0f );
	glTranslatef( m_vViewSize.x * 0.5f * ( fZoom - 1.0f ), m_vViewSize.y * 0.5f * ( fZoom - 1.0f ), 0.0f );
	glTranslatef( -vScroll.x, -vScroll.y, 0.0f );
}

void CViewer::PopCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

GLvoid CViewer::KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (m_hDC && !ReleaseDC(hWnd,m_hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window								*
 *	height			- Height Of The GL Window								*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*/
 
BOOL CViewer::CreateGLWindow(const char* title, int width, int height, int bits, INT nMenuId)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size


	HMENU hmenu = NULL;
	if ( nMenuId >= 0 )
	{
		hmenu = LoadMenu( hInstance, MAKEINTRESOURCE(nMenuId) );
	}

	// Create The Window
	hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
									"OpenGL",							// Class Name
									title,								// Window Title
									dwStyle |							// Defined Window Style
									WS_CLIPSIBLINGS |					// Required Window Style
									WS_CLIPCHILDREN,					// Required Window Style
									CW_USEDEFAULT, 
									CW_USEDEFAULT,								// Window Position
									WindowRect.right-WindowRect.left,	// Calculate Window Width
									WindowRect.bottom-WindowRect.top,	// Calculate Window Height
									NULL,								// No Parent Window
									hmenu,								// No Menu
									hInstance,							// Instance
									NULL );

	if ( !hWnd )								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		(BYTE)bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	m_hDC=GetDC(hWnd);
	if (!m_hDC)							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	PixelFormat=ChoosePixelFormat(m_hDC,&pfd);
	if (!PixelFormat)	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	hRC=wglCreateContext(m_hDC);
	if (!hRC)				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(m_hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

void CViewer::GetViewableBoundingBox( VECTOR& vMin, VECTOR& vMax )
{
	VECTOR vScroll = GetGameEngine()->GetCameraManager()->GetCurrentScroll();
	VECTOR vExtents = m_vViewSize * 0.5f;
	VECTOR vCenter = vExtents + vScroll;

	vMin = vCenter - vExtents * ( m_fZoom + m_fDBAddZoom );
	vMax = vCenter + vExtents * ( m_fZoom + m_fDBAddZoom );
}

VECTOR CViewer::GetMouseWorldPosition()
{
	CMouse* pMouse = GetGameEngine()->GetInput()->GetMouse();
	VECTOR vMousePos = pMouse->GetMousePosition();

	vMousePos.x = ( vMousePos.x - m_vBorderSize.x ) / ( m_vWindowSize.x - m_vBorderSize.x * 2.0f );
	vMousePos.y = ( vMousePos.y - m_vBorderSize.y ) / ( m_vWindowSize.y - m_vBorderSize.y * 2.0f );
	vMousePos.x *= m_vViewSize.x;
	vMousePos.y *= m_vViewSize.y;

	VECTOR vScroll = GetGameEngine()->GetCameraManager()->GetCurrentScroll();

	// Zoom
	vMousePos.x *= ( m_fZoom + m_fDBAddZoom );
	vMousePos.y *= ( m_fZoom + m_fDBAddZoom );
	vMousePos.x -= m_vViewSize.x * 0.5f * ( ( m_fZoom + m_fDBAddZoom ) - 1.0f );
	vMousePos.y -= m_vViewSize.y * 0.5f * ( ( m_fZoom + m_fDBAddZoom ) - 1.0f );

	vMousePos += vScroll;
	return vMousePos;
}

VECTOR CViewer::GetMouseScreenPosition()
{
	CMouse* pMouse = GetGameEngine()->GetInput()->GetMouse();
	VECTOR vMousePos = pMouse->GetMousePosition();

	vMousePos.x = ( vMousePos.x - m_vBorderSize.x ) / ( m_vWindowSize.x - m_vBorderSize.x * 2.0f );
	vMousePos.y = ( vMousePos.y - m_vBorderSize.y ) / ( m_vWindowSize.y - m_vBorderSize.y * 2.0f );
	vMousePos.x *= m_vViewSize.x;
	vMousePos.y *= m_vViewSize.y;

	return vMousePos;
}

void CViewer::SetWidescreen( BOOL bWidescreen )
{
	m_bWidescreen = bWidescreen;
	
	FLOAT fAspect = ASPECT_RATIO_STANDARD;
	if ( m_bWidescreen )
	{
		fAspect = ASPECT_RATIO_WIDESCREEN;
	}
	m_vViewSize.x = m_fViewHeight * fAspect;
	m_vViewSize.y = m_fViewHeight;

	ReSizeGLScene( (INT)m_vWindowSize.x, (INT)m_vWindowSize.y );
}
