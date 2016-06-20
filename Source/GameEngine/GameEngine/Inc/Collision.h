#ifndef _COLLISION_H_
#define _COLLISION_H_

class CCollision
{
public:
	enum ERampType
	{
		ERampType_TL_BR,
		ERampType_BL_TR,
        ERampType_Ceil_TL_BR,
        ERampType_Ceil_BL_TR,

		ERampType_Max
	};

	class SweepResult
	{
		public:
			SweepResult() : 
				pActor(NULL),
				nCollideX(0),
				nCollideY(0),
				pTileProperties(NULL)
			{
			}

			class CActor*	pActor;
			VECTOR	vResult;
			INT		nCollideX;
			INT		nCollideY;
			class CTileProperties* pTileProperties;
	};

	struct SAABBox
	{
        SAABBox() {}
		SAABBox( VECTOR e, VECTOR p ) : vExtents(e), vPos(p) {}
		VECTOR vExtents;
		VECTOR vPos;
	};

	static BOOL	CheckAABoxOverlap( SAABBox& sBox1, SAABBox& sBox2 );
	static BOOL CheckLineBox( VECTOR vPoint1, VECTOR vPoint2, SAABBox& sBox, FLOAT &fT );
	static BOOL	CheckAABoxSweep( SweepResult& sResult, SAABBox& sBox1, VECTOR& vVel1, SAABBox& sBox2, VECTOR vVel2 = VECTOR(0,0) );
	static BOOL	CheckRampCollision( SweepResult& sResult, SAABBox& sBox1, VECTOR& vVel1, SAABBox& sBox2, ERampType eRampType );

};

#endif
