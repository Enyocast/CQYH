#include "stdafx.h"
#include "compose_data.h"

BOOL COMPOSE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, COMPOSE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();
    char szFieldName[256];

    READ_INT("FormulaID", m_nFormulaID);
    READ_INT("ResultItem", m_nItemID);
    READ_INT("DoubleRate", m_dwDoubleRate);
    READ_INT("Money", m_nMoney);
    READ_INT("BroadCast", m_nBroadCast);

    for (INT32 i=0; i<MAX_COMPOSE_ITEM_COUNT; i++)
    {
        snprintf(szFieldName, 256, "ItemID%d", i + 1);
        READ_INT(szFieldName, m_nRequireItemID[i]);

        snprintf(szFieldName, 256, "ItemCount%d", i + 1);
        READ_INT(szFieldName, m_nRequireItemCount[i]);
    }

    READ_END(m_nFormulaID);
}
