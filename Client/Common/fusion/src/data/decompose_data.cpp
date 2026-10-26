#include "stdafx.h"
#include "decompose_data.h"

BOOL DECOMPOSE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, DECOMPOSE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();
    char szFieldName[256];

    READ_INT("ItemTemplateID", m_nTemplateID);

    for (INT32 i=0; i<MAX_DECOMPOSE_ITEM_COUNT; i++)
    {
        snprintf(szFieldName, 256, "DropChance%d", i + 1);
        READ_INT(szFieldName, m_data[i].nDropChance);

        snprintf(szFieldName, 256, "DropGroupID%d", i + 1);
        READ_INT(szFieldName, m_data[i].nDropGroupID);
    }

    READ_END(m_nTemplateID);
}
