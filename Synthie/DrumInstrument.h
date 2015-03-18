#pragma once
#include "Instrument.h"
#include "WavePlayer.h"
#include "SineWave.h"


class CDrumInstrument :
	public CInstrument
{
public:
	CDrumInstrument();
	virtual ~CDrumInstrument();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);
	void SetDuration(double dur) { m_duration = dur; }
	void SetFreq(double freq) { m_freq = freq; }
	void SetAmp(double amplitude){ m_amp = amplitude; }
	CWavePlayer *GetPlayer() { return &m_wavePlayer; }

	void SetType(int type);



private:
	CWavePlayer m_wavePlayer;
	int m_type;

	double m_duration;
	double m_freq;
	double m_amp;
	double m_time;
	CSineWave m_drumwave;
};

