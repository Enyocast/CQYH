#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/message/external_message_header.h"
#include "../../../../../../Common/message/c2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_external_client_to_manage_ids_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table external_message_namespace = globals["ExternalMessage"].get_or_create<sol::table>();
    external_message_namespace["c2m_message_begin"] = static_cast<lua_Number>(ExternalMessage::c2m_message_begin);
    external_message_namespace["c2m_query_role_info"] = static_cast<lua_Number>(ExternalMessage::c2m_query_role_info);
    external_message_namespace["c2m_team_join"] = static_cast<lua_Number>(ExternalMessage::c2m_team_join);
    external_message_namespace["c2m_team_leave"] = static_cast<lua_Number>(ExternalMessage::c2m_team_leave);
    external_message_namespace["c2m_team_answer"] = static_cast<lua_Number>(ExternalMessage::c2m_team_answer);
    external_message_namespace["c2m_team_changeinfo"] = static_cast<lua_Number>(ExternalMessage::c2m_team_changeinfo);
    external_message_namespace["c2m_team_change_activity_info"] = static_cast<lua_Number>(ExternalMessage::c2m_team_change_activity_info);
    external_message_namespace["c2m_team_query_activity_team"] = static_cast<lua_Number>(ExternalMessage::c2m_team_query_activity_team);
    external_message_namespace["c2m_team_remove_activity_team"] = static_cast<lua_Number>(ExternalMessage::c2m_team_remove_activity_team);
    external_message_namespace["c2m_friend_add"] = static_cast<lua_Number>(ExternalMessage::c2m_friend_add);
    external_message_namespace["c2m_friend_del"] = static_cast<lua_Number>(ExternalMessage::c2m_friend_del);
    external_message_namespace["c2m_friend_change_group"] = static_cast<lua_Number>(ExternalMessage::c2m_friend_change_group);
    external_message_namespace["c2m_change_info"] = static_cast<lua_Number>(ExternalMessage::c2m_change_info);
    external_message_namespace["c2m_friend_chat"] = static_cast<lua_Number>(ExternalMessage::c2m_friend_chat);
    external_message_namespace["c2m_personal_enemy_add"] = static_cast<lua_Number>(ExternalMessage::c2m_personal_enemy_add);
    external_message_namespace["c2m_personal_enemy_del"] = static_cast<lua_Number>(ExternalMessage::c2m_personal_enemy_del);
    external_message_namespace["c2m_chat_message"] = static_cast<lua_Number>(ExternalMessage::c2m_chat_message);
    external_message_namespace["c2m_query_line_req"] = static_cast<lua_Number>(ExternalMessage::c2m_query_line_req);
    external_message_namespace["c2m_master_teacher_ignore"] = static_cast<lua_Number>(ExternalMessage::c2m_master_teacher_ignore);
    external_message_namespace["c2m_master_get_recruit_list"] = static_cast<lua_Number>(ExternalMessage::c2m_master_get_recruit_list);
    external_message_namespace["c2m_master_get_solo_list"] = static_cast<lua_Number>(ExternalMessage::c2m_master_get_solo_list);
    external_message_namespace["c2m_master_stud_submit_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_stud_submit_app);
    external_message_namespace["c2m_master_agree_stud_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_agree_stud_app);
    external_message_namespace["c2m_master_refuse_stud_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_refuse_stud_app);
    external_message_namespace["c2m_master_cancel_stud_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_cancel_stud_app);
    external_message_namespace["c2m_master_teacher_submit_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_teacher_submit_app);
    external_message_namespace["c2m_master_agree_teacher_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_agree_teacher_app);
    external_message_namespace["c2m_master_refuse_teacher_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_refuse_teacher_app);
    external_message_namespace["c2m_master_cancel_teacher_app"] = static_cast<lua_Number>(ExternalMessage::c2m_master_cancel_teacher_app);
    external_message_namespace["c2m_master_leave_teacher"] = static_cast<lua_Number>(ExternalMessage::c2m_master_leave_teacher);
    external_message_namespace["c2m_master_fire_stud"] = static_cast<lua_Number>(ExternalMessage::c2m_master_fire_stud);
    external_message_namespace["c2m_master_info"] = static_cast<lua_Number>(ExternalMessage::c2m_master_info);
    external_message_namespace["c2m_master_cz"] = static_cast<lua_Number>(ExternalMessage::c2m_master_cz);
    external_message_namespace["c2m_master_grad"] = static_cast<lua_Number>(ExternalMessage::c2m_master_grad);
    external_message_namespace["c2m_mail_write"] = static_cast<lua_Number>(ExternalMessage::c2m_mail_write);
    external_message_namespace["c2m_mail_list_recv"] = static_cast<lua_Number>(ExternalMessage::c2m_mail_list_recv);
    external_message_namespace["c2m_mail_read"] = static_cast<lua_Number>(ExternalMessage::c2m_mail_read);
    external_message_namespace["c2m_mail_delete"] = static_cast<lua_Number>(ExternalMessage::c2m_mail_delete);
    external_message_namespace["c2m_mail_get_attach"] = static_cast<lua_Number>(ExternalMessage::c2m_mail_get_attach);
    external_message_namespace["c2m_join_battle"] = static_cast<lua_Number>(ExternalMessage::c2m_join_battle);
    external_message_namespace["c2m_cancel_join_battle_req"] = static_cast<lua_Number>(ExternalMessage::c2m_cancel_join_battle_req);
    external_message_namespace["c2m_join_battle_confirm_ack"] = static_cast<lua_Number>(ExternalMessage::c2m_join_battle_confirm_ack);
    external_message_namespace["c2m_query_guild_name"] = static_cast<lua_Number>(ExternalMessage::c2m_query_guild_name);
    external_message_namespace["c2m_view_guild_list"] = static_cast<lua_Number>(ExternalMessage::c2m_view_guild_list);
    external_message_namespace["c2m_more_guild_info"] = static_cast<lua_Number>(ExternalMessage::c2m_more_guild_info);
    external_message_namespace["c2m_find_guild"] = static_cast<lua_Number>(ExternalMessage::c2m_find_guild);
    external_message_namespace["c2m_apply_to_join_guild"] = static_cast<lua_Number>(ExternalMessage::c2m_apply_to_join_guild);
    external_message_namespace["c2m_get_apply_guild_list"] = static_cast<lua_Number>(ExternalMessage::c2m_get_apply_guild_list);
    external_message_namespace["c2m_revert_guild_apply"] = static_cast<lua_Number>(ExternalMessage::c2m_revert_guild_apply);
    external_message_namespace["c2m_invite_to_join_guild"] = static_cast<lua_Number>(ExternalMessage::c2m_invite_to_join_guild);
    external_message_namespace["c2m_revert_guild_invitation"] = static_cast<lua_Number>(ExternalMessage::c2m_revert_guild_invitation);
    external_message_namespace["c2m_disband_guild"] = static_cast<lua_Number>(ExternalMessage::c2m_disband_guild);
    external_message_namespace["c2m_guild_notice_change"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_notice_change);
    external_message_namespace["c2m_guild_announce_change"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_announce_change);
    external_message_namespace["c2m_guild_forbid_chat"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_forbid_chat);
    external_message_namespace["c2m_guild_change_position"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_change_position);
    external_message_namespace["c2m_guild_role_leave"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_role_leave);
    external_message_namespace["c2m_guild_banish_role"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_banish_role);
    external_message_namespace["c2m_guild_demise"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_demise);
    external_message_namespace["c2m_guild_diplomat_app"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_diplomat_app);
    external_message_namespace["c2m_guild_get_apply_union_list"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_get_apply_union_list);
    external_message_namespace["c2m_guild_reply_union_app"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_reply_union_app);
    external_message_namespace["c2m_guild_cancel_alliance"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_cancel_alliance);
    external_message_namespace["c2m_guild_change_storage_right"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_change_storage_right);
    external_message_namespace["c2m_guild_move_item"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_move_item);
    external_message_namespace["c2m_guild_more_history"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_more_history);
    external_message_namespace["c2m_guild_more_chest"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_more_chest);
    external_message_namespace["c2m_guild_upgrade_welfare"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_upgrade_welfare);
    external_message_namespace["c2m_guild_cancel_welfare_upgrade"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_cancel_welfare_upgrade);
    external_message_namespace["c2m_guild_cancel_building_upgrade"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_cancel_building_upgrade);
    external_message_namespace["c2m_guild_get_dungeon_list"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_get_dungeon_list);
    external_message_namespace["c2m_guild_declare_war"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_declare_war);
    external_message_namespace["c2m_guild_achievement"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_achievement);
    external_message_namespace["c2m_guild_activity"] = static_cast<lua_Number>(ExternalMessage::c2m_guild_activity);
    external_message_namespace["c2m_arena_get_data"] = static_cast<lua_Number>(ExternalMessage::c2m_arena_get_data);
    external_message_namespace["c2m_shield"] = static_cast<lua_Number>(ExternalMessage::c2m_shield);
    external_message_namespace["c2m_auction_search_type"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_search_type);
    external_message_namespace["c2m_auction_search"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_search);
    external_message_namespace["c2m_auction_query"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_query);
    external_message_namespace["c2m_auction_sell"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_sell);
    external_message_namespace["c2m_auction_cancel_sell"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_cancel_sell);
    external_message_namespace["c2m_auction_buy"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_buy);
    external_message_namespace["c2m_auction_list_my_selling"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_list_my_selling);
    external_message_namespace["c2m_auction_list_my_buying"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_list_my_buying);
    external_message_namespace["c2m_auction_pay_left_money"] = static_cast<lua_Number>(ExternalMessage::c2m_auction_pay_left_money);
    external_message_namespace["c2m_exchange_add_order"] = static_cast<lua_Number>(ExternalMessage::c2m_exchange_add_order);
    external_message_namespace["c2m_exchange_cancel_order"] = static_cast<lua_Number>(ExternalMessage::c2m_exchange_cancel_order);
    external_message_namespace["c2m_exchange_list_prices"] = static_cast<lua_Number>(ExternalMessage::c2m_exchange_list_prices);
    external_message_namespace["c2m_exchange_list_my_orders"] = static_cast<lua_Number>(ExternalMessage::c2m_exchange_list_my_orders);
    external_message_namespace["c2m_exchange_list_my_logs"] = static_cast<lua_Number>(ExternalMessage::c2m_exchange_list_my_logs);
    external_message_namespace["c2m_check_real_money"] = static_cast<lua_Number>(ExternalMessage::c2m_check_real_money);
    external_message_namespace["c2m_check_real_money_shop_data"] = static_cast<lua_Number>(ExternalMessage::c2m_check_real_money_shop_data);
    external_message_namespace["c2m_real_money_buy"] = static_cast<lua_Number>(ExternalMessage::c2m_real_money_buy);
    external_message_namespace["c2m_real_money_shop_log"] = static_cast<lua_Number>(ExternalMessage::c2m_real_money_shop_log);
    external_message_namespace["c2m_sale_info"] = static_cast<lua_Number>(ExternalMessage::c2m_sale_info);
    external_message_namespace["c2m_gm_command"] = static_cast<lua_Number>(ExternalMessage::c2m_gm_command);
    external_message_namespace["c2m_query_ranklist"] = static_cast<lua_Number>(ExternalMessage::c2m_query_ranklist);
    external_message_namespace["c2m_award_use_number"] = static_cast<lua_Number>(ExternalMessage::c2m_award_use_number);
    external_message_namespace["c2m_buy_time"] = static_cast<lua_Number>(ExternalMessage::c2m_buy_time);
    external_message_namespace["c2m_change_recall_state"] = static_cast<lua_Number>(ExternalMessage::c2m_change_recall_state);
    external_message_namespace["c2m_dynamic_auth"] = static_cast<lua_Number>(ExternalMessage::c2m_dynamic_auth);
    external_message_namespace["c2m_team_query"] = static_cast<lua_Number>(ExternalMessage::c2m_team_query);
    external_message_namespace["c2m_team_invite"] = static_cast<lua_Number>(ExternalMessage::c2m_team_invite);
    external_message_namespace["c2m_arena_fund"] = static_cast<lua_Number>(ExternalMessage::c2m_arena_fund);
    external_message_namespace["c2m_message_end"] = static_cast<lua_Number>(ExternalMessage::c2m_message_end);
}

}
