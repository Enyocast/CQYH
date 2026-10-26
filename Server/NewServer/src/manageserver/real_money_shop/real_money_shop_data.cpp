#include "stdafx.h"
#include "real_money_shop_data.h"
#include "read_data_helper.h"

BOOL REAL_MONEY_SHOP_DATA::ReadLine(INT32& rnID, const char*& rpcszName, REAL_MONEY_SHOP_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("ItemID", m_nItemTemplateID);
    READ_INT("ItemCount", m_shItemCount);
    READ_INT("Page", m_byPage);
    READ_INT("Flag", m_byFlag);
    READ_INT("CurrentPrice", m_nCurrentPrice);
    READ_INT("OriginalPrice", m_nOriginalPrice);
    READ_INT("RenQi", m_nRenQi);

    READ_END(m_nItemTemplateID);
}
