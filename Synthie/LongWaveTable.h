#pragma once
#include "WaveInstrumentFactory.h"
#include <vector>

class CLongWaveTable :
	public CWaveInstrumentFactory
{
public:
	CLongWaveTable();
	~CLongWaveTable();

private:
	std::vector<std::string> m_WaveContainer;
};

