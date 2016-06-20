#ifndef _FRETNOTE_H_
#define _FRETNOTE_H_

#include "GameEngine.h"
#include "Window.h"
#include "Tuning.h"
#include <vector>

class CFretNote : public CWindow
{
public:
	static const float KeyWidth;
	static const float KeyHeight;

	CFretNote(CWorkspace* InWorkspace, VECTOR InLocation, VECTOR InDimensions, CNote InNote, bool bInDrawDot);
	virtual ~CFretNote() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Render();
	virtual void RenderDot();

	virtual void OnLeftClick(VECTOR vPos);

protected:
	virtual VECTOR GetWindowDimensions();

	CNote Note;
	VECTOR Dimensions;

	bool bDrawDot;
};

#endif