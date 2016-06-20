#include "StdAfx.h"
#include "Workspace.h"
#include "Render2d.h"
#include "MidiController.h"
#include "MidiControllerGuitar.h"
#include "MidiOutput.h"
#include "Fretboard.h"
#include "Piano.h"
#include "Tuning.h"
#include "Input.h"
#include "..\resource.h"

const int TUNING_MENU_ID = 41000;
const int CLEAR_NOTES_ID = 53454;

void CWorkspace::Init()
{
	AddTuning("Standard", -1,			CNote("E", 2), CNote("A", 2), CNote("D", 3), CNote("G", 3), CNote("B", 3), CNote("E", 4));
	AddTuning("Drop D", 0,				CNote("D", 2), CNote("A", 2), CNote("D", 3), CNote("G", 3), CNote("B", 3), CNote("E", 4));
	AddTuning("Double Drop D", 0,		CNote("D", 2), CNote("A", 2), CNote("D", 3), CNote("G", 3), CNote("B", 3), CNote("D", 4));
	AddTuning("D Modal", 0,				CNote("D", 2), CNote("A", 2), CNote("D", 3), CNote("G", 3), CNote("A", 3), CNote("D", 4));
	AddTuning("Double Daddy", 0,		CNote("D", 2), CNote("A", 2), CNote("D", 3), CNote("D", 3), CNote("A", 3), CNote("D", 4));
	AddTuning("Drop C#", 0,				CNote("C#", 2), CNote("G#", 2), CNote("C#", 3), CNote("F#", 3), CNote("A#", 3), CNote("D#", 4));
	AddTuning("Drop C", 0,				CNote("C", 2), CNote("G", 2), CNote("C", 3), CNote("F", 3), CNote("A", 3), CNote("D", 4));
	AddTuning("Drop B", 0,				CNote("B", 1), CNote("F#", 2), CNote("B", 2), CNote("E", 3), CNote("G#", 3), CNote("C#", 4));
	AddTuning("Drop A", 0,				CNote("A", 1), CNote("E", 2), CNote("A", 2), CNote("D", 3), CNote("F#", 3), CNote("B", 3));

	AddTuning("Open C", 1,				CNote("C", 2), CNote("G", 2), CNote("C", 3), CNote("G", 3), CNote("C", 4), CNote("E", 4));
	AddTuning("Open E", 1,				CNote("E", 2), CNote("B", 2), CNote("E", 3), CNote("G#", 3), CNote("B", 3), CNote("E", 4));
	AddTuning("Open F", 1,				CNote("C", 2), CNote("F", 2), CNote("C", 3), CNote("F", 3), CNote("A", 3), CNote("F", 4));
	AddTuning("Open G", 1,				CNote("D", 2), CNote("G", 2), CNote("D", 3), CNote("G", 3), CNote("B", 3), CNote("D", 4));
	AddTuning("Open A", 1,				CNote("E", 2), CNote("A", 2), CNote("C#", 3), CNote("E", 3), CNote("A", 3), CNote("E", 4));
	AddTuning("Open A2", 1,				CNote("E", 2), CNote("A", 2), CNote("E", 3), CNote("A", 3), CNote("C#", 4), CNote("E", 4));
	AddTuning("Open Am", 1,				CNote("E", 2), CNote("A", 2), CNote("E", 3), CNote("A", 3), CNote("C", 4), CNote("E", 4));
	AddTuning("Open Em", 1,				CNote("E", 2), CNote("B", 2), CNote("E", 3), CNote("G", 3), CNote("B", 3), CNote("E", 4));
	AddTuning("Open D", 1,				CNote("D", 2), CNote("A", 2), CNote("D", 3), CNote("F#", 3), CNote("A", 3), CNote("D", 4));
	AddTuning("Open Dm", 1,				CNote("D", 2), CNote("A", 2), CNote("D", 3), CNote("F", 3), CNote("A", 3), CNote("D", 4));
	AddTuning("Open C#", 1,				CNote("C#", 2), CNote("G#", 2), CNote("C#", 3), CNote("F", 3), CNote("G#", 3), CNote("C#", 4));

	AddTuning("Half Step Down", 2,		CNote("D#", 2), CNote("G#", 2), CNote("C#", 3), CNote("F#", 3), CNote("A#", 3), CNote("D#", 4));
	AddTuning("Whole Step Down", 2,		CNote("D", 2), CNote("G", 2), CNote("C", 3), CNote("F", 3), CNote("A", 3), CNote("D", 4));
	AddTuning("G Modal", 2,				CNote("D", 2), CNote("G", 2), CNote("D", 3), CNote("G", 3), CNote("C", 4), CNote("D", 4));
	AddTuning("All 4'th", 2,			CNote("E", 2), CNote("A", 2), CNote("D", 3), CNote("G", 3), CNote("C", 4), CNote("F", 4));
	AddTuning("NST", 2,					CNote("C", 2), CNote("G", 2), CNote("D", 3), CNote("A", 3), CNote("E", 4), CNote("G", 4));
	AddTuning("Rain Song", 2,			CNote("D", 2), CNote("G", 2), CNote("C", 3), CNote("G", 3), CNote("C", 4), CNote("D", 4));
	AddTuning("Capo 1", 2,				CNote("F", 2), CNote("A#", 2), CNote("D#", 3), CNote("G#", 3), CNote("C", 4), CNote("F", 4));

	CTuning Twelve("12 String - Standard", 2);
	Twelve.AddString(CNote("E", 3));
	Twelve.AddString(CNote("E", 2));
	Twelve.AddString(CNote("A", 3));
	Twelve.AddString(CNote("A", 2));
	Twelve.AddString(CNote("D", 4));
	Twelve.AddString(CNote("D", 3));
	Twelve.AddString(CNote("G", 4));
	Twelve.AddString(CNote("G", 3));
	Twelve.AddString(CNote("B", 3));
	Twelve.AddString(CNote("B", 3));
	Twelve.AddString(CNote("E", 4));
	Twelve.AddString(CNote("E", 4));
	Tunings.push_back(Twelve);


	CTuning Banjo("Banjo", 3);
	Banjo.AddString(CNote("G", 4));
	Banjo.AddString(CNote("D", 3));
	Banjo.AddString(CNote("G", 3));
	Banjo.AddString(CNote("B", 3));
	Banjo.AddString(CNote("D", 4));
	Tunings.push_back(Banjo);

	AddTuning("Ukelele: C", 4,			CNote("G", 4), CNote("C", 4), CNote("E", 4), CNote("A", 4));
	AddTuning("Ukelele: D", 4,			CNote("A", 4), CNote("D", 4), CNote("F#", 4), CNote("B", 4));
	AddTuning("Ukelele: Low G", 4,		CNote("G", 3), CNote("C", 4), CNote("E", 4), CNote("A", 4));
	AddTuning("Ukelele: Low A", 4,		CNote("A", 3), CNote("D", 4), CNote("F#", 4), CNote("B", 4));
	AddTuning("Ukelele: Slack Key", 4,	CNote("G", 4), CNote("C", 4), CNote("E", 4), CNote("G", 4));
	AddTuning("Ukelele: B", 4,			CNote("F#", 4), CNote("B", 3), CNote("D#", 4), CNote("G#", 4));

	Windows.push_back(new CFretboard(this, VECTOR(50.0f, 100.0f), Tunings[0]));
	//Windows.push_back(new CFretboard(this, VECTOR(80.0f, 300.0f), RainSong));
	//Windows.push_back(new CFretboard(this, VECTOR(80.0f, 500.0f), UkeleleD));

	Windows.push_back(new CPiano(this, VECTOR(80.0f, 300.0f)));

	MidiController = new CMidiControllerGuitar(this, VECTOR(1000.0f, 50.0f), Tunings[0]);
	//MidiController = new CMidiController(this, VECTOR(1000.0f, 50.0f));
	Windows.push_back(MidiController);

	MidiOutput = new CMidiOutput();

	CKeyboard* pKeyboard = GetGameEngine()->GetInput()->GetKeyboard();
	CMouse* pMouse = GetGameEngine()->GetInput()->GetMouse();
	pMouse->Callbacks.push_back(this);
	pKeyboard->Callbacks.push_back(this);
	GetGameEngine()->AddMenuCallback(this);

	MovingWindow = nullptr;
	bShiftDown = false;
}

