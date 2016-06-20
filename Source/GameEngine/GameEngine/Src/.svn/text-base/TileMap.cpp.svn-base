#include "StdAfx.h"
#include "TileMap.h"
#include "Render2d.h"
#include "View.h"
#include "Collision.h"
#include "TileSetMapping.h"

static const COLOUR_RGB		GRID_CLR = COLOUR_RGB(0.6f, 0.6f, 0.6f);
static const FLOAT			COLLISION_SKIN	= 1.0f;

void CTileMap::Init( STileInfo& TileInfo, std::string strBitmapFile, VECTOR vSize )
{
	m_strTileSetFile = strBitmapFile;
	m_TileInfo = TileInfo;
	m_vSize = vSize;
	m_bAlternateTiles = FALSE;

	LoadTileSet();

	m_bShowGrid = FALSE;
	m_TileData = new std::vector< SPlacedTileProperties >( (INT)(m_vSize.x * m_vSize.y) );
}

void CTileMap::Term()
{
	m_pTileSet->Term();
	SAFE_DELETE( m_pTileSet );
	SAFE_DELETE( m_TileData );
}

void CTileMap::Serialize( CSerializer* Serializer )
{
	Serializer->Serialize( m_vSize );

	if ( Serializer->IsReading() )
	{
		ASSERT( !m_TileData );
		m_TileData = new std::vector< SPlacedTileProperties >( (INT)(m_vSize.x * m_vSize.y) );
	}

	Serializer->BulkSerialize( &m_TileInfo, sizeof(m_TileInfo) );
	Serializer->Serialize( m_strTileSetFile );

	if ( Serializer->GetVersion() < EFileVersion_TileSetMapping )
	{
		std::string OldFile = m_strTileSetFile;

		m_strTileSetFile = "Tiles/TilesAll.tileset";
		ASSERT( !m_pTileSet );
		LoadTileSet();

		if ( OldFile == "Tiles02.bmp" )
		{
			((CTileSetMapping*)m_pTileSet)->ShiftMapping( 72 );
		}
		else if ( OldFile == "Tiles03.bmp" )
		{
			((CTileSetMapping*)m_pTileSet)->ShiftMapping( 72 + 90 );
		}
	}
	else
	{
		if ( Serializer->IsReading() )
		{
			ASSERT( !m_pTileSet );
			LoadTileSet();
		}
		m_pTileSet->Serialize( Serializer );
	}

	for ( UINT i = 0; i < (*m_TileData).size(); i++ )
	{
		Serializer->Serialize( ((*m_TileData)[i]).nTileId );
		Serializer->Serialize( ((*m_TileData)[i]).nCollision );

        /*
		if ( Serializer->GetVersion() < EFileVersion_TileProperties )
		{
			CTileProperties* pProp = m_pTileSet->GetTileProperties( ((*m_TileData)[i]).nTileId );

			if ( pProp && ((*m_TileData)[i]).nCollision == ETileCollision_InstantDeath )
			{
				pProp->bInstantDeath = TRUE;
			}
		}*/
	}
}

void CTileMap::Render()
{
	RenderTiles();

	if ( m_bShowGrid )
	{
		RenderGrid();
	}
}

void CTileMap::RenderTiles()
{
	VECTOR vWindowMin, vWindowMax;
	GetGameEngine()->GetView()->GetViewableBoundingBox( vWindowMin, vWindowMax );

	FLOAT tw = m_pTileSet->GetTileWidth();
	FLOAT th = m_pTileSet->GetTileHeight();

	INT nMinX = max( (INT)(vWindowMin.x / tw), 0 );
	INT nMinY = max( (INT)(vWindowMin.y / th), 0 );
	INT nMaxX = min( (INT)(vWindowMax.x / tw) + 1, (INT)m_vSize.x );
	INT nMaxY = min( (INT)(vWindowMax.y / th) + 1, (INT)m_vSize.y );

	for ( INT y = nMinY; y < nMaxY; y++ )
	{
		for ( INT x = nMinX; x < nMaxX; x++ )
		{
			VECTOR vPos( x * tw, y * th );
			SPlacedTileProperties* pProp = GetTileProperties(x, y);
			CTileProperties* pProperties = m_pTileSet->GetTileProperties( pProp->nTileId );

			if ( pProp->nTileId >= 0 && pProp->nModifier != ETileModifier_OpenDoor )
			{
				m_pTileSet->DrawTile( pProp->nTileId, vPos, m_bAlternateTiles, pProperties->bHorizFlip, pProperties->bVertFlip );
			}

			if ( m_bDrawCollision )
			{
				RenderCollision( vPos, pProp->nTileId, pProperties );
			}
		}
	}
}

