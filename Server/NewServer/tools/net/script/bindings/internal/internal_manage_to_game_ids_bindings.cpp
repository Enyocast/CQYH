#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/m2g_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"
#include "../../../../../../Common/define/variable_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_manage_to_game_ids_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["m2g_begin"] = static_cast<lua_Number>(InternalMessage::m2g_begin);
    internal_message_namespace["m2g_register_ack"] = static_cast<lua_Number>(InternalMessage::m2g_register_ack);
    internal_message_namespace["m2g_sync_rsakey"] = static_cast<lua_Number>(InternalMessage::m2g_sync_rsakey);
    internal_message_namespace["m2g_pre_enter_gs"] = static_cast<lua_Number>(InternalMessage::m2g_pre_enter_gs);
    internal_message_namespace["m2g_enter_gs_ack"] = static_cast<lua_Number>(InternalMessage::m2g_enter_gs_ack);
    internal_message_namespace["m2g_leave_gs"] = static_cast<lua_Number>(InternalMessage::m2g_leave_gs);
    internal_message_namespace["m2g_query_scene_ack"] = static_cast<lua_Number>(InternalMessage::m2g_query_scene_ack);
    internal_message_namespace["m2g_create_scene"] = static_cast<lua_Number>(InternalMessage::m2g_create_scene);
    internal_message_namespace["m2g_destroy_scene"] = static_cast<lua_Number>(InternalMessage::m2g_destroy_scene);
    internal_message_namespace["m2g_close_scene"] = static_cast<lua_Number>(InternalMessage::m2g_close_scene);
    internal_message_namespace["m2g_change_scene"] = static_cast<lua_Number>(InternalMessage::m2g_change_scene);
    internal_message_namespace["m2g_jump_arena_scene"] = static_cast<lua_Number>(InternalMessage::m2g_jump_arena_scene);
    internal_message_namespace["m2g_team_new"] = static_cast<lua_Number>(InternalMessage::m2g_team_new);
    internal_message_namespace["m2g_team_add_member"] = static_cast<lua_Number>(InternalMessage::m2g_team_add_member);
    internal_message_namespace["m2g_team_remove_member"] = static_cast<lua_Number>(InternalMessage::m2g_team_remove_member);
    internal_message_namespace["m2g_team_changeinfo"] = static_cast<lua_Number>(InternalMessage::m2g_team_changeinfo);
    internal_message_namespace["m2g_change_info"] = static_cast<lua_Number>(InternalMessage::m2g_change_info);
    internal_message_namespace["m2g_friend_add"] = static_cast<lua_Number>(InternalMessage::m2g_friend_add);
    internal_message_namespace["m2g_friend_del"] = static_cast<lua_Number>(InternalMessage::m2g_friend_del);
    internal_message_namespace["m2g_room_enter_dungeon"] = static_cast<lua_Number>(InternalMessage::m2g_room_enter_dungeon);
    internal_message_namespace["m2g_mst_submit_teacher_app"] = static_cast<lua_Number>(InternalMessage::m2g_mst_submit_teacher_app);
    internal_message_namespace["m2g_mst_agree_teacher_app"] = static_cast<lua_Number>(InternalMessage::m2g_mst_agree_teacher_app);
    internal_message_namespace["m2g_mst_submit_stud_app"] = static_cast<lua_Number>(InternalMessage::m2g_mst_submit_stud_app);
    internal_message_namespace["m2g_mst_agree_stud_app"] = static_cast<lua_Number>(InternalMessage::m2g_mst_agree_stud_app);
    internal_message_namespace["m2g_mst_cz"] = static_cast<lua_Number>(InternalMessage::m2g_mst_cz);
    internal_message_namespace["m2g_mst_sync_state"] = static_cast<lua_Number>(InternalMessage::m2g_mst_sync_state);
    internal_message_namespace["m2g_mst_sync_data"] = static_cast<lua_Number>(InternalMessage::m2g_mst_sync_data);
    internal_message_namespace["m2g_mst_create_relation_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_mst_create_relation_ntf);
    internal_message_namespace["m2g_mst_del_relation_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_mst_del_relation_ntf);
    internal_message_namespace["m2g_mst_update_data"] = static_cast<lua_Number>(InternalMessage::m2g_mst_update_data);
    internal_message_namespace["m2g_mail_cost_check"] = static_cast<lua_Number>(InternalMessage::m2g_mail_cost_check);
    internal_message_namespace["m2g_mail_get_simple_attach"] = static_cast<lua_Number>(InternalMessage::m2g_mail_get_simple_attach);
    internal_message_namespace["m2g_mail_get_buffer_attach"] = static_cast<lua_Number>(InternalMessage::m2g_mail_get_buffer_attach);
    internal_message_namespace["m2g_call_lua_function"] = static_cast<lua_Number>(InternalMessage::m2g_call_lua_function);
    internal_message_namespace["m2g_join_battle"] = static_cast<lua_Number>(InternalMessage::m2g_join_battle);
    internal_message_namespace["m2g_pre_create_guild"] = static_cast<lua_Number>(InternalMessage::m2g_pre_create_guild);
    internal_message_namespace["m2g_role_add_guild"] = static_cast<lua_Number>(InternalMessage::m2g_role_add_guild);
    internal_message_namespace["m2g_guild_disband"] = static_cast<lua_Number>(InternalMessage::m2g_guild_disband);
    internal_message_namespace["m2g_guild_add_member"] = static_cast<lua_Number>(InternalMessage::m2g_guild_add_member);
    internal_message_namespace["m2g_guild_del_member"] = static_cast<lua_Number>(InternalMessage::m2g_guild_del_member);
    internal_message_namespace["m2g_sync_guild_data_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_sync_guild_data_ntf);
    internal_message_namespace["m2g_guild_sync_attr_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_sync_attr_ntf);
    internal_message_namespace["m2g_guild_sync_variable_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_sync_variable_ntf);
    internal_message_namespace["m2g_guild_draw_salary"] = static_cast<lua_Number>(InternalMessage::m2g_guild_draw_salary);
    internal_message_namespace["m2g_guild_add_diplomat_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_add_diplomat_ntf);
    internal_message_namespace["m2g_guild_del_diplomat_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_del_diplomat_ntf);
    internal_message_namespace["m2g_guild_pre_push_item_ack"] = static_cast<lua_Number>(InternalMessage::m2g_guild_pre_push_item_ack);
    internal_message_namespace["m2g_guild_pre_pop_item_ack"] = static_cast<lua_Number>(InternalMessage::m2g_guild_pre_pop_item_ack);
    internal_message_namespace["m2g_guild_pop_item_ack"] = static_cast<lua_Number>(InternalMessage::m2g_guild_pop_item_ack);
    internal_message_namespace["m2g_guild_upgrade_building_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_upgrade_building_ntf);
    internal_message_namespace["m2g_guild_update_building_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_update_building_ntf);
    internal_message_namespace["m2g_guild_del_building_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_del_building_ntf);
    internal_message_namespace["m2g_guild_update_welfare_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_update_welfare_ntf);
    internal_message_namespace["m2g_guild_update_state_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_update_state_ntf);
    internal_message_namespace["m2g_guild_change_position_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_change_position_ntf);
    internal_message_namespace["m2g_guild_pre_open_dungeon_ack"] = static_cast<lua_Number>(InternalMessage::m2g_guild_pre_open_dungeon_ack);
    internal_message_namespace["m2g_guild_enter_dungeon"] = static_cast<lua_Number>(InternalMessage::m2g_guild_enter_dungeon);
    internal_message_namespace["m2g_guild_sync_war_relation"] = static_cast<lua_Number>(InternalMessage::m2g_guild_sync_war_relation);
    internal_message_namespace["m2g_guild_sync_war_char"] = static_cast<lua_Number>(InternalMessage::m2g_guild_sync_war_char);
    internal_message_namespace["m2g_guild_change_res_ack"] = static_cast<lua_Number>(InternalMessage::m2g_guild_change_res_ack);
    internal_message_namespace["m2g_guild_war_end"] = static_cast<lua_Number>(InternalMessage::m2g_guild_war_end);
    internal_message_namespace["m2g_guild_sync_building_state_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_sync_building_state_ntf);
    internal_message_namespace["m2g_guild_sync_member_salary_ntf"] = static_cast<lua_Number>(InternalMessage::m2g_guild_sync_member_salary_ntf);
    internal_message_namespace["m2g_sync_role_social_data"] = static_cast<lua_Number>(InternalMessage::m2g_sync_role_social_data);
    internal_message_namespace["m2g_guild_achievement_reward"] = static_cast<lua_Number>(InternalMessage::m2g_guild_achievement_reward);
    internal_message_namespace["m2g_arena_reward"] = static_cast<lua_Number>(InternalMessage::m2g_arena_reward);
    internal_message_namespace["m2g_shield"] = static_cast<lua_Number>(InternalMessage::m2g_shield);
    internal_message_namespace["m2g_sync_gm_data"] = static_cast<lua_Number>(InternalMessage::m2g_sync_gm_data);
    internal_message_namespace["m2g_update_statistic_value"] = static_cast<lua_Number>(InternalMessage::m2g_update_statistic_value);
    internal_message_namespace["m2g_call_gm_command"] = static_cast<lua_Number>(InternalMessage::m2g_call_gm_command);
    internal_message_namespace["m2g_drop_limit"] = static_cast<lua_Number>(InternalMessage::m2g_drop_limit);
    internal_message_namespace["m2g_auction_sell"] = static_cast<lua_Number>(InternalMessage::m2g_auction_sell);
    internal_message_namespace["m2g_auction_buy"] = static_cast<lua_Number>(InternalMessage::m2g_auction_buy);
    internal_message_namespace["m2g_exchange_add_order"] = static_cast<lua_Number>(InternalMessage::m2g_exchange_add_order);
    internal_message_namespace["m2g_adventure_reward"] = static_cast<lua_Number>(InternalMessage::m2g_adventure_reward);
    internal_message_namespace["m2g_complete_achievement"] = static_cast<lua_Number>(InternalMessage::m2g_complete_achievement);
    internal_message_namespace["m2g_enroll_sabac"] = static_cast<lua_Number>(InternalMessage::m2g_enroll_sabac);
    internal_message_namespace["m2g_occupy_sabac"] = static_cast<lua_Number>(InternalMessage::m2g_occupy_sabac);
    internal_message_namespace["m2g_query_role_location"] = static_cast<lua_Number>(InternalMessage::m2g_query_role_location);
    internal_message_namespace["m2g_query_role_location_ack"] = static_cast<lua_Number>(InternalMessage::m2g_query_role_location_ack);
    internal_message_namespace["m2g_take_role"] = static_cast<lua_Number>(InternalMessage::m2g_take_role);
    internal_message_namespace["m2g_arrest_role"] = static_cast<lua_Number>(InternalMessage::m2g_arrest_role);
    internal_message_namespace["m2g_real_money_buy_success"] = static_cast<lua_Number>(InternalMessage::m2g_real_money_buy_success);
    internal_message_namespace["m2g_fcm_state"] = static_cast<lua_Number>(InternalMessage::m2g_fcm_state);
    internal_message_namespace["m2g_free_mode"] = static_cast<lua_Number>(InternalMessage::m2g_free_mode);
    internal_message_namespace["m2g_award"] = static_cast<lua_Number>(InternalMessage::m2g_award);
    internal_message_namespace["m2g_spawn_npc"] = static_cast<lua_Number>(InternalMessage::m2g_spawn_npc);
    internal_message_namespace["m2g_sync_server_variable"] = static_cast<lua_Number>(InternalMessage::m2g_sync_server_variable);
    internal_message_namespace["m2g_update_server_variable"] = static_cast<lua_Number>(InternalMessage::m2g_update_server_variable);
    internal_message_namespace["m2g_update_average_level"] = static_cast<lua_Number>(InternalMessage::m2g_update_average_level);
    internal_message_namespace["m2g_get_black_market_limit_info"] = static_cast<lua_Number>(InternalMessage::m2g_get_black_market_limit_info);
    internal_message_namespace["m2g_check_black_market_product"] = static_cast<lua_Number>(InternalMessage::m2g_check_black_market_product);
    internal_message_namespace["m2g_add_exercise_time"] = static_cast<lua_Number>(InternalMessage::m2g_add_exercise_time);
    internal_message_namespace["m2g_end"] = static_cast<lua_Number>(InternalMessage::m2g_end);
}

}
