/********************************************************************
	created:	4:9:2013   11:00
	file:		time_trigger.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_TIME_TRIGGER_H_
#define _H_TIME_TRIGGER_H_

#include "base_list.h"

struct BASE_TRIGGER_NODE;

enum TIME_TRIGGER_RET
{
    TIME_TRIGGER_RET_END = 0,
    TIME_TRIGGER_RET_CONTINUE = 1,
};

enum TIME_TRIGGER_TYPE
{
	tttInvalid,

	tttLuaTimer,

	tttTotal
};

//////////////////////////////////////////////////////////////////////////
// Return value: TIME_TRIGGER_RET
// The function manages BASE_TRIGGER_NODE lifetime: release on END, retain on CONTINUE
// When returning CONTINUE, update nWashoutTime internally with the new expiry time
//////////////////////////////////////////////////////////////////////////
typedef INT32 (*fpTimeTriggerCallBack)(BASE_TRIGGER_NODE *pTriggerNode);


// Base class for time-trigger nodes
struct BASE_TRIGGER_NODE : BASE_LIST_NODE
{
    //BASE_LIST_NODE  node;
	UINT32					dwWashoutTime;
	INT32					nTriggerType;
    fpTimeTriggerCallBack   fp;
};

class CTimeTrigger
{
protected:
    CTimeTrigger();
    ~CTimeTrigger();

    static CTimeTrigger     m_Instance;
public:
    static CTimeTrigger &GetInstance();

    BOOL Init();
    BOOL UnInit();
    BOOL MainLoop();
    
    BOOL InsertTrigger(BASE_TRIGGER_NODE* pTriggerNode);
    BOOL DeleteTrigger(BASE_TRIGGER_NODE* pTriggerNode);

	inline BASE_TRIGGER_NODE* GetFirstTrigger(INT32 nTriggerType);
	inline BASE_TRIGGER_NODE* GetNextTrigger(void);

private:
	CBaseList		m_TimerList[tttTotal];
	BASE_TRIGGER_NODE* m_pTraverseNode;
};

inline BASE_TRIGGER_NODE* CTimeTrigger::GetFirstTrigger(INT32 nTriggerType)
{
	LOG_PROCESS_ERROR(nTriggerType >= tttInvalid && nTriggerType < tttTotal);
	if (m_TimerList[nTriggerType].IsEmpty())
		return NULL;
	m_pTraverseNode = (BASE_TRIGGER_NODE*)m_TimerList[nTriggerType].Head().pNext;
	return m_pTraverseNode;
Exit0:
	return NULL;
}

inline BASE_TRIGGER_NODE* CTimeTrigger::GetNextTrigger(void)
{
	LOG_PROCESS_ERROR(m_pTraverseNode);
	LOG_PROCESS_ERROR(m_pTraverseNode->nTriggerType >= tttInvalid && m_pTraverseNode->nTriggerType < tttTotal);
	PROCESS_ERROR(m_pTraverseNode->pNext != &m_TimerList[m_pTraverseNode->nTriggerType].Rear());

	m_pTraverseNode = (BASE_TRIGGER_NODE*)m_pTraverseNode->pNext;

	return m_pTraverseNode;
Exit0:
	return NULL;
}

#endif //_H_TIME_TRIGGER_H_