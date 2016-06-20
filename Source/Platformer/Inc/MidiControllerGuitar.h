#ifndef _MIDI_CONTROLLER_GUITAR_H_
#define _MIDI_CONTROLLER_GUITAR_H_

#include "GameEngine.h"
#include "Note.h"
#include "Tuning.h"
#include "MidiController.h"
#include "portmidi.h"
#include <set>

class CMidiControllerGuitar : public CMidiController
{
public:
	CMidiControllerGuitar(CWorkspace* InWorkspace, VECTOR InLocation, CTuning InTuning);
	virtual ~CMidiControllerGuitar() {}

	void	Render();

	virtual bool HasTuning() { return true; }
	virtual void SetTuning(CTuning InTuning);

protected:
	virtual void HandleMidiMessage(int status, int data1, int data2);

	CTuning Standard;
	CTuning Tuning;
};

#endif