void CTileMap::RenderGrid()
{
	FLOAT tw = m_pTileSet->GetTileWidth();
	FLOAT th = m_pTileSet->GetTileHeight();

	VECTOR p0( 0.0f, 0.0f );
	VECTOR p1( tw * m_vSize.x, 0.0f );
	for ( UINT y = 0; y < m_vSize.y; y++ )
	{
		CRender2d::DrawLine( p0, p1, GRID_CLR );
		p0.y += th;
		p1.y += th;
	}

	p0.Set( 0.0f, 0.0f );
	p1.Set( 0.0f, th * m_vSize.y );
	for ( UINT x = 0; x < m_vSize.x; x++ )
	{
		CRender2d::DrawLine( p0, p1, GRID_CLR );
		p0.x += tw;
		p1.x += tw;
	}
}

void CTileMap::RenderCollision( VECTOR vPos, INT nTileId, CTileProperties* pProperties )
{
	if ( pProperties )
	{
		FLOAT tw = m_pTileSet->GetTileWidth();
		FLOAT th = m_pTileSet->GetTileHeight();
		VECTOR vExtents( tw * 0.5f, th * 0.5f );
		FLOAT fAlpha = 0.25f;
        vPos += vExtents;

		if ( pProperties->bInstantDeath )
		{
			CRender2d::DrawRectFill( vPos, vExtents, 0.0f, COLOUR_RGB( 1.0f, 0.0f, 0.0f, fAlpha ) );
		}
		else
		{
            COLOUR_RGB Clr( 1.0f, 1.0f, 0.0f, fAlpha );
            ETileCollision eType = GetCollisionType( pProperties );
            switch( eType )
            {
                case ETileCollision_Normal:
                {
			        CRender2d::DrawRectFill( vPos, vExtents, 0.0f, Clr );
                }
                break;
                case ETileCollision_Slope_TL_BR:
                {
                    CRender2d::DrawTriangle( vPos - vExtents, vPos + vExtents, vPos + VECTOR( -vExtents.x, vExtents.y ), Clr );
                }
                break;
                case ETileCollision_Slope_BL_TR:
                {
                    CRender2d::DrawTriangle( vPos + VECTOR( -vExtents.x, vExtents.y ), vPos + VECTOR( vExtents.x, -vExtents.y ), vPos + vExtents, Clr );
                }
                break;
                case ETileCollision_Slope_Ceil_TL_BR:
                {
                    CRender2d::DrawTriangle( vPos - vExtents, vPos + VECTOR( vExtents.x, -vExtents.y ), vPos + vExtents, Clr );
                }
                break;
                case ETileCollision_Slope_Ceil_BL_TR:
                {
                    CRender2d::DrawTriangle( vPos + VECTOR( -vExtents.x, vExtents.y ), vPos - vExtents, vPos + VECTOR( vExtents.x, -vExtents.y ), Clr );
                }
                break;
                
            }
		}
	}
}

CTileMap::SPlacedTileProperties* CTileMap::GetTileProperties( INT x, INT y )
{
	INT nIndx = (INT)(x + y * m_vSize.x);
	return &((*m_TileData)[nIndx]);
}

CTileMap::SPlacedTileProperties* CTileMap::GetTileProperties( VECTOR vTile )
{
	return GetTileProperties( (INT)vTile.x, (INT)vTile.y );
}

