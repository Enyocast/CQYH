#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/scene_def.h"
#include "../../../../../../Common/define/scene_file_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::gen_msg::bindings {

void register_scene_file_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table server_point_type_namespace = globals["SERVER_POINT_TYPE"].get_or_create<sol::table>();
    server_point_type_namespace["sptInvalid"] = static_cast<lua_Number>(sptInvalid);
    server_point_type_namespace["sptCustom"] = static_cast<lua_Number>(sptCustom);
    server_point_type_namespace["sptRevive"] = static_cast<lua_Number>(sptRevive);
    server_point_type_namespace["sptReplay"] = static_cast<lua_Number>(sptReplay);
    server_point_type_namespace["sptTotal"] = static_cast<lua_Number>(sptTotal);
}

}
