#ifndef _PK_DROP_COUNT_DATA_H_
#define _PK_DROP_COUNT_DATA_H_

#include "data_manager.h"
#include "role_def.h"

struct PK_DROP_COUNT_DATA
{
    INT32 m_nLevel;
    INT32 m_nMaxDropCount[3][rncTotal];    //Drop limits: the first dimension represents ordinary inventory items, valuable inventory items, and equipped items; the second represents white, yellow, and red names
    INT32 m_nProtectTime;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, PK_DROP_COUNT_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


#endif // _PK_DROP_COUNT_DATA_H_
