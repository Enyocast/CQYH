#include "stdafx.h"
#include "role_relation_data.h"
#include "script_mgr.h"


BOOL ROLE_RELATION_DATA::ReadLine(INT32& rnID, const char*& rpcszName, ROLE_RELATION_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("FractionID", nFactionID);
    for (INT32 nIndex = 0; nIndex < MAX_ROLE_FRACTION_ID; nIndex++)
    {
        char szField[256];
        snprintf(szField, 256, "%d", nIndex);
        READ_INT(szField, nRelation[nIndex]);
    }

    READ_END(nFactionID);
}
