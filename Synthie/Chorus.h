#pragma once
#include "DelayEffect.h"
#include <cmath>


// Implementation of chorus effect (borrows from Exam Question B1 solution)
class CChorus :
	public CDelayEffect
{
public:
	CChorus();
	virtual ~CChorus();
	virtual void Process(double *);
};
