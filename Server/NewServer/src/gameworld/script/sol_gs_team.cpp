#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/team_def.h"
#include "../../inc/gameworld/team.h"

int sol_gs_team_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_TEAM_MEMBER_COUNT"] = static_cast<lua_Number>(MAX_TEAM_MEMBER_COUNT);
    globals["MAX_ADJACENT_ROLE_NOTEAM_COUNT"] = static_cast<lua_Number>(MAX_ADJACENT_ROLE_NOTEAM_COUNT);
    globals["MAX_ADJACENT_TEAM_COUNT"] = static_cast<lua_Number>(MAX_ADJACENT_TEAM_COUNT);
    globals["TEAM_SYNC_MEMBERINFO_TO_MS"] = static_cast<lua_Number>(TEAM_SYNC_MEMBERINFO_TO_MS);
    globals["TEAM_SYNC_MEMBERINFO_TO_CLIENT"] = static_cast<lua_Number>(TEAM_SYNC_MEMBERINFO_TO_CLIENT);
    globals["TEAM_SYNC_MEMBERINFO_STOP"] = static_cast<lua_Number>(TEAM_SYNC_MEMBERINFO_STOP);
    globals["MAX_TEAM_COUNT_PER_PAGE"] = static_cast<lua_Number>(MAX_TEAM_COUNT_PER_PAGE);
    globals["MAX_TEAM_PAGE_COUNT"] = static_cast<lua_Number>(MAX_TEAM_PAGE_COUNT);
    globals["MAX_TEAM_COUNT_PER_ACTIVITY"] = static_cast<lua_Number>(MAX_TEAM_COUNT_PER_ACTIVITY);
    globals["MAX_TEAM_ACTIVITY"] = static_cast<lua_Number>(MAX_TEAM_ACTIVITY);
    globals["MAX_TEAM_DUNGEON"] = static_cast<lua_Number>(MAX_TEAM_DUNGEON);
    globals["TEAM_AUCTION_BID_FRAME_INTERVAL"] = static_cast<lua_Number>(TEAM_AUCTION_BID_FRAME_INTERVAL);
    globals["TEAM_AUCTION_ITEM_INIT_INDEX"] = static_cast<lua_Number>(TEAM_AUCTION_ITEM_INIT_INDEX);
    globals["etatInvite"] = static_cast<lua_Number>(etatInvite);
    globals["etatEnter"] = static_cast<lua_Number>(etatEnter);
    globals["etarAgree"] = static_cast<lua_Number>(etarAgree);
    globals["etarDisAgree"] = static_cast<lua_Number>(etarDisAgree);
    globals["etaInvalid"] = static_cast<lua_Number>(etaInvalid);
    globals["etaFreeForAll"] = static_cast<lua_Number>(etaFreeForAll);
    globals["etaTeamAuction"] = static_cast<lua_Number>(etaTeamAuction);
    globals["etaLeaderPick"] = static_cast<lua_Number>(etaLeaderPick);
    globals["etaTotal"] = static_cast<lua_Number>(etaTotal);
    globals["etsOnline"] = static_cast<lua_Number>(etsOnline);
    globals["etsOffline"] = static_cast<lua_Number>(etsOffline);
    globals["etaatInvalid"] = static_cast<lua_Number>(etaatInvalid);
    globals["etaatActivity"] = static_cast<lua_Number>(etaatActivity);
    globals["etaatDungeon"] = static_cast<lua_Number>(etaatDungeon);
    globals["etaatTotal"] = static_cast<lua_Number>(etaatTotal);
    globals["etbsInvalid"] = static_cast<lua_Number>(etbsInvalid);
    globals["etbsBidding"] = static_cast<lua_Number>(etbsBidding);
    globals["etbsAbandon"] = static_cast<lua_Number>(etbsAbandon);
    globals["etbsTotal"] = static_cast<lua_Number>(etbsTotal);
    globals["TAA_ADDITEM"] = static_cast<lua_Number>(TAA_ADDITEM);
    globals["TAA_START_AUCTION"] = static_cast<lua_Number>(TAA_START_AUCTION);
    globals["TAA_BID"] = static_cast<lua_Number>(TAA_BID);
    globals["TAA_ABANDON_SELF_REQUEST"] = static_cast<lua_Number>(TAA_ABANDON_SELF_REQUEST);
    globals["TAA_ABANDON_LEAVE_SCENE"] = static_cast<lua_Number>(TAA_ABANDON_LEAVE_SCENE);
    globals["TAA_REWARD_MONEY"] = static_cast<lua_Number>(TAA_REWARD_MONEY);
    globals["TAA_WIN_ITEM"] = static_cast<lua_Number>(TAA_WIN_ITEM);
    globals["TAA_LEADER_GOT_ITEM"] = static_cast<lua_Number>(TAA_LEADER_GOT_ITEM);
    globals["TAA_RETURN_DEPOSIT"] = static_cast<lua_Number>(TAA_RETURN_DEPOSIT);
    globals["TAA_FINISH_AUCTION"] = static_cast<lua_Number>(TAA_FINISH_AUCTION);
    globals["TAA_TOTAL"] = static_cast<lua_Number>(TAA_TOTAL);
    globals["TAMR_NO_CHANGE"] = static_cast<lua_Number>(TAMR_NO_CHANGE);
    globals["TAMR_OFFER_PRICE"] = static_cast<lua_Number>(TAMR_OFFER_PRICE);
    globals["TAMR_ABANDON"] = static_cast<lua_Number>(TAMR_ABANDON);
    globals["TAMR_REWARD"] = static_cast<lua_Number>(TAMR_REWARD);
    globals["TAMR_RETURN_DEPOSITE"] = static_cast<lua_Number>(TAMR_RETURN_DEPOSITE);
    auto type1 = cqyh::lua::usertype<TeamMember>(L, globals, "TeamMember", "TeamMember");
    type1["szRoleName"] = cqyh::lua::string_property(&TeamMember::szRoleName);
    type1["dwRoleID"] = sol::property([](const TeamMember& self) { return self.dwRoleID; }, [](TeamMember& self, decltype(TeamMember::dwRoleID) value) { self.dwRoleID = value; });
    type1["nLevel"] = sol::property([](const TeamMember& self) { return self.nLevel; }, [](TeamMember& self, decltype(TeamMember::nLevel) value) { self.nLevel = value; });
    type1["nSex"] = sol::property([](const TeamMember& self) { return self.nSex; }, [](TeamMember& self, decltype(TeamMember::nSex) value) { self.nSex = value; });
    type1["nClass"] = sol::property([](const TeamMember& self) { return self.nClass; }, [](TeamMember& self, decltype(TeamMember::nClass) value) { self.nClass = value; });
    auto type2 = cqyh::lua::usertype<CTeamInGS>(L, globals, "CTeamInGS", "CTeamInGS");
    type2.set_function("GetLeaderID", [](CTeamInGS* self) -> decltype(auto) { return self->GetLeaderID(); });
    type2.set_function("SetLeaderID", [](CTeamInGS* self, unsigned int dwLeaderID) -> decltype(auto) { self->SetLeaderID(dwLeaderID); });
    type2.set_function("GetActivityType", [](CTeamInGS* self) -> decltype(auto) { return self->GetActivityType(); });
    type2.set_function("SetActivityType", [](CTeamInGS* self, unsigned int dwActivityType) -> decltype(auto) { self->SetActivityType(dwActivityType); });
    type2.set_function("GetActivityID", [](CTeamInGS* self) -> decltype(auto) { return self->GetActivityID(); });
    type2.set_function("SetActivityID", [](CTeamInGS* self, unsigned int dwActivityID) -> decltype(auto) { self->SetActivityID(dwActivityID); });
    type2.set_function("GetAuctionItemColorLimit", [](CTeamInGS* self) -> decltype(auto) { return self->GetAuctionItemColorLimit(); });
    type2.set_function("SetAuctionItemColorLimit", [](CTeamInGS* self, signed int nAuctionItemColorLimit) -> decltype(auto) { self->SetAuctionItemColorLimit(nAuctionItemColorLimit); });
    type2.set_function("GetTeamName", [](CTeamInGS* self) -> decltype(auto) { return self->GetTeamName(); });
    type2.set_function("AddNewMember", [](CTeamInGS* self, unsigned int dwMemberID, const char* szRoleName_arg, signed int nLevel, signed int nSex, signed int nClass) -> decltype(auto) { char* szRoleName = const_cast<char*>(szRoleName_arg); return static_cast<bool>(self->AddNewMember(dwMemberID,szRoleName,nLevel,nSex,nClass)); });
    type2.set_function("RemoveMember", [](CTeamInGS* self, unsigned int dwMemberID) -> decltype(auto) { return static_cast<bool>(self->RemoveMember(dwMemberID)); });
    type2.set_function("GetMaxMemberCount", [](CTeamInGS* self) -> decltype(auto) { return self->GetMaxMemberCount(); });
    type2.set_function("SetMaxMemberCount", [](CTeamInGS* self, unsigned int dwMaxMemberCount) -> decltype(auto) { self->SetMaxMemberCount(dwMaxMemberCount); });
    type2.set_function("GetMemberCount", [](CTeamInGS* self) -> decltype(auto) { return self->GetMemberCount(); });
    type2.set_function("SetMemberCount", [](CTeamInGS* self, unsigned int dwMemberCount) -> decltype(auto) { self->SetMemberCount(dwMemberCount); });
    type2.set_function("GetCreateTime", [](CTeamInGS* self) -> decltype(auto) { return self->GetCreateTime(); });
    type2.set_function("SetCreateTime", [](CTeamInGS* self, unsigned int dwCreateTime) -> decltype(auto) { self->SetCreateTime(dwCreateTime); });
    type2.set_function("GetMemberTable", [](CTeamInGS* self, signed int nIndex) -> decltype(auto) { return self->GetMemberTable(nIndex); });
    return 1;
}
