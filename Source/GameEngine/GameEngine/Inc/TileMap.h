
#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include "TileSet.h"
#include "Collision.h"

enum ETileModifier
{
	ETileModifier_None = 0,
	ETileModifier_OpenDoor,

	ETileModifier_Max
};

class CTileMap
{
public:
	CTileMap() : m_TileData(NULL), m_bShowGrid(FALSE), m_bDrawCollision(FALSE), m_pTileSet(NULL) {}

	void	Init( STileInfo& TileInfo, std::string strBitmapFile, VECTOR vSize );
	void	Term();

	void	Render();

	void	Serialize( CSerializer* Serializer );

    std::string GetTileSetFile();
    void        SetTileSetFile( std::string strFile );

	inline VECTOR GetSize() { return m_vSize; }
	void	Resize( VECTOR vSize );

	BOOL	CheckSweepCollision( CCollision::SweepResult& sResult, CCollision::SAABBox& sBox, VECTOR& vVel );
    BOOL    CheckLineCollision( CCollision::SweepResult& sResult, VECTOR vPoint1, VECTOR vPoint2 );
	
	CTileSet* GetTileSet();
	void	SetTile( VECTOR vPos, INT nTileId );
	void	SetCollision( VECTOR vPos, INT nCollisionType );
	INT		GetTile( VECTOR vPos );
	void	ClearToTile( INT nTileId );
	void	SwitchTile( INT nOldTileId, INT nTileId );

	void	OpenDoor( VECTOR vTileMin, VECTOR vTileMax );
	void	CloseDoor( VECTOR vTileMin, VECTOR vTileMax );

	void	ToggleGrid();
	void	ToggleDrawCollision();

	void	ShiftDown( INT nTileX, INT nTileY );
	void	ShiftRight( INT nTileX, INT nTileY );
	void	ShiftUp( INT nTileX, INT nTileY );
	void	ShiftLeft( INT nTileX, INT nTileY );

	void	EnableAlternateTiles( BOOL bEnable );

private:
	struct SPlacedTileProperties
	{
		SPlacedTileProperties() : nTileId(-1), nCollision(0), nModifier(0) {}
		INT	nTileId;
		INT	nCollision;
		INT nModifier;
	};
	SPlacedTileProperties* GetTileProperties( INT x, INT y );
	SPlacedTileProperties* GetTileProperties( VECTOR vTile );

	void	RenderTiles();
	void	RenderGrid();
	void	RenderCollision( VECTOR vPos, INT nTileId, CTileProperties* pProperties );
	VECTOR	GetTileCoordinates( VECTOR vPos );

	ETileCollision	GetCollisionType( CTileProperties* pProperties );

	void	LoadTileSet();

	CTileSet*	m_pTileSet;
	VECTOR		m_vSize;

	BOOL	m_bShowGrid;
	BOOL	m_bDrawCollision;
	BOOL	m_bAlternateTiles;

	STileInfo		m_TileInfo;
	std::string		m_strTileSetFile;

	std::vector< SPlacedTileProperties >* m_TileData;
};

inline CTileSet* CTileMap::GetTileSet()
{
	return m_pTileSet;
}

inline void CTileMap::ToggleGrid()
{
	m_bShowGrid = !m_bShowGrid;
}

inline void CTileMap::ToggleDrawCollision()
{
	m_bDrawCollision = !m_bDrawCollision;
}

inline void CTileMap::EnableAlternateTiles( BOOL bEnable )
{
	m_bAlternateTiles = bEnable;
}

inline std::string CTileMap::GetTileSetFile()
{
    return m_strTileSetFile;
}

inline void CTileMap::SetTileSetFile( std::string strFile )
{
    m_strTileSetFile = strFile;
}


#endif
