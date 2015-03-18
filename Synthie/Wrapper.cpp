#include "stdafx.h"
#include "Wrapper.h"


CWrapper::CWrapper()
{
	m_frame[0] = 0;
	m_frame[1] = 0;
}


CWrapper::~CWrapper()
{
}


void CWrapper::Set(double * f)
{
	m_frame[0] = f[0];
	m_frame[1] = f[1];
}