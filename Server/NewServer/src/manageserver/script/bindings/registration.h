#pragma once

struct lua_State;

namespace cqyh::manageserver::bindings {
void register_error_definitions(lua_State* L);
}
