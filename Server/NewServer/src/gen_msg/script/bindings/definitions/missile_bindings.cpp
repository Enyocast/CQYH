#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/missile_def.h"

namespace cqyh::gen_msg::bindings {

void register_missile_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table missile_move_type_namespace = globals["MISSILE_MOVE_TYPE"].get_or_create<sol::table>();
    missile_move_type_namespace["mmtInvalid"] = static_cast<lua_Number>(mmtInvalid);
    missile_move_type_namespace["mmtLine"] = static_cast<lua_Number>(mmtLine);
    missile_move_type_namespace["mmtAccordingToTerrain"] = static_cast<lua_Number>(mmtAccordingToTerrain);
    missile_move_type_namespace["mmtStatic"] = static_cast<lua_Number>(mmtStatic);
    missile_move_type_namespace["mmtLockTarget"] = static_cast<lua_Number>(mmtLockTarget);
    missile_move_type_namespace["mmtTotal"] = static_cast<lua_Number>(mmtTotal);
    sol::table missile_collision_group_namespace = globals["MISSILE_COLLISION_GROUP"].get_or_create<sol::table>();
    missile_collision_group_namespace["mcgRole"] = static_cast<lua_Number>(mcgRole);
    missile_collision_group_namespace["mcgNpc"] = static_cast<lua_Number>(mcgNpc);
    missile_collision_group_namespace["mcgDoodad"] = static_cast<lua_Number>(mcgDoodad);
    sol::table missile_lock_type_namespace = globals["MISSILE_LOCK_TYPE"].get_or_create<sol::table>();
    missile_lock_type_namespace["mltInvalid"] = static_cast<lua_Number>(mltInvalid);
    missile_lock_type_namespace["mltSelf"] = static_cast<lua_Number>(mltSelf);
    missile_lock_type_namespace["mltObject"] = static_cast<lua_Number>(mltObject);
    missile_lock_type_namespace["mltPos"] = static_cast<lua_Number>(mltPos);
    missile_lock_type_namespace["mltTotal"] = static_cast<lua_Number>(mltTotal);
}

}
