using namespace std;
#pragma once
#include <list>
#include <vector>
#include "msxml2.h"
#include "Instrument.h"
#include "Note.h"
#include "OddSinesFactory.h"
#include "WaveInstrumentFactory.h"
#include "DrumInstrumentFactory.h"
#include "ShortWaveFactory.h"
#include "Effect.h"
#include "EffectFactory.h"

#define CHORUS 1
#define FLANGING 2
#define NOISEGATING 3
#define REVERBERATION 4

class CSynthesizer
{
public:
	CSynthesizer();
	virtual ~CSynthesizer();
public:
	//! Number of audio channels
	int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return m_samplePeriod; }

	//! Beats per minute 
	double GetBeatsPerMinute() { return m_bpm; }

	//! Set the number of channels
	void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

	void Clear();
	void OpenScore(CString & );
	void XmlLoadScore(IXMLDOMNode * xml);
	void XmlLoadInstrument(IXMLDOMNode * xml);
	void XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument);
	void XmlLoadEffect(IXMLDOMNode * xml, std::wstring & instrument);
private:
	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	double  m_bpm;                  //!< Beats per minute
	int     m_beatspermeasure;  //!< Beats per measure
	double  m_secperbeat;        //!< Seconds per beat
	int m_currentNote;          //!< The current note we are playing
	int m_measure;              //!< The current measure
	double m_beat;              //!< The current beat within the measure
	COddSinesFactory m_oddsinesfactory;
	CWaveInstrumentFactory m_waveinstfactory;
	CDrumInstrumentFactory m_drumfactory;
	CShortWaveFactory m_shortwavefactory;
	std::list<CInstrument *>  m_instruments;	//!< List of synthesizer instruments
	std::vector<CNote> m_notes;					//!< List of notes in the synthesizer
	CEffect * m_effects[NUMEFFECTCHANNELS];		//!< List of synthesizer effects
	CEffectFactory m_effectfactory;					//!< Factory for creating effects

public:
	void Start();
	bool Generate(double*);
private:
	double m_time;
public:
	// Get the time since we started generating audio
	double GetTime();
};

