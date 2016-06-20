#ifndef _VIEW_H_
#define _VIEW_H_

class CViewer
{
public:
	BOOL	Init( const CHAR* pTitle, INT nWidth, INT nHeight, INT nMenuId );
	void	Term();

	void	Start2DRender();
	void	PushCameraMatrix();
	void	PopCameraMatrix();

	void	Sync();

	void	SetWidescreen( BOOL bWidescreen );

	HDC		GetHDC();
	HWND	GetHWnd();
	void	Resize( INT nWidth, INT nHeight );

	VECTOR	GetViewSize();
	void	GetViewableBoundingBox( VECTOR& vMin, VECTOR& vMax );

	VECTOR	GetMouseWorldPosition();
	VECTOR	GetMouseScreenPosition();

	void	IncreaseZoom();
	void	DecreaseZoom();
	FLOAT	GetZoom();

private:

	HDC			m_hDC; 
	HGLRC		hRC;		// Permanent Rendering Context
	HWND		hWnd;		// Holds Our Window Handle
	HINSTANCE	hInstance;		// Holds The Instance Of The Application
	FLOAT		m_fViewHeight;
	VECTOR		m_vViewSize;
	VECTOR		m_vBorderSize;
	VECTOR		m_vWindowSize;
	FLOAT		m_fZoom;
	FLOAT		m_fDBAddZoom;
	BOOL		m_bWidescreen;


	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);		// Resize And Initialize The GL Window
	int InitGL(GLvoid);										// All Setup For OpenGL Goes Here
	int DrawGLScene(GLvoid);									// Here's Where We Do All The Drawing
	GLvoid KillGLWindow(GLvoid);								// Properly Kill The Window
	BOOL CreateGLWindow(const char* title, int width, int height, int bits, INT nMenuId);

};

inline HDC CViewer::GetHDC()
{
	return m_hDC;
}

inline HWND CViewer::GetHWnd()
{
	return hWnd;
}

inline VECTOR CViewer::GetViewSize()
{
	return m_vViewSize;
}

inline void CViewer::IncreaseZoom()
{
	m_fDBAddZoom += 0.1f;
}

inline void CViewer::DecreaseZoom()
{
	m_fDBAddZoom -= 0.1f;
	m_fDBAddZoom = Math::Max( m_fDBAddZoom, 0.0f );
}

inline FLOAT CViewer::GetZoom()
{
	return ( m_fZoom + m_fDBAddZoom );
}

#endif
