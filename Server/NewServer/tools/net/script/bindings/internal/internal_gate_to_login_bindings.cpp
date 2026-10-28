#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/t2l_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gate_to_login_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["t2l_begin"] = static_cast<lua_Number>(InternalMessage::t2l_begin);
    internal_message_namespace["t2l_register"] = static_cast<lua_Number>(InternalMessage::t2l_register);
    internal_message_namespace["t2l_login_req"] = static_cast<lua_Number>(InternalMessage::t2l_login_req);
    internal_message_namespace["t2l_end"] = static_cast<lua_Number>(InternalMessage::t2l_end);
    auto internal_message_t2l_register_type = cqyh::lua::usertype<InternalMessage::T2L_REGISTER>(L, internal_message_namespace, "T2L_REGISTER", "InternalMessage::T2L_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2l_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2L_REGISTER(); });
    internal_message_t2l_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2L_REGISTER>(new InternalMessage::T2L_REGISTER()); });
    internal_message_t2l_register_type["dwGTSessionID"] = sol::property([](const InternalMessage::T2L_REGISTER& self) { return self.dwGTSessionID; }, [](InternalMessage::T2L_REGISTER& self, decltype(InternalMessage::T2L_REGISTER::dwGTSessionID) value) { self.dwGTSessionID = value; });
    auto internal_message_t2l_login_req_type = cqyh::lua::usertype<InternalMessage::T2L_LOGIN_REQ>(L, internal_message_namespace, "T2L_LOGIN_REQ", "InternalMessage::T2L_LOGIN_REQ", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_t2l_login_req_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::T2L_LOGIN_REQ(); });
    internal_message_t2l_login_req_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::T2L_LOGIN_REQ>(new InternalMessage::T2L_LOGIN_REQ()); });
    internal_message_t2l_login_req_type["dwClientSessionID"] = sol::property([](const InternalMessage::T2L_LOGIN_REQ& self) { return self.dwClientSessionID; }, [](InternalMessage::T2L_LOGIN_REQ& self, decltype(InternalMessage::T2L_LOGIN_REQ::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_t2l_login_req_type["szUserName"] = cqyh::lua::string_property(&InternalMessage::T2L_LOGIN_REQ::szUserName);
    internal_message_t2l_login_req_type["szOASessionID"] = cqyh::lua::string_property(&InternalMessage::T2L_LOGIN_REQ::szOASessionID);
}

}
