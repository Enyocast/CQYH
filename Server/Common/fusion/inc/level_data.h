#ifndef _LEVEL_DATA_H_
#define _LEVEL_DATA_H_

#include "data_manager.h"

//tolua_begin

struct ROLE_LEVEL_DATA
{
	INT32   m_nLevel;
	INT32   m_nMaxExp;
	INT32   m_nPow;
    INT32   m_nMoneyType01DailyUseLimit;
    INT32   m_nMoneyType02DailyEarnLimit;
    INT32   m_nMoneyTypeBFTotalLimit;
    INT32   m_nMoneyTypeBFWeeklyEarnLimit;
    INT32   m_nMoneyTypeArenaTotalLimit;
    INT32   m_nMoneyTypeArenaWeeklyEarnLimit;
    INT32   m_nDailyExpLimit;
    INT32   m_nMaxExtraExp;
	INT32	m_nDailyExtraExp;
    INT32   m_nGoldPoolPer5Min;
    INT32   m_nExerciseExpPerHour;
	INT32	m_nOnlineExtraExpPer5Min;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ROLE_LEVEL_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct HERO_LEVEL_DATA
{
	INT32 m_nLevel;
	INT32 m_nMaxExp;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, HERO_LEVEL_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


INT32 GetMaxExp(INT32 nObjType, INT32 nLevel);

//tolua_end

#endif	// _LEVEL_DATA_H_
