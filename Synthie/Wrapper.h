#pragma once
#include "AudioNode.h"
class CWrapper :
	public CAudioNode
{
public:
	CWrapper();
	virtual ~CWrapper();

	virtual void Start() { ; };
	virtual bool Generate() { return true; }
	void Set(double *);
};
