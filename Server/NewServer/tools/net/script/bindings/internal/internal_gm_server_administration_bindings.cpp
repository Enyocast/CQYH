#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmsvr_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_server_administration_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2gm_exe_gm_str_ack_type = cqyh::lua::usertype<InternalMessage::M2GM_EXE_GM_STR_ACK>(L, internal_message_namespace, "M2GM_EXE_GM_STR_ACK", "InternalMessage::M2GM_EXE_GM_STR_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_exe_gm_str_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_EXE_GM_STR_ACK(); });
    internal_message_m2gm_exe_gm_str_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_EXE_GM_STR_ACK>(new InternalMessage::M2GM_EXE_GM_STR_ACK()); });
    internal_message_m2gm_exe_gm_str_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::M2GM_EXE_GM_STR_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::M2GM_EXE_GM_STR_ACK& self, decltype(InternalMessage::M2GM_EXE_GM_STR_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2gm_exe_gm_str_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2GM_EXE_GM_STR_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2GM_EXE_GM_STR_ACK& self, decltype(InternalMessage::M2GM_EXE_GM_STR_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_m2gm_exe_gm_str_ack_type["nResult"] = sol::property([](const InternalMessage::M2GM_EXE_GM_STR_ACK& self) { return self.nResult; }, [](InternalMessage::M2GM_EXE_GM_STR_ACK& self, decltype(InternalMessage::M2GM_EXE_GM_STR_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_gm2_m_exe_gm_str_type = cqyh::lua::usertype<InternalMessage::GM2M_EXE_GM_STR>(L, internal_message_namespace, "GM2M_EXE_GM_STR", "InternalMessage::GM2M_EXE_GM_STR", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_exe_gm_str_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_EXE_GM_STR(); });
    internal_message_gm2_m_exe_gm_str_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_EXE_GM_STR>(new InternalMessage::GM2M_EXE_GM_STR()); });
    internal_message_gm2_m_exe_gm_str_type["dwTLUserID"] = sol::property([](const InternalMessage::GM2M_EXE_GM_STR& self) { return self.dwTLUserID; }, [](InternalMessage::GM2M_EXE_GM_STR& self, decltype(InternalMessage::GM2M_EXE_GM_STR::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_gm2_m_exe_gm_str_type["dwCmdSerialID"] = sol::property([](const InternalMessage::GM2M_EXE_GM_STR& self) { return self.dwCmdSerialID; }, [](InternalMessage::GM2M_EXE_GM_STR& self, decltype(InternalMessage::GM2M_EXE_GM_STR::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_gm2_m_exe_gm_str_type["szGMStr"] = cqyh::lua::string_property(&InternalMessage::GM2M_EXE_GM_STR::szGMStr);
}

}
