#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmsvr_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_server_announcements_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2gm_announce_ack_type = cqyh::lua::usertype<InternalMessage::M2GM_ANNOUNCE_ACK>(L, internal_message_namespace, "M2GM_ANNOUNCE_ACK", "InternalMessage::M2GM_ANNOUNCE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_announce_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_ANNOUNCE_ACK(); });
    internal_message_m2gm_announce_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_ANNOUNCE_ACK>(new InternalMessage::M2GM_ANNOUNCE_ACK()); });
    internal_message_m2gm_announce_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::M2GM_ANNOUNCE_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::M2GM_ANNOUNCE_ACK& self, decltype(InternalMessage::M2GM_ANNOUNCE_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2gm_announce_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2GM_ANNOUNCE_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2GM_ANNOUNCE_ACK& self, decltype(InternalMessage::M2GM_ANNOUNCE_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_m2gm_announce_ack_type["nResult"] = sol::property([](const InternalMessage::M2GM_ANNOUNCE_ACK& self) { return self.nResult; }, [](InternalMessage::M2GM_ANNOUNCE_ACK& self, decltype(InternalMessage::M2GM_ANNOUNCE_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_announce_data_type = cqyh::lua::usertype<InternalMessage::ANNOUNCE_DATA>(L, internal_message_namespace, "ANNOUNCE_DATA", "InternalMessage::ANNOUNCE_DATA");
    internal_message_announce_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::ANNOUNCE_DATA(); });
    internal_message_announce_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::ANNOUNCE_DATA>(new InternalMessage::ANNOUNCE_DATA()); });
    internal_message_announce_data_type["nGroupID"] = sol::property([](const InternalMessage::ANNOUNCE_DATA& self) { return self.nGroupID; }, [](InternalMessage::ANNOUNCE_DATA& self, decltype(InternalMessage::ANNOUNCE_DATA::nGroupID) value) { self.nGroupID = value; });
    internal_message_announce_data_type["dwSerial"] = sol::property([](const InternalMessage::ANNOUNCE_DATA& self) { return self.dwSerial; }, [](InternalMessage::ANNOUNCE_DATA& self, decltype(InternalMessage::ANNOUNCE_DATA::dwSerial) value) { self.dwSerial = value; });
    internal_message_announce_data_type["dwIntervalTime"] = sol::property([](const InternalMessage::ANNOUNCE_DATA& self) { return self.dwIntervalTime; }, [](InternalMessage::ANNOUNCE_DATA& self, decltype(InternalMessage::ANNOUNCE_DATA::dwIntervalTime) value) { self.dwIntervalTime = value; });
    internal_message_announce_data_type["dwRepeatNum"] = sol::property([](const InternalMessage::ANNOUNCE_DATA& self) { return self.dwRepeatNum; }, [](InternalMessage::ANNOUNCE_DATA& self, decltype(InternalMessage::ANNOUNCE_DATA::dwRepeatNum) value) { self.dwRepeatNum = value; });
    internal_message_announce_data_type["szText"] = cqyh::lua::string_property(&InternalMessage::ANNOUNCE_DATA::szText);
    auto internal_message_m2gm_get_announce_list_ack_type = cqyh::lua::usertype<InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK>(L, internal_message_namespace, "M2GM_GET_ANNOUNCE_LIST_ACK", "InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_get_announce_list_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK(); });
    internal_message_m2gm_get_announce_list_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK>(new InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK()); });
    internal_message_m2gm_get_announce_list_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self, decltype(InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2gm_get_announce_list_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self, decltype(InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_m2gm_get_announce_list_ack_type["nResult"] = sol::property([](const InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self) { return self.nResult; }, [](InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self, decltype(InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK::nResult) value) { self.nResult = value; });
    internal_message_m2gm_get_announce_list_ack_type["nCount"] = sol::property([](const InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self) { return self.nCount; }, [](InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK& self, decltype(InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK::nCount) value) { self.nCount = value; });
    internal_message_m2gm_get_announce_list_ack_type["data"] = cqyh::lua::array_property(&InternalMessage::M2GM_GET_ANNOUNCE_LIST_ACK::data);
    auto internal_message_m2gm_del_announce_ack_type = cqyh::lua::usertype<InternalMessage::M2GM_DEL_ANNOUNCE_ACK>(L, internal_message_namespace, "M2GM_DEL_ANNOUNCE_ACK", "InternalMessage::M2GM_DEL_ANNOUNCE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_del_announce_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_DEL_ANNOUNCE_ACK(); });
    internal_message_m2gm_del_announce_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_DEL_ANNOUNCE_ACK>(new InternalMessage::M2GM_DEL_ANNOUNCE_ACK()); });
    internal_message_m2gm_del_announce_ack_type["dwTLUserID"] = sol::property([](const InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self) { return self.dwTLUserID; }, [](InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self, decltype(InternalMessage::M2GM_DEL_ANNOUNCE_ACK::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_m2gm_del_announce_ack_type["dwCmdSerialID"] = sol::property([](const InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self) { return self.dwCmdSerialID; }, [](InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self, decltype(InternalMessage::M2GM_DEL_ANNOUNCE_ACK::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_m2gm_del_announce_ack_type["nResult"] = sol::property([](const InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self) { return self.nResult; }, [](InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self, decltype(InternalMessage::M2GM_DEL_ANNOUNCE_ACK::nResult) value) { self.nResult = value; });
    internal_message_m2gm_del_announce_ack_type["dwAnnounceSerial"] = sol::property([](const InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self) { return self.dwAnnounceSerial; }, [](InternalMessage::M2GM_DEL_ANNOUNCE_ACK& self, decltype(InternalMessage::M2GM_DEL_ANNOUNCE_ACK::dwAnnounceSerial) value) { self.dwAnnounceSerial = value; });
    auto internal_message_gm2_m_announce_type = cqyh::lua::usertype<InternalMessage::GM2M_ANNOUNCE>(L, internal_message_namespace, "GM2M_ANNOUNCE", "InternalMessage::GM2M_ANNOUNCE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_announce_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_ANNOUNCE(); });
    internal_message_gm2_m_announce_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_ANNOUNCE>(new InternalMessage::GM2M_ANNOUNCE()); });
    internal_message_gm2_m_announce_type["dwTLUserID"] = sol::property([](const InternalMessage::GM2M_ANNOUNCE& self) { return self.dwTLUserID; }, [](InternalMessage::GM2M_ANNOUNCE& self, decltype(InternalMessage::GM2M_ANNOUNCE::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_gm2_m_announce_type["nGroupID"] = sol::property([](const InternalMessage::GM2M_ANNOUNCE& self) { return self.nGroupID; }, [](InternalMessage::GM2M_ANNOUNCE& self, decltype(InternalMessage::GM2M_ANNOUNCE::nGroupID) value) { self.nGroupID = value; });
    internal_message_gm2_m_announce_type["dwCmdSerialID"] = sol::property([](const InternalMessage::GM2M_ANNOUNCE& self) { return self.dwCmdSerialID; }, [](InternalMessage::GM2M_ANNOUNCE& self, decltype(InternalMessage::GM2M_ANNOUNCE::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_gm2_m_announce_type["dwBeginTime"] = sol::property([](const InternalMessage::GM2M_ANNOUNCE& self) { return self.dwBeginTime; }, [](InternalMessage::GM2M_ANNOUNCE& self, decltype(InternalMessage::GM2M_ANNOUNCE::dwBeginTime) value) { self.dwBeginTime = value; });
    internal_message_gm2_m_announce_type["nRepeatNum"] = sol::property([](const InternalMessage::GM2M_ANNOUNCE& self) { return self.nRepeatNum; }, [](InternalMessage::GM2M_ANNOUNCE& self, decltype(InternalMessage::GM2M_ANNOUNCE::nRepeatNum) value) { self.nRepeatNum = value; });
    internal_message_gm2_m_announce_type["dwIntervalTime"] = sol::property([](const InternalMessage::GM2M_ANNOUNCE& self) { return self.dwIntervalTime; }, [](InternalMessage::GM2M_ANNOUNCE& self, decltype(InternalMessage::GM2M_ANNOUNCE::dwIntervalTime) value) { self.dwIntervalTime = value; });
    internal_message_gm2_m_announce_type["szText"] = cqyh::lua::string_property(&InternalMessage::GM2M_ANNOUNCE::szText);
    auto internal_message_gm2_m_get_announce_list_type = cqyh::lua::usertype<InternalMessage::GM2M_GET_ANNOUNCE_LIST>(L, internal_message_namespace, "GM2M_GET_ANNOUNCE_LIST", "InternalMessage::GM2M_GET_ANNOUNCE_LIST", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_get_announce_list_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_GET_ANNOUNCE_LIST(); });
    internal_message_gm2_m_get_announce_list_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_GET_ANNOUNCE_LIST>(new InternalMessage::GM2M_GET_ANNOUNCE_LIST()); });
    internal_message_gm2_m_get_announce_list_type["nGroupID"] = sol::property([](const InternalMessage::GM2M_GET_ANNOUNCE_LIST& self) { return self.nGroupID; }, [](InternalMessage::GM2M_GET_ANNOUNCE_LIST& self, decltype(InternalMessage::GM2M_GET_ANNOUNCE_LIST::nGroupID) value) { self.nGroupID = value; });
    internal_message_gm2_m_get_announce_list_type["dwTLUserID"] = sol::property([](const InternalMessage::GM2M_GET_ANNOUNCE_LIST& self) { return self.dwTLUserID; }, [](InternalMessage::GM2M_GET_ANNOUNCE_LIST& self, decltype(InternalMessage::GM2M_GET_ANNOUNCE_LIST::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_gm2_m_get_announce_list_type["dwCmdSerialID"] = sol::property([](const InternalMessage::GM2M_GET_ANNOUNCE_LIST& self) { return self.dwCmdSerialID; }, [](InternalMessage::GM2M_GET_ANNOUNCE_LIST& self, decltype(InternalMessage::GM2M_GET_ANNOUNCE_LIST::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    auto internal_message_gm2_m_del_announce_type = cqyh::lua::usertype<InternalMessage::GM2M_DEL_ANNOUNCE>(L, internal_message_namespace, "GM2M_DEL_ANNOUNCE", "InternalMessage::GM2M_DEL_ANNOUNCE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_m_del_announce_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2M_DEL_ANNOUNCE(); });
    internal_message_gm2_m_del_announce_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2M_DEL_ANNOUNCE>(new InternalMessage::GM2M_DEL_ANNOUNCE()); });
    internal_message_gm2_m_del_announce_type["nGroupID"] = sol::property([](const InternalMessage::GM2M_DEL_ANNOUNCE& self) { return self.nGroupID; }, [](InternalMessage::GM2M_DEL_ANNOUNCE& self, decltype(InternalMessage::GM2M_DEL_ANNOUNCE::nGroupID) value) { self.nGroupID = value; });
    internal_message_gm2_m_del_announce_type["dwTLUserID"] = sol::property([](const InternalMessage::GM2M_DEL_ANNOUNCE& self) { return self.dwTLUserID; }, [](InternalMessage::GM2M_DEL_ANNOUNCE& self, decltype(InternalMessage::GM2M_DEL_ANNOUNCE::dwTLUserID) value) { self.dwTLUserID = value; });
    internal_message_gm2_m_del_announce_type["dwCmdSerialID"] = sol::property([](const InternalMessage::GM2M_DEL_ANNOUNCE& self) { return self.dwCmdSerialID; }, [](InternalMessage::GM2M_DEL_ANNOUNCE& self, decltype(InternalMessage::GM2M_DEL_ANNOUNCE::dwCmdSerialID) value) { self.dwCmdSerialID = value; });
    internal_message_gm2_m_del_announce_type["dwAnnounceSerial"] = sol::property([](const InternalMessage::GM2M_DEL_ANNOUNCE& self) { return self.dwAnnounceSerial; }, [](InternalMessage::GM2M_DEL_ANNOUNCE& self, decltype(InternalMessage::GM2M_DEL_ANNOUNCE::dwAnnounceSerial) value) { self.dwAnnounceSerial = value; });
}

}
