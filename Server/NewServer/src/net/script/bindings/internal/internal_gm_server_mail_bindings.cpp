#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmsvr_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_gm_server_mail_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2gm_send_mail_ack_type = cqyh::lua::usertype<InternalMessage::M2GM_SEND_MAIL_ACK>(L, internal_message_namespace, "M2GM_SEND_MAIL_ACK", "InternalMessage::M2GM_SEND_MAIL_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_send_mail_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_SEND_MAIL_ACK(); });
    internal_message_m2gm_send_mail_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_SEND_MAIL_ACK>(new InternalMessage::M2GM_SEND_MAIL_ACK()); });
    internal_message_m2gm_send_mail_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::M2GM_SEND_MAIL_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::M2GM_SEND_MAIL_ACK& self, decltype(InternalMessage::M2GM_SEND_MAIL_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2gm_send_mail_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2GM_SEND_MAIL_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2GM_SEND_MAIL_ACK& self, decltype(InternalMessage::M2GM_SEND_MAIL_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_m2gm_send_mail_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2GM_SEND_MAIL_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2GM_SEND_MAIL_ACK& self, decltype(InternalMessage::M2GM_SEND_MAIL_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2gm_send_mail_ack_type["nResult"] = sol::property([](const InternalMessage::M2GM_SEND_MAIL_ACK& self) { return self.nResult; }, [](InternalMessage::M2GM_SEND_MAIL_ACK& self, decltype(InternalMessage::M2GM_SEND_MAIL_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_m2gm_del_mail_ack_type = cqyh::lua::usertype<InternalMessage::M2GM_DEL_MAIL_ACK>(L, internal_message_namespace, "M2GM_DEL_MAIL_ACK", "InternalMessage::M2GM_DEL_MAIL_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_del_mail_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_DEL_MAIL_ACK(); });
    internal_message_m2gm_del_mail_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_DEL_MAIL_ACK>(new InternalMessage::M2GM_DEL_MAIL_ACK()); });
    internal_message_m2gm_del_mail_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::M2GM_DEL_MAIL_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::M2GM_DEL_MAIL_ACK& self, decltype(InternalMessage::M2GM_DEL_MAIL_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2gm_del_mail_ack_type["dwMailID"] = sol::property([](const InternalMessage::M2GM_DEL_MAIL_ACK& self) { return self.dwMailID; }, [](InternalMessage::M2GM_DEL_MAIL_ACK& self, decltype(InternalMessage::M2GM_DEL_MAIL_ACK::dwMailID) value) { self.dwMailID = value; });
    internal_message_m2gm_del_mail_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2GM_DEL_MAIL_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2GM_DEL_MAIL_ACK& self, decltype(InternalMessage::M2GM_DEL_MAIL_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_m2gm_del_mail_ack_type["nResult"] = sol::property([](const InternalMessage::M2GM_DEL_MAIL_ACK& self) { return self.nResult; }, [](InternalMessage::M2GM_DEL_MAIL_ACK& self, decltype(InternalMessage::M2GM_DEL_MAIL_ACK::nResult) value) { self.nResult = value; });
    internal_message_m2gm_del_mail_ack_type["szBuffer"] = cqyh::lua::string_property(&InternalMessage::M2GM_DEL_MAIL_ACK::szBuffer);
    auto internal_message_gm2_m_send_mail_type = cqyh::lua::usertype<InternalMessage::GM2M_SEND_MAIL>(L, internal_message_namespace, "GM2M_SEND_MAIL", "InternalMessage::GM2M_SEND_MAIL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_send_mail_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_SEND_MAIL(); });
    internal_message_gm2_m_send_mail_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_SEND_MAIL>(new InternalMessage::GM2M_SEND_MAIL()); });
    internal_message_gm2_m_send_mail_type["dwTLUserID"] = sol::property([](const InternalMessage::GM2M_SEND_MAIL& self) { return self.dwTLUserID; }, [](InternalMessage::GM2M_SEND_MAIL& self, decltype(InternalMessage::GM2M_SEND_MAIL::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_gm2_m_send_mail_type["dwCmdSerialID"] = sol::property([](const InternalMessage::GM2M_SEND_MAIL& self) { return self.dwCmdSerialID; }, [](InternalMessage::GM2M_SEND_MAIL& self, decltype(InternalMessage::GM2M_SEND_MAIL::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_gm2_m_send_mail_type["dwRoleID"] = sol::property([](const InternalMessage::GM2M_SEND_MAIL& self) { return self.dwRoleID; }, [](InternalMessage::GM2M_SEND_MAIL& self, decltype(InternalMessage::GM2M_SEND_MAIL::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_gm2_m_send_mail_type["szSubject"] = cqyh::lua::string_property(&InternalMessage::GM2M_SEND_MAIL::szSubject);
    internal_message_gm2_m_send_mail_type["szContent"] = cqyh::lua::string_property(&InternalMessage::GM2M_SEND_MAIL::szContent);
    internal_message_gm2_m_send_mail_type["dwItemID"] = sol::property([](const InternalMessage::GM2M_SEND_MAIL& self) { return self.dwItemID; }, [](InternalMessage::GM2M_SEND_MAIL& self, decltype(InternalMessage::GM2M_SEND_MAIL::dwItemID) value) { self.dwItemID = value; });
    internal_message_gm2_m_send_mail_type["nItemNum"] = sol::property([](const InternalMessage::GM2M_SEND_MAIL& self) { return self.nItemNum; }, [](InternalMessage::GM2M_SEND_MAIL& self, decltype(InternalMessage::GM2M_SEND_MAIL::nItemNum) value) { self.nItemNum = value; });
    auto internal_message_gm2_m_del_mail_type = cqyh::lua::usertype<InternalMessage::GM2M_DEL_MAIL>(L, internal_message_namespace, "GM2M_DEL_MAIL", "InternalMessage::GM2M_DEL_MAIL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_del_mail_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_DEL_MAIL(); });
    internal_message_gm2_m_del_mail_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_DEL_MAIL>(new InternalMessage::GM2M_DEL_MAIL()); });
    internal_message_gm2_m_del_mail_type["dwTLUserID"] = sol::property([](const InternalMessage::GM2M_DEL_MAIL& self) { return self.dwTLUserID; }, [](InternalMessage::GM2M_DEL_MAIL& self, decltype(InternalMessage::GM2M_DEL_MAIL::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_gm2_m_del_mail_type["dwCmdSerialID"] = sol::property([](const InternalMessage::GM2M_DEL_MAIL& self) { return self.dwCmdSerialID; }, [](InternalMessage::GM2M_DEL_MAIL& self, decltype(InternalMessage::GM2M_DEL_MAIL::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_gm2_m_del_mail_type["dwRoleID"] = sol::property([](const InternalMessage::GM2M_DEL_MAIL& self) { return self.dwRoleID; }, [](InternalMessage::GM2M_DEL_MAIL& self, decltype(InternalMessage::GM2M_DEL_MAIL::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_gm2_m_del_mail_type["dwMailID"] = sol::property([](const InternalMessage::GM2M_DEL_MAIL& self) { return self.dwMailID; }, [](InternalMessage::GM2M_DEL_MAIL& self, decltype(InternalMessage::GM2M_DEL_MAIL::dwMailID) value) { self.dwMailID = value; });
}

}
