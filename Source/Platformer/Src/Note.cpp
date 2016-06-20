#include "StdAfx.h"
#include "Note.h"

CNote::CNote(string Note, int Octave)
{
	int Value = 0;
	if (Note == "C")
		Value = 0;
	else if (Note == "C#" || Note == "Db")
		Value = 1;
	else if (Note == "D")
		Value = 2;
	else if (Note == "D#" || Note == "Eb")
		Value = 3;
	else if (Note == "E")
		Value = 4;
	else if (Note == "F")
		Value = 5;
	else if (Note == "F#" || Note == "Gb")
		Value = 6;
	else if (Note == "G")
		Value = 7;
	else if (Note == "G#" || Note == "Ab")
		Value = 8;
	else if (Note == "A")
		Value = 9;
	else if (Note == "A#" || Note == "Bb")
		Value = 10;
	else if (Note == "B")
		Value = 11;

	MidiValue = Value + (Octave + 1) * 12;
}

string CNote::GetString(bool bIncludeOctave) const
{
	string Str;
	switch (MidiValue % 12)
	{
	case 0:
		Str += "C";
		break;
	case 1:
		Str += "C#";
		break;
	case 2:
		Str += "D";
		break;
	case 3:
		Str += "D#";
		break;
	case 4:
		Str += "E";
		break;
	case 5:
		Str += "F";
		break;
	case 6:
		Str += "F#";
		break;
	case 7:
		Str += "G";
		break;
	case 8:
		Str += "G#";
		break;
	case 9:
		Str += "A";
		break;
	case 10:
		Str += "A#";
		break;
	default:
		Str += "B";
		break;
	}

	if (bIncludeOctave)
	{
		Str += std::to_string(MidiValue / 12 - 1);
	}
	return Str;
}

int CNote::GetMidiValue() const
{
	return MidiValue;
}
