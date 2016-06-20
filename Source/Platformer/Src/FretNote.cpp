#include "StdAfx.h"
#include "FretNote.h"
#include "Render2d.h"
#include "MidiController.h"
#include "Workspace.h"

#include <vector>
using namespace std;

const float CFretNote::KeyWidth = 24.0f;
const float CFretNote::KeyHeight = 120.0f;

CFretNote::CFretNote(CWorkspace* InWorkspace, VECTOR InLocation, VECTOR InDimensions, CNote InNote, bool bInDrawDot) : 
CWindow(InWorkspace, InLocation), Note(InNote), Dimensions(InDimensions), bDrawDot(bInDrawDot)
{
	bDrawBackground = false;
}

void CFretNote::Update(const FLOAT DeltaTime)
{
}

void CFretNote::Render()
{
	CMidiController* MidiController = Workspace->GetMidiController();

	COLOUR_RGB ClrUnselected = COLOUR_RGB(1.0f, 1.0f, 1.0f);
	COLOUR_RGB ClrSelected = COLOUR_RGB(1.0f, 1.0f, 0.0f);
	COLOUR_RGB ClrOutline = COLOUR_RGB(0.0f, 0.0f, 0.0f);

	bool isNoteOn = false;
	isNoteOn = MidiController->IsNoteOn(Note);
	CRender2d::DrawRectOutline(GetWindowDimensions() * 0.5f, GetWindowDimensions() * 0.5f, 0.0f, isNoteOn ? ClrSelected : ClrUnselected, ClrOutline);

	CRender2d::PushMatrix();
	CRender2d::Translate(Dimensions * 0.5f);
	glRasterPos2f(-4.0f, 0.0f);
	CRender2d::Print("%s", Note.GetString().c_str());
	CRender2d::PopMatrix();
}

void CFretNote::RenderDot()
{
	COLOUR_RGB ClrBlack = COLOUR_RGB(0.0f, 0.0f, 0.0f);
	if (bDrawDot)
	{
		VECTOR Pos = Dimensions;
		Pos.x *= 0.5f;
		CRender2d::DrawCircleFill(Pos, 5.0f, ClrBlack);
	}

}

VECTOR CFretNote::GetWindowDimensions()
{
	return Dimensions;
}

void CFretNote::OnLeftClick(VECTOR vPos)
{
	CMidiController* MidiController = Workspace->GetMidiController();
	MidiController->ToggleNote(Note);
}
