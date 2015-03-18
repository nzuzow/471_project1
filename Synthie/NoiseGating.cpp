#include "stdafx.h"
#include "NoiseGating.h"


CNoiseGating::CNoiseGating()
{
	// Initialize attack & release
	m_ar.SetSource(&m_wrapper);
	m_ar.Start();

	m_threshold = 0.05;
	m_hold = 441;
	m_window = 0;
}


CNoiseGating::~CNoiseGating()
{
}

// Processing for two channel noise gating effect
void CNoiseGating::Process(double * frame)
{
	// Gating process
	for (int i = 0; i < 2; i++)
	{
		if (frame[i] > 0. && frame[i] < m_threshold)
		{
			m_window++;
			if (m_window > m_hold)
				frame[i] = 0;
		}
		else if (frame[i] < 0. && frame[i] > (-1. * m_threshold))
		{
			if (m_window > m_hold)
				frame[i] = 0.;
		}
		else
		{
			m_window = 0;
		}
	}

	// Set wrapper with now modified frame
	m_wrapper.Set(frame);

	// Generate attack and release on wrapper & edit frame accordingly
	if (m_ar.Generate())
	{
		frame[0] = m_ar.Frame()[0];
		frame[1] = m_ar.Frame()[1];
	}
}