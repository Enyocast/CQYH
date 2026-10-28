#pragma once

struct lua_State;

namespace cqyh::fusion::bindings {
void register_error_definitions(lua_State* L);
void register_id_definitions(lua_State* L);
void register_server_definitions(lua_State* L);
void register_npc_definitions(lua_State* L);
void register_role_definitions(lua_State* L);
void register_doodad_definitions(lua_State* L);
void register_char_definitions(lua_State* L);
void register_missile_definitions(lua_State* L);
void register_grid_definitions(lua_State* L);
void register_scene_definitions(lua_State* L);
void register_scene_file_definitions(lua_State* L);
void register_attribute_definitions(lua_State* L);
void register_modifier_definitions(lua_State* L);
void register_spell_definitions(lua_State* L);
void register_aura_definitions(lua_State* L);
void register_ai_definitions(lua_State* L);
void register_chat_definitions(lua_State* L);
void register_friend_definitions(lua_State* L);
void register_item_definitions(lua_State* L);
void register_money_definitions(lua_State* L);
void register_quest_definitions(lua_State* L);
void register_team_definitions(lua_State* L);
void register_adventure_definitions(lua_State* L);
void register_achievement_definitions(lua_State* L);
void register_master_definitions(lua_State* L);
void register_queue_match_definitions(lua_State* L);
void register_variable_definitions(lua_State* L);
void register_guild_definitions(lua_State* L);
void register_gm_svr_definitions(lua_State* L);
void register_log_bindings(lua_State* L);
void register_global_bindings(lua_State* L);
void register_asimov_bindings(lua_State* L);
void register_game_world_bindings(lua_State* L);
void register_guild_bindings(lua_State* L);
void register_new_role_bindings(lua_State* L);
void register_obj_pool_bindings(lua_State* L);
void register_server_bindings(lua_State* L);
void register_mt_bindings(lua_State* L);
void register_guard_bindings(lua_State* L);
}
