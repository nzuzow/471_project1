#pragma once
#include "ShortWaveTable.h"
class CShortWaveFactory
{
public:
	CShortWaveFactory();
	~CShortWaveFactory();

	void SetNote(CNote *note);
	CShortWaveTable *CreateInstrument();
	bool CShortWaveFactory::LoadFile(const char *filename);
	int SetWaveIdx(const WCHAR *name);
	void SetType(int type){ m_type = type; }
private:
	std::vector<std::vector<short>> m_waves;
	int m_type;
	//std::vector<short> m_wave;
};

