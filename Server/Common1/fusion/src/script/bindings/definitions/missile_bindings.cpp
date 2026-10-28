#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/missile_def.h"

namespace cqyh::fusion::bindings {

void register_missile_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["mmtInvalid"] = static_cast<lua_Number>(mmtInvalid);
    globals["mmtLine"] = static_cast<lua_Number>(mmtLine);
    globals["mmtAccordingToTerrain"] = static_cast<lua_Number>(mmtAccordingToTerrain);
    globals["mmtStatic"] = static_cast<lua_Number>(mmtStatic);
    globals["mmtLockTarget"] = static_cast<lua_Number>(mmtLockTarget);
    globals["mmtTotal"] = static_cast<lua_Number>(mmtTotal);
    globals["mcgRole"] = static_cast<lua_Number>(mcgRole);
    globals["mcgNpc"] = static_cast<lua_Number>(mcgNpc);
    globals["mcgDoodad"] = static_cast<lua_Number>(mcgDoodad);
    globals["mltInvalid"] = static_cast<lua_Number>(mltInvalid);
    globals["mltSelf"] = static_cast<lua_Number>(mltSelf);
    globals["mltObject"] = static_cast<lua_Number>(mltObject);
    globals["mltPos"] = static_cast<lua_Number>(mltPos);
    globals["mltTotal"] = static_cast<lua_Number>(mltTotal);
}

}