void CTileMap::SetTile( VECTOR vPos, INT nTileId )
{
	VECTOR vTile = GetTileCoordinates( vPos );
	if ( vTile.x >= 0 && vTile.x < m_vSize.x &&
		 vTile.y >= 0 && vTile.y < m_vSize.y )
	{
		SPlacedTileProperties* pProp = GetTileProperties( vTile );
		pProp->nTileId = nTileId;
	}
}

INT CTileMap::GetTile( VECTOR vPos )
{
	VECTOR vTile = GetTileCoordinates( vPos );
	if ( vTile.x >= 0 && vTile.x < m_vSize.x &&
		 vTile.y >= 0 && vTile.y < m_vSize.y )
	{
		SPlacedTileProperties* pProp = GetTileProperties( vTile );
		return pProp->nTileId;
	}
	return -1;
}

void CTileMap::SetCollision( VECTOR vPos, INT nCollisionType )
{
	VECTOR vTile = GetTileCoordinates( vPos );
	if ( vTile.x >= 0 && vTile.x < m_vSize.x &&
		 vTile.y >= 0 && vTile.y < m_vSize.y )
	{
		SPlacedTileProperties* pProp = GetTileProperties( vTile );
		pProp->nCollision = nCollisionType;
	}
}

VECTOR CTileMap::GetTileCoordinates( VECTOR vPos )
{
	FLOAT tw = m_pTileSet->GetTileWidth();
	FLOAT th = m_pTileSet->GetTileHeight();
	return VECTOR( (INT)(vPos.x / tw), (INT)(vPos.y / th) );
}

