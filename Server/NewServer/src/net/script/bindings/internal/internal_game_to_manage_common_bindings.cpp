#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_game_to_manage_common_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_ready_type = cqyh::lua::usertype<InternalMessage::G2M_READY>(L, internal_message_namespace, "G2M_READY", "InternalMessage::G2M_READY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_ready_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_READY(); });
    internal_message_g2m_ready_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_READY>(new InternalMessage::G2M_READY()); });
    auto internal_message_g2m_pre_enter_gs_ack_type = cqyh::lua::usertype<InternalMessage::G2M_PRE_ENTER_GS_ACK>(L, internal_message_namespace, "G2M_PRE_ENTER_GS_ACK", "InternalMessage::G2M_PRE_ENTER_GS_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_pre_enter_gs_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_PRE_ENTER_GS_ACK(); });
    internal_message_g2m_pre_enter_gs_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_PRE_ENTER_GS_ACK>(new InternalMessage::G2M_PRE_ENTER_GS_ACK()); });
    internal_message_g2m_pre_enter_gs_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2M_PRE_ENTER_GS_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::G2M_PRE_ENTER_GS_ACK& self, decltype(InternalMessage::G2M_PRE_ENTER_GS_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2m_pre_enter_gs_ack_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_PRE_ENTER_GS_ACK& self) { return self.dwRoleID; }, [](InternalMessage::G2M_PRE_ENTER_GS_ACK& self, decltype(InternalMessage::G2M_PRE_ENTER_GS_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_pre_enter_gs_ack_type["nErrCode"] = sol::property([](const InternalMessage::G2M_PRE_ENTER_GS_ACK& self) { return self.nErrCode; }, [](InternalMessage::G2M_PRE_ENTER_GS_ACK& self, decltype(InternalMessage::G2M_PRE_ENTER_GS_ACK::nErrCode) value) { self.nErrCode = value; });
    auto internal_message_g2m_enter_gs_type = cqyh::lua::usertype<InternalMessage::G2M_ENTER_GS>(L, internal_message_namespace, "G2M_ENTER_GS", "InternalMessage::G2M_ENTER_GS", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_enter_gs_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ENTER_GS(); });
    internal_message_g2m_enter_gs_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ENTER_GS>(new InternalMessage::G2M_ENTER_GS()); });
    internal_message_g2m_enter_gs_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.dwClientSessionID; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2m_enter_gs_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_enter_gs_type["llMasterExp"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.llMasterExp; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::llMasterExp) value) { self.llMasterExp = value; });
    internal_message_g2m_enter_gs_type["dwMasterCD"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.dwMasterCD; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::dwMasterCD) value) { self.dwMasterCD = value; });
    internal_message_g2m_enter_gs_type["dwGuildCD"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.dwGuildCD; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::dwGuildCD) value) { self.dwGuildCD = value; });
    internal_message_g2m_enter_gs_type["byGMLevel"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.byGMLevel; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::byGMLevel) value) { self.byGMLevel = value; });
    internal_message_g2m_enter_gs_type["byTwitter"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.byTwitter; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::byTwitter) value) { self.byTwitter = value; });
    internal_message_g2m_enter_gs_type["dwMasterTwitterCD"] = sol::property([](const InternalMessage::G2M_ENTER_GS& self) { return self.dwMasterTwitterCD; }, [](InternalMessage::G2M_ENTER_GS& self, decltype(InternalMessage::G2M_ENTER_GS::dwMasterTwitterCD) value) { self.dwMasterTwitterCD = value; });
    internal_message_g2m_enter_gs_type["szSignature"] = cqyh::lua::string_property(&InternalMessage::G2M_ENTER_GS::szSignature);
    auto internal_message_g2m_leave_gs_ack_type = cqyh::lua::usertype<InternalMessage::G2M_LEAVE_GS_ACK>(L, internal_message_namespace, "G2M_LEAVE_GS_ACK", "InternalMessage::G2M_LEAVE_GS_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_leave_gs_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_LEAVE_GS_ACK(); });
    internal_message_g2m_leave_gs_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_LEAVE_GS_ACK>(new InternalMessage::G2M_LEAVE_GS_ACK()); });
    internal_message_g2m_leave_gs_ack_type["dwClientSessionID"] = sol::property([](const InternalMessage::G2M_LEAVE_GS_ACK& self) { return self.dwClientSessionID; }, [](InternalMessage::G2M_LEAVE_GS_ACK& self, decltype(InternalMessage::G2M_LEAVE_GS_ACK::dwClientSessionID) value) { self.dwClientSessionID = value; });
    internal_message_g2m_leave_gs_ack_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_LEAVE_GS_ACK& self) { return self.dwRoleID; }, [](InternalMessage::G2M_LEAVE_GS_ACK& self, decltype(InternalMessage::G2M_LEAVE_GS_ACK::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2m_server_info_type = cqyh::lua::usertype<InternalMessage::G2M_SERVER_INFO>(L, internal_message_namespace, "G2M_SERVER_INFO", "InternalMessage::G2M_SERVER_INFO", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_server_info_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_SERVER_INFO(); });
    internal_message_g2m_server_info_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_SERVER_INFO>(new InternalMessage::G2M_SERVER_INFO()); });
    auto internal_message_g2m_close_ack_type = cqyh::lua::usertype<InternalMessage::G2M_CLOSE_ACK>(L, internal_message_namespace, "G2M_CLOSE_ACK", "InternalMessage::G2M_CLOSE_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_close_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_CLOSE_ACK(); });
    internal_message_g2m_close_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_CLOSE_ACK>(new InternalMessage::G2M_CLOSE_ACK()); });
    auto internal_message_g2m_add_kill_list_type = cqyh::lua::usertype<InternalMessage::G2M_ADD_KILL_LIST>(L, internal_message_namespace, "G2M_ADD_KILL_LIST", "InternalMessage::G2M_ADD_KILL_LIST", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_add_kill_list_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ADD_KILL_LIST(); });
    internal_message_g2m_add_kill_list_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ADD_KILL_LIST>(new InternalMessage::G2M_ADD_KILL_LIST()); });
    internal_message_g2m_add_kill_list_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ADD_KILL_LIST& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ADD_KILL_LIST& self, decltype(InternalMessage::G2M_ADD_KILL_LIST::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_add_kill_list_type["dwKillerID"] = sol::property([](const InternalMessage::G2M_ADD_KILL_LIST& self) { return self.dwKillerID; }, [](InternalMessage::G2M_ADD_KILL_LIST& self, decltype(InternalMessage::G2M_ADD_KILL_LIST::dwKillerID) value) { self.dwKillerID = value; });
    auto internal_message_g2m_update_ranklist_node_type = cqyh::lua::usertype<InternalMessage::G2M_UPDATE_RANKLIST_NODE>(L, internal_message_namespace, "G2M_UPDATE_RANKLIST_NODE", "InternalMessage::G2M_UPDATE_RANKLIST_NODE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_update_ranklist_node_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_UPDATE_RANKLIST_NODE(); });
    internal_message_g2m_update_ranklist_node_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_UPDATE_RANKLIST_NODE>(new InternalMessage::G2M_UPDATE_RANKLIST_NODE()); });
    internal_message_g2m_update_ranklist_node_type["byServerGroup"] = sol::property([](const InternalMessage::G2M_UPDATE_RANKLIST_NODE& self) { return self.byServerGroup; }, [](InternalMessage::G2M_UPDATE_RANKLIST_NODE& self, decltype(InternalMessage::G2M_UPDATE_RANKLIST_NODE::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_g2m_update_ranklist_node_type["nRankListType"] = sol::property([](const InternalMessage::G2M_UPDATE_RANKLIST_NODE& self) { return self.nRankListType; }, [](InternalMessage::G2M_UPDATE_RANKLIST_NODE& self, decltype(InternalMessage::G2M_UPDATE_RANKLIST_NODE::nRankListType) value) { self.nRankListType = value; });
    internal_message_g2m_update_ranklist_node_type["llKey"] = sol::property([](const InternalMessage::G2M_UPDATE_RANKLIST_NODE& self) { return self.llKey; }, [](InternalMessage::G2M_UPDATE_RANKLIST_NODE& self, decltype(InternalMessage::G2M_UPDATE_RANKLIST_NODE::llKey) value) { self.llKey = value; });
    internal_message_g2m_update_ranklist_node_type["llValue"] = sol::property([](const InternalMessage::G2M_UPDATE_RANKLIST_NODE& self) { return self.llValue; }, [](InternalMessage::G2M_UPDATE_RANKLIST_NODE& self, decltype(InternalMessage::G2M_UPDATE_RANKLIST_NODE::llValue) value) { self.llValue = value; });
    auto internal_message_g2m_adventure_trigger_type = cqyh::lua::usertype<InternalMessage::G2M_ADVENTURE_TRIGGER>(L, internal_message_namespace, "G2M_ADVENTURE_TRIGGER", "InternalMessage::G2M_ADVENTURE_TRIGGER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_adventure_trigger_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ADVENTURE_TRIGGER(); });
    internal_message_g2m_adventure_trigger_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ADVENTURE_TRIGGER>(new InternalMessage::G2M_ADVENTURE_TRIGGER()); });
    internal_message_g2m_adventure_trigger_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ADVENTURE_TRIGGER& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ADVENTURE_TRIGGER& self, decltype(InternalMessage::G2M_ADVENTURE_TRIGGER::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_adventure_trigger_type["nAdventureID"] = sol::property([](const InternalMessage::G2M_ADVENTURE_TRIGGER& self) { return self.nAdventureID; }, [](InternalMessage::G2M_ADVENTURE_TRIGGER& self, decltype(InternalMessage::G2M_ADVENTURE_TRIGGER::nAdventureID) value) { self.nAdventureID = value; });
    internal_message_g2m_adventure_trigger_type["nVarID"] = sol::property([](const InternalMessage::G2M_ADVENTURE_TRIGGER& self) { return self.nVarID; }, [](InternalMessage::G2M_ADVENTURE_TRIGGER& self, decltype(InternalMessage::G2M_ADVENTURE_TRIGGER::nVarID) value) { self.nVarID = value; });
    internal_message_g2m_adventure_trigger_type["nMaxCount"] = sol::property([](const InternalMessage::G2M_ADVENTURE_TRIGGER& self) { return self.nMaxCount; }, [](InternalMessage::G2M_ADVENTURE_TRIGGER& self, decltype(InternalMessage::G2M_ADVENTURE_TRIGGER::nMaxCount) value) { self.nMaxCount = value; });
    internal_message_g2m_adventure_trigger_type["nChance"] = sol::property([](const InternalMessage::G2M_ADVENTURE_TRIGGER& self) { return self.nChance; }, [](InternalMessage::G2M_ADVENTURE_TRIGGER& self, decltype(InternalMessage::G2M_ADVENTURE_TRIGGER::nChance) value) { self.nChance = value; });
}

}
