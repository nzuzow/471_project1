#pragma once
class CEffect
{
public:
	CEffect();
	virtual ~CEffect();
	void ProcessStart(double *);
	void SetWet(double w) { m_wet = w; }
	void SetDry(double d) { m_dry = d; }
	double GetWet() { return m_wet; }
	double GetDry() { return m_dry; }

private:
	double m_wet;	//!< Amount of "dry" input to keep
	double m_dry;	//!< Amount of "wet" output to provide
	virtual void Process(double *) = 0;
};
