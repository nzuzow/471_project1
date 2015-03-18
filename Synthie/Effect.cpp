#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect()
{
	// Default to 100% wet output
	m_wet = 1.0;
	m_dry = 0.0;
}


CEffect::~CEffect()
{
}


void CEffect::ProcessStart(double * frame)
{
	// Initialize dry & wet frames
	double * dframe = new double[2];
	dframe[0] = frame[0];
	dframe[1] = frame[1];
	double * wframe = new double[2];
	wframe[0] = frame[0];
	wframe[1] = frame[1];

	// Process the wet frame to add the effect
	Process(wframe);

	// Set final frame value according to dry & wet amounts
	frame[0] = m_dry * dframe[0] + m_wet * wframe[0];
	frame[1] = m_dry * dframe[1] + m_wet * wframe[1];

	// Clean up
	delete dframe;
	delete wframe;
}
