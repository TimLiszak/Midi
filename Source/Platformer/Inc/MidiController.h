#ifndef _MIDI_CONTROLLER_H_
#define _MIDI_CONTROLLER_H_

#include "GameEngine.h"
#include "Note.h"
#include "Workspace.h"
#include "Window.h"
#include "portmidi.h"
#include <set>
#include <vector>
using namespace std;

class CMidiController : public CWindow
{
public:
	CMidiController(CWorkspace* InWorkspace, VECTOR InLocation);
	virtual ~CMidiController() {}

	void	Update(const FLOAT DeltaTime);
	void	Render();
	bool	IsNoteOn(CNote Note) const;

	void	ToggleNote(CNote Note);

	virtual void ClearAll();

	virtual void NextSet();
	virtual void PreviousSet();

protected:
	virtual void HandleMidiMessage(int status, int data1, int data2);
	virtual VECTOR GetWindowDimensions();

	vector< set<CNote> > NotesHeldList;
	int CurrentSet;

	enum EState
	{
		EState_Initialize,
		EState_Read,
		EState_MAX
	};

	EState State;
	PmStream * midi;
};

#endif