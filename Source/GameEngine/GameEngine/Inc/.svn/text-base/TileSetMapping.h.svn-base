
#ifndef _TILESET_MAPPING_H_
#define _TILESET_MAPPING_H_

#include "TextureManager.h"
#include "Reflectable.h"
#include "TileSet.h"
#include "TileSetBitmap.h"

class CTileSetMapping : public CTileSet
{
	friend class CTileMap;

public:
	void	Init( STileInfo& TileInfo, std::string strFile );
	virtual void	Term();

	virtual void	Serialize( CSerializer* Serializer );

	virtual void	DrawTile( INT nTileId, VECTOR vPos, BOOL bAlternate, BOOL bHorizFlip = FALSE, BOOL bVertFlip = FALSE );

	virtual FLOAT	GetTileWidth();
	virtual FLOAT	GetTileHeight();
	virtual INT		GetNumOfTiles();

	void	SetTileMap( INT nIndex, INT nTileId );
	void	ShiftMapping( INT nNumTiles );

	virtual CTileProperties* GetTileProperties( INT nTileId );
	CTileSet*	GetMasterTileSet();

private:
	CTileSet*	m_pTileSet;
	std::vector<INT>				m_TileMapping;
	std::vector<CTileProperties>	m_TileProperties;
};

inline CTileSet* CTileSetMapping::GetMasterTileSet()
{
	return m_pTileSet;
}

inline FLOAT CTileSetMapping::GetTileWidth()
{
	return m_pTileSet->GetTileWidth();
}

inline FLOAT CTileSetMapping::GetTileHeight()
{
	return m_pTileSet->GetTileHeight();
}

inline INT CTileSetMapping::GetNumOfTiles()
{
	return m_TileMapping.size();
}

#endif
