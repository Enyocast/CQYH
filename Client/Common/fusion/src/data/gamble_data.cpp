#include "stdafx.h"
#include "gamble_data.h"


BOOL GAMBLE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, GAMBLE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT_EXPR("GambleType", nGambleType);
    READ_INT("GambleLevel", nGambleLevel);
    READ_INT("CostItemID", nCostItemID);
    READ_INT("CostItemCount", nCostItemCount);
    READ_INT("CostMoney", nCostMoney);
    READ_INT("RandomAttrFactor", nRandomAttrFactor);
    READ_INT("SocketFactor", nSocketFactor);
    READ_INT("DropGroupID", NormalDrop.nDropGroupID);
    READ_INT("SuccessRate", NormalDrop.nDropChance);

    READ_INT("BossCount1", nBossCount[0]);
    READ_INT("BossGroupID1", BossDrop[0].nDropGroupID);
    pData->BossDrop[0].nDropChance = 1000000;
    READ_INT("BossCount2", nBossCount[1]);
    READ_INT("BossGroupID2", BossDrop[1].nDropGroupID);
    pData->BossDrop[1].nDropChance = 1000000;
    READ_INT("BossCount3", nBossCount[2]);
    READ_INT("BossGroupID3", BossDrop[2].nDropGroupID);
    pData->BossDrop[2].nDropChance = 1000000;
    READ_INT("BossCount4", nBossCount[3]);
    READ_INT("BossGroupID4", BossDrop[3].nDropGroupID);
    pData->BossDrop[3].nDropChance = 1000000;

    READ_INT("WorldCount", nWorldCount);
    READ_INT("WorldGroup", WorldDrop.nDropGroupID);
    pData->WorldDrop.nDropChance = 1000000;

    READ_INT("WorldGroupPos", nWorldGroupPos);
    READ_INT("L1ModL0", nL1ModL0);
    READ_INT("L2ModL0", nL2ModL0);
    READ_INT("L2ModL1", nL2ModL1);

    pData->nGambleKey = MakeKey(pData->nGambleType, pData->nGambleLevel);

    READ_END(nGambleKey);
}
