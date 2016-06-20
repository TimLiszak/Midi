
#ifndef _DEBUG_CAMERA_H_
#define _DEBUG_CAMERA_H_

#include "Camera.h"

class CDebugCamera : public CCamera
{
public:
	CDebugCamera();
	virtual void	Update( const FLOAT fFrameTime, BOOL bIsCurrent );
	void	SetScroll( VECTOR vScroll );
	virtual VECTOR	GetScroll();

	virtual BOOL	IsEventCamera() { return TRUE; }

private:

	VECTOR	 m_vScroll;
	VECTOR	 m_vLastMousePos;

};

#endif
