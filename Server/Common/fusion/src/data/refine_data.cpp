#include "stdafx.h"
#include "refine_data.h"

BOOL REFINE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, REFINE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

	memset(pData, 0, sizeof(REFINE_DATA));

    READ_INT("RefineLevel", m_nRefineLevel);
    READ_INT("RequireLevel", m_nRequireLevel);
    READ_INT("SuccessRate", m_dwSuccessRate);
    READ_INT("BasePow", m_nBasePow);
    READ_INT("Cost", m_nCost);
    READ_INT("BroadCast", m_nBroadCast);

    READ_END(m_nRefineLevel);
}

BOOL REFINE_ATTR_DATA::ReadLine(INT32& rnID, const char*& rpcszName, REFINE_ATTR_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    memset(pData, 0, sizeof(REFINE_ATTR_DATA));

    READ_INT("RefineLevel", m_wRefineLevel);
    READ_INT_EXPR("Class", m_byClass);
    READ_INT_EXPR("NormalEquipSlot", m_byEquipSlot);

    for (INT32 i=0; i<MAX_REFINE_ATTR_COUNT; i++)
    {
        char szColumn[256];
        snprintf(szColumn, 256, "Attr%d", i+1);
        READ_INT_EXPR(szColumn, m_nAttrID[i]);
    }

    pData->m_nRefineKey = MakeKey(pData->m_wRefineLevel, pData->m_byClass, pData->m_byEquipSlot);

    READ_END(m_nRefineKey);
}
