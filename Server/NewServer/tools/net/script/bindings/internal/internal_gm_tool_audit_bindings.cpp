#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_audit_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_log_type = cqyh::lua::usertype<InternalMessage::TL2GM_LOG>(L, internal_message_namespace, "TL2GM_LOG", "InternalMessage::TL2GM_LOG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_log_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_LOG(); });
    internal_message_tl2_gm_log_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_LOG>(new InternalMessage::TL2GM_LOG()); });
    internal_message_tl2_gm_log_type["nLogType"] = sol::property([](const InternalMessage::TL2GM_LOG& self) { return self.nLogType; }, [](InternalMessage::TL2GM_LOG& self, decltype(InternalMessage::TL2GM_LOG::nLogType) value) { self.nLogType = value; });
    internal_message_tl2_gm_log_type["dwBeginTime"] = sol::property([](const InternalMessage::TL2GM_LOG& self) { return self.dwBeginTime; }, [](InternalMessage::TL2GM_LOG& self, decltype(InternalMessage::TL2GM_LOG::dwBeginTime) value) { self.dwBeginTime = value; });
    internal_message_tl2_gm_log_type["dwEndTime"] = sol::property([](const InternalMessage::TL2GM_LOG& self) { return self.dwEndTime; }, [](InternalMessage::TL2GM_LOG& self, decltype(InternalMessage::TL2GM_LOG::dwEndTime) value) { self.dwEndTime = value; });
    internal_message_tl2_gm_log_type["szQueryStr"] = cqyh::lua::string_property(&InternalMessage::TL2GM_LOG::szQueryStr);
    auto internal_message_gm2_tl_log_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_LOG_ACK>(L, internal_message_namespace, "GM2TL_LOG_ACK", "InternalMessage::GM2TL_LOG_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_log_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_LOG_ACK(); });
    internal_message_gm2_tl_log_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_LOG_ACK>(new InternalMessage::GM2TL_LOG_ACK()); });
    internal_message_gm2_tl_log_ack_type["nLogType"] = sol::property([](const InternalMessage::GM2TL_LOG_ACK& self) { return self.nLogType; }, [](InternalMessage::GM2TL_LOG_ACK& self, decltype(InternalMessage::GM2TL_LOG_ACK::nLogType) value) { self.nLogType = value; });
    internal_message_gm2_tl_log_ack_type["bTruncated"] = sol::property([](const InternalMessage::GM2TL_LOG_ACK& self) { return static_cast<bool>(self.bTruncated); }, [](InternalMessage::GM2TL_LOG_ACK& self, bool value) { self.bTruncated = value; });
    internal_message_gm2_tl_log_ack_type["nLength"] = sol::property([](const InternalMessage::GM2TL_LOG_ACK& self) { return self.nLength; }, [](InternalMessage::GM2TL_LOG_ACK& self, decltype(InternalMessage::GM2TL_LOG_ACK::nLength) value) { self.nLength = value; });
    internal_message_gm2_tl_log_ack_type["szBuffer"] = cqyh::lua::string_property(&InternalMessage::GM2TL_LOG_ACK::szBuffer);
}

}
