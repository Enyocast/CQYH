#include "stdafx.h"
#include "data_manager.h"
#include "activity_reward_data.h"

BOOL ACTIVITY_REWARD_DATA::ReadLine(INT32& rnID, const char*& rpcszName, ACTIVITY_REWARD_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("ID", nID);
	LOG_PROCESS_ERROR(pData->nID >=0 && pData->nID <= 32);

	READ_INT("ActivityValue", nActivityValue);
	READ_INT("RewardItemID", nRewardItemID);
	READ_INT("RewardItemCount", nRewardItemCount);
    READ_INT("MoneyType01DailyUseLimit", nMoneytype01DailyUseLimit);

	READ_END(nID);
}