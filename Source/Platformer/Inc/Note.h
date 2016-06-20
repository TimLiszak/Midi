#ifndef _NOTE_H_
#define _NOTE_H_

#include "GameEngine.h"
#include <string>
using namespace std;

class CNote
{
public:
	CNote(int InMidiValue) : MidiValue(InMidiValue) {}
	CNote(string Note, int Octave);
	virtual ~CNote() {}

	string GetString(bool bIncludeOctave = false) const;
	int GetMidiValue() const;

	inline CNote operator+(const int& HalfSteps) const
	{
		CNote Result(this->MidiValue + HalfSteps);
		return Result;
	}

	inline int operator-(const CNote& Note) const
	{
		return this->MidiValue - Note.MidiValue;
	}

	inline bool operator==(const CNote& Note) const
	{
		return this->MidiValue == Note.MidiValue;
	}

	inline bool operator<(const CNote& Note) const
	{
		return this->MidiValue < Note.MidiValue;
	}

protected:
	int MidiValue;
};

#endif