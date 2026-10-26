#ifndef _COMPOSE_DATA_H_
#define _COMPOSE_DATA_H_

#include "item_def.h"
#include "data_manager.h"

struct COMPOSE_DATA
{
    INT32 m_nFormulaID;
    INT32 m_nItemID;
    UINT32 m_dwDoubleRate;
    INT32 m_nMoney;
    BOOL m_nBroadCast;
    INT32 m_nRequireItemID[MAX_COMPOSE_ITEM_COUNT];
    INT32 m_nRequireItemCount[MAX_COMPOSE_ITEM_COUNT];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, COMPOSE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


#endif // _COMPOSE_DATA_H_