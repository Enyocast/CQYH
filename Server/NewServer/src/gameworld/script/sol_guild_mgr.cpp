#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "guild_mgr.h"
#include "gs_guild.h"
#include "asimov_guild.h"
#include "../../../inc/gameworld/gs_guild_data.h"

int sol_guild_mgr_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CGuildMgr>(L, globals, "CGuildMgr", "CGuildMgr");
    type1.set_function("GetInstance", []() -> decltype(auto) { return CGuildMgr::GetInstance(); });
    type1.set_function("FindGuild", [](CGuildMgr* self, unsigned int dwGuildID) -> decltype(auto) { return self->FindGuild(dwGuildID); });
    type1.set_function("AddWarRelation", [](CGuildMgr* self, unsigned int dwIntruderID, unsigned int dwDefenderID) -> decltype(auto) { return static_cast<bool>(self->AddWarRelation(dwIntruderID,dwDefenderID)); });
    type1.set_function("FindWarRelation", [](CGuildMgr* self, unsigned int dwIntruderID, unsigned int dwDefenderID) -> decltype(auto) { return self->FindWarRelation(dwIntruderID,dwDefenderID); });
    type1.set_function("FindWarByAttackGuildID", [](CGuildMgr* self, unsigned int dwIntruderID) -> decltype(auto) { return self->FindWarByAttackGuildID(dwIntruderID); });
    type1.set_function("FindWarByDefendGuildID", [](CGuildMgr* self, unsigned int dwDefenderID) -> decltype(auto) { return self->FindWarByDefendGuildID(dwDefenderID); });
    type1.set_function("DelWarRelation", [](CGuildMgr* self, unsigned int dwIntruderID, unsigned int dwDefenderID) -> decltype(auto) { return static_cast<bool>(self->DelWarRelation(dwIntruderID,dwDefenderID)); });
    type1.set_function("IsHostile", [](CGuildMgr* self, unsigned int dwGuildID, unsigned int dwTargetGuildID) -> decltype(auto) { return static_cast<bool>(self->IsHostile(dwGuildID,dwTargetGuildID)); });
    type1.set_function("IsFriendly", [](CGuildMgr* self, unsigned int dwGuildID, unsigned int dwTargetGuildID) -> decltype(auto) { return static_cast<bool>(self->IsFriendly(dwGuildID,dwTargetGuildID)); });
    globals.set_function("SendMSToAddRes", [](unsigned int dwRoleID, signed int nType, signed int nCount) -> decltype(auto) { return static_cast<bool>(SendMSToAddRes(dwRoleID,nType,nCount)); });
    return 1;
}
