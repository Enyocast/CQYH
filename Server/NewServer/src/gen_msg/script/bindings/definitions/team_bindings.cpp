#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/scene_def.h"
#include "../../../../../../Common/define/team_def.h"

namespace cqyh::gen_msg::bindings {

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
    sol::table team_answer_type_namespace = globals["TEAM_ANSWER_TYPE"].get_or_create<sol::table>();
    team_answer_type_namespace["etatInvite"] = static_cast<lua_Number>(etatInvite);
    team_answer_type_namespace["etatEnter"] = static_cast<lua_Number>(etatEnter);
    sol::table team_answer_result_namespace = globals["TEAM_ANSWER_RESULT"].get_or_create<sol::table>();
    team_answer_result_namespace["etarAgree"] = static_cast<lua_Number>(etarAgree);
    team_answer_result_namespace["etarDisAgree"] = static_cast<lua_Number>(etarDisAgree);
    sol::table team_assign_namespace = globals["TEAM_ASSIGN"].get_or_create<sol::table>();
    team_assign_namespace["etaInvalid"] = static_cast<lua_Number>(etaInvalid);
    team_assign_namespace["etaFreeForAll"] = static_cast<lua_Number>(etaFreeForAll);
    team_assign_namespace["etaTeamAuction"] = static_cast<lua_Number>(etaTeamAuction);
    team_assign_namespace["etaLeaderPick"] = static_cast<lua_Number>(etaLeaderPick);
    team_assign_namespace["etaTotal"] = static_cast<lua_Number>(etaTotal);
    sol::table team_member_state_namespace = globals["TEAM_MEMBER_STATE"].get_or_create<sol::table>();
    team_member_state_namespace["etsOnline"] = static_cast<lua_Number>(etsOnline);
    team_member_state_namespace["etsOffline"] = static_cast<lua_Number>(etsOffline);
    sol::table team_activity_action_type_namespace = globals["TEAM_ACTIVITY_ACTION_TYPE"].get_or_create<sol::table>();
    team_activity_action_type_namespace["etaatInvalid"] = static_cast<lua_Number>(etaatInvalid);
    team_activity_action_type_namespace["etaatActivity"] = static_cast<lua_Number>(etaatActivity);
    team_activity_action_type_namespace["etaatDungeon"] = static_cast<lua_Number>(etaatDungeon);
    team_activity_action_type_namespace["etaatTotal"] = static_cast<lua_Number>(etaatTotal);
    sol::table team_bid_state_namespace = globals["TEAM_BID_STATE"].get_or_create<sol::table>();
    team_bid_state_namespace["etbsInvalid"] = static_cast<lua_Number>(etbsInvalid);
    team_bid_state_namespace["etbsBidding"] = static_cast<lua_Number>(etbsBidding);
    team_bid_state_namespace["etbsAbandon"] = static_cast<lua_Number>(etbsAbandon);
    team_bid_state_namespace["etbsTotal"] = static_cast<lua_Number>(etbsTotal);
    sol::table team_auction_action_namespace = globals["TEAM_AUCTION_ACTION"].get_or_create<sol::table>();
    team_auction_action_namespace["TAA_ADDITEM"] = static_cast<lua_Number>(TAA_ADDITEM);
    team_auction_action_namespace["TAA_START_AUCTION"] = static_cast<lua_Number>(TAA_START_AUCTION);
    team_auction_action_namespace["TAA_BID"] = static_cast<lua_Number>(TAA_BID);
    team_auction_action_namespace["TAA_ABANDON_SELF_REQUEST"] = static_cast<lua_Number>(TAA_ABANDON_SELF_REQUEST);
    team_auction_action_namespace["TAA_ABANDON_LEAVE_SCENE"] = static_cast<lua_Number>(TAA_ABANDON_LEAVE_SCENE);
    team_auction_action_namespace["TAA_REWARD_MONEY"] = static_cast<lua_Number>(TAA_REWARD_MONEY);
    team_auction_action_namespace["TAA_WIN_ITEM"] = static_cast<lua_Number>(TAA_WIN_ITEM);
    team_auction_action_namespace["TAA_LEADER_GOT_ITEM"] = static_cast<lua_Number>(TAA_LEADER_GOT_ITEM);
    team_auction_action_namespace["TAA_RETURN_DEPOSIT"] = static_cast<lua_Number>(TAA_RETURN_DEPOSIT);
    team_auction_action_namespace["TAA_FINISH_AUCTION"] = static_cast<lua_Number>(TAA_FINISH_AUCTION);
    team_auction_action_namespace["TAA_TOTAL"] = static_cast<lua_Number>(TAA_TOTAL);
    sol::table team_auction_money_reason_namespace = globals["TEAM_AUCTION_MONEY_REASON"].get_or_create<sol::table>();
    team_auction_money_reason_namespace["TAMR_NO_CHANGE"] = static_cast<lua_Number>(TAMR_NO_CHANGE);
    team_auction_money_reason_namespace["TAMR_OFFER_PRICE"] = static_cast<lua_Number>(TAMR_OFFER_PRICE);
    team_auction_money_reason_namespace["TAMR_ABANDON"] = static_cast<lua_Number>(TAMR_ABANDON);
    team_auction_money_reason_namespace["TAMR_REWARD"] = static_cast<lua_Number>(TAMR_REWARD);
    team_auction_money_reason_namespace["TAMR_RETURN_DEPOSITE"] = static_cast<lua_Number>(TAMR_RETURN_DEPOSITE);
}

}
