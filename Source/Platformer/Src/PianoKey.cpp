#include "StdAfx.h"
#include "PianoKey.h"
#include "Render2d.h"
#include "MidiController.h"
#include "Workspace.h"

#include <vector>
using namespace std;

const float CPianoKey::KeyWidth = 24.0f;
const float CPianoKey::KeyHeight = 120.0f;

CPianoKey::CPianoKey(CWorkspace* InWorkspace, VECTOR InLocation, CNote InNote, bool bInBlackKey) : CWindow(InWorkspace, InLocation), Note(InNote), bBlackKey(bInBlackKey)
{
	bDrawBackground = false;
}

void CPianoKey::Update(const FLOAT DeltaTime)
{
}

void CPianoKey::Render()
{
	CMidiController* MidiController = Workspace->GetMidiController();

	COLOUR_RGB ClrUnselected = COLOUR_RGB(1.0f, 1.0f, 1.0f);
	COLOUR_RGB ClrSelected = COLOUR_RGB(1.0f, 1.0f, 0.0f);
	COLOUR_RGB ClrBlack = COLOUR_RGB(0.0f, 0.0f, 0.0f);
	COLOUR_RGB ClrOutline = COLOUR_RGB(0.0f, 0.0f, 0.0f);

	VECTOR BlackKeyOffset(KeyWidth * 0.5f, -KeyHeight * 0.25f);
	VECTOR WhiteKeyExtents(KeyWidth * 0.5f, KeyHeight * 0.5f);
	VECTOR BlackKeyExtents(KeyWidth * 0.25f, KeyHeight * 0.25f);

	bool isNoteOn = false;
	isNoteOn = MidiController->IsNoteOn(Note);
	if (bBlackKey)
	{
		CRender2d::DrawRectOutline(GetWindowDimensions() * 0.5f, GetWindowDimensions() * 0.5f, 0.0f, isNoteOn ? ClrSelected : ClrBlack, ClrOutline);
	}
	else
	{
		CRender2d::DrawRectOutline(GetWindowDimensions() * 0.5f, GetWindowDimensions() * 0.5f, 0.0f, isNoteOn ? ClrSelected : ClrUnselected, ClrOutline);
	}
}

VECTOR CPianoKey::GetWindowDimensions()
{
	if (bBlackKey)
	{
		return VECTOR(KeyWidth * 0.5f, KeyHeight * 0.5f);
	}
	return VECTOR(KeyWidth, KeyHeight);
}

void CPianoKey::OnLeftClick(VECTOR vPos)
{
	CMidiController* MidiController = Workspace->GetMidiController();
	MidiController->ToggleNote(Note);
}
