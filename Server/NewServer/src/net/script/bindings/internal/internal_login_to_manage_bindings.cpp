#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/l2m_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_login_to_manage_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["l2m_begin"] = static_cast<lua_Number>(InternalMessage::l2m_begin);
    internal_message_namespace["l2m_register"] = static_cast<lua_Number>(InternalMessage::l2m_register);
    internal_message_namespace["l2m_ready"] = static_cast<lua_Number>(InternalMessage::l2m_ready);
    internal_message_namespace["l2m_close_ack"] = static_cast<lua_Number>(InternalMessage::l2m_close_ack);
    internal_message_namespace["l2m_login_query_req"] = static_cast<lua_Number>(InternalMessage::l2m_login_query_req);
    internal_message_namespace["l2m_end"] = static_cast<lua_Number>(InternalMessage::l2m_end);
    auto internal_message_l2m_register_type = cqyh::lua::usertype<InternalMessage::L2M_REGISTER>(L, internal_message_namespace, "L2M_REGISTER", "InternalMessage::L2M_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_l2m_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::L2M_REGISTER(); });
    internal_message_l2m_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::L2M_REGISTER>(new InternalMessage::L2M_REGISTER()); });
    internal_message_l2m_register_type["dwAddr"] = sol::property([](const InternalMessage::L2M_REGISTER& self) { return self.dwAddr; }, [](InternalMessage::L2M_REGISTER& self, decltype(InternalMessage::L2M_REGISTER::dwAddr) value) { self.dwAddr = value; });
    internal_message_l2m_register_type["wPort"] = sol::property([](const InternalMessage::L2M_REGISTER& self) { return self.wPort; }, [](InternalMessage::L2M_REGISTER& self, decltype(InternalMessage::L2M_REGISTER::wPort) value) { self.wPort = value; });
    auto internal_message_l2m_ready_type = cqyh::lua::usertype<InternalMessage::L2M_READY>(L, internal_message_namespace, "L2M_READY", "InternalMessage::L2M_READY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_l2m_ready_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::L2M_READY(); });
    internal_message_l2m_ready_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::L2M_READY>(new InternalMessage::L2M_READY()); });
    auto internal_message_l2m_close_ack_type = cqyh::lua::usertype<InternalMessage::L2M_CLOSE_ACK>(L, internal_message_namespace, "L2M_CLOSE_ACK", "InternalMessage::L2M_CLOSE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_l2m_close_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::L2M_CLOSE_ACK(); });
    internal_message_l2m_close_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::L2M_CLOSE_ACK>(new InternalMessage::L2M_CLOSE_ACK()); });
    auto internal_message_l2m_login_query_req_type = cqyh::lua::usertype<InternalMessage::L2M_LOGIN_QUERY_REQ>(L, internal_message_namespace, "L2M_LOGIN_QUERY_REQ", "InternalMessage::L2M_LOGIN_QUERY_REQ", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_l2m_login_query_req_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::L2M_LOGIN_QUERY_REQ(); });
    internal_message_l2m_login_query_req_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::L2M_LOGIN_QUERY_REQ>(new InternalMessage::L2M_LOGIN_QUERY_REQ()); });
    internal_message_l2m_login_query_req_type["dwClientSessionID"] = sol::property([](const InternalMessage::L2M_LOGIN_QUERY_REQ& self) { return self.dwClientSessionID; }, [](InternalMessage::L2M_LOGIN_QUERY_REQ& self, decltype(InternalMessage::L2M_LOGIN_QUERY_REQ::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_l2m_login_query_req_type["szUserName"] = cqyh::lua::string_property(&InternalMessage::L2M_LOGIN_QUERY_REQ::szUserName);
    internal_message_l2m_login_query_req_type["szPassword"] = cqyh::lua::string_property(&InternalMessage::L2M_LOGIN_QUERY_REQ::szPassword);
}

}
