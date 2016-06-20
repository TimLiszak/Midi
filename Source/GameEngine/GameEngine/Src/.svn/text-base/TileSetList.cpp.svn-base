#include "StdAfx.h"
#include "TileSetList.h"
#include "FileReader.h"
#include "TextParser.h"
#include "TileSetBitmap.h"

static const INT	MAX_LINE_CHAR	= 500;

void CTileSetList::Init( std::string strListFile )
{
	CFileReader FileReader;
	m_nNumberOfTiles = 0;
	
	if ( FileReader.Open( ( "Data/" + strListFile ).c_str() ) )
	{
		while( !FileReader.EndOfFile() )
		{
			std::string strLine = FileReader.ReadLine();

			CTextParser TextParser( strLine );
			std::string BitmapFile = TextParser.ParseToken();
			if ( BitmapFile.size() == 0 ) break;  // no more tokens

			STileInfo TileInfo;
			TileInfo.fTileHeight = (FLOAT)TextParser.ParseInt();
			TileInfo.fTileWidth = (FLOAT)TextParser.ParseInt();
			TileInfo.fBorderWidth = (FLOAT)TextParser.ParseInt();

			CTileSetBitmap* pBitmap = new CTileSetBitmap();
			pBitmap->Init( TileInfo, BitmapFile );
			m_nNumberOfTiles += pBitmap->GetNumOfTiles();

			m_BitmapSets.push_back( pBitmap );
		}
	}
	else
	{
		ASSERT(FALSE);
	}
}

void CTileSetList::Term()
{
	std::list<CTileSetBitmap*>::iterator it;
	for ( it = m_BitmapSets.begin() ; it != m_BitmapSets.end(); it++ )
	{
		delete (*it);
	}
	m_BitmapSets.clear();
}

void CTileSetList::DrawTile( INT nTileId, VECTOR vPos, BOOL bAlternate, BOOL bHorizFlip, BOOL bVertFlip )
{
	INT nTileCnt = 0;
	std::list<CTileSetBitmap*>::iterator it;
	for ( it = m_BitmapSets.begin() ; it != m_BitmapSets.end(); it++ )
	{
		if ( nTileId >= nTileCnt + (*it)->GetNumOfTiles() )
		{
			nTileCnt += (*it)->GetNumOfTiles();
		}
		else
		{
			INT nLocalTile = nTileId - nTileCnt;
			(*it)->DrawTile( nLocalTile, vPos, FALSE, bHorizFlip, bVertFlip );
			return;
		}
	}
}

FLOAT CTileSetList::GetTileWidth()
{
	return m_BitmapSets.front()->GetTileWidth();
}

FLOAT CTileSetList::GetTileHeight()
{
	return m_BitmapSets.front()->GetTileHeight();
}

INT CTileSetList::GetNumOfTiles()
{
	return m_nNumberOfTiles;
}
