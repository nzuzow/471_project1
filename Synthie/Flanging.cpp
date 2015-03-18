#include "stdafx.h"
#include "Flanging.h"


CFlanging::CFlanging()
{
	m_phase = 0.;
}


CFlanging::~CFlanging()
{
}

// Processing for two channel flanging effect
void CFlanging::Process(double * frame)
{
	// Start with input
	for (int i = 0; i < 2; i++)
	{
		m_input[(wrloc + i) % 2] = frame[i];
	}

	// Calculate delays and adjust phase
	int delaysize1 = int(88.2 * (6 + 4 * sin(m_phase)));
	int delaysize2 = int(88.2 * (10 + 8 * cos(m_phase)));
	m_phase += 2 * PI * 1 / 44100.;

	// Factor in appropriate delays
	for (int i = 0; i < 2; i++)
	{
		frame[i] += m_input[(wrloc + i + delaysize1) % QUEUESIZE] * (0.75 + 0.25 * sin(m_phase * 2));
		frame[i] += m_input[(wrloc + i + delaysize2) % QUEUESIZE] * (0.75 + 0.25 * sin(2 * m_phase * 2));
		frame[i] /= 3;
	}

	// Write to output
	for (int i = 0; i < 2; i++)
	{
		m_output[(wrloc + i) / QUEUESIZE] = frame[i];
	}

	// Adjust write location
	wrloc += 2;
	wrloc %= QUEUESIZE;
}