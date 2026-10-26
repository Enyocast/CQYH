#ifndef _INIT_REPUTATION_DATA_H_
#define _INIT_REPUTATION_DATA_H_

#include "data_manager.h"
#include "char_def.h"
#include "role_def.h"

//tolua_begin
struct INIT_REPUTATION_DATA
{
    INT32   nForceID;
    INT32   nInitValue;
	INT32	nMaxValue;
	BOOL	bActive;
    BOOL    bCanAttackWithFreePkMode;
	BOOL	bSabacMode;
	//tolua_end
	INT32	nAwardItemID[clsPlayerEnd][MAX_REPUTATION_AWARD_COUNT];
	INT32	nAwardItemCount[clsPlayerEnd][MAX_REPUTATION_AWARD_COUNT];
	INT32	nMaxAwardItemCount[clsPlayerEnd];
	//tolua_begin

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, INIT_REPUTATION_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};
//tolua_end

#endif  // _INIT_REPUTATION_DATA_H_