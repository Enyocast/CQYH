#include "stdafx.h"
#include "level_damage_mod_data.h"

BOOL LEVEL_DAMAGE_MOD_DATA::ReadLine(INT32& rnID, const char*& rpcszName, LEVEL_DAMAGE_MOD_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("RoleLevel", nRoleLevel);

    for (INT32 nIndex = 1; nIndex <= MAX_NPC_LEVEL; nIndex++)
    {
		char szField[8] = { 0 };
		sprintf(szField, "%d", nIndex);
        READ_INT(szField, nModData[nIndex]);
    }

    READ_END(nRoleLevel);
}
