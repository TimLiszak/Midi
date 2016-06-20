#include "StdAfx.h"
#include "PlayerCamera.h"
#include "Input.h"
#include "View.h"
#include "DynamicActor.h"

static const FLOAT	MAX_ZOOM	= 2.0f;

CPlayerCamera::CPlayerCamera( CActor* pActor )
{
	m_fZoom = 1.0f;
	m_vMax.Set( 99999.0f, 99999.0f );
	m_vMin.Set( -99999.0f, -99999.0f );
	m_vOffset.Set( 0.0f, 0.0f );
	m_Actors.push_back( pActor );
}

void CPlayerCamera::AddActor( CActor* pActor )
{
	m_Actors.push_back( pActor );
}

VECTOR CPlayerCamera::GetScroll()
{
	VECTOR vScroll = m_vScroll;

	vScroll.x = Math::Max( vScroll.x, m_vMin.x );
	vScroll.y = Math::Max( vScroll.y, m_vMin.y );
	vScroll.x = Math::Min( vScroll.x, m_vMax.x );
	vScroll.y = Math::Min( vScroll.y, m_vMax.y );
	return vScroll;
}

VECTOR CPlayerCamera::GetScrollNoLimit() 
{ 
	return m_vScroll; 
}

BOOL CPlayerCamera::GetLimits( VECTOR& vMin, VECTOR& vMax )
{
	vMin = m_vMin;
	vMax = m_vMax;
	return TRUE;
}

void CPlayerCamera::Update( const FLOAT fFrameTime, BOOL bIsCurrent )
{
	VECTOR vSize = GetGameEngine()->GetView()->GetViewSize();
	vSize = vSize;

	VECTOR vMin( 999999.9f, 999999.9f );
	VECTOR vMax( -999999.9f, -999999.9f );
	VECTOR vAvgPos( 0.0f, 0.0f );
	UINT uCnt = 0;
	std::list<CActor*>::iterator it;
	for ( it = m_Actors.begin() ; it != m_Actors.end(); it++ )
	{
		if ( !(*it)->IsDead() )
		{
			VECTOR vPos = (*it)->GetPosition();
			vAvgPos += vPos;
			uCnt++;

			vMin.x = Math::Min( vMin.x, vPos.x );
			vMin.y = Math::Min( vMin.y, vPos.y );
			vMax.x = Math::Max( vMax.x, vPos.x );
			vMax.y = Math::Max( vMax.y, vPos.y );
		}
	}
	if ( uCnt > 0 )
	{
		vAvgPos = vAvgPos / (FLOAT)uCnt;

		VECTOR vBox = vMax - vMin;
		vBox *= 0.5f;
		FLOAT fScale = Math::Abs( Math::Max( vBox.x / vSize.x, vBox.y / vSize.y ) ) / 0.8f;
		if ( fScale > 1.0f )
		{
			fScale = Math::Min( fScale, MAX_ZOOM );
			m_fZoom = fScale;
		}
		else
		{
			m_fZoom = 1.0f ;
		}


	}
	else
	{
		vAvgPos = m_vLastPosition;
	}


	m_vLastPosition = vAvgPos;

	m_vScroll = vAvgPos - vSize;
	m_vScroll += m_vOffset;
}

FLOAT CPlayerCamera::GetSpeed()
{
	FLOAT fMaxSpeed = 0.0f;
	std::list<CActor*>::iterator it;
	for ( it = m_Actors.begin() ; it != m_Actors.end(); it++ )
	{
		if ( !(*it)->IsDead() )
		{
			if ( (*it)->IsDynamic() )
			{
				CDynamicActor* pDynamicActor = (CDynamicActor*)(*it);
				FLOAT fSpeed = Math::Abs( pDynamicActor->GetVelocity().y );
				FLOAT fXSpeed = Math::Abs( pDynamicActor->GetVelocity().x );
				if( fXSpeed > 400 * GetGameEngine()->GetFrameTime() )
				{
					fSpeed = Math::Max( fSpeed, fXSpeed );
				}
				fMaxSpeed = Math::Max( fMaxSpeed, fSpeed );
			}
		}
	}
	return fMaxSpeed;
}
