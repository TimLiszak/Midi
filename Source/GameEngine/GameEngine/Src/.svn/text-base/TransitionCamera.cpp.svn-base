#include "StdAfx.h"
#include "TransitionCamera.h"

CTransitionCamera::CTransitionCamera() :
	m_pCameraStart(NULL),
	m_pCameraEnd(NULL),
	m_fTime(0.0f)
{
}

void CTransitionCamera::Update( const FLOAT fFrameTime, BOOL bIsCurrent )
{
	ASSERT( m_pCameraStart );
	ASSERT( m_pCameraEnd );

	if ( m_fTime < m_fMaxTime )
	{
		m_fTime += fFrameTime;
	}
}

VECTOR CTransitionCamera::GetScroll()
{
	ASSERT( m_pCameraStart );
	ASSERT( m_pCameraEnd );

	FLOAT fT = m_fTime / m_fMaxTime;
	VECTOR v0 = m_pCameraStart->GetScroll();
	VECTOR v1 = m_pCameraEnd->GetScroll();

	VECTOR vPos = v0 * (1.0f - fT) + v1 * fT;
	return vPos;
}

BOOL CTransitionCamera::IsFinished()
{
	return ( m_fTime >= m_fMaxTime );
}

void CTransitionCamera::StartTransition( CCamera* pStart, CCamera* pEnd, FLOAT fTime )
{
	m_pCameraStart = pStart;
	m_pCameraEnd = pEnd;
	m_fMaxTime = fTime;
	m_fTime = 0.0f;
}

CCamera* CTransitionCamera::EndTransition()
{
	CCamera* pEnd = m_pCameraEnd;
	m_pCameraStart = NULL;
	m_pCameraEnd = NULL;
	return pEnd;
}

FLOAT CTransitionCamera::GetZoom()
{
	FLOAT fT = m_fTime / m_fMaxTime;
	FLOAT z1 = m_pCameraStart->GetZoom();
	FLOAT z2 = m_pCameraEnd->GetZoom();
	return z1 * (1.0f - fT) + z2 * fT;
}
