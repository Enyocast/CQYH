#ifndef _KILL_NPC_QUEST_H_
#define _KILL_NPC_QUEST_H_

#include "quest_def.h"

class CRole;
class CNpc;

class CKillNpcQuest
{
public:
	CKillNpcQuest();
	~CKillNpcQuest();

	BOOL Init(CRole* poOwner);
	BOOL UnInit(void);
	BOOL ResetDailyQuest(void);
	BOOL ResetWeeklyQuest(void);

	inline UINT16 GetKillCount(INT32 nQuestID);
	inline UINT8 GetCompleteState(INT32 nQuestID);

	BOOL Load_v_1(const char* pData, UINT32 dwSize);
	BOOL Save(const char* pData, UINT32& rdwSize);

	INT32 CanComplete(INT32 nQuestID, INT32 nIndex);
	INT32 Complete(INT32 nQuestID, INT32 nIndex);

	void OnKillNpc(CNpc* poNpc);

private:
	CRole*	m_poOwner;
	UINT16	m_wKillNpcCount[MAX_KILL_NPC_QUEST_COUNT];
	UINT8	m_byCompleteList[MAX_KILL_NPC_QUEST_COUNT];
};

inline UINT16 CKillNpcQuest::GetKillCount(INT32 nQuestID)
{
	LOG_PROCESS_ERROR(nQuestID >= 0 && nQuestID < MAX_KILL_NPC_QUEST_COUNT);

	return m_wKillNpcCount[nQuestID];
Exit0:
	return 0;
}

inline UINT8 CKillNpcQuest::GetCompleteState(INT32 nQuestID)
{
	LOG_PROCESS_ERROR(nQuestID >= 0 && nQuestID < MAX_KILL_NPC_QUEST_COUNT);

	return m_byCompleteList[nQuestID];
Exit0:
	return 0;
}

#endif	// _KILL_NPC_QUEST_H_