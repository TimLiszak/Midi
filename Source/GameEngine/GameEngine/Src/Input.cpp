#include "StdAfx.h"
#include "Input.h"

BOOL CALLBACK    _EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext );
BOOL CALLBACK    _EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );

struct DI_ENUM_CONTEXT
{
    DIJOYCONFIG* pPreferredJoyCfg;
    bool bPreferredJoyCfgValid;
	CInput* pInstance;
};

struct DI_ENUM_OBJECT_CONTEXT
{
	CInput* pInstance;
    LPDIRECTINPUTDEVICE8 pJoystick;
};

void CInput::Init()
{
	m_FoundGampads.clear();
	g_pDI = NULL;
	InitDirectInput( GetGameEngine()->GetView()->GetHWnd() );

	m_Keyboard.Init();
	m_Mouse.Init();

	for (UINT i = 0; i < MAX_GAMEPADS; i++) 
	{
		m_Gamepad[i].Init();
	}

	UINT i = 0;
	std::list< LPDIRECTINPUTDEVICE8 >::iterator it;
	for ( it = m_FoundGampads.begin() ; it != m_FoundGampads.end(); it++ )
	{
		m_Gamepad[i].SetDirectInputDevice( (*it) );
		i++;
		if ( i >= MAX_GAMEPADS )
		{
			break;
		}
	}

	m_bDisableInput = FALSE;
}

void CInput::Update()
{
	m_Keyboard.ProcessInput();
	m_Mouse.ProcessInput();

	for (UINT i = 0; i < MAX_GAMEPADS; i++) 
	{
		m_Gamepad[i].ProcessInput();
	}
}

void CInput::Term()
{
	m_Keyboard.Term();
	m_Mouse.Term();

	for (UINT i = 0; i < MAX_GAMEPADS; i++) 
	{
		m_Gamepad[i].Term();
	}
}

HRESULT CInput::InitDirectInput( HWND hDlg )
{
    HRESULT hr;

    // Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    // Create a DInput object
    if( FAILED( hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION,
                                         IID_IDirectInput8, ( VOID** )&g_pDI, NULL ) ) )
        return hr;


    //if( g_bFilterOutXinputDevices )
    //    SetupForIsXInputDevice();

    DIJOYCONFIG PreferredJoyCfg = {0};
    DI_ENUM_CONTEXT enumContext;
    enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
    enumContext.bPreferredJoyCfgValid = false;
	enumContext.pInstance = this;

    IDirectInputJoyConfig8* pJoyConfig = NULL;
    if( FAILED( hr = g_pDI->QueryInterface( IID_IDirectInputJoyConfig8, ( void** )&pJoyConfig ) ) )
        return hr;

    PreferredJoyCfg.dwSize = sizeof( PreferredJoyCfg );
    if( SUCCEEDED( pJoyConfig->GetConfig( 0, &PreferredJoyCfg, DIJC_GUIDINSTANCE ) ) ) // This function is expected to fail if no joystick is attached
        enumContext.bPreferredJoyCfgValid = true;
    SAFE_RELEASE( pJoyConfig );

    // Look for a simple joystick we can use for this sample program.
    if( FAILED( hr = g_pDI->EnumDevices( DI8DEVCLASS_GAMECTRL,
                                         _EnumJoysticksCallback,
                                         &enumContext, DIEDFL_ATTACHEDONLY ) ) )
        return hr;

    //if( g_bFilterOutXinputDevices )
    //    CleanupForIsXInputDevice();

    // Make sure we got a joystick
    if( m_FoundGampads.size() == 0 )
    {
        //MessageBox( NULL, TEXT( "Joystick not found. The sample will now exit." ),
        //            TEXT( "DirectInput Sample" ),
        //            MB_ICONERROR | MB_OK );
        //EndDialog( hDlg, 0 );
        return S_OK;
    }

	std::list<LPDIRECTINPUTDEVICE8>::iterator it;
	for ( it = m_FoundGampads.begin() ; it != m_FoundGampads.end(); it++ )
	{
		// Set the data format to "simple joystick" - a predefined data format 
		//
		// A data format specifies which controls on a device we are interested in,
		// and how they should be reported. This tells DInput that we will be
		// passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
		if( FAILED( hr = (*it)->SetDataFormat( &c_dfDIJoystick2 ) ) )
			return hr;

		// Set the cooperative level to let DInput know how this device should
		// interact with the system and with other DInput applications.
		if( FAILED( hr = (*it)->SetCooperativeLevel( hDlg, DISCL_EXCLUSIVE |
														   DISCL_FOREGROUND ) ) )
			return hr;

		DI_ENUM_OBJECT_CONTEXT ObjContext;
		ObjContext.pInstance = this;
		ObjContext.pJoystick = (*it);

		// Enumerate the joystick objects. The callback function enabled user
		// interface elements for objects that are found, and sets the min/max
		// values property for discovered axes.
		if( FAILED( hr = (*it)->EnumObjects( _EnumObjectsCallback,
												   ( VOID* )&ObjContext, DIDFT_ALL ) ) )
			return hr;

	}
	
    return S_OK;
}


