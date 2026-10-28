#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_announcements_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_announce_type = cqyh::lua::usertype<InternalMessage::TL2GM_ANNOUNCE>(L, internal_message_namespace, "TL2GM_ANNOUNCE", "InternalMessage::TL2GM_ANNOUNCE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_announce_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_ANNOUNCE(); });
    internal_message_tl2_gm_announce_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_ANNOUNCE>(new InternalMessage::TL2GM_ANNOUNCE()); });
    internal_message_tl2_gm_announce_type["nGroupID"] = sol::property([](const InternalMessage::TL2GM_ANNOUNCE& self) { return self.nGroupID; }, [](InternalMessage::TL2GM_ANNOUNCE& self, decltype(InternalMessage::TL2GM_ANNOUNCE::nGroupID) value) { self.nGroupID = value; });
    internal_message_tl2_gm_announce_type["dwBeginTime"] = sol::property([](const InternalMessage::TL2GM_ANNOUNCE& self) { return self.dwBeginTime; }, [](InternalMessage::TL2GM_ANNOUNCE& self, decltype(InternalMessage::TL2GM_ANNOUNCE::dwBeginTime) value) { self.dwBeginTime = value; });
    internal_message_tl2_gm_announce_type["nRepeatNum"] = sol::property([](const InternalMessage::TL2GM_ANNOUNCE& self) { return self.nRepeatNum; }, [](InternalMessage::TL2GM_ANNOUNCE& self, decltype(InternalMessage::TL2GM_ANNOUNCE::nRepeatNum) value) { self.nRepeatNum = value; });
    internal_message_tl2_gm_announce_type["dwIntervalTime"] = sol::property([](const InternalMessage::TL2GM_ANNOUNCE& self) { return self.dwIntervalTime; }, [](InternalMessage::TL2GM_ANNOUNCE& self, decltype(InternalMessage::TL2GM_ANNOUNCE::dwIntervalTime) value) { self.dwIntervalTime = value; });
    internal_message_tl2_gm_announce_type["szText"] = cqyh::lua::string_property(&InternalMessage::TL2GM_ANNOUNCE::szText);
    auto internal_message_tl2_gm_get_announce_list_type = cqyh::lua::usertype<InternalMessage::TL2GM_GET_ANNOUNCE_LIST>(L, internal_message_namespace, "TL2GM_GET_ANNOUNCE_LIST", "InternalMessage::TL2GM_GET_ANNOUNCE_LIST", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_get_announce_list_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_GET_ANNOUNCE_LIST(); });
    internal_message_tl2_gm_get_announce_list_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_GET_ANNOUNCE_LIST>(new InternalMessage::TL2GM_GET_ANNOUNCE_LIST()); });
    internal_message_tl2_gm_get_announce_list_type["nGroupID"] = sol::property([](const InternalMessage::TL2GM_GET_ANNOUNCE_LIST& self) { return self.nGroupID; }, [](InternalMessage::TL2GM_GET_ANNOUNCE_LIST& self, decltype(InternalMessage::TL2GM_GET_ANNOUNCE_LIST::nGroupID) value) { self.nGroupID = value; });
    auto internal_message_tl2_gm_del_announce_type = cqyh::lua::usertype<InternalMessage::TL2GM_DEL_ANNOUNCE>(L, internal_message_namespace, "TL2GM_DEL_ANNOUNCE", "InternalMessage::TL2GM_DEL_ANNOUNCE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_del_announce_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_DEL_ANNOUNCE(); });
    internal_message_tl2_gm_del_announce_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_DEL_ANNOUNCE>(new InternalMessage::TL2GM_DEL_ANNOUNCE()); });
    internal_message_tl2_gm_del_announce_type["nGroupID"] = sol::property([](const InternalMessage::TL2GM_DEL_ANNOUNCE& self) { return self.nGroupID; }, [](InternalMessage::TL2GM_DEL_ANNOUNCE& self, decltype(InternalMessage::TL2GM_DEL_ANNOUNCE::nGroupID) value) { self.nGroupID = value; });
    internal_message_tl2_gm_del_announce_type["dwAnnounceSerial"] = sol::property([](const InternalMessage::TL2GM_DEL_ANNOUNCE& self) { return self.dwAnnounceSerial; }, [](InternalMessage::TL2GM_DEL_ANNOUNCE& self, decltype(InternalMessage::TL2GM_DEL_ANNOUNCE::dwAnnounceSerial) value) { self.dwAnnounceSerial = value; });
    auto internal_message_gm2_tl_announce_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_ANNOUNCE_ACK>(L, internal_message_namespace, "GM2TL_ANNOUNCE_ACK", "InternalMessage::GM2TL_ANNOUNCE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_announce_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_ANNOUNCE_ACK(); });
    internal_message_gm2_tl_announce_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_ANNOUNCE_ACK>(new InternalMessage::GM2TL_ANNOUNCE_ACK()); });
    internal_message_gm2_tl_announce_ack_type["nGroupID"] = sol::property([](const InternalMessage::GM2TL_ANNOUNCE_ACK& self) { return self.nGroupID; }, [](InternalMessage::GM2TL_ANNOUNCE_ACK& self, decltype(InternalMessage::GM2TL_ANNOUNCE_ACK::nGroupID) value) { self.nGroupID = value; });
    internal_message_gm2_tl_announce_ack_type["nAreaID"] = sol::property([](const InternalMessage::GM2TL_ANNOUNCE_ACK& self) { return self.nAreaID; }, [](InternalMessage::GM2TL_ANNOUNCE_ACK& self, decltype(InternalMessage::GM2TL_ANNOUNCE_ACK::nAreaID) value) { self.nAreaID = value; });
    internal_message_gm2_tl_announce_ack_type["nResult"] = sol::property([](const InternalMessage::GM2TL_ANNOUNCE_ACK& self) { return self.nResult; }, [](InternalMessage::GM2TL_ANNOUNCE_ACK& self, decltype(InternalMessage::GM2TL_ANNOUNCE_ACK::nResult) value) { self.nResult = value; });
    auto internal_message_gmtl_announce_data_type = cqyh::lua::usertype<InternalMessage::GMTL_ANNOUNCE_DATA>(L, internal_message_namespace, "GMTL_ANNOUNCE_DATA", "InternalMessage::GMTL_ANNOUNCE_DATA");
    internal_message_gmtl_announce_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GMTL_ANNOUNCE_DATA(); });
    internal_message_gmtl_announce_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GMTL_ANNOUNCE_DATA>(new InternalMessage::GMTL_ANNOUNCE_DATA()); });
    internal_message_gmtl_announce_data_type["nGroupID"] = sol::property([](const InternalMessage::GMTL_ANNOUNCE_DATA& self) { return self.nGroupID; }, [](InternalMessage::GMTL_ANNOUNCE_DATA& self, decltype(InternalMessage::GMTL_ANNOUNCE_DATA::nGroupID) value) { self.nGroupID = value; });
    internal_message_gmtl_announce_data_type["dwSerial"] = sol::property([](const InternalMessage::GMTL_ANNOUNCE_DATA& self) { return self.dwSerial; }, [](InternalMessage::GMTL_ANNOUNCE_DATA& self, decltype(InternalMessage::GMTL_ANNOUNCE_DATA::dwSerial) value) { self.dwSerial = value; });
    internal_message_gmtl_announce_data_type["dwIntervalTime"] = sol::property([](const InternalMessage::GMTL_ANNOUNCE_DATA& self) { return self.dwIntervalTime; }, [](InternalMessage::GMTL_ANNOUNCE_DATA& self, decltype(InternalMessage::GMTL_ANNOUNCE_DATA::dwIntervalTime) value) { self.dwIntervalTime = value; });
    internal_message_gmtl_announce_data_type["dwRepeatNum"] = sol::property([](const InternalMessage::GMTL_ANNOUNCE_DATA& self) { return self.dwRepeatNum; }, [](InternalMessage::GMTL_ANNOUNCE_DATA& self, decltype(InternalMessage::GMTL_ANNOUNCE_DATA::dwRepeatNum) value) { self.dwRepeatNum = value; });
    internal_message_gmtl_announce_data_type["szText"] = cqyh::lua::string_property(&InternalMessage::GMTL_ANNOUNCE_DATA::szText);
    auto internal_message_gm2_tl_get_announce_list_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK>(L, internal_message_namespace, "GM2TL_GET_ANNOUNCE_LIST_ACK", "InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_get_announce_list_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK(); });
    internal_message_gm2_tl_get_announce_list_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK>(new InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK()); });
    internal_message_gm2_tl_get_announce_list_ack_type["nGroupID"] = sol::property([](const InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK& self) { return self.nGroupID; }, [](InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK& self, decltype(InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK::nGroupID) value) { self.nGroupID = value; });
    internal_message_gm2_tl_get_announce_list_ack_type["nCount"] = sol::property([](const InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK& self) { return self.nCount; }, [](InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK& self, decltype(InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK::nCount) value) { self.nCount = value; });
    internal_message_gm2_tl_get_announce_list_ack_type["data"] = cqyh::lua::array_property(&InternalMessage::GM2TL_GET_ANNOUNCE_LIST_ACK::data);
    auto internal_message_gm2_tl_del_announce_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_DEL_ANNOUNCE_ACK>(L, internal_message_namespace, "GM2TL_DEL_ANNOUNCE_ACK", "InternalMessage::GM2TL_DEL_ANNOUNCE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_del_announce_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_DEL_ANNOUNCE_ACK(); });
    internal_message_gm2_tl_del_announce_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_DEL_ANNOUNCE_ACK>(new InternalMessage::GM2TL_DEL_ANNOUNCE_ACK()); });
    internal_message_gm2_tl_del_announce_ack_type["nGroupID"] = sol::property([](const InternalMessage::GM2TL_DEL_ANNOUNCE_ACK& self) { return self.nGroupID; }, [](InternalMessage::GM2TL_DEL_ANNOUNCE_ACK& self, decltype(InternalMessage::GM2TL_DEL_ANNOUNCE_ACK::nGroupID) value) { self.nGroupID = value; });
    internal_message_gm2_tl_del_announce_ack_type["dwAnnounceSerial"] = sol::property([](const InternalMessage::GM2TL_DEL_ANNOUNCE_ACK& self) { return self.dwAnnounceSerial; }, [](InternalMessage::GM2TL_DEL_ANNOUNCE_ACK& self, decltype(InternalMessage::GM2TL_DEL_ANNOUNCE_ACK::dwAnnounceSerial) value) { self.dwAnnounceSerial = value; });
}

}
