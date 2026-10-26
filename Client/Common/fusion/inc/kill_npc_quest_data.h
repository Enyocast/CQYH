#ifndef _KILL_NPC_QUEST_DATA_H_
#define _KILL_NPC_QUEST_DATA_H_

#include "data_manager.h"
#include "quest_def.h"
#include "string_def.h"

struct KILL_NPC_QUEST_DATA
{
	INT32	nQuestID;
	INT32	nNpcTemplateID;
	INT32	nNpcGroupID;
	INT32	eResetType;

	char	szName[MAX_KILL_COUNT_PER_NPC][COMMON_NAME_LEN];
	INT32	nKillCount[MAX_KILL_COUNT_PER_NPC];
	INT32	nAchievementPts[MAX_KILL_COUNT_PER_NPC];
	INT32	nRewardExp[MAX_KILL_COUNT_PER_NPC];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, KILL_NPC_QUEST_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif	// _KILL_NPC_QUEST_DATA_H_