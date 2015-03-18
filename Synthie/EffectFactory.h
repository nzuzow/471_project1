#pragma once

#include <vector>
#include <map>

#include "Note.h"
#include "Instrument.h"

class CEffectFactory
{
public:
	CEffectFactory();
	virtual ~CEffectFactory();
	void NextEffect();
	void AddNote(CNote & n) { m_notes.push_back(n); }
	void Fit(CInstrument *, const std::wstring &);
	void Start();
	void Clear();

private:
	std::vector<CNote> m_notes;		//!< The notes for an effect
	std::map<const std::wstring, CNote> m_active;	//!< The active effects
	int m_current;					//!< The current effect number
};

