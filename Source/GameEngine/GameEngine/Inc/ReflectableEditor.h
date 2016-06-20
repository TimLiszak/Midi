#ifndef _REFLECTABLE_EDITOR_H_
#define _REFLECTABLE_EDITOR_H_

#include "Reflectable.h"

class CReflectableEditor
{
public:
	void	Init();
	void	Term();
	void	Update( const FLOAT fFrameTime );
	void	Render();

	void	SetObject( CReflectable* pObject );
	void	SetObject( CReflectable* pObject, VECTOR vPosition );

private:
    void    AddToEditString( CHAR ch );
    void    EndEditString();

	CReflectable* m_pObject;
	std::list< CReflectable* > m_Stack;
	INT		m_nSelectedMember;
	FLOAT	m_fButtonHoldTime;
	
	BOOL	m_bSetPosition;
	VECTOR	m_vPosition;

	BOOL	m_bEditString;
	std::string m_strEditString;
};

inline void CReflectableEditor::SetObject( CReflectable* pObject )
{
	m_pObject = pObject;
	m_bSetPosition = FALSE;
    m_bEditString = FALSE;
}

inline void CReflectableEditor::SetObject( CReflectable* pObject, VECTOR vPosition )
{
	m_pObject = pObject;
	m_bSetPosition = TRUE;
	m_vPosition = vPosition;
    m_bEditString = FALSE;
}

#endif