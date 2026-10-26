#include "stdafx.h"
#include "simple_timer.h"

CSimpleTimer::CSimpleTimer(void)
{
	m_bEnabled = false;
	m_nStartTime = 0;
	m_nNextTrigTime = 0;
	m_nRemainTrigTimes = 0;
	m_nInterval = 0;
}

void CSimpleTimer::Enable(UINT32 nInterval, UINT32 nTrigTimes, UINT32 nNow, UINT32 nDelay)
{
	m_nStartTime = nNow;
	m_nInterval = nInterval;
	m_nRemainTrigTimes = nTrigTimes;
	m_nNextTrigTime = nNow + nDelay;

	m_bEnabled = true;
}

void CSimpleTimer::Disable(void)
{
	m_bEnabled = false;
}

bool CSimpleTimer::Trig(UINT32 nNow)
{
	if(m_nRemainTrigTimes <= 0)
	{
		Disable();
		return false;
	}

	if(!m_bEnabled || m_nNextTrigTime > nNow)
		return false;

	m_nRemainTrigTimes--;

	m_nNextTrigTime = nNow + m_nInterval;

	return true;
}

bool CSimpleTimer::TrigOver(void)
{
	return m_nRemainTrigTimes <= 0;
}

UINT32 CSimpleTimer::GetRemainTime(void)
{
	if(!m_bEnabled)
		return 0;

	return m_nRemainTrigTimes * m_nInterval;
}
