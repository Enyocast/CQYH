#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/t2g_message.h"

namespace cqyh::net::bindings {

void register_internal_gate_to_game_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["t2g_begin"] = static_cast<lua_Number>(InternalMessage::t2g_begin);
    internal_message_namespace["t2g_register_ack"] = static_cast<lua_Number>(InternalMessage::t2g_register_ack);
    internal_message_namespace["t2g_role_enter"] = static_cast<lua_Number>(InternalMessage::t2g_role_enter);
    internal_message_namespace["t2g_client_msg"] = static_cast<lua_Number>(InternalMessage::t2g_client_msg);
    internal_message_namespace["t2g_end"] = static_cast<lua_Number>(InternalMessage::t2g_end);
    auto internal_message_t2g_register_ack_type = cqyh::lua::usertype<InternalMessage::T2G_REGISTER_ACK>(L, internal_message_namespace, "T2G_REGISTER_ACK", "InternalMessage::T2G_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2g_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2G_REGISTER_ACK(); });
    internal_message_t2g_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2G_REGISTER_ACK>(new InternalMessage::T2G_REGISTER_ACK()); });
    internal_message_t2g_register_ack_type["dwGTSessionID"] = sol::property([](const InternalMessage::T2G_REGISTER_ACK& self) { return self.dwGTSessionID; }, [](InternalMessage::T2G_REGISTER_ACK& self, decltype(InternalMessage::T2G_REGISTER_ACK::dwGTSessionID) value) { self.dwGTSessionID = value; });
    auto internal_message_t2g_role_enter_type = cqyh::lua::usertype<InternalMessage::T2G_ROLE_ENTER>(L, internal_message_namespace, "T2G_ROLE_ENTER", "InternalMessage::T2G_ROLE_ENTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2g_role_enter_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2G_ROLE_ENTER(); });
    internal_message_t2g_role_enter_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2G_ROLE_ENTER>(new InternalMessage::T2G_ROLE_ENTER()); });
    internal_message_t2g_role_enter_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2G_ROLE_ENTER& self) { return self.dwClientSessionID; }, [](InternalMessage::T2G_ROLE_ENTER& self, decltype(InternalMessage::T2G_ROLE_ENTER::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2g_role_enter_type["dwRoleID"] = sol::property([](const InternalMessage::T2G_ROLE_ENTER& self) { return self.dwRoleID; }, [](InternalMessage::T2G_ROLE_ENTER& self, decltype(InternalMessage::T2G_ROLE_ENTER::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_t2g_client_msg_type = cqyh::lua::usertype<InternalMessage::T2G_CLIENT_MSG>(L, internal_message_namespace, "T2G_CLIENT_MSG", "InternalMessage::T2G_CLIENT_MSG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2g_client_msg_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2G_CLIENT_MSG(); });
    internal_message_t2g_client_msg_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2G_CLIENT_MSG>(new InternalMessage::T2G_CLIENT_MSG()); });
    internal_message_t2g_client_msg_type["dwSessionID"] = sol::property([](const InternalMessage::T2G_CLIENT_MSG& self) { return self.dwSessionID; }, [](InternalMessage::T2G_CLIENT_MSG& self, decltype(InternalMessage::T2G_CLIENT_MSG::dwSessionID) value) { self.dwSessionID = value; });
    internal_message_t2g_client_msg_type["szData"] = cqyh::lua::string_property(&InternalMessage::T2G_CLIENT_MSG::szData);
}

}
