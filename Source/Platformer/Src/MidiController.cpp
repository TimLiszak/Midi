#include "StdAfx.h"
#include "MidiController.h"
#include "MidiOutput.h"
#include "Render2d.h"
#include "Note.h"

#include "portmidi.h"
#include "porttime.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

#define INPUT_BUFFER_SIZE 100
#define DRIVER_INFO NULL
#define TIME_PROC ((int32_t (*)(void *)) Pt_Time)
#define TIME_INFO NULL

CMidiController::CMidiController(CWorkspace* InWorkspace, VECTOR InLocation) : CWindow(InWorkspace, InLocation)
{
	State = EState_Initialize;
	CurrentSet = 0;
	NotesHeldList.resize(5);
}

void CMidiController::Update(const FLOAT DeltaTime)
{
	PmEvent buffer[1];
	PmError status;
	int length;

	switch (State)
	{
		case EState_Initialize:
		{
			int default_in = -1;
			for (int i = 0; i < Pm_CountDevices(); i++) 
			{
				char *deflt;
				const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
				string Name = info->name;
				if (info->input && Name.find("iConnect") != std::string::npos)
				{
					default_in = i;
				}
			}

			if (default_in >= 0)
			{
				/* open input device */
				Pm_OpenInput(&midi,
					default_in,
					DRIVER_INFO,
					INPUT_BUFFER_SIZE,
					TIME_PROC,
					TIME_INFO);

				Pm_SetFilter(midi, PM_FILT_ACTIVE | PM_FILT_CLOCK | PM_FILT_SYSEX);
				Pm_SetChannelMask(midi, Pm_Channel(0) | Pm_Channel(1) | Pm_Channel(2) | Pm_Channel(3) | Pm_Channel(4) | Pm_Channel(5));

				/* empty the buffer after setting filter, just in case anything
				got through */
				while (Pm_Poll(midi)) {
					Pm_Read(midi, buffer, 1);
				}

				State = EState_Read;

			}
		}
		break;

		case EState_Read:
		{
			status = Pm_Poll(midi);
			while (status == TRUE) 
			{
				length = Pm_Read(midi, buffer, 1);
				if (length > 0) 
				{
					int status = Pm_MessageStatus(buffer[0].message);
					int data1 = Pm_MessageData1(buffer[0].message);
					int data2 = Pm_MessageData2(buffer[0].message);
					HandleMidiMessage(status, data1, data2);
				}
				else 
				{
					assert(0);
				}
				status = Pm_Poll(midi);
			}
		}
		break;
	}
}

void CMidiController::Render()
{
	set<CNote>& NotesHeld = NotesHeldList[CurrentSet];
	GetGameEngine()->GetDebugPrint()->ChangeColour(COLOUR_RGB(0.0f, 0.0f, 0.0f));
	for (std::set<CNote>::iterator it = NotesHeld.begin(); it != NotesHeld.end(); ++it)
	{
		GetGameEngine()->GetDebugPrint()->Printf("%s   (%d)", (*it).GetString(true).c_str(), (*it).GetMidiValue());
	}
}

bool CMidiController::IsNoteOn(CNote Note) const
{
	const set<CNote>& NotesHeld = NotesHeldList[CurrentSet];
	return NotesHeld.find(Note) != NotesHeld.end();
}

void CMidiController::HandleMidiMessage(int status, int data1, int data2)
{
	set<CNote>& NotesHeld = NotesHeldList[CurrentSet];
	CNote note(data1);

	switch (status)
	{
		case 0x90: // Key press
		case 0x91: // Key press
		case 0x92: // Key press
		case 0x93: // Key press
		case 0x94: // Key press
		case 0x95: // Key press
		{
			if (data2 == 0)
			{
				if (NotesHeld.find(note) != NotesHeld.end())
				{
					NotesHeld.erase(NotesHeld.find(note));
				}
			}
			else
			{
				NotesHeld.insert(note);
			}
		}
		break;
		case 0x80: // Key up
		{
			if (NotesHeld.find(note) != NotesHeld.end())
			{
				NotesHeld.erase(NotesHeld.find(note));
			}
		}
		break;
	}

	Workspace->GetMidiOutput()->HandleMidiMessage(status, data1, data2);
}

VECTOR CMidiController::GetWindowDimensions()
{
	return VECTOR(300.0f, 50.0f);
}

void CMidiController::ClearAll()
{
	NotesHeldList.clear();
	NotesHeldList.resize(5);
	CurrentSet = 0;
}

void CMidiController::ToggleNote(CNote note)
{
	set<CNote>& NotesHeld = NotesHeldList[CurrentSet];
	if (!IsNoteOn(note))
	{
		NotesHeld.insert(note);
	}
	else
	{
		NotesHeld.erase(NotesHeld.find(note));
	}
}

void CMidiController::NextSet()
{
	CurrentSet++;
	if (CurrentSet >= NotesHeldList.size())
	{
		NotesHeldList.resize(NotesHeldList.size() * 2);
	}
}

void CMidiController::PreviousSet()
{
	CurrentSet--;
	if (CurrentSet < 0)
	{
		CurrentSet = 0;
	}
}
