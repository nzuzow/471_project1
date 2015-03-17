#pragma once
#include "WavePlayer.h"
#include "DrumInstrument.h"
#include <vector>

class CDrumInstrumentFactory
{
public:
	CDrumInstrumentFactory();
	virtual ~CDrumInstrumentFactory();

	void SetNote(CNote *note);
	CDrumInstrument *CreateInstrument();
	bool CDrumInstrumentFactory::LoadFile(const char *filename);

	void SetType(int type){ m_type = type; }
	int SetDrumValue(const WCHAR *name);

private:
	std::vector<std::vector<short>> m_waves;
	int m_type;
	double m_amp;
	double m_freq;
	double m_duration;

};

