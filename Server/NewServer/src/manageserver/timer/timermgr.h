#ifndef _TIMER_MGR_H_
#define _TIMER_MGR_H_

#include "base_list.h"
#include "id_object_pool.h"

typedef BOOL (*TIMER_FUNC)(INT32 nParam1, INT32 nParam2, INT32 nParam3, const CHAR* szParam4);

static const UINT32 SECOND = 1;
static const UINT32 MINUTE = 60 * SECOND;
static const UINT32 HOUR = 60 * MINUTE;
static const UINT32 DAY = 24 * HOUR;
static const INT32	MAX_TRIG_COUNT = 0x7FFFFFFF;

enum eTimerLevel
{
	etlInvalid = -1,
	etlSecond,
	etlMinute,
	etlHour,
	etlDay,
	etlTotal
};

static const UINT32 lstTimeStandLevel[etlTotal] = {SECOND, MINUTE, HOUR, DAY};


struct STimer : public BASE_LIST_NODE
{
	UINT32 dwTimerID;

	UINT32 m_dwNextTrigTime;
	INT32 m_nRemainTrigCount;
	INT32 m_nInterval;

	CHAR  m_szFunc[32];
	TIMER_FUNC m_pFunc;

	INT32 m_nParam[3];
	CHAR  m_szParam[32];

	INT8 m_byTimerLevel;
};

class CTimerMgr
{
public:
	CTimerMgr();
	~CTimerMgr();

	BOOL Init(UINT32 dwCurTime);
	BOOL UnInit(VOID);
	static CTimerMgr& GetInstance(VOID);

	STimer* CreateTimer();
	BOOL DestroyTimer(STimer* pstTimer);
	STimer* FindTimer(UINT32 dwTimerID);

	BOOL StartTimer(STimer* pstTimer, UINT32 nDelay = 0);
	BOOL StartTimerAtTime(STimer* pstTimer, UINT32 dwStartTime);
	BOOL StopTimer(STimer* pstTimer);

	BOOL MainLoop(void);
private:
	BOOL _TrigTimerLevel(INT32 eTimeLevel);
	BOOL _UpdateTimer(STimer* pstTimer);
private:
	static CTimerMgr ms_Instance;
	UINT32  m_nTimerIDGenerator;

	UINT32	m_dwCurTime;

	CIDObjectPool<STimer, UINT32>		m_TimerPool;
	CBaseList							m_lstTimer[etlTotal];

	UINT32								m_lstNextTrigTime[etlTotal];
};


#endif // _TIMER_MGR_H_
