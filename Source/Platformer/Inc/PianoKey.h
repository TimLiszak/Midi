#ifndef _PIANOKEY_H_
#define _PIANOKEY_H_

#include "GameEngine.h"
#include "Window.h"
#include "Tuning.h"
#include <vector>

class CPianoKey : public CWindow
{
public:
	static const float KeyWidth;
	static const float KeyHeight;

	CPianoKey(CWorkspace* InWorkspace, VECTOR InLocation, CNote InNote, bool bInBlackKey);
	virtual ~CPianoKey() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();

	virtual void OnLeftClick(VECTOR vPos);

protected:
	virtual VECTOR GetWindowDimensions();

	CNote Note;
	bool bBlackKey;
};

#endif