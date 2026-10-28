#pragma once

struct lua_State;

namespace cqyh::gameworld::bindings {
void register_attribute_definitions(lua_State* L);
void register_role_definitions(lua_State* L);
void register_modifier_definitions(lua_State* L);
void register_ai_bindings(lua_State* L);
void register_aura_bindings(lua_State* L);
void register_doodad_bindings(lua_State* L);
void register_init_reputation_bindings(lua_State* L);
void register_item_bindings(lua_State* L);
void register_level_bindings(lua_State* L);
void register_missile_bindings(lua_State* L);
void register_npc_bindings(lua_State* L);
void register_npc_relation_bindings(lua_State* L);
void register_quest_bindings(lua_State* L);
void register_role_relation_bindings(lua_State* L);
void register_scene_bindings(lua_State* L);
void register_shop_bindings(lua_State* L);
void register_attr_conversion_bindings(lua_State* L);
void register_achievement_bindings(lua_State* L);
void register_title_bindings(lua_State* L);
void register_guild_building_bindings(lua_State* L);
void register_guild_activity_bindings(lua_State* L);
void register_attribute_bindings(lua_State* L);
void register_soul_bindings(lua_State* L);
void register_pet_bindings(lua_State* L);
void register_spell_bindings(lua_State* L);
void register_error_definitions(lua_State* L);
void register_item_definitions(lua_State* L);
void register_item_bag_bindings(lua_State* L);
void register_item_mgr_bindings(lua_State* L);
}
