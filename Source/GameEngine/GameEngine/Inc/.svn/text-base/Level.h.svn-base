#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "DynamicActor.h"
#include "Collision.h"
#include "TileSet.h"
#include "Reflectable.h"
class CTileMap;

class CLevelObject : public CDynamicActor, public CSerializable
{
public:
	CLevelObject();

	CActorDescription* GetActorDescription() { return m_pDescription; }
	virtual UINT	GetObjectId() = 0;
	virtual void	Reset() {}
	virtual CLevelObject*	CopyObject();
	virtual void	FixActorIds( std::map<INT, INT>& IdMap ) {}
	virtual void	MoveActorGroup( VECTOR vMove ) {}
	virtual INT		GetUniqueActorId() { return GetActorDescription()->nUniqueActorId; } ;
	virtual void	CharacterCollision( class CCharacter* pCharacter, INT nCollideX, INT nCollideY ) {}

	virtual BOOL	CanSelectOtherObjects() { return FALSE; }
	virtual void	SelectOtherObjects( VECTOR vPos, VECTOR vExtents ) {};

	inline void SetEnabled( BOOL bEnable, INT nEnableById = 0 ) 
	{ 
		if ( !m_bEnabled && bEnable )
		{
			m_bWasEnabled = TRUE;
		}	
		if ( bEnable )
		{
			m_TriggerId[nEnableById] = TRUE;
		}
		m_bEnabled = bEnable; 
	}

	inline BOOL IsEnabled() { return m_bEnabled; }

protected:
	BOOL	m_bEnabled;
	BOOL	m_bWasEnabled;
	std::map<INT, BOOL>	m_TriggerId;
};

class CRotatableLevelObject : public CLevelObject
{
public:
	virtual inline BOOL	IsRotatable() { return TRUE; }
	virtual void	SetRotation( FLOAT fAngle ) = 0;
	virtual FLOAT	GetRotation() = 0;

protected:
	FLOAT	m_fCurrentRotation;
};

class CLevel : public CReflectable, public CSerializable
{
public:
	REFLECTION_INFO;

	void	Init();
	void	Term();
	void	Update( const FLOAT fFrameTime );
	void	Render();
	void	Reset();

	void	ReleaseActors();
	void	RemoveAllLevelObjects();

	virtual void	Serialize( CSerializer* Serializer );

	void	RegisterLevelObjectType( CLevelObject* pActor );

	BOOL	CheckSweepCollision( CCollision::SweepResult& sResult, VECTOR vExtents, VECTOR vP1, VECTOR vP2, UINT uGroupsMask );
	BOOL	CheckBoxCollision( std::list<CLevelObject*>& pResults, CCollision::SAABBox& Box, UINT uGroupsMask );

	void	AddLevelObject( CLevelObject* pActor );
	void	RemoveLevelObject( CLevelObject* pActor );

	void	CreateTileMap( STileInfo& TileInfo, std::string strBitmapFile, VECTOR vSize );
	void	DeleteTileMap();
	CTileMap*	GetTileMap();

	COLOUR_RGB	GetClearColour();
	BOOL	RespawnCoopImmediately();

	INT		GetNextUniqueActorId();

	void	PrintObjectInfo();

	void	ShiftDown( FLOAT fX, FLOAT fY, FLOAT fAmount );
	void	ShiftRight( FLOAT fX, FLOAT fY, FLOAT fAmount );
	void	ShiftUp( FLOAT fX, FLOAT fY, FLOAT fAmount );
	void	ShiftLeft( FLOAT fX, FLOAT fY, FLOAT fAmount );

	CLevelObject*	GetLevelObject( INT nActorId );
	CLevelObject*	GetLevelObject( UINT uIndex, UINT uObjectId );

	virtual void	PropertiesUpdated();
	
	std::map< UINT, CLevelObject* >*	GetObjectTypes();

private:
	std::map< UINT, CLevelObject* >	m_LevelObjectTypes;
	std::list< CLevelObject* > m_LevelObjects;
	class CTileMap*		m_pTileMap;

    std::string m_strTileSetFile;
	COLOUR_RGB	m_ClearColour;
	INT			m_nUniqueActorIdCnt;
	BOOL		m_bRespawnCoopImmediately;
	VECTOR		m_vGridSize;
};

inline void CLevel::RegisterMembers(CReflectInfo* p_info)
{
	REGISTER_ALL( REF_FLOAT, m_ClearColour.r, 0.0f, 1.0f, 0.005f );
	REGISTER_ALL( REF_FLOAT, m_ClearColour.g, 0.0f, 1.0f, 0.005f );
	REGISTER_ALL( REF_FLOAT, m_ClearColour.b, 0.0f, 1.0f, 0.005f );
	REGISTER_LIMIT( REF_UINT, m_bRespawnCoopImmediately, 0, 1 );
	REGISTER( REF_VECTOR, m_vGridSize );
    REGISTER( REF_STRING, m_strTileSetFile );
}


inline CTileMap* CLevel::GetTileMap()
{
	return m_pTileMap;
}

inline void CLevel::AddLevelObject( CLevelObject* pActor )
{
	ASSERT( !pActor->GetExtents().IsZero() );
	m_LevelObjects.push_back( pActor );
}

inline COLOUR_RGB CLevel::GetClearColour()
{
	return m_ClearColour;
}

inline INT CLevel::GetNextUniqueActorId()
{
	return m_nUniqueActorIdCnt++;
}

inline BOOL	CLevel::RespawnCoopImmediately()
{
	return m_bRespawnCoopImmediately;
}

inline std::map< UINT, CLevelObject* >* CLevel::GetObjectTypes()
{
	return &m_LevelObjectTypes;
}

#endif
