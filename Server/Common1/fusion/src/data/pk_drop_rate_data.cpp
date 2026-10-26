#include "stdafx.h"
#include "pk_drop_rate_data.h"

BOOL PK_DROP_RATE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, PK_DROP_RATE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT_EXPR("ItemColor", m_dwItemColor);
    READ_INT("IsWeapon", m_dwIsWeapon);
    READ_INT("KilledByPlayer", m_dwKilledByPlayer);
    READ_INT("DropRateWhite", m_dwDropRate[rncWhite]);
    READ_INT("DropRateYellow", m_dwDropRate[rncYellow]);
    READ_INT("DropRateRed", m_dwDropRate[rncRed]);

    rnID = MakeKey(pData->m_dwItemColor, pData->m_dwIsWeapon, pData->m_dwKilledByPlayer);
    return TRUE;

Exit0:
    rnID = MakeKey(pData->m_dwItemColor, pData->m_dwIsWeapon, pData->m_dwKilledByPlayer);
    return FALSE;
}
