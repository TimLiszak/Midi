
#ifndef _COOP_CAMERA_H_
#define _COOP_CAMERA_H_

#include "Camera.h"

class CCoopCamera : public CCamera
{
public:
	static const INT	MAX_PLAYERS = 2;

	CCoopCamera();

	void		SetCamera( INT nIndex, CCamera* pCamera );
	CCamera*	GetCamera( INT nIndex );

	virtual void	Update( const FLOAT fFrameTime, BOOL bIsCurrent );
	virtual VECTOR	GetScroll();
	virtual FLOAT	GetZoom();

	void		SetCameraCut( BOOL bCut );

protected:
	CCamera*	m_pCamera[MAX_PLAYERS];
	VECTOR		m_vCurrentScroll;
	BOOL		m_bCut;
	FLOAT		m_fLimit;

};

inline void CCoopCamera::SetCamera( INT nIndex, CCamera* pCamera )
{
	m_pCamera[nIndex] = pCamera;
}

inline CCamera* CCoopCamera::GetCamera( INT nIndex )
{
	return m_pCamera[nIndex];
}

inline void CCoopCamera::SetCameraCut( BOOL bCut )
{
	m_bCut = bCut;
}

#endif
