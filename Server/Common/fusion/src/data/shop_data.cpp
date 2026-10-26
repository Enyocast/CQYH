#include "stdafx.h"
#include "shop_data.h"
#include "item_data.h"
#include "money_def.h"
#include "npc_def.h"

BOOL SHOP_DATA::ReadLine(INT32& rnID, const char*& rpcszName, SHOP_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("ShopID", m_nShopID);
    READ_INT("Index", m_nIndex);
    READ_STR("ShopName", m_szShopName);
    READ_INT("ItemID", m_nItemID);
    READ_INT("ItemCount", m_nItemCount);

    READ_INT_EXPR("CostItemID1", m_nCostItemID1);
    READ_INT("CostValue1", m_nCostValue1);
    LOG_PROCESS_ERROR((pData->m_nCostItemID1 > MONEYTYPE_INVALID && pData->m_nCostItemID1 < MONEYTYPE_COUNT && pData->m_nCostValue1 > 0) || pData->m_nShopID == 0);

    READ_INT_EXPR("CostItemID2", m_nCostItemID2);
    READ_INT("CostValue2", m_nCostValue2);
    LOG_PROCESS_ERROR((pData->m_nCostItemID2 > MONEYTYPE_INVALID && pData->m_nCostItemID2 < MONEYTYPE_COUNT && pData->m_nCostValue2 > 0) || pData->m_nCostItemID2 == MONEYTYPE_INVALID);

    READ_INT("RequireForceID", m_nRequireForceID);
    LOG_PROCESS_ERROR(pData->m_nRequireForceID >= INVALID_FORCE_ID);
    READ_INT("Reputation", m_nReputation);

    READ_INT("RequireGuildBuildingID", m_nRequireGuildBuildingID);
    READ_INT("BuildingLevel", m_nBuildingLevel);
    READ_INT("ShopTypeSell", m_nShopTypeSell);

    rnID = MAKELONG(pData->m_nShopID, pData->m_nIndex);
    return TRUE;

Exit0:
    rnID = MAKELONG(pData->m_nShopID, pData->m_nIndex);
    return FALSE;
}
