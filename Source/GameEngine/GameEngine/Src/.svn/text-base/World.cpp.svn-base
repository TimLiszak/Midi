#include "StdAfx.h"
#include "World.h"
#include "TileMap.h"
#include "Level.h"
#include "DynamicActor.h"
#include "Input.h"

void CWorld::Init()
{
	m_pLevel = new CLevel();
	m_pLevel->Init();
}

void CWorld::Term()
{
	m_pLevel->Term();
	delete m_pLevel;

	ASSERT( m_listActors.size() == 0 );
}

void CWorld::Update( const FLOAT fFrameTime )
{
	std::list<CActor*>::iterator it;
	for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
	{
		(*it)->UpdateActor( fFrameTime );
		(*it)->UpdateComponents( fFrameTime );
	}

	for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
	{
		if ( (*it)->IsDynamic() )
		{
			CDynamicActor* pActor = (CDynamicActor*)(*it);
			pActor->UpdateMovement( pActor->GetPosition(), pActor->GetTargetPosition() );
		}
	}

	m_pLevel->Update( fFrameTime );
}

void CWorld::Render()
{
    static const INT DRAW_LEVEL_LAYER = 1;

    for ( INT i = MAX_ACTOR_LAYER - 1; i >= 0; i-- )
    {
        if ( i == DRAW_LEVEL_LAYER )
        {
        	m_pLevel->Render();
        }

	    std::list<CActor*>::iterator it;
	    for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
	    {
            if ( (*it)->m_pDescription->uDrawLayer == (UINT)i )
            {
		        if ( !(*it)->VisibleInEditorOnly() || GetGameEngine()->CanShowEditorVisibleObjects() )
		        {
		            (*it)->Render();
		            (*it)->RenderSprite();
		        }
            }
	    }
    }
}


void CWorld::RenderEditorSelection()
{
	std::list<CActor*>::iterator it;
	for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
	{
		(*it)->RenderEditorSelection();
	}
}

void CWorld::ReleaseActor( CActor* pActor )
{
	pActor->Term();
	m_listActors.remove( pActor );
	delete pActor;
}

void CWorld::DebugDrawActors()
{
	std::list<CActor*>::iterator it;
	for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
	{
		(*it)->DebugDraw();
	}
}

BOOL CWorld::CheckBoxCollision( std::list<CActor*>& pResults, CCollision::SAABBox& Box, UINT uGroupsMask )
{
	BOOL bCollide = FALSE;

	std::list<CActor*>::iterator it;
	for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
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

BOOL CWorld::CheckLineCollision( CActor*& pResult, VECTOR vStart, VECTOR vEnd, UINT uGroupsMask, FLOAT& fT )
{
	fT = 1.0f;
	BOOL bCollide = FALSE;

	std::list<CActor*>::iterator it;
	for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
	{
		if ( ( 1 << (*it)->GetActorGroup() ) & uGroupsMask )
		{
			FLOAT fNewT = 0.0f;
			if ( (*it)->CheckLineCollision( vStart, vEnd, fNewT ) )
			{
				if ( fNewT <= fT )
				{
					fT = fNewT;
					pResult = *it;
					bCollide = TRUE;
				}
			}
		}
	}
	return bCollide;
}


BOOL CWorld::CheckSweepCollision( CCollision::SweepResult& sResult, CActor* pActor, VECTOR vExtents, VECTOR vP1, VECTOR vP2, UINT uGroupsMask )
{
	sResult.nCollideX = 0;
	sResult.nCollideY = 0;
	sResult.pActor = NULL;

	BOOL bCollision = FALSE;
	std::list<CActor*>::iterator it;
	for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
	{
		if ( pActor != (*it) && ( 1 << (*it)->GetActorGroup() ) & uGroupsMask )
		{
			if( (*it)->CheckSweepCollision( sResult, vExtents, vP1, vP2 ) )
			{
				vP2 = sResult.vResult;
				bCollision = TRUE;
			}
		}
	}
	return bCollision;
}

void CWorld::LevelObjectDeleted( class CLevelObject* pObject )
{
    std::list<CActor*>::iterator it;
    for ( it = m_listActors.begin() ; it != m_listActors.end(); it++ )
    {
		(*it)->LevelObjectDeleted( pObject );
    }
}
