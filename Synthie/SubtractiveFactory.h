#pragma once
#include "WavePlayer.h"
#include "Subtractive.h"
#include <vector>

class CNote;

class CSubtractiveFactory
{
public:
	CSubtractiveFactory();
	virtual ~CSubtractiveFactory();

	CSubtractive *CreateInstrument();
	void SetNote(CNote *note);
	bool LoadFile(const char *filename);
	int SetSubType(const WCHAR *name);
	void SetType(int num) { m_type = num; }

private:
	std::vector<std::vector<short>> m_waves;
	int  m_type;

};

