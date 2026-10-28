#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "math_ex.h"

int sol_math_ex_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_DIRECTION_COUNT"] = static_cast<lua_Number>(MAX_DIRECTION_COUNT);
    globals["SIN_COS_NUMBER"] = static_cast<lua_Number>(SIN_COS_NUMBER);
    return 1;
}
