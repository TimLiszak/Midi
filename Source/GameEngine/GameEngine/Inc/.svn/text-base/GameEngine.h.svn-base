#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

class CGameMode
{
public:
	virtual void	Init() = 0;
	virtual void	Term() = 0;
	virtual void	Update( const FLOAT fFrameTime ) = 0;
	virtual void	Render() = 0;
	virtual void	OnClose() {};
};

class CMenuCallback
{
public:
	virtual void	MenuSelected( INT nMenuId ) = 0;
};

class CDragDropCallback
{
public:
	virtual void	DragDropFiles( const std::vector< std::string >& Files ) = 0;
};

class CGameEngine
{
public:
	static CGameEngine*	GetInstance()
	{
		if ( !m_pInstance )
		{
			m_pInstance = new CGameEngine();
		}
		return m_pInstance;
	}

	BOOL	Init( const CHAR* pTitle, INT nWidth, INT nHeight, INT nMenuId = -1 );
	void	Term();
	void	Run( CGameMode* pGameMode );
	void	SwitchGameMode( CGameMode* pGameMode );

	void	AddMenuCallback( CMenuCallback* pCallback );
	void	RemoveMenuCallback( CMenuCallback* pCallback );
	void	AddDragDropCallback( CDragDropCallback* pCallback );
	void	RemoveDragDropCallback( CDragDropCallback* pCallback );

	FLOAT	GetFrameTime();
	FLOAT	GetTotalTime();

	class CGameMode*		GetCurrentGameMode();
	class CDebugPrint*		GetDebugPrint();
	class CInput*			GetInput();
	class CWorld*			GetWorld();
	class CViewer*			GetView();
	class CTextureManager*	GetTextureManager();
	class CSpriteManager*	GetSpriteManager();
	class CCameraManager*	GetCameraManager();
	class CReflectableEditor*	GetReflectableEditor();

	void	ToggleDrawBoundingBoxes();
	void	ToggleDebugPause();
	
	void	ShowEditorVisibleObjects( BOOL bVisible );
	BOOL	CanShowEditorVisibleObjects();
    void    DisableBackspaceQuit( BOOL bDisable );
    BOOL    IsDisableBackspaceQuit();


	BOOL	WndProcCallback( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	void	ReflectEngineObjects();

	void	UpdateGame( CGameMode* pGameMode );
	void	RenderGame( CGameMode* pGameMode );

	void	HandleWinMessages();

	CGameEngine();
	static CGameEngine*		m_pInstance;

	class CGameMode*		m_pCurrentGameMode;
	class CGameMode*		m_pNextGameMode;
	class CViewer*			m_pView;
	class CTextureManager*	m_pTextureManager;
	class CSpriteManager*	m_pSpriteManager;
	class CInput*			m_pInput;
	class CDebugPrint*		m_pDebugPrint;
	class CWorld*			m_pWorld;
	class CCameraManager*	m_pCameraManager;
	class CReflectableEditor* m_pReflectableEditor;
	class CGameSettings*	m_pGameSettings;

	INT				m_nPreviousTime;
	FLOAT			m_fFrameTime;
	FLOAT			m_fTotalTime;
	BOOL			m_bQuit;
	BOOL			m_bActive;

	BOOL			m_bDrawBoundingBoxes;
	BOOL			m_bDebugPause;
	BOOL			m_bShowEditorVisibleObjects;
	BOOL			m_bDisableBackspaceQuit;

	static const INT	NUM_FRAME_TIMES = 10;
	FLOAT	m_StoredFrameTimes[NUM_FRAME_TIMES];
	INT		m_nStoredFrameTimeCnt;

	std::list<CMenuCallback*>		m_MenuCallbacks;
	std::list<CDragDropCallback*>	m_DragDropCallbacks;
	
};

inline class CGameEngine* GetGameEngine()
{
	return CGameEngine::GetInstance();
}

inline void CGameEngine::AddMenuCallback( CMenuCallback* pCallback )
{
	m_MenuCallbacks.push_back( pCallback );
}

inline void CGameEngine::RemoveMenuCallback( CMenuCallback* pCallback )
{
	m_MenuCallbacks.remove( pCallback );
}

inline void CGameEngine::AddDragDropCallback( CDragDropCallback* pCallback )
{
	m_DragDropCallbacks.push_back( pCallback );
}

inline void CGameEngine::RemoveDragDropCallback( CDragDropCallback* pCallback )
{
	m_DragDropCallbacks.remove( pCallback );
}

inline CGameMode* CGameEngine::GetCurrentGameMode()
{
	return m_pCurrentGameMode;
}

inline CDebugPrint* CGameEngine::GetDebugPrint()
{
	return m_pDebugPrint;
}

inline CInput* CGameEngine::GetInput()
{
	return m_pInput;
}

inline CWorld* CGameEngine::GetWorld()
{
	return m_pWorld;
}

inline CViewer* CGameEngine::GetView()
{
	return m_pView;
}

inline CTextureManager* CGameEngine::GetTextureManager()
{
	return m_pTextureManager;
}

inline CSpriteManager* CGameEngine::GetSpriteManager()
{
	return m_pSpriteManager;
}

inline CCameraManager* CGameEngine::GetCameraManager()
{
	return m_pCameraManager;
}

inline CReflectableEditor* CGameEngine::GetReflectableEditor()
{
	return m_pReflectableEditor;
}

inline FLOAT CGameEngine::GetTotalTime()
{
	return m_fTotalTime;
}

inline FLOAT CGameEngine::GetFrameTime()
{
	return m_fFrameTime;
}

inline void CGameEngine::ToggleDrawBoundingBoxes()
{
	m_bDrawBoundingBoxes = !m_bDrawBoundingBoxes;
}

inline void CGameEngine::ToggleDebugPause()
{
	m_bDebugPause = !m_bDebugPause;
}

inline void CGameEngine::ShowEditorVisibleObjects( BOOL bVisible )
{
	m_bShowEditorVisibleObjects = bVisible;
}

inline BOOL CGameEngine::CanShowEditorVisibleObjects()
{
	return m_bShowEditorVisibleObjects;
}

inline void CGameEngine::DisableBackspaceQuit( BOOL bDisable )
{
	m_bDisableBackspaceQuit = bDisable;
}

inline BOOL CGameEngine::IsDisableBackspaceQuit()
{
	return m_bDisableBackspaceQuit;
}


#endif