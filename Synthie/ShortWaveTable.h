#pragma once
#include "WaveInstrumentFactory.h"
#include "WavePlayer.h"
#include "SineWave.h"
#include "AR.h"

class CShortWaveTable :
	public CInstrument
{
public:
	CShortWaveTable();
	~CShortWaveTable();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);
	CWavePlayer *GetPlayer() { return &m_wavePlayer; }
	void SetDuration(double d) { m_ar.SetDuration(d); }
	void SetFreq(double f) { m_sine.SetFreq(f); }
	void SetAmplitude(double d) { m_sine.SetAmplitude(d); }



private:
	CWavePlayer m_wavePlayer;
	CAR         m_ar;
	double m_duration;
	double m_time;
	CSineWave m_sine;
};



