#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/m2t_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_manage_to_gate_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["m2t_begin"] = static_cast<lua_Number>(InternalMessage::m2t_begin);
    internal_message_namespace["m2t_register_ack"] = static_cast<lua_Number>(InternalMessage::m2t_register_ack);
    internal_message_namespace["m2t_enter_gate_ack"] = static_cast<lua_Number>(InternalMessage::m2t_enter_gate_ack);
    internal_message_namespace["m2t_query_scene_ack"] = static_cast<lua_Number>(InternalMessage::m2t_query_scene_ack);
    internal_message_namespace["m2t_close_client_session"] = static_cast<lua_Number>(InternalMessage::m2t_close_client_session);
    internal_message_namespace["m2t_return_select_role"] = static_cast<lua_Number>(InternalMessage::m2t_return_select_role);
    internal_message_namespace["m2t_change_gs"] = static_cast<lua_Number>(InternalMessage::m2t_change_gs);
    internal_message_namespace["m2t_client_msg"] = static_cast<lua_Number>(InternalMessage::m2t_client_msg);
    internal_message_namespace["m2t_broadcast_client_msg"] = static_cast<lua_Number>(InternalMessage::m2t_broadcast_client_msg);
    internal_message_namespace["m2t_switch_server_group_state"] = static_cast<lua_Number>(InternalMessage::m2t_switch_server_group_state);
    internal_message_namespace["m2t_gm_command"] = static_cast<lua_Number>(InternalMessage::m2t_gm_command);
    internal_message_namespace["m2t_check_new_name"] = static_cast<lua_Number>(InternalMessage::m2t_check_new_name);
    internal_message_namespace["m2t_end"] = static_cast<lua_Number>(InternalMessage::m2t_end);
    auto internal_message_m2t_register_ack_type = cqyh::lua::usertype<InternalMessage::M2T_REGISTER_ACK>(L, internal_message_namespace, "M2T_REGISTER_ACK", "InternalMessage::M2T_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_REGISTER_ACK(); });
    internal_message_m2t_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_REGISTER_ACK>(new InternalMessage::M2T_REGISTER_ACK()); });
    internal_message_m2t_register_ack_type["dwGTSessionID"] = sol::property([](const InternalMessage::M2T_REGISTER_ACK& self) { return self.dwGTSessionID; }, [](InternalMessage::M2T_REGISTER_ACK& self, decltype(InternalMessage::M2T_REGISTER_ACK::dwGTSessionID) value) { self.dwGTSessionID = value; });
    auto internal_message_m2t_enter_gate_type = cqyh::lua::usertype<InternalMessage::M2T_ENTER_GATE>(L, internal_message_namespace, "M2T_ENTER_GATE", "InternalMessage::M2T_ENTER_GATE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_enter_gate_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_ENTER_GATE(); });
    internal_message_m2t_enter_gate_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_ENTER_GATE>(new InternalMessage::M2T_ENTER_GATE()); });
    internal_message_m2t_enter_gate_type["dwSessionID"] = sol::property([](const InternalMessage::M2T_ENTER_GATE& self) { return self.dwSessionID; }, [](InternalMessage::M2T_ENTER_GATE& self, decltype(InternalMessage::M2T_ENTER_GATE::dwSessionID) value) { self.dwSessionID = value; });
    internal_message_m2t_enter_gate_type["nErrCode"] = sol::property([](const InternalMessage::M2T_ENTER_GATE& self) { return self.nErrCode; }, [](InternalMessage::M2T_ENTER_GATE& self, decltype(InternalMessage::M2T_ENTER_GATE::nErrCode) value) { self.nErrCode = value; });
    internal_message_m2t_enter_gate_type["dwQueueLen"] = sol::property([](const InternalMessage::M2T_ENTER_GATE& self) { return self.dwQueueLen; }, [](InternalMessage::M2T_ENTER_GATE& self, decltype(InternalMessage::M2T_ENTER_GATE::dwQueueLen) value) { self.dwQueueLen = value; });
    auto internal_message_m2t_query_scene_ack_type = cqyh::lua::usertype<InternalMessage::M2T_QUERY_SCENE_ACK>(L, internal_message_namespace, "M2T_QUERY_SCENE_ACK", "InternalMessage::M2T_QUERY_SCENE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_query_scene_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_QUERY_SCENE_ACK(); });
    internal_message_m2t_query_scene_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_QUERY_SCENE_ACK>(new InternalMessage::M2T_QUERY_SCENE_ACK()); });
    internal_message_m2t_query_scene_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2T_QUERY_SCENE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::M2T_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2T_QUERY_SCENE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2t_query_scene_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2T_QUERY_SCENE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2T_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2T_QUERY_SCENE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2t_query_scene_ack_type["dwGSSessionID"] = sol::property([](const InternalMessage::M2T_QUERY_SCENE_ACK& self) { return self.dwGSSessionID; }, [](InternalMessage::M2T_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2T_QUERY_SCENE_ACK::dwGSSessionID) value) { self.dwGSSessionID = value; });
    internal_message_m2t_query_scene_ack_type["nErrorCode"] = sol::property([](const InternalMessage::M2T_QUERY_SCENE_ACK& self) { return self.nErrorCode; }, [](InternalMessage::M2T_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2T_QUERY_SCENE_ACK::nErrorCode) value) { self.nErrorCode = value; });
    internal_message_m2t_query_scene_ack_type["nErrCodeParam1"] = sol::property([](const InternalMessage::M2T_QUERY_SCENE_ACK& self) { return self.nErrCodeParam1; }, [](InternalMessage::M2T_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2T_QUERY_SCENE_ACK::nErrCodeParam1) value) { self.nErrCodeParam1 = value; });
    internal_message_m2t_query_scene_ack_type["nErrCodeParam2"] = sol::property([](const InternalMessage::M2T_QUERY_SCENE_ACK& self) { return self.nErrCodeParam2; }, [](InternalMessage::M2T_QUERY_SCENE_ACK& self, decltype(InternalMessage::M2T_QUERY_SCENE_ACK::nErrCodeParam2) value) { self.nErrCodeParam2 = value; });
    auto internal_message_m2t_return_select_role_type = cqyh::lua::usertype<InternalMessage::M2T_RETURN_SELECT_ROLE>(L, internal_message_namespace, "M2T_RETURN_SELECT_ROLE", "InternalMessage::M2T_RETURN_SELECT_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_return_select_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_RETURN_SELECT_ROLE(); });
    internal_message_m2t_return_select_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_RETURN_SELECT_ROLE>(new InternalMessage::M2T_RETURN_SELECT_ROLE()); });
    internal_message_m2t_return_select_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2T_RETURN_SELECT_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::M2T_RETURN_SELECT_ROLE& self, decltype(InternalMessage::M2T_RETURN_SELECT_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    auto internal_message_m2t_change_gs_type = cqyh::lua::usertype<InternalMessage::M2T_CHANGE_GS>(L, internal_message_namespace, "M2T_CHANGE_GS", "InternalMessage::M2T_CHANGE_GS", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_change_gs_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_CHANGE_GS(); });
    internal_message_m2t_change_gs_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_CHANGE_GS>(new InternalMessage::M2T_CHANGE_GS()); });
    internal_message_m2t_change_gs_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2T_CHANGE_GS& self) { return self.dwClientSessionID; }, [](InternalMessage::M2T_CHANGE_GS& self, decltype(InternalMessage::M2T_CHANGE_GS::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2t_change_gs_type["dwGSSessionID"] = sol::property([](const InternalMessage::M2T_CHANGE_GS& self) { return self.dwGSSessionID; }, [](InternalMessage::M2T_CHANGE_GS& self, decltype(InternalMessage::M2T_CHANGE_GS::dwGSSessionID) value) { self.dwGSSessionID = value; });
    auto internal_message_m2t_client_msg_type = cqyh::lua::usertype<InternalMessage::M2T_CLIENT_MSG>(L, internal_message_namespace, "M2T_CLIENT_MSG", "InternalMessage::M2T_CLIENT_MSG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_client_msg_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_CLIENT_MSG(); });
    internal_message_m2t_client_msg_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_CLIENT_MSG>(new InternalMessage::M2T_CLIENT_MSG()); });
    internal_message_m2t_client_msg_type["dwSessionID"] = sol::property([](const InternalMessage::M2T_CLIENT_MSG& self) { return self.dwSessionID; }, [](InternalMessage::M2T_CLIENT_MSG& self, decltype(InternalMessage::M2T_CLIENT_MSG::dwSessionID) value) { self.dwSessionID = value; });
    internal_message_m2t_client_msg_type["szData"] = cqyh::lua::string_property(&InternalMessage::M2T_CLIENT_MSG::szData);
    auto internal_message_m2t_broadcast_client_msg_type = cqyh::lua::usertype<InternalMessage::M2T_BROADCAST_CLIENT_MSG>(L, internal_message_namespace, "M2T_BROADCAST_CLIENT_MSG", "InternalMessage::M2T_BROADCAST_CLIENT_MSG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_broadcast_client_msg_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_BROADCAST_CLIENT_MSG(); });
    internal_message_m2t_broadcast_client_msg_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_BROADCAST_CLIENT_MSG>(new InternalMessage::M2T_BROADCAST_CLIENT_MSG()); });
    internal_message_m2t_broadcast_client_msg_type["wSessionCount"] = sol::property([](const InternalMessage::M2T_BROADCAST_CLIENT_MSG& self) { return self.wSessionCount; }, [](InternalMessage::M2T_BROADCAST_CLIENT_MSG& self, decltype(InternalMessage::M2T_BROADCAST_CLIENT_MSG::wSessionCount) value) { self.wSessionCount = value; });
    internal_message_m2t_broadcast_client_msg_type["dwSessionIDList"] = cqyh::lua::array_property(&InternalMessage::M2T_BROADCAST_CLIENT_MSG::dwSessionIDList);
    auto internal_message_m2t_close_client_session_type = cqyh::lua::usertype<InternalMessage::M2T_CLOSE_CLIENT_SESSION>(L, internal_message_namespace, "M2T_CLOSE_CLIENT_SESSION", "InternalMessage::M2T_CLOSE_CLIENT_SESSION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_close_client_session_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_CLOSE_CLIENT_SESSION(); });
    internal_message_m2t_close_client_session_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_CLOSE_CLIENT_SESSION>(new InternalMessage::M2T_CLOSE_CLIENT_SESSION()); });
    internal_message_m2t_close_client_session_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2T_CLOSE_CLIENT_SESSION& self) { return self.dwClientSessionID; }, [](InternalMessage::M2T_CLOSE_CLIENT_SESSION& self, decltype(InternalMessage::M2T_CLOSE_CLIENT_SESSION::dwClientSessionID) value) { self.dwClientSessionID = value; });
    auto internal_message_m2t_switch_server_group_state_type = cqyh::lua::usertype<InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE>(L, internal_message_namespace, "M2T_SWITCH_SERVER_GROUP_STATE", "InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_switch_server_group_state_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE(); });
    internal_message_m2t_switch_server_group_state_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE>(new InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE()); });
    internal_message_m2t_switch_server_group_state_type["byServerGroup"] = sol::property([](const InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE& self) { return self.byServerGroup; }, [](InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE& self, decltype(InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_m2t_switch_server_group_state_type["byOpened"] = sol::property([](const InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE& self) { return self.byOpened; }, [](InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE& self, decltype(InternalMessage::M2T_SWITCH_SERVER_GROUP_STATE::byOpened) value) { self.byOpened = value; });
    auto internal_message_m2t_gm_command_type = cqyh::lua::usertype<InternalMessage::M2T_GM_COMMAND>(L, internal_message_namespace, "M2T_GM_COMMAND", "InternalMessage::M2T_GM_COMMAND", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_gm_command_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_GM_COMMAND(); });
    internal_message_m2t_gm_command_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_GM_COMMAND>(new InternalMessage::M2T_GM_COMMAND()); });
    internal_message_m2t_gm_command_type["szGMCommand"] = cqyh::lua::string_property(&InternalMessage::M2T_GM_COMMAND::szGMCommand);
    auto internal_message_m2t_check_new_name_type = cqyh::lua::usertype<InternalMessage::M2T_CHECK_NEW_NAME>(L, internal_message_namespace, "M2T_CHECK_NEW_NAME", "InternalMessage::M2T_CHECK_NEW_NAME", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2t_check_new_name_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2T_CHECK_NEW_NAME(); });
    internal_message_m2t_check_new_name_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2T_CHECK_NEW_NAME>(new InternalMessage::M2T_CHECK_NEW_NAME()); });
    internal_message_m2t_check_new_name_type["nErrorCode"] = sol::property([](const InternalMessage::M2T_CHECK_NEW_NAME& self) { return self.nErrorCode; }, [](InternalMessage::M2T_CHECK_NEW_NAME& self, decltype(InternalMessage::M2T_CHECK_NEW_NAME::nErrorCode) value) { self.nErrorCode = value; });
    internal_message_m2t_check_new_name_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2T_CHECK_NEW_NAME& self) { return self.dwClientSessionID; }, [](InternalMessage::M2T_CHECK_NEW_NAME& self, decltype(InternalMessage::M2T_CHECK_NEW_NAME::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2t_check_new_name_type["dwID"] = sol::property([](const InternalMessage::M2T_CHECK_NEW_NAME& self) { return self.dwID; }, [](InternalMessage::M2T_CHECK_NEW_NAME& self, decltype(InternalMessage::M2T_CHECK_NEW_NAME::dwID) value) { self.dwID = value; });
    internal_message_m2t_check_new_name_type["szName"] = cqyh::lua::string_property(&InternalMessage::M2T_CHECK_NEW_NAME::szName);
    internal_message_m2t_check_new_name_type["UserData"] = cqyh::lua::string_property(&InternalMessage::M2T_CHECK_NEW_NAME::UserData);
}

}
