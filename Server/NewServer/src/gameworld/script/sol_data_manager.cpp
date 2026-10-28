#include "stdafx.h"
#include "bindings/registration.h"

int sol_data_manager_open(lua_State* L)
{
    cqyh::gameworld::bindings::register_ai_bindings(L);
    cqyh::gameworld::bindings::register_aura_bindings(L);
    cqyh::gameworld::bindings::register_doodad_bindings(L);
    cqyh::gameworld::bindings::register_init_reputation_bindings(L);
    cqyh::gameworld::bindings::register_item_bindings(L);
    cqyh::gameworld::bindings::register_level_bindings(L);
    cqyh::gameworld::bindings::register_missile_bindings(L);
    cqyh::gameworld::bindings::register_npc_bindings(L);
    cqyh::gameworld::bindings::register_npc_relation_bindings(L);
    cqyh::gameworld::bindings::register_quest_bindings(L);
    cqyh::gameworld::bindings::register_role_relation_bindings(L);
    cqyh::gameworld::bindings::register_scene_bindings(L);
    cqyh::gameworld::bindings::register_shop_bindings(L);
    cqyh::gameworld::bindings::register_attr_conversion_bindings(L);
    cqyh::gameworld::bindings::register_achievement_bindings(L);
    cqyh::gameworld::bindings::register_title_bindings(L);
    cqyh::gameworld::bindings::register_guild_building_bindings(L);
    cqyh::gameworld::bindings::register_guild_activity_bindings(L);
    cqyh::gameworld::bindings::register_attribute_bindings(L);
    cqyh::gameworld::bindings::register_soul_bindings(L);
    cqyh::gameworld::bindings::register_pet_bindings(L);
    cqyh::gameworld::bindings::register_spell_bindings(L);
    return 1;
}
