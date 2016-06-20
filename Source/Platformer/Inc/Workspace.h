#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_

#include "GameEngine.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Tuning.h"
#include <vector>

class CWorkspace : public CGameMode, IMouseCallback, IKeyboardCallback, CMenuCallback
{
public:
	void	Init();
	void	Update(const FLOAT DeltaTime);
	void	Term();
	void	Render();

	class CMidiController* GetMidiController();
	class CMidiOutput* GetMidiOutput();

	virtual void	MouseDownCallback(EMouseButton eButton, VECTOR vPos);
	virtual void	MouseUpCallback(EMouseButton eButton, VECTOR vPos);
	virtual void	MouseMoveCallback(VECTOR vPos);
	virtual void	MenuSelected(INT nMenuId);

	virtual void	KeyDownCallback(int nKey);
	virtual void	KeyUpCallback(int nKey);

private:
	void AddTuning(string Name, int Category, CNote Note1, CNote Note2, CNote Note3, CNote Note4, CNote Note5, CNote Note6);
	void AddTuning(string Name, int Category, CNote Note1, CNote Note2, CNote Note3, CNote Note4);

	class CMidiController* MidiController;
	class CMidiOutput* MidiOutput;

	std::vector<CTuning> Tunings;
	std::vector<class CWindow*> Windows;

	CWindow* SelectedWindow;
	CWindow* MovingWindow;
	VECTOR MovingStart;

	bool bShiftDown;
};

#endif