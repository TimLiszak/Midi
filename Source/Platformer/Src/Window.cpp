#include "StdAfx.h"
#include "Window.h"
#include "Render2d.h"

CWindow::CWindow(CWorkspace* InWorkspace, VECTOR InLocation) : Workspace(InWorkspace), Location(InLocation)
{
	bDrawBackground = true;
}

void CWindow::Update(const FLOAT DeltaTime)
{
}

void CWindow::Render()
{
}

void CWindow::BeginWindow()
{
	CRender2d::PushMatrix();
	CRender2d::Translate(Location);

	if (bDrawBackground)
	{
		CRender2d::DrawRectFill(GetWindowDimensions() * 0.5f, GetWindowDimensions() * 0.5f, 0.0f, COLOUR_RGB(0.4f, 0.4f, 0.4f));
	}
}

void CWindow::EndWindow()
{
	CRender2d::PopMatrix();
}

bool CWindow::IsInWindow(VECTOR InLocation)
{
	return InLocation.x >= Location.x &&
		InLocation.x <= Location.x + GetWindowDimensions().x &&
		InLocation.y >= Location.y &&
		InLocation.y <= Location.y + GetWindowDimensions().y;
}
