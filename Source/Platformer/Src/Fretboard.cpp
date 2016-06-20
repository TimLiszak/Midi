#include "StdAfx.h"
#include "Fretboard.h"
#include "Render2d.h"
#include "MidiController.h"
#include "Workspace.h"

#include <vector>
using namespace std;

const float FretWidth = 16.0f;
const float FretHeight = 24.0f;
const float Header = 20.0f;
const float Border = 10.0f;
const float Space = 20.0f;

CFretboard::CFretboard(CWorkspace* InWorkspace, VECTOR InLocation, CTuning InTuning) : CWindow(InWorkspace, InLocation), Tuning(InTuning)
{
	FretScale.push_back(1.0f);
	FretScale.push_back(3.54f);
	FretScale.push_back(3.17f);
	FretScale.push_back(2.99f);
	FretScale.push_back(2.82f);
	FretScale.push_back(2.66f);
	FretScale.push_back(2.51f);
	FretScale.push_back(2.37f);
	FretScale.push_back(2.24f);
	FretScale.push_back(2.11f);
	FretScale.push_back(1.94f);
	FretScale.push_back(1.88f);
	FretScale.push_back(1.78f);
	FretScale.push_back(1.68f);
	FretScale.push_back(1.58f);
	FretScale.push_back(1.49f);
	FretScale.push_back(1.41f);
	FretScale.push_back(1.33f);
	FretScale.push_back(1.25f);
	FretScale.push_back(1.18f);
	FretScale.push_back(1.12f);
	FretScale.push_back(1.05f);
	FretScale.push_back(1.0f);

	Init();
}

void CFretboard::Init()
{
	FretNotes.empty();
	VECTOR Pos(Border, Header);
	VECTOR OffsetY(0.0f, FretHeight);

	int Fret = 0;
	for (std::vector<float>::iterator it = FretScale.begin(); it != FretScale.end(); ++it)
	{
		float Width = FretWidth * (*it);
		VECTOR Extents(Width * 0.5f, FretHeight * 0.5f);
		VECTOR OffsetX(Width, 0.0f);

		for (int String = 0; String < Tuning.GetNumStrings(); String++)
		{
			CNote Note = Tuning.GetNote(String, Fret);
			VECTOR Loc = Pos + OffsetY * String;

			bool bDrawDot = false;
			if (String == 2)
			{
				if (Fret == 3 || Fret == 5 || Fret == 7 || Fret == 9 || Fret == 15 || Fret == 17 || Fret == 19)
				{
					bDrawDot = true;
				}
			}
			if (String == 1 || String == 3)
			{
				if (Fret == 12)
				{
					bDrawDot = true;
				}
			}

			FretNotes.push_back(new CFretNote(Workspace, Loc, Extents * 2.0f, Note, bDrawDot));
		}

		Pos += OffsetX;
		if (Fret == 0)
		{
			Pos.x += Space;
		}
		Fret++;
	}
}

void CFretboard::Update(const FLOAT DeltaTime)
{
}

void CFretboard::Render()
{
	CMidiController* MidiController = Workspace->GetMidiController();

	COLOUR_RGB ClrUnselected = COLOUR_RGB(1.0f, 1.0f, 1.0f);
	COLOUR_RGB ClrSelected = COLOUR_RGB(1.0f, 1.0f, 0.0f);
	COLOUR_RGB ClrBlack = COLOUR_RGB(0.0f, 0.0f, 0.0f);
	COLOUR_RGB ClrOutline = COLOUR_RGB(0.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(6.0f, 12.0f);
	CRender2d::Print(Tuning.GetText().c_str());

	for (std::vector<CFretNote*>::iterator it = FretNotes.begin(); it != FretNotes.end(); ++it)
	{
		(*it)->BeginWindow();
		(*it)->Render();
		(*it)->EndWindow();
	}

	for (std::vector<CFretNote*>::iterator it = FretNotes.begin(); it != FretNotes.end(); ++it)
	{
		(*it)->BeginWindow();
		(*it)->RenderDot();
		(*it)->EndWindow();
	}

	/*
	{
		VECTOR Pos(Border, Header);
		VECTOR OffsetY(0.0f, FretHeight);

		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(6.0f, 12.0f);
		CRender2d::Print(Tuning.GetText().c_str());

		bool is_in;
		int Fret = 0;
		for (std::vector<float>::iterator it = FretScale.begin(); it != FretScale.end(); ++it)
		{
			float Width = FretWidth * (*it);
			VECTOR Extents(Width * 0.5f, FretHeight * 0.5f);
			VECTOR OffsetX(Width, 0.0f);

			if (Fret == 3 || Fret == 5 || Fret == 7 || Fret == 9 || Fret == 15 || Fret == 17 || Fret == 19)
			{
				CRender2d::DrawCircleFill(Pos + Extents + OffsetY * (Tuning.GetNumStrings() - 1) * 0.5f, 8.0f, ClrBlack);
			}
			if (Fret == 12)
			{
				CRender2d::DrawCircleFill(Pos + Extents + OffsetY * (Tuning.GetNumStrings() - 1) * 0.2f, 8.0f, ClrBlack);
				CRender2d::DrawCircleFill(Pos + Extents + OffsetY * (Tuning.GetNumStrings() - 1) * 0.8f, 8.0f, ClrBlack);
			}

			Pos += OffsetX;
			if (Fret == 0)
			{
				Pos.x += Space;
			}
			Fret++;
		}
	}
	*/
}

VECTOR CFretboard::GetWindowDimensions()
{
	float Width = 0.0f;
	float Height = 0.0f;
	for (std::vector<float>::iterator it = FretScale.begin(); it != FretScale.end(); ++it)
	{
		Width += FretWidth * (*it);
	}

	Width += (Border * 2.0f) + Space;
	Height = Border + Header + FretHeight * Tuning.GetNumStrings();

	return VECTOR(Width, Height);
}

void CFretboard::SetTuning(CTuning InTuning)
{
	Tuning = InTuning;
	Init();
}

void CFretboard::OnLeftClick(VECTOR vPos)
{
	CFretNote* FoundKey = nullptr;
	for (std::vector<CFretNote*>::iterator it = FretNotes.begin(); it != FretNotes.end(); ++it)
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
