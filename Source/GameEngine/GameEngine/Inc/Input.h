
#ifndef _INPUT_H_
#define _INPUT_H_

#include "Keyboard.h"
#include "Mouse.h"
#include "Gamepad.h"

class CInput
{
public:
	static const INT	MAX_GAMEPADS = 2;

	void	Init();
	void	Update();
	void	Term();

	BOOL	IsInputDisabled();
	void	DisableInput( BOOL bDisable );


	CKeyboard*	GetKeyboard();
	CMouse*		GetMouse();
	CGamepad*	GetGamepad( UINT uIndex );

	BOOL EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
	BOOL EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext );


private:
	HRESULT InitDirectInput( HWND hDlg );

	LPDIRECTINPUT8          g_pDI;
	std::list< LPDIRECTINPUTDEVICE8 > m_FoundGampads;

	CKeyboard	m_Keyboard;
	CMouse		m_Mouse;
	CGamepad	m_Gamepad[MAX_GAMEPADS];

	BOOL	m_bDisableInput;
};

inline CKeyboard* CInput::GetKeyboard()
{
	return &m_Keyboard;
}

inline CMouse* CInput::GetMouse()
{
	return &m_Mouse;
}

inline CGamepad* CInput::GetGamepad( UINT uIndex )
{
	ASSERT( uIndex < MAX_GAMEPADS );
	return &m_Gamepad[uIndex];
}

inline BOOL CInput::IsInputDisabled()
{
	return m_bDisableInput;
}

inline void CInput::DisableInput( BOOL bDisable )
{
	m_bDisableInput = bDisable;
}

#endif
