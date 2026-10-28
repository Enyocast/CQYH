#include "stdafx.h"
#include "bindings/registration.h"

int sol_attribute_def_open(lua_State* L)
{
    cqyh::gameworld::bindings::register_attribute_definitions(L);
    cqyh::gameworld::bindings::register_role_definitions(L);
    cqyh::gameworld::bindings::register_modifier_definitions(L);
    return 1;
}
