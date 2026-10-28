#include "stdafx.h"
#include "bindings/registration.h"

int sol_global_config_open(lua_State* L)
{
    cqyh::fusion::bindings::register_error_definitions(L);
    cqyh::fusion::bindings::register_id_definitions(L);
    cqyh::fusion::bindings::register_server_definitions(L);
    cqyh::fusion::bindings::register_npc_definitions(L);
    cqyh::fusion::bindings::register_role_definitions(L);
    cqyh::fusion::bindings::register_doodad_definitions(L);
    cqyh::fusion::bindings::register_char_definitions(L);
    cqyh::fusion::bindings::register_missile_definitions(L);
    cqyh::fusion::bindings::register_grid_definitions(L);
    cqyh::fusion::bindings::register_scene_definitions(L);
    cqyh::fusion::bindings::register_scene_file_definitions(L);
    cqyh::fusion::bindings::register_attribute_definitions(L);
    cqyh::fusion::bindings::register_modifier_definitions(L);
    cqyh::fusion::bindings::register_spell_definitions(L);
    cqyh::fusion::bindings::register_aura_definitions(L);
    cqyh::fusion::bindings::register_ai_definitions(L);
    cqyh::fusion::bindings::register_chat_definitions(L);
    cqyh::fusion::bindings::register_friend_definitions(L);
    cqyh::fusion::bindings::register_item_definitions(L);
    cqyh::fusion::bindings::register_money_definitions(L);
    cqyh::fusion::bindings::register_quest_definitions(L);
    cqyh::fusion::bindings::register_team_definitions(L);
    cqyh::fusion::bindings::register_adventure_definitions(L);
    cqyh::fusion::bindings::register_achievement_definitions(L);
    cqyh::fusion::bindings::register_master_definitions(L);
    cqyh::fusion::bindings::register_queue_match_definitions(L);
    cqyh::fusion::bindings::register_variable_definitions(L);
    cqyh::fusion::bindings::register_guild_definitions(L);
    cqyh::fusion::bindings::register_gm_svr_definitions(L);
    cqyh::fusion::bindings::register_log_bindings(L);
    cqyh::fusion::bindings::register_global_bindings(L);
    cqyh::fusion::bindings::register_asimov_bindings(L);
    cqyh::fusion::bindings::register_game_world_bindings(L);
    cqyh::fusion::bindings::register_guild_bindings(L);
    cqyh::fusion::bindings::register_new_role_bindings(L);
    cqyh::fusion::bindings::register_obj_pool_bindings(L);
    cqyh::fusion::bindings::register_server_bindings(L);
    cqyh::fusion::bindings::register_mt_bindings(L);
    cqyh::fusion::bindings::register_guard_bindings(L);
    return 1;
}
