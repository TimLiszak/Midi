#include "StdAfx.h"
#include "MidiControllerGuitar.h"
#include "MidiOutput.h"
#include "Render2d.h"
#include "Note.h"

CMidiControllerGuitar::CMidiControllerGuitar(CWorkspace* InWorkspace, VECTOR InLocation, CTuning InTuning) : CMidiController(InWorkspace, InLocation), Standard("Standard", 0), Tuning(InTuning)
{
	Standard.AddString(CNote("E", 2));
	Standard.AddString(CNote("A", 2));
	Standard.AddString(CNote("D", 3));
	Standard.AddString(CNote("G", 3));
	Standard.AddString(CNote("B", 3));
	Standard.AddString(CNote("E", 4));
}

void CMidiControllerGuitar::HandleMidiMessage(int status, int data1, int data2)
{
	set<CNote>& NotesHeld = NotesHeldList[CurrentSet];
	CNote note(data1);

	switch (status)
	{
		case 0x90: 
		case 0x91: 
		case 0x92: 
		case 0x93: 
		case 0x94: 
		case 0x95: 
		{
			int String = status - 0x90;

			if (String < Tuning.GetNumStrings())
			{
				int Fret = Standard.GetFret(String, note);

				int num = 1;
				bool dbl = false;
				if (Tuning.GetNumStrings() > 6)
				{
					String = String * 2;
					num = 2;
				}

				for (int i = 0; i < num; i++)
				{
					note = Tuning.GetNote(String + i, Fret);
					Workspace->GetMidiOutput()->HandleMidiMessage(status, note.GetMidiValue(), data2);

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
			}
		}
		break;

		default:
		{
			Workspace->GetMidiOutput()->HandleMidiMessage(status, data1, data2);
		}
		break;
	}
}

void CMidiControllerGuitar::Render()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(6.0f, 12.0f);
	CRender2d::Print("MIDI Controller - Guitar");

	glRasterPos2f(6.0f, 30.0f);
	CRender2d::Print(Tuning.GetText().c_str());
}

void CMidiControllerGuitar::SetTuning(CTuning InTuning)
{
	Tuning = InTuning;
}
