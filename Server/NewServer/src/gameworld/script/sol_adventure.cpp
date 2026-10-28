#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../common/define/adventure_def.h"

int sol_adventure_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_ADVENTURE_TRIGGER_PARAM"] = static_cast<lua_Number>(MAX_ADVENTURE_TRIGGER_PARAM);
    globals["MAX_ADVENTURE_REWARD_PARAM"] = static_cast<lua_Number>(MAX_ADVENTURE_REWARD_PARAM);
    globals["attInvalid"] = static_cast<lua_Number>(attInvalid);
    globals["attKillNpc"] = static_cast<lua_Number>(attKillNpc);
    globals["attDestoryDoodad"] = static_cast<lua_Number>(attDestoryDoodad);
    globals["attRefineEquip"] = static_cast<lua_Number>(attRefineEquip);
    globals["attAddSoul"] = static_cast<lua_Number>(attAddSoul);
    globals["attRandomizeEquip"] = static_cast<lua_Number>(attRandomizeEquip);
    globals["att5MinOnlineTime"] = static_cast<lua_Number>(att5MinOnlineTime);
    globals["attServerTime"] = static_cast<lua_Number>(attServerTime);
    globals["attTotal"] = static_cast<lua_Number>(attTotal);
    globals["adrInvalid"] = static_cast<lua_Number>(adrInvalid);
    globals["adrSpawnNpcAtPoint"] = static_cast<lua_Number>(adrSpawnNpcAtPoint);
    globals["adrSpawnNpcNearby"] = static_cast<lua_Number>(adrSpawnNpcNearby);
    globals["adrSpawnNpcSurround"] = static_cast<lua_Number>(adrSpawnNpcSurround);
    globals["adrSpawnDoodadAtPoint"] = static_cast<lua_Number>(adrSpawnDoodadAtPoint);
    globals["adrSpawnDoodadNearby"] = static_cast<lua_Number>(adrSpawnDoodadNearby);
    globals["adrSendMail"] = static_cast<lua_Number>(adrSendMail);
    globals["adrTotal"] = static_cast<lua_Number>(adrTotal);
    return 1;
}
