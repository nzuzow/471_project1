#include "stdafx.h"
#include "Synthesizer.h"
#include "Instrument.h"
#include "ToneInstrument.h"
#include "OddSinesInstrument.h"
#include "xmlhelp.h"
#include <vector>
#include <algorithm>
#include "Flanging.h"
#include "Chorus.h"
#include "Reverberation.h"
#include "NoiseGating.h"

CSynthesizer::CSynthesizer()
: m_time(0)
{
	CoInitialize(NULL);
	m_channels = 2;
	m_sampleRate = 44100.;
	m_samplePeriod = 1 / m_sampleRate;
	m_bpm = 120;            
	m_beatspermeasure = 4;
	m_secperbeat = 0.5;     

	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		m_effects[i] = NULL;
	}

	m_waveinstfactory.LoadFile("drumriff.wav");
}


CSynthesizer::~CSynthesizer()
{
	Clear();
}


//! Start the synthesizer
void CSynthesizer::Start()
{
	/*m_time = 0;
	CToneInstrument *ti = new CToneInstrument();
	ti->SetSampleRate(GetSampleRate());
	ti->SetFreq(440);
	ti->SetDuration(3);
	ti->Start();
	m_instruments.push_back(ti);*/
	m_instruments.clear();
	m_currentNote = 0;
	m_measure = 0;
	m_beat = 0;
	m_time = 0;
	m_effectfactory.Start();
}


bool CSynthesizer::Generate(double * frame)
{
	//
	// Phase 1: Determine if any notes need to be played.
	//

	while (m_currentNote < (int)m_notes.size())
	{
		// Get a pointer to the current note
		CNote *note = &m_notes[m_currentNote];

		// If the measure is in the future we can't play
		// this note just yet.
		if (note->Measure() > m_measure)
			break;

		// If this is the current measure, but the
		// beat has not been reached, we can't play
		// this note.
		if (note->Measure() == m_measure && note->Beat() > m_beat)
			break;

		//
		// Play the note!
		//

		// Create the instrument object
		CInstrument *instrument = NULL;
		if (note->Instrument() == L"ToneInstrument")
		{
			instrument = new CToneInstrument(GetBeatsPerMinute());
		}
		else if (note->Instrument() == L"OddSines")
		{
			m_oddsinesfactory.SetNote(note);
			instrument = m_oddsinesfactory.CreateInstrument();
		}
		else if (note->Instrument() == L"Wave")
		{
			m_waveinstfactory.SetNote(note);
			instrument = m_waveinstfactory.CreateInstrument();
		}
		
		else if (note->Instrument() == L"ShortWaveTable")
		{
			m_shortwavefactory.SetNote(note);
			instrument = m_shortwavefactory.CreateInstrument();
		}
		else if (note->Instrument() == L"LongWave")
		{
			m_longwavefactory.SetNote(note);
			instrument = m_longwavefactory.CreateInstrument();
		}
		else if (note->Instrument() == L"Subtractive")
		{
			m_oddsinesfactory.SetNote(note);
			instrument = m_oddsinesfactory.CreateInstrument();
		}
		else if (note->Instrument() == L"Drum")
		{
			m_drumfactory.SetNote(note);
			instrument = m_drumfactory.CreateInstrument();
		}
		else if (note->Instrument() == L"Chorus")
		{
			m_effects[CHORUS] = new CChorus();
		}
		else if (note->Instrument() == L"Flanging")
		{
			m_effects[FLANGING] = new CFlanging();
		}
		else if (note->Instrument() == L"NoiseGating")
		{
			m_effects[NOISEGATING] = new CNoiseGating();
		}
		else if (note->Instrument() == L"Reverberation")
		{
			m_effects[REVERBERATION] = new CReverberation();
		}
		else if (note->Instrument() == L"effect")
		{
			m_effectfactory.NextEffect();
		}

		// Configure the instrument object
		if (instrument != NULL)
		{
			instrument->SetSampleRate(GetSampleRate());
			instrument->SetNote(note);
			instrument->Start();

			m_instruments.push_back(instrument);
		}

		m_currentNote++;
	}
	//
	// Phase 2: Clear all channels to silence 
	//

	for (int c = 0; c < GetNumChannels(); c++)
		frame[c] = 0;
	
	double channelframes[NUMEFFECTCHANNELS][2];
	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		for (int c = 0; c < GetNumChannels(); c++)
		{
			channelframes[i][c] = 0;
	}
	}

	//
	// Phase 3: Play an active instruments
	//

	//
	// We have a list of active (playing) instruments.  We iterate over 
	// that list.  For each instrument we call generate, then add the
	// output to our output frame.  If an instrument is done (Generate()
	// returns false), we remove it from the list.
	//

	for (list<CInstrument *>::iterator node = m_instruments.begin(); node != m_instruments.end();)
	{
		// Since we may be removing an item from the list, we need to know in 
		// advance, what is after it in the list.  We keep that node as "next"
		list<CInstrument *>::iterator next = node;
		next++;

		// Get a pointer to the allocated instrument
		CInstrument *instrument = *node;

		// Call the generate function
		if (instrument->Generate())
		{
			// If we returned true, we have a valid sample.  Add it 
			// to the frame.
			for (int i = 0; i < NUMEFFECTCHANNELS; i++)
			{
				for (int c = 0; c < GetNumChannels(); c++)
			{
					channelframes[i][c] += instrument->Frame(c) * instrument->Send(i);
				}
			}
		}
		else
		{
			// If we returned false, the instrument is done.  Remove it
			// from the list and delete it from memory.
			m_instruments.erase(node);
			delete instrument;
		}

		// Move to the next instrument in the list
		node = next;
	}

	// 
	// Phase 3a: Effects
	//

	// Process each effect channel
	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		if (m_effects[i])
			m_effects[i]->ProcessStart(channelframes[i]);
	}

	// Mix effects with original audio
	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		for (int c = 0; c < GetNumChannels(); c++)
			frame[c] += channelframes[i][c];
	}

	//
	// Phase 4: Advance the time and beats
	//

	// Time advances by the sample period
	m_time += GetSamplePeriod();

	// Beat advances by the sample period divided by the 
	// number of seconds per beat.  The inverse of seconds
	// per beat is beats per second.
	m_beat += GetSamplePeriod() / m_secperbeat;

	// When the measure is complete, we move to
	// a new measure.  We might be a fraction into
	// the new measure, so we subtract out rather 
	// than just setting to zero.
	if (m_beat > m_beatspermeasure)
	{
		m_beat -= m_beatspermeasure;
		m_measure++;
	}
	//
	// Phase 5: Determine when we are done
	//

	// We are done when there is nothing to play.  We'll put something more 
	// complex here later.
	return !m_instruments.empty() || m_currentNote < (int)m_notes.size();
}


// Get the time since we started generating audio
double CSynthesizer::GetTime()
{
	return m_time;
}


void CSynthesizer::Clear()
{
	m_instruments.clear();
	m_notes.clear();
	
	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		if (m_effects[i] != NULL)
			delete m_effects[i];
	}

	m_effectfactory.Clear();
}


void CSynthesizer::XmlLoadScore(IXMLDOMNode * xml)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		if (name == L"bpm")
		{
			value.ChangeType(VT_R8);
			m_bpm = value.dblVal;
			m_secperbeat = 1 / (m_bpm / 60);
		}
		else if (name == L"beatspermeasure")
		{
			value.ChangeType(VT_I4);
			m_beatspermeasure = value.intVal;
		}

	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);
		if (name == L"instrument")
		{
			XmlLoadInstrument(node);
		}
	}
}


void CSynthesizer::OpenScore(CString & filename)
{
	Clear();

	//
	// Create an XML document
	//

	CComPtr<IXMLDOMDocument>  pXMLDoc;
	bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
		IID_IXMLDOMDocument, (void**)&pXMLDoc));
	if (!succeeded)
	{
		AfxMessageBox(L"Failed to create an XML document to use");
		return;
	}

	// Open the XML document
	VARIANT_BOOL ok;
	succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
	if (!succeeded || ok == VARIANT_FALSE)
	{
		AfxMessageBox(L"Failed to open XML score file");
		return;
	}

	//
	// Traverse the XML document in memory!!!!
	// Top level tag is <score>
	//

	CComPtr<IXMLDOMNode> node;
	pXMLDoc->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR nodeName;
		node->get_nodeName(&nodeName);
		if (nodeName == "score")
		{
			XmlLoadScore(node);
		}
	}
	sort(m_notes.begin(), m_notes.end());
}


void CSynthesizer::XmlLoadInstrument(IXMLDOMNode * xml)
{
	wstring instrument = L"";

	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "instrument")
		{
			instrument = value.bstrVal;
		}
	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"note")
		{
			XmlLoadNote(node, instrument);
		}
		if (name == L"effect")
		{
			XmlLoadEffect(node, instrument);
		}
	}

}


void CSynthesizer::XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument)
{
	m_notes.push_back(CNote());
	m_notes.back().XmlLoad(xml, instrument);
}


void CSynthesizer::XmlLoadEffect(IXMLDOMNode * xml, std::wstring & instrument)
{
	m_notes.push_back(CNote());
	m_notes.back().XmlLoad(xml, std::wstring(L"effect"));
	CNote n;
	n.XmlLoad(xml, instrument);
	m_effectfactory.AddNote(n);
}