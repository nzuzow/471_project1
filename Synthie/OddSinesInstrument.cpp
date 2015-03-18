#include "stdafx.h"
#include "OddSinesInstrument.h"
#include "Notes.h"


COddSinesInstrument::COddSinesInstrument()
{
}


COddSinesInstrument::~COddSinesInstrument()
{
}

void COddSinesInstrument::Start()
{
	m_sines.SetSampleRate(GetSampleRate());
	m_sines.Start();
	m_ar.SetSource(&m_sines);

	m_ar.SetSampleRate(GetSampleRate());
	m_ar.Start();
	m_time = 0;
}


void COddSinesInstrument::SetNote(CNote *note)
{
}


bool COddSinesInstrument::Generate()
{
	m_sines.Generate();
	
	bool valid = m_ar.Generate();

	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

	m_time += GetSamplePeriod();
	return valid;
}
