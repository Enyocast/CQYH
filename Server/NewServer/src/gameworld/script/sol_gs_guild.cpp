#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../inc/gameworld/gs_guild_data.h"
#include "../../inc/gameworld/role_guild_data.h"
#include "../../inc/gameworld/gs_guild.h"
#include "../../../inc/gameworld/asimov_guild.h"

int sol_gs_guild_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<GUILD_WAR_DATA>(L, globals, "GUILD_WAR_DATA", "GUILD_WAR_DATA");
    type1["dwIntruderID"] = sol::property([](const GUILD_WAR_DATA& self) { return self.dwIntruderID; }, [](GUILD_WAR_DATA& self, decltype(GUILD_WAR_DATA::dwIntruderID) value) { self.dwIntruderID = value; });
    type1["dwDefenderID"] = sol::property([](const GUILD_WAR_DATA& self) { return self.dwDefenderID; }, [](GUILD_WAR_DATA& self, decltype(GUILD_WAR_DATA::dwDefenderID) value) { self.dwDefenderID = value; });
    auto type2 = cqyh::lua::usertype<GS_G_B_DATA>(L, globals, "GS_G_B_DATA", "GS_G_B_DATA");
    type2.set_function("new", [](sol::table) -> decltype(auto) { return new GS_G_B_DATA(); });
    type2.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<GS_G_B_DATA>(new GS_G_B_DATA()); });
    type2.set_function("new", sol::overload([](sol::table, NAMEID qwID, signed int nT, signed int nL) -> decltype(auto) { return new GS_G_B_DATA(qwID,nT,nL); }, [](sol::table) -> decltype(auto) { return new GS_G_B_DATA(); }));
    type2.set_function("new_local", sol::overload([](sol::table, NAMEID qwID, signed int nT, signed int nL) -> decltype(auto) { return std::unique_ptr<GS_G_B_DATA>(new GS_G_B_DATA(qwID,nT,nL)); }, [](sol::table) -> decltype(auto) { return std::unique_ptr<GS_G_B_DATA>(new GS_G_B_DATA()); }));
    type2["qwNameID"] = &GS_G_B_DATA::qwNameID;
    type2["nType"] = sol::property([](const GS_G_B_DATA& self) { return self.nType; }, [](GS_G_B_DATA& self, decltype(GS_G_B_DATA::nType) value) { self.nType = value; });
    type2["nLevel"] = sol::property([](const GS_G_B_DATA& self) { return self.nLevel; }, [](GS_G_B_DATA& self, decltype(GS_G_B_DATA::nLevel) value) { self.nLevel = value; });
    type2["dwReviveTime"] = sol::property([](const GS_G_B_DATA& self) { return self.dwReviveTime; }, [](GS_G_B_DATA& self, decltype(GS_G_B_DATA::dwReviveTime) value) { self.dwReviveTime = value; });
    auto type3 = cqyh::lua::usertype<GS_GUILD_MEMBER>(L, globals, "GS_GUILD_MEMBER", "GS_GUILD_MEMBER");
    type3["dwRoleID"] = sol::property([](const GS_GUILD_MEMBER& self) { return self.dwRoleID; }, [](GS_GUILD_MEMBER& self, decltype(GS_GUILD_MEMBER::dwRoleID) value) { self.dwRoleID = value; });
    type3["nPosition"] = sol::property([](const GS_GUILD_MEMBER& self) { return self.nPosition; }, [](GS_GUILD_MEMBER& self, decltype(GS_GUILD_MEMBER::nPosition) value) { self.nPosition = value; });
    type3.set_function("new", [](sol::table) -> decltype(auto) { return new GS_GUILD_MEMBER(); });
    type3.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<GS_GUILD_MEMBER>(new GS_GUILD_MEMBER()); });
    type3.set_function("new", sol::overload([](sol::table, unsigned int dwID, signed int nP) -> decltype(auto) { return new GS_GUILD_MEMBER(dwID,nP); }, [](sol::table) -> decltype(auto) { return new GS_GUILD_MEMBER(); }));
    type3.set_function("new_local", sol::overload([](sol::table, unsigned int dwID, signed int nP) -> decltype(auto) { return std::unique_ptr<GS_GUILD_MEMBER>(new GS_GUILD_MEMBER(dwID,nP)); }, [](sol::table) -> decltype(auto) { return std::unique_ptr<GS_GUILD_MEMBER>(new GS_GUILD_MEMBER()); }));
    type3.set_function(".eq", [](GS_GUILD_MEMBER* self, unsigned int dwRoleID) -> decltype(auto) { return static_cast<bool>(self->operator==(dwRoleID)); });
    auto type4 = cqyh::lua::usertype<CRoleGuildData>(L, globals, "CRoleGuildData", "CRoleGuildData");
    type4.set_function("CalculateFundLimit", [](CRoleGuildData* self, signed int nPosition, signed int nMoney) -> decltype(auto) { return self->CalculateFundLimit(nPosition,nMoney); });
    type4.set_function("CalculateResLimit", [](CRoleGuildData* self, signed int nPosition, signed int nRes) -> decltype(auto) { return self->CalculateResLimit(nPosition,nRes); });
    auto type5 = cqyh::lua::usertype<CGSGuild>(L, globals, "CGSGuild", "CGSGuild");
    type5.set_function("GetID", [](CGSGuild* self) -> decltype(auto) { return self->GetID(); });
    type5.set_function("GetName", [](CGSGuild* self) -> decltype(auto) { return self->GetName(); });
    type5.set_function("GetState", [](CGSGuild* self) -> decltype(auto) { return self->GetState(); });
    type5.set_function("SetState", [](CGSGuild* self, signed int nState) -> decltype(auto) { self->SetState(nState); });
    type5.set_function("GetLeaderID", [](CGSGuild* self) -> decltype(auto) { return self->GetLeaderID(); });
    type5.set_function("SetLeaderID", [](CGSGuild* self, unsigned int dwRoleID) -> decltype(auto) { self->SetLeaderID(dwRoleID); });
    type5.set_function("GetMember", [](CGSGuild* self, unsigned int dwRoleID) -> decltype(auto) { return self->GetMember(dwRoleID); });
    type5.set_function("GetMaxMemberCount", [](CGSGuild* self) -> decltype(auto) { return self->GetMaxMemberCount(); });
    type5.set_function("AddMember", [](CGSGuild* self, unsigned int dwRoleID, signed int nPosition) -> decltype(auto) { return static_cast<bool>(self->AddMember(dwRoleID,nPosition)); });
    type5.set_function("DelMember", [](CGSGuild* self, unsigned int dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DelMember(dwRoleID)); });
    type5.set_function("IsMember", [](CGSGuild* self, unsigned int dwRoleID) -> decltype(auto) { return static_cast<bool>(self->IsMember(dwRoleID)); });
    type5.set_function("GetWelfareLevelByType", [](CGSGuild* self, signed int nType) -> decltype(auto) { return self->GetWelfareLevelByType(nType); });
    type5.set_function("SetWelfareLevelByType", [](CGSGuild* self, signed int nType, signed int nLevel) -> decltype(auto) { return static_cast<bool>(self->SetWelfareLevelByType(nType,nLevel)); });
    type5.set_function("IsActiveWelfareBuffer", [](CGSGuild* self, signed int nType) -> decltype(auto) { return static_cast<bool>(self->IsActiveWelfareBuffer(nType)); });
    type5.set_function("GetBuildingMaxLevelByType", [](CGSGuild* self, signed int nType) -> decltype(auto) { return self->GetBuildingMaxLevelByType(nType); });
    type5.set_function("GetBuildingDataByNpcID", [](CGSGuild* self, NAMEID qwNpcNameID) -> decltype(auto) { return self->GetBuildingDataByNpcID(qwNpcNameID); });
    type5.set_function("GetFunBuildingDataByType", [](CGSGuild* self, signed int nType) -> decltype(auto) { return self->GetFunBuildingDataByType(nType); });
    type5.set_function("FirstUnFunBuilding", [](CGSGuild* self) -> decltype(auto) { return self->FirstUnFunBuilding(); });
    type5.set_function("NextUnFunBuilding", [](CGSGuild* self) -> decltype(auto) { return self->NextUnFunBuilding(); });
    type5.set_function("FirstUpgradeBuilding", [](CGSGuild* self) -> decltype(auto) { return self->FirstUpgradeBuilding(); });
    type5.set_function("NextUpgradeBuilding", [](CGSGuild* self) -> decltype(auto) { return self->NextUpgradeBuilding(); });
    type5.set_function("IsBuildingEnable", [](CGSGuild* self, NAMEID qwNameID) -> decltype(auto) { return static_cast<bool>(self->IsBuildingEnable(qwNameID)); });
    type5.set_function("GetMoney", [](CGSGuild* self) -> decltype(auto) { return self->GetMoney(); });
    type5.set_function("GetHerb", [](CGSGuild* self) -> decltype(auto) { return self->GetHerb(); });
    type5.set_function("GetWood", [](CGSGuild* self) -> decltype(auto) { return self->GetWood(); });
    type5.set_function("GetCrystal", [](CGSGuild* self) -> decltype(auto) { return self->GetCrystal(); });
    type5.set_function("GetSilver", [](CGSGuild* self) -> decltype(auto) { return self->GetSilver(); });
    type5.set_function("GetRes", [](CGSGuild* self, signed int nResType) -> decltype(auto) { return self->GetRes(nResType); });
    type5.set_function("GetMaxRes", [](CGSGuild* self, signed int nResType) -> decltype(auto) { return self->GetMaxRes(nResType); });
    type5.set_function("GetMaxStorage", [](CGSGuild* self, signed int nType) -> decltype(auto) { return self->GetMaxStorage(nType); });
    type5.set_function("AddAlliance", [](CGSGuild* self, unsigned int dwTargetID) -> decltype(auto) { return static_cast<bool>(self->AddAlliance(dwTargetID)); });
    type5.set_function("DelAlliance", [](CGSGuild* self, unsigned int dwTargetID) -> decltype(auto) { return static_cast<bool>(self->DelAlliance(dwTargetID)); });
    type5.set_function("IsAlliance", [](CGSGuild* self, unsigned int dwTargetID) -> decltype(auto) { return static_cast<bool>(self->IsAlliance(dwTargetID)); });
    type5.set_function("AddEnemy", [](CGSGuild* self, unsigned int dwTargetID) -> decltype(auto) { return static_cast<bool>(self->AddEnemy(dwTargetID)); });
    type5.set_function("DelEnemy", [](CGSGuild* self, unsigned int dwTargetID) -> decltype(auto) { return static_cast<bool>(self->DelEnemy(dwTargetID)); });
    type5.set_function("IsEnemy", [](CGSGuild* self, unsigned int dwTargetID) -> decltype(auto) { return static_cast<bool>(self->IsEnemy(dwTargetID)); });
    type5.set_function("GetVariable", [](CGSGuild* self, signed int nIndex) -> decltype(auto) { return self->GetVariable(nIndex); });
    type5.set_function("IsActivityOpen", [](CGSGuild* self, signed int nActivityID) -> decltype(auto) { return static_cast<bool>(self->IsActivityOpen(nActivityID)); });
    type5.set_function("GetActivityMaxRepeatNum", [](CGSGuild* self, signed int nActivityID) -> decltype(auto) { return self->GetActivityMaxRepeatNum(nActivityID); });
    return 1;
}
