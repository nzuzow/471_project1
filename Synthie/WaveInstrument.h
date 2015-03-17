#pragma once
#include "Instrument.h"
class CWaveInstrument :
	public CInstrument
{
public:
	CWaveInstrument();
	virtual ~CWaveInstrument();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	CWavePlayer *GetPlayer() { return &m_wavePlayer; }

private:
	CWavePlayer m_wavePlayer;
};

