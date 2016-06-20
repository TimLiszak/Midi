#include "StdAfx.h"
#include "TileSetMapping.h"
#include "FileReader.h"
#include "TextParser.h"
#include "TileSetBitmap.h"
#include "TileSetList.h"

static const INT	DEFAULT_NUM_TILES	= 24 * 3;

void CTileSetMapping::Init( STileInfo& TileInfo, std::string strFile )
{
	// define default mapping
	m_TileMapping.resize( DEFAULT_NUM_TILES );
	m_TileProperties.resize( DEFAULT_NUM_TILES );
	for ( INT i = 0; i < DEFAULT_NUM_TILES; i++ )
	{
		m_TileMapping[i] = i;
		m_TileProperties[i].Reset();
	}

	// load tile set
	INT nSize = strFile.size();
	std::string strExt = strFile.substr( nSize - 4, nSize - 1 );

	if ( strExt == ".bmp" )
	{
		m_pTileSet = new CTileSetBitmap();
		((CTileSetBitmap*)m_pTileSet)->Init( TileInfo, strFile );
	}
	else
	{
		m_pTileSet = new CTileSetList();
		((CTileSetList*)m_pTileSet)->Init( strFile );
	}
}

void CTileSetMapping::Term()
{
	m_pTileSet->Term();
	delete m_pTileSet;
}

void CTileSetMapping::DrawTile( INT nTileId, VECTOR vPos, BOOL bAlternate, BOOL bHorizFlip, BOOL bVertFlip )
{
	if ( nTileId < (INT)m_TileMapping.size() )
	{
		if ( bAlternate && m_TileProperties[nTileId].nAlternateTileId >= 0 )
		{
			m_pTileSet->DrawTile( m_TileProperties[nTileId].nAlternateTileId, vPos, FALSE, bHorizFlip, bVertFlip );
		}
		else
		{
			m_pTileSet->DrawTile( m_TileMapping[nTileId], vPos, FALSE, bHorizFlip, bVertFlip );
		}
	}
}

void CTileSetMapping::SetTileMap( INT nIndex, INT nTileId )
{
	m_TileMapping[nIndex] = nTileId;
}

void CTileSetMapping::ShiftMapping( INT nNumTiles )
{
	for ( INT i = 0; i < (INT)m_TileMapping.size(); i++ )
	{
		m_TileMapping[i] += nNumTiles;
		while ( m_TileMapping[i] > m_pTileSet->GetNumOfTiles() )
		{
			m_TileMapping[i] -= m_pTileSet->GetNumOfTiles();
		}
	}
}

void CTileSetMapping::Serialize( CSerializer* Serializer )
{
	Serializer->Serialize( m_TileMapping );
	if ( Serializer->GetVersion() >= EFileVersion_TileProperties )
	{
		Serializer->Serialize( m_TileProperties );
	}
	else
	{
		m_TileProperties.resize( m_TileMapping.size() );
		for ( UINT i = 0; i < m_TileMapping.size(); i++ )
		{
			m_TileProperties[i].Reset();
		}
		
	}
}

CTileProperties* CTileSetMapping::GetTileProperties( INT nTileId )
{
    if ( nTileId >= 0 && nTileId < (INT)m_TileProperties.size() )
	{
		return &m_TileProperties[nTileId];
	}
	return NULL;
}
