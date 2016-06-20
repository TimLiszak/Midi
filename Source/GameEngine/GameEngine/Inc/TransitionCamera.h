
#ifndef _TRANSITION_CAMERA_H_
#define _TRANSITION_CAMERA_H_

#include "Camera.h"

class CTransitionCamera : public CCamera
{
public:
	CTransitionCamera();

	virtual void	Update( const FLOAT fFrameTime, BOOL bIsCurrent );
	virtual VECTOR	GetScroll();

	void	StartTransition( CCamera* pStart, CCamera* pEnd, FLOAT fTime );
	BOOL	IsFinished();
	CCamera* EndTransition();

	virtual FLOAT	GetZoom();

protected:

	CCamera*	m_pCameraStart;
	CCamera*	m_pCameraEnd;
	FLOAT		m_fTime;
	FLOAT		m_fMaxTime;

};

#endif