void CWorkspace::AddTuning(string Name, int Category, CNote Note1, CNote Note2, CNote Note3, CNote Note4)
{
	CTuning Tuning(Name, Category);
	Tuning.AddString(Note1);
	Tuning.AddString(Note2);
	Tuning.AddString(Note3);
	Tuning.AddString(Note4);
	Tunings.push_back(Tuning);
}

void CWorkspace::AddTuning(string Name, int Category, CNote Note1, CNote Note2, CNote Note3, CNote Note4, CNote Note5, CNote Note6)
{
	CTuning Tuning(Name, Category);
	Tuning.AddString(Note1);
	Tuning.AddString(Note2);
	Tuning.AddString(Note3);
	Tuning.AddString(Note4);
	Tuning.AddString(Note5);
	Tuning.AddString(Note6);
	Tunings.push_back(Tuning);
}

void CWorkspace::Update(const FLOAT DeltaTime)
{
	MidiController->Update(DeltaTime);
	MidiOutput->Update(DeltaTime);

	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		(*it)->Update(DeltaTime);
	}
}

void CWorkspace::Term()
{
	delete MidiOutput;

	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		delete (*it);
	}
	Windows.clear();
}

void CWorkspace::Render()
{
	MidiController->Render();
	MidiOutput->Render();

	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		(*it)->BeginWindow();
		(*it)->Render();
		(*it)->EndWindow();
	}
}

