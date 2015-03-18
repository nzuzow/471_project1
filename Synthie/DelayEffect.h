#pragma once
#include "Effect.h"
#include <vector>

#ifndef QUEUESIZE
#define QUEUESIZE 4410
#endif

// Parent class for effects involving delays (ex: chorus, flange, reverb)

class CDelayEffect :
	public CEffect
{
public:
	CDelayEffect();
	virtual ~CDelayEffect();

protected:
	std::vector<double> m_input;	//!< Input queue
	std::vector<double> m_output;	//!< Output queue
	int wrloc;
	double m_phase;
};

