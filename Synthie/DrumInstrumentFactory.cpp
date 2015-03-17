#include "stdafx.h"
#include "DrumInstrumentFactory.h"
#include "audio/DirSoundSource.h"
#include "Notes.h"
#include <string>
#include <cmath>

CDrumInstrumentFactory::CDrumInstrumentFactory()
{
	m_waves.clear();
	m_amp = .5;

	LoadFile("dirty_snare01.wav");
	LoadFile("dirty_snare02.wav");
	LoadFile("dirty_snare03.wav");
	LoadFile("beepers01.wav");
	LoadFile("beepers02.wav");
	LoadFile("perturbed_hit01.wav");
	LoadFile("perturbed_hit02.wav");
	LoadFile("perturbed_hit03.wav");
	LoadFile("step_snare.wav");
	LoadFile("alien_hihats_01.wav");
	LoadFile("alien_hihats_02.wav");
	LoadFile("alien_hihats_03.wav");
	LoadFile("alien_hihats_04.wav");
	LoadFile("alien_hihats_05.wav");
	LoadFile("alien_hihats_06.wav");
	LoadFile("alien_hihats_07.wav");
	LoadFile("V10_loose_skin.wav");
	LoadFile("V28_loose_skin.wav");
	LoadFile("V55_loose_skin.wav");
	LoadFile("V_08Floor_tom.wav");
	LoadFile("V_04Floor_tom.wav");

	/*
	for (double time = 0; time < 2; time += 1. / 44100.)
	{
	m_wave.push_back(short(3267 * sin(2 * 3.1415 * 1000 * time)));
	}
	*/
}


CDrumInstrumentFactory::~CDrumInstrumentFactory()
{
}

CDrumInstrument *CDrumInstrumentFactory::CreateInstrument()
{
	CDrumInstrument *instrument = new CDrumInstrument();
	instrument->GetPlayer()->SetSamples(&m_waves[m_type][0], (int)m_waves[m_type].size());

	return instrument;
}

void CDrumInstrumentFactory::SetNote(CNote *note)
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

		if (name == "DrumType")
		{
			SetType(SetDrumValue(value.bstrVal));
		}
		else if (name == "note")
		{
			m_freq = (NoteToFrequency(value.bstrVal));
		}

	}
}

bool CDrumInstrumentFactory::LoadFile(const char *filename)
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

int CDrumInstrumentFactory::SetDrumValue(const WCHAR *name)
{
	/*
	LoadFile("dirty_snare01.wav");
	LoadFile("dirty_snare02.wav");
	LoadFile("dirty_snare03.wav");
	LoadFile("beepers01.wav");
	LoadFile("beepers02.wav");
	LoadFile("perturbed_hit01.wav");
	LoadFile("perturbed_hit02.wav");
	LoadFile("perturbed_hit03.wav");
	LoadFile("step_snare.wav");
	LoadFile("alien_hihats_01.wav");
	LoadFile("alien_hihats_02.wav");
	LoadFile("alien_hihats_03.wav");
	LoadFile("alien_hihats_04.wav");
	LoadFile("alien_hihats_05.wav");
	LoadFile("alien_hihats_06.wav");
	LoadFile("alien_hihats_07.wav");
	LoadFile("V10_loose_skin.wav");
	LoadFile("V28_loose_skin.wav");
	LoadFile("V55_loose_skin.wav");
	LoadFile("V_08Floor_tom.wav");
	LoadFile("V_04Floor_tom.wav");
	*/
	if (std::wstring(name) == L"Snare1"){ return 0; }
	else if (std::wstring(name) == L"Snare2"){ return 1; }
	else if (std::wstring(name) == L"Snare3"){ return 2; }
	else if (std::wstring(name) == L"Snare4"){ return 3; }
	else if (std::wstring(name) == L"Beeper1"){ return 4; }
	else if (std::wstring(name) == L"Beeper2"){ return 5; }
	else if (std::wstring(name) == L"Hit1"){ return 6; }
	else if (std::wstring(name) == L"Hit2"){ return 7; }
	else if (std::wstring(name) == L"Hit3"){ return 8; }
	else if (std::wstring(name) == L"HiHat1"){ return 9; }
	else if (std::wstring(name) == L"HiHat2"){ return 10; }
	else if (std::wstring(name) == L"HiHat3"){ return 11; }
	else if (std::wstring(name) == L"HiHat4"){ return 12; }
	else if (std::wstring(name) == L"HiHat5"){ return 13; }
	else if (std::wstring(name) == L"HiHat6"){ return 14; }
	else if (std::wstring(name) == L"HiHat7"){ return 15; }
	else if (std::wstring(name) == L"Tom1"){ return 16; }
	else if (std::wstring(name) == L"Tom2"){ return 17; }
	else if (std::wstring(name) == L"Skin1"){ return 18; }
	else if (std::wstring(name) == L"Skin2"){ return 19; }
	else if (std::wstring(name) == L"Skin3"){ return 20; }
}