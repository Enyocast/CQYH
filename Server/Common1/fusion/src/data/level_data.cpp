#include "stdafx.h"
#include "level_data.h"
#include "script_mgr.h"
#include "id_def.h"


BOOL ROLE_LEVEL_DATA::ReadLine(INT32& rnID, const char*& rpcszName, ROLE_LEVEL_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("Level", m_nLevel);
    READ_INT("MaxExp", m_nMaxExp);
    READ_INT("Pow", m_nPow);
    READ_INT("MoneyType01DailyUseLimit", m_nMoneyType01DailyUseLimit);
    READ_INT("MoneyType02DailyEarnLimit", m_nMoneyType02DailyEarnLimit);
    READ_INT("MoneyTypeBFTotalLimit", m_nMoneyTypeBFTotalLimit);
    READ_INT("MoneyTypeBFWeeklyEarnLimit", m_nMoneyTypeBFWeeklyEarnLimit);
    READ_INT("MoneyTypeArenaTotalLimit", m_nMoneyTypeArenaTotalLimit);
    READ_INT("MoneyTypeArenaWeeklyEarnLimit", m_nMoneyTypeArenaWeeklyEarnLimit);
    READ_INT("DailyExpLimit", m_nDailyExpLimit);
    READ_INT("MaxExtraExp", m_nMaxExtraExp);
	READ_INT("DailyExtraExp", m_nDailyExtraExp);
    READ_INT("GoldPoolPer5Min", m_nGoldPoolPer5Min);
    READ_INT("ExerciseExpPerHour", m_nExerciseExpPerHour);

    READ_END(m_nLevel);
}

BOOL HERO_LEVEL_DATA::ReadLine(INT32& rnID, const char*& rpcszName, HERO_LEVEL_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("Level", m_nLevel);
    READ_INT("MaxExp", m_nMaxExp);

    READ_END(m_nLevel);
}


INT32 GetMaxExp(INT32 nObjType, INT32 nLevel)
{
	if(nObjType == otHero)
	{
		const HERO_LEVEL_DATA* poLevel = CDataManager<HERO_LEVEL_DATA>::GetInstance().GetData(nLevel);
		LOG_PROCESS_ERROR(poLevel);

		return poLevel->m_nMaxExp;
	}
	else if(nObjType == otRole)
	{
		const ROLE_LEVEL_DATA* poLevel = CDataManager<ROLE_LEVEL_DATA>::GetInstance().GetData(nLevel);
		LOG_PROCESS_ERROR(poLevel);

		return poLevel->m_nMaxExp;
	}

Exit0:
	return -1;
}