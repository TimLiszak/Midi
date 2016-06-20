#ifndef _MIDI_OUTPUT_H_
#define _MIDI_OUTPUT_H_

#include "GameEngine.h"
#include "Note.h"
#include "portmidi.h"
#include <set>

class CMidiOutput
{
public:
	CMidiOutput();
	virtual ~CMidiOutput() {}

	void	Update(const FLOAT DeltaTime);
	void	Render();
	void	HandleMidiMessage(int status, int data1, int data2);

	virtual void ClearAll();

protected:

	enum EState
	{
		EState_Initialize,
		EState_Write,
		EState_MAX
	};

	EState State;
	PmStream * midi;
};

#endif