CMidiController* CWorkspace::GetMidiController()
{
	return MidiController;
}

CMidiOutput* CWorkspace::GetMidiOutput()
{
	return MidiOutput;
}

void CWorkspace::MouseDownCallback(EMouseButton eButton, VECTOR vPos)
{
	MovingWindow = nullptr;

	CWindow* FoundWindow = nullptr;
	for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
	{
		if ((*it)->IsInWindow(vPos))
		{
			FoundWindow = (*it);
			break;
		}
	}
	
	if (eButton == EMouseButton_Left)
	{
		if (bShiftDown)
		{
			MovingWindow = FoundWindow;
			MovingStart = vPos;
		}
		else if (FoundWindow)
		{
			FoundWindow->OnLeftClick(vPos - FoundWindow->Location);
		}
	}
	if (eButton == EMouseButton_Right)
	{
		if (FoundWindow && FoundWindow->HasTuning())
		{
			SelectedWindow = FoundWindow;
			HWND hWnd = GetGameEngine()->GetView()->GetHWnd();

			RECT Rect;
			GetWindowRect(hWnd, &Rect);

			HMENU hPopupMenu = CreatePopupMenu();
				
			{
				HMENU hTuningMenu = CreatePopupMenu();
				AppendMenu(hPopupMenu, MF_POPUP, (UINT)hTuningMenu, "&Tuning");

				vector<HMENU> Categories;
				Categories.push_back(CreatePopupMenu());
				Categories.push_back(CreatePopupMenu());
				Categories.push_back(CreatePopupMenu());
				Categories.push_back(CreatePopupMenu());
				Categories.push_back(CreatePopupMenu());
				AppendMenu(hTuningMenu, MF_POPUP, (UINT)Categories[0], "Guitar - Power");
				AppendMenu(hTuningMenu, MF_POPUP, (UINT)Categories[1], "Guitar - Open");
				AppendMenu(hTuningMenu, MF_POPUP, (UINT)Categories[2], "Guitar - Other");
				AppendMenu(hTuningMenu, MF_POPUP, (UINT)Categories[3], "Banjo");
				AppendMenu(hTuningMenu, MF_POPUP, (UINT)Categories[4], "Ukelele");

				int i = 0;
				for (std::vector<CTuning>::iterator it2 = Tunings.begin(); it2 != Tunings.end(); ++it2)
				{
					int Category = (*it2).GetCategory();
					if (Category == -1)
					{
						InsertMenu(hTuningMenu, i, MF_BYPOSITION | MF_STRING, TUNING_MENU_ID + i, (*it2).GetText().c_str());
					}
					else
					{
						InsertMenu(Categories[(*it2).GetCategory()], i, MF_BYPOSITION | MF_STRING, TUNING_MENU_ID + i, (*it2).GetText().c_str());
					}
					i++;
				}
			}

			{
				HMENU hMenu = CreatePopupMenu();
				AppendMenu(hPopupMenu, MF_POPUP, (UINT)hMenu, "&MIDI Input");
				for (int i = 0; i < Pm_CountDevices(); i++)
				{
					const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
					string Name = info->name;
					if (info->input)
					{
						AppendMenu(hMenu, MF_BYPOSITION | MF_STRING | MF_CHECKED, 10 + i, Name.c_str());
					}
				}
			}

			{
				HMENU hMenu = CreatePopupMenu();
				AppendMenu(hPopupMenu, MF_POPUP, (UINT)hMenu, "&MIDI Output");
				for (int i = 0; i < Pm_CountDevices(); i++)
				{
					const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
					string Name = info->name;
					if (info->output)
					{
						AppendMenu(hMenu, MF_BYPOSITION | MF_STRING, 10 + i, Name.c_str());
					}
				}

				AppendMenu(hPopupMenu, MF_BYPOSITION | MF_STRING, CLEAR_NOTES_ID, "Clear Notes");
			}

			SetForegroundWindow(hWnd);
			TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, vPos.x + Rect.left, vPos.y + Rect.top + 40, 0, hWnd, NULL);
		}
	}
}

