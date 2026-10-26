#include "stdafx.h"
#include "npc_relation_data.h"
#include "script_mgr.h"


BOOL NPC_RELATION_DATA::ReadLine(INT32& rnID, const char*& rpcszName, NPC_RELATION_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("ForceID", nForceID);
    for (INT32 nIndex = 0; nIndex < MAX_NPC_FORCE_ID; nIndex++)
    {
        char szField[256];
        snprintf(szField, 256, "%d", nIndex);
        READ_INT(szField, nRelation[nIndex]);
    }

    READ_END(nForceID);
}
