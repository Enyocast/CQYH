#include "stdafx.h"
#include "gamble_data.h"


BOOL GAMBLE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, GAMBLE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT_EXPR("EquipType", nEquipType);
    READ_INT("CostItemID", nCostItemID);
    READ_INT("CostItemCount", nCostItemCount);
    READ_INT("RandomAttrFactor", nRandomAttrFactor);
    READ_INT("SocketFactor", nSocketFactor);
    READ_INT("DropGroupID", nDropGroupID);
    READ_INT("SuccessRate", nSuccessRate);

    READ_END(nEquipType);
}
