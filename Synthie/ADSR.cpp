#include "stdafx.h"
#include "ADSR.h"


CADSR::CADSR()
{
	m_duration = 0.1;
	m_attack = 0.03;
	m_decay = 0.02;
	m_sustain = 0.03;
	m_release = 0.02;
}


CADSR::~CADSR()
{
}

void CADSR::Start()
{
	m_source->SetSampleRate(GetSampleRate());
	m_source->Start();
	m_time = 0;
}

bool CADSR::Generate()
{
	// Tell the component to generate an audio sample
	m_source->Generate();

	// Read the component's sample and make it our resulting frame.
	if (m_time <  m_attack)
	{
		m_frame[0] = m_source->Frame(0) * m_time / m_attack;
		m_frame[1] = m_source->Frame(1) * m_time / m_attack;
	}
	else if ((m_time > m_attack) && (m_time < m_duration - m_release - m_sustain))
	{
		m_frame[0] = m_source->Frame(0) * (m_duration - m_time - m_sustain) / (m_release + m_decay);
		m_frame[1] = m_source->Frame(1) * (m_duration - m_time - m_sustain) / (m_release + m_decay);
	}
	else if ((m_time > m_attack + m_decay) && (m_time < m_duration - m_release))
	{
		m_frame[0] = m_source->Frame(0) * (m_decay / (m_release + m_decay));
		m_frame[1] = m_source->Frame(1) * (m_decay / (m_release + m_decay));
	}
	else if (m_time > m_duration - m_release)
	{
		m_frame[0] = m_source->Frame(0) * (m_duration - m_time) / (m_release + m_decay);
		m_frame[1] = m_source->Frame(1) * (m_duration - m_time) / (m_release + m_decay);
	}
	else
	{
		m_frame[0] = m_source->Frame(0);
		m_frame[1] = m_source->Frame(1);
	}
	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration;
}

