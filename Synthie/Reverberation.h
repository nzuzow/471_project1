#pragma once
#include "DelayEffect.h"
class CReverberation :
	public CDelayEffect
{
public:
	CReverberation();
	virtual ~CReverberation();
	virtual void Process(double *);
};
