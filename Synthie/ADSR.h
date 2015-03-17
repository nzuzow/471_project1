#pragma once
#pragma once
#include "AudioNode.h"
class CADSR :
	public CAudioNode
{
public:
	CADSR();
	~CADSR();
private:
	double m_duration;
	double m_time;
	double m_attack;
	double m_decay;
	double m_sustain;
	double m_release;
	int pushtest;
	CAudioNode* m_source;
public:
	void SetSource(CAudioNode* const &source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	void SetAttack(double a) { m_attack = a; }
	void SetRelease(double r) { m_release = r; }
	virtual void Start();
	virtual bool Generate();
};

