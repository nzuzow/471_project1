#include "stdafx.h"
#include "WaveInstrumentFactory.h"
#include <cmath>


CWaveInstrumentFactory::CWaveInstrumentFactory()
{
	for (double time = 0; time<2; time += 1. / 44100.)
	{
		m_wave.push_back(short(3267 * sin(2 * 3.1415 * 1000 * time)));
	}
}


CWaveInstrumentFactory::~CWaveInstrumentFactory()
{
}

CWaveInstrument *CWaveInstrumentFactory::CreateInstrument()
{
	CWaveInstrument *instrument = new CWaveInstrument();
	instrument->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());

	return instrument;
}

void CWaveInstrumentFactory::SetNote(CNote *note)
{
}