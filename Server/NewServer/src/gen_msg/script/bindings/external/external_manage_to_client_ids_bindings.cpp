#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/message/external_message_header.h"
#include "../../../../../../Common/message/m2c_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/ranklist_def.h"
#include "../../../../../../Common/define/string_def.h"
#include "../../../../../../Common/define/team_def.h"
#include "../../../../../../Common/define/variable_def.h"

namespace cqyh::gen_msg::bindings {

void register_external_manage_to_client_ids_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table external_message_namespace = globals["ExternalMessage"].get_or_create<sol::table>();
    external_message_namespace["m2c_message_begin"] = static_cast<lua_Number>(ExternalMessage::m2c_message_begin);
    external_message_namespace["m2c_sync_role_info"] = static_cast<lua_Number>(ExternalMessage::m2c_sync_role_info);
    external_message_namespace["m2c_error_notify"] = static_cast<lua_Number>(ExternalMessage::m2c_error_notify);
    external_message_namespace["m2c_queue_info"] = static_cast<lua_Number>(ExternalMessage::m2c_queue_info);
    external_message_namespace["m2c_team_join"] = static_cast<lua_Number>(ExternalMessage::m2c_team_join);
    external_message_namespace["m2c_team_leave"] = static_cast<lua_Number>(ExternalMessage::m2c_team_leave);
    external_message_namespace["m2c_team_add_member"] = static_cast<lua_Number>(ExternalMessage::m2c_team_add_member);
    external_message_namespace["m2c_team_remove_member"] = static_cast<lua_Number>(ExternalMessage::m2c_team_remove_member);
    external_message_namespace["m2c_team_answer"] = static_cast<lua_Number>(ExternalMessage::m2c_team_answer);
    external_message_namespace["m2c_team_changeinfo"] = static_cast<lua_Number>(ExternalMessage::m2c_team_changeinfo);
    external_message_namespace["m2c_team_sync_memberinfo"] = static_cast<lua_Number>(ExternalMessage::m2c_team_sync_memberinfo);
    external_message_namespace["m2c_team_sync_memberstate"] = static_cast<lua_Number>(ExternalMessage::m2c_team_sync_memberstate);
    external_message_namespace["m2c_activity_query_team"] = static_cast<lua_Number>(ExternalMessage::m2c_activity_query_team);
    external_message_namespace["m2c_activity_change_dungeon"] = static_cast<lua_Number>(ExternalMessage::m2c_activity_change_dungeon);
    external_message_namespace["m2c_self_info"] = static_cast<lua_Number>(ExternalMessage::m2c_self_info);
    external_message_namespace["m2c_friend_list"] = static_cast<lua_Number>(ExternalMessage::m2c_friend_list);
    external_message_namespace["m2c_friend_info_change"] = static_cast<lua_Number>(ExternalMessage::m2c_friend_info_change);
    external_message_namespace["m2c_friend_add"] = static_cast<lua_Number>(ExternalMessage::m2c_friend_add);
    external_message_namespace["m2c_friend_del"] = static_cast<lua_Number>(ExternalMessage::m2c_friend_del);
    external_message_namespace["m2c_friend_added_by"] = static_cast<lua_Number>(ExternalMessage::m2c_friend_added_by);
    external_message_namespace["m2c_friend_deleted_by"] = static_cast<lua_Number>(ExternalMessage::m2c_friend_deleted_by);
    external_message_namespace["m2c_friend_chat"] = static_cast<lua_Number>(ExternalMessage::m2c_friend_chat);
    external_message_namespace["m2c_personal_enemy_add"] = static_cast<lua_Number>(ExternalMessage::m2c_personal_enemy_add);
    external_message_namespace["m2c_personal_enemy_del"] = static_cast<lua_Number>(ExternalMessage::m2c_personal_enemy_del);
    external_message_namespace["m2c_chat_message"] = static_cast<lua_Number>(ExternalMessage::m2c_chat_message);
    external_message_namespace["m2c_publish_quest"] = static_cast<lua_Number>(ExternalMessage::m2c_publish_quest);
    external_message_namespace["m2c_query_line_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_query_line_ack);
    external_message_namespace["m2c_master_twitter_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_twitter_ack);
    external_message_namespace["m2c_master_hello_teacher"] = static_cast<lua_Number>(ExternalMessage::m2c_master_hello_teacher);
    external_message_namespace["m2c_master_recruit_list"] = static_cast<lua_Number>(ExternalMessage::m2c_master_recruit_list);
    external_message_namespace["m2c_master_get_solo_list_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_get_solo_list_ack);
    external_message_namespace["m2c_master_info"] = static_cast<lua_Number>(ExternalMessage::m2c_master_info);
    external_message_namespace["m2c_master_sync_lvl"] = static_cast<lua_Number>(ExternalMessage::m2c_master_sync_lvl);
    external_message_namespace["m2c_master_stud_submit_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_stud_submit_app_ack);
    external_message_namespace["m2c_master_stud_submit_app_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_stud_submit_app_ntf);
    external_message_namespace["m2c_master_agree_stud_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_agree_stud_app_ack);
    external_message_namespace["m2c_master_refuse_stud_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_refuse_stud_app_ack);
    external_message_namespace["m2c_master_refuse_stud_app_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_refuse_stud_app_ntf);
    external_message_namespace["m2c_master_cancel_stud_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_cancel_stud_app_ack);
    external_message_namespace["m2c_master_cancel_stud_app_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_cancel_stud_app_ntf);
    external_message_namespace["m2c_master_teacher_submit_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_teacher_submit_app_ack);
    external_message_namespace["m2c_master_teacher_submit_app_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_teacher_submit_app_ntf);
    external_message_namespace["m2c_master_agree_teacher_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_agree_teacher_app_ack);
    external_message_namespace["m2c_master_refuse_teacher_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_refuse_teacher_app_ack);
    external_message_namespace["m2c_master_refuse_teacher_app_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_refuse_teacher_app_ntf);
    external_message_namespace["m2c_master_cancel_teacher_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_cancel_teacher_app_ack);
    external_message_namespace["m2c_master_cancel_teacher_app_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_cancel_teacher_app_ntf);
    external_message_namespace["m2c_master_leave_teacher_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_leave_teacher_ack);
    external_message_namespace["m2c_master_leave_teacher_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_leave_teacher_ntf);
    external_message_namespace["m2c_master_fire_student_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_fire_student_ack);
    external_message_namespace["m2c_master_fire_student_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_fire_student_ntf);
    external_message_namespace["m2c_master_add_student_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_add_student_ntf);
    external_message_namespace["m2c_master_del_student_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_master_del_student_ntf);
    external_message_namespace["m2c_master_clear_info"] = static_cast<lua_Number>(ExternalMessage::m2c_master_clear_info);
    external_message_namespace["m2c_master_cz_level"] = static_cast<lua_Number>(ExternalMessage::m2c_master_cz_level);
    external_message_namespace["m2c_master_cz_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_master_cz_ack);
    external_message_namespace["m2c_master_grad"] = static_cast<lua_Number>(ExternalMessage::m2c_master_grad);
    external_message_namespace["m2c_mail_write_success"] = static_cast<lua_Number>(ExternalMessage::m2c_mail_write_success);
    external_message_namespace["m2c_mail_list_recv"] = static_cast<lua_Number>(ExternalMessage::m2c_mail_list_recv);
    external_message_namespace["m2c_mail_read"] = static_cast<lua_Number>(ExternalMessage::m2c_mail_read);
    external_message_namespace["m2c_mail_delete_success"] = static_cast<lua_Number>(ExternalMessage::m2c_mail_delete_success);
    external_message_namespace["m2c_mail_new_count"] = static_cast<lua_Number>(ExternalMessage::m2c_mail_new_count);
    external_message_namespace["m2c_mail_get_attach_success"] = static_cast<lua_Number>(ExternalMessage::m2c_mail_get_attach_success);
    external_message_namespace["m2c_join_battle_queue"] = static_cast<lua_Number>(ExternalMessage::m2c_join_battle_queue);
    external_message_namespace["m2c_cancel_join_battle_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_cancel_join_battle_ack);
    external_message_namespace["m2c_join_battle_confirm_req"] = static_cast<lua_Number>(ExternalMessage::m2c_join_battle_confirm_req);
    external_message_namespace["m2c_query_guild_name_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_query_guild_name_ack);
    external_message_namespace["m2c_create_guild_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_create_guild_ack);
    external_message_namespace["m2c_view_guild_list_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_view_guild_list_ack);
    external_message_namespace["m2c_more_guild_info_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_more_guild_info_ack);
    external_message_namespace["m2c_find_guild_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_find_guild_ack);
    external_message_namespace["m2c_guild_info_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_info_ntf);
    external_message_namespace["m2c_apply_to_join_guild_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_apply_to_join_guild_ack);
    external_message_namespace["m2c_get_apply_guild_list_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_get_apply_guild_list_ack);
    external_message_namespace["m2c_revert_guild_apply_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_revert_guild_apply_ack);
    external_message_namespace["m2c_del_guild_app"] = static_cast<lua_Number>(ExternalMessage::m2c_del_guild_app);
    external_message_namespace["m2c_guild_add_member_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_add_member_ntf);
    external_message_namespace["m2c_guild_del_member_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_del_member_ntf);
    external_message_namespace["m2c_be_invited_to_join_guild"] = static_cast<lua_Number>(ExternalMessage::m2c_be_invited_to_join_guild);
    external_message_namespace["m2c_invite_to_join_guild_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_invite_to_join_guild_ack);
    external_message_namespace["m2c_disband_guild_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_disband_guild_ntf);
    external_message_namespace["m2c_guild_notice_change"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_notice_change);
    external_message_namespace["m2c_guild_forbid_chat_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_forbid_chat_ntf);
    external_message_namespace["m2c_guild_change_position_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_change_position_ntf);
    external_message_namespace["m2c_guild_role_leave_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_role_leave_ntf);
    external_message_namespace["m2c_guild_role_leave_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_role_leave_ack);
    external_message_namespace["m2c_guild_demise_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_demise_ntf);
    external_message_namespace["m2c_guild_contribute_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_contribute_ack);
    external_message_namespace["m2c_guild_attr_modify_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_attr_modify_ntf);
    external_message_namespace["m2c_guild_apply_alliance_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_apply_alliance_ack);
    external_message_namespace["m2c_guild_get_apply_union_list_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_get_apply_union_list_ack);
    external_message_namespace["m2c_guild_reply_union_app_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_reply_union_app_ack);
    external_message_namespace["m2c_guild_add_diplomat_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_add_diplomat_ntf);
    external_message_namespace["m2c_guild_del_diplomat_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_del_diplomat_ntf);
    external_message_namespace["m2c_guild_notify_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_notify_ntf);
    external_message_namespace["m2c_guild_change_storage_right_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_change_storage_right_ntf);
    external_message_namespace["m2c_guild_view_storage_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_view_storage_ack);
    external_message_namespace["m2c_guild_storage_event"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_storage_event);
    external_message_namespace["m2c_guild_push_item_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_push_item_ack);
    external_message_namespace["m2c_guild_pop_item_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_pop_item_ack);
    external_message_namespace["m2c_guild_move_item_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_move_item_ack);
    external_message_namespace["m2c_guild_add_history_event_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_add_history_event_ntf);
    external_message_namespace["m2c_guild_add_storage_event_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_add_storage_event_ntf);
    external_message_namespace["m2c_guild_member_salary_change"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_member_salary_change);
    external_message_namespace["m2c_guild_more_history"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_more_history);
    external_message_namespace["m2c_guild_more_chest"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_more_chest);
    external_message_namespace["m2c_guild_join_guild_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_join_guild_ntf);
    external_message_namespace["m2c_guild_upgrade_welfare_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_upgrade_welfare_ntf);
    external_message_namespace["m2c_guild_update_welfare_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_update_welfare_ntf);
    external_message_namespace["m2c_guild_cancel_welfare_upgrade_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_cancel_welfare_upgrade_ntf);
    external_message_namespace["m2c_guild_upgrade_building_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_upgrade_building_ntf);
    external_message_namespace["m2c_guild_update_building_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_update_building_ntf);
    external_message_namespace["m2c_guild_cancel_building_upgrade_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_cancel_building_upgrade_ntf);
    external_message_namespace["m2c_guild_del_building_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_del_building_ntf);
    external_message_namespace["m2c_guild_get_dungeon_list_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_get_dungeon_list_ack);
    external_message_namespace["m2c_guild_open_dungeon_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_open_dungeon_ack);
    external_message_namespace["m2c_guild_dungeon_award"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_dungeon_award);
    external_message_namespace["m2c_guild_battle_achievement"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_battle_achievement);
    external_message_namespace["m2c_guild_building_state_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_building_state_ntf);
    external_message_namespace["m2c_guild_sync_war_cd_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_sync_war_cd_ntf);
    external_message_namespace["m2c_guild_achievement_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_achievement_ack);
    external_message_namespace["m2c_guild_join_war_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_join_war_ntf);
    external_message_namespace["m2c_arena_get_data_ack"] = static_cast<lua_Number>(ExternalMessage::m2c_arena_get_data_ack);
    external_message_namespace["m2c_arena_end"] = static_cast<lua_Number>(ExternalMessage::m2c_arena_end);
    external_message_namespace["m2c_arena_match_begin_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_arena_match_begin_ntf);
    external_message_namespace["m2c_sync_social_attr_ntf"] = static_cast<lua_Number>(ExternalMessage::m2c_sync_social_attr_ntf);
    external_message_namespace["m2c_auction_search"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_search);
    external_message_namespace["m2c_auction_query"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_query);
    external_message_namespace["m2c_auction_sell"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_sell);
    external_message_namespace["m2c_auction_cancel_sell"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_cancel_sell);
    external_message_namespace["m2c_auction_buy"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_buy);
    external_message_namespace["m2c_auction_finished"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_finished);
    external_message_namespace["m2c_auction_list_my_selling"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_list_my_selling);
    external_message_namespace["m2c_auction_list_my_buying"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_list_my_buying);
    external_message_namespace["m2c_auction_pay_left_money"] = static_cast<lua_Number>(ExternalMessage::m2c_auction_pay_left_money);
    external_message_namespace["m2c_exchange_add_order"] = static_cast<lua_Number>(ExternalMessage::m2c_exchange_add_order);
    external_message_namespace["m2c_exchange_cancel_order"] = static_cast<lua_Number>(ExternalMessage::m2c_exchange_cancel_order);
    external_message_namespace["m2c_exchange_list_prices"] = static_cast<lua_Number>(ExternalMessage::m2c_exchange_list_prices);
    external_message_namespace["m2c_exchange_list_my_orders"] = static_cast<lua_Number>(ExternalMessage::m2c_exchange_list_my_orders);
    external_message_namespace["m2c_exchange_list_my_logs"] = static_cast<lua_Number>(ExternalMessage::m2c_exchange_list_my_logs);
    external_message_namespace["m2c_sync_real_money"] = static_cast<lua_Number>(ExternalMessage::m2c_sync_real_money);
    external_message_namespace["m2c_sync_real_money_shop_data"] = static_cast<lua_Number>(ExternalMessage::m2c_sync_real_money_shop_data);
    external_message_namespace["m2c_real_money_buy"] = static_cast<lua_Number>(ExternalMessage::m2c_real_money_buy);
    external_message_namespace["m2c_real_money_shop_log"] = static_cast<lua_Number>(ExternalMessage::m2c_real_money_shop_log);
    external_message_namespace["m2c_sale_info"] = static_cast<lua_Number>(ExternalMessage::m2c_sale_info);
    external_message_namespace["m2c_query_ranklist"] = static_cast<lua_Number>(ExternalMessage::m2c_query_ranklist);
    external_message_namespace["m2c_occupy_sabac"] = static_cast<lua_Number>(ExternalMessage::m2c_occupy_sabac);
    external_message_namespace["m2c_enroll_sabac"] = static_cast<lua_Number>(ExternalMessage::m2c_enroll_sabac);
    external_message_namespace["m2c_erect_statue"] = static_cast<lua_Number>(ExternalMessage::m2c_erect_statue);
    external_message_namespace["m2c_sabac_winner_login"] = static_cast<lua_Number>(ExternalMessage::m2c_sabac_winner_login);
    external_message_namespace["m2c_fcm_state"] = static_cast<lua_Number>(ExternalMessage::m2c_fcm_state);
    external_message_namespace["m2c_time_info"] = static_cast<lua_Number>(ExternalMessage::m2c_time_info);
    external_message_namespace["m2c_buy_time"] = static_cast<lua_Number>(ExternalMessage::m2c_buy_time);
    external_message_namespace["m2c_free_mode"] = static_cast<lua_Number>(ExternalMessage::m2c_free_mode);
    external_message_namespace["m2c_sync_friend_intimacy"] = static_cast<lua_Number>(ExternalMessage::m2c_sync_friend_intimacy);
    external_message_namespace["m2c_sync_friend_intimacy_list"] = static_cast<lua_Number>(ExternalMessage::m2c_sync_friend_intimacy_list);
    external_message_namespace["m2c_team_sync_team_info"] = static_cast<lua_Number>(ExternalMessage::m2c_team_sync_team_info);
    external_message_namespace["m2c_arena_fund"] = static_cast<lua_Number>(ExternalMessage::m2c_arena_fund);
    external_message_namespace["m2c_guild_war_record"] = static_cast<lua_Number>(ExternalMessage::m2c_guild_war_record);
    external_message_namespace["m2c_h5_url"] = static_cast<lua_Number>(ExternalMessage::m2c_h5_url);
    external_message_namespace["m2c_message_end"] = static_cast<lua_Number>(ExternalMessage::m2c_message_end);
}

}
