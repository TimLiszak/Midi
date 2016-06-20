#include "StdAfx.h"
#include "Tuning.h"

void CTuning::AddString(CNote OpenNote)
{
	Strings.insert(Strings.begin(), OpenNote);
}

CNote CTuning::GetNote(int String, int Fret)
{
	return Strings[String] + Fret;
}

int CTuning::GetNumStrings() const
{
	return Strings.size();
}

int CTuning::GetFret(int String, CNote Note)
{
	return Note - Strings[String];
}

string CTuning::GetText()
{
	string Text = Name + " - ";
	for (int i = Strings.size() - 1; i >= 0; i--)
	{
		Text += Strings[i].GetString() + " ";
	}

	return Text;
}
int CTuning::GetCategory() const
{
	return Category;
}
