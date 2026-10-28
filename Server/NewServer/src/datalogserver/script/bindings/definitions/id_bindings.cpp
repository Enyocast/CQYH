#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/id_def.h"

namespace cqyh::datalogserver::bindings {

void register_id_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["INVALID_OBJECT_ID"] = static_cast<lua_Number>(INVALID_OBJECT_ID);
    globals["OBJECT_TYPE_MASK"] = static_cast<lua_Number>(OBJECT_TYPE_MASK);
    globals["OBJECT_ID_MASK"] = static_cast<lua_Number>(OBJECT_ID_MASK);
    globals["MAX_OBJECT_ID"] = static_cast<lua_Number>(MAX_OBJECT_ID);
    sol::table object_type_namespace = globals["OBJECT_TYPE"].get_or_create<sol::table>();
    object_type_namespace["otInvalid"] = static_cast<lua_Number>(otInvalid);
    object_type_namespace["otRole"] = static_cast<lua_Number>(otRole);
    object_type_namespace["otNpc"] = static_cast<lua_Number>(otNpc);
    object_type_namespace["otHero"] = static_cast<lua_Number>(otHero);
    object_type_namespace["otDoodad"] = static_cast<lua_Number>(otDoodad);
    object_type_namespace["otMissile"] = static_cast<lua_Number>(otMissile);
    object_type_namespace["otDrop"] = static_cast<lua_Number>(otDrop);
    object_type_namespace["otGuild"] = static_cast<lua_Number>(otGuild);
    object_type_namespace["otTeam"] = static_cast<lua_Number>(otTeam);
    object_type_namespace["otBattleTeam"] = static_cast<lua_Number>(otBattleTeam);
    object_type_namespace["otChannel"] = static_cast<lua_Number>(otChannel);
    object_type_namespace["otTrumpet"] = static_cast<lua_Number>(otTrumpet);
    object_type_namespace["otTotal"] = static_cast<lua_Number>(otTotal);
    globals.set_function("MakeObjectID", [](unsigned int dwType, unsigned int dwIndex) -> decltype(auto) { return MakeObjectID(dwType,dwIndex); });
    globals.set_function("GetTypeFromID", [](unsigned int dwObjID) -> decltype(auto) { return GetTypeFromID(dwObjID); });
    globals.set_function("GetIndexFromID", [](unsigned int dwObjID) -> decltype(auto) { return GetIndexFromID(dwObjID); });
}

}
