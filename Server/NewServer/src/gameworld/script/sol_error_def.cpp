#include "stdafx.h"
#include "bindings/registration.h"

int sol_error_def_open(lua_State* L)
{
    cqyh::gameworld::bindings::register_error_definitions(L);
    return 1;
}
