#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/baselib/tabfile.h"
#include "../../../../../../Common/fusion/inc/attribute_data.h"

namespace cqyh::gameworld::bindings {

void register_attribute_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto attribute_data_type = cqyh::lua::usertype<ATTRIBUTE_DATA>(L, globals, "ATTRIBUTE_DATA", "ATTRIBUTE_DATA");
}

}
