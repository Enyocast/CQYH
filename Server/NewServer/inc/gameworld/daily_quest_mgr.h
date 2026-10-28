#ifndef _DAILY_QUEST_H_
#define _DAILY_QUEST_H_

#include "role_def.h"
#include "quest_def.h"

#define MAX_DAILY_QUEST_GROUP_COUNT (MAX_ROLE_LEVEL/5)	// Number of level brackets

struct QUEST_DATA;

class CDailyQuestMgr
{
public:
	CDailyQuestMgr();
	virtual ~CDailyQuestMgr();

	static CDailyQuestMgr& GetInstance(void);

	BOOL Init(void);
	BOOL UnInit(void);

	INT32 AddDailyQuest(QUEST_DATA* pQuest);

	INT32 GetRandomQuestIndex(INT32 nLevel);
	INT32 GetQuestIDByIndex(INT32 nLevel, INT32 nIndex);
	INT32 GetIndexByQuestID(INT32 nLevelIndex, INT32 nQuestID);

private:
	BOOL _AddDailyQuest(INT32 nIndex, INT32 nQuestID);

private:
	static CDailyQuestMgr ms_Instance;

	INT32	m_DailyQuestGroup[MAX_DAILY_QUEST_GROUP_COUNT][MAX_REWARD_QUEST_COUNT_PER_GROUP];
	INT32	m_DailyQuestGroupSize[MAX_DAILY_QUEST_GROUP_COUNT];
};


#endif // _DAILY_QUEST_H_