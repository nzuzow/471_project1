#include "stdafx.h"
#include "ShortWaveFactory.h"
#include "audio/DirSoundSource.h"


CShortWaveFactory::CShortWaveFactory()
{
	LoadFile("ShortWaves/357harm.wav");
	LoadFile("ShortWaves/allharm.wav");
	LoadFile("ShortWaves/evenharm.wav");
	LoadFile("ShortWaves/multisine.wav");
	LoadFile("ShortWaves/oddharm.wav");
	
	
}


CShortWaveFactory::~CShortWaveFactory()
{
}

CShortWaveTable *CShortWaveFactory::CreateInstrument()
{

	CShortWaveTable *instrument = new CShortWaveTable();
	/*instrument->SetAmp(m_amp);
	instrument->SetType(m_type);
	instrument->SetFreq(m_freq);*/
	instrument->GetPlayer()->SetSamples(&m_waves[m_type][0], (int)m_waves[m_type].size());
	//instrument->GetPlayer()->SetSamples(&m_waves[0], (int)m_wave.size());

	return instrument;
}

void CShortWaveFactory::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "WaveIdx")
		{
			SetType(SetWaveIdx(value.bstrVal));
		}

	}
}

bool CShortWaveFactory::LoadFile(const char *filename)
{
	std::vector<short> m_wave;

	CDirSoundSource m_file;
	if (!m_file.Open(filename))
	{
		CString msg = L"Unable to open audio file: ";
		msg = +filename;
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i < m_file.NumSampleFrames(); i++)
	{
		short frame[2];
		m_file.ReadFrame(frame);
		m_wave.push_back(frame[0]);

	}

	m_file.Close();
	m_waves.push_back(m_wave);
	return true;
}

int CShortWaveFactory::SetWaveIdx(const WCHAR *name)
{

	if (std::wstring(name) == L"357harm"){ return 0; }
	else if (std::wstring(name) == L"allharm"){ return 1; }
	else if (std::wstring(name) == L"evenharm"){ return 2; }
	else if (std::wstring(name) == L"multisine"){ return 3; }
	else if (std::wstring(name) == L"oddharm"){ return 4; }
}