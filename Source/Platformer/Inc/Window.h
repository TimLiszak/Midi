#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "GameEngine.h"
#include "Tuning.h"
class CWorkspace;

class CWindow
{
public:
	CWindow(CWorkspace* InWorkspace, VECTOR InLocation);
	virtual ~CWindow() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();

	virtual void BeginWindow();
	virtual void EndWindow();

	virtual bool IsInWindow(VECTOR InLocation);

	virtual bool HasTuning() { return false; }
	virtual void SetTuning(CTuning InTuning) {}

	virtual void OnLeftClick(VECTOR vPos) {}

	virtual void ClearAll() {}

	VECTOR Location;
	bool bDrawBackground;

protected:
	virtual VECTOR GetWindowDimensions() = 0;

	CWorkspace* Workspace;
};

#endif