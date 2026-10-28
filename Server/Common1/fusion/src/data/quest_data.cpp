#include "stdafx.h"
#include "quest_data.h"
#include "id_def.h"
#include "script_mgr.h"

BOOL QUEST_DATA::ReadLine(INT32& rnID, const char*& rpcszName, QUEST_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    // 基本属性
    READ_INT("QuestTempID", nQuestID);

    READ_INT("ResetType", eResetType);
    READ_INT("CanAbandon", bCanAbandon);
	READ_INT("CanShare",  bCanShare);	
	READ_INT("CanPublish",  bCanPublish);	
	READ_INT("QuestType",  nQuestType);	
    READ_INT("nResetTime", dwResetTime);
    READ_INT("DurationLimit", nDurationLimit);
    READ_INT("CircleID", nCircleID);
	pData->nQuality = 0;

	//LOG_PROCESS_ERROR(CheckValidQuestID(pData->nQuestType, pData->nQuestID));

    READ_INT("EmergencyCD", nEmergencyCoolDown);
	pData->nEmergencyCoolDown = pData->nEmergencyCoolDown * GAME_FPS;

    READ_STR("QuestName", szName);
	pData->dwResetTime -= (pData->dwResetTime%86400);

	for (INT32 nIdx = 0; nIdx < MAX_FLY_SPOT_PER_QUEST; ++nIdx)
	{
		char szColumn[COMMON_NAME_LEN];

		snprintf(szColumn, COMMON_NAME_LEN, "Destinations.DestMapId%d", nIdx + 1);
		READ_INT(szColumn, nSceneID[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "Destinations.DestX%d", nIdx + 1);
		READ_LENGTH(szColumn, nX[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "Destinations.DestY%d", nIdx + 1);
		READ_LENGTH(szColumn, nY[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "Destinations.DestZ%d", nIdx + 1);
		READ_LENGTH(szColumn, nZ[nIdx]);
	}

    // 接交任务检测条件
    READ_INT("MaxCompleteCount", nMaxCompletedCount);
    if (pData->nQuestID >= 0 && pData->nQuestID < MAX_NORMAL_QUEST_COUNT)
        LOG_PROCESS_ERROR(pData->nMaxCompletedCount == 0 || pData->nMaxCompletedCount == 1);
    else if (pData->nQuestID >= REPEAT_QUEST_START_ID && pData->nQuestID < REPEAT_QUEST_START_ID + MAX_REPEAT_QUEST_COUNT)
        LOG_PROCESS_ERROR(pData->nMaxCompletedCount > 1 && pData->nMaxCompletedCount < MAX_REPEAT_QUEST_CYCLE);
    READ_INT("ClassLimit", nClassLimit);
    READ_INT("SexLimit", nSexLimit);
    READ_INT("RelationLimit", nRelationLimit);

    // 接任务检测条件
    READ_INT("PreQuestTempID1", nPreQuestID1);
    READ_INT("PreQuestTempID2", nPreQuestID2);
    READ_INT("StartNPCNew", nStartNpcID);
    READ_INT("StartItem", nStartItemID);
    READ_INT("StartZone", bStartZone);

    READ_INT("MinLevelLimit", nMinLevelLimit);
    READ_INT("MaxLevelLimit", nMaxLevelLimit);
    READ_INT("BuffLimit", nBuffIDLimit);
    READ_INT("BuffLevelLimit", nBuffLevelLimit);
    READ_INT("MoneyTypeLimit", nMoneyTypeLimit);
    READ_INT("MoneyAmountLimit", nMoneyAmountLimit);
    READ_INT("ReputationForceID", nReputationForceID);
    READ_INT("ReputationMinLimit", nReputationMinLimit);
    READ_INT("ReputationMaxLimit", nReputationMaxLimit);

    READ_INT("YearLimit", nYearLimit);
    READ_INT("MonthLimit", nMonthLimit);

    READ_INT("StartWeekday", nStartWeekday);
    READ_INT("WeekdayDuration", nWeekdayDuration);
    LOG_PROCESS_ERROR(pData->nWeekdayDuration >= 0 && pData->nWeekdayDuration < 7);

    READ_INT("StartMonthday", nStartMonthday);
    READ_INT("MonthdayDuration", nMonthdayDuration);

    READ_INT("nAcceptTimeStart", dwAcceptStartTime);
    READ_INT("nAcceptTimeEnd", dwAcceptEndTime);
    READ_INT("AcceptStartHour", nAcceptStartHour);
    READ_INT("AcceptStartMinute", nAcceptStartMin);
    READ_INT("AcceptEndHour", nAcceptEndHour);
    READ_INT("AcceptEndMinute", nAcceptEndMin);
    //pData->nAcceptStartHour = pData->nAcceptStartMin = pData->nAcceptEndHour = pData->nAcceptEndMin = 0;
    pData->nAcceptStartDayTime = pData->nAcceptStartHour * 3600 + pData->nAcceptStartMin * 60;
    pData->nAcceptEndDayTime = pData->nAcceptEndHour * 3600 + pData->nAcceptEndMin * 60;
    LOG_PROCESS_ERROR(pData->nAcceptStartDayTime <= pData->nAcceptEndDayTime);

    for (INT32 nIdx = 0; nIdx < MAX_CONDITION_PER_QUEST; ++nIdx)
    {
        char szColumn[COMMON_NAME_LEN];

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "ItemLimit.CheckItemID", nIdx + 1);
        READ_INT(szColumn, vecItemLimitID[nIdx]);

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "ItemLimit.CheckItemCnt", nIdx + 1);
        READ_INT(szColumn, vecItemLimitCnt[nIdx]);
    }

	READ_QUEST_VAR("VarLimit.CheckVarType1", "VarLimit.CheckVarID1", nLimitVarID1);
    READ_INT("VarLimit.CheckVarCnt1", nLimitVarValue1);
	READ_QUEST_VAR("VarLimit.CheckVarType2", "VarLimit.CheckVarID2", nLimitVarID2);
    READ_INT("VarLimit.CheckVarCnt2", nLimitVarValue2);
    READ_STR("BeforeAcceptScriptName", szBeforeAcceptScriptName);

    // 接任务执行动作
    READ_INT("OfferCurrencyType", nOfferMoneyType);
    READ_INT("OfferCurrencyAmount", nOfferMoneyAmount);
    READ_INT("OfferBuff", nOfferBuffID);
    READ_INT("OfferBuffLevel", nOfferBuffLevel);

    READ_INT("OfferItem.CheckItemID1", nOfferItemID);
    READ_INT("OfferItem.CheckItemCnt1", nOfferItemCnt);
    READ_STR("AfterAcceptScriptName", szAfterAcceptScriptName);

    // 交任务检测条件
	READ_INT("TalkNpcID", nTalkNpcID);
	READ_INT("TalkVarID", nTalkVarID);
	READ_INT("ExplorVarID", nExploreVarID);

    READ_INT("FinishNpcNew", nFinishNpc);
    READ_INT("FinishItem", nFinishItemID);
    READ_INT("CheckBuff", nCheckBuffID);
    READ_INT("CheckBuffLevel", nCheckBuffLevel);
	READ_INT("CheckLevel", nCheckLevel);

	READ_INT("CheckReputationForceID", nCheckReputationForceID);
	READ_INT("CheckReputation", nCheckReputationForceValue);

    for (INT32 nIdx = 0; nIdx < MAX_CONDITION_PER_QUEST; ++nIdx)
    {
        char szColumn[COMMON_NAME_LEN];

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillNpc.CheckKillNpcNew", nIdx + 1);
        READ_INT(szColumn, nCheckKillNpcID[nIdx]);

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillNpc.CheckKillNpcGroupId", nIdx + 1);
        READ_INT(szColumn, nCheckKillNpcGroupID[nIdx]);

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillNpc.CheckKillNpcCnt", nIdx + 1);
        READ_INT(szColumn, nCheckKillNpcCnt[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillDoodad.CheckKillDoodadID", nIdx + 1);
		READ_INT(szColumn, nCheckKillDoodadID[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillDoodad.CheckKillDoodadCnt", nIdx + 1);
		READ_INT(szColumn, nCheckKillDoodadCnt[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckItem.CheckItemID", nIdx + 1);
		READ_INT(szColumn, nCheckItemID[nIdx]);

		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckItem.CheckItemCnt", nIdx + 1);
		READ_INT(szColumn, nCheckItemCount[nIdx]);

		pData->nCheckKillItemNpcID[nIdx] = 0;
		pData->nCheckKillItemNpcRate[nIdx] = 0;
		pData->nCheckKillItemCnt[nIdx] = 0;
    }
    
	for (INT32 nCheckVarIndex = 0; nCheckVarIndex < MAX_CHECK_VAR_COUNT; nCheckVarIndex++)
	{
		char szCheckType[COMMON_NAME_LEN];
		char szCheckID[COMMON_NAME_LEN];
		char szCheckCount[COMMON_NAME_LEN];

		snprintf(szCheckType, COMMON_NAME_LEN, "%s%d", "CheckVar.CheckVarType", nCheckVarIndex + 1);
		snprintf(szCheckID, COMMON_NAME_LEN, "%s%d", "CheckVar.CheckVarID", nCheckVarIndex + 1);
		snprintf(szCheckCount, COMMON_NAME_LEN, "%s%d", "CheckVar.CheckVarCnt", nCheckVarIndex + 1);

		READ_QUEST_VAR(szCheckType, szCheckID, nCheckVarID[nCheckVarIndex])
		READ_INT(szCheckCount, nCheckVarValue[nCheckVarIndex]);
	}

    READ_STR("BeforeCompleteScriptName", szBeforeCompleteScriptName);

	for (INT32 nIdx = 0; nIdx < CHECK_KILL_PLAYER_CONDITION; ++nIdx)
	{
		char szColumn[COMMON_NAME_LEN];

		memset(szColumn, 0, sizeof(szColumn));
		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillPlayer.CheckKillPlayerLevelStart", nIdx + 1);
		READ_INT(szColumn, nCheckKillPlayerLevlStart[nIdx]);

		memset(szColumn, 0, sizeof(szColumn));
		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillPlayer.CheckKillPlayerLevelEnd", nIdx + 1);
		READ_INT(szColumn, nCheckKillPlayerLevlEnd[nIdx]);

		memset(szColumn, 0, sizeof(szColumn)); 
		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillPlayer.CheckKillPlayerCnt", nIdx + 1);
		READ_INT(szColumn, nCheckKillPlayerCount[nIdx]);

		memset(szColumn, 0, sizeof(szColumn));
		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillPlayer.CheckKillPlayerBuffId", nIdx + 1);
		READ_INT(szColumn, nCheckKillBufPlayerBufID[nIdx]);

		memset(szColumn, 0, sizeof(szColumn));
		snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "CheckKillPlayer.CheckKillPlayerCnt", nIdx + 1);
		READ_INT(szColumn, nCheckKillBufPlayerCount[nIdx]);

		if (pData->nCheckKillPlayerCount[nIdx])
		{
			LOG_PROCESS_ERROR(pData->nCheckKillPlayerLevlStart[nIdx] < pData->nCheckKillPlayerLevlEnd[nIdx]);
		}
	}

    // 交任务执行动作
 	READ_INT("AwardCurrencyType", stRewardData.nAwardMoneyType1);
 	READ_INT("AwardCurrencyAmount", stRewardData.nAwardMoneyAmount1);
	READ_INT("AwardCurrencyTypeEx", stRewardData.nAwardMoneyType2);
	READ_INT("AwardCurrencyAmountEx", stRewardData.nAwardMoneyAmount2);
    
	READ_INT("AwardExp", stRewardData.nAwardExp);
    READ_INT("AwardBuff", stRewardData.nAwardBuffID);
    READ_INT("AwardBuffLevel", stRewardData.nAwardBuffLevel);
    READ_INT("AwardActivity", stRewardData.nActivity);
    READ_INT("AwardTitle", stRewardData.nAwardTitleID);
    READ_INT("AwardReputationType", stRewardData.nAwardReputationForceID);
    READ_INT("AwardReputation", stRewardData.nAwardReputation);

	for (INT32 nIdx = 0; nIdx < MAX_REWARD_PER_QUEST; ++nIdx)
    {
        char szColumn[COMMON_NAME_LEN];

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "AwardItem.AwardItemID", nIdx + 1);
        READ_INT(szColumn, stRewardData.vecAwardItemID[nIdx]);

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "AwardItem.AwardItemCnt", nIdx + 1);
        READ_INT(szColumn, stRewardData.vecAwardItemCnt[nIdx]);
    }

    pData->stRewardData.bNeedSelectAward = FALSE;

    for (INT32 nIdx = 0; nIdx < MAX_SELECTABLE_REWARD_COUNT; ++nIdx)
    {
        char szColumn[256];

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "SelectableAwardItem.SelectableAwardItemID", nIdx + 1);
        READ_INT(szColumn, stRewardData.vecSelectableAwardItemID[nIdx]);

        snprintf(szColumn, COMMON_NAME_LEN, "%s%d", "SelectableAwardItem.SelectableAwardItemCnt", nIdx + 1);
        READ_INT(szColumn, stRewardData.vecSelectableAwardItemCnt[nIdx]);

        if (pData->stRewardData.vecSelectableAwardItemID[nIdx] != INVALID_OBJECT_ID)
            pData->stRewardData.bNeedSelectAward = TRUE;
    }

    READ_STR("AfterCompleteScriptName", szAfterCompleteScriptName);

    READ_STR("AbandonScriptName", szAbandonScriptName);

	READ_END(nQuestID);
}

BOOL QUEST_DATA::CheckValidQuestID(INT32 nQuestType, INT32 nQuestID)
{
		INT32 nRetCode = 0;
		
		switch(nQuestType)
		{
		case qtTrunk:
		case qtBranch:
		case qtActivity:
		case qtGuild:
		case qtMaster:
		case qtWedding:
		case qtAdventure:
		case qtGuide:
			{
				LOG_PROCESS_ERROR((nQuestID >= INVALID_QUEST_ID) && (nQuestID <= MAX_NORMAL_QUEST_COUNT));
			}
			break;
		case qtCircle:
			{
				LOG_PROCESS_ERROR((nQuestID >= CIRCLE_QUEST_START_ID) && (nQuestID <= (CIRCLE_QUEST_START_ID + MAX_CIRCLE_QUEST_COUNT)));
			}
			break;
		case qtReward:
			{
				LOG_PROCESS_ERROR((nQuestID >= REWARD_QUEST_START_ID) && (nQuestID <= (REWARD_QUEST_START_ID + MAX_REWARD_QUEST_COUNT)));
			}
			break;
		case qtDaily:
			{
				LOG_PROCESS_ERROR((nQuestID >= REPEAT_QUEST_START_ID) && (nQuestID < (REPEAT_QUEST_START_ID + MAX_REPEAT_QUEST_COUNT)));
			}
			break;
		case qtEmegency:
			{
				LOG_PROCESS_ERROR((nQuestID >= EMERGENCY_QUEST_START_ID) && (nQuestID < (EMERGENCY_QUEST_START_ID + MAX_EMERGENCY_QUEST_COUNT)));
			}
		default:
			break;
		}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL REWARD_QUEST_MONEY_COST_DATA::ReadLine(INT32& rnID, const char*& rpcszName, REWARD_QUEST_MONEY_COST_DATA* pData, CTabFile * pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("Time", nTime);
    READ_INT("MoneyCost", nMoneyCost);

	READ_END(nTime);
}

BOOL QUEST_RECYCLE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, QUEST_RECYCLE_DATA* pData, CTabFile * pTabConfig, INT32 nRow)
{
	READ_START();

    READ_INT("ItemLevel", nItemLevel);
    READ_INT_EXPR("ItemColor", nItemColor);
    READ_INT_EXPR("ItemSubType", nItemSubType);
    READ_INT("VarIndex", nVarIndex);

	rnID = MAKE_QUEST_CYCLE_KEY(pData->nItemLevel, pData->nItemColor, pData->nItemSubType);

	return TRUE;
Exit0:
	return FALSE;
}