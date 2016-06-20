#include "StdAfx.h"
#include "DebugCamera.h"
#include "Input.h"
#include "View.h"

CDebugCamera::CDebugCamera()
{
	m_vScroll.x = 0.0f;
	m_vScroll.y = 0.0f;
}

VECTOR CDebugCamera::GetScroll()
{
	return m_vScroll;
}

void CDebugCamera::SetScroll( VECTOR vScroll )
{
	m_vScroll = vScroll;
}

void CDebugCamera::Update( const FLOAT fFrameTime, BOOL bIsCurrent )
{
	CMouse* pMouse = GetGameEngine()->GetInput()->GetMouse();
	VECTOR vScroll = GetScroll();

	if ( pMouse->IsMouseDown( EMouseButton_Middle ) )
	{
		VECTOR vMove = pMouse->GetMousePosition() - m_vLastMousePos;
		vMove = vMove * GetGameEngine()->GetView()->GetZoom();
		vScroll = vScroll - vMove;
		SetScroll( vScroll );
	}
	m_vLastMousePos = pMouse->GetMousePosition();
}