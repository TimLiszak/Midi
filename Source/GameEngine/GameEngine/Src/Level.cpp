#include "StdAfx.h"
#include "Level.h"
#include "World.h"
#include "TileMap.h"
#include "FileSerializer.h"

CReflectInfo CLevel::m_ref_info; 

CLevelObject::CLevelObject() : CDynamicActor(),
	m_bEnabled( TRUE ),
	m_bWasEnabled( FALSE )
{
}

CLevelObject* CLevelObject::CopyObject()
{
	VECTOR vPos = GetPosition();
	VECTOR vExtents = GetExtents();
	vPos.x += 50.0f;

	// Copy object
	CFileOutputSerializer OutSerializer;
	OutSerializer.Open( "Temp", CURRENT_FILE_VERSION );
	this->Serialize( &OutSerializer );
	OutSerializer.Close();

	// Create new object
	CLevelObject* pNewActor = (CLevelObject*)this->GetNewInstance();
	CFileInputSerializer InSerializer;
	BOOL bLoaded = FALSE;
	bLoaded = InSerializer.Open( "Temp" );
	ASSERT( bLoaded );
	pNewActor->Serialize( &InSerializer );
	InSerializer.Close();

	pNewActor->GetActorDescription()->nUniqueActorId = GetGameEngine()->GetWorld()->GetLevel()->GetNextUniqueActorId();
	pNewActor->Init( pNewActor->GetActorDescription() );

	pNewActor->SetPosition( vPos );
	pNewActor->SetExtents( vExtents );
	pNewActor->SetActorGroup( pNewActor->GetActorDescription()->uGroup );


	ASSERT( !pNewActor->GetExtents().IsZero() );

	return pNewActor;
}


void CLevel::Init()
{
	m_nUniqueActorIdCnt = 0;
	m_pTileMap = NULL;
	m_vGridSize.Set( 0.0f, 0.0f );
	m_ClearColour = COLOUR_RGB( 0.2f, 0.2f, 0.2f );
	m_bRespawnCoopImmediately = FALSE;
}

void CLevel::Term()
{
	ReleaseActors();
}

void CLevel::ReleaseActors()
{
	RemoveAllLevelObjects();

	DeleteTileMap();
	m_ClearColour = COLOUR_RGB( 1.0f, 1.0f, 1.0f );
}

void CLevel::RemoveAllLevelObjects()
{
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		GetGameEngine()->GetWorld()->ReleaseActor( (*it) );
	}
	m_LevelObjects.clear();
	m_nUniqueActorIdCnt = 0;
}

void CLevel::Update( const FLOAT fFrameTime )
{
}

void CLevel::Render()
{
	if ( m_pTileMap )
	{
		m_pTileMap->Render();
	}
}

BOOL CLevel::CheckSweepCollision( CCollision::SweepResult& sResult, VECTOR vExtents, VECTOR vP1, VECTOR vP2, UINT uGroupsMask )
{
	sResult.nCollideX = 0;
	sResult.nCollideY = 0;
	sResult.pActor = NULL;

	BOOL bCollision = FALSE;
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		if ( ( 1 << (*it)->GetActorGroup() ) & uGroupsMask )
		{
			if( (*it)->CheckSweepCollision( sResult, vExtents, vP1, vP2 ) )
			{
				vP2 = sResult.vResult;
				bCollision = TRUE;
			}
		}
	}

	if ( m_pTileMap )
	{
		CCollision::SAABBox sBox1( vExtents, vP1 );
		VECTOR vVel = vP2 - vP1;
		BOOL bResult = m_pTileMap->CheckSweepCollision( sResult, sBox1, vVel );
		if ( bResult )
		{
			bCollision = TRUE;
		}
	}
	return bCollision;
}

void CLevel::CreateTileMap( STileInfo& TileInfo, std::string strBitmapFile, VECTOR vSize )
{
	if ( m_pTileMap )
	{
		DeleteTileMap();
	}

	m_pTileMap = new CTileMap();
	m_pTileMap->Init( TileInfo, strBitmapFile, vSize );
	m_vGridSize = vSize;
    m_strTileSetFile = strBitmapFile;
}

void CLevel::DeleteTileMap()
{
	if ( m_pTileMap )
	{
		m_pTileMap->Term();
		delete m_pTileMap;
		m_pTileMap = NULL;
		m_vGridSize.Set( 0.0f, 0.0f );
	}
}

void CLevel::Serialize( CSerializer* Serializer )
{
	Serializer->Serialize( m_nUniqueActorIdCnt );
	Serializer->Serialize( m_ClearColour.r );
	Serializer->Serialize( m_ClearColour.g );
	Serializer->Serialize( m_ClearColour.b );
	Serializer->Serialize( m_bRespawnCoopImmediately );

	BOOL bHasTileMap = ( m_pTileMap != NULL );
	Serializer->Serialize( bHasTileMap );

	if ( bHasTileMap )
	{
		if ( Serializer->IsReading() )
		{
			ASSERT( !m_pTileMap );
			m_pTileMap = new CTileMap();
		}
		m_pTileMap->Serialize( Serializer );
		m_vGridSize = m_pTileMap->GetSize();
        m_strTileSetFile = m_pTileMap->GetTileSetFile();
	}

	UINT nNumLevelObjects = m_LevelObjects.size();
	Serializer->Serialize( nNumLevelObjects );

	if ( Serializer->IsWriting() )
	{
		std::list<CLevelObject*>::iterator it;
		for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
		{
			ASSERT( !(*it)->GetExtents().IsZero() );

			UINT uId = (*it)->GetObjectId();
			Serializer->Serialize( uId );
			(*it)->Serialize( Serializer );
		}
	}
	else
	{
		ASSERT( m_LevelObjects.size() == 0 );
		ASSERT( Serializer->IsReading() );

		for ( UINT i = 0; i < nNumLevelObjects; i++ )
		{
			UINT uId = 0;
			Serializer->Serialize( uId );
			CLevelObject* pType = m_LevelObjectTypes[uId];
			CLevelObject* pNewActor = (CLevelObject*)pType->GetNewInstance();
			pNewActor->Serialize( Serializer );
			pNewActor->Init( pNewActor->GetActorDescription() );

			/*
			if ( pNewActor->GetExtents().IsZero() )
			{
				ASSERT( FALSE );
				GetGameEngine()->GetWorld()->ReleaseActor( pNewActor );
			}
			else*/
			{
				AddLevelObject( pNewActor );
			}
		}
	}
}

