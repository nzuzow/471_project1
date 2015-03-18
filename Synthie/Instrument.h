#pragma once
#include "AudioNode.h"
#include "Note.h"

class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	CInstrument(double);
	virtual ~CInstrument();
	virtual void SetNote(CNote *note) = 0;
	double Send(int i) { return sends[i]; }
	void SetSend(int i, double v) { sends[i] = v; }

private:
	double sends[NUMEFFECTCHANNELS];
};

