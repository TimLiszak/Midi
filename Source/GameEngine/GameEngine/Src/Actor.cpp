#include "StdAfx.h"
#include "Actor.h"
#include "Render2d.h"
#include "Level.h"
#include "World.h"
#include "SpriteManager.h"

CReflectInfo CActorDescription::m_ref_info; 

CActorDescription::~CActorDescription()
{
}

void CActorDescription::Serialize( CSerializer* Serializer ) 
{
	Serializer->Serialize( nUniqueActorId );
	Serializer->Serialize( vPosition );
	Serializer->Serialize( vExtents );

	if ( Serializer->GetVersion() >= EFileVersion_DrawLayer )
	{
        Serializer->Serialize( uDrawLayer );
    }

	if ( Serializer->GetVersion() >= EFileVersion_Sprite )
	{
		Serializer->Serialize( SpriteInfo );
	}

	if ( Serializer->IsReading() )
	{
		ASSERT( nUniqueActorId != -1 );
	}
}

CActor::CActor() : m_uGroup(0), m_bEnableComponents( TRUE ), m_pDescription(NULL), m_pSprite(NULL)
{
}

void CActor::Init( CActorDescription* pDesc )
{
	m_pDescription = pDesc;
	CreateComponents();

	for (UINT i = 0; i < m_vecComponents.size(); i++)
	{
		m_vecComponents[i]->Init();
	}
	this->SetPosition( pDesc->vPosition );
	m_uGroup = pDesc->uGroup;
	m_vExtents = pDesc->vExtents;
	m_bEnableComponents = TRUE;

	ReloadSprite();
}

void CActor::UpdateComponents( const FLOAT fFrameTime )
{
	if ( !m_bEnableComponents ) return;

	for (UINT i = 0; i < m_vecComponents.size(); i++)
	{
		if ( m_vecComponents[i]->IsEnabled() )
		{
			m_vecComponents[i]->Update( fFrameTime );
		}
	}
}

void CActor::Term()
{
	for (UINT i = 0; i < m_vecComponents.size(); i++)
	{
		m_vecComponents[i]->Term();
		delete m_vecComponents[i];
	}
	m_vecComponents.clear();
	this->TermActor();
	SAFE_DELETE( m_pDescription );
}

void CActor::DebugDraw()
{
	CRender2d::DrawRect( m_vPosition, m_vExtents, 0.0f, COLOUR_RGB(1.0f,1.0f,0.0f) );
}

void CActor::RenderSprite()
{
	if ( m_pSprite )
	{
		m_pSprite->Render( this, &m_pDescription->SpriteInfo );
	}
}

BOOL CActor::CheckSweepCollision( CCollision::SweepResult& sResult, VECTOR vExtents, VECTOR vP1, VECTOR vP2 )
{
	CCollision::SAABBox sBox1( vExtents, vP1 );
	CCollision::SAABBox sBox2( m_vExtents, m_vPosition );
	VECTOR vVel = vP2 - vP1;
	BOOL bCollide = CCollision::CheckAABoxSweep( sResult, sBox1, vVel, sBox2 );

	if ( bCollide )
	{
		sResult.pActor = this;
		return TRUE;
	}
	return FALSE;
}

BOOL CActor::CheckBoxCollision( CCollision::SAABBox& Box )
{
	CCollision::SAABBox ActorBox( GetExtents(), GetPosition() );
	return CCollision::CheckAABoxOverlap( Box, ActorBox );
}

BOOL CActor::CheckLineCollision( VECTOR vStart, VECTOR vEnd, FLOAT& fT )
{
	CCollision::SAABBox ActorBox( GetExtents(), GetPosition() );
	return CCollision::CheckLineBox( vStart, vEnd, ActorBox, fT );
}

void CActor::ReloadSprite()
{
	m_pSprite = NULL;
	if ( m_pDescription->SpriteInfo.strFilename.size() > 0 )
	{
		m_pSprite = GetGameEngine()->GetSpriteManager()->LoadSprite( m_pDescription->SpriteInfo.strFilename );
	}
}
