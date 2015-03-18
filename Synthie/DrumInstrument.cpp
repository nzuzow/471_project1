#include "stdafx.h"
#include "DrumInstrument.h"
#include "DrumInstrumentFactory.h"
#include "Notes.h"
#include "SineWave.h"



CDrumInstrument::CDrumInstrument()
{
	m_drumwave.SetFreq(100);
	m_freq = 300;
	m_amp = .5;
}


CDrumInstrument::~CDrumInstrument()
{
}

void CDrumInstrument::Start()
{
	m_wavePlayer.SetSampleRate(GetSampleRate());
	m_wavePlayer.Start();
	m_time = 0;
}

void CDrumInstrument::SetNote(CNote *note)
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

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			double seconds = value.dblVal * 1 / (m_bpm / 60.0);
			SetDuration(seconds);
		}
	}

}

bool CDrumInstrument::Generate()
{
	bool valid = m_wavePlayer.Generate();


	m_frame[0] = m_wavePlayer.Frame(0);
	m_frame[1] = m_wavePlayer.Frame(1);

	return valid;
	// Update time
	//m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	//return m_time < m_duration;
}

void CDrumInstrument::SetType(int type)
{
	m_type = type;
}