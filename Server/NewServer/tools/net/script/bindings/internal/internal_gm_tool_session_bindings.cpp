#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_session_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_login_type = cqyh::lua::usertype<InternalMessage::TL2GM_LOGIN>(L, internal_message_namespace, "TL2GM_LOGIN", "InternalMessage::TL2GM_LOGIN", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_login_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_LOGIN(); });
    internal_message_tl2_gm_login_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_LOGIN>(new InternalMessage::TL2GM_LOGIN()); });
    internal_message_tl2_gm_login_type["nVersion"] = sol::property([](const InternalMessage::TL2GM_LOGIN& self) { return self.nVersion; }, [](InternalMessage::TL2GM_LOGIN& self, decltype(InternalMessage::TL2GM_LOGIN::nVersion) value) { self.nVersion = value; });
    internal_message_tl2_gm_login_type["nDependVersion"] = sol::property([](const InternalMessage::TL2GM_LOGIN& self) { return self.nDependVersion; }, [](InternalMessage::TL2GM_LOGIN& self, decltype(InternalMessage::TL2GM_LOGIN::nDependVersion) value) { self.nDependVersion = value; });
    internal_message_tl2_gm_login_type["szName"] = cqyh::lua::string_property(&InternalMessage::TL2GM_LOGIN::szName);
    internal_message_tl2_gm_login_type["szPwd"] = cqyh::lua::string_property(&InternalMessage::TL2GM_LOGIN::szPwd);
    auto internal_message_tl2_gm_logout_type = cqyh::lua::usertype<InternalMessage::TL2GM_LOGOUT>(L, internal_message_namespace, "TL2GM_LOGOUT", "InternalMessage::TL2GM_LOGOUT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_logout_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_LOGOUT(); });
    internal_message_tl2_gm_logout_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_LOGOUT>(new InternalMessage::TL2GM_LOGOUT()); });
    auto internal_message_gm2_tl_login_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_LOGIN_ACK>(L, internal_message_namespace, "GM2TL_LOGIN_ACK", "InternalMessage::GM2TL_LOGIN_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_login_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_LOGIN_ACK(); });
    internal_message_gm2_tl_login_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_LOGIN_ACK>(new InternalMessage::GM2TL_LOGIN_ACK()); });
    internal_message_gm2_tl_login_ack_type["nResult"] = sol::property([](const InternalMessage::GM2TL_LOGIN_ACK& self) { return self.nResult; }, [](InternalMessage::GM2TL_LOGIN_ACK& self, decltype(InternalMessage::GM2TL_LOGIN_ACK::nResult) value) { self.nResult = value; });
    internal_message_gm2_tl_login_ack_type["nMSCount"] = sol::property([](const InternalMessage::GM2TL_LOGIN_ACK& self) { return self.nMSCount; }, [](InternalMessage::GM2TL_LOGIN_ACK& self, decltype(InternalMessage::GM2TL_LOGIN_ACK::nMSCount) value) { self.nMSCount = value; });
    internal_message_gm2_tl_login_ack_type["stMSInfo"] = cqyh::lua::array_property(&InternalMessage::GM2TL_LOGIN_ACK::stMSInfo);
    auto internal_message_gm2_tl_logout_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_LOGOUT_ACK>(L, internal_message_namespace, "GM2TL_LOGOUT_ACK", "InternalMessage::GM2TL_LOGOUT_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_logout_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_LOGOUT_ACK(); });
    internal_message_gm2_tl_logout_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_LOGOUT_ACK>(new InternalMessage::GM2TL_LOGOUT_ACK()); });
}

}
