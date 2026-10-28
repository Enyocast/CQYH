#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/d2g_message.h"

namespace cqyh::net::bindings {

void register_internal_database_to_game_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["d2g_begin"] = static_cast<lua_Number>(InternalMessage::d2g_begin);
    internal_message_namespace["d2g_register_ack"] = static_cast<lua_Number>(InternalMessage::d2g_register_ack);
    internal_message_namespace["d2g_load_lock_role_data_ack"] = static_cast<lua_Number>(InternalMessage::d2g_load_lock_role_data_ack);
    internal_message_namespace["d2g_unlock_role_data_ack"] = static_cast<lua_Number>(InternalMessage::d2g_unlock_role_data_ack);
    internal_message_namespace["d2g_load_lock_role_data_fail_ack"] = static_cast<lua_Number>(InternalMessage::d2g_load_lock_role_data_fail_ack);
    internal_message_namespace["d2g_end"] = static_cast<lua_Number>(InternalMessage::d2g_end);
    auto internal_message_d2g_register_ack_type = cqyh::lua::usertype<InternalMessage::D2G_REGISTER_ACK>(L, internal_message_namespace, "D2G_REGISTER_ACK", "InternalMessage::D2G_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2g_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2G_REGISTER_ACK(); });
    internal_message_d2g_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2G_REGISTER_ACK>(new InternalMessage::D2G_REGISTER_ACK()); });
    auto internal_message_d2g_load_lock_role_data_ack_type = cqyh::lua::usertype<InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK>(L, internal_message_namespace, "D2G_LOAD_LOCK_ROLE_DATA_ACK", "InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2g_load_lock_role_data_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK(); });
    internal_message_d2g_load_lock_role_data_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK>(new InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK()); });
    internal_message_d2g_load_lock_role_data_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK& self, decltype(InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2g_load_lock_role_data_ack_type["dwRoleID"] = sol::property([](const InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK& self) { return self.dwRoleID; }, [](InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK& self, decltype(InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_d2g_load_lock_role_data_ack_type["dwDataSize"] = sol::property([](const InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK& self) { return self.dwDataSize; }, [](InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK& self, decltype(InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK::dwDataSize) value) { self.dwDataSize = value; });
    internal_message_d2g_load_lock_role_data_ack_type["RoleData"] = cqyh::lua::string_property(&InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_ACK::RoleData);
    auto internal_message_d2g_unlock_role_data_ack_type = cqyh::lua::usertype<InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK>(L, internal_message_namespace, "D2G_UNLOCK_ROLE_DATA_ACK", "InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2g_unlock_role_data_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK(); });
    internal_message_d2g_unlock_role_data_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK>(new InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK()); });
    internal_message_d2g_unlock_role_data_ack_type["nError"] = sol::property([](const InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK& self) { return self.nError; }, [](InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK& self, decltype(InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK::nError) value) { self.nError = value; });
    internal_message_d2g_unlock_role_data_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK& self, decltype(InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2g_unlock_role_data_ack_type["dwRoleID"] = sol::property([](const InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK& self) { return self.dwRoleID; }, [](InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK& self, decltype(InternalMessage::D2G_UNLOCK_ROLE_DATA_ACK::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_d2g_load_lock_role_data_fail_ack_type = cqyh::lua::usertype<InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK>(L, internal_message_namespace, "D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK", "InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_d2g_load_lock_role_data_fail_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK(); });
    internal_message_d2g_load_lock_role_data_fail_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK>(new InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK()); });
    internal_message_d2g_load_lock_role_data_fail_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK& self, decltype(InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_d2g_load_lock_role_data_fail_ack_type["dwRoleID"] = sol::property([](const InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK& self) { return self.dwRoleID; }, [](InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK& self, decltype(InternalMessage::D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK::dwRoleID) value) { self.dwRoleID = value; });
}

}
