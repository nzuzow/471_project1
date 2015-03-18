#include "stdafx.h"
#include "LongWaveFactory.h"
#include "audio/DirSoundSource.h"
#include "Notes.h"
#include <string>
#include <cmath>


CLongWaveFactory::CLongWaveFactory()
{
	//m_waves.clear();
	//m_amp = .5;

	LoadFile("short_audio/bass1.wav");
	LoadFile("short_audio/synthFunky1.wav");
	LoadFile("short_audio/brassGuitarHit4.wav");
	LoadFile("short_audio/bandFluteHit7.wav");
	//LoadFile("beepers02.wav");

	/*for (double time = 0; time<2; time += 1. / 44100.)
	{
		m_wave.push_back(short(3267 * sin(2 * 3.1415 * 1000 * time)));
	}*/
}


CLongWaveFactory::~CLongWaveFactory()
{
}


CLongWaveInstrument *CLongWaveFactory::CreateInstrument()
{
	CLongWaveInstrument *instrument = new CLongWaveInstrument();
	instrument->GetPlayer()->SetSamples(&m_waveContainer[m_type][0], (int)m_waveContainer[m_type].size());

	return instrument;
}
/*CWaveInstrument *CLongWaveFactory::CreateInstrument()
{
	CWaveInstrument *instrument = new CWaveInstrument();
	instrument->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());

	return instrument;
}*/

void CLongWaveFactory::SetNote(CNote *note)
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
		
		if (name == "Wave") {
			SetType(SetWaveValue(value.bstrVal));
		}
		/*if (name == "DrumType")
		{
		SetType(SetDrumValue(value.bstrVal));
		}
		else if (name == "note")
		{
		m_freq = (NoteToFrequency(value.bstrVal));
		}*/

	}
}

bool CLongWaveFactory::LoadFile(const char *filename)
{
	m_wave.clear();

	CDirSoundSource m_file;
	if (!m_file.Open(filename))
	{
		CString msg = L"Unable to open audio file: ";
		msg += filename;
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i<m_file.NumSampleFrames(); i++)
	{
		short frame[2];
		m_file.ReadFrame(frame);
		m_wave.push_back(frame[0]);
	}
	m_file.Close();

	m_waveContainer.push_back(m_wave);
	return true;
}

int CLongWaveFactory::SetWaveValue(const WCHAR *name)
{
	if (std::wstring(name) == L"W1") { 
		return 0; 
	} else if (std::wstring(name) == L"W2") {
		return 1;
	} else if (std::wstring(name) == L"W3") {
		return 2;
	} else if (std::wstring(name) == L"W4") {
		return 3;
	} else if (std::wstring(name) == L"W5") {
		return 4;
	}
}
