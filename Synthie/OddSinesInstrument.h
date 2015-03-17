#pragma once
#include "Instrument.h"
#include "AR.h"
#include "Notes.h"

class COddSinesInstrument :
	public CInstrument
{
public:
	COddSinesInstrument();
	~COddSinesInstrument();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	void SetDuration(double d) { m_ar.SetDuration(d); }
	void SetFreq(double f) {}

private:
	CAR         m_ar;
	double  m_time;
};

