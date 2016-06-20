#include "StdAfx.h"
#include "CoopCamera.h"

static const FLOAT	SCROLL_RATE = 400.0f;

CCoopCamera::CCoopCamera()
{
	for ( INT i = 0; i < MAX_PLAYERS; i++ )
	{
		m_pCamera[i] = NULL;
	}
	m_bCut = TRUE;
	m_fLimit = SCROLL_RATE;
}

void CCoopCamera::Update( const FLOAT fFrameTime, BOOL bIsCurrent )
{
	VECTOR vCombinedMin( 999999.9f, 999999.9f );
	VECTOR vCombinedMax( -999999.9f, -999999.9f );
	VECTOR vAvgScroll( 0.0f, 0.0f );
	FLOAT fMaxSpeed = 0.0f;

	BOOL bLimit = FALSE;
	UINT nCamCnt = 0;
	for ( INT i = 0; i < MAX_PLAYERS; i++ )
	{
		if ( m_pCamera[i] )
		{
			VECTOR vMin, vMax;
			vAvgScroll += m_pCamera[i]->GetScrollNoLimit();
			fMaxSpeed = Math::Max( fMaxSpeed, m_pCamera[i]->GetSpeed() );
			if ( m_pCamera[i]->GetLimits( vMin, vMax ) )
			{
				vCombinedMin.x = Math::Min( vCombinedMin.x, vMin.x );
				vCombinedMin.y = Math::Min( vCombinedMin.y, vMin.y );
				vCombinedMax.x = Math::Max( vCombinedMax.x, vMax.x );
				vCombinedMax.y = Math::Max( vCombinedMax.y, vMax.y );
				bLimit = TRUE;
			}
			nCamCnt++;
		}
	}

	if ( nCamCnt == 0 )
	{
		m_vCurrentScroll = VECTOR( 0.0f, 0.0f );
		return;
	}

	ASSERT( nCamCnt > 0 );
	vAvgScroll = vAvgScroll / (FLOAT)nCamCnt;

	if ( bLimit )
	{
		vAvgScroll.x = Math::Max( vAvgScroll.x, vCombinedMin.x );
		vAvgScroll.y = Math::Max( vAvgScroll.y, vCombinedMin.y );
		vAvgScroll.x = Math::Min( vAvgScroll.x, vCombinedMax.x );
		vAvgScroll.y = Math::Min( vAvgScroll.y, vCombinedMax.y );
	}

	if ( m_bCut )
	{
		m_vCurrentScroll = vAvgScroll;
		m_bCut = FALSE;
	}
	else
	{
		FLOAT fLimit = fMaxSpeed + m_fLimit * fFrameTime ;
		VECTOR vLastScroll = m_vCurrentScroll;
		VECTOR vDiff = vAvgScroll - vLastScroll;
		if ( vDiff.GetLengthSquared() >= fLimit * fLimit )
		{
			m_vCurrentScroll = vLastScroll + vDiff.Normalize() * fLimit;
		}
		else
		{
			m_vCurrentScroll = vAvgScroll;
		}
	}
}

VECTOR CCoopCamera::GetScroll()
{
	return m_vCurrentScroll;
}

FLOAT CCoopCamera::GetZoom()
{
	FLOAT fZoom = 0.0f;
	UINT nCamCnt = 0;
	for ( INT i = 0; i < MAX_PLAYERS; i++ )
	{
		if ( m_pCamera[i] )
		{
			fZoom += m_pCamera[i]->GetZoom();
			nCamCnt++;
		}
	}

	if ( nCamCnt == 0 )
	{
		return 1.0f;
	}

	ASSERT( nCamCnt > 0 );
	return fZoom / (FLOAT)nCamCnt;
}
