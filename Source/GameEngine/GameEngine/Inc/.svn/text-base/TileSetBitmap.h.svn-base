
#ifndef _TILESET_BITMAP_H_
#define _TILESET_BITMAP_H_

#include "TextureManager.h"
#include "Reflectable.h"
#include "TileSet.h"

class CTileSetBitmap : public CTileSet
{
	friend class CTileMap;

public:
	void	Init( STileInfo& TileInfo, std::string strBitmapFile );
	virtual void	Term();

	virtual void	DrawTile( INT nTileId, VECTOR vPos, BOOL bAlternate, BOOL bHorizFlip = FALSE, BOOL bVertFlip = FALSE );

	virtual FLOAT	GetTileWidth();
	virtual FLOAT	GetTileHeight();
	virtual INT		GetNumOfTiles();

	virtual CTileProperties* GetTileProperties( INT nTileId );

private:
	CTexture*	m_pTexture;
	STileInfo	m_TileInfo;
	INT			m_nNumTilesX;
	INT			m_nNumTilesY;
	CTileProperties	m_DefaultProperties;
};

inline FLOAT CTileSetBitmap::GetTileWidth()
{
	return m_TileInfo.fTileWidth;
}

inline FLOAT CTileSetBitmap::GetTileHeight()
{
	return m_TileInfo.fTileHeight;
}

inline INT CTileSetBitmap::GetNumOfTiles()
{
	return m_nNumTilesX * m_nNumTilesY;
}

inline CTileProperties* CTileSetBitmap::GetTileProperties( INT nTileId )
{
	return &m_DefaultProperties;
}

#endif