BOOL CALLBACK _EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext )
{
	DI_ENUM_OBJECT_CONTEXT* pObjContext = (DI_ENUM_OBJECT_CONTEXT*)pContext;
	return pObjContext->pInstance->EnumObjectsCallback( pdidoi, pContext );
}

//-----------------------------------------------------------------------------
// Name: EnumObjectsCallback()
// Desc: Callback function for enumerating objects (axes, buttons, POVs) on a 
//       joystick. This function enables user interface elements for objects
//       that are found to exist, and scales axes min/max values.
//-----------------------------------------------------------------------------
BOOL CInput::EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext )
{
    //HWND hDlg = ( HWND )pContext;
	DI_ENUM_OBJECT_CONTEXT* pObjContext = (DI_ENUM_OBJECT_CONTEXT*)pContext;

    static int nSliderCount = 0;  // Number of returned slider controls
    static int nPOVCount = 0;     // Number of returned POV controls

    // For axes that are returned, set the DIPROP_RANGE property for the
    // enumerated axis in order to scale min/max values.
    if( pdidoi->dwType & DIDFT_AXIS )
    {
        DIPROPRANGE diprg;
        diprg.diph.dwSize = sizeof( DIPROPRANGE );
        diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );
        diprg.diph.dwHow = DIPH_BYID;
        diprg.diph.dwObj = pdidoi->dwType; // Specify the enumerated axis
        diprg.lMin = -1000;
        diprg.lMax = +1000;

        // Set the range for the axis
		if( FAILED( pObjContext->pJoystick->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
            return DIENUM_STOP;

    }

    return DIENUM_CONTINUE;
}

BOOL CALLBACK _EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,
                                     VOID* pContext )
{
    DI_ENUM_CONTEXT* pEnumContext = ( DI_ENUM_CONTEXT* )pContext;
	return pEnumContext->pInstance->EnumJoysticksCallback( pdidInstance, pContext );
}

BOOL CInput::EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,
                                     VOID* pContext )
{
    //DI_ENUM_CONTEXT* pEnumContext = ( DI_ENUM_CONTEXT* )pContext;
    HRESULT hr;

    //if( g_bFilterOutXinputDevices && IsXInputDevice( &pdidInstance->guidProduct ) )
    //    return DIENUM_CONTINUE;

    // Skip anything other than the perferred joystick device as defined by the control panel.  
    // Instead you could store all the enumerated joysticks and let the user pick.
    //if( pEnumContext->bPreferredJoyCfgValid &&
    //    !IsEqualGUID( pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance ) )
    //    return DIENUM_CONTINUE;

    // Obtain an interface to the enumerated joystick.
	LPDIRECTINPUTDEVICE8   pJoystick = NULL;
    hr = g_pDI->CreateDevice( pdidInstance->guidInstance, &pJoystick, NULL );
    // If it failed, then we can't use this joystick. (Maybe the user unplugged
    // it while we were in the middle of enumerating it.)
    if( FAILED( hr ) )
        return DIENUM_CONTINUE;

	if ( pJoystick )
	{
		m_FoundGampads.push_back( pJoystick );
	}

    // Stop enumeration. Note: we're just taking the first joystick we get. You
    // could store all the enumerated joysticks and let the user pick.
    return DIENUM_CONTINUE;
}
