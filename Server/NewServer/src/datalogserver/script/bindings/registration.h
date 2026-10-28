#pragma once

struct lua_State;

namespace cqyh::datalogserver::bindings {
void register_item_definitions(lua_State* L);
void register_char_definitions(lua_State* L);
void register_id_definitions(lua_State* L);
void register_quest_definitions(lua_State* L);
void register_guild_definitions(lua_State* L);
}
