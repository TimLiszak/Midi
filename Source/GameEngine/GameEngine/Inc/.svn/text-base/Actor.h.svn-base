
#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Collision.h"
#include "Reflectable.h"
#include "SpriteInfo.h"

#define MAX_ACTOR_LAYER     3

class CActorDescription : public CReflectable, CSerializable
{
public:
	CActorDescription() : nUniqueActorId(-1), uGroup(0), uDrawLayer(0) {}
	virtual ~CActorDescription();

	REFLECTION_INFO;

	UINT	uGroup;
	INT		nUniqueActorId;
    UINT    uDrawLayer;
	VECTOR	vPosition;
	VECTOR	vExtents;
	CSpriteInfo SpriteInfo;

	virtual void Serialize( CSerializer* Serializer );
};


inline void CActorDescription::RegisterMembers(CReflectInfo* p_info)
{
	REGISTER_INC( REF_VECTOR, vPosition, 0.0f );
	REGISTER_LIMIT( REF_VECTOR, vExtents, 1.0f, 99999.0f );
	REGISTER_LIMIT( REF_UINT, uDrawLayer, 0, MAX_ACTOR_LAYER - 1 );
}


class CActorComponent
{
public:
	CActorComponent( class CActor* pActor ) : m_pActor(pActor), m_bEnabled(TRUE) {}
	virtual ~CActorComponent() {}

	virtual void	Init() = 0;
	virtual void	Update( const FLOAT fFrameTime ) = 0;
	virtual void	Term() = 0;

	inline BOOL	IsEnabled() { return m_bEnabled; }
	inline void SetEnabled( BOOL bEnabled ) { m_bEnabled = bEnabled; }

protected:
	CActor* m_pActor;
	BOOL	m_bEnabled;
};

class CActor
{
	typedef CActorDescription	ActorDescription;

	friend class CWorld;
public:

	CActor();
	virtual ~CActor() {}
	virtual CActor*	GetNewInstance() = 0;
	void	Init( CActorDescription* pDesc );

	virtual inline BOOL	IsDynamic() { return FALSE; }
	virtual inline BOOL	IsMovable() { return FALSE; }
	virtual inline BOOL	IsRotatable() { return FALSE; }
	virtual inline BOOL	IsDangerous() { return FALSE; }

	virtual BOOL	IsDead() { return FALSE; }

	virtual BOOL	VisibleInEditorOnly() { return FALSE; }

	VECTOR	GetPosition() const;
	VECTOR	GetExtents() const;
	UINT	GetActorGroup();

	virtual void	SetPosition( VECTOR vPos, BOOL bFromEditor = FALSE );
	virtual void	SetExtents( VECTOR vExtents );
	virtual void	SetActorGroup( UINT uGroup );
	virtual void	ShiftByTile( INT nX, INT nY ) {}

	virtual BOOL CheckSweepCollision( CCollision::SweepResult& sResult, VECTOR vExtents, VECTOR vP1, VECTOR vP2 );
	virtual BOOL CheckBoxCollision( CCollision::SAABBox& Box );
	virtual BOOL CheckLineCollision( VECTOR vStart, VECTOR vEnd, FLOAT& fT );


    virtual void	LevelObjectDeleted( class CLevelObject* pObject ) {}
	void	ReloadSprite();
	void	DebugDraw();
	virtual void	UpdateEditorSelection() {}
	virtual void	RenderEditorSelection() {}

protected:
	virtual void	UpdateActor( const FLOAT fFrameTime ) {}
	void			RenderSprite();
	virtual void	Render() {}
	virtual void	CreateComponents() = 0;
	virtual void	TermActor() {}

	std::vector< CActorComponent* > m_vecComponents;

	VECTOR		m_vPosition;
	VECTOR		m_vExtents;
	UINT		m_uGroup;
	BOOL		m_bEnableComponents;
	class CSprite*	m_pSprite;

	ActorDescription*	m_pDescription;

private:
	void	UpdateComponents( const FLOAT fFrameTime );
	void	Term();
};

inline VECTOR CActor::GetPosition() const
{
	return m_vPosition;
}

inline VECTOR CActor::GetExtents() const
{
	return m_vExtents;
}

inline void CActor::SetPosition( VECTOR vPos, BOOL bFromEditor )
{
	m_vPosition = vPos;
}

inline void CActor::SetExtents( VECTOR vExtents )
{
	ASSERT( !vExtents.IsZero() );
	m_vExtents = vExtents;
}

inline UINT CActor::GetActorGroup()
{
	return m_uGroup;
}

inline void CActor::SetActorGroup( UINT uGroup )
{
	m_uGroup = uGroup;
}

#endif
