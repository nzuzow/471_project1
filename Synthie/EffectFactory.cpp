#include "stdafx.h"

#include <algorithm>

#include "EffectFactory.h"


CEffectFactory::CEffectFactory()
{
	m_current = 0;
}


CEffectFactory::~CEffectFactory()
{
}


void CEffectFactory::NextEffect()
{
	if (m_notes.size() > 0 || m_current < m_notes.size())
	{
		m_active[m_notes[m_current].Instrument()] = m_notes[m_current];
		m_current++;
	}
}


void CEffectFactory::Fit(CInstrument * instr, const std::wstring & name)
{
	if (m_active.find(name) != m_active.end())
	{
		CNote n = m_active[name];
		for (int i = 0; i < NUMEFFECTCHANNELS; i++)
		{
			instr->SetSend(i, n.GetSend(i));
		}
	}
}


void CEffectFactory::Start()
{
	std::sort(m_notes.begin(), m_notes.end());
}


void CEffectFactory::Clear()
{
	m_notes.clear();
	m_active.clear();
	m_current = 0;
}