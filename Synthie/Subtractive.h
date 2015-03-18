#pragma once
#include "Instrument.h"
#include "WavePlayer.h"
#include "SineWave.h"

class CSubtractive :
	public CInstrument
{
public:
	CSubtractive();
	virtual ~CSubtractive();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);
	void SetDuration(double dur) { m_duration = dur; }
	CWavePlayer *GetPlayer() { return &m_wavePlayer; }
	void SetType(int type) { m_type = type; }

private:
	CWavePlayer m_wavePlayer;
	int m_type;

	double m_duration;
	CSineWave m_sub;

};

