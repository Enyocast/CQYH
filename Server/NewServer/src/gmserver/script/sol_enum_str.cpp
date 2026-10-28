#include "stdafx.h"
#include "bindings/registration.h"

int sol_enum_str_open(lua_State* L)
{
    cqyh::gmserver::bindings::register_error_definitions(L);
    cqyh::gmserver::bindings::register_item_definitions(L);
    return 1;
}
