#ifndef _DYNAMIC_ACTOR_H_
#define _DYNAMIC_ACTOR_H_

#include "Actor.h"
#include "Collision.h"

class CDynamicActor : public CActor
{
	friend class CWorld;

public:
	CDynamicActor() : CActor() {}

	virtual inline BOOL	IsDynamic() { return TRUE; }

	virtual void	SetPosition( VECTOR vPos, BOOL bFromEditor = FALSE );
	VECTOR	GetTargetPosition();
	void	SetTargetPosition( VECTOR vPos );
	VECTOR	GetVelocity();

	virtual BOOL CheckSweepCollision( CCollision::SweepResult& sResult, VECTOR vExtents, VECTOR vP1, VECTOR vP2 );

protected:
	virtual void UpdateMovement( VECTOR vCurrentPos, VECTOR vTarget );

private:
	VECTOR	m_vTargetPosition;
	VECTOR	m_vVelocity;
};

inline VECTOR CDynamicActor::GetVelocity()
{
	return m_vVelocity;
}

inline VECTOR CDynamicActor::GetTargetPosition()
{
	return m_vTargetPosition;
}

inline void CDynamicActor::SetTargetPosition( VECTOR vPos )
{
	m_vTargetPosition = vPos;
	m_vVelocity = m_vTargetPosition - GetPosition();
}

#endif