BOOL CTileMap::CheckSweepCollision( CCollision::SweepResult& sResult, CCollision::SAABBox& sBox, VECTOR& vVel )
{
	BOOL bCollision = FALSE;
	FLOAT tw = m_pTileSet->GetTileWidth();
	FLOAT th = m_pTileSet->GetTileHeight();
	VECTOR vTileExtents( tw * 0.5f, th * 0.5f );

	VECTOR vCurrent = sBox.vPos;
	VECTOR vTarget = sBox.vPos + vVel;

	VECTOR vTopLeft0 = GetTileCoordinates( VECTOR( vCurrent.x - sBox.vExtents.x - COLLISION_SKIN, vCurrent.y - sBox.vExtents.y - COLLISION_SKIN ) );
	VECTOR vBotRight0 = GetTileCoordinates( VECTOR( vCurrent.x + sBox.vExtents.x + COLLISION_SKIN, vCurrent.y + sBox.vExtents.y + COLLISION_SKIN ) );

	VECTOR vTopLeft1 = GetTileCoordinates( VECTOR( vTarget.x - sBox.vExtents.x - COLLISION_SKIN, vTarget.y - sBox.vExtents.y - COLLISION_SKIN ) );
	VECTOR vBotRight1 = GetTileCoordinates( VECTOR( vTarget.x + sBox.vExtents.x + COLLISION_SKIN, vTarget.y + sBox.vExtents.y + COLLISION_SKIN ) );

	vTopLeft0.x = min( vTopLeft0.x, vTopLeft1.x );
	vBotRight0.x = max( vBotRight0.x, vBotRight1.x );
	vTopLeft0.y = min( vTopLeft0.y, vTopLeft1.y );
	vBotRight0.y = max( vBotRight0.y, vBotRight1.y );

	vTopLeft0.x = Math::Clamp( vTopLeft0.x, 0.0f, m_vSize.x - 1.0f );
	vTopLeft0.y = Math::Clamp( vTopLeft0.y, 0.0f, m_vSize.y - 1.0f );
	vBotRight0.x = Math::Clamp( vBotRight0.x, 0.0f, m_vSize.x - 1.0f );
	vBotRight0.y = Math::Clamp( vBotRight0.y, 0.0f, m_vSize.y - 1.0f );

	for (INT tx = (INT)vTopLeft0.x; tx <= (INT)vBotRight0.x; tx++)
	{
		for (INT ty = (INT)vTopLeft0.y; ty <= (INT)vBotRight0.y; ty++)
		{
			SPlacedTileProperties* pProp = GetTileProperties( tx, ty );
			CTileProperties* pProperties = m_pTileSet->GetTileProperties( pProp->nTileId );

            ETileCollision eType = GetCollisionType( pProperties );
			if ( eType != ETileCollision_None )
			{
				BOOL bInstantDeath = pProperties->bInstantDeath;

				if ( pProp->nModifier != ETileModifier_OpenDoor && !bInstantDeath )
				{
					VECTOR vPos( tx * tw, ty * th );
					CCollision::SAABBox sTileBox( vTileExtents, vPos + vTileExtents );

                    switch( eType )
                    {
                        case ETileCollision_Normal:
                        {
					        if ( CCollision::CheckAABoxSweep( sResult, sBox, vVel, sTileBox ) )
					        {
						        vVel = sResult.vResult - sBox.vPos;
						        sResult.pTileProperties = pProperties;
						        bCollision = TRUE;
					        }
                        }
                        break;

                        case ETileCollision_Slope_TL_BR:
                        {
                            if ( CCollision::CheckRampCollision( sResult, sBox, vVel, sTileBox, CCollision::ERampType_TL_BR ) )
					        {
						        vVel = sResult.vResult - sBox.vPos;
						        sResult.pTileProperties = pProperties;
						        bCollision = TRUE;
					        }
                        }
                        break;

                        case ETileCollision_Slope_BL_TR:
                        {
					        if ( CCollision::CheckRampCollision( sResult, sBox, vVel, sTileBox, CCollision::ERampType_BL_TR ) )
					        {
						        vVel = sResult.vResult - sBox.vPos;
						        sResult.pTileProperties = pProperties;
						        bCollision = TRUE;
					        }
                        }
                        break;

                        case ETileCollision_Slope_Ceil_TL_BR:
                        {
                            if ( CCollision::CheckRampCollision( sResult, sBox, vVel, sTileBox, CCollision::ERampType_Ceil_TL_BR ) )
					        {
						        vVel = sResult.vResult - sBox.vPos;
						        sResult.pTileProperties = pProperties;
						        bCollision = TRUE;
					        }
                        }
                        break;

                        case ETileCollision_Slope_Ceil_BL_TR:
                        {
					        if ( CCollision::CheckRampCollision( sResult, sBox, vVel, sTileBox, CCollision::ERampType_Ceil_BL_TR ) )
					        {
						        vVel = sResult.vResult - sBox.vPos;
						        sResult.pTileProperties = pProperties;
						        bCollision = TRUE;
					        }
                        }
                        break;
                    }
				}
			}
		}
	}

	// Check instant death
	for (INT tx = (INT)vTopLeft0.x; tx <= (INT)vBotRight0.x; tx++)
	{
		for (INT ty = (INT)vTopLeft0.y; ty <= (INT)vBotRight0.y; ty++)
		{
			SPlacedTileProperties* pProp = GetTileProperties( tx, ty );
			CTileProperties* pProperties = m_pTileSet->GetTileProperties( pProp->nTileId );
			BOOL bInstantDeath = pProperties && pProperties->bInstantDeath;

			if ( pProp->nModifier != ETileModifier_OpenDoor && bInstantDeath )
			{
				VECTOR vPos( tx * tw, ty * th );
				CCollision::SAABBox sTileBox( vTileExtents, vPos + vTileExtents );
				if ( CCollision::CheckAABoxSweep( sResult, sBox, vVel, sTileBox ) )
				{
					vVel = sResult.vResult - sBox.vPos;
					sResult.pTileProperties = pProperties;
					bCollision = TRUE;
				}
			}

		}
	}

	return bCollision;
}

