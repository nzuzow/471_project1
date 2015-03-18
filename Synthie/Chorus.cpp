#include "stdafx.h"
#include "Chorus.h"


CChorus::CChorus()
{
	m_phase = 0.;
}


CChorus::~CChorus()
{
}

// Processing for two channel chorus effect
void CChorus::Process(double * frame)
{
	// Start with input
	for (int i = 0; i < 2; i++)
	{
		m_input[(wrloc + i) % QUEUESIZE] = frame[i];
	}

	// Calculate appropriate delay & adjust phase
	int delaysize = int(88.2 * (25 + 2 * sin(m_phase)));
	m_phase += 2 * PI * 2 / 44100.;

	// Factor in delay
	for (int i = 0; i < 2; i++)
	{
		frame[i] += m_input[(wrloc + i + delaysize) % QUEUESIZE];
		frame[i] /= 2.;
	}

	// Write to output queue
	for (int i = 0; i < 2; i++)
	{
		m_output[(wrloc + i) / QUEUESIZE] = frame[i];
	}

	// Adjust write location
	wrloc += 2;
	wrloc %= QUEUESIZE;
}