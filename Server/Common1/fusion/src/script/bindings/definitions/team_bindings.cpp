#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/team_def.h"

namespace cqyh::fusion::bindings {

void register_team_definitions(lua_State* L)
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
}

}
