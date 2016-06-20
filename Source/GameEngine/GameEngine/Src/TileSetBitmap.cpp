#include "StdAfx.h"
#include "TileSetBitmap.h"

void CTileSetBitmap::Init( STileInfo& TileInfo, std::string strBitmapFile )
{
	m_TileInfo = TileInfo;
	//m_strBitmapFile = strBitmapFile;

	std::string strFileName = strBitmapFile;
	m_pTexture = GetGameEngine()->GetTextureManager()->BuildTexture( strFileName );

	m_nNumTilesX = (INT)((m_pTexture->fWidth - m_TileInfo.fBorderWidth) / (m_TileInfo.fTileWidth + m_TileInfo.fBorderWidth));
	m_nNumTilesY = (INT)((m_pTexture->fHeight - m_TileInfo.fBorderWidth) / (m_TileInfo.fTileHeight + m_TileInfo.fBorderWidth));

}

void CTileSetBitmap::Term()
{
}

void CTileSetBitmap::DrawTile( INT nTileId, VECTOR vPos, BOOL bAlternate, BOOL bHorizFlip, BOOL bVertFlip )
{
	glEnable( GL_TEXTURE_2D );

	glPushMatrix();
	glTranslatef( vPos.x, vPos.y, 0.0f );

	glBindTexture( GL_TEXTURE_2D, m_pTexture->nTexId );

    nTileId = m_nNumTilesX * m_nNumTilesY - nTileId - 1;
	INT fIndxY = nTileId / m_nNumTilesX;
	INT fIndxX = ( m_nNumTilesX - 1 ) - ( nTileId - fIndxY * m_nNumTilesX );

	double fTX = m_TileInfo.fTileWidth / m_pTexture->fWidth;
	double fTY = m_TileInfo.fTileHeight / m_pTexture->fHeight;
	double fBX = m_TileInfo.fBorderWidth / m_pTexture->fWidth;
	double fBY = m_TileInfo.fBorderWidth / m_pTexture->fHeight;

	FLOAT u0 = (FLOAT)( fBX + fIndxX * (fBX + fTX) );
	FLOAT u1 = (FLOAT)( fBX + fTX + fIndxX * (fBX + fTX) );
	FLOAT v0 = (FLOAT)( fBY + fIndxY * (fBY + fTY) );
	FLOAT v1 = (FLOAT)( fBY + fTY + fIndxY * (fBY + fTY) );

	if ( bHorizFlip )
	{
		FLOAT Temp = u0;
		u0 = u1;
		u1 = Temp;
	}
	if ( bVertFlip )
	{
		FLOAT Temp = v0;
		v0 = v1;
		v1 = Temp;
	}

    FLOAT x0 = 0.0f;
    FLOAT x1 = m_TileInfo.fTileWidth;
    FLOAT y0 = 0.0f;
    FLOAT y1 = m_TileInfo.fTileHeight;

	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTexCoord2f( u0, v1 ); 
		glVertex2f( x0, y0 );

		glTexCoord2f( u0, v0 ); 
		glVertex2f( x0, y1 );

		glTexCoord2f( u1, v0 ); 
		glVertex2f( x1, y1 );

		glTexCoord2f( u1, v1 ); 
		glVertex2f( x1, y0 );
	glEnd();
	glPopMatrix();

	glDisable( GL_TEXTURE_2D );
}
