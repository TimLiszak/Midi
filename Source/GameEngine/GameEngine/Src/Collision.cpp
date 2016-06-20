#include "StdAfx.h"
#include "Collision.h"

BOOL	CCollision::CheckAABoxOverlap( SAABBox& sBox1, SAABBox& sBox2 )
{
	if ( sBox1.vPos.x + sBox1.vExtents.x >= sBox2.vPos.x - sBox2.vExtents.x &&
		 sBox1.vPos.x - sBox1.vExtents.x <= sBox2.vPos.x + sBox2.vExtents.x &&
		 sBox1.vPos.y + sBox1.vExtents.y >= sBox2.vPos.y - sBox2.vExtents.y &&
		 sBox1.vPos.y - sBox1.vExtents.y <= sBox2.vPos.y + sBox2.vExtents.y )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL	CCollision::CheckLineBox( VECTOR vStart, VECTOR vEnd, SAABBox& sBox, FLOAT &fT )
{
	VECTOR vMin = sBox.vPos - sBox.vExtents;
	VECTOR vMax = sBox.vPos + sBox.vExtents;
	FLOAT tStart, tEnd;
	FLOAT t0 = 0.0f;
	FLOAT t1 = 1.0f;

	for ( INT i = 0; i < 2; i++ )
	{
		if ( vStart[i] < vEnd[i] )
		{
			if ( vStart[i] > vMax[i] || vEnd[i] < vMin[i] )  
			{
				return FALSE;
			}
			FLOAT fDiff = vEnd[i] - vStart[i];  
			tStart = (vStart[i] < vMin[i])? (vMin[i] - vStart[i]) / fDiff : 0;  
			tEnd = (vEnd[i] > vMax[i])? (vMax[i] - vStart[i]) / fDiff : 1;  
		}
		else
		{
			if (vEnd[i] > vMax[i] || vStart[i] < vMin[i])
			{
				return FALSE;  
			}
			FLOAT fDiff = vEnd[i] - vStart[i];  
			tStart = (vStart[i] > vMax[i])? (vMax[i] - vStart[i]) / fDiff : 0;  
			tEnd = (vEnd[i] < vMin[i])? (vMin[i] - vStart[i]) / fDiff : 1;  
		}

		if (tStart > t0) t0 = tStart;
		if (tEnd < t1) t1 = tEnd;
		if (t1 < t0) return FALSE;  
	}
	fT = t0;
	return TRUE;
}

BOOL	CCollision::CheckAABoxSweep( SweepResult& sResult, SAABBox& sBox1, VECTOR& vVel1, SAABBox& sBox2, VECTOR vVel2 )
{
	VECTOR vNewPos = sBox1.vPos + vVel1;
	BOOL bCollide = FALSE;
	BOOL bCheckX = FALSE;
	BOOL bCheckY = FALSE;

	BOOL bMovingObjLeft = vVel2.x < 0 && vVel1.x == 0;
	BOOL bMovingObjRight = vVel2.x > 0 && vVel1.x == 0;

	if ( vNewPos.x - sBox1.vExtents.x < sBox2.vPos.x + sBox2.vExtents.x &&
		 vNewPos.x + sBox1.vExtents.x > sBox2.vPos.x - sBox2.vExtents.x ) 
	{
		bCheckY = TRUE;
	}

	// moving down
	if ( vVel1.y > 0 && bCheckY )
	{
		if ( vNewPos.y - vVel1.y + sBox1.vExtents.y > sBox2.vPos.y - sBox2.vExtents.y + 5.0f )
		{
		}
		else if ( vNewPos.y + sBox1.vExtents.y > sBox2.vPos.y - sBox2.vExtents.y )
		{
			vNewPos.y = sBox2.vPos.y - sBox2.vExtents.y - sBox1.vExtents.y; 
			bCollide = TRUE;
			sResult.nCollideY = 1;
		}
	}

	if ( vNewPos.y - sBox1.vExtents.y < sBox2.vPos.y + sBox2.vExtents.y &&
		 vNewPos.y + sBox1.vExtents.y > sBox2.vPos.y - sBox2.vExtents.y ) 
	{
		bCheckX = TRUE;
	}

	if ( ( vVel1.x > 0 || bMovingObjLeft ) && bCheckX )
	{
		if ( vNewPos.x - vVel1.x + sBox1.vExtents.x > sBox2.vPos.x - sBox2.vExtents.x + 5.0f )
		{
		}
		else if ( vNewPos.x + sBox1.vExtents.x > sBox2.vPos.x - sBox2.vExtents.x )
		{
			vNewPos.x = sBox2.vPos.x - sBox2.vExtents.x - sBox1.vExtents.x; 
			bCollide = TRUE;
			sResult.nCollideX = 1;
		}
	}
	else if ( ( vVel1.x < 0 || bMovingObjRight ) && bCheckX )
	{
		if ( vNewPos.x - vVel1.x - sBox1.vExtents.x < sBox2.vPos.x + sBox2.vExtents.x - 5.0f )
		{
		}
		else if ( vNewPos.x - sBox1.vExtents.x < sBox2.vPos.x + sBox2.vExtents.x )
		{
			vNewPos.x = sBox2.vPos.x + sBox2.vExtents.x + sBox1.vExtents.x; 
			bCollide = TRUE;
			sResult.nCollideX = -1;
		}
	}

	bCheckY = FALSE;
	if ( vNewPos.x - sBox1.vExtents.x < sBox2.vPos.x + sBox2.vExtents.x &&
		 vNewPos.x + sBox1.vExtents.x > sBox2.vPos.x - sBox2.vExtents.x ) 
	{
		bCheckY = TRUE;
	}

	// moving up
	if ( vVel1.y < 0 && bCheckY )
	{
		if ( vNewPos.y - vVel1.y - sBox1.vExtents.y < sBox2.vPos.y + sBox2.vExtents.y - 5.0f )
		{
		}
		else if ( vNewPos.y - sBox1.vExtents.y < sBox2.vPos.y + sBox2.vExtents.y )
		{
			vNewPos.y = sBox2.vPos.y + sBox2.vExtents.y + sBox1.vExtents.y; 
			bCollide = TRUE;
			sResult.nCollideY = -1;
		}
	}

	sResult.vResult = vNewPos;
	return bCollide;
}

BOOL	CCollision::CheckRampCollision( SweepResult& sResult, SAABBox& sBox1, VECTOR& vVel1, SAABBox& sBox2, ERampType eRampType )
{
	VECTOR vNewPos = sBox1.vPos + vVel1;
	BOOL bCollide = FALSE;
	BOOL bCheckY = FALSE;

	FLOAT fPlayerFootX;
	if ( eRampType == ERampType_TL_BR ||
         eRampType == ERampType_Ceil_BL_TR )
	{
		fPlayerFootX = vNewPos.x - sBox1.vExtents.x;
	}
	else
	{
		fPlayerFootX = vNewPos.x + sBox1.vExtents.x;
	}

	if ( fPlayerFootX <= sBox2.vPos.x + sBox2.vExtents.x &&
		 fPlayerFootX >= sBox2.vPos.x - sBox2.vExtents.x &&
		 vNewPos.y - sBox1.vExtents.y < sBox2.vPos.y + sBox2.vExtents.y &&
		 vNewPos.y + sBox1.vExtents.y > sBox2.vPos.y - sBox2.vExtents.y ) 
	{
		bCheckY = TRUE;
	}

	// moving down
	if ( bCheckY )
	{
		FLOAT fY0, fY1;

        if ( eRampType >= ERampType_Ceil_TL_BR )
        {
		    if ( eRampType == ERampType_Ceil_TL_BR )
		    {
			    fY0 = sBox2.vPos.y - sBox2.vExtents.y;
			    fY1 = sBox2.vPos.y + sBox2.vExtents.y;
		    }
		    else
		    {
			    fY0 = sBox2.vPos.y + sBox2.vExtents.y;
			    fY1 = sBox2.vPos.y - sBox2.vExtents.y;
		    }
		    FLOAT fT = ( fPlayerFootX - (sBox2.vPos.x - sBox2.vExtents.x) ) / ( sBox2.vExtents.x * 2.0f );
		    FLOAT fGroundY = fT * fY1 + ( 1.0f - fT ) * fY0 + sBox1.vExtents.y;
		    if ( vNewPos.y <= fGroundY )
		    {
			    vNewPos.y = fGroundY + 1.0f; 
			    bCollide = TRUE;
			    sResult.nCollideY = -1;
		    }
        }
        else
        {
		    if ( eRampType == ERampType_TL_BR )
		    {
			    fY0 = sBox2.vPos.y - sBox2.vExtents.y;
			    fY1 = sBox2.vPos.y + sBox2.vExtents.y;
		    }
		    else
		    {
			    fY0 = sBox2.vPos.y + sBox2.vExtents.y;
			    fY1 = sBox2.vPos.y - sBox2.vExtents.y;
		    }
		    FLOAT fT = ( fPlayerFootX - (sBox2.vPos.x - sBox2.vExtents.x) ) / ( sBox2.vExtents.x * 2.0f );
		    FLOAT fGroundY = fT * fY1 + ( 1.0f - fT ) * fY0 - sBox1.vExtents.y;
		    if ( vNewPos.y >= fGroundY )
		    {
			    vNewPos.y = fGroundY; 
			    bCollide = TRUE;
			    sResult.nCollideY = 1;
		    }
        }
	}

	sResult.vResult = vNewPos;
	return bCollide;
}
