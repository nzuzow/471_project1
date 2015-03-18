#pragma once
#include "Effect.h"
#include "AR.h"
#include "Wrapper.h"

class CNoiseGating :
	public CEffect
{
public:
	CNoiseGating();
	virtual ~CNoiseGating();
	virtual void Process(double *);

private:
	double m_threshold;
	int m_hold;
	int m_window;
	CAR m_ar;
	CWrapper m_wrapper;
};
