#pragma once
#include "DelayEffect.h"
#include <cmath>

class CFlanging :
	public CDelayEffect
{
public:
	CFlanging();
	virtual ~CFlanging();
	virtual void Process(double *);
};

