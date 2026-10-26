#ifndef _REAL_MONEY_SHOP_DATA_H_
#define _REAL_MONEY_SHOP_DATA_H_

#include "data_manager.h"

struct REAL_MONEY_SHOP_DATA
{
    INT32   m_nItemTemplateID;
    INT16   m_shItemCount;
    UINT8   m_byPage;
    UINT8   m_byFlag;
    INT32   m_nCurrentPrice;
    INT32   m_nOriginalPrice;
    INT32   m_nRenQi;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, REAL_MONEY_SHOP_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


#endif // _REAL_MONEY_SHOP_DATA_H_
