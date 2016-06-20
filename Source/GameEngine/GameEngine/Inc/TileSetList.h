
#ifndef _TILESET_LIST_H_
#define _TILESET_LIST_H_

#include "TextureManager.h"
#include "Reflectable.h"
#include "TileSet.h"
#include "TileSetBitmap.h"

class CTileSetList : public CTileSet
{
	friend class CTileMap;

public:
	void	Init( std::string strListFile );
	virtual void	Term();

	virtual void	DrawTile( INT nTileId, VECTOR vPos, BOOL bAlternate, BOOL bHorizFlip = FALSE, BOOL bVertFlip = FALSE );

	virtual FLOAT	GetTileWidth();
	virtual FLOAT	GetTileHeight();
	virtual INT		GetNumOfTiles();

	virtual CTileProperties* GetTileProperties( INT nTileId );

private:
	std::list< CTileSetBitmap* >	m_BitmapSets;
	INT		m_nNumberOfTiles;
	CTileProperties	m_DefaultProperties;
};

inline CTileProperties* CTileSetList::GetTileProperties( INT nTileId )
{
	return &m_DefaultProperties;
}

#endif
