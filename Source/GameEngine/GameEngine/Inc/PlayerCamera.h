
#ifndef _PLAYER_CAMERA_H_
#define _PLAYER_CAMERA_H_

#include "Camera.h"
#include "Actor.h"

class CPlayerCamera : public CCamera
{
public:
	CPlayerCamera( CActor* pActor );
	void	AddActor( CActor* pActor );
	
	virtual void	Update( const FLOAT fFrameTime, BOOL bIsCurrent );
	virtual BOOL	GetLimits( VECTOR& vMin, VECTOR& vMax );
	virtual FLOAT	GetZoom();
	virtual VECTOR	GetScroll();
	virtual VECTOR	GetScrollNoLimit();
	virtual FLOAT	GetSpeed();

	void	SetMaxX( FLOAT fMaxX );
	void	SetMaxY( FLOAT fMaxY );
	void	SetMinX( FLOAT fMinX );
	void	SetMinY( FLOAT fMinY );
	void	SetOffset( VECTOR vOffset );

private:
	VECTOR		m_vScroll;
	std::list< CActor* >	m_Actors;

	VECTOR		m_vMax;
	VECTOR		m_vMin;
	VECTOR		m_vOffset;
	VECTOR		m_vLastPosition;
	FLOAT		m_fZoom;

};

inline void CPlayerCamera::SetMaxX( FLOAT fMaxX )
{
	m_vMax.x = fMaxX;
}

inline void CPlayerCamera::SetMaxY( FLOAT fMaxY )
{
	m_vMax.y = fMaxY;
}

inline void CPlayerCamera::SetMinX( FLOAT fMinX )
{
	m_vMin.x = fMinX;
}

inline void CPlayerCamera::SetMinY( FLOAT fMinY )
{
	m_vMin.y = fMinY;
}

inline void CPlayerCamera::SetOffset( VECTOR vOffset )
{
	m_vOffset = vOffset;
}

inline FLOAT CPlayerCamera::GetZoom()
{
	return m_fZoom;
}

#endif
