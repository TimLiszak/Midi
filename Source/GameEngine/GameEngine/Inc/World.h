#ifndef _WORLD_H_
#define _WORLD_H_

#include "Actor.h"
#include "Collision.h"

class CTileSet;
class CTileMap;
class CLevel;

class CWorld
{
public:
	void	Init();
	void	Term();
	void	Update( const FLOAT fFrameTime );
	void	Render();
	void	RenderEditorSelection();

	BOOL	CheckBoxCollision( std::list<CActor*>& pResults, CCollision::SAABBox& Box, UINT uGroupsMask );
	BOOL	CheckLineCollision( CActor*& pResult, VECTOR vStart, VECTOR vEnd, UINT uGroupsMask, FLOAT& fT );
	BOOL	CheckSweepCollision( CCollision::SweepResult& sResult, CActor* pActor, VECTOR vExtents, VECTOR vP1, VECTOR vP2, UINT uGroupsMask );

	template <typename T> T* SpawnActor( UINT uGroup, VECTOR vPos, VECTOR vExtents );
	template <typename T, typename ActorDescription> T* SpawnActor( ActorDescription*& pDesc );
	template <typename T> T* SpawnActorNoInit();
	void	ReleaseActor( CActor* pActor );

    void	LevelObjectDeleted( class CLevelObject* pObject );

	CLevel*		GetLevel();

	void	DebugDrawActors();

private:
	std::list< CActor* > m_listActors;
	class CLevel*		m_pLevel;
};

template <typename T, typename ActorDescription> 
T* CWorld::SpawnActor( ActorDescription*& pDesc )
{
	T* pActor = new T();
	pActor->InitActor( pDesc );
	pActor->Init( pDesc );
	m_listActors.push_back( pActor );
	return pActor;
}

template <typename T> 
T* CWorld::SpawnActor( UINT uGroup, VECTOR vPos, VECTOR vExtents )
{
	CActorDescription* pDesc = new CActorDescription();
	pDesc->uGroup = uGroup;
	pDesc->vPosition = vPos;
	pDesc->vExtents = vExtents;
	return SpawnActor< T >( pDesc );
}

template <typename T> 
T* CWorld::SpawnActorNoInit()
{
	T* pActor = new T();
	m_listActors.push_back( pActor );
	return pActor;
}

inline CLevel* CWorld::GetLevel()
{
	return m_pLevel;
}

#endif
