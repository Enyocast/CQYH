#ifndef _GAMBLE_DATA_H_
#define _GAMBLE_DATA_H_

#include "data_manager.h"
#include "item_def.h"

struct GAMBLE_DATA
{
    INT32 nGambleKey;
    INT32 nGambleType;
    INT32 nGambleLevel;
    INT32 nCostItemID;
    INT32 nCostItemCount;
    INT32 nCostMoney;
    INT32 nRandomAttrFactor;
    INT32 nSocketFactor;

    DROP_CHANCE_DATA NormalDrop;
    INT32 nBossCount[4];
    DROP_CHANCE_DATA BossDrop[4];
    INT32 nWorldCount;
    DROP_CHANCE_DATA WorldDrop;

    INT32 nWorldGroupPos;
    INT32 nL1ModL0;
    INT32 nL2ModL0;
    INT32 nL2ModL1;

    static INT32 MakeKey(INT32 nGambleType, INT32 nGambleLevel) { return nGambleType << 16 | nGambleLevel; }
    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GAMBLE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _GAMBLE_DATA_H_
