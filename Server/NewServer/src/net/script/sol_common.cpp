#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"

int sol_common_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    return 1;
}