void CWorkspace::MouseUpCallback(EMouseButton eButton, VECTOR vPos)
{
	MovingWindow = nullptr;
}

void CWorkspace::MouseMoveCallback(VECTOR vPos)
{
	if (MovingWindow)
	{
		MovingWindow->Location += (vPos - MovingStart);
		MovingStart = vPos;
	}
}

void CWorkspace::MenuSelected(INT nMenuId)
{
	if (nMenuId == CLEAR_NOTES_ID)
	{
		MidiController->ClearAll();
	}

	if (nMenuId == ID_MIDI_CLEAR_ALL)
	{
		for (std::vector<CWindow*>::iterator it = Windows.begin(); it != Windows.end(); ++it)
		{
			(*it)->ClearAll();
		}
		MidiOutput->ClearAll();
	}
	
	if (nMenuId == ID_ADDOBJECT_GUITAR)
	{
		Windows.push_back(new CFretboard(this, VECTOR(50.0f, 100.0f), Tunings[0]));
	}

	if (nMenuId >= TUNING_MENU_ID && nMenuId < TUNING_MENU_ID + Tunings.size())
	{
		int Index = nMenuId - TUNING_MENU_ID;
		((CFretboard*)SelectedWindow)->SetTuning(Tunings[Index]);
	}
}

void CWorkspace::KeyDownCallback(int nKey)
{
	switch (nKey)
	{
		case EKbKey_SHIFT:
			bShiftDown = true;
		break;
		case EKbKey_LEFT:
			MidiController->PreviousSet();
		break;
		case EKbKey_RIGHT:
			MidiController->NextSet();
		break;
	}
}

void CWorkspace::KeyUpCallback(int nKey)
{
	switch (nKey)
	{
		case EKbKey_SHIFT:
			bShiftDown = false;
		break;
		case EKbKey_LEFT:
		break;
		case EKbKey_RIGHT:
		break;
	}
}
