
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

enum EKeyConfig
{
	EKeyConfig_Xbox,
	EKeyConfig_PS3,
	EKeyConfig_TimSpecial,

	EKeyConfig_Max
};

enum EPadButtons
{
	EPad_DPadUp, 
	EPad_DPadDown,
	EPad_DPadLeft,
	EPad_DPadRight,

	EPad_FaceTop,
	EPad_FaceBottom,
	EPad_FaceLeft,
	EPad_FaceRight,

	EPad_LeftShoulder1,
	EPad_LeftShoulder2,
	EPad_RightShoulder1,
	EPad_RightShoulder2,

	EPad_LeftStick,
	EPad_RightStick,

	EPad_Start,
	EPad_Select,
	EPad_Home,

	EPad_Max
};

enum EStick
{
	EStick_Left,
	EStick_Right,

	EStick_Max
};

class CGamepad
{
public:
	CGamepad() : g_pJoystick(NULL) {}
	void	Init();
	void	Term();
	void	ProcessInput();
	void	Acquire();

	void	SetDirectInputDevice( LPDIRECTINPUTDEVICE8 pJoystick );

	BOOL	IsKeyDown( EPadButtons eButton );
	BOOL	IsKeyTriggered( EPadButtons eButton );
	BOOL	IsKeyReleased( EPadButtons eButton );

	BOOL	IsStickHeld( EStick eStick );
	FLOAT	GetStickX( EStick eStick );
	FLOAT	GetStickY( EStick eStick );

	void	SetKeyConfig( EKeyConfig eConfig );

private:
	HRESULT UpdateInputState();

	LPDIRECTINPUTDEVICE8    g_pJoystick;

	struct SPadState
	{
		BOOL	bIsDown;
		BOOL	bIsTriggered;
		BOOL	bIsReleased;
	};
	struct SStickState
	{
		FLOAT	fXAxis;
		FLOAT	fYAxis;
	};
	SPadState	m_PadState[EPad_Max];
	SStickState	m_StickState[EStick_Max];
	
	std::map<INT, EPadButtons> m_XboxKeyMap;
	std::map<INT, EPadButtons> m_PS3KeyMap;
	std::map<INT, EPadButtons> m_TimKeyMap;

	std::map<INT, EPadButtons>* m_pKeyMap;


};

inline BOOL	CGamepad::IsKeyDown( EPadButtons eButton )
{
	return m_PadState[eButton].bIsDown;
}

inline BOOL	CGamepad::IsKeyTriggered( EPadButtons eButton )
{
	return m_PadState[eButton].bIsTriggered;
}

inline BOOL	CGamepad::IsKeyReleased( EPadButtons eButton )
{
	return m_PadState[eButton].bIsReleased;
}

inline BOOL CGamepad::IsStickHeld( EStick eStick )
{
	return m_StickState[eStick].fXAxis != 0.0f ||
		   m_StickState[eStick].fYAxis != 0.0f;
}

inline FLOAT CGamepad::GetStickX( EStick eStick )
{
	return m_StickState[eStick].fXAxis;
}

inline FLOAT CGamepad::GetStickY( EStick eStick )
{
	return m_StickState[eStick].fYAxis;
}

inline void CGamepad::SetKeyConfig( EKeyConfig eConfig )
{
	switch( eConfig )
	{
		case EKeyConfig_Xbox:
		{
			m_pKeyMap = &m_XboxKeyMap;
		}
		break;
		case EKeyConfig_PS3:
		{
			m_pKeyMap = &m_PS3KeyMap;
		}
		break;
		case EKeyConfig_TimSpecial:
		{
			m_pKeyMap = &m_TimKeyMap;
		}
		break;
	}
}

#endif

