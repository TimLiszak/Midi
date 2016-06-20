#ifndef _FRETBOARD_H_
#define _FRETBOARD_H_

#include "GameEngine.h"
#include "Window.h"
#include "Tuning.h"
#include "FretNote.h"
#include <vector>

class CFretboard : public CWindow
{
public:
	CFretboard(CWorkspace* InWorkspace, VECTOR InLocation, CTuning InTuning);
	virtual ~CFretboard() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();

	virtual bool HasTuning() { return true; }
	virtual void SetTuning(CTuning InTuning);

	virtual void OnLeftClick(VECTOR vPos);

protected:
	virtual VECTOR GetWindowDimensions();
	virtual void Init();

	CTuning Tuning;
	std::vector<float> FretScale;

	std::vector<class CFretNote*> FretNotes;
};

#endif