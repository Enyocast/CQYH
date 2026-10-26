#ifndef level_damage_mod_data_h__
#define level_damage_mod_data_h__

#include "data_manager.h"
#include "npc_def.h"

//tolua_begin
struct LEVEL_DAMAGE_MOD_DATA
{
	INT32 nRoleLevel;
    INT32 nModData[MAX_NPC_LEVEL + 1];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, LEVEL_DAMAGE_MOD_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};
//tolua_end

#endif // level_damage_mod_data_h__
