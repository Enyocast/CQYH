#ifndef _GAMBLE_DATA_H_
#define _GAMBLE_DATA_H_

#include "data_manager.h"

struct GAMBLE_DATA
{
    INT32 nEquipType;
    INT32 nCostItemID;
    INT32 nCostItemCount;
    INT32 nRandomAttrFactor;
    INT32 nSocketFactor;
    INT32 nDropGroupID;
    INT32 nSuccessRate;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GAMBLE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _GAMBLE_DATA_H_
