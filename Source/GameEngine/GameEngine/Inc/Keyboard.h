
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <vector>
using namespace std;

enum EKbKey 
{
	EKbKey_BACK         = 0x08,
	EKbKey_TAB          = 0x09,

	EKbKey_CLEAR        = 0x0C,
	EKbKey_RETURN       = 0x0D,

	EKbKey_SHIFT        = 0x10,
	EKbKey_CONTROL      = 0x11,
	EKbKey_MENU         = 0x12,
	EKbKey_PAUSE        = 0x13,
	EKbKey_CAPITAL      = 0x14,

	EKbKey_KANA         = 0x15,
	EKbKey_JUNJA        = 0x17,
	EKbKey_FINAL        = 0x18,
	EKbKey_HANJA        = 0x19,

	EKbKey_ESCAPE       = 0x1B,

	EKbKey_CONVERT      = 0x1C,
	EKbKey_NONCONVERT   = 0x1D,
	EKbKey_ACCEPT       = 0x1E,
	EKbKey_MODECHANGE   = 0x1F,

	EKbKey_SPACE        = 0x20,
	EKbKey_PRIOR        = 0x21,
	EKbKey_NEXT         = 0x22,
	EKbKey_END          = 0x23,
	EKbKey_HOME         = 0x24,
	EKbKey_LEFT         = 0x25,
	EKbKey_UP           = 0x26,
	EKbKey_RIGHT        = 0x27,
	EKbKey_DOWN         = 0x28,
	EKbKey_SELECT       = 0x29,
	EKbKey_PRINT        = 0x2A,
	EKbKey_EXECUTE      = 0x2B,
	EKbKey_SNAPSHOT     = 0x2C,
	EKbKey_INSERT       = 0x2D,
	EKbKey_DELETE       = 0x2E,
	EKbKey_HELP         = 0x2F,

	EKbKey_0			= 0x30,
	EKbKey_1			= 0x31,
	EKbKey_2			= 0x32,
	EKbKey_3			= 0x33,
	EKbKey_4			= 0x34,
	EKbKey_5			= 0x35,
	EKbKey_6			= 0x36,
	EKbKey_7			= 0x37,
	EKbKey_8			= 0x38,
	EKbKey_9			= 0x39,

	EKbKey_A			= 0x41,
	EKbKey_B			= 0x42,
	EKbKey_C			= 0x43,
	EKbKey_D			= 0x44,
	EKbKey_E			= 0x45,
	EKbKey_F			= 0x46,
	EKbKey_G			= 0x47,
	EKbKey_H			= 0x48,
	EKbKey_I			= 0x49,
	EKbKey_J			= 0x4A,
	EKbKey_K			= 0x4B,
	EKbKey_L			= 0x4C,
	EKbKey_M			= 0x4D,
	EKbKey_N			= 0x4E,
	EKbKey_O			= 0x4F,
	EKbKey_P			= 0x50,
	EKbKey_Q			= 0x51,
	EKbKey_R			= 0x52,
	EKbKey_S			= 0x53,
	EKbKey_T			= 0x54,
	EKbKey_U			= 0x55,
	EKbKey_V			= 0x56,
	EKbKey_W			= 0x57,
	EKbKey_X			= 0x58,
	EKbKey_Y			= 0x59,
	EKbKey_Z			= 0x5A,

	EKbKey_LWIN         = 0x5B,
	EKbKey_RWIN         = 0x5C,
	EKbKey_APPS         = 0x5D,

	EKbKey_SLEEP        = 0x5F,
	EKbKey_NUMPAD0      = 0x60,
	EKbKey_NUMPAD1      = 0x61,
	EKbKey_NUMPAD2      = 0x62,
	EKbKey_NUMPAD3      = 0x63,
	EKbKey_NUMPAD4      = 0x64,
	EKbKey_NUMPAD5      = 0x65,
	EKbKey_NUMPAD6      = 0x66,
	EKbKey_NUMPAD7      = 0x67,
	EKbKey_NUMPAD8      = 0x68,
	EKbKey_NUMPAD9      = 0x69,
	EKbKey_MULTIPLY     = 0x6A,
	EKbKey_ADD          = 0x6B,
	EKbKey_SEPARATOR    = 0x6C,
	EKbKey_SUBTRACT     = 0x6D,
	EKbKey_DECIMAL      = 0x6E,
	EKbKey_DIVIDE       = 0x6F,
	EKbKey_F1           = 0x70,
	EKbKey_F2           = 0x71,
	EKbKey_F3           = 0x72,
	EKbKey_F4           = 0x73,
	EKbKey_F5           = 0x74,
	EKbKey_F6           = 0x75,
	EKbKey_F7           = 0x76,
	EKbKey_F8           = 0x77,
	EKbKey_F9           = 0x78,
	EKbKey_F10          = 0x79,
	EKbKey_F11          = 0x7A,
	EKbKey_F12          = 0x7B,
	EKbKey_F13          = 0x7C,
	EKbKey_F14          = 0x7D,
	EKbKey_F15          = 0x7E,
	EKbKey_F16          = 0x7F,
	EKbKey_F17          = 0x80,
	EKbKey_F18          = 0x81,
	EKbKey_F19          = 0x82,
	EKbKey_F20          = 0x83,
	EKbKey_F21          = 0x84,
	EKbKey_F22          = 0x85,
	EKbKey_F23          = 0x86,
	EKbKey_F24          = 0x87,

	EKbKey_NUMLOCK      = 0x90,
	EKbKey_SCROLL       = 0x91,

    EKbKey_DASH         = 0xBD,
    EKbKey_PERIOD       = 0xBE,
    EKbKey_FORWARDSLASH = 0xBF,
    EKbKey_BACKSLASH    = 0xDC,


	EKbKey_MaxKeys		= 0x100
};

class IKeyboardCallback
{
public:
	virtual void	KeyDownCallback(int nKey) = 0;
	virtual void	KeyUpCallback(int nKey) = 0;
};

class CKeyboard
{
public:
	void	Init();
	void	Term();

	void	ProcessInput();

	BOOL	IsKeyDown( EKbKey eKey );
	BOOL	IsKeyTriggered( EKbKey eKey );
	BOOL	IsKeyReleased( EKbKey eKey );

	void	KeyDownCallback( int nKey );
	void	KeyUpCallback( int nKey );

	INT		GetNextCharacter();

	vector<IKeyboardCallback*> Callbacks;

private:
	struct SKeyState
	{
		BOOL bIsDown;
		BOOL bIsTriggered;
		BOOL bIsReleased;
	};

	SKeyState	m_sKeyStates[EKbKey_MaxKeys];

	BOOL	m_KeyBuffer[256];			// Array Used For The Keyboard Routine
	std::list<INT>	m_KeyQueue;
};

inline BOOL CKeyboard::IsKeyDown( EKbKey eKey )
{
	return m_sKeyStates[eKey].bIsDown;
}

inline BOOL CKeyboard::IsKeyTriggered( EKbKey eKey )
{
	return m_sKeyStates[eKey].bIsTriggered;
}

inline BOOL CKeyboard::IsKeyReleased( EKbKey eKey )
{
	return m_sKeyStates[eKey].bIsReleased;
}

#endif