void CLevel::RegisterLevelObjectType( CLevelObject* pActor )
{
	UINT uId = pActor->GetObjectId();
	ASSERT( !m_LevelObjectTypes[uId] );
	m_LevelObjectTypes[uId] = pActor;
}

void CLevel::PrintObjectInfo()
{
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		CLevelObject* pObj = (*it);
		TRACE( "%d: pos %.2f %.2f extents %.2f %.2f\n", pObj->GetObjectId(),
			pObj->GetPosition().x,
			pObj->GetPosition().y,
			pObj->GetExtents().x,
			pObj->GetExtents().y );
	}
}

void CLevel::ShiftDown( FLOAT fX, FLOAT fY, FLOAT fAmount )
{
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		VECTOR vPos = (*it)->GetActorDescription()->vPosition;

		if ( vPos.x >= fX && vPos.y >= fY )
		{
			vPos.y += fAmount;
			(*it)->GetActorDescription()->vPosition = vPos;
			(*it)->SetPosition( vPos, TRUE );
			(*it)->ShiftByTile( 0, 1 );
		}
	}
}

void CLevel::ShiftRight( FLOAT fX, FLOAT fY, FLOAT fAmount )
{
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		VECTOR vPos = (*it)->GetActorDescription()->vPosition;

		if ( vPos.x >= fX && vPos.y >= fY )
		{
			vPos.x += fAmount;
			(*it)->GetActorDescription()->vPosition = vPos;
			(*it)->SetPosition( vPos, TRUE );
			(*it)->ShiftByTile( 1, 0 );
		}
	}
}

void CLevel::ShiftUp( FLOAT fX, FLOAT fY, FLOAT fAmount )
{
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		VECTOR vPos = (*it)->GetActorDescription()->vPosition;

		if ( vPos.x >= fX && vPos.y >= fY )
		{
			vPos.y -= fAmount;
			(*it)->GetActorDescription()->vPosition = vPos;
			(*it)->SetPosition( vPos, TRUE );
			(*it)->ShiftByTile( 0, -1 );
		}
	}
}

void CLevel::ShiftLeft( FLOAT fX, FLOAT fY, FLOAT fAmount )
{
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		VECTOR vPos = (*it)->GetActorDescription()->vPosition;

		if ( vPos.x >= fX && vPos.y >= fY )
		{
			vPos.x -= fAmount;
			(*it)->GetActorDescription()->vPosition = vPos;
			(*it)->SetPosition( vPos, TRUE );
			(*it)->ShiftByTile( -1, 0 );
		}
	}
}

CLevelObject* CLevel::GetLevelObject( INT nActorId )
{
	CLevelObject* pFoundActor = NULL;
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		if ( (*it)->GetActorDescription()->nUniqueActorId == nActorId )
		{
			ASSERT( !pFoundActor );
			pFoundActor = (*it);

#ifndef DEBUG
			return pFoundActor;
#endif
		}
	}
	return pFoundActor;
}

CLevelObject* CLevel::GetLevelObject( UINT uIndex, UINT uObjectId )
{
	UINT uCnt = 0;
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		if ( (*it)->GetObjectId() == uObjectId )
		{
			if ( uCnt == uIndex )
			{
				return (*it);
			}
			uCnt++;
		}
	}
	return NULL;
}

BOOL CLevel::CheckBoxCollision( std::list<CLevelObject*>& pResults, CCollision::SAABBox& Box, UINT uGroupsMask )
{
	BOOL bCollide = FALSE;

	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		if ( ( 1 << (*it)->GetActorGroup() ) & uGroupsMask )
		{
			if ( (*it)->CheckBoxCollision( Box ) )
			{
				pResults.push_back( *it );
				bCollide = TRUE;
			}
		}
	}
	return bCollide;
}

void CLevel::RemoveLevelObject( CLevelObject* pActor )
{
	m_LevelObjects.remove( pActor );

    GetGameEngine()->GetWorld()->LevelObjectDeleted( pActor );
}

void CLevel::Reset()
{
	std::list<CLevelObject*>::iterator it;
	for ( it = m_LevelObjects.begin() ; it != m_LevelObjects.end(); it++ )
	{
		(*it)->Reset();
	}
}

void CLevel::PropertiesUpdated()
{
	if ( m_pTileMap )
	{
		if ( m_pTileMap->GetSize() != m_vGridSize )
		{
			m_pTileMap->Resize( m_vGridSize );
		}
        m_pTileMap->SetTileSetFile( m_strTileSetFile );
	}
}
