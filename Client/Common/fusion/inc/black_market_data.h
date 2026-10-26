#ifndef _BLACK_MARKET_DATA_H_
#define _BLACK_MARKET_DATA_H_

#include "data_manager.h"

struct BLACK_MARKET_DATA
{
    INT32 nBMProductID;
    INT32 nBMID;
    INT32 nItemID;
    INT32 nPrice;
    INT32 nLimitType;
    INT32 nLimit;
    UINT32 dwRefreshTime;
    UINT32 dwCooldownTime;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, BLACK_MARKET_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


#endif // _BLACK_MARKET_DATA_H_
