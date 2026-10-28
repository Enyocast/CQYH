#ifndef _CIRCLE_QUEST_H_
#define _CIRCLE_QUEST_H_

#include "role_def.h"
#include "quest_def.h"   

struct QUEST_DATA;

class CCIRCLE_QUEST_MGR
{
public:
	CCIRCLE_QUEST_MGR();
	virtual ~CCIRCLE_QUEST_MGR();

	static CCIRCLE_QUEST_MGR& GetInstance(void);

	BOOL Init(const char* pcszConfigName, const char* pcszPath);
	BOOL UnInit(void);

	INT32 AddCircleQuest(QUEST_DATA* pQuest);
	INT32 GetRandomCircleQuest(INT32 nCircleID, INT32 nLevel);

private:
	INT32 _AddtoCircleList(INT32 nCircleID, INT32 nIndexID, INT32 nQuestID);
	INT32 _SetGroupID(INT32 nCircleID, INT32 nGroupID);

private:
    static CCIRCLE_QUEST_MGR ms_Instance;

	typedef std::list<INT32>	CIRCLE_QUEST_ID_LIST;
	typedef CIRCLE_QUEST_ID_LIST::iterator IterCircleQuestIDList;

	CIRCLE_QUEST_ID_LIST	m_Circle_Quest_ID_List[MAX_CIRCLE_COUNT][MAX_ROLE_LEVEL/CIRCLE_QUEST_LEVEL_PER_GRADE];	//Each cycle maintains MAX_ROLE_LEVEL level brackets; give players quests for their bracket

	INT32	m_nGroupID[MAX_CIRCLE_QUEST_COUNT];
};

#endif	// _CIRCLE_QUEST_H_