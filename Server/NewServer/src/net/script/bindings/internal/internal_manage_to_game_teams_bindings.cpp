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

namespace cqyh::net::bindings {

void register_internal_manage_to_game_teams_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_team_member_content_type = cqyh::lua::usertype<InternalMessage::TEAM_MEMBER_CONTENT>(L, internal_message_namespace, "TEAM_MEMBER_CONTENT", "InternalMessage::TEAM_MEMBER_CONTENT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_team_member_content_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TEAM_MEMBER_CONTENT(); });
    internal_message_team_member_content_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TEAM_MEMBER_CONTENT>(new InternalMessage::TEAM_MEMBER_CONTENT()); });
    internal_message_team_member_content_type["dwMemberID"] = sol::property([](const InternalMessage::TEAM_MEMBER_CONTENT& self) { return self.dwMemberID; }, [](InternalMessage::TEAM_MEMBER_CONTENT& self, decltype(InternalMessage::TEAM_MEMBER_CONTENT::dwMemberID) value) { self.dwMemberID = value; });
    internal_message_team_member_content_type["szRoleName"] = cqyh::lua::array_property(&InternalMessage::TEAM_MEMBER_CONTENT::szRoleName);
    internal_message_team_member_content_type["btLevel"] = sol::property([](const InternalMessage::TEAM_MEMBER_CONTENT& self) { return self.btLevel; }, [](InternalMessage::TEAM_MEMBER_CONTENT& self, decltype(InternalMessage::TEAM_MEMBER_CONTENT::btLevel) value) { self.btLevel = value; });
    internal_message_team_member_content_type["btSex"] = sol::property([](const InternalMessage::TEAM_MEMBER_CONTENT& self) { return self.btSex; }, [](InternalMessage::TEAM_MEMBER_CONTENT& self, decltype(InternalMessage::TEAM_MEMBER_CONTENT::btSex) value) { self.btSex = value; });
    internal_message_team_member_content_type["btClass"] = sol::property([](const InternalMessage::TEAM_MEMBER_CONTENT& self) { return self.btClass; }, [](InternalMessage::TEAM_MEMBER_CONTENT& self, decltype(InternalMessage::TEAM_MEMBER_CONTENT::btClass) value) { self.btClass = value; });
    auto internal_message_m2g_team_new_type = cqyh::lua::usertype<InternalMessage::M2G_TEAM_NEW>(L, internal_message_namespace, "M2G_TEAM_NEW", "InternalMessage::M2G_TEAM_NEW", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_team_new_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_TEAM_NEW(); });
    internal_message_m2g_team_new_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_TEAM_NEW>(new InternalMessage::M2G_TEAM_NEW()); });
    internal_message_m2g_team_new_type["byGroupID"] = sol::property([](const InternalMessage::M2G_TEAM_NEW& self) { return self.byGroupID; }, [](InternalMessage::M2G_TEAM_NEW& self, decltype(InternalMessage::M2G_TEAM_NEW::byGroupID) value) { self.byGroupID = value; });
    internal_message_m2g_team_new_type["dwTeamID"] = sol::property([](const InternalMessage::M2G_TEAM_NEW& self) { return self.dwTeamID; }, [](InternalMessage::M2G_TEAM_NEW& self, decltype(InternalMessage::M2G_TEAM_NEW::dwTeamID) value) { self.dwTeamID = value; });
    internal_message_m2g_team_new_type["szTeamName"] = cqyh::lua::string_property(&InternalMessage::M2G_TEAM_NEW::szTeamName);
    internal_message_m2g_team_new_type["nMemberSizeLimit"] = sol::property([](const InternalMessage::M2G_TEAM_NEW& self) { return self.nMemberSizeLimit; }, [](InternalMessage::M2G_TEAM_NEW& self, decltype(InternalMessage::M2G_TEAM_NEW::nMemberSizeLimit) value) { self.nMemberSizeLimit = value; });
    internal_message_m2g_team_new_type["byAssignType"] = sol::property([](const InternalMessage::M2G_TEAM_NEW& self) { return self.byAssignType; }, [](InternalMessage::M2G_TEAM_NEW& self, decltype(InternalMessage::M2G_TEAM_NEW::byAssignType) value) { self.byAssignType = value; });
    internal_message_m2g_team_new_type["dwLeadID"] = sol::property([](const InternalMessage::M2G_TEAM_NEW& self) { return self.dwLeadID; }, [](InternalMessage::M2G_TEAM_NEW& self, decltype(InternalMessage::M2G_TEAM_NEW::dwLeadID) value) { self.dwLeadID = value; });
    internal_message_m2g_team_new_type["dwCreateTime"] = sol::property([](const InternalMessage::M2G_TEAM_NEW& self) { return self.dwCreateTime; }, [](InternalMessage::M2G_TEAM_NEW& self, decltype(InternalMessage::M2G_TEAM_NEW::dwCreateTime) value) { self.dwCreateTime = value; });
    internal_message_m2g_team_new_type["byCount"] = sol::property([](const InternalMessage::M2G_TEAM_NEW& self) { return self.byCount; }, [](InternalMessage::M2G_TEAM_NEW& self, decltype(InternalMessage::M2G_TEAM_NEW::byCount) value) { self.byCount = value; });
    internal_message_m2g_team_new_type["stTeamMemberList"] = cqyh::lua::array_property(&InternalMessage::M2G_TEAM_NEW::stTeamMemberList);
    auto internal_message_m2g_team_add_member_type = cqyh::lua::usertype<InternalMessage::M2G_TEAM_ADD_MEMBER>(L, internal_message_namespace, "M2G_TEAM_ADD_MEMBER", "InternalMessage::M2G_TEAM_ADD_MEMBER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_team_add_member_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_TEAM_ADD_MEMBER(); });
    internal_message_m2g_team_add_member_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_TEAM_ADD_MEMBER>(new InternalMessage::M2G_TEAM_ADD_MEMBER()); });
    internal_message_m2g_team_add_member_type["dwTeamID"] = sol::property([](const InternalMessage::M2G_TEAM_ADD_MEMBER& self) { return self.dwTeamID; }, [](InternalMessage::M2G_TEAM_ADD_MEMBER& self, decltype(InternalMessage::M2G_TEAM_ADD_MEMBER::dwTeamID) value) { self.dwTeamID = value; });
    internal_message_m2g_team_add_member_type["stMemberInfo"] = &InternalMessage::M2G_TEAM_ADD_MEMBER::stMemberInfo;
    auto internal_message_m2g_team_remove_member_type = cqyh::lua::usertype<InternalMessage::M2G_TEAM_REMOVE_MEMBER>(L, internal_message_namespace, "M2G_TEAM_REMOVE_MEMBER", "InternalMessage::M2G_TEAM_REMOVE_MEMBER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_team_remove_member_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_TEAM_REMOVE_MEMBER(); });
    internal_message_m2g_team_remove_member_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_TEAM_REMOVE_MEMBER>(new InternalMessage::M2G_TEAM_REMOVE_MEMBER()); });
    internal_message_m2g_team_remove_member_type["dwTeamID"] = sol::property([](const InternalMessage::M2G_TEAM_REMOVE_MEMBER& self) { return self.dwTeamID; }, [](InternalMessage::M2G_TEAM_REMOVE_MEMBER& self, decltype(InternalMessage::M2G_TEAM_REMOVE_MEMBER::dwTeamID) value) { self.dwTeamID = value; });
    internal_message_m2g_team_remove_member_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_TEAM_REMOVE_MEMBER& self) { return self.dwRoleID; }, [](InternalMessage::M2G_TEAM_REMOVE_MEMBER& self, decltype(InternalMessage::M2G_TEAM_REMOVE_MEMBER::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_m2g_team_changeinfo_type = cqyh::lua::usertype<InternalMessage::M2G_TEAM_CHANGEINFO>(L, internal_message_namespace, "M2G_TEAM_CHANGEINFO", "InternalMessage::M2G_TEAM_CHANGEINFO", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_team_changeinfo_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_TEAM_CHANGEINFO(); });
    internal_message_m2g_team_changeinfo_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_TEAM_CHANGEINFO>(new InternalMessage::M2G_TEAM_CHANGEINFO()); });
    internal_message_m2g_team_changeinfo_type["dwTeamID"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.dwTeamID; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::dwTeamID) value) { self.dwTeamID = value; });
    internal_message_m2g_team_changeinfo_type["szTeamName"] = cqyh::lua::string_property(&InternalMessage::M2G_TEAM_CHANGEINFO::szTeamName);
    internal_message_m2g_team_changeinfo_type["nTeamMemberLimit"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.nTeamMemberLimit; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::nTeamMemberLimit) value) { self.nTeamMemberLimit = value; });
    internal_message_m2g_team_changeinfo_type["byAssignType"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.byAssignType; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::byAssignType) value) { self.byAssignType = value; });
    internal_message_m2g_team_changeinfo_type["byAuctionItemColorLimit"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.byAuctionItemColorLimit; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::byAuctionItemColorLimit) value) { self.byAuctionItemColorLimit = value; });
    internal_message_m2g_team_changeinfo_type["dwLeadID"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.dwLeadID; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::dwLeadID) value) { self.dwLeadID = value; });
    internal_message_m2g_team_changeinfo_type["dwRoomID"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.dwRoomID; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::dwRoomID) value) { self.dwRoomID = value; });
    internal_message_m2g_team_changeinfo_type["dwActivityType"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.dwActivityType; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::dwActivityType) value) { self.dwActivityType = value; });
    internal_message_m2g_team_changeinfo_type["dwActivityID"] = sol::property([](const InternalMessage::M2G_TEAM_CHANGEINFO& self) { return self.dwActivityID; }, [](InternalMessage::M2G_TEAM_CHANGEINFO& self, decltype(InternalMessage::M2G_TEAM_CHANGEINFO::dwActivityID) value) { self.dwActivityID = value; });
}

}
