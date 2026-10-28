#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/arena_def.h"
#include "../../inc/gameworld/arena.h"

int sol_arena_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["ARENA_REWARD_COUNT"] = static_cast<lua_Number>(ARENA_REWARD_COUNT);
    globals["ARENA_FIRST_WAIT_TIME"] = static_cast<lua_Number>(ARENA_FIRST_WAIT_TIME);
    globals["ARENA_WEEKLY_DAY_ONE"] = static_cast<lua_Number>(ARENA_WEEKLY_DAY_ONE);
    globals["ARENA_WEEKLY_DAY_TWO"] = static_cast<lua_Number>(ARENA_WEEKLY_DAY_TWO);
    globals["ARENA_WEEKLY_DAY_THREE"] = static_cast<lua_Number>(ARENA_WEEKLY_DAY_THREE);
    globals["ARENA_APPLY_HOUR_BEGIN"] = static_cast<lua_Number>(ARENA_APPLY_HOUR_BEGIN);
    globals["ARENA_APPLY_HOUR_END"] = static_cast<lua_Number>(ARENA_APPLY_HOUR_END);
    globals["ARENA_MATCH_HOUR_BEGIN"] = static_cast<lua_Number>(ARENA_MATCH_HOUR_BEGIN);
    globals["ARENA_MATCH_HOUR_END"] = static_cast<lua_Number>(ARENA_MATCH_HOUR_END);
    globals["ARENA_GET_REWARD_MINUTE"] = static_cast<lua_Number>(ARENA_GET_REWARD_MINUTE);
    globals["ARENA_MAX_SEASON_NUM"] = static_cast<lua_Number>(ARENA_MAX_SEASON_NUM);
    globals["ARENA_JOIN_SEASON_MONEY_CONSUMPTION"] = static_cast<lua_Number>(ARENA_JOIN_SEASON_MONEY_CONSUMPTION);
    globals["ARENA_JOIN_SEASON_LVL_LIMIT"] = static_cast<lua_Number>(ARENA_JOIN_SEASON_LVL_LIMIT);
    globals["ARENA_SPECIAL_REWARD_RANK_LIMIT"] = static_cast<lua_Number>(ARENA_SPECIAL_REWARD_RANK_LIMIT);
    globals["ARENA_SPECIAL_REWARD_PERCENT"] = static_cast<lua_Number>(ARENA_SPECIAL_REWARD_PERCENT);
    globals["ARENA_FIRST_REWARD_RANK_LIMIT"] = static_cast<lua_Number>(ARENA_FIRST_REWARD_RANK_LIMIT);
    globals["ARENA_FIRST_REWARD_PERCENT"] = static_cast<lua_Number>(ARENA_FIRST_REWARD_PERCENT);
    globals["ARENA_SECOND_REWARD_RANK_LIMIT"] = static_cast<lua_Number>(ARENA_SECOND_REWARD_RANK_LIMIT);
    globals["ARENA_SECOND_REWARD_PERCENT"] = static_cast<lua_Number>(ARENA_SECOND_REWARD_PERCENT);
    globals["ARENA_THIRD_REWARD_RANK_LIMIT"] = static_cast<lua_Number>(ARENA_THIRD_REWARD_RANK_LIMIT);
    globals["ARENA_THIRD_REWARD_PERCENT"] = static_cast<lua_Number>(ARENA_THIRD_REWARD_PERCENT);
    globals["MAX_ARENA_RANK_NUM"] = static_cast<lua_Number>(MAX_ARENA_RANK_NUM);
    globals["MAX_ARENA_MATCH_NUM"] = static_cast<lua_Number>(MAX_ARENA_MATCH_NUM);
    globals["ARENA_MATCH_WAIT_TIME"] = static_cast<lua_Number>(ARENA_MATCH_WAIT_TIME);
    globals["ARENA_WEEK_SECOND"] = static_cast<lua_Number>(ARENA_WEEK_SECOND);
    globals["ARENA_TUESDAY_SETTLE_TIME"] = static_cast<lua_Number>(ARENA_TUESDAY_SETTLE_TIME);
    globals["ARENA_THURSDAY_SETTLE_TIME"] = static_cast<lua_Number>(ARENA_THURSDAY_SETTLE_TIME);
    globals["ARENA_SATURDAY_SETTLE_TIME"] = static_cast<lua_Number>(ARENA_SATURDAY_SETTLE_TIME);
    globals["AMVI_JJC_BEGIN_TIME"] = static_cast<lua_Number>(AMVI_JJC_BEGIN_TIME);
    globals["AMVI_JJC_END_TIME"] = static_cast<lua_Number>(AMVI_JJC_END_TIME);
    globals["AMVI_JJC_STATUS"] = static_cast<lua_Number>(AMVI_JJC_STATUS);
    globals["AMVI_JJC_ROLE_NUM"] = static_cast<lua_Number>(AMVI_JJC_ROLE_NUM);
    globals["AMVI_JJC_ROLE_ID_1"] = static_cast<lua_Number>(AMVI_JJC_ROLE_ID_1);
    globals["AMVI_JJC_ROLE_ID_2"] = static_cast<lua_Number>(AMVI_JJC_ROLE_ID_2);
    globals["AMVI_JJC_POTION_STAT_1"] = static_cast<lua_Number>(AMVI_JJC_POTION_STAT_1);
    globals["AMVI_JJC_POTION_STAT_2"] = static_cast<lua_Number>(AMVI_JJC_POTION_STAT_2);
    globals["ARENA_STAT_NONE"] = static_cast<lua_Number>(ARENA_STAT_NONE);
    globals["ARENA_STAT_WAIT"] = static_cast<lua_Number>(ARENA_STAT_WAIT);
    globals["ARENA_STAT_READY"] = static_cast<lua_Number>(ARENA_STAT_READY);
    globals["ARENA_STAT_FIGHT"] = static_cast<lua_Number>(ARENA_STAT_FIGHT);
    globals["ARENA_STAT_END"] = static_cast<lua_Number>(ARENA_STAT_END);
    globals["ARENA_STAT_CLEAR"] = static_cast<lua_Number>(ARENA_STAT_CLEAR);
    globals["avArenaFundLow"] = static_cast<lua_Number>(avArenaFundLow);
    globals["avArenaFundHigh"] = static_cast<lua_Number>(avArenaFundHigh);
    globals["avArenaTicketRewardLow"] = static_cast<lua_Number>(avArenaTicketRewardLow);
    globals["avArenaTicketRewardHigh"] = static_cast<lua_Number>(avArenaTicketRewardHigh);
    globals["avArenaSystemFollowNum"] = static_cast<lua_Number>(avArenaSystemFollowNum);
    globals["avArenaTicketsCount"] = static_cast<lua_Number>(avArenaTicketsCount);
    globals["avArenaCanOpen"] = static_cast<lua_Number>(avArenaCanOpen);
    globals["avArenaOpenTime"] = static_cast<lua_Number>(avArenaOpenTime);
    globals["avArenaIsOpen"] = static_cast<lua_Number>(avArenaIsOpen);
    globals["avArenaRewardCanOpen"] = static_cast<lua_Number>(avArenaRewardCanOpen);
    globals["avArenaRewardIsOpen"] = static_cast<lua_Number>(avArenaRewardIsOpen);
    globals["FIRST_ARENA_MATCH"] = static_cast<lua_Number>(FIRST_ARENA_MATCH);
    globals["SECOND_ARENA_MATCH"] = static_cast<lua_Number>(SECOND_ARENA_MATCH);
    globals["THIRD_ARENA_MATCH"] = static_cast<lua_Number>(THIRD_ARENA_MATCH);
    globals["FOURTH_ARENA_MATCH"] = static_cast<lua_Number>(FOURTH_ARENA_MATCH);
    globals["ARENA_MATCH_COUNT"] = static_cast<lua_Number>(ARENA_MATCH_COUNT);
    globals["ARENA_RES_WIN"] = static_cast<lua_Number>(ARENA_RES_WIN);
    globals["ARENA_RES_DEFEAT"] = static_cast<lua_Number>(ARENA_RES_DEFEAT);
    globals["ARENA_RES_TIE"] = static_cast<lua_Number>(ARENA_RES_TIE);
    auto type1 = cqyh::lua::usertype<ARENA_RANK_DATA>(L, globals, "ARENA_RANK_DATA", "ARENA_RANK_DATA");
    type1["dwRoleID"] = sol::property([](const ARENA_RANK_DATA& self) { return self.dwRoleID; }, [](ARENA_RANK_DATA& self, decltype(ARENA_RANK_DATA::dwRoleID) value) { self.dwRoleID = value; });
    type1["byPointSeasonVictoryTimes"] = sol::property([](const ARENA_RANK_DATA& self) { return self.byPointSeasonVictoryTimes; }, [](ARENA_RANK_DATA& self, decltype(ARENA_RANK_DATA::byPointSeasonVictoryTimes) value) { self.byPointSeasonVictoryTimes = value; });
    type1["nPointSeasonEndTime"] = sol::property([](const ARENA_RANK_DATA& self) { return self.nPointSeasonEndTime; }, [](ARENA_RANK_DATA& self, decltype(ARENA_RANK_DATA::nPointSeasonEndTime) value) { self.nPointSeasonEndTime = value; });
    auto type2 = cqyh::lua::usertype<ARENA_DB_DATA>(L, globals, "ARENA_DB_DATA", "ARENA_DB_DATA");
    type2["rankData"] = cqyh::lua::array_property(&ARENA_DB_DATA::rankData);
    auto type3 = cqyh::lua::usertype<CArena>(L, globals, "CArena", "CArena");
    type3.set_function("IsInSeason", [](CArena* self) -> decltype(auto) { return static_cast<bool>(self->IsInSeason()); });
    type3.set_function("JoinNewSeason", [](CArena* self) -> decltype(auto) { return static_cast<bool>(self->JoinNewSeason()); });
    type3.set_function("QuitSeason", [](CArena* self) -> decltype(auto) { return static_cast<bool>(self->QuitSeason()); });
    type3.set_function("GetSeasonNum", [](CArena* self) -> decltype(auto) { return self->GetSeasonNum(); });
    type3.set_function("CanGetCommonReward", [](CArena* self) -> decltype(auto) { return static_cast<bool>(self->CanGetCommonReward()); });
    type3.set_function("GetCommonReward", [](CArena* self, unsigned int dwItemID, signed int nMoney) -> decltype(auto) { return static_cast<bool>(self->GetCommonReward(dwItemID,nMoney)); });
    type3.set_function("Win", [](CArena* self) -> decltype(auto) { return static_cast<bool>(self->Win()); });
    type3.set_function("Defeated", [](CArena* self) -> decltype(auto) { return static_cast<bool>(self->Defeated()); });
    type3.set_function("GetHP", [](CArena* self) -> decltype(auto) { return self->GetHP(); });
    type3.set_function("SetHP", [](CArena* self, signed int nHp) -> decltype(auto) { self->SetHP(nHp); });
    return 1;
}
