#pragma once
#include "WaveInstrument.h"
#include <vector>

class CWaveInstrumentFactory
{
public:
	CWaveInstrumentFactory();
	~CWaveInstrumentFactory();

	void SetNote(CNote *note);
	CWaveInstrument *CreateInstrument();
	bool CWaveInstrumentFactory::LoadFile(const char *filename);

private:
	std::vector<short> m_wave;
};

