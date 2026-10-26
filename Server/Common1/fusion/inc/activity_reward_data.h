#ifndef _ACTIVITY_REWARD_DATA_H_
#define _ACTIVITY_REWARD_DATA_H_

#include "data_manager.h"

struct ACTIVITY_REWARD_DATA
{
	INT32	nID;
	INT32	nActivityValue;
	INT32	nRewardItemID;
	INT32	nRewardItemCount;
    INT32	nMoneytype01DailyUseLimit;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ACTIVITY_REWARD_DATA* pData, CTabFile * pTabConfig, INT32 nRow);
};

#endif //_ACTIVITY_REWARD_DATA_H_