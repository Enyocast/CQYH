#include "stdafx.h"
#include "money_data.h"
#include "money_def.h"

BOOL MONEY_DATA::ReadLine(INT32& rnID, const char*& rpcszName, MONEY_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("MoneyID", m_nMoneyID);
    READ_STR("MoneyName", m_szMoneyName);

    READ_INT("TotalLimit", m_nTotalLimit);
    READ_INT("DailyEarnLimit", m_nDailyEarnLimit);
    READ_INT("DailyUseLimit", m_nDailyUseLimit);
    READ_INT("WeeklyEarnLimit", m_nWeeklyEarnLimit);
    READ_INT("WeeklyUseLimit", m_nWeeklyUseLimit);

    rpcszName = pData->m_szMoneyName;
    READ_END(m_nMoneyID);
}
