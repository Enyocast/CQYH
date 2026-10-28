#ifndef _SHOP_DATA_H_
#define _SHOP_DATA_H_

#include "data_manager.h"
#include "string_def.h"
struct ITEM_DATA;
struct SHOP_DATA
{
    INT32 m_nShopID;
    INT32 m_nIndex;
    char m_szShopName[SHOP_NAME_LEN];
    INT32 m_nItemID;
    INT32 m_nItemCount;
    INT32 m_nCostItemID1;
    INT32 m_nCostValue1;
    INT32 m_nCostItemID2;
    INT32 m_nCostValue2;
    INT32 m_nRequireForceID;
    INT32 m_nReputation;
    INT32 m_nRequireGuildBuildingID;
    INT32 m_nBuildingLevel;
    INT32 m_nShopTypeSell;

    const ITEM_DATA* m_pItemTemplate;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SHOP_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _SHOP_DATA_H_
