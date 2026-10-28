#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_connection_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_register_type = cqyh::lua::usertype<InternalMessage::TL2GM_REGISTER>(L, internal_message_namespace, "TL2GM_REGISTER", "InternalMessage::TL2GM_REGISTER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_register_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_REGISTER(); });
    internal_message_tl2_gm_register_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_REGISTER>(new InternalMessage::TL2GM_REGISTER()); });
    internal_message_tl2_gm_register_type["dwIP"] = sol::property([](const InternalMessage::TL2GM_REGISTER& self) { return self.dwIP; }, [](InternalMessage::TL2GM_REGISTER& self, decltype(InternalMessage::TL2GM_REGISTER::dwIP) value) { self.dwIP = value; });
    internal_message_tl2_gm_register_type["wPort"] = sol::property([](const InternalMessage::TL2GM_REGISTER& self) { return self.wPort; }, [](InternalMessage::TL2GM_REGISTER& self, decltype(InternalMessage::TL2GM_REGISTER::wPort) value) { self.wPort = value; });
    internal_message_tl2_gm_register_type["szComputerName"] = cqyh::lua::string_property(&InternalMessage::TL2GM_REGISTER::szComputerName);
    auto internal_message_tl2_gm_verify_type = cqyh::lua::usertype<InternalMessage::TL2GM_VERIFY>(L, internal_message_namespace, "TL2GM_VERIFY", "InternalMessage::TL2GM_VERIFY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_verify_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_VERIFY(); });
    internal_message_tl2_gm_verify_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_VERIFY>(new InternalMessage::TL2GM_VERIFY()); });
    internal_message_tl2_gm_verify_type["szName"] = cqyh::lua::string_property(&InternalMessage::TL2GM_VERIFY::szName);
    internal_message_tl2_gm_verify_type["szPwd"] = cqyh::lua::string_property(&InternalMessage::TL2GM_VERIFY::szPwd);
    auto internal_message_tl2_gm_select_group_type = cqyh::lua::usertype<InternalMessage::TL2GM_SELECT_GROUP>(L, internal_message_namespace, "TL2GM_SELECT_GROUP", "InternalMessage::TL2GM_SELECT_GROUP", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_select_group_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_SELECT_GROUP(); });
    internal_message_tl2_gm_select_group_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_SELECT_GROUP>(new InternalMessage::TL2GM_SELECT_GROUP()); });
    internal_message_tl2_gm_select_group_type["byGroupID"] = sol::property([](const InternalMessage::TL2GM_SELECT_GROUP& self) { return self.byGroupID; }, [](InternalMessage::TL2GM_SELECT_GROUP& self, decltype(InternalMessage::TL2GM_SELECT_GROUP::byGroupID) value) { self.byGroupID = value; });
    auto internal_message_gm2_tl_register_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_REGISTER_ACK>(L, internal_message_namespace, "GM2TL_REGISTER_ACK", "InternalMessage::GM2TL_REGISTER_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_register_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_REGISTER_ACK(); });
    internal_message_gm2_tl_register_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_REGISTER_ACK>(new InternalMessage::GM2TL_REGISTER_ACK()); });
    internal_message_gm2_tl_register_ack_type["nResult"] = sol::property([](const InternalMessage::GM2TL_REGISTER_ACK& self) { return self.nResult; }, [](InternalMessage::GM2TL_REGISTER_ACK& self, decltype(InternalMessage::GM2TL_REGISTER_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_gm2_tl_verify_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_VERIFY_ACK>(L, internal_message_namespace, "GM2TL_VERIFY_ACK", "InternalMessage::GM2TL_VERIFY_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_verify_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_VERIFY_ACK(); });
    internal_message_gm2_tl_verify_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_VERIFY_ACK>(new InternalMessage::GM2TL_VERIFY_ACK()); });
    internal_message_gm2_tl_verify_ack_type["bLD"] = sol::property([](const InternalMessage::GM2TL_VERIFY_ACK& self) { return static_cast<bool>(self.bLD); }, [](InternalMessage::GM2TL_VERIFY_ACK& self, bool value) { self.bLD = value; });
    internal_message_gm2_tl_verify_ack_type["nResult"] = sol::property([](const InternalMessage::GM2TL_VERIFY_ACK& self) { return self.nResult; }, [](InternalMessage::GM2TL_VERIFY_ACK& self, decltype(InternalMessage::GM2TL_VERIFY_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_gm2_tl_select_group_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_SELECT_GROUP_ACK>(L, internal_message_namespace, "GM2TL_SELECT_GROUP_ACK", "InternalMessage::GM2TL_SELECT_GROUP_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_select_group_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_SELECT_GROUP_ACK(); });
    internal_message_gm2_tl_select_group_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_SELECT_GROUP_ACK>(new InternalMessage::GM2TL_SELECT_GROUP_ACK()); });
    internal_message_gm2_tl_select_group_ack_type["byGroupID"] = sol::property([](const InternalMessage::GM2TL_SELECT_GROUP_ACK& self) { return self.byGroupID; }, [](InternalMessage::GM2TL_SELECT_GROUP_ACK& self, decltype(InternalMessage::GM2TL_SELECT_GROUP_ACK::byGroupID) value) { self.byGroupID = value; });
}

}
