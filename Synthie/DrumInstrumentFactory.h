#pragma once
#include "WavePlayer.h"
#include "DrumInstrument.h"
#include <vector>

class CNote;

enum DrumStates{Snare1,Snare2,Snare3,Snare4,Beeper1,Beeper2,Hit1,Hit2,Hit3,HiHat1,HiHat2,HiHat3,HiHat4,HiHat5,
				HiHat6,HiHat7, Tom1,Tom2, Skin1,Skin2,Skin3};



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

