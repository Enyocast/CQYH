#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/d2t_message.h"

namespace cqyh::net_tools::bindings {

void register_internal_database_to_gate_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["d2t_begin"] = static_cast<lua_Number>(InternalMessage::d2t_begin);
    internal_message_namespace["d2t_register_ack"] = static_cast<lua_Number>(InternalMessage::d2t_register_ack);
    internal_message_namespace["d2t_sync_role_list"] = static_cast<lua_Number>(InternalMessage::d2t_sync_role_list);
    internal_message_namespace["d2t_create_role_ack"] = static_cast<lua_Number>(InternalMessage::d2t_create_role_ack);
    internal_message_namespace["d2t_delete_role_ack"] = static_cast<lua_Number>(InternalMessage::d2t_delete_role_ack);
    internal_message_namespace["d2t_undelete_role_ack"] = static_cast<lua_Number>(InternalMessage::d2t_undelete_role_ack);
    internal_message_namespace["d2t_forever_delete_role_ack"] = static_cast<lua_Number>(InternalMessage::d2t_forever_delete_role_ack);
    internal_message_namespace["d2t_close_client_session"] = static_cast<lua_Number>(InternalMessage::d2t_close_client_session);
    internal_message_namespace["d2t_end"] = static_cast<lua_Number>(InternalMessage::d2t_end);
    auto internal_message_d2t_register_ack_type = cqyh::lua::usertype<InternalMessage::D2T_REGISTER_ACK>(L, internal_message_namespace, "D2T_REGISTER_ACK", "InternalMessage::D2T_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2t_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2T_REGISTER_ACK(); });
    internal_message_d2t_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2T_REGISTER_ACK>(new InternalMessage::D2T_REGISTER_ACK()); });
    auto internal_message_d2t_create_role_ack_type = cqyh::lua::usertype<InternalMessage::D2T_CREATE_ROLE_ACK>(L, internal_message_namespace, "D2T_CREATE_ROLE_ACK", "InternalMessage::D2T_CREATE_ROLE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2t_create_role_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2T_CREATE_ROLE_ACK(); });
    internal_message_d2t_create_role_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2T_CREATE_ROLE_ACK>(new InternalMessage::D2T_CREATE_ROLE_ACK()); });
    internal_message_d2t_create_role_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2T_CREATE_ROLE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2T_CREATE_ROLE_ACK& self, decltype(InternalMessage::D2T_CREATE_ROLE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2t_create_role_ack_type["nErrCode"] = sol::property([](const InternalMessage::D2T_CREATE_ROLE_ACK& self) { return self.nErrCode; }, [](InternalMessage::D2T_CREATE_ROLE_ACK& self, decltype(InternalMessage::D2T_CREATE_ROLE_ACK::nErrCode) value) { self.nErrCode = value; });
    internal_message_d2t_create_role_ack_type["BaseData"] = cqyh::lua::string_property(&InternalMessage::D2T_CREATE_ROLE_ACK::BaseData);
    auto internal_message_d2t_delete_role_ack_type = cqyh::lua::usertype<InternalMessage::D2T_DELETE_ROLE_ACK>(L, internal_message_namespace, "D2T_DELETE_ROLE_ACK", "InternalMessage::D2T_DELETE_ROLE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2t_delete_role_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2T_DELETE_ROLE_ACK(); });
    internal_message_d2t_delete_role_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2T_DELETE_ROLE_ACK>(new InternalMessage::D2T_DELETE_ROLE_ACK()); });
    internal_message_d2t_delete_role_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2T_DELETE_ROLE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2T_DELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_DELETE_ROLE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2t_delete_role_ack_type["dwRoleID"] = sol::property([](const InternalMessage::D2T_DELETE_ROLE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::D2T_DELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_DELETE_ROLE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_d2t_delete_role_ack_type["nErrCode"] = sol::property([](const InternalMessage::D2T_DELETE_ROLE_ACK& self) { return self.nErrCode; }, [](InternalMessage::D2T_DELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_DELETE_ROLE_ACK::nErrCode) value) { self.nErrCode = value; });
    auto internal_message_d2t_undelete_role_ack_type = cqyh::lua::usertype<InternalMessage::D2T_UNDELETE_ROLE_ACK>(L, internal_message_namespace, "D2T_UNDELETE_ROLE_ACK", "InternalMessage::D2T_UNDELETE_ROLE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2t_undelete_role_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2T_UNDELETE_ROLE_ACK(); });
    internal_message_d2t_undelete_role_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2T_UNDELETE_ROLE_ACK>(new InternalMessage::D2T_UNDELETE_ROLE_ACK()); });
    internal_message_d2t_undelete_role_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2T_UNDELETE_ROLE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2T_UNDELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_UNDELETE_ROLE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2t_undelete_role_ack_type["dwRoleID"] = sol::property([](const InternalMessage::D2T_UNDELETE_ROLE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::D2T_UNDELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_UNDELETE_ROLE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_d2t_undelete_role_ack_type["nErrCode"] = sol::property([](const InternalMessage::D2T_UNDELETE_ROLE_ACK& self) { return self.nErrCode; }, [](InternalMessage::D2T_UNDELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_UNDELETE_ROLE_ACK::nErrCode) value) { self.nErrCode = value; });
    auto internal_message_d2t_forever_delete_role_ack_type = cqyh::lua::usertype<InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK>(L, internal_message_namespace, "D2T_FOREVER_DELETE_ROLE_ACK", "InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2t_forever_delete_role_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK(); });
    internal_message_d2t_forever_delete_role_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK>(new InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK()); });
    internal_message_d2t_forever_delete_role_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2t_forever_delete_role_ack_type["dwRoleID"] = sol::property([](const InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_d2t_forever_delete_role_ack_type["nErrCode"] = sol::property([](const InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK& self) { return self.nErrCode; }, [](InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK& self, decltype(InternalMessage::D2T_FOREVER_DELETE_ROLE_ACK::nErrCode) value) { self.nErrCode = value; });
    auto internal_message_d2t_sync_role_list_type = cqyh::lua::usertype<InternalMessage::D2T_SYNC_ROLE_LIST>(L, internal_message_namespace, "D2T_SYNC_ROLE_LIST", "InternalMessage::D2T_SYNC_ROLE_LIST", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2t_sync_role_list_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2T_SYNC_ROLE_LIST(); });
    internal_message_d2t_sync_role_list_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2T_SYNC_ROLE_LIST>(new InternalMessage::D2T_SYNC_ROLE_LIST()); });
    internal_message_d2t_sync_role_list_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2T_SYNC_ROLE_LIST& self) { return self.dwClientSessionID; }, [](InternalMessage::D2T_SYNC_ROLE_LIST& self, decltype(InternalMessage::D2T_SYNC_ROLE_LIST::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2t_sync_role_list_type["nErrCode"] = sol::property([](const InternalMessage::D2T_SYNC_ROLE_LIST& self) { return self.nErrCode; }, [](InternalMessage::D2T_SYNC_ROLE_LIST& self, decltype(InternalMessage::D2T_SYNC_ROLE_LIST::nErrCode) value) { self.nErrCode = value; });
    internal_message_d2t_sync_role_list_type["byRoleCount"] = sol::property([](const InternalMessage::D2T_SYNC_ROLE_LIST& self) { return self.byRoleCount; }, [](InternalMessage::D2T_SYNC_ROLE_LIST& self, decltype(InternalMessage::D2T_SYNC_ROLE_LIST::byRoleCount) value) { self.byRoleCount = value; });
    internal_message_d2t_sync_role_list_type["BaseData"] = cqyh::lua::string_property(&InternalMessage::D2T_SYNC_ROLE_LIST::BaseData);
    auto internal_message_d2t_close_client_session_type = cqyh::lua::usertype<InternalMessage::D2T_CLOSE_CLIENT_SESSION>(L, internal_message_namespace, "D2T_CLOSE_CLIENT_SESSION", "InternalMessage::D2T_CLOSE_CLIENT_SESSION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2t_close_client_session_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2T_CLOSE_CLIENT_SESSION(); });
    internal_message_d2t_close_client_session_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2T_CLOSE_CLIENT_SESSION>(new InternalMessage::D2T_CLOSE_CLIENT_SESSION()); });
    internal_message_d2t_close_client_session_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2T_CLOSE_CLIENT_SESSION& self) { return self.dwClientSessionID; }, [](InternalMessage::D2T_CLOSE_CLIENT_SESSION& self, decltype(InternalMessage::D2T_CLOSE_CLIENT_SESSION::dwClientSessionID) value) { self.dwClientSessionID = value; });
}

}
