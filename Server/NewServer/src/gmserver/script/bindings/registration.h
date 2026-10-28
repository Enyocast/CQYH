#pragma once

struct lua_State;

namespace cqyh::gmserver::bindings {
void register_error_definitions(lua_State* L);
void register_item_definitions(lua_State* L);
}
