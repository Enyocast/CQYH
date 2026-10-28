#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_game_to_manage_ids_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["g2m_begin"] = static_cast<lua_Number>(InternalMessage::g2m_begin);
    internal_message_namespace["g2m_register"] = static_cast<lua_Number>(InternalMessage::g2m_register);
    internal_message_namespace["g2m_ready"] = static_cast<lua_Number>(InternalMessage::g2m_ready);
    internal_message_namespace["g2m_server_info"] = static_cast<lua_Number>(InternalMessage::g2m_server_info);
    internal_message_namespace["g2m_close_ack"] = static_cast<lua_Number>(InternalMessage::g2m_close_ack);
    internal_message_namespace["g2m_broadcast_group_client"] = static_cast<lua_Number>(InternalMessage::g2m_broadcast_group_client);
    internal_message_namespace["g2m_pre_enter_gs_ack"] = static_cast<lua_Number>(InternalMessage::g2m_pre_enter_gs_ack);
    internal_message_namespace["g2m_enter_gs"] = static_cast<lua_Number>(InternalMessage::g2m_enter_gs);
    internal_message_namespace["g2m_leave_gs_ack"] = static_cast<lua_Number>(InternalMessage::g2m_leave_gs_ack);
    internal_message_namespace["g2m_reset_scene"] = static_cast<lua_Number>(InternalMessage::g2m_reset_scene);
    internal_message_namespace["g2m_query_scene"] = static_cast<lua_Number>(InternalMessage::g2m_query_scene);
    internal_message_namespace["g2m_create_scene_ack"] = static_cast<lua_Number>(InternalMessage::g2m_create_scene_ack);
    internal_message_namespace["g2m_close_scene"] = static_cast<lua_Number>(InternalMessage::g2m_close_scene);
    internal_message_namespace["g2m_destroy_scene_ack"] = static_cast<lua_Number>(InternalMessage::g2m_destroy_scene_ack);
    internal_message_namespace["g2m_chat_message"] = static_cast<lua_Number>(InternalMessage::g2m_chat_message);
    internal_message_namespace["g2m_leave_team"] = static_cast<lua_Number>(InternalMessage::g2m_leave_team);
    internal_message_namespace["g2m_team_sync_member"] = static_cast<lua_Number>(InternalMessage::g2m_team_sync_member);
    internal_message_namespace["g2m_clear_team_dungeon"] = static_cast<lua_Number>(InternalMessage::g2m_clear_team_dungeon);
    internal_message_namespace["g2m_publish_quest"] = static_cast<lua_Number>(InternalMessage::g2m_publish_quest);
    internal_message_namespace["g2m_update_role_info"] = static_cast<lua_Number>(InternalMessage::g2m_update_role_info);
    internal_message_namespace["g2m_mail_cost_check"] = static_cast<lua_Number>(InternalMessage::g2m_mail_cost_check);
    internal_message_namespace["g2m_send_system_mail"] = static_cast<lua_Number>(InternalMessage::g2m_send_system_mail);
    internal_message_namespace["g2m_send_system_mail_with_simple_attach"] = static_cast<lua_Number>(InternalMessage::g2m_send_system_mail_with_simple_attach);
    internal_message_namespace["g2m_send_system_mail_with_buffer_attach"] = static_cast<lua_Number>(InternalMessage::g2m_send_system_mail_with_buffer_attach);
    internal_message_namespace["g2m_mail_get_attach"] = static_cast<lua_Number>(InternalMessage::g2m_mail_get_attach);
    internal_message_namespace["g2m_call_lua_function"] = static_cast<lua_Number>(InternalMessage::g2m_call_lua_function);
    internal_message_namespace["g2m_mst_submit_teacher_app_ack"] = static_cast<lua_Number>(InternalMessage::g2m_mst_submit_teacher_app_ack);
    internal_message_namespace["g2m_mst_agree_teacher_app_ack"] = static_cast<lua_Number>(InternalMessage::g2m_mst_agree_teacher_app_ack);
    internal_message_namespace["g2m_mst_submit_stud_app_ack"] = static_cast<lua_Number>(InternalMessage::g2m_mst_submit_stud_app_ack);
    internal_message_namespace["g2m_mst_agree_stud_app_ack"] = static_cast<lua_Number>(InternalMessage::g2m_mst_agree_stud_app_ack);
    internal_message_namespace["g2m_sync_master_exp"] = static_cast<lua_Number>(InternalMessage::g2m_sync_master_exp);
    internal_message_namespace["g2m_master_cz"] = static_cast<lua_Number>(InternalMessage::g2m_master_cz);
    internal_message_namespace["g2m_try_to_find_teacher"] = static_cast<lua_Number>(InternalMessage::g2m_try_to_find_teacher);
    internal_message_namespace["g2m_master_twitter"] = static_cast<lua_Number>(InternalMessage::g2m_master_twitter);
    internal_message_namespace["g2m_guild_create"] = static_cast<lua_Number>(InternalMessage::g2m_guild_create);
    internal_message_namespace["g2m_pre_create_guild_ack"] = static_cast<lua_Number>(InternalMessage::g2m_pre_create_guild_ack);
    internal_message_namespace["g2m_guild_draw_salary"] = static_cast<lua_Number>(InternalMessage::g2m_guild_draw_salary);
    internal_message_namespace["g2m_guild_contribute"] = static_cast<lua_Number>(InternalMessage::g2m_guild_contribute);
    internal_message_namespace["g2m_guild_view_storage"] = static_cast<lua_Number>(InternalMessage::g2m_guild_view_storage);
    internal_message_namespace["g2m_guild_pre_push_item"] = static_cast<lua_Number>(InternalMessage::g2m_guild_pre_push_item);
    internal_message_namespace["g2m_guild_push_item"] = static_cast<lua_Number>(InternalMessage::g2m_guild_push_item);
    internal_message_namespace["g2m_guild_pre_pop_item"] = static_cast<lua_Number>(InternalMessage::g2m_guild_pre_pop_item);
    internal_message_namespace["g2m_guild_pop_item"] = static_cast<lua_Number>(InternalMessage::g2m_guild_pop_item);
    internal_message_namespace["g2m_guild_create_building"] = static_cast<lua_Number>(InternalMessage::g2m_guild_create_building);
    internal_message_namespace["g2m_guild_upgrade_building"] = static_cast<lua_Number>(InternalMessage::g2m_guild_upgrade_building);
    internal_message_namespace["g2m_guild_del_building"] = static_cast<lua_Number>(InternalMessage::g2m_guild_del_building);
    internal_message_namespace["g2m_guild_pre_open_dungeon"] = static_cast<lua_Number>(InternalMessage::g2m_guild_pre_open_dungeon);
    internal_message_namespace["g2m_guild_open_dungeon"] = static_cast<lua_Number>(InternalMessage::g2m_guild_open_dungeon);
    internal_message_namespace["g2m_guild_enter_dungeon"] = static_cast<lua_Number>(InternalMessage::g2m_guild_enter_dungeon);
    internal_message_namespace["g2m_guild_close_dungeon_commission"] = static_cast<lua_Number>(InternalMessage::g2m_guild_close_dungeon_commission);
    internal_message_namespace["g2m_guild_change_res"] = static_cast<lua_Number>(InternalMessage::g2m_guild_change_res);
    internal_message_namespace["g2m_guild_end_war"] = static_cast<lua_Number>(InternalMessage::g2m_guild_end_war);
    internal_message_namespace["g2m_guild_change_building_state"] = static_cast<lua_Number>(InternalMessage::g2m_guild_change_building_state);
    internal_message_namespace["g2m_guild_achievement_reward"] = static_cast<lua_Number>(InternalMessage::g2m_guild_achievement_reward);
    internal_message_namespace["g2m_guild_leave_guild"] = static_cast<lua_Number>(InternalMessage::g2m_guild_leave_guild);
    internal_message_namespace["g2m_arena_sync_data"] = static_cast<lua_Number>(InternalMessage::g2m_arena_sync_data);
    internal_message_namespace["g2m_arena_join_season"] = static_cast<lua_Number>(InternalMessage::g2m_arena_join_season);
    internal_message_namespace["g2m_arena_match"] = static_cast<lua_Number>(InternalMessage::g2m_arena_match);
    internal_message_namespace["g2m_arena_win"] = static_cast<lua_Number>(InternalMessage::g2m_arena_win);
    internal_message_namespace["g2m_arena_defeated"] = static_cast<lua_Number>(InternalMessage::g2m_arena_defeated);
    internal_message_namespace["g2m_arena_reward"] = static_cast<lua_Number>(InternalMessage::g2m_arena_reward);
    internal_message_namespace["g2m_add_kill_list"] = static_cast<lua_Number>(InternalMessage::g2m_add_kill_list);
    internal_message_namespace["g2m_gm_log"] = static_cast<lua_Number>(InternalMessage::g2m_gm_log);
    internal_message_namespace["g2m_drop_limit"] = static_cast<lua_Number>(InternalMessage::g2m_drop_limit);
    internal_message_namespace["g2m_auction_sell"] = static_cast<lua_Number>(InternalMessage::g2m_auction_sell);
    internal_message_namespace["g2m_auction_buy"] = static_cast<lua_Number>(InternalMessage::g2m_auction_buy);
    internal_message_namespace["g2m_auction_pay"] = static_cast<lua_Number>(InternalMessage::g2m_auction_pay);
    internal_message_namespace["g2m_exchange_add_order"] = static_cast<lua_Number>(InternalMessage::g2m_exchange_add_order);
    internal_message_namespace["g2m_ranklist_role_data"] = static_cast<lua_Number>(InternalMessage::g2m_ranklist_role_data);
    internal_message_namespace["g2m_update_ranklist_node"] = static_cast<lua_Number>(InternalMessage::g2m_update_ranklist_node);
    internal_message_namespace["g2m_adventure_trigger"] = static_cast<lua_Number>(InternalMessage::g2m_adventure_trigger);
    internal_message_namespace["g2m_send_award_to_ump"] = static_cast<lua_Number>(InternalMessage::g2m_send_award_to_ump);
    internal_message_namespace["g2m_enroll_sabac"] = static_cast<lua_Number>(InternalMessage::g2m_enroll_sabac);
    internal_message_namespace["g2m_occupy_sabac"] = static_cast<lua_Number>(InternalMessage::g2m_occupy_sabac);
    internal_message_namespace["g2m_erect_statue"] = static_cast<lua_Number>(InternalMessage::g2m_erect_statue);
    internal_message_namespace["g2m_query_role_location"] = static_cast<lua_Number>(InternalMessage::g2m_query_role_location);
    internal_message_namespace["g2m_query_role_location_ack"] = static_cast<lua_Number>(InternalMessage::g2m_query_role_location_ack);
    internal_message_namespace["g2m_take_role"] = static_cast<lua_Number>(InternalMessage::g2m_take_role);
    internal_message_namespace["g2m_recall_team_member"] = static_cast<lua_Number>(InternalMessage::g2m_recall_team_member);
    internal_message_namespace["g2m_set_server_variable"] = static_cast<lua_Number>(InternalMessage::g2m_set_server_variable);
    internal_message_namespace["g2m_get_black_market_limit_info"] = static_cast<lua_Number>(InternalMessage::g2m_get_black_market_limit_info);
    internal_message_namespace["g2m_check_black_market_product"] = static_cast<lua_Number>(InternalMessage::g2m_check_black_market_product);
    internal_message_namespace["g2m_add_exercise_time"] = static_cast<lua_Number>(InternalMessage::g2m_add_exercise_time);
    internal_message_namespace["g2m_freeze_login"] = static_cast<lua_Number>(InternalMessage::g2m_freeze_login);
    internal_message_namespace["g2m_temporary_charge"] = static_cast<lua_Number>(InternalMessage::g2m_temporary_charge);
    internal_message_namespace["g2m_query_real_money_ack"] = static_cast<lua_Number>(InternalMessage::g2m_query_real_money_ack);
    internal_message_namespace["g2m_role_rela_money_shop_buy_item_ack"] = static_cast<lua_Number>(InternalMessage::g2m_role_rela_money_shop_buy_item_ack);
    internal_message_namespace["g2m_end"] = static_cast<lua_Number>(InternalMessage::g2m_end);
}

}
