#ifndef _PK_DROP_COUNT_DATA_H_
#define _PK_DROP_COUNT_DATA_H_

#include "data_manager.h"
#include "role_def.h"

struct PK_DROP_COUNT_DATA
{
    INT32 m_nLevel;
    INT32 m_nMaxDropCount[3][rncTotal];    //掉落上限，前一个3表示背包内普通物品，背包内贵重物品，已装备物品；后一个3表示白名，黄名，红名
    INT32 m_nProtectTime;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, PK_DROP_COUNT_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


#endif // _PK_DROP_COUNT_DATA_H_
