#ifndef _PIANO_H_
#define _PIANO_H_

#include "GameEngine.h"
#include "Window.h"
#include "Tuning.h"
#include "PianoKey.h"
#include <vector>

class CPiano : public CWindow
{
public:
	CPiano(CWorkspace* InWorkspace, VECTOR InLocation);
	virtual ~CPiano() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();

	virtual void OnLeftClick(VECTOR vPos);

protected:
	virtual VECTOR GetWindowDimensions();

	std::vector<class CPianoKey*> PianoKeys;
};

#endif