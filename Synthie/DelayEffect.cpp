#include "stdafx.h"
#include "DelayEffect.h"


CDelayEffect::CDelayEffect()
{
	// Initialize values
	m_input.resize(QUEUESIZE);
	m_output.resize(QUEUESIZE);
	wrloc = 0;
}


CDelayEffect::~CDelayEffect()
{
}
