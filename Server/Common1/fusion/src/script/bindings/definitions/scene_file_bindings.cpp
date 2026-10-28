#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/scene_file_def.h"

namespace cqyh::fusion::bindings {

void register_scene_file_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["sptInvalid"] = static_cast<lua_Number>(sptInvalid);
    globals["sptCustom"] = static_cast<lua_Number>(sptCustom);
    globals["sptRevive"] = static_cast<lua_Number>(sptRevive);
    globals["sptReplay"] = static_cast<lua_Number>(sptReplay);
    globals["sptTotal"] = static_cast<lua_Number>(sptTotal);
}

}
