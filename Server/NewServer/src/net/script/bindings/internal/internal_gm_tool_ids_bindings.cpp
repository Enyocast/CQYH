#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_gm_tool_ids_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["tl_begin"] = static_cast<lua_Number>(InternalMessage::tl_begin);
    internal_message_namespace["tl2gm_register"] = static_cast<lua_Number>(InternalMessage::tl2gm_register);
    internal_message_namespace["tl2gm_verify"] = static_cast<lua_Number>(InternalMessage::tl2gm_verify);
    internal_message_namespace["tl2gm_login"] = static_cast<lua_Number>(InternalMessage::tl2gm_login);
    internal_message_namespace["tl2gm_logout"] = static_cast<lua_Number>(InternalMessage::tl2gm_logout);
    internal_message_namespace["tl2gm_pre_query"] = static_cast<lua_Number>(InternalMessage::tl2gm_pre_query);
    internal_message_namespace["tl2gm_query_role_id"] = static_cast<lua_Number>(InternalMessage::tl2gm_query_role_id);
    internal_message_namespace["tl2gm_query_role_data"] = static_cast<lua_Number>(InternalMessage::tl2gm_query_role_data);
    internal_message_namespace["tl2gm_forbid_chat"] = static_cast<lua_Number>(InternalMessage::tl2gm_forbid_chat);
    internal_message_namespace["tl2gm_freeze_role"] = static_cast<lua_Number>(InternalMessage::tl2gm_freeze_role);
    internal_message_namespace["tl2gm_kick_role"] = static_cast<lua_Number>(InternalMessage::tl2gm_kick_role);
    internal_message_namespace["tl2gm_send_mail"] = static_cast<lua_Number>(InternalMessage::tl2gm_send_mail);
    internal_message_namespace["tl2gm_announce"] = static_cast<lua_Number>(InternalMessage::tl2gm_announce);
    internal_message_namespace["tl2gm_get_announce_list"] = static_cast<lua_Number>(InternalMessage::tl2gm_get_announce_list);
    internal_message_namespace["tl2gm_del_announce"] = static_cast<lua_Number>(InternalMessage::tl2gm_del_announce);
    internal_message_namespace["tl2gm_log"] = static_cast<lua_Number>(InternalMessage::tl2gm_log);
    internal_message_namespace["tl2gm_exe_gm_str"] = static_cast<lua_Number>(InternalMessage::tl2gm_exe_gm_str);
    internal_message_namespace["tl2gm_load_role_data"] = static_cast<lua_Number>(InternalMessage::tl2gm_load_role_data);
    internal_message_namespace["tl2gm_modify_role_data"] = static_cast<lua_Number>(InternalMessage::tl2gm_modify_role_data);
    internal_message_namespace["tl2gm_release_role"] = static_cast<lua_Number>(InternalMessage::tl2gm_release_role);
    internal_message_namespace["tl2gm_query_name_to_id"] = static_cast<lua_Number>(InternalMessage::tl2gm_query_name_to_id);
    internal_message_namespace["tl2gm_role_exe_cmd"] = static_cast<lua_Number>(InternalMessage::tl2gm_role_exe_cmd);
    internal_message_namespace["tl2gm_select_group"] = static_cast<lua_Number>(InternalMessage::tl2gm_select_group);
    internal_message_namespace["tl2gm_exchange_price"] = static_cast<lua_Number>(InternalMessage::tl2gm_exchange_price);
    internal_message_namespace["tl2gm_order_detail"] = static_cast<lua_Number>(InternalMessage::tl2gm_order_detail);
    internal_message_namespace["tl2gm_exchange_history"] = static_cast<lua_Number>(InternalMessage::tl2gm_exchange_history);
    internal_message_namespace["tl2gm_add_system_order"] = static_cast<lua_Number>(InternalMessage::tl2gm_add_system_order);
    internal_message_namespace["tl2gm_del_system_order"] = static_cast<lua_Number>(InternalMessage::tl2gm_del_system_order);
    internal_message_namespace["tl2gm_sys_exchange_info"] = static_cast<lua_Number>(InternalMessage::tl2gm_sys_exchange_info);
    internal_message_namespace["tl2gm_get_exchange_limit"] = static_cast<lua_Number>(InternalMessage::tl2gm_get_exchange_limit);
    internal_message_namespace["tl2gm_set_exchange_limit"] = static_cast<lua_Number>(InternalMessage::tl2gm_set_exchange_limit);
    internal_message_namespace["gm2tl_register_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_register_ack);
    internal_message_namespace["gm2tl_verify_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_verify_ack);
    internal_message_namespace["gm2tl_login_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_login_ack);
    internal_message_namespace["gm2tl_item_list_ntf"] = static_cast<lua_Number>(InternalMessage::gm2tl_item_list_ntf);
    internal_message_namespace["gm2tl_logout_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_logout_ack);
    internal_message_namespace["gm2tl_pre_query_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_pre_query_ack);
    internal_message_namespace["gm2tl_query_role_id_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_query_role_id_ack);
    internal_message_namespace["gm2tl_query_role_data_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_query_role_data_ack);
    internal_message_namespace["gm2tl_forbid_chat_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_forbid_chat_ack);
    internal_message_namespace["gm2tl_freeze_role_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_freeze_role_ack);
    internal_message_namespace["gm2tl_kick_role_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_kick_role_ack);
    internal_message_namespace["gm2tl_send_mail_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_send_mail_ack);
    internal_message_namespace["gm2tl_announce_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_announce_ack);
    internal_message_namespace["gm2tl_get_announce_list_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_get_announce_list_ack);
    internal_message_namespace["gm2tl_del_announce_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_del_announce_ack);
    internal_message_namespace["gm2tl_log_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_log_ack);
    internal_message_namespace["gm2tl_exe_gm_str_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_exe_gm_str_ack);
    internal_message_namespace["gm2tl_load_role_data_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_load_role_data_ack);
    internal_message_namespace["gm2tl_modify_role_data_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_modify_role_data_ack);
    internal_message_namespace["gm2tl_query_name_to_id_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_query_name_to_id_ack);
    internal_message_namespace["gm2tl_error_str"] = static_cast<lua_Number>(InternalMessage::gm2tl_error_str);
    internal_message_namespace["gm2tl_role_exe_gm_cmd"] = static_cast<lua_Number>(InternalMessage::gm2tl_role_exe_gm_cmd);
    internal_message_namespace["gm2tl_select_group_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_select_group_ack);
    internal_message_namespace["gm2tl_query_exchange_log_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_query_exchange_log_ack);
    internal_message_namespace["gm2tl_query_exchange_history_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_query_exchange_history_ack);
    internal_message_namespace["gm2tl_exchange_price"] = static_cast<lua_Number>(InternalMessage::gm2tl_exchange_price);
    internal_message_namespace["gm2tl_query_order_detail_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_query_order_detail_ack);
    internal_message_namespace["gm2tl_add_system_order_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_add_system_order_ack);
    internal_message_namespace["gm2tl_del_system_order_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_del_system_order_ack);
    internal_message_namespace["gm2tl_query_sys_exchange_info_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_query_sys_exchange_info_ack);
    internal_message_namespace["gm2tl_get_exchange_limit_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_get_exchange_limit_ack);
    internal_message_namespace["gm2tl_set_exchange_limit_ack"] = static_cast<lua_Number>(InternalMessage::gm2tl_set_exchange_limit_ack);
    internal_message_namespace["tl_end"] = static_cast<lua_Number>(InternalMessage::tl_end);
}

}
