#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "./guild/ms_guild_mgr.h"
#include "./guild/ms_guild.h"
#include "./guild/ms_guild_mgr.h"
#include "../onlinerole/online_role_data.h"

int sol_ms_guild_mgr_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CMsGuildMgr>(L, globals, "CMsGuildMgr", "CMsGuildMgr");
    type1.set_function("GetInstance", []() -> decltype(auto) { return CMsGuildMgr::GetInstance(); });
    type1.set_function("PreCreateGuild", [](CMsGuildMgr* self, unsigned int dwNewGuildID, MS_ONLINE_ROLE_DATA* onlineRoleData, const char* pcszGuildName, const char* pcszAnnounce, signed int nIsNeedToConsume) -> decltype(auto) { return static_cast<bool>(self->PreCreateGuild(dwNewGuildID,*onlineRoleData,pcszGuildName,pcszAnnounce,nIsNeedToConsume)); });
    type1.set_function("FindGuildByID", [](CMsGuildMgr* self, unsigned int dwGuildID) -> decltype(auto) { return self->FindGuildByID(dwGuildID); });
    type1.set_function("FindGuildByName", [](CMsGuildMgr* self, const char* pcszGuildName) -> decltype(auto) { return self->FindGuildByName(pcszGuildName); });
    type1.set_function("InsertGuildIntoLvlRank", [](CMsGuildMgr* self, CMsGuild* pMsGuild) -> decltype(auto) { return static_cast<bool>(self->InsertGuildIntoLvlRank(pMsGuild)); });
    type1.set_function("RemoveGuildFromLvlRank", [](CMsGuildMgr* self, CMsGuild* pMsGuild) -> decltype(auto) { return static_cast<bool>(self->RemoveGuildFromLvlRank(pMsGuild)); });
    type1.set_function("DestroyGuild", [](CMsGuildMgr* self, CMsGuild* pMsGuild) -> decltype(auto) { return static_cast<bool>(self->DestroyGuild(pMsGuild)); });
    type1.set_function("ClearWarData", [](CMsGuildMgr* self) -> decltype(auto) { return static_cast<bool>(self->ClearWarData()); });
    type1.set_function("FirstWarData", [](CMsGuildMgr* self) -> decltype(auto) { return self->FirstWarData(); });
    type1.set_function("NextWarData", [](CMsGuildMgr* self) -> decltype(auto) { return self->NextWarData(); });
    type1.set_function("GetFirstGuildOnLvlRank", [](CMsGuildMgr* self) -> decltype(auto) { return self->GetFirstGuildOnLvlRank(); });
    type1.set_function("GetNextGuildOnLvlRank", [](CMsGuildMgr* self, CMsGuild* pMsGuild) -> decltype(auto) { return self->GetNextGuildOnLvlRank(pMsGuild); });
    type1.set_function("GetPrevGuildOnLvlRank", [](CMsGuildMgr* self, CMsGuild* pMsGuild) -> decltype(auto) { return self->GetPrevGuildOnLvlRank(pMsGuild); });
    type1.set_function("DelAlliance", [](CMsGuildMgr* self, signed int dwGuildID, signed int dwAllianceID) -> decltype(auto) { return static_cast<bool>(self->DelAlliance(dwGuildID,dwAllianceID)); });
    type1.set_function("DelEnemy", [](CMsGuildMgr* self, signed int dwGuildID, signed int dwEnemyID) -> decltype(auto) { return static_cast<bool>(self->DelEnemy(dwGuildID,dwEnemyID)); });
    globals.set_function("GuildWarEnd", [](unsigned int dwDefenderID, signed int nWarDefenderResult) -> decltype(auto) { return static_cast<bool>(GuildWarEnd(dwDefenderID,nWarDefenderResult)); });
    globals.set_function("GuildSyncWarRelation", [](unsigned int dwIntruderID, unsigned int dwDefenderID) -> decltype(auto) { return static_cast<bool>(GuildSyncWarRelation(dwIntruderID,dwDefenderID)); });
    globals.set_function("GuildSyncResChange", [](unsigned int dwNpcID, unsigned int dwGuildID, bool bAdd, signed int nResType, signed int nChangeCount, signed int nCtxType) -> decltype(auto) { return static_cast<bool>(GuildSyncResChange(dwNpcID,dwGuildID,bAdd,nResType,nChangeCount,nCtxType)); });
    return 1;
}
