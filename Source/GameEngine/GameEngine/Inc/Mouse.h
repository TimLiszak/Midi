
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <vector>
using namespace std;

enum EMouseButton
{
	EMouseButton_Left,
	EMouseButton_Right,
	EMouseButton_Middle,

	EMouseButton_Max
};


class IMouseCallback
{
public:
	virtual void	MouseDownCallback(EMouseButton eButton, VECTOR vPos) = 0;
	virtual void	MouseUpCallback(EMouseButton eButton, VECTOR vPos) = 0;
	virtual void	MouseMoveCallback(VECTOR vPos) = 0;
};

class CMouse
{
public:
	void	Init();
	void	Term();
	void	ProcessInput();

	BOOL	IsMouseDown( EMouseButton eButton );
	BOOL	IsMouseTriggered( EMouseButton eButton );
	BOOL	IsMouseReleased( EMouseButton eButton );
	VECTOR GetMousePosition();

	void	MouseDownCallback( EMouseButton eButton, VECTOR vPos );
	void	MouseUpCallback( EMouseButton eButton, VECTOR vPos );
	void	MouseMoveCallback( VECTOR vPos );

	vector<IMouseCallback*> Callbacks;

private:
	struct SMouseState
	{
		BOOL	bIsDown;
		BOOL	bIsTriggered;
		BOOL	bIsReleased;
	};
	SMouseState	m_MouseState[EMouseButton_Max];

	BOOL	m_bIsDown[EMouseButton_Max];
	VECTOR m_vPosition;
};

inline BOOL	CMouse::IsMouseDown( EMouseButton eButton )
{
	return m_MouseState[eButton].bIsDown;
}

inline BOOL	CMouse::IsMouseTriggered( EMouseButton eButton )
{
	return m_MouseState[eButton].bIsTriggered;
}

inline BOOL	CMouse::IsMouseReleased( EMouseButton eButton )
{
	return m_MouseState[eButton].bIsReleased;
}

inline VECTOR CMouse::GetMousePosition()
{
	return m_vPosition;
}

#endif

