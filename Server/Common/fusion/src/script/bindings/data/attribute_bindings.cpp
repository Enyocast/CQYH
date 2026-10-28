#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"
#include "../../../../inc/attribute_data.h"

namespace cqyh::fusion::bindings {

void register_attribute_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto attribute_data_type = cqyh::lua::usertype<ATTRIBUTE_DATA>(L, globals, "ATTRIBUTE_DATA", "ATTRIBUTE_DATA");
}

}
