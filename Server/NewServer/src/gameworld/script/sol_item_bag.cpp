#include "stdafx.h"
#include "bindings/registration.h"

int sol_item_bag_open(lua_State* L)
{
    cqyh::gameworld::bindings::register_item_definitions(L);
    cqyh::gameworld::bindings::register_item_bag_bindings(L);
    cqyh::gameworld::bindings::register_item_mgr_bindings(L);
    return 1;
}
