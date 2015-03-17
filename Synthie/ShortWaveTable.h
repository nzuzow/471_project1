#pragma once
#include "WaveInstrumentFactory.h"
#include <vector>

class CShortWaveTable :
	public CWaveInstrumentFactory
{
public:
	CShortWaveTable();
	~CShortWaveTable();

private:
	std::vector<std::string> m_WaveContainer;

};

