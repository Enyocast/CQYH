#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_game_to_manage_teams_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_team_sync_member_type = cqyh::lua::usertype<InternalMessage::G2M_TEAM_SYNC_MEMBER>(L, internal_message_namespace, "G2M_TEAM_SYNC_MEMBER", "InternalMessage::G2M_TEAM_SYNC_MEMBER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_team_sync_member_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_TEAM_SYNC_MEMBER(); });
    internal_message_g2m_team_sync_member_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_TEAM_SYNC_MEMBER>(new InternalMessage::G2M_TEAM_SYNC_MEMBER()); });
    internal_message_g2m_team_sync_member_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.dwRoleID; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_team_sync_member_type["nLevel"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nLevel; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nLevel) value) { self.nLevel = value; });
    internal_message_g2m_team_sync_member_type["nMaxHp"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nMaxHp; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nMaxHp) value) { self.nMaxHp = value; });
    internal_message_g2m_team_sync_member_type["nMaxMp"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nMaxMp; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nMaxMp) value) { self.nMaxMp = value; });
    internal_message_g2m_team_sync_member_type["nCurHp"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nCurHp; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nCurHp) value) { self.nCurHp = value; });
    internal_message_g2m_team_sync_member_type["nCurMp"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nCurMp; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nCurMp) value) { self.nCurMp = value; });
    internal_message_g2m_team_sync_member_type["nX"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nX; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nX) value) { self.nX = value; });
    internal_message_g2m_team_sync_member_type["nY"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nY; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nY) value) { self.nY = value; });
    internal_message_g2m_team_sync_member_type["nZ"] = sol::property([](const InternalMessage::G2M_TEAM_SYNC_MEMBER& self) { return self.nZ; }, [](InternalMessage::G2M_TEAM_SYNC_MEMBER& self, decltype(InternalMessage::G2M_TEAM_SYNC_MEMBER::nZ) value) { self.nZ = value; });
    auto internal_message_g2m_leave_team_type = cqyh::lua::usertype<InternalMessage::G2M_LEAVE_TEAM>(L, internal_message_namespace, "G2M_LEAVE_TEAM", "InternalMessage::G2M_LEAVE_TEAM", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_leave_team_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_LEAVE_TEAM(); });
    internal_message_g2m_leave_team_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_LEAVE_TEAM>(new InternalMessage::G2M_LEAVE_TEAM()); });
    internal_message_g2m_leave_team_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_LEAVE_TEAM& self) { return self.dwRoleID; }, [](InternalMessage::G2M_LEAVE_TEAM& self, decltype(InternalMessage::G2M_LEAVE_TEAM::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2m_recall_team_member_type = cqyh::lua::usertype<InternalMessage::G2M_RECALL_TEAM_MEMBER>(L, internal_message_namespace, "G2M_RECALL_TEAM_MEMBER", "InternalMessage::G2M_RECALL_TEAM_MEMBER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_recall_team_member_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_RECALL_TEAM_MEMBER(); });
    internal_message_g2m_recall_team_member_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_RECALL_TEAM_MEMBER>(new InternalMessage::G2M_RECALL_TEAM_MEMBER()); });
    internal_message_g2m_recall_team_member_type["dwLeaderID"] = sol::property([](const InternalMessage::G2M_RECALL_TEAM_MEMBER& self) { return self.dwLeaderID; }, [](InternalMessage::G2M_RECALL_TEAM_MEMBER& self, decltype(InternalMessage::G2M_RECALL_TEAM_MEMBER::dwLeaderID) value) { self.dwLeaderID = value; });
    internal_message_g2m_recall_team_member_type["nSceneTempID"] = sol::property([](const InternalMessage::G2M_RECALL_TEAM_MEMBER& self) { return self.nSceneTempID; }, [](InternalMessage::G2M_RECALL_TEAM_MEMBER& self, decltype(InternalMessage::G2M_RECALL_TEAM_MEMBER::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_g2m_recall_team_member_type["nSceneID"] = sol::property([](const InternalMessage::G2M_RECALL_TEAM_MEMBER& self) { return self.nSceneID; }, [](InternalMessage::G2M_RECALL_TEAM_MEMBER& self, decltype(InternalMessage::G2M_RECALL_TEAM_MEMBER::nSceneID) value) { self.nSceneID = value; });
    internal_message_g2m_recall_team_member_type["nX"] = sol::property([](const InternalMessage::G2M_RECALL_TEAM_MEMBER& self) { return self.nX; }, [](InternalMessage::G2M_RECALL_TEAM_MEMBER& self, decltype(InternalMessage::G2M_RECALL_TEAM_MEMBER::nX) value) { self.nX = value; });
    internal_message_g2m_recall_team_member_type["nY"] = sol::property([](const InternalMessage::G2M_RECALL_TEAM_MEMBER& self) { return self.nY; }, [](InternalMessage::G2M_RECALL_TEAM_MEMBER& self, decltype(InternalMessage::G2M_RECALL_TEAM_MEMBER::nY) value) { self.nY = value; });
    internal_message_g2m_recall_team_member_type["nZ"] = sol::property([](const InternalMessage::G2M_RECALL_TEAM_MEMBER& self) { return self.nZ; }, [](InternalMessage::G2M_RECALL_TEAM_MEMBER& self, decltype(InternalMessage::G2M_RECALL_TEAM_MEMBER::nZ) value) { self.nZ = value; });
}

}
