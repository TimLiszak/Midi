#include "StdAfx.h"
#include "TileSet.h"

CReflectInfo CTileProperties::m_ref_info; 

CTileProperties::CTileProperties()
{
	Reset();
}

void CTileProperties::Reset()
{
	nCollision = ETileCollision_Normal;
	bInstantDeath = FALSE;
	nAlternateTileId = -1;
	bCollisionAlternate = TRUE;
	bHorizFlip = FALSE;
	bVertFlip = FALSE;
}

void CTileProperties::Serialize( CSerializer* Serializer )
{
	if ( Serializer->GetVersion() >= EFileVersion_TileSlopes )
  	{
 	    Serializer->Serialize( nCollision );
	}
    else
  	{
        BOOL bCollision;
 	    Serializer->Serialize( bCollision );
        nCollision = bCollision ? 1 : 0;
    }
    
	Serializer->Serialize( bInstantDeath );
	Serializer->Serialize( nAlternateTileId );
	Serializer->Serialize( bCollisionAlternate );

	if ( Serializer->GetVersion() >= EFileVersion_TileFlip )
	{
		Serializer->Serialize( bHorizFlip );
		Serializer->Serialize( bVertFlip );
	}
}
