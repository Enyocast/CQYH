#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_gm_tool_chat_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_forbid_chat_type = cqyh::lua::usertype<InternalMessage::TL2GM_FORBID_CHAT>(L, internal_message_namespace, "TL2GM_FORBID_CHAT", "InternalMessage::TL2GM_FORBID_CHAT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_forbid_chat_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_FORBID_CHAT(); });
    internal_message_tl2_gm_forbid_chat_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_FORBID_CHAT>(new InternalMessage::TL2GM_FORBID_CHAT()); });
    internal_message_tl2_gm_forbid_chat_type["dwTime"] = sol::property([](const InternalMessage::TL2GM_FORBID_CHAT& self) { return self.dwTime; }, [](InternalMessage::TL2GM_FORBID_CHAT& self, decltype(InternalMessage::TL2GM_FORBID_CHAT::dwTime) value) { self.dwTime = value; });
    internal_message_tl2_gm_forbid_chat_type["dwRoleID"] = sol::property([](const InternalMessage::TL2GM_FORBID_CHAT& self) { return self.dwRoleID; }, [](InternalMessage::TL2GM_FORBID_CHAT& self, decltype(InternalMessage::TL2GM_FORBID_CHAT::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_gm2_tl_forbid_chat_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_FORBID_CHAT_ACK>(L, internal_message_namespace, "GM2TL_FORBID_CHAT_ACK", "InternalMessage::GM2TL_FORBID_CHAT_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_forbid_chat_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_FORBID_CHAT_ACK(); });
    internal_message_gm2_tl_forbid_chat_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_FORBID_CHAT_ACK>(new InternalMessage::GM2TL_FORBID_CHAT_ACK()); });
    internal_message_gm2_tl_forbid_chat_ack_type["dwRoleID"] = sol::property([](const InternalMessage::GM2TL_FORBID_CHAT_ACK& self) { return self.dwRoleID; }, [](InternalMessage::GM2TL_FORBID_CHAT_ACK& self, decltype(InternalMessage::GM2TL_FORBID_CHAT_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_gm2_tl_forbid_chat_ack_type["nResult"] = sol::property([](const InternalMessage::GM2TL_FORBID_CHAT_ACK& self) { return self.nResult; }, [](InternalMessage::GM2TL_FORBID_CHAT_ACK& self, decltype(InternalMessage::GM2TL_FORBID_CHAT_ACK::nResult) value) { self.nResult = value; });
}

}
