#include "StdAfx.h"
#include "SpriteInfo.h"

CReflectInfo CSpriteInfo::m_ref_info; 

void CSpriteInfo::Serialize( CSerializer* Serializer )
{
	Serializer->Serialize( strFilename );
	Serializer->Serialize( fTexCoordU0 );
	Serializer->Serialize( fTexCoordU1 );
	Serializer->Serialize( fTexCoordV0 );
	Serializer->Serialize( fTexCoordV1 );
	Serializer->Serialize( bTile );
	Serializer->Serialize( bHorizFlip );
	Serializer->Serialize( bVertFlip );
}
