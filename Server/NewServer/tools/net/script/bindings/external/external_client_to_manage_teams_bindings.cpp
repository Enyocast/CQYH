#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/message/external_message_header.h"
#include "../../../../../../Common/message/c2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_external_client_to_manage_teams_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table external_message_namespace = globals["ExternalMessage"].get_or_create<sol::table>();
    auto external_message_c2m_team_join_type = cqyh::lua::usertype<ExternalMessage::C2M_TEAM_JOIN>(L, external_message_namespace, "C2M_TEAM_JOIN", "ExternalMessage::C2M_TEAM_JOIN", sol::base_classes, sol::bases<ExternalMessage::MESSAGE_HEADER>());
    external_message_c2m_team_join_type.set_function("new", [](sol::table) -> decltype(auto) { return new ExternalMessage::C2M_TEAM_JOIN(); });
    external_message_c2m_team_join_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<ExternalMessage::C2M_TEAM_JOIN>(new ExternalMessage::C2M_TEAM_JOIN()); });
    external_message_c2m_team_join_type["dwTargetRoleID"] = sol::property([](const ExternalMessage::C2M_TEAM_JOIN& self) { return self.dwTargetRoleID; }, [](ExternalMessage::C2M_TEAM_JOIN& self, decltype(ExternalMessage::C2M_TEAM_JOIN::dwTargetRoleID) value) { self.dwTargetRoleID = value; });
    auto external_message_c2m_team_leave_type = cqyh::lua::usertype<ExternalMessage::C2M_TEAM_LEAVE>(L, external_message_namespace, "C2M_TEAM_LEAVE", "ExternalMessage::C2M_TEAM_LEAVE", sol::base_classes, sol::bases<ExternalMessage::MESSAGE_HEADER>());
    external_message_c2m_team_leave_type.set_function("new", [](sol::table) -> decltype(auto) { return new ExternalMessage::C2M_TEAM_LEAVE(); });
    external_message_c2m_team_leave_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<ExternalMessage::C2M_TEAM_LEAVE>(new ExternalMessage::C2M_TEAM_LEAVE()); });
    external_message_c2m_team_leave_type["dwLeaveRoleID"] = sol::property([](const ExternalMessage::C2M_TEAM_LEAVE& self) { return self.dwLeaveRoleID; }, [](ExternalMessage::C2M_TEAM_LEAVE& self, decltype(ExternalMessage::C2M_TEAM_LEAVE::dwLeaveRoleID) value) { self.dwLeaveRoleID = value; });
    auto external_message_c2m_team_answer_type = cqyh::lua::usertype<ExternalMessage::C2M_TEAM_ANSWER>(L, external_message_namespace, "C2M_TEAM_ANSWER", "ExternalMessage::C2M_TEAM_ANSWER", sol::base_classes, sol::bases<ExternalMessage::MESSAGE_HEADER>());
    external_message_c2m_team_answer_type.set_function("new", [](sol::table) -> decltype(auto) { return new ExternalMessage::C2M_TEAM_ANSWER(); });
    external_message_c2m_team_answer_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<ExternalMessage::C2M_TEAM_ANSWER>(new ExternalMessage::C2M_TEAM_ANSWER()); });
    external_message_c2m_team_answer_type["dwAnswerRequestRoleID"] = sol::property([](const ExternalMessage::C2M_TEAM_ANSWER& self) { return self.dwAnswerRequestRoleID; }, [](ExternalMessage::C2M_TEAM_ANSWER& self, decltype(ExternalMessage::C2M_TEAM_ANSWER::dwAnswerRequestRoleID) value) { self.dwAnswerRequestRoleID = value; });
    external_message_c2m_team_answer_type["byAnswerType"] = sol::property([](const ExternalMessage::C2M_TEAM_ANSWER& self) { return self.byAnswerType; }, [](ExternalMessage::C2M_TEAM_ANSWER& self, decltype(ExternalMessage::C2M_TEAM_ANSWER::byAnswerType) value) { self.byAnswerType = value; });
    external_message_c2m_team_answer_type["byAnswerResult"] = sol::property([](const ExternalMessage::C2M_TEAM_ANSWER& self) { return self.byAnswerResult; }, [](ExternalMessage::C2M_TEAM_ANSWER& self, decltype(ExternalMessage::C2M_TEAM_ANSWER::byAnswerResult) value) { self.byAnswerResult = value; });
    auto external_message_c2m_team_changeinfo_type = cqyh::lua::usertype<ExternalMessage::C2M_TEAM_CHANGEINFO>(L, external_message_namespace, "C2M_TEAM_CHANGEINFO", "ExternalMessage::C2M_TEAM_CHANGEINFO", sol::base_classes, sol::bases<ExternalMessage::MESSAGE_HEADER>());
    external_message_c2m_team_changeinfo_type.set_function("new", [](sol::table) -> decltype(auto) { return new ExternalMessage::C2M_TEAM_CHANGEINFO(); });
    external_message_c2m_team_changeinfo_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<ExternalMessage::C2M_TEAM_CHANGEINFO>(new ExternalMessage::C2M_TEAM_CHANGEINFO()); });
    external_message_c2m_team_changeinfo_type["nTeamMemberLimit"] = sol::property([](const ExternalMessage::C2M_TEAM_CHANGEINFO& self) { return self.nTeamMemberLimit; }, [](ExternalMessage::C2M_TEAM_CHANGEINFO& self, decltype(ExternalMessage::C2M_TEAM_CHANGEINFO::nTeamMemberLimit) value) { self.nTeamMemberLimit = value; });
    external_message_c2m_team_changeinfo_type["byAssignType"] = sol::property([](const ExternalMessage::C2M_TEAM_CHANGEINFO& self) { return self.byAssignType; }, [](ExternalMessage::C2M_TEAM_CHANGEINFO& self, decltype(ExternalMessage::C2M_TEAM_CHANGEINFO::byAssignType) value) { self.byAssignType = value; });
    external_message_c2m_team_changeinfo_type["byItemAuctionColorLimit"] = sol::property([](const ExternalMessage::C2M_TEAM_CHANGEINFO& self) { return self.byItemAuctionColorLimit; }, [](ExternalMessage::C2M_TEAM_CHANGEINFO& self, decltype(ExternalMessage::C2M_TEAM_CHANGEINFO::byItemAuctionColorLimit) value) { self.byItemAuctionColorLimit = value; });
    external_message_c2m_team_changeinfo_type["dwLeadID"] = sol::property([](const ExternalMessage::C2M_TEAM_CHANGEINFO& self) { return self.dwLeadID; }, [](ExternalMessage::C2M_TEAM_CHANGEINFO& self, decltype(ExternalMessage::C2M_TEAM_CHANGEINFO::dwLeadID) value) { self.dwLeadID = value; });
    external_message_c2m_team_changeinfo_type["szTeamName"] = cqyh::lua::string_property(&ExternalMessage::C2M_TEAM_CHANGEINFO::szTeamName);
}

}
