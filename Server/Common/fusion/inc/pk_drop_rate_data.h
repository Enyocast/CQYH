#ifndef _PK_DROP_COUNT_RATE_H_
#define _PK_DROP_COUNT_RATE_H_

#include "data_manager.h"
#include "role_def.h"

struct PK_DROP_RATE_DATA
{
    UINT32 m_dwItemColor;
    UINT32 m_dwIsWeapon;
    UINT32 m_dwKilledByPlayer;
    UINT32 m_dwDropRate[rncTotal];

    static UINT32 MakeKey(UINT32 dwItemColor, UINT32 dwIsWeapon, UINT32 dwKilledByPlayer) { return dwItemColor << 16 | dwIsWeapon << 8 | dwKilledByPlayer; }
    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, PK_DROP_RATE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _PK_DROP_COUNT_RATE_H_
