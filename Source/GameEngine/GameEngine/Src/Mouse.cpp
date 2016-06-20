#include "StdAfx.h"
#include "Mouse.h"

void CMouse::Init()
{
	memset( m_bIsDown, 0, sizeof(m_bIsDown) );
	memset( m_MouseState, 0, sizeof(m_MouseState) );
}

void CMouse::ProcessInput()
{
	for (UINT i = 0; i < EMouseButton_Max; i++)
	{
		m_MouseState[i].bIsTriggered = FALSE;
		m_MouseState[i].bIsReleased = FALSE;

		if ( m_bIsDown[i] )
		{
			if ( !m_MouseState[i].bIsDown )
			{
				m_MouseState[i].bIsTriggered = TRUE;
			}
			m_MouseState[i].bIsDown = TRUE;
		}
		else
		{
			if ( m_MouseState[i].bIsDown )
			{
				m_MouseState[i].bIsReleased = TRUE;
			}
			m_MouseState[i].bIsDown = FALSE;
		}
	}
}

void CMouse::Term()
{
}

void CMouse::MouseDownCallback( EMouseButton eButton, VECTOR vPos )
{
	m_bIsDown[eButton] = TRUE;
	m_vPosition = vPos;

	for (vector<IMouseCallback*>::iterator it = Callbacks.begin(); it != Callbacks.end(); ++it)
	{
		(*it)->MouseDownCallback(eButton, vPos);
	}
}

void CMouse::MouseUpCallback( EMouseButton eButton, VECTOR vPos )
{
	m_bIsDown[eButton] = FALSE;
	m_vPosition = vPos;

	for (vector<IMouseCallback*>::iterator it = Callbacks.begin(); it != Callbacks.end(); ++it)
	{
		(*it)->MouseUpCallback(eButton, vPos);
	}
}

void CMouse::MouseMoveCallback( VECTOR vPos )
{
	m_vPosition = vPos;

	for (vector<IMouseCallback*>::iterator it = Callbacks.begin(); it != Callbacks.end(); ++it)
	{
		(*it)->MouseMoveCallback(vPos);
	}
}
