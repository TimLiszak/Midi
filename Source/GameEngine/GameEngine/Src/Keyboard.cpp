#include "StdAfx.h"
#include "Keyboard.h"
#include "DebugPrint.h"

void CKeyboard::Init()
{
	memset( m_KeyBuffer, 0, sizeof(m_KeyBuffer) );
	memset( m_sKeyStates, 0, sizeof(m_sKeyStates) );
}

void CKeyboard::Term()
{
}

INT CKeyboard::GetNextCharacter()
{
	if ( m_KeyQueue.size() > 0 )
	{
		INT nKey = m_KeyQueue.front();
		m_KeyQueue.pop_front();
		return nKey;
	}
	return 0;
}

void CKeyboard::ProcessInput()
{
	m_KeyQueue.clear();

	for (UINT i = 0; i < EKbKey_MaxKeys; i++)
	{
		m_sKeyStates[i].bIsTriggered = FALSE;
		m_sKeyStates[i].bIsReleased = FALSE;

		if ( m_KeyBuffer[i] )
		{
			// If it was not down, set triggered
			if ( !m_sKeyStates[i].bIsDown )
			{
				m_sKeyStates[i].bIsTriggered = TRUE;
				m_KeyQueue.push_back( i );
			}
			m_sKeyStates[i].bIsDown = TRUE;
		}
		else
		{
			// If it was down, set released
			if ( m_sKeyStates[i].bIsDown )
			{
				m_sKeyStates[i].bIsReleased = TRUE;
			}
			m_sKeyStates[i].bIsDown = FALSE;
		}
	}
}

void CKeyboard::KeyDownCallback( int nKey )
{
	m_KeyBuffer[nKey] = true;

	for (vector<IKeyboardCallback*>::iterator it = Callbacks.begin(); it != Callbacks.end(); ++it)
	{
		(*it)->KeyDownCallback(nKey);
	}
}

void CKeyboard::KeyUpCallback( int nKey )
{
	m_KeyBuffer[nKey] = false;

	for (vector<IKeyboardCallback*>::iterator it = Callbacks.begin(); it != Callbacks.end(); ++it)
	{
		(*it)->KeyUpCallback(nKey);
	}
}
