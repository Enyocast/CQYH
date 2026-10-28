#include "stdafx.h"
#include "bindings/registration.h"

int sol_enum_module_open(lua_State* L)
{
    cqyh::gen_msg::bindings::register_error_definitions(L);
    cqyh::gen_msg::bindings::register_id_definitions(L);
    cqyh::gen_msg::bindings::register_variable_definitions(L);
    cqyh::gen_msg::bindings::register_npc_definitions(L);
    cqyh::gen_msg::bindings::register_role_definitions(L);
    cqyh::gen_msg::bindings::register_doodad_definitions(L);
    cqyh::gen_msg::bindings::register_char_definitions(L);
    cqyh::gen_msg::bindings::register_missile_definitions(L);
    cqyh::gen_msg::bindings::register_grid_definitions(L);
    cqyh::gen_msg::bindings::register_scene_definitions(L);
    cqyh::gen_msg::bindings::register_scene_file_definitions(L);
    cqyh::gen_msg::bindings::register_attribute_definitions(L);
    cqyh::gen_msg::bindings::register_spell_definitions(L);
    cqyh::gen_msg::bindings::register_aura_definitions(L);
    cqyh::gen_msg::bindings::register_ai_definitions(L);
    cqyh::gen_msg::bindings::register_chat_definitions(L);
    cqyh::gen_msg::bindings::register_friend_definitions(L);
    cqyh::gen_msg::bindings::register_item_definitions(L);
    cqyh::gen_msg::bindings::register_money_definitions(L);
    cqyh::gen_msg::bindings::register_quest_definitions(L);
    cqyh::gen_msg::bindings::register_team_definitions(L);
    cqyh::gen_msg::bindings::register_achievement_definitions(L);
    cqyh::gen_msg::bindings::register_master_definitions(L);
    cqyh::gen_msg::bindings::register_queue_match_definitions(L);
    cqyh::gen_msg::bindings::register_guild_definitions(L);
    cqyh::gen_msg::bindings::register_modifier_definitions(L);
    return 1;
}
