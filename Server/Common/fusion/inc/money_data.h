#ifndef _MONEY_DATA_H_
#define _MONEY_DATA_H_

#include "data_manager.h"

struct MONEY_DATA
{
    INT32 m_nMoneyID;
    char  m_szMoneyName[64];
    INT32 m_nTotalLimit;
    INT32 m_nDailyEarnLimit;
    INT32 m_nDailyUseLimit;
    INT32 m_nWeeklyEarnLimit;
    INT32 m_nWeeklyUseLimit;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, MONEY_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _MONEY_DATA_H_
