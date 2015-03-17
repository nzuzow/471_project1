#pragma once
class CWaveInstrumentFactory
{
public:
	CWaveInstrumentFactory();
	~CWaveInstrumentFactory();

	void SetNote(CNote *note);
	CWaveInstrument *CreateInstrument();

private:
	std::vector<short> m_wave;
};

