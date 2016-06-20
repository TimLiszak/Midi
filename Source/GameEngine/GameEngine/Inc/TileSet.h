
#ifndef _TILESET_H_
#define _TILESET_H_

#include "TextureManager.h"
#include "Reflectable.h"

enum ETileCollision
{
    ETileCollision_None = 0,
    ETileCollision_Normal,
    ETileCollision_Slope_TL_BR,
    ETileCollision_Slope_BL_TR,
    ETileCollision_Slope_Ceil_TL_BR,
    ETileCollision_Slope_Ceil_BL_TR,

    ETileCollision_Max
};

class CTileProperties : public CReflectable, public CSerializable
{
public:
	REFLECTION_INFO;

	CTileProperties();
	void	Reset();
	virtual void	Serialize( CSerializer* Serializer );

	UINT 	nCollision;
	BOOL	bInstantDeath;
	INT		nAlternateTileId;
	BOOL	bCollisionAlternate;
	BOOL	bHorizFlip;
	BOOL	bVertFlip;
};

inline void CTileProperties::RegisterMembers(CReflectInfo* p_info)
{
	REGISTER_LIMIT( REF_UINT, nCollision, 0, ETileCollision_Slope_Ceil_BL_TR );
	REGISTER_LIMIT( REF_UINT, bInstantDeath, 0, 1 );
	REGISTER( REF_INT, nAlternateTileId );
	REGISTER_LIMIT( REF_UINT, bCollisionAlternate, 0, 1 );
	REGISTER_LIMIT( REF_UINT, bHorizFlip, 0, 1 );
	REGISTER_LIMIT( REF_UINT, bVertFlip, 0, 1 );
}

struct STileInfo
{
	FLOAT	fTileWidth;
	FLOAT	fTileHeight;
	FLOAT	fBorderWidth;
};

class CTileSet
{
	friend class CTileMap;

public:
	virtual void	Term() {}

	virtual void	Serialize( CSerializer* Serializer ) {}

	virtual void	DrawTile( INT nTileId, VECTOR vPos, BOOL bAlternate, BOOL bHorizFlip = FALSE, BOOL bVertFlip = FALSE ) = 0;
	virtual FLOAT	GetTileWidth() = 0;
	virtual FLOAT	GetTileHeight() = 0;
	virtual INT		GetNumOfTiles() = 0;

	virtual CTileProperties* GetTileProperties( INT nTileId ) = 0;
};

#endif
