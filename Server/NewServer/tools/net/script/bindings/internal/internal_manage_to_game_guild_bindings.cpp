#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/m2g_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"
#include "../../../../../../Common/define/variable_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_manage_to_game_guild_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_pre_create_guild_type = cqyh::lua::usertype<InternalMessage::M2G_PRE_CREATE_GUILD>(L, internal_message_namespace, "M2G_PRE_CREATE_GUILD", "InternalMessage::M2G_PRE_CREATE_GUILD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_pre_create_guild_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_PRE_CREATE_GUILD(); });
    internal_message_m2g_pre_create_guild_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_PRE_CREATE_GUILD>(new InternalMessage::M2G_PRE_CREATE_GUILD()); });
    internal_message_m2g_pre_create_guild_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_PRE_CREATE_GUILD& self) { return self.dwRoleID; }, [](InternalMessage::M2G_PRE_CREATE_GUILD& self, decltype(InternalMessage::M2G_PRE_CREATE_GUILD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_pre_create_guild_type["szGuildName"] = cqyh::lua::string_property(&InternalMessage::M2G_PRE_CREATE_GUILD::szGuildName);
    internal_message_m2g_pre_create_guild_type["byIsNeedToConsume"] = sol::property([](const InternalMessage::M2G_PRE_CREATE_GUILD& self) { return self.byIsNeedToConsume; }, [](InternalMessage::M2G_PRE_CREATE_GUILD& self, decltype(InternalMessage::M2G_PRE_CREATE_GUILD::byIsNeedToConsume) value) { self.byIsNeedToConsume = value; });
    auto internal_message_m2g_role_add_guild_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_ROLE_ADD_GUILD_NTF>(L, internal_message_namespace, "M2G_ROLE_ADD_GUILD_NTF", "InternalMessage::M2G_ROLE_ADD_GUILD_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_role_add_guild_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_ROLE_ADD_GUILD_NTF(); });
    internal_message_m2g_role_add_guild_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_ROLE_ADD_GUILD_NTF>(new InternalMessage::M2G_ROLE_ADD_GUILD_NTF()); });
    internal_message_m2g_role_add_guild_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self, decltype(InternalMessage::M2G_ROLE_ADD_GUILD_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_role_add_guild_ntf_type["nState"] = sol::property([](const InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self) { return self.nState; }, [](InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self, decltype(InternalMessage::M2G_ROLE_ADD_GUILD_NTF::nState) value) { self.nState = value; });
    internal_message_m2g_role_add_guild_ntf_type["dwLeaderID"] = sol::property([](const InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self) { return self.dwLeaderID; }, [](InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self, decltype(InternalMessage::M2G_ROLE_ADD_GUILD_NTF::dwLeaderID) value) { self.dwLeaderID = value; });
    internal_message_m2g_role_add_guild_ntf_type["szGuildName"] = cqyh::lua::string_property(&InternalMessage::M2G_ROLE_ADD_GUILD_NTF::szGuildName);
    internal_message_m2g_role_add_guild_ntf_type["byBuildingNum"] = sol::property([](const InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self) { return self.byBuildingNum; }, [](InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self, decltype(InternalMessage::M2G_ROLE_ADD_GUILD_NTF::byBuildingNum) value) { self.byBuildingNum = value; });
    internal_message_m2g_role_add_guild_ntf_type["byUpgradeBuildingNum"] = sol::property([](const InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self) { return self.byUpgradeBuildingNum; }, [](InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self, decltype(InternalMessage::M2G_ROLE_ADD_GUILD_NTF::byUpgradeBuildingNum) value) { self.byUpgradeBuildingNum = value; });
    internal_message_m2g_role_add_guild_ntf_type["byServerGroup"] = sol::property([](const InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self) { return self.byServerGroup; }, [](InternalMessage::M2G_ROLE_ADD_GUILD_NTF& self, decltype(InternalMessage::M2G_ROLE_ADD_GUILD_NTF::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_m2g_role_add_guild_ntf_type["arrBData"] = cqyh::lua::array_property(&InternalMessage::M2G_ROLE_ADD_GUILD_NTF::arrBData);
    auto internal_message_m2g_guild_delete_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_DELETE_NTF>(L, internal_message_namespace, "M2G_GUILD_DELETE_NTF", "InternalMessage::M2G_GUILD_DELETE_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_delete_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_DELETE_NTF(); });
    internal_message_m2g_guild_delete_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_DELETE_NTF>(new InternalMessage::M2G_GUILD_DELETE_NTF()); });
    internal_message_m2g_guild_delete_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_DELETE_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_DELETE_NTF& self, decltype(InternalMessage::M2G_GUILD_DELETE_NTF::dwGuildID) value) { self.dwGuildID = value; });
    auto internal_message_m2g_sync_guild_data_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_SYNC_GUILD_DATA_NTF>(L, internal_message_namespace, "M2G_SYNC_GUILD_DATA_NTF", "InternalMessage::M2G_SYNC_GUILD_DATA_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_sync_guild_data_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_SYNC_GUILD_DATA_NTF(); });
    internal_message_m2g_sync_guild_data_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_SYNC_GUILD_DATA_NTF>(new InternalMessage::M2G_SYNC_GUILD_DATA_NTF()); });
    internal_message_m2g_sync_guild_data_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_sync_guild_data_ntf_type["nState"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.nState; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::nState) value) { self.nState = value; });
    internal_message_m2g_sync_guild_data_ntf_type["dwLeaderID"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.dwLeaderID; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::dwLeaderID) value) { self.dwLeaderID = value; });
    internal_message_m2g_sync_guild_data_ntf_type["szGuildName"] = cqyh::lua::string_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::szGuildName);
    internal_message_m2g_sync_guild_data_ntf_type["byMemberNum"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.byMemberNum; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::byMemberNum) value) { self.byMemberNum = value; });
    internal_message_m2g_sync_guild_data_ntf_type["memberList"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::memberList);
    internal_message_m2g_sync_guild_data_ntf_type["byAllianceNum"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.byAllianceNum; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::byAllianceNum) value) { self.byAllianceNum = value; });
    internal_message_m2g_sync_guild_data_ntf_type["arrAllianceID"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::arrAllianceID);
    internal_message_m2g_sync_guild_data_ntf_type["byEnemyNum"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.byEnemyNum; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::byEnemyNum) value) { self.byEnemyNum = value; });
    internal_message_m2g_sync_guild_data_ntf_type["arrEnemyID"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::arrEnemyID);
    internal_message_m2g_sync_guild_data_ntf_type["arrWelfareAuraLvl"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::arrWelfareAuraLvl);
    internal_message_m2g_sync_guild_data_ntf_type["arrVariables"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::arrVariables);
    internal_message_m2g_sync_guild_data_ntf_type["byBuildingNum"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.byBuildingNum; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::byBuildingNum) value) { self.byBuildingNum = value; });
    internal_message_m2g_sync_guild_data_ntf_type["byUpgradeBuildingNum"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.byUpgradeBuildingNum; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::byUpgradeBuildingNum) value) { self.byUpgradeBuildingNum = value; });
    internal_message_m2g_sync_guild_data_ntf_type["dwSabacEnrollTime"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::dwSabacEnrollTime);
    internal_message_m2g_sync_guild_data_ntf_type["bySabacOccupied"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.bySabacOccupied; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::bySabacOccupied) value) { self.bySabacOccupied = value; });
    internal_message_m2g_sync_guild_data_ntf_type["byServerGroup"] = sol::property([](const InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self) { return self.byServerGroup; }, [](InternalMessage::M2G_SYNC_GUILD_DATA_NTF& self, decltype(InternalMessage::M2G_SYNC_GUILD_DATA_NTF::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_m2g_sync_guild_data_ntf_type["arrBData"] = cqyh::lua::array_property(&InternalMessage::M2G_SYNC_GUILD_DATA_NTF::arrBData);
    auto internal_message_m2g_guild_sync_attr_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_SYNC_ATTR_NTF>(L, internal_message_namespace, "M2G_GUILD_SYNC_ATTR_NTF", "InternalMessage::M2G_GUILD_SYNC_ATTR_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_sync_attr_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_SYNC_ATTR_NTF(); });
    internal_message_m2g_guild_sync_attr_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_SYNC_ATTR_NTF>(new InternalMessage::M2G_GUILD_SYNC_ATTR_NTF()); });
    internal_message_m2g_guild_sync_attr_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_ATTR_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_SYNC_ATTR_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_ATTR_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_sync_attr_ntf_type["nAttrType"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_ATTR_NTF& self) { return self.nAttrType; }, [](InternalMessage::M2G_GUILD_SYNC_ATTR_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_ATTR_NTF::nAttrType) value) { self.nAttrType = value; });
    internal_message_m2g_guild_sync_attr_ntf_type["dwAttrValue"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_ATTR_NTF& self) { return self.dwAttrValue; }, [](InternalMessage::M2G_GUILD_SYNC_ATTR_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_ATTR_NTF::dwAttrValue) value) { self.dwAttrValue = value; });
    auto internal_message_m2g_guild_update_state_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_UPDATE_STATE_NTF>(L, internal_message_namespace, "M2G_GUILD_UPDATE_STATE_NTF", "InternalMessage::M2G_GUILD_UPDATE_STATE_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_update_state_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_UPDATE_STATE_NTF(); });
    internal_message_m2g_guild_update_state_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_UPDATE_STATE_NTF>(new InternalMessage::M2G_GUILD_UPDATE_STATE_NTF()); });
    internal_message_m2g_guild_update_state_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_STATE_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_UPDATE_STATE_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_STATE_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_update_state_ntf_type["nState"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_STATE_NTF& self) { return self.nState; }, [](InternalMessage::M2G_GUILD_UPDATE_STATE_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_STATE_NTF::nState) value) { self.nState = value; });
    auto internal_message_m2g_guild_change_res_ack_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_CHANGE_RES_ACK>(L, internal_message_namespace, "M2G_GUILD_CHANGE_RES_ACK", "InternalMessage::M2G_GUILD_CHANGE_RES_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_change_res_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_CHANGE_RES_ACK(); });
    internal_message_m2g_guild_change_res_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_CHANGE_RES_ACK>(new InternalMessage::M2G_GUILD_CHANGE_RES_ACK()); });
    internal_message_m2g_guild_change_res_ack_type["dwNpcID"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self) { return self.dwNpcID; }, [](InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self, decltype(InternalMessage::M2G_GUILD_CHANGE_RES_ACK::dwNpcID) value) { self.dwNpcID = value; });
    internal_message_m2g_guild_change_res_ack_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self, decltype(InternalMessage::M2G_GUILD_CHANGE_RES_ACK::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_change_res_ack_type["bAdd"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self) { return static_cast<bool>(self.bAdd); }, [](InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self, bool value) { self.bAdd = value; });
    internal_message_m2g_guild_change_res_ack_type["nResType"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self) { return self.nResType; }, [](InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self, decltype(InternalMessage::M2G_GUILD_CHANGE_RES_ACK::nResType) value) { self.nResType = value; });
    internal_message_m2g_guild_change_res_ack_type["nCount"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self) { return self.nCount; }, [](InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self, decltype(InternalMessage::M2G_GUILD_CHANGE_RES_ACK::nCount) value) { self.nCount = value; });
    internal_message_m2g_guild_change_res_ack_type["byCtxType"] = sol::property([](const InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self) { return self.byCtxType; }, [](InternalMessage::M2G_GUILD_CHANGE_RES_ACK& self, decltype(InternalMessage::M2G_GUILD_CHANGE_RES_ACK::byCtxType) value) { self.byCtxType = value; });
}

}
