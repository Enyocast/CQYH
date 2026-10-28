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

void register_internal_manage_to_game_common_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_pre_enter_gs_type = cqyh::lua::usertype<InternalMessage::M2G_PRE_ENTER_GS>(L, internal_message_namespace, "M2G_PRE_ENTER_GS", "InternalMessage::M2G_PRE_ENTER_GS", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_pre_enter_gs_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_PRE_ENTER_GS(); });
    internal_message_m2g_pre_enter_gs_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_PRE_ENTER_GS>(new InternalMessage::M2G_PRE_ENTER_GS()); });
    internal_message_m2g_pre_enter_gs_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_pre_enter_gs_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.dwRoleID; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_pre_enter_gs_type["szUserName"] = cqyh::lua::string_property(&InternalMessage::M2G_PRE_ENTER_GS::szUserName);
    internal_message_m2g_pre_enter_gs_type["byFcmState"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.byFcmState; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::byFcmState) value) { self.byFcmState = value; });
    internal_message_m2g_pre_enter_gs_type["bIpWhiteList"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.bIpWhiteList; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::bIpWhiteList) value) { self.bIpWhiteList = value; });
    internal_message_m2g_pre_enter_gs_type["bUserWhiteList"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.bUserWhiteList; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::bUserWhiteList) value) { self.bUserWhiteList = value; });
    internal_message_m2g_pre_enter_gs_type["dwIpAddr"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.dwIpAddr; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::dwIpAddr) value) { self.dwIpAddr = value; });
    internal_message_m2g_pre_enter_gs_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_pre_enter_gs_type["nSceneID"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.nSceneID; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::nSceneID) value) { self.nSceneID = value; });
    internal_message_m2g_pre_enter_gs_type["nDestX"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.nDestX; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::nDestX) value) { self.nDestX = value; });
    internal_message_m2g_pre_enter_gs_type["nDestY"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.nDestY; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::nDestY) value) { self.nDestY = value; });
    internal_message_m2g_pre_enter_gs_type["nDestZ"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.nDestZ; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::nDestZ) value) { self.nDestZ = value; });
    internal_message_m2g_pre_enter_gs_type["wFaceDirection"] = sol::property([](const InternalMessage::M2G_PRE_ENTER_GS& self) { return self.wFaceDirection; }, [](InternalMessage::M2G_PRE_ENTER_GS& self, decltype(InternalMessage::M2G_PRE_ENTER_GS::wFaceDirection) value) { self.wFaceDirection = value; });
    auto internal_message_m2g_enter_gs_ack_type = cqyh::lua::usertype<InternalMessage::M2G_ENTER_GS_ACK>(L, internal_message_namespace, "M2G_ENTER_GS_ACK", "InternalMessage::M2G_ENTER_GS_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_enter_gs_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_ENTER_GS_ACK(); });
    internal_message_m2g_enter_gs_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_ENTER_GS_ACK>(new InternalMessage::M2G_ENTER_GS_ACK()); });
    internal_message_m2g_enter_gs_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2G_ENTER_GS_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::M2G_ENTER_GS_ACK& self, decltype(InternalMessage::M2G_ENTER_GS_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2g_enter_gs_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_ENTER_GS_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2G_ENTER_GS_ACK& self, decltype(InternalMessage::M2G_ENTER_GS_ACK::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_m2g_leave_gs_type = cqyh::lua::usertype<InternalMessage::M2G_LEAVE_GS>(L, internal_message_namespace, "M2G_LEAVE_GS", "InternalMessage::M2G_LEAVE_GS", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_leave_gs_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_LEAVE_GS(); });
    internal_message_m2g_leave_gs_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_LEAVE_GS>(new InternalMessage::M2G_LEAVE_GS()); });
    internal_message_m2g_leave_gs_type["dwClientSessionID"] = sol::property([](const InternalMessage::M2G_LEAVE_GS& self) { return self.dwClientSessionID; }, [](InternalMessage::M2G_LEAVE_GS& self, decltype(InternalMessage::M2G_LEAVE_GS::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_m2g_leave_gs_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_LEAVE_GS& self) { return self.dwRoleID; }, [](InternalMessage::M2G_LEAVE_GS& self, decltype(InternalMessage::M2G_LEAVE_GS::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_m2g_change_info_type = cqyh::lua::usertype<InternalMessage::M2G_CHANGE_INFO>(L, internal_message_namespace, "M2G_CHANGE_INFO", "InternalMessage::M2G_CHANGE_INFO", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_change_info_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_CHANGE_INFO(); });
    internal_message_m2g_change_info_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_CHANGE_INFO>(new InternalMessage::M2G_CHANGE_INFO()); });
    internal_message_m2g_change_info_type["dwCliSessionID"] = sol::property([](const InternalMessage::M2G_CHANGE_INFO& self) { return self.dwCliSessionID; }, [](InternalMessage::M2G_CHANGE_INFO& self, decltype(InternalMessage::M2G_CHANGE_INFO::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_m2g_change_info_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_CHANGE_INFO& self) { return self.dwRoleID; }, [](InternalMessage::M2G_CHANGE_INFO& self, decltype(InternalMessage::M2G_CHANGE_INFO::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_change_info_type["szSignature"] = cqyh::lua::string_property(&InternalMessage::M2G_CHANGE_INFO::szSignature);
    auto internal_message_m2g_update_statistic_value_type = cqyh::lua::usertype<InternalMessage::M2G_UPDATE_STATISTIC_VALUE>(L, internal_message_namespace, "M2G_UPDATE_STATISTIC_VALUE", "InternalMessage::M2G_UPDATE_STATISTIC_VALUE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_update_statistic_value_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_UPDATE_STATISTIC_VALUE(); });
    internal_message_m2g_update_statistic_value_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_UPDATE_STATISTIC_VALUE>(new InternalMessage::M2G_UPDATE_STATISTIC_VALUE()); });
    internal_message_m2g_update_statistic_value_type["dwID"] = sol::property([](const InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self) { return self.dwID; }, [](InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self, decltype(InternalMessage::M2G_UPDATE_STATISTIC_VALUE::dwID) value) { self.dwID = value; });
    internal_message_m2g_update_statistic_value_type["dwType"] = sol::property([](const InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self) { return self.dwType; }, [](InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self, decltype(InternalMessage::M2G_UPDATE_STATISTIC_VALUE::dwType) value) { self.dwType = value; });
    internal_message_m2g_update_statistic_value_type["dwIndex"] = sol::property([](const InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self) { return self.dwIndex; }, [](InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self, decltype(InternalMessage::M2G_UPDATE_STATISTIC_VALUE::dwIndex) value) { self.dwIndex = value; });
    internal_message_m2g_update_statistic_value_type["nValue"] = sol::property([](const InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self) { return self.nValue; }, [](InternalMessage::M2G_UPDATE_STATISTIC_VALUE& self, decltype(InternalMessage::M2G_UPDATE_STATISTIC_VALUE::nValue) value) { self.nValue = value; });
    auto internal_message_m2g_adventure_reward_type = cqyh::lua::usertype<InternalMessage::M2G_ADVENTURE_REWARD>(L, internal_message_namespace, "M2G_ADVENTURE_REWARD", "InternalMessage::M2G_ADVENTURE_REWARD", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_adventure_reward_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_ADVENTURE_REWARD(); });
    internal_message_m2g_adventure_reward_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_ADVENTURE_REWARD>(new InternalMessage::M2G_ADVENTURE_REWARD()); });
    internal_message_m2g_adventure_reward_type["nServerGroup"] = sol::property([](const InternalMessage::M2G_ADVENTURE_REWARD& self) { return self.nServerGroup; }, [](InternalMessage::M2G_ADVENTURE_REWARD& self, decltype(InternalMessage::M2G_ADVENTURE_REWARD::nServerGroup) value) { self.nServerGroup = value; });
    internal_message_m2g_adventure_reward_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_ADVENTURE_REWARD& self) { return self.dwRoleID; }, [](InternalMessage::M2G_ADVENTURE_REWARD& self, decltype(InternalMessage::M2G_ADVENTURE_REWARD::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_adventure_reward_type["nGroupID"] = sol::property([](const InternalMessage::M2G_ADVENTURE_REWARD& self) { return self.nGroupID; }, [](InternalMessage::M2G_ADVENTURE_REWARD& self, decltype(InternalMessage::M2G_ADVENTURE_REWARD::nGroupID) value) { self.nGroupID = value; });
    internal_message_m2g_adventure_reward_type["nAdventureID"] = sol::property([](const InternalMessage::M2G_ADVENTURE_REWARD& self) { return self.nAdventureID; }, [](InternalMessage::M2G_ADVENTURE_REWARD& self, decltype(InternalMessage::M2G_ADVENTURE_REWARD::nAdventureID) value) { self.nAdventureID = value; });
    auto internal_message_server_var_data_type = cqyh::lua::usertype<InternalMessage::SERVER_VAR_DATA>(L, internal_message_namespace, "SERVER_VAR_DATA", "InternalMessage::SERVER_VAR_DATA");
    internal_message_server_var_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::SERVER_VAR_DATA(); });
    internal_message_server_var_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::SERVER_VAR_DATA>(new InternalMessage::SERVER_VAR_DATA()); });
    internal_message_server_var_data_type["qwKey"] = sol::property([](const InternalMessage::SERVER_VAR_DATA& self) { return self.qwKey; }, [](InternalMessage::SERVER_VAR_DATA& self, decltype(InternalMessage::SERVER_VAR_DATA::qwKey) value) { self.qwKey = value; });
    internal_message_server_var_data_type["nValue"] = sol::property([](const InternalMessage::SERVER_VAR_DATA& self) { return self.nValue; }, [](InternalMessage::SERVER_VAR_DATA& self, decltype(InternalMessage::SERVER_VAR_DATA::nValue) value) { self.nValue = value; });
}

}