BOOL CTileMap::CheckLineCollision( CCollision::SweepResult& sResult, VECTOR vPoint0, VECTOR vPoint1 )
{
	FLOAT tw = m_pTileSet->GetTileWidth();
	FLOAT th = m_pTileSet->GetTileHeight();

    bool bFoundSpace = false;
    int tileX = -1;
    int tileY = -1;

    int x0 = (INT)vPoint0.x;
    int y0 = (INT)vPoint0.y;
    int x1 = (INT)vPoint1.x;
    int y1 = (INT)vPoint1.y;

    int dx = abs(x1-x0);
    int dy = abs(y1-y0) ;
    int sx = ( x0 < x1 ) ? 1 : -1;
    int sy = ( y0 < y1 ) ? 1 : -1;
    int err = dx-dy;

    BOOL bLoop = TRUE;
    while( bLoop )
    {
        int newTileX = (INT)(x0 / tw);
        int newTileY = (INT)(y0 / th);
        if ( tileX != newTileX || tileY != newTileY )
        {
		    SPlacedTileProperties* pProp = GetTileProperties( newTileX, newTileY );
		    CTileProperties* pProperties = m_pTileSet->GetTileProperties( pProp->nTileId );
            ETileCollision eType = GetCollisionType( pProperties );
		    if ( eType != ETileCollision_None )
		    {
                if ( bFoundSpace )
                {
                    // collide
                    sResult.vResult.x = (FLOAT)x0;
                    sResult.vResult.y = (FLOAT)y0;
                    return TRUE;
                }
            }
            else
            {
                bFoundSpace = TRUE;
            }
            tileX = newTileX;
            tileY = newTileY;
        }

        if ( x0 == x1 && y0 == y1 )
        {
            break;
        }

        int e2 = 2*err;

        if ( e2 > -dy )
        {
            err = err - dy;
            x0 = x0 + sx;
        }
        if ( e2 < dx )
        {
            err = err + dx;
            y0 = y0 + sy; 
        }
    }


    /*
    INT dx = abs(x1-x0);
    INT dy = abs(y1-y0);
    INT sx = ( x0 < x1 ) ? 1 : -1;
    INT sy = ( y0 < y1 ) ? 1 : -1;
    INT err = dx-dy;

    BOOL bLoop = TRUE;
    while( bLoop )
    {
        // Check collision
		SPlacedTileProperties* pProp = GetTileProperties( x0, y0 );
		CTileProperties* pProperties = m_pTileSet->GetTileProperties( pProp->nTileId );
        ETileCollision eType = GetCollisionType( pProperties );
		if ( eType != ETileCollision_None )
		{
            sResult.vResult.x = x0 * tw;
            sResult.vResult.y = y0 * th;
            return TRUE;
        }

        if ( x0 == x1 && y0 == y1 )
        {
            break;
        }

        INT e2 = 2*err;
        if ( e2 > -dy )
        {
            err = err - dy;
            x0 = x0 + sx;
        }
        if ( e2 < dx )
        {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
    */

    return FALSE;
}

void CTileMap::Resize( VECTOR vSize )
{
	std::vector< SPlacedTileProperties >* pNewTileData = new std::vector< SPlacedTileProperties >( (INT)(vSize.x * vSize.y) );
	for (INT x = 0; x < (INT)Math::Min( vSize.x, m_vSize.x ); x++)
	{
		for (INT y = 0; y < (INT)Math::Min( vSize.y, m_vSize.y ); y++)
		{
			INT nNewIndx = (INT)(x + y * vSize.x);
			(*pNewTileData)[nNewIndx] = *GetTileProperties( x, y );
		}
	}
	delete m_TileData;
	m_TileData = pNewTileData;
	m_vSize = vSize;
}

void CTileMap::ShiftDown( INT nTileX, INT nTileY )
{
	for ( INT y = (INT)m_vSize.y - 1; y > nTileY; y-- )
	{
		for ( INT x = nTileX; x < (INT)m_vSize.x; x++ )
		{
			*GetTileProperties( x, y ) = *GetTileProperties( x, y - 1 );
		}
	}

	for ( INT x = nTileX; x < (INT)m_vSize.x; x++ )
	{
		SPlacedTileProperties* pProp = GetTileProperties( x, nTileY );
		pProp->nTileId = -1;
		pProp->nCollision = 0;
	}
}

