
#ifndef _SPRITE_INFO_H_
#define _SPRITE_INFO_H_

#include "Reflectable.h"

class CSpriteInfo : public CReflectable, public CSerializable
{
public:
	REFLECTION_INFO;

	CSpriteInfo() : 
		fTexCoordU0(0.0f),
		fTexCoordU1(1.0f),
		fTexCoordV0(0.0f),
		fTexCoordV1(1.0f),
		bTile( FALSE ),
		bHorizFlip( FALSE ),
		bVertFlip( FALSE )
	{
	}

	virtual void	Serialize( CSerializer* Serializer );

	std::string	strFilename;
	FLOAT	fTexCoordU0;
	FLOAT	fTexCoordU1;
	FLOAT	fTexCoordV0;
	FLOAT	fTexCoordV1;
	BOOL	bTile;
	BOOL	bHorizFlip;
	BOOL	bVertFlip;
};

inline void CSpriteInfo::RegisterMembers(CReflectInfo* p_info)
{
	REGISTER( REF_STRING, strFilename );
	REGISTER_INC( REF_FLOAT, fTexCoordU0, 0.05f );
	REGISTER_INC( REF_FLOAT, fTexCoordU1, 0.05f );
	REGISTER_INC( REF_FLOAT, fTexCoordV0, 0.05f );
	REGISTER_INC( REF_FLOAT, fTexCoordV1, 0.05f );
	REGISTER_LIMIT( REF_UINT, bTile, 0, 1 );
	REGISTER_LIMIT( REF_UINT, bHorizFlip, 0, 1 );
	REGISTER_LIMIT( REF_UINT, bVertFlip, 0, 1 );
}

#endif
