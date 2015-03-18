#pragma once
#include "LongWaveInstrument.h"
#include <vector>

class CLongWaveFactory
{
public:
	CLongWaveFactory();
	~CLongWaveFactory();

	void SetNote(CNote *note);
	CLongWaveInstrument *CreateInstrument();
	bool CLongWaveFactory::LoadFile(const char *filename);

	void SetType(int type){ m_type = type; }
	int SetWaveValue(const WCHAR *name);

private:
	std::vector<std::vector<short>> m_waveContainer;
	std::vector<short> m_wave;
	int m_type;

};

