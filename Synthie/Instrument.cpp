#include "stdafx.h"
#include "Instrument.h"


CInstrument::CInstrument()
{
	// Default all effects except dry to 0
	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		if (i == 0)
			sends[i] = 1.;
		else
			sends[i] = 0.;
	}
}

// Constructor to set the beats per minute
CInstrument::CInstrument(double bpm)
{
	m_bpm = bpm;

	// Default all effects except dry to 0
	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		if (i == 0)
			sends[i] = 1.;
		else
			sends[i] = 0.;
	}
}

CInstrument::~CInstrument()
{
}
