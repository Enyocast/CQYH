#ifndef _ACHIEVEMENT_DATA_H_
#define _ACHIEVEMENT_DATA_H_

#include "string_def.h"
#include "achievement_def.h"
#include "data_manager.h"
#include "variable_def.h"

#define MAX_HANDBOOKITEM_COUNT	(32)
struct ACHIEVEMENT_DATA
{
	INT32 nAchievementID;												// Achievement ID
	char szName[COMMON_NAME_LEN];

	INT32 vecAchievementType[MAX_CON_PER_ACHIEVEMENT];                  // Type of each condition
	INT32 vecAchievementValue1[MAX_CON_PER_ACHIEVEMENT];				
	INT32 vecAchievementValue2[MAX_CON_PER_ACHIEVEMENT];				
	INT32 vecAchievementValue3[MAX_CON_PER_ACHIEVEMENT];				
	INT32 nAwardSlotCount;

	INT32 nPreAchievementID1;											// Prerequisite achievement 1
	INT32 nPreAchievementID2;											// Prerequisite achievement 2

	INT32 nRewardType[MAX_REWARD_PER_ACHIEVEMENT];						// Achievement reward type
	INT32 nRewardID[MAX_REWARD_PER_ACHIEVEMENT];						// Achievement reward

	INT32 nAchievementPts;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ACHIEVEMENT_DATA* pData, CTabFile* pTabConfig, INT32 nRow);

};

struct HANDBOOK_DATA
{
	INT32 nHandbookID;
	INT32 nHandbookType;
	INT32 nIndex;
	INT32 nID[MAX_HANDBOOKITEM_COUNT];
	char szValue[1024];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, HANDBOOK_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

class CAchievementIndexData
{
public:

	BOOL Init(void);
	BOOL UnInit(void);

	static CAchievementIndexData& GetInstance(void);
	UINT16* GetAchievementIds(INT16 nCondType, INT16 nSubType);

private:

	CAchievementIndexData();
	~CAchievementIndexData();

	static CAchievementIndexData   ms_Instance;
	UINT16 awDefAchievementId[adTotal][ACHIEVEMENT_MAX];
	UINT16 awVarAchievementId[avdTotal][ACHIEVEMENT_MAX];
	UINT16 awRoleVarAchievementId[MAX_ROLE_VARIABLE_COUNT][ACHIEVEMENT_MAX];

};


#endif // _ACHIEVEMENT_DATA_H_
