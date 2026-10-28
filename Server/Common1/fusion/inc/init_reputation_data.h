#ifndef _INIT_REPUTATION_DATA_H_
#define _INIT_REPUTATION_DATA_H_

#include "data_manager.h"
#include "char_def.h"
#include "role_def.h"
struct INIT_REPUTATION_DATA
{
    INT32   nForceID;
    INT32   nInitValue;
	INT32	nMaxValue;
	BOOL	bActive;
    BOOL    bCanAttackWithFreePkMode;
	BOOL	bSabacMode;
	INT32	nAwardItemID[clsPlayerEnd][MAX_REPUTATION_AWARD_COUNT];
	INT32	nAwardItemCount[clsPlayerEnd][MAX_REPUTATION_AWARD_COUNT];
	INT32	nMaxAwardItemCount[clsPlayerEnd];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, INIT_REPUTATION_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif  // _INIT_REPUTATION_DATA_H_