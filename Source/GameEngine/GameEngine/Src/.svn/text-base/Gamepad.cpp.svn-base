#include "StdAfx.h"
#include "Gamepad.h"
#include "DebugPrint.h"
#include "View.h"

static const FLOAT	STICK_AXIS_MAX = 1000.0f;
static const FLOAT	STICK_DEAD_ZONE = 0.3f;

void CGamepad::SetDirectInputDevice( LPDIRECTINPUTDEVICE8 pJoystick )
{
	g_pJoystick = pJoystick;
}

void CGamepad::Init()
{
	memset( m_PadState, 0, sizeof(m_PadState) );
	memset( m_StickState, 0, sizeof(m_StickState) );

	g_pJoystick = NULL;

	m_XboxKeyMap[0] = EPad_FaceBottom;
	m_XboxKeyMap[1] = EPad_FaceRight;
	m_XboxKeyMap[2] = EPad_FaceLeft;
	m_XboxKeyMap[3] = EPad_FaceTop;
	m_XboxKeyMap[4] = EPad_LeftShoulder1;
	m_XboxKeyMap[5] = EPad_RightShoulder1;
	m_XboxKeyMap[6] = EPad_Select;
	m_XboxKeyMap[7] = EPad_Start;
	m_XboxKeyMap[8] = EPad_LeftStick;
	m_XboxKeyMap[9] = EPad_RightStick;

	m_PS3KeyMap[0] = EPad_Select;
	m_PS3KeyMap[1] = EPad_LeftStick;
	m_PS3KeyMap[2] = EPad_RightStick;
	m_PS3KeyMap[3] = EPad_Start;
	m_PS3KeyMap[4] = EPad_DPadUp;
	m_PS3KeyMap[5] = EPad_DPadRight;
	m_PS3KeyMap[6] = EPad_DPadDown;
	m_PS3KeyMap[7] = EPad_DPadLeft;
	m_PS3KeyMap[8] = EPad_LeftShoulder2;
	m_PS3KeyMap[9] = EPad_RightShoulder2;
	m_PS3KeyMap[10] = EPad_LeftShoulder1;
	m_PS3KeyMap[11] = EPad_RightShoulder1;
	m_PS3KeyMap[12] = EPad_FaceTop;
	m_PS3KeyMap[13] = EPad_FaceRight;
	m_PS3KeyMap[14] = EPad_FaceBottom;
	m_PS3KeyMap[15] = EPad_FaceLeft;
	m_PS3KeyMap[16] = EPad_Home;

	
	m_TimKeyMap[0] = EPad_FaceTop;
	m_TimKeyMap[1] = EPad_FaceRight;
	m_TimKeyMap[2] = EPad_FaceBottom;
	m_TimKeyMap[3] = EPad_FaceLeft;
	m_TimKeyMap[4] = EPad_LeftShoulder2;
	m_TimKeyMap[5] = EPad_RightShoulder2;
	m_TimKeyMap[6] = EPad_LeftShoulder1;
	m_TimKeyMap[7] = EPad_RightShoulder1;
	m_TimKeyMap[8] = EPad_Select;
	m_TimKeyMap[9] = EPad_Start;
	m_TimKeyMap[10] = EPad_LeftStick;
	m_TimKeyMap[11] = EPad_RightStick;
	m_TimKeyMap[12] = EPad_Home;


	m_pKeyMap = &m_PS3KeyMap;

}

void CGamepad::Term()
{
}

void CGamepad::Acquire()
{
	if ( g_pJoystick )
	{
		g_pJoystick->Acquire();
	}
}

void CGamepad::ProcessInput()
{
	UpdateInputState();
}

HRESULT CGamepad::UpdateInputState()
{
    HRESULT hr;
    //TCHAR strText[512] = {0}; // Device state text
    DIJOYSTATE2 js;           // DInput joystick state 

    if( NULL == g_pJoystick )
        return S_OK;

    // Poll the device to read the current state
    hr = g_pJoystick->Poll();
    if( FAILED( hr ) )
    {
        // DInput is telling us that the input stream has been
        // interrupted. We aren't tracking any state between polls, so
        // we don't have any special reset that needs to be done. We
        // just re-acquire and try again.
        hr = g_pJoystick->Acquire();
        while( hr == DIERR_INPUTLOST )
            hr = g_pJoystick->Acquire();

        // hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
        // may occur when the app is minimized or in the process of 
        // switching, so just try again later 
        return S_OK;
    }

    // Get the input's device state
    if( FAILED( hr = g_pJoystick->GetDeviceState( sizeof( DIJOYSTATE2 ), &js ) ) )
        return hr; // The device should have been acquired during the Poll()


    for( UINT i = 0; i < (*m_pKeyMap).size(); i++ )
    {
		EPadButtons eButton = (*m_pKeyMap)[i];
        BOOL bIsDown = ( js.rgbButtons[i] & 0x80 );

		m_PadState[eButton].bIsTriggered = FALSE;
		m_PadState[eButton].bIsReleased = FALSE;

		if ( bIsDown )
		{
			if ( !m_PadState[eButton].bIsDown )
			{
				m_PadState[eButton].bIsTriggered = TRUE;
			}
			m_PadState[eButton].bIsDown = TRUE;
		}
		else
		{
			if ( m_PadState[eButton].bIsDown )
			{
				m_PadState[eButton].bIsReleased = TRUE;
			}
			m_PadState[eButton].bIsDown = FALSE;
		}

	}

	
	//m_PadState[EPad_DPadRight].bIsDown = ( js.lX > 0 );
	//m_PadState[EPad_DPadLeft].bIsDown = ( js.lX < 0 );
	//m_PadState[EPad_DPadUp].bIsDown = ( js.lY < 0 );
	//m_PadState[EPad_DPadDown].bIsDown = ( js.lY > 0 );

	m_StickState[EStick_Left].fXAxis = (FLOAT)js.lX / STICK_AXIS_MAX;
	m_StickState[EStick_Left].fYAxis = (FLOAT)js.lY / STICK_AXIS_MAX;
	m_StickState[EStick_Right].fXAxis = (FLOAT)js.lX / STICK_AXIS_MAX;
	m_StickState[EStick_Right].fYAxis = (FLOAT)js.lY / STICK_AXIS_MAX;

	//Check deadzone
	for (INT i = 0; i < EStick_Max; i++)
	{
		FLOAT fX = m_StickState[i].fXAxis;
		FLOAT fY = m_StickState[i].fYAxis;
		if ( fX * fX + fY * fY < STICK_DEAD_ZONE * STICK_DEAD_ZONE )
		{
			m_StickState[i].fXAxis = 0.0f;
			m_StickState[i].fYAxis = 0.0f;
		}
	}
	
    // Display joystick state to dialog
	//GetGameEngine()->GetDebugPrint()->Printf( "left stick x %f\n", m_StickState[EStick_Left].fXAxis );
	//GetGameEngine()->GetDebugPrint()->Printf( "left stick y %f\n", m_StickState[EStick_Left].fYAxis );
	//GetGameEngine()->GetDebugPrint()->Printf( "right stick x %f\n", m_StickState[EStick_Right].fXAxis );
	//GetGameEngine()->GetDebugPrint()->Printf( "right stick y %f\n", m_StickState[EStick_Right].fYAxis );

	/*
    // Fill up text with which buttons are pressed
	std::string strButtons = "";
    for( UINT i = 0; i < (*m_pKeyMap).size(); i++ )
    {
        if( js.rgbButtons[i] & 0x80 )
        {
			CHAR buf[100];
			sprintf_s( buf, 100, "%02d ", i );
            strButtons += buf;
        }
    }
	GetGameEngine()->GetDebugPrint()->Printf( "buttons %s\n", strButtons.c_str() );*/
	

    return S_OK;
}

