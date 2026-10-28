#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/l2t_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_login_to_gate_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["l2t_begin"] = static_cast<lua_Number>(InternalMessage::l2t_begin);
    internal_message_namespace["l2t_register_ack"] = static_cast<lua_Number>(InternalMessage::l2t_register_ack);
    internal_message_namespace["l2t_login_ack"] = static_cast<lua_Number>(InternalMessage::l2t_login_ack);
    internal_message_namespace["l2t_end"] = static_cast<lua_Number>(InternalMessage::l2t_end);
    auto internal_message_l2t_register_ack_type = cqyh::lua::usertype<InternalMessage::L2T_REGISTER_ACK>(L, internal_message_namespace, "L2T_REGISTER_ACK", "InternalMessage::L2T_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_l2t_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::L2T_REGISTER_ACK(); });
    internal_message_l2t_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::L2T_REGISTER_ACK>(new InternalMessage::L2T_REGISTER_ACK()); });
    auto internal_message_l2t_login_ack_type = cqyh::lua::usertype<InternalMessage::L2T_LOGIN_ACK>(L, internal_message_namespace, "L2T_LOGIN_ACK", "InternalMessage::L2T_LOGIN_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_l2t_login_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::L2T_LOGIN_ACK(); });
    internal_message_l2t_login_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::L2T_LOGIN_ACK>(new InternalMessage::L2T_LOGIN_ACK()); });
    internal_message_l2t_login_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::L2T_LOGIN_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::L2T_LOGIN_ACK& self, decltype(InternalMessage::L2T_LOGIN_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_l2t_login_ack_type["nErrorCode"] = sol::property([](const InternalMessage::L2T_LOGIN_ACK& self) { return self.nErrorCode; }, [](InternalMessage::L2T_LOGIN_ACK& self, decltype(InternalMessage::L2T_LOGIN_ACK::nErrorCode) value) { self.nErrorCode = value; });
    internal_message_l2t_login_ack_type["szOASessionID"] = cqyh::lua::string_property(&InternalMessage::L2T_LOGIN_ACK::szOASessionID);
    internal_message_l2t_login_ack_type["szUserName"] = cqyh::lua::string_property(&InternalMessage::L2T_LOGIN_ACK::szUserName);
    internal_message_l2t_login_ack_type["szPGT"] = cqyh::lua::string_property(&InternalMessage::L2T_LOGIN_ACK::szPGT);
    internal_message_l2t_login_ack_type["bAdult"] = sol::property([](const InternalMessage::L2T_LOGIN_ACK& self) { return self.bAdult; }, [](InternalMessage::L2T_LOGIN_ACK& self, decltype(InternalMessage::L2T_LOGIN_ACK::bAdult) value) { self.bAdult = value; });
    internal_message_l2t_login_ack_type["wInfoLen"] = sol::property([](const InternalMessage::L2T_LOGIN_ACK& self) { return self.wInfoLen; }, [](InternalMessage::L2T_LOGIN_ACK& self, decltype(InternalMessage::L2T_LOGIN_ACK::wInfoLen) value) { self.wInfoLen = value; });
    internal_message_l2t_login_ack_type["abyInfo"] = cqyh::lua::array_property(&InternalMessage::L2T_LOGIN_ACK::abyInfo);
}

}
