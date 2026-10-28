#include "stdafx.h"
#include "sol_bindings.h"

int sol_asimov_common_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    return 1;
}
