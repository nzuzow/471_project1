#include "stdafx.h"
#include "Reverberation.h"


CReverberation::CReverberation()
{
	m_input.resize(88200);
	m_output.resize(88200);
}


CReverberation::~CReverberation()
{
}


// Processing for two channel reverberation effect
void CReverberation::Process(double * frame)
{
	// Start with input
	for (int i = 0; i < 2; i++)
	{
		m_input[(wrloc + i) % 88200] = frame[i];
	}

	// Implement reverb effect for each channel
	for (int i = 0; i < 2; i++)
	{
		frame[i] += 1 * m_input[(wrloc + i + int(88.2 * 100)) % 88200] + 0.5 * m_input[(wrloc + i + int(88.2 * 200)) % 88200]
			+ 0.25 * m_input[(wrloc + i + int(88.2 * 400)) % 88200] + 0.125 * m_input[(wrloc + i + int(88.2 * 800)) % 88200];
		frame[i] /= 2.75;
	}

	// Write to output
	for (int i = 0; i < 2; i++)
	{
		m_output[(wrloc + i) / 88200] = frame[i];
	}

	// Adjust write location
	wrloc += 2;
	wrloc %= 88200;
}