#include "stdafx.h"
#include "SubtractiveFactory.h"
#include "audio/DirSoundSource.h"
#include "Note.h"


CSubtractiveFactory::CSubtractiveFactory()
{
	m_waves.clear();

	LoadFile("SubWaves/triangle.wav");
	LoadFile("SubWaves/sawtooth.wav");
	LoadFile("SubWaves/squarewave.wav");

}


CSubtractiveFactory::~CSubtractiveFactory()
{
}


CSubtractive *CSubtractiveFactory::CreateInstrument()
{

	CSubtractive *instrument = new CSubtractive();
	instrument->SetType(m_type);
	instrument->GetPlayer()->SetSamples(&m_waves[m_type][0], (int)m_waves[m_type].size());

	return instrument;
}


bool CSubtractiveFactory::LoadFile(const char *filename)
{
	std::vector<short> wave;

	CDirSoundSource file;
	if (!file.Open(filename))
	{
		CString msg = L"Unable to open audio file: ";
		msg = +filename;
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i < file.NumSampleFrames(); i++)
	{
		short frame[2];
		file.ReadFrame(frame);
		wave.push_back(frame[0]);

	}

	file.Close();
	m_waves.push_back(wave);
	return true;
}


void CSubtractiveFactory::SetNote(CNote *note)
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
		
		if (name == "SubType")
		{
			SetType(SetSubType(value.bstrVal));
		}/*
		else if (name == "note")
		{
			m_freq = (NoteToFrequency(value.bstrVal));
		}*/

	}
}


int CSubtractiveFactory::SetSubType(const WCHAR *name)
{
	if (std::wstring(name) == L"Triangle"){ return 0; }
	else if (std::wstring(name) == L"Sawtooth"){ return 1; }
	else if (std::wstring(name) == L"Square"){ return 2; }
}