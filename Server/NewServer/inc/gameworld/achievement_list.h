#ifndef _ACHIEVEMENT_LIST_H_
#define _ACHIEVEMENT_LIST_H_

#include "achievement_def.h"
#include "variable_def.h"

#ifdef _ROBOT

#define ROBOT_ACHIEVEMENT_COMPLETED_CHECK(cAchievementList, nCondType, nSubType) \
		cAchievementList.RobotCompletedCheck(nCondType, nSubType);
#else

#define ROBOT_ACHIEVEMENT_COMPLETED_CHECK(cAchievementList, nCondType, nSubType)

#endif

class CRole;
struct ACHIEVEMENT_DATA;

struct ACCEPTED_ACHIEVEMENT
{
	INT32   nAchievementID;
	const	ACHIEVEMENT_DATA* pData;
};

class CAchievementsList   
{
public:
	CAchievementsList();
	virtual ~CAchievementsList();

	BOOL Init(CRole* pOwner);
	BOOL UnInit(void);

	BOOL Load_v_1(const char* pData, UINT32 dwSize);

	BOOL Save(const char* pData, UINT32& rdwSize);

	INT32 CanComplete(INT32 nAchievementID);
	INT32 Complete(INT32 nAchievementID);
	inline INT32 GetCompletedCount();

	INT32 CanReward(INT32 nAchievementID);
	INT32 Reward(INT32 nAchievementID);

	inline INT32 GetVariable(INT32 nIndex);
	void SetVariable(INT32 nIndex, INT32 nValue);
	void AddVariable(INT32 nIndex, INT32 nCount);

	void ActivateHandbook(INT32 nHandbookType, INT32 nIndex);

private:
	UINT16 	m_wAchievement[ACHIEVEMENT_MAX];
	UINT32	m_dwAchievementReward[ACHIEVEMENT_MAX/32];
    INT32   m_nAchievementStatistics[MAX_ACHIEVEMENT_STATISTIC_COUNT];
	CRole* 	m_pOwner;
	INT32  	m_nCompletedCount;

	UINT32	m_dwHandbook[htTotal][MAX_HANKBOOK_COUNT_PER_TYPE/32];

#ifdef _ROBOT

public:
	void RobotSyncAchievementList(const char* pcData, UINT32 dwSize, INT32 nCompletedCount);
	void RobotCompletedCheck(INT16 nCondType, INT16 nSubType);
	void RobotAchievementCheckLog(BOOL bCondTYpeCheck, INT16 nCondType, INT16 nSubType, INT16 nAchievementId, BOOL bAchievementCheck);

#endif // _ROBOT


private:
	BOOL  _IsCompleted(INT32 nAchievementID);

private:
	inline INT32 _CheckLevel(INT32 nLevel);
	inline INT32 _CheckExp(UINT32 nExp);
	inline INT32 _CheckPKValue(UINT32 dwPkValue);
	inline INT32 _CheckForceReputation(INT32 nForceID, INT32 nReputationValue);
	inline INT32 _CheckEquipSet(INT32 nSetID);
	inline INT32 _CheckTotalMoney(INT32 nMoneyType, INT32 nCount);
	inline INT32 _CheckKillPlayerTotalCount(INT32 nCount);
	inline INT32 _CheckEnterScene(INT32 nSceceID);
	inline INT32 _CheckCompleteQuest(INT32 nQuestID);
	inline INT32 _CheckCompleteQuestCount(INT32 nCount);	
	inline INT32 _CheckLearnSpell(INT32 nSpellID);	
	inline INT32 _CheckTitle(INT32 nTitleID);
	inline INT32 _CheckTitleCount(INT32 nTitleCount);
	inline INT32 _CheckFriendCount(INT32 nTitleCount);
	inline INT32 _CheckAchievement(INT32 nAchievementID);	
	inline INT32 _CheckAchievementCount(INT32 nAchievementCount);	
	inline INT32 _CheckadCreateTime(UINT32 dwCurrentTime, UINT32 dwTime);	
	inline INT32 _CheckMount(INT32 nMountCount);
	inline INT32 _CheckHero(INT32 nHeroClass, INT32 nHeroLevel);
	inline INT32 _CheckSetCount(INT32 nSetCount);
	inline INT32 _CheckSet(INT32 nSetID);
	inline INT32 _CheckLeaveStudentCount(INT32 nCount);
	inline INT32 _CheckSpiritLevel(INT32 nLevel);
	//inline INT32 _CheckSpiritAirColorCount(INT32 nColor, INT32 nCount);
	inline INT32 _CheckSpiritBuyAirEquipSlotCount(INT32 nCount);
	inline INT32 _CheckSpiritBuyAirBagSlotCount(INT32 nCount);
	inline INT32 _CheckSpiritBuyAirStallSlotCount(INT32 nCount);
	inline INT32 _CheckVip();
	inline INT32 _CheckSpiritBloodPageLevel(INT32 nPage, INT32 nSlotIndex, INT32 nNumber);
	inline INT32 _CheckExplore(INT32 nSceneTemplateID);

private:
	INT32 _CheckVariousForceCount(INT32 nMinReputation, INT32 nCount);
	INT32 _CheckEquip(INT32 nEquipID);
	INT32 _CheckVariable(INT32 nValue1, INT32 nValue2);
	INT32 _CheckRoleVariable(INT32 nValue1, INT32 nValue2);
	INT32 _CheckGetItem(INT32 nItemID);
	INT32 _CheckItemLuck(INT32 nLuck);
	INT32 _CheckItemRefine(INT32 nLuck);
	INT32 _CheckRefineLevel(INT32 nLevel);
	INT32 _CheckSpellLevelSpecified(INT32 nSpellID, INT32 nSpellLevel);
	INT32 _CheckSpellLevel(INT32 nSpellLevel, INT32 nCount);
	INT32 _CheckSpellCount(INT32 nCount);
	INT32 _CheckActiveSpellCount(INT32 nCount);
	INT32 _CheckRuneCount(INT32 nCount);	
	INT32 _CheckEquipPassiveSpellCount(INT32 nCount);
	INT32 _CheckEquipPassiveSpellIDCount(INT32 nSpellID);
	INT32 _CheckEquipColor(INT32 nColor);
	INT32 _CheckEquipBodyColor(INT32 nColor, INT32 nBodyPartID);
	INT32 _CheckBankSlotCount(INT32 nCount);
	INT32 _CheckTotalBagSlotCount(INT32 nCount);
	INT32 _CheckItemBagSlotCount(INT32 nCount);
	INT32 _CheckEquipBagSlotCount(INT32 nCount);
	INT32 _CheckMaterialBagSlotCount(INT32 nCount);
	INT32 _CheckSpiritAirColorLevel(INT32 nColor, INT32 nLevel);
	INT32 _CheckSpiritBloodPageCount(INT32 nCount);
	INT32 _CheckRanklist(INT32 nRankType, INT32 nRank);
	INT32 _CheckSpiritBloodPageCompleteCount(INT32 nPage, INT32 nCount);
	INT32 _CheckColorItemCompose(INT32 nColor, INT32 nCount);
	INT32 _CheckColorItemDeCompose(INT32 nColor, INT32 nCount);
	INT32 _CheckRuneWeaponCount(INT32 nCount);
	INT32 _CheckHandbook(INT32 nType, INT32 nCount);
};

inline INT32 CAchievementsList::GetCompletedCount()
{
	return m_nCompletedCount;
}

inline INT32 CAchievementsList::GetVariable(INT32 nIndex)
{
	LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_ACHIEVEMENT_STATISTIC_COUNT);

	return m_nAchievementStatistics[nIndex];
Exit0:
	return 0;
}

#endif // _ACHIEVEMENT_H_