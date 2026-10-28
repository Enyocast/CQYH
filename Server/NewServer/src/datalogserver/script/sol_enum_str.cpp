#include "stdafx.h"
#include "bindings/registration.h"

int sol_enum_str_open(lua_State* L)
{
    cqyh::datalogserver::bindings::register_item_definitions(L);
    cqyh::datalogserver::bindings::register_char_definitions(L);
    cqyh::datalogserver::bindings::register_id_definitions(L);
    cqyh::datalogserver::bindings::register_quest_definitions(L);
    cqyh::datalogserver::bindings::register_guild_definitions(L);
    return 1;
}
