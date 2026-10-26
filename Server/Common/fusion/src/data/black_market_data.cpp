#include "stdafx.h"
#include "black_market_data.h"

BOOL BLACK_MARKET_DATA::ReadLine(INT32& rnID, const char*& rpcszName, BLACK_MARKET_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("BlackMarketProductID", nBMProductID);
    READ_INT("BlackMarketID", nBMID);
    READ_INT("ItemID", nItemID);
    READ_INT("Price", nPrice);
    READ_INT("LimitType", nLimitType);
    READ_INT("Limit", nLimit);
    READ_INT("LimitRefreshTime", dwRefreshTime);
    READ_INT("CooldownTime", dwCooldownTime);

    READ_END(nBMProductID);
}
