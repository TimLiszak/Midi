#include "StdAfx.h"
#include "Piano.h"
#include "Render2d.h"
#include "MidiController.h"
#include "Workspace.h"

#include <vector>
using namespace std;

const float Border = 10.0f;

CPiano::CPiano(CWorkspace* InWorkspace, VECTOR InLocation) : CWindow(InWorkspace, InLocation)
{
	CNote Note("C", 2);
	VECTOR Pos(Border, Border);
	VECTOR Offset(CPianoKey::KeyWidth, 0.0f);
	VECTOR BlackKeyOffset(CPianoKey::KeyWidth * 0.75f, 0.0f);
	int WhiteStep[] = { 2, 2, 1, 2, 2, 2, 1 };
	int BlackPos[] = { 1, 2, 1, 1, 2 };
	int BlackStep[] = { 2, 3, 2, 2, 3 };

	for (int i = 0; i < 36; i++)
	{
		PianoKeys.push_back(new CPianoKey(InWorkspace, Pos, Note, false));
		 
		Pos += Offset;
		Note = Note + WhiteStep[i % 7];
	}

	Note = CNote("C#", 2);
	Pos = VECTOR(Border, Border);
	for (int i = 0; i < 25; i++)
	{
		PianoKeys.push_back(new CPianoKey(InWorkspace, Pos + BlackKeyOffset, Note, true));

		Pos += Offset * BlackPos[i % 5];
		Note = Note + BlackStep[i % 5];
	}
}

void CPiano::Update(const FLOAT DeltaTime)
{
}

void CPiano::Render()
{
	for (std::vector<CPianoKey*>::iterator it = PianoKeys.begin(); it != PianoKeys.end(); ++it)
	{
		(*it)->BeginWindow();
		(*it)->Render();
		(*it)->EndWindow();
	}
}

VECTOR CPiano::GetWindowDimensions()
{
	return VECTOR(36 * CPianoKey::KeyWidth + Border * 2, CPianoKey::KeyHeight + Border * 2);
}

void CPiano::OnLeftClick(VECTOR vPos)
{
	CPianoKey* FoundKey = nullptr;
	for (std::vector<CPianoKey*>::iterator it = PianoKeys.begin(); it != PianoKeys.end(); ++it)
	{
		if ((*it)->IsInWindow(vPos))
		{
			FoundKey = (*it);
		}
	}

	if (FoundKey)
	{
		FoundKey->OnLeftClick(vPos - FoundKey->Location);
	}
}

