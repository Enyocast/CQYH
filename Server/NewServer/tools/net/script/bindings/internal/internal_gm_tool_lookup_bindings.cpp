#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_lookup_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_pre_query_type = cqyh::lua::usertype<InternalMessage::TL2GM_PRE_QUERY>(L, internal_message_namespace, "TL2GM_PRE_QUERY", "InternalMessage::TL2GM_PRE_QUERY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_pre_query_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_PRE_QUERY(); });
    internal_message_tl2_gm_pre_query_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_PRE_QUERY>(new InternalMessage::TL2GM_PRE_QUERY()); });
    internal_message_tl2_gm_pre_query_type["szRoleName"] = cqyh::lua::string_property(&InternalMessage::TL2GM_PRE_QUERY::szRoleName);
    auto internal_message_tl2_gm_query_name_to_id_type = cqyh::lua::usertype<InternalMessage::TL2GM_QUERY_NAME_TO_ID>(L, internal_message_namespace, "TL2GM_QUERY_NAME_TO_ID", "InternalMessage::TL2GM_QUERY_NAME_TO_ID", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_query_name_to_id_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_QUERY_NAME_TO_ID(); });
    internal_message_tl2_gm_query_name_to_id_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_QUERY_NAME_TO_ID>(new InternalMessage::TL2GM_QUERY_NAME_TO_ID()); });
    internal_message_tl2_gm_query_name_to_id_type["nIndex"] = sol::property([](const InternalMessage::TL2GM_QUERY_NAME_TO_ID& self) { return self.nIndex; }, [](InternalMessage::TL2GM_QUERY_NAME_TO_ID& self, decltype(InternalMessage::TL2GM_QUERY_NAME_TO_ID::nIndex) value) { self.nIndex = value; });
    internal_message_tl2_gm_query_name_to_id_type["szRoleName"] = cqyh::lua::string_property(&InternalMessage::TL2GM_QUERY_NAME_TO_ID::szRoleName);
    auto internal_message_gm2_tl_pre_query_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_PRE_QUERY_ACK>(L, internal_message_namespace, "GM2TL_PRE_QUERY_ACK", "InternalMessage::GM2TL_PRE_QUERY_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_pre_query_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_PRE_QUERY_ACK(); });
    internal_message_gm2_tl_pre_query_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_PRE_QUERY_ACK>(new InternalMessage::GM2TL_PRE_QUERY_ACK()); });
    internal_message_gm2_tl_pre_query_ack_type["dwRoleID"] = sol::property([](const InternalMessage::GM2TL_PRE_QUERY_ACK& self) { return self.dwRoleID; }, [](InternalMessage::GM2TL_PRE_QUERY_ACK& self, decltype(InternalMessage::GM2TL_PRE_QUERY_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_gm2_tl_pre_query_ack_type["szRoleName"] = cqyh::lua::string_property(&InternalMessage::GM2TL_PRE_QUERY_ACK::szRoleName);
    auto internal_message_gm2_tl_query_name_to_id_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK>(L, internal_message_namespace, "GM2TL_QUERY_NAME_TO_ID_ACK", "InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_query_name_to_id_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK(); });
    internal_message_gm2_tl_query_name_to_id_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK>(new InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK()); });
    internal_message_gm2_tl_query_name_to_id_ack_type["nIndex"] = sol::property([](const InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK& self) { return self.nIndex; }, [](InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK& self, decltype(InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK::nIndex) value) { self.nIndex = value; });
    internal_message_gm2_tl_query_name_to_id_ack_type["dwRoleID"] = sol::property([](const InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK& self) { return self.dwRoleID; }, [](InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK& self, decltype(InternalMessage::GM2TL_QUERY_NAME_TO_ID_ACK::dwRoleID) value) { self.dwRoleID = value; });
}

}
