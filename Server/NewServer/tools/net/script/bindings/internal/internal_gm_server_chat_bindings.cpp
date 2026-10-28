#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmsvr_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_server_chat_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2gm_forbid_chat_ack_type = cqyh::lua::usertype<InternalMessage::M2GM_FORBID_CHAT_ACK>(L, internal_message_namespace, "M2GM_FORBID_CHAT_ACK", "InternalMessage::M2GM_FORBID_CHAT_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_forbid_chat_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_FORBID_CHAT_ACK(); });
    internal_message_m2gm_forbid_chat_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_FORBID_CHAT_ACK>(new InternalMessage::M2GM_FORBID_CHAT_ACK()); });
    internal_message_m2gm_forbid_chat_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::M2GM_FORBID_CHAT_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::M2GM_FORBID_CHAT_ACK& self, decltype(InternalMessage::M2GM_FORBID_CHAT_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2gm_forbid_chat_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2GM_FORBID_CHAT_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2GM_FORBID_CHAT_ACK& self, decltype(InternalMessage::M2GM_FORBID_CHAT_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_m2gm_forbid_chat_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2GM_FORBID_CHAT_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2GM_FORBID_CHAT_ACK& self, decltype(InternalMessage::M2GM_FORBID_CHAT_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2gm_forbid_chat_ack_type["nResult"] = sol::property([](const InternalMessage::M2GM_FORBID_CHAT_ACK& self) { return self.nResult; }, [](InternalMessage::M2GM_FORBID_CHAT_ACK& self, decltype(InternalMessage::M2GM_FORBID_CHAT_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_gm2_m_forbid_chat_type = cqyh::lua::usertype<InternalMessage::GM2M_FORBID_CHAT>(L, internal_message_namespace, "GM2M_FORBID_CHAT", "InternalMessage::GM2M_FORBID_CHAT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_forbid_chat_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_FORBID_CHAT(); });
    internal_message_gm2_m_forbid_chat_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_FORBID_CHAT>(new InternalMessage::GM2M_FORBID_CHAT()); });
    internal_message_gm2_m_forbid_chat_type["dwTLUser"] = sol::property([](const InternalMessage::GM2M_FORBID_CHAT& self) { return self.dwTLUser; }, [](InternalMessage::GM2M_FORBID_CHAT& self, decltype(InternalMessage::GM2M_FORBID_CHAT::dwTLUser) value) { self.dwTLUser = value; });
    internal_message_gm2_m_forbid_chat_type["dwCmdSerialID"] = sol::property([](const InternalMessage::GM2M_FORBID_CHAT& self) { return self.dwCmdSerialID; }, [](InternalMessage::GM2M_FORBID_CHAT& self, decltype(InternalMessage::GM2M_FORBID_CHAT::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_gm2_m_forbid_chat_type["dwTime"] = sol::property([](const InternalMessage::GM2M_FORBID_CHAT& self) { return self.dwTime; }, [](InternalMessage::GM2M_FORBID_CHAT& self, decltype(InternalMessage::GM2M_FORBID_CHAT::dwTime) value) { self.dwTime = value; });
    internal_message_gm2_m_forbid_chat_type["dwRoleID"] = sol::property([](const InternalMessage::GM2M_FORBID_CHAT& self) { return self.dwRoleID; }, [](InternalMessage::GM2M_FORBID_CHAT& self, decltype(InternalMessage::GM2M_FORBID_CHAT::dwRoleID) value) { self.dwRoleID = value; });
}

}
