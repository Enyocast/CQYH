#include "stdafx.h"
#include "sol_bindings.h"
#include "../../../Common/define/guild_def.h"
#include "../../inc/gameworld/asimov_guild.h"

int sol_asimov_guild_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto member = cqyh::lua::usertype<ASIMOV_GUILD_MEMBER>(L, globals, "ASIMOV_GUILD_MEMBER", "ASIMOV_GUILD_MEMBER");
    member["dwRoleID"] = &ASIMOV_GUILD_MEMBER::dwRoleID;
    member["byPosition"] = &ASIMOV_GUILD_MEMBER::byPosition;
    member["byGuildFlag"] = &ASIMOV_GUILD_MEMBER::byGuildFlag;
    member["nSalary"] = &ASIMOV_GUILD_MEMBER::nSalary;
    member["dwDrawSalaryTime"] = &ASIMOV_GUILD_MEMBER::dwDrawSalaryTime;
    auto type = cqyh::lua::usertype<CGSGuild>(L, globals, "CGSGuild", "CGSGuild");
    type.set_function("GetID", [](CGSGuild* self) -> decltype(auto) { return self->GetID(); });
    type.set_function("GetState", [](CGSGuild* self) -> decltype(auto) { return self->GetState(); });
    type.set_function("SetState", [](CGSGuild* self, INT32 nState) -> decltype(auto) { self->SetState(nState); });
    type.set_function("GetLeaderID", [](CGSGuild* self) -> decltype(auto) { return self->GetLeaderID(); });
    type.set_function("SetLeaderID", [](CGSGuild* self, UINT32 dwRoleID) -> decltype(auto) { self->SetLeaderID(dwRoleID); });
    type.set_function("GetLevel", [](CGSGuild* self) -> decltype(auto) { return self->GetLevel(); });
    type.set_function("GetMoney", [](CGSGuild* self) -> decltype(auto) { return self->GetMoney(); });
    type.set_function("SetMoney", [](CGSGuild* self, INT32 nMoney) -> decltype(auto) { self->SetMoney(nMoney); });
    type.set_function("GetProsperity", [](CGSGuild* self) -> decltype(auto) { return self->GetProsperity(); });
    type.set_function("SetProsperity", [](CGSGuild* self, INT32 nProsperity) -> decltype(auto) { self->SetProsperity(nProsperity); });
    type.set_function("GetHerb", [](CGSGuild* self) -> decltype(auto) { return self->GetHerb(); });
    type.set_function("SetHerb", [](CGSGuild* self, INT32 nHerb) -> decltype(auto) { self->SetHerb(nHerb); });
    type.set_function("GetWood", [](CGSGuild* self) -> decltype(auto) { return self->GetWood(); });
    type.set_function("SetWood", [](CGSGuild* self, INT32 nWood) -> decltype(auto) { self->SetWood(nWood); });
    type.set_function("GetCrystal", [](CGSGuild* self) -> decltype(auto) { return self->GetCrystal(); });
    type.set_function("SetCrystal", [](CGSGuild* self, INT32 nCrystal) -> decltype(auto) { self->SetCrystal(nCrystal); });
    type.set_function("GetSilver", [](CGSGuild* self) -> decltype(auto) { return self->GetSilver(); });
    type.set_function("SetSilver", [](CGSGuild* self, INT32 nSilver) -> decltype(auto) { self->SetSilver(nSilver); });
    type.set_function("GetMemberCount", [](CGSGuild* self) -> decltype(auto) { return self->GetMemberCount(); });
    type.set_function("GetAllianceNum", [](CGSGuild* self) -> decltype(auto) { return self->GetAllianceNum(); });
    type.set_function("GetEnemyNum", [](CGSGuild* self) -> decltype(auto) { return self->GetEnemyNum(); });
    type.set_function("SetName", [](CGSGuild* self, const char* pcszName) -> decltype(auto) { return static_cast<bool>(self->SetName(pcszName)); });
    type.set_function("SetNotice", [](CGSGuild* self, const char * pcszNotice) -> decltype(auto) { return static_cast<bool>(self->SetNotice(pcszNotice)); });
    type.set_function("IsOfficeFull", [](CGSGuild* self, INT32 nPosition) -> decltype(auto) { return static_cast<bool>(self->IsOfficeFull(nPosition)); });
    type.set_function("AddMember", [](CGSGuild* self, UINT32 dwRoleID, UINT8 byPosition, UINT8 byFlag, INT32 nSalary) -> decltype(auto) { return static_cast<bool>(self->AddMember(dwRoleID, byPosition, byFlag, nSalary)); });
    type.set_function("DelMember", [](CGSGuild* self, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DelMember(dwRoleID)); });
    type.set_function("ChangeStorageRight", [](CGSGuild* self, INT32 nPosition, UINT16 wRight) -> decltype(auto) { return static_cast<bool>(self->ChangeStorageRight(nPosition, wRight)); });
    type.set_function("IsAlliance", [](CGSGuild* self, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->IsAlliance(dwGuildID)); });
    type.set_function("IsEnemy", [](CGSGuild* self, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->IsEnemy(dwGuildID)); });
    type.set_function("AddAlliance", [](CGSGuild* self, UINT32 dwGuildID, UINT32 dwEndTime) -> decltype(auto) { return static_cast<bool>(self->AddAlliance(dwGuildID, dwEndTime)); });
    type.set_function("DelAlliance", [](CGSGuild* self, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->DelAlliance(dwGuildID)); });
    type.set_function("AddEnemy", [](CGSGuild* self, UINT32 dwGuildID, UINT32 dwEndTime, bool bIsActive) -> decltype(auto) { return static_cast<bool>(self->AddEnemy(dwGuildID, dwEndTime, bIsActive)); });
    type.set_function("DelEnemy", [](CGSGuild* self, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->DelEnemy(dwGuildID)); });
    type.set_function("RandomApplyUnion", [](CGSGuild* self) -> decltype(auto) { return self->RandomApplyUnion(); });
    type.set_function("ClearApp", [](CGSGuild* self) -> decltype(auto) { return static_cast<bool>(self->ClearApp()); });
    type.set_function("AddApp", [](CGSGuild* self, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->AddApp(dwRoleID)); });
    type.set_function("AlreadyExistInAppList", [](CGSGuild* self, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->AlreadyExistInAppList(dwRoleID)); });
    type.set_function("GetAppNum", [](CGSGuild* self) -> decltype(auto) { return self->GetAppNum(); });
    type.set_function("GetRoleIDByIndexFromAppList", [](CGSGuild* self, INT32 nIndex) -> decltype(auto) { return self->GetRoleIDByIndexFromAppList(nIndex); });
    return 1;
}
