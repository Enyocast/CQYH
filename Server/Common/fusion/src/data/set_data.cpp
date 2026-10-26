#include "stdafx.h"
#include "set_data.h"
#include "item_data.h"
#include "attribute_data.h"
#include "read_data_helper.h"

BOOL SET_DATA::ReadLine(INT32& rnID, const char*& rpcszName, SET_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    char column_name[COMMON_NAME_LEN];

    READ_START();

    memset(pData, 0, sizeof(SET_DATA));

    READ_INT("SetID", m_nSetID);

    for (INT32 i=0; i<MAX_SET_PART_COUNT; i++)
    {
        snprintf(column_name, COMMON_NAME_LEN, "ItemID%d", i+1);
        READ_INT(column_name, m_nItemID[i]);
    }

    for (INT32 i=0; i<MAX_SET_ATTR_COUNT; i++)
    {
        snprintf(column_name, COMMON_NAME_LEN, "Count%d", i+1);
        READ_INT(column_name, m_nCount[i]);

        snprintf(column_name, COMMON_NAME_LEN, "Attr%d", i+1);
        READ_INT(column_name, m_nAttrID[i]);
    }

    READ_END(m_nSetID);
}
