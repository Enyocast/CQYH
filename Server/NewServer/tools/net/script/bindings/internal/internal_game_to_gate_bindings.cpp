#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2t_message.h"

namespace cqyh::net_tools::bindings {

void register_internal_game_to_gate_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["g2t_begin"] = static_cast<lua_Number>(InternalMessage::g2t_begin);
    internal_message_namespace["g2t_register"] = static_cast<lua_Number>(InternalMessage::g2t_register);
    internal_message_namespace["g2t_client_msg"] = static_cast<lua_Number>(InternalMessage::g2t_client_msg);
    internal_message_namespace["g2t_broadcast_client_msg"] = static_cast<lua_Number>(InternalMessage::g2t_broadcast_client_msg);
    internal_message_namespace["g2t_close_client_session"] = static_cast<lua_Number>(InternalMessage::g2t_close_client_session);
    internal_message_namespace["g2t_return_role_select"] = static_cast<lua_Number>(InternalMessage::g2t_return_role_select);
    internal_message_namespace["g2t_end"] = static_cast<lua_Number>(InternalMessage::g2t_end);
    auto internal_message_g2t_register_type = cqyh::lua::usertype<InternalMessage::G2T_REGISTER>(L, internal_message_namespace, "G2T_REGISTER", "InternalMessage::G2T_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2t_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2T_REGISTER(); });
    internal_message_g2t_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2T_REGISTER>(new InternalMessage::G2T_REGISTER()); });
    internal_message_g2t_register_type["dwGSSessionID"] = sol::property([](const InternalMessage::G2T_REGISTER& self) { return self.dwGSSessionID; }, [](InternalMessage::G2T_REGISTER& self, decltype(InternalMessage::G2T_REGISTER::dwGSSessionID) value) { self.dwGSSessionID = value; });
    auto internal_message_g2t_client_msg_type = cqyh::lua::usertype<InternalMessage::G2T_CLIENT_MSG>(L, internal_message_namespace, "G2T_CLIENT_MSG", "InternalMessage::G2T_CLIENT_MSG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2t_client_msg_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2T_CLIENT_MSG(); });
    internal_message_g2t_client_msg_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2T_CLIENT_MSG>(new InternalMessage::G2T_CLIENT_MSG()); });
    internal_message_g2t_client_msg_type["dwSessionID"] = sol::property([](const InternalMessage::G2T_CLIENT_MSG& self) { return self.dwSessionID; }, [](InternalMessage::G2T_CLIENT_MSG& self, decltype(InternalMessage::G2T_CLIENT_MSG::dwSessionID) value) { self.dwSessionID = value; });
    internal_message_g2t_client_msg_type["szData"] = cqyh::lua::string_property(&InternalMessage::G2T_CLIENT_MSG::szData);
    auto internal_message_g2t_broadcast_client_msg_type = cqyh::lua::usertype<InternalMessage::G2T_BROADCAST_CLIENT_MSG>(L, internal_message_namespace, "G2T_BROADCAST_CLIENT_MSG", "InternalMessage::G2T_BROADCAST_CLIENT_MSG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2t_broadcast_client_msg_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2T_BROADCAST_CLIENT_MSG(); });
    internal_message_g2t_broadcast_client_msg_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2T_BROADCAST_CLIENT_MSG>(new InternalMessage::G2T_BROADCAST_CLIENT_MSG()); });
    internal_message_g2t_broadcast_client_msg_type["wSessionCount"] = sol::property([](const InternalMessage::G2T_BROADCAST_CLIENT_MSG& self) { return self.wSessionCount; }, [](InternalMessage::G2T_BROADCAST_CLIENT_MSG& self, decltype(InternalMessage::G2T_BROADCAST_CLIENT_MSG::wSessionCount) value) { self.wSessionCount = value; });
    internal_message_g2t_broadcast_client_msg_type["dwSessionIDList"] = cqyh::lua::array_property(&InternalMessage::G2T_BROADCAST_CLIENT_MSG::dwSessionIDList);
    auto internal_message_g2t_return_role_select_type = cqyh::lua::usertype<InternalMessage::G2T_RETURN_ROLE_SELECT>(L, internal_message_namespace, "G2T_RETURN_ROLE_SELECT", "InternalMessage::G2T_RETURN_ROLE_SELECT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2t_return_role_select_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2T_RETURN_ROLE_SELECT(); });
    internal_message_g2t_return_role_select_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2T_RETURN_ROLE_SELECT>(new InternalMessage::G2T_RETURN_ROLE_SELECT()); });
    internal_message_g2t_return_role_select_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2T_RETURN_ROLE_SELECT& self) { return self.dwClientSessionID; }, [](InternalMessage::G2T_RETURN_ROLE_SELECT& self, decltype(InternalMessage::G2T_RETURN_ROLE_SELECT::dwClientSessionID) value) { self.dwClientSessionID = value; });
    auto internal_message_g2t_close_client_session_type = cqyh::lua::usertype<InternalMessage::G2T_CLOSE_CLIENT_SESSION>(L, internal_message_namespace, "G2T_CLOSE_CLIENT_SESSION", "InternalMessage::G2T_CLOSE_CLIENT_SESSION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2t_close_client_session_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2T_CLOSE_CLIENT_SESSION(); });
    internal_message_g2t_close_client_session_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2T_CLOSE_CLIENT_SESSION>(new InternalMessage::G2T_CLOSE_CLIENT_SESSION()); });
    internal_message_g2t_close_client_session_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2T_CLOSE_CLIENT_SESSION& self) { return self.dwClientSessionID; }, [](InternalMessage::G2T_CLOSE_CLIENT_SESSION& self, decltype(InternalMessage::G2T_CLOSE_CLIENT_SESSION::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2t_close_client_session_type["byLogout"] = sol::property([](const InternalMessage::G2T_CLOSE_CLIENT_SESSION& self) { return self.byLogout; }, [](InternalMessage::G2T_CLOSE_CLIENT_SESSION& self, decltype(InternalMessage::G2T_CLOSE_CLIENT_SESSION::byLogout) value) { self.byLogout = value; });
}

}