void CTileMap::ShiftRight( INT nTileX, INT nTileY )
{
	for ( INT x = (INT)m_vSize.x - 1; x > nTileX; x-- )
	{
		for ( INT y = nTileY; y < (INT)m_vSize.y; y++ )
		{
			*GetTileProperties( x, y ) = *GetTileProperties( x - 1, y );
		}
	}

	for ( INT y = nTileY; y < (INT)m_vSize.y; y++ )
	{
		SPlacedTileProperties* pProp = GetTileProperties( nTileX, y );
		pProp->nTileId = -1;
		pProp->nCollision = 0;
	}
}

void CTileMap::ShiftUp( INT nTileX, INT nTileY )
{
	for ( INT y = nTileY; y < (INT)m_vSize.y - 1; y++ )
	{
		for ( INT x = nTileX; x < (INT)m_vSize.x; x++ )
		{
			*GetTileProperties( x, y ) = *GetTileProperties( x, y + 1 );
		}
	}

	for ( INT x = nTileX; x < (INT)m_vSize.x; x++ )
	{
		SPlacedTileProperties* pProp = GetTileProperties( x, (INT)m_vSize.y - 1 );
		pProp->nTileId = -1;
		pProp->nCollision = 0;
	}
}

void CTileMap::ShiftLeft( INT nTileX, INT nTileY )
{
	for ( INT x = nTileX; x < (INT)m_vSize.x - 1; x++ )
	{
		for ( INT y = nTileY; y < (INT)m_vSize.y; y++ )
		{
			*GetTileProperties( x, y ) = *GetTileProperties( x + 1, y );
		}
	}

	for ( INT y = nTileY; y < (INT)m_vSize.y; y++ )
	{
		SPlacedTileProperties* pProp = GetTileProperties( (INT)m_vSize.x - 1, y );
		pProp->nTileId = -1;
		pProp->nCollision = 0;
	}
}

void CTileMap::OpenDoor( VECTOR vTileMin, VECTOR vTileMax )
{
	for ( INT x = (INT)vTileMin.x; x <= (INT)vTileMax.x; x++ )
	{
		for ( INT y = (INT)vTileMin.y; y <= (INT)vTileMax.y; y++ )
		{
			if ( x >= 0 && y >= 0 )
			{
				GetTileProperties( VECTOR( x, y ) )->nModifier = ETileModifier_OpenDoor;
			}
		}
	}
}

void CTileMap::CloseDoor( VECTOR vTileMin, VECTOR vTileMax )
{
	for ( INT x = (INT)vTileMin.x; x <= (INT)vTileMax.x; x++ )
	{
		for ( INT y = (INT)vTileMin.y; y <= (INT)vTileMax.y; y++ )
		{
			GetTileProperties( VECTOR( x, y ) )->nModifier = ETileModifier_None;
		}
	}
}

void CTileMap::ClearToTile( INT nTileId )
{
	for ( UINT i = 0; i < (*m_TileData).size(); i++ )
	{
		((*m_TileData)[i]).nTileId = nTileId;

		if ( nTileId >= 0 )
		{
			((*m_TileData)[i]).nCollision = 1;
		}
		else
		{
			((*m_TileData)[i]).nCollision = 0;
		}
	}
}

void CTileMap::SwitchTile( INT nOldTileId, INT nTileId )
{
	for ( UINT i = 0; i < (*m_TileData).size(); i++ )
	{
		if ( ((*m_TileData)[i]).nTileId == nOldTileId )
		{
			((*m_TileData)[i]).nTileId = nTileId;
		}
	}
}

void CTileMap::LoadTileSet()
{
	ASSERT( !m_pTileSet );

	m_pTileSet = new CTileSetMapping();
	((CTileSetMapping*)m_pTileSet)->Init( m_TileInfo, m_strTileSetFile );
}

ETileCollision CTileMap::GetCollisionType( CTileProperties* pProperties )
{
	if ( pProperties )
	{
		if ( m_bAlternateTiles && pProperties->nAlternateTileId >= 0 )
		{
			if ( pProperties->bCollisionAlternate )
            {
                 return ETileCollision_Normal;
            }
            else
            {
                return ETileCollision_None;
            }
		}
		else
		{
			return (ETileCollision)pProperties->nCollision;
		}
	}
	return ETileCollision_None;
}
