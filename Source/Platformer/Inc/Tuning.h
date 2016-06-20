#ifndef _TUNING_H_
#define _TUNING_H_

#include "GameEngine.h"
#include "Note.h"
#include <vector>
#include <string>
using namespace std;

class CTuning
{
public:
	CTuning(string InName, int InCategory) : Name(InName), Category(InCategory) {}
	virtual ~CTuning() {}

	void AddString(CNote OpenNote);

	string GetText();
	CNote GetNote(int String, int Fret);
	int GetFret(int String, CNote Note);
	int GetNumStrings() const;
	int GetCategory() const;

protected:
	string Name;
	vector<CNote> Strings;
	int Category;
};

#endif
