# fusion - translated from fusion.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_library(fusion STATIC
    src/data/achievement_data.cpp
    src/data/activity_reward_data.cpp
    src/data/adventure_data.cpp
    src/data/ai_data.cpp
    src/data/attr_conversion_data.cpp
    src/data/attribute_data.cpp
    src/data/attribute_pool_data.cpp
    src/data/aura_data.cpp
    src/data/black_market_data.cpp
    src/data/checkin_data.cpp
    src/data/circle_quest_data.cpp
    src/data/compose_data.cpp
    src/data/decompose_data.cpp
    src/data/doodad_data.cpp
    src/data/drop_group_data.cpp
    src/data/dungeon_data.cpp
    src/data/gamble_data.cpp
    src/data/gm_log_note.cpp
    src/data/guild_achievement_cdtn.cpp
    src/data/guild_achievement.cpp
    src/data/guild_activity.cpp
    src/data/guild_building_data.cpp
    src/data/guild_dungeon_data.cpp
    src/data/guild_welfare_data.cpp
    src/data/hero_attr_data.cpp
    src/data/init_reputation_data.cpp
    src/data/item_data.cpp
    src/data/level_damage_mod_data.cpp
    src/data/level_data.cpp
    src/data/mail_template_data.cpp
    src/data/master_gift.cpp
    src/data/missile_data.cpp
    src/data/money_data.cpp
    src/data/mount_data.cpp
    src/data/npc_data.cpp
    src/data/npc_relation_data.cpp
    src/data/pk_drop_count_data.cpp
    src/data/pk_drop_rate_data.cpp
    src/data/quest_data.cpp
    src/data/refine_data.cpp
    src/data/role_relation_data.cpp
    src/data/rune_data.cpp
    src/data/scene_data.cpp
    src/data/set_data.cpp
    src/data/shop_data.cpp
    src/data/soul_data.cpp
    src/data/spell_data.cpp
    src/data/spirit_data.cpp
    src/data/title_data.cpp
    src/enum_string.cpp
    src/fusion.cpp
    src/global_config.cpp
    src/global_data_manager.cpp
    src/kill_npc_quest_data.cpp
    src/npc_pattern.cpp
    src/pet_data.cpp
    src/read_data_helper.cpp
    src/role_db_base_data_conv.cpp
    src/script/tolua_common.cpp
    src/script/tolua_data_manager.cpp
    src/script/tolua_enum.cpp
    src/script/tolua_enumstr.cpp
    src/script/tolua_global_config.cpp
    src/script/tolua_guild_config.cpp
    src/script/tolua_guild_def.cpp
    src/script/tolua_string_table.cpp
    src/stdafx.cpp
)

cqyh_target_defaults(fusion)
cqyh_use_pch(fusion ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(fusion PRIVATE
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/3rd/lua/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
    ${CQYH_SERVER_DIR}/NewServer/3rd/toluapp/include
)

