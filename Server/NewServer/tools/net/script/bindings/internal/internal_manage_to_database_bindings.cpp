#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/m2d_message.h"

namespace cqyh::net_tools::bindings {

void register_internal_manage_to_database_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["m2d_begin"] = static_cast<lua_Number>(InternalMessage::m2d_begin);
    internal_message_namespace["m2d_register_ack"] = static_cast<lua_Number>(InternalMessage::m2d_register_ack);
    internal_message_namespace["m2d_create_role_ack"] = static_cast<lua_Number>(InternalMessage::m2d_create_role_ack);
    internal_message_namespace["m2d_can_delete_role_ack"] = static_cast<lua_Number>(InternalMessage::m2d_can_delete_role_ack);
    internal_message_namespace["m2d_delete_role_ack"] = static_cast<lua_Number>(InternalMessage::m2d_delete_role_ack);
    internal_message_namespace["m2d_leave_db"] = static_cast<lua_Number>(InternalMessage::m2d_leave_db);
    internal_message_namespace["m2d_clear_role_cache"] = static_cast<lua_Number>(InternalMessage::m2d_clear_role_cache);
    internal_message_namespace["m2d_gm_command"] = static_cast<lua_Number>(InternalMessage::m2d_gm_command);
    internal_message_namespace["m2d_end"] = static_cast<lua_Number>(InternalMessage::m2d_end);
    auto internal_message_m2d_register_ack_type = cqyh::lua::usertype<InternalMessage::M2D_REGISTER_ACK>(L, internal_message_namespace, "M2D_REGISTER_ACK", "InternalMessage::M2D_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2d_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2D_REGISTER_ACK(); });
    internal_message_m2d_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2D_REGISTER_ACK>(new InternalMessage::M2D_REGISTER_ACK()); });
    internal_message_m2d_register_ack_type["szServerAddr"] = cqyh::lua::string_property(&InternalMessage::M2D_REGISTER_ACK::szServerAddr);
    internal_message_m2d_register_ack_type["szLoginName"] = cqyh::lua::string_property(&InternalMessage::M2D_REGISTER_ACK::szLoginName);
    internal_message_m2d_register_ack_type["szPassword"] = cqyh::lua::string_property(&InternalMessage::M2D_REGISTER_ACK::szPassword);
    internal_message_m2d_register_ack_type["szDBName"] = cqyh::lua::string_property(&InternalMessage::M2D_REGISTER_ACK::szDBName);
    internal_message_m2d_register_ack_type["szCharSet"] = cqyh::lua::string_property(&InternalMessage::M2D_REGISTER_ACK::szCharSet);
    internal_message_m2d_register_ack_type["dwServerPort"] = sol::property([](const InternalMessage::M2D_REGISTER_ACK& self) { return self.dwServerPort; }, [](InternalMessage::M2D_REGISTER_ACK& self, decltype(InternalMessage::M2D_REGISTER_ACK::dwServerPort) value) { self.dwServerPort = value; });
    auto internal_message_m2d_create_role_ack_type = cqyh::lua::usertype<InternalMessage::M2D_CREATE_ROLE_ACK>(L, internal_message_namespace, "M2D_CREATE_ROLE_ACK", "InternalMessage::M2D_CREATE_ROLE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2d_create_role_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2D_CREATE_ROLE_ACK(); });
    internal_message_m2d_create_role_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2D_CREATE_ROLE_ACK>(new InternalMessage::M2D_CREATE_ROLE_ACK()); });
    internal_message_m2d_create_role_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2D_CREATE_ROLE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::M2D_CREATE_ROLE_ACK& self, decltype(InternalMessage::M2D_CREATE_ROLE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2d_create_role_ack_type["BaseData"] = cqyh::lua::string_property(&InternalMessage::M2D_CREATE_ROLE_ACK::BaseData);
    auto internal_message_m2d_can_delete_role_ack_type = cqyh::lua::usertype<InternalMessage::M2D_CAN_DELETE_ROLE_ACK>(L, internal_message_namespace, "M2D_CAN_DELETE_ROLE_ACK", "InternalMessage::M2D_CAN_DELETE_ROLE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2d_can_delete_role_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2D_CAN_DELETE_ROLE_ACK(); });
    internal_message_m2d_can_delete_role_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2D_CAN_DELETE_ROLE_ACK>(new InternalMessage::M2D_CAN_DELETE_ROLE_ACK()); });
    internal_message_m2d_can_delete_role_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2D_CAN_DELETE_ROLE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::M2D_CAN_DELETE_ROLE_ACK& self, decltype(InternalMessage::M2D_CAN_DELETE_ROLE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2d_can_delete_role_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2D_CAN_DELETE_ROLE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2D_CAN_DELETE_ROLE_ACK& self, decltype(InternalMessage::M2D_CAN_DELETE_ROLE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2d_can_delete_role_ack_type["nResult"] = sol::property([](const InternalMessage::M2D_CAN_DELETE_ROLE_ACK& self) { return self.nResult; }, [](InternalMessage::M2D_CAN_DELETE_ROLE_ACK& self, decltype(InternalMessage::M2D_CAN_DELETE_ROLE_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_m2d_delete_role_ack_type = cqyh::lua::usertype<InternalMessage::M2D_DELETE_ROLE_ACK>(L, internal_message_namespace, "M2D_DELETE_ROLE_ACK", "InternalMessage::M2D_DELETE_ROLE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2d_delete_role_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2D_DELETE_ROLE_ACK(); });
    internal_message_m2d_delete_role_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2D_DELETE_ROLE_ACK>(new InternalMessage::M2D_DELETE_ROLE_ACK()); });
    internal_message_m2d_delete_role_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2D_DELETE_ROLE_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::M2D_DELETE_ROLE_ACK& self, decltype(InternalMessage::M2D_DELETE_ROLE_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2d_delete_role_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2D_DELETE_ROLE_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2D_DELETE_ROLE_ACK& self, decltype(InternalMessage::M2D_DELETE_ROLE_ACK::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_m2d_leave_db_type = cqyh::lua::usertype<InternalMessage::M2D_LEAVE_DB>(L, internal_message_namespace, "M2D_LEAVE_DB", "InternalMessage::M2D_LEAVE_DB", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2d_leave_db_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2D_LEAVE_DB(); });
    internal_message_m2d_leave_db_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2D_LEAVE_DB>(new InternalMessage::M2D_LEAVE_DB()); });
    internal_message_m2d_leave_db_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2D_LEAVE_DB& self) { return self.dwClientSessionID; }, [](InternalMessage::M2D_LEAVE_DB& self, decltype(InternalMessage::M2D_LEAVE_DB::dwClientSessionID) value) { self.dwClientSessionID = value; });
    auto internal_message_m2d_clear_role_cache_type = cqyh::lua::usertype<InternalMessage::M2D_CLEAR_ROLE_CACHE>(L, internal_message_namespace, "M2D_CLEAR_ROLE_CACHE", "InternalMessage::M2D_CLEAR_ROLE_CACHE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2d_clear_role_cache_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2D_CLEAR_ROLE_CACHE(); });
    internal_message_m2d_clear_role_cache_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2D_CLEAR_ROLE_CACHE>(new InternalMessage::M2D_CLEAR_ROLE_CACHE()); });
    internal_message_m2d_clear_role_cache_type["dwTLUserID"] = sol::property([](const InternalMessage::M2D_CLEAR_ROLE_CACHE& self) { return self.dwTLUserID; }, [](InternalMessage::M2D_CLEAR_ROLE_CACHE& self, decltype(InternalMessage::M2D_CLEAR_ROLE_CACHE::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2d_clear_role_cache_type["dwRoleID"] = sol::property([](const InternalMessage::M2D_CLEAR_ROLE_CACHE& self) { return self.dwRoleID; }, [](InternalMessage::M2D_CLEAR_ROLE_CACHE& self, decltype(InternalMessage::M2D_CLEAR_ROLE_CACHE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2d_clear_role_cache_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2D_CLEAR_ROLE_CACHE& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2D_CLEAR_ROLE_CACHE& self, decltype(InternalMessage::M2D_CLEAR_ROLE_CACHE::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    auto internal_message_m2d_gm_command_type = cqyh::lua::usertype<InternalMessage::M2D_GM_COMMAND>(L, internal_message_namespace, "M2D_GM_COMMAND", "InternalMessage::M2D_GM_COMMAND", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2d_gm_command_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2D_GM_COMMAND(); });
    internal_message_m2d_gm_command_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2D_GM_COMMAND>(new InternalMessage::M2D_GM_COMMAND()); });
    internal_message_m2d_gm_command_type["szGMCommand"] = cqyh::lua::string_property(&InternalMessage::M2D_GM_COMMAND::szGMCommand);
}

}
