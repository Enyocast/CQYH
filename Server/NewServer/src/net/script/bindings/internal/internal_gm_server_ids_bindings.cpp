#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmsvr_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_gm_server_ids_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["gmsvr_begin"] = static_cast<lua_Number>(InternalMessage::gmsvr_begin);
    internal_message_namespace["m2gm_register"] = static_cast<lua_Number>(InternalMessage::m2gm_register);
    internal_message_namespace["m2gm_clear_role_cache_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_clear_role_cache_ack);
    internal_message_namespace["m2gm_unlock_role_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_unlock_role_ack);
    internal_message_namespace["m2gm_query_role_data_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_query_role_data_ack);
    internal_message_namespace["m2gm_forbid_chat_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_forbid_chat_ack);
    internal_message_namespace["m2gm_freeze_role_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_freeze_role_ack);
    internal_message_namespace["m2gm_kick_role_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_kick_role_ack);
    internal_message_namespace["m2gm_send_mail_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_send_mail_ack);
    internal_message_namespace["m2gm_announce_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_announce_ack);
    internal_message_namespace["m2gm_get_announce_list_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_get_announce_list_ack);
    internal_message_namespace["m2gm_del_announce_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_del_announce_ack);
    internal_message_namespace["m2gm_exe_gm_str_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_exe_gm_str_ack);
    internal_message_namespace["m2gm_gm_str_cmd_log"] = static_cast<lua_Number>(InternalMessage::m2gm_gm_str_cmd_log);
    internal_message_namespace["m2gm_del_mail_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_del_mail_ack);
    internal_message_namespace["m2gm_check_role_freeze_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_check_role_freeze_ack);
    internal_message_namespace["m2gm_get_exchange_price_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_get_exchange_price_ack);
    internal_message_namespace["m2gm_get_exchange_price_detail_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_get_exchange_price_detail_ack);
    internal_message_namespace["m2gm_add_system_order_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_add_system_order_ack);
    internal_message_namespace["m2gm_cancel_system_order_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_cancel_system_order_ack);
    internal_message_namespace["m2gm_get_exchange_limit_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_get_exchange_limit_ack);
    internal_message_namespace["m2gm_set_exchange_limit_ack"] = static_cast<lua_Number>(InternalMessage::m2gm_set_exchange_limit_ack);
    internal_message_namespace["gm2m_register_ack"] = static_cast<lua_Number>(InternalMessage::gm2m_register_ack);
    internal_message_namespace["gm2m_clear_role_cache"] = static_cast<lua_Number>(InternalMessage::gm2m_clear_role_cache);
    internal_message_namespace["gm2m_unlock_role"] = static_cast<lua_Number>(InternalMessage::gm2m_unlock_role);
    internal_message_namespace["gm2m_query_role_data"] = static_cast<lua_Number>(InternalMessage::gm2m_query_role_data);
    internal_message_namespace["gm2m_forbid_chat"] = static_cast<lua_Number>(InternalMessage::gm2m_forbid_chat);
    internal_message_namespace["gm2m_freeze_role"] = static_cast<lua_Number>(InternalMessage::gm2m_freeze_role);
    internal_message_namespace["gm2m_kick_role"] = static_cast<lua_Number>(InternalMessage::gm2m_kick_role);
    internal_message_namespace["gm2m_send_mail"] = static_cast<lua_Number>(InternalMessage::gm2m_send_mail);
    internal_message_namespace["gm2m_announce"] = static_cast<lua_Number>(InternalMessage::gm2m_announce);
    internal_message_namespace["gm2m_get_announce_list"] = static_cast<lua_Number>(InternalMessage::gm2m_get_announce_list);
    internal_message_namespace["gm2m_del_announce"] = static_cast<lua_Number>(InternalMessage::gm2m_del_announce);
    internal_message_namespace["gm2m_exe_gm_str"] = static_cast<lua_Number>(InternalMessage::gm2m_exe_gm_str);
    internal_message_namespace["gm2m_del_mail"] = static_cast<lua_Number>(InternalMessage::gm2m_del_mail);
    internal_message_namespace["gm2m_check_role_freeze"] = static_cast<lua_Number>(InternalMessage::gm2m_check_role_freeze);
    internal_message_namespace["gm2m_get_exchange_price"] = static_cast<lua_Number>(InternalMessage::gm2m_get_exchange_price);
    internal_message_namespace["gm2m_get_exchange_price_detail"] = static_cast<lua_Number>(InternalMessage::gm2m_get_exchange_price_detail);
    internal_message_namespace["gm2m_add_system_order"] = static_cast<lua_Number>(InternalMessage::gm2m_add_system_order);
    internal_message_namespace["gm2m_cancel_system_order"] = static_cast<lua_Number>(InternalMessage::gm2m_cancel_system_order);
    internal_message_namespace["gm2m_get_exchange_limit"] = static_cast<lua_Number>(InternalMessage::gm2m_get_exchange_limit);
    internal_message_namespace["gm2m_set_exchange_limit"] = static_cast<lua_Number>(InternalMessage::gm2m_set_exchange_limit);
    internal_message_namespace["gmsvr_end"] = static_cast<lua_Number>(InternalMessage::gmsvr_end);
}

}
