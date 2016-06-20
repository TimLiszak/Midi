
#ifndef _LOOK_AT_CAMERA_H_
#define _LOOK_AT_CAMERA_H_

#include "Camera.h"

class CLookAtCamera : public CCamera
{
public:
	CLookAtCamera( VECTOR vTarget, FLOAT fLookAtTime );

	void	SetTarget( VECTOR vTarget );
	void	SetLookAtTime( FLOAT fLookAtTime );

	virtual void	Update( const FLOAT fFrameTime, BOOL bIsCurrent );
	virtual BOOL	IsEventCamera() { return TRUE; }

	virtual VECTOR	GetScroll();

protected:
	VECTOR		m_vScroll;
	VECTOR		m_vTarget;
	FLOAT		m_fTime;
	FLOAT		m_fLookAtTime;
};

inline void CLookAtCamera::SetTarget( VECTOR vTarget )
{
	m_vTarget = vTarget;
}

inline void CLookAtCamera::SetLookAtTime( FLOAT fLookAtTime )
{
	m_fLookAtTime = fLookAtTime;
}

#endif
