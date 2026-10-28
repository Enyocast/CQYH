#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/id_def.h"

namespace cqyh::fusion::bindings {

void register_id_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["INVALID_OBJECT_ID"] = static_cast<lua_Number>(INVALID_OBJECT_ID);
    globals["OBJECT_TYPE_MASK"] = static_cast<lua_Number>(OBJECT_TYPE_MASK);
    globals["OBJECT_ID_MASK"] = static_cast<lua_Number>(OBJECT_ID_MASK);
    globals["MAX_OBJECT_ID"] = static_cast<lua_Number>(MAX_OBJECT_ID);
    globals["otInvalid"] = static_cast<lua_Number>(otInvalid);
    globals["otRole"] = static_cast<lua_Number>(otRole);
    globals["otNpc"] = static_cast<lua_Number>(otNpc);
    globals["otHero"] = static_cast<lua_Number>(otHero);
    globals["otDoodad"] = static_cast<lua_Number>(otDoodad);
    globals["otMissile"] = static_cast<lua_Number>(otMissile);
    globals["otDrop"] = static_cast<lua_Number>(otDrop);
    globals["otGuild"] = static_cast<lua_Number>(otGuild);
    globals["otTeam"] = static_cast<lua_Number>(otTeam);
    globals["otBattleTeam"] = static_cast<lua_Number>(otBattleTeam);
    globals["otChannel"] = static_cast<lua_Number>(otChannel);
    globals["otTrumpet"] = static_cast<lua_Number>(otTrumpet);
    globals["otTotal"] = static_cast<lua_Number>(otTotal);
    globals.set_function("MakeObjectID", [](unsigned int dwType, unsigned int dwIndex) -> decltype(auto) { return MakeObjectID(dwType,dwIndex); });
    globals.set_function("GetTypeFromID", [](unsigned int dwObjID) -> decltype(auto) { return GetTypeFromID(dwObjID); });
    globals.set_function("GetIndexFromID", [](unsigned int dwObjID) -> decltype(auto) { return GetIndexFromID(dwObjID); });
}

}
