#include "StdAfx.h"
#include "DynamicActor.h"

void CDynamicActor::SetPosition( VECTOR vPos, BOOL bFromEditor )
{
	CActor::SetPosition( vPos, bFromEditor );
	m_vTargetPosition = vPos;
}

void CDynamicActor::UpdateMovement( VECTOR vCurrentPos, VECTOR vTarget )
{
	// no collision check
	SetPosition( vTarget );
}

BOOL CDynamicActor::CheckSweepCollision( CCollision::SweepResult& sResult, VECTOR vExtents, VECTOR vP1, VECTOR vP2 )
{
	VECTOR vThisVel = m_vTargetPosition - m_vPosition;
	CCollision::SAABBox sBox1( vExtents, vP1 );
	CCollision::SAABBox sBox2( m_vExtents, GetTargetPosition() );
	VECTOR vVel = vP2 - vP1;
	BOOL bCollide = CCollision::CheckAABoxSweep( sResult, sBox1, vVel, sBox2, vThisVel );

	if ( bCollide )
	{
		sResult.pActor = this;
		return TRUE;
	}
	return FALSE;
}
