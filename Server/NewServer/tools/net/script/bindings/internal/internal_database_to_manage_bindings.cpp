#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/d2m_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_database_to_manage_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["d2m_begin"] = static_cast<lua_Number>(InternalMessage::d2m_begin);
    internal_message_namespace["d2m_register"] = static_cast<lua_Number>(InternalMessage::d2m_register);
    internal_message_namespace["d2m_ready"] = static_cast<lua_Number>(InternalMessage::d2m_ready);
    internal_message_namespace["d2m_close_ack"] = static_cast<lua_Number>(InternalMessage::d2m_close_ack);
    internal_message_namespace["d2m_create_role"] = static_cast<lua_Number>(InternalMessage::d2m_create_role);
    internal_message_namespace["d2m_can_delete_role"] = static_cast<lua_Number>(InternalMessage::d2m_can_delete_role);
    internal_message_namespace["d2m_delete_role"] = static_cast<lua_Number>(InternalMessage::d2m_delete_role);
    internal_message_namespace["d2m_leave_db_ack"] = static_cast<lua_Number>(InternalMessage::d2m_leave_db_ack);
    internal_message_namespace["d2m_clear_role_cache_ack"] = static_cast<lua_Number>(InternalMessage::d2m_clear_role_cache_ack);
    internal_message_namespace["d2m_end"] = static_cast<lua_Number>(InternalMessage::d2m_end);
    auto internal_message_d2m_register_type = cqyh::lua::usertype<InternalMessage::D2M_REGISTER>(L, internal_message_namespace, "D2M_REGISTER", "InternalMessage::D2M_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_REGISTER(); });
    internal_message_d2m_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_REGISTER>(new InternalMessage::D2M_REGISTER()); });
    internal_message_d2m_register_type["dwAddr"] = sol::property([](const InternalMessage::D2M_REGISTER& self) { return self.dwAddr; }, [](InternalMessage::D2M_REGISTER& self, decltype(InternalMessage::D2M_REGISTER::dwAddr) value) { self.dwAddr = value; });
    internal_message_d2m_register_type["wPort"] = sol::property([](const InternalMessage::D2M_REGISTER& self) { return self.wPort; }, [](InternalMessage::D2M_REGISTER& self, decltype(InternalMessage::D2M_REGISTER::wPort) value) { self.wPort = value; });
    auto internal_message_d2m_ready_type = cqyh::lua::usertype<InternalMessage::D2M_READY>(L, internal_message_namespace, "D2M_READY", "InternalMessage::D2M_READY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_ready_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_READY(); });
    internal_message_d2m_ready_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_READY>(new InternalMessage::D2M_READY()); });
    auto internal_message_d2m_close_ack_type = cqyh::lua::usertype<InternalMessage::D2M_CLOSE_ACK>(L, internal_message_namespace, "D2M_CLOSE_ACK", "InternalMessage::D2M_CLOSE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_close_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_CLOSE_ACK(); });
    internal_message_d2m_close_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_CLOSE_ACK>(new InternalMessage::D2M_CLOSE_ACK()); });
    auto internal_message_d2m_create_role_type = cqyh::lua::usertype<InternalMessage::D2M_CREATE_ROLE>(L, internal_message_namespace, "D2M_CREATE_ROLE", "InternalMessage::D2M_CREATE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_create_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_CREATE_ROLE(); });
    internal_message_d2m_create_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_CREATE_ROLE>(new InternalMessage::D2M_CREATE_ROLE()); });
    internal_message_d2m_create_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2M_CREATE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::D2M_CREATE_ROLE& self, decltype(InternalMessage::D2M_CREATE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2m_create_role_type["szUserName"] = cqyh::lua::string_property(&InternalMessage::D2M_CREATE_ROLE::szUserName);
    internal_message_d2m_create_role_type["byServerGroup"] = sol::property([](const InternalMessage::D2M_CREATE_ROLE& self) { return self.byServerGroup; }, [](InternalMessage::D2M_CREATE_ROLE& self, decltype(InternalMessage::D2M_CREATE_ROLE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_d2m_create_role_type["BaseData"] = cqyh::lua::string_property(&InternalMessage::D2M_CREATE_ROLE::BaseData);
    auto internal_message_d2m_can_delete_role_type = cqyh::lua::usertype<InternalMessage::D2M_CAN_DELETE_ROLE>(L, internal_message_namespace, "D2M_CAN_DELETE_ROLE", "InternalMessage::D2M_CAN_DELETE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_can_delete_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_CAN_DELETE_ROLE(); });
    internal_message_d2m_can_delete_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_CAN_DELETE_ROLE>(new InternalMessage::D2M_CAN_DELETE_ROLE()); });
    internal_message_d2m_can_delete_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2M_CAN_DELETE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::D2M_CAN_DELETE_ROLE& self, decltype(InternalMessage::D2M_CAN_DELETE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2m_can_delete_role_type["dwRoleID"] = sol::property([](const InternalMessage::D2M_CAN_DELETE_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::D2M_CAN_DELETE_ROLE& self, decltype(InternalMessage::D2M_CAN_DELETE_ROLE::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_d2m_delete_role_type = cqyh::lua::usertype<InternalMessage::D2M_DELETE_ROLE>(L, internal_message_namespace, "D2M_DELETE_ROLE", "InternalMessage::D2M_DELETE_ROLE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_delete_role_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_DELETE_ROLE(); });
    internal_message_d2m_delete_role_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_DELETE_ROLE>(new InternalMessage::D2M_DELETE_ROLE()); });
    internal_message_d2m_delete_role_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2M_DELETE_ROLE& self) { return self.dwClientSessionID; }, [](InternalMessage::D2M_DELETE_ROLE& self, decltype(InternalMessage::D2M_DELETE_ROLE::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2m_delete_role_type["dwRoleID"] = sol::property([](const InternalMessage::D2M_DELETE_ROLE& self) { return self.dwRoleID; }, [](InternalMessage::D2M_DELETE_ROLE& self, decltype(InternalMessage::D2M_DELETE_ROLE::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_d2m_leave_db_ack_type = cqyh::lua::usertype<InternalMessage::D2M_LEAVE_DB_ACK>(L, internal_message_namespace, "D2M_LEAVE_DB_ACK", "InternalMessage::D2M_LEAVE_DB_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_leave_db_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_LEAVE_DB_ACK(); });
    internal_message_d2m_leave_db_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_LEAVE_DB_ACK>(new InternalMessage::D2M_LEAVE_DB_ACK()); });
    internal_message_d2m_leave_db_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2M_LEAVE_DB_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2M_LEAVE_DB_ACK& self, decltype(InternalMessage::D2M_LEAVE_DB_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    auto internal_message_d2m_clear_role_cache_ack_type = cqyh::lua::usertype<InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK>(L, internal_message_namespace, "D2M_CLEAR_ROLE_CACHE_ACK", "InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2m_clear_role_cache_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK(); });
    internal_message_d2m_clear_role_cache_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK>(new InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK()); });
    internal_message_d2m_clear_role_cache_ack_type["dwRoleID"] = sol::property([](const InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self, decltype(InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_d2m_clear_role_cache_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self, decltype(InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_d2m_clear_role_cache_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self, decltype(InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_d2m_clear_role_cache_ack_type["byResult"] = sol::property([](const InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self) { return self.byResult; }, [](InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK& self, decltype(InternalMessage::D2M_CLEAR_ROLE_CACHE_ACK::byResult) value) { self.byResult = value; });
}

}
