#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_mail_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_send_mail_type = cqyh::lua::usertype<InternalMessage::TL2GM_SEND_MAIL>(L, internal_message_namespace, "TL2GM_SEND_MAIL", "InternalMessage::TL2GM_SEND_MAIL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_send_mail_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_SEND_MAIL(); });
    internal_message_tl2_gm_send_mail_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_SEND_MAIL>(new InternalMessage::TL2GM_SEND_MAIL()); });
    internal_message_tl2_gm_send_mail_type["dwRoleID"] = sol::property([](const InternalMessage::TL2GM_SEND_MAIL& self) { return self.dwRoleID; }, [](InternalMessage::TL2GM_SEND_MAIL& self, decltype(InternalMessage::TL2GM_SEND_MAIL::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_tl2_gm_send_mail_type["szSubject"] = cqyh::lua::string_property(&InternalMessage::TL2GM_SEND_MAIL::szSubject);
    internal_message_tl2_gm_send_mail_type["szContent"] = cqyh::lua::string_property(&InternalMessage::TL2GM_SEND_MAIL::szContent);
    internal_message_tl2_gm_send_mail_type["szReason"] = cqyh::lua::string_property(&InternalMessage::TL2GM_SEND_MAIL::szReason);
    internal_message_tl2_gm_send_mail_type["dwItemID"] = sol::property([](const InternalMessage::TL2GM_SEND_MAIL& self) { return self.dwItemID; }, [](InternalMessage::TL2GM_SEND_MAIL& self, decltype(InternalMessage::TL2GM_SEND_MAIL::dwItemID) value) { self.dwItemID = value; });
    internal_message_tl2_gm_send_mail_type["nItemNum"] = sol::property([](const InternalMessage::TL2GM_SEND_MAIL& self) { return self.nItemNum; }, [](InternalMessage::TL2GM_SEND_MAIL& self, decltype(InternalMessage::TL2GM_SEND_MAIL::nItemNum) value) { self.nItemNum = value; });
    auto internal_message_gm2_tl_send_mail_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_SEND_MAIL_ACK>(L, internal_message_namespace, "GM2TL_SEND_MAIL_ACK", "InternalMessage::GM2TL_SEND_MAIL_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_send_mail_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_SEND_MAIL_ACK(); });
    internal_message_gm2_tl_send_mail_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_SEND_MAIL_ACK>(new InternalMessage::GM2TL_SEND_MAIL_ACK()); });
    internal_message_gm2_tl_send_mail_ack_type["dwRoleID"] = sol::property([](const InternalMessage::GM2TL_SEND_MAIL_ACK& self) { return self.dwRoleID; }, [](InternalMessage::GM2TL_SEND_MAIL_ACK& self, decltype(InternalMessage::GM2TL_SEND_MAIL_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_gm2_tl_send_mail_ack_type["nResult"] = sol::property([](const InternalMessage::GM2TL_SEND_MAIL_ACK& self) { return self.nResult; }, [](InternalMessage::GM2TL_SEND_MAIL_ACK& self, decltype(InternalMessage::GM2TL_SEND_MAIL_ACK::nResult) value) { self.nResult = value; });
}

}
