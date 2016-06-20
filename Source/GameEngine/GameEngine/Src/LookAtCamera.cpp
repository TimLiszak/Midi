#include "StdAfx.h"
#include "LookAtCamera.h"
#include "View.h"
#include "CameraManager.h"
#include "Input.h"

CLookAtCamera::CLookAtCamera( VECTOR vTarget, FLOAT fLookAtTime ) :
	m_vTarget(vTarget),
	m_fTime(0.0f),
	m_fLookAtTime( fLookAtTime )
{
}

void CLookAtCamera::Update( const FLOAT fFrameTime, BOOL bIsCurrent )
{
	if ( bIsCurrent )
	{
		m_fTime += fFrameTime;
		if ( m_fTime > m_fLookAtTime )
		{
			GetGameEngine()->GetInput()->DisableInput( FALSE );
			m_fTime = 0.0f;
			GetGameEngine()->GetCameraManager()->SetPreviousCamera();
		}
	}

	VECTOR vSize = GetGameEngine()->GetView()->GetViewSize();
	vSize = vSize * 0.5f;
	m_vScroll = m_vTarget - vSize;
}

VECTOR CLookAtCamera::GetScroll()
{
	return m_vScroll;
}



