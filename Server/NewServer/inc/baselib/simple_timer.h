#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

class CSimpleTimer
{
public:
	CSimpleTimer(void);

	void Enable(UINT32 nInterval, UINT32 nTrigTimes, UINT32 nNow, UINT32 nDelay);

	void Disable(void);

	bool Trig(UINT32 nNow);

	UINT32 GetRemainTime(void);

	bool TrigOver(void);

private:
	bool m_bEnabled;
	UINT32 m_nStartTime;
	UINT32 m_nNextTrigTime;
	UINT32 m_nRemainTrigTimes;
	UINT32 m_nInterval;
};

#endif // _simple_timer_h__
