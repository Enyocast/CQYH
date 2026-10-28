#include "stdafx.h"
#include "sol_bindings.h"
#include "robot_message_handler.h"
#include "role.h"
#include "character.h"

int sol_robot_message_handler_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type = cqyh::lua::usertype<CRobotMessageHandler>(L, globals, "CRobotMessageHandler", "CRobotMessageHandler");
    type.set_function("GetInstance", []() -> decltype(auto) { return CRobotMessageHandler::GetInstance(); });
    type.set_function("SetTradeTendency", [](CRobotMessageHandler* self, INT32 nSuccTradeTendency) -> decltype(auto) { self->SetTradeTendency(nSuccTradeTendency); });
    type.set_function("DoTradeAsk", [](CRobotMessageHandler* self, CRole* pRole, UINT32 dwTargetRoleID) -> decltype(auto) { return static_cast<bool>(self->DoTradeAsk(pRole, dwTargetRoleID)); });
    type.set_function("DoTradeAccept", [](CRobotMessageHandler* self, CRole* pRole, UINT32 dwTargetRoleID) -> decltype(auto) { return static_cast<bool>(self->DoTradeAccept(pRole, dwTargetRoleID)); });
    type.set_function("DoTradeSetMoney", [](CRobotMessageHandler* self, CRole* pRole, INT32 nMoneyCount) -> decltype(auto) { return static_cast<bool>(self->DoTradeSetMoney(pRole, nMoneyCount)); });
    type.set_function("DoTradeSetItem", [](CRobotMessageHandler* self, CRole* pRole, UINT8 bAdd, UINT8 byTradeSlot, UINT8 byConSlot, UINT8 byItemSlot) -> decltype(auto) { return static_cast<bool>(self->DoTradeSetItem(pRole, bAdd, byTradeSlot, byConSlot, byItemSlot)); });
    type.set_function("DoTradeLock", [](CRobotMessageHandler* self, CRole* pRole) -> decltype(auto) { return static_cast<bool>(self->DoTradeLock(pRole)); });
    type.set_function("DoTradeUnlock", [](CRobotMessageHandler* self, CRole* pRole) -> decltype(auto) { return static_cast<bool>(self->DoTradeUnlock(pRole)); });
    type.set_function("DoTradeConfirm", [](CRobotMessageHandler* self, CRole* pRole) -> decltype(auto) { return static_cast<bool>(self->DoTradeConfirm(pRole)); });
    type.set_function("DoTradeCancel", [](CRobotMessageHandler* self, CRole* pRole) -> decltype(auto) { return static_cast<bool>(self->DoTradeCancel(pRole)); });
    type.set_function("SetTeamAuto", [](CRobotMessageHandler* self, bool bAuto) -> decltype(auto) { self->SetTeamAuto(bAuto); });
    type.set_function("DoTeamJoinRand", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoTeamJoinRand(poRole)); });
    type.set_function("DoTeamJoin", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwTargetRoleID) -> decltype(auto) { return static_cast<bool>(self->DoTeamJoin(poRole, dwTargetRoleID)); });
    type.set_function("DoTeamLeave", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwLeaveRoleID) -> decltype(auto) { return static_cast<bool>(self->DoTeamLeave(poRole, dwLeaveRoleID)); });
    type.set_function("DoTeamAnswer", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwAnswerReqRoleID, UINT8 byType, UINT8 byAnswerResult) -> decltype(auto) { return static_cast<bool>(self->DoTeamAnswer(poRole, dwAnswerReqRoleID, byType, byAnswerResult)); });
    type.set_function("DoTeamChangeInfo", [](CRobotMessageHandler* self, CRole* poRole, INT32 nTeamMemberLimit, UINT8 byAssignType, UINT8 dwLeadID, UINT8 byAuctionItemColorLimit) -> decltype(auto) { return static_cast<bool>(self->DoTeamChangeInfo(poRole, nTeamMemberLimit, byAssignType, dwLeadID, byAuctionItemColorLimit)); });
    type.set_function("DoAdjacentNoTeamRole", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoAdjacentNoTeamRole(poRole)); });
    type.set_function("DoAdjacentTeam", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoAdjacentTeam(poRole)); });
    type.set_function("DoTeamChangeActivityInfo", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwActivityType, INT32 nActivityID) -> decltype(auto) { return static_cast<bool>(self->DoTeamChangeActivityInfo(poRole, dwActivityType, nActivityID)); });
    type.set_function("DoTeamQueryActivityTeam", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwActivityType, INT32 nActivityID, INT32 nPgae) -> decltype(auto) { return static_cast<bool>(self->DoTeamQueryActivityTeam(poRole, dwActivityType, nActivityID, nPgae)); });
    type.set_function("DoTeamRemoveActivityTeam", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoTeamRemoveActivityTeam(poRole)); });
    type.set_function("DoSelectFocus", [](CRobotMessageHandler* self, CRole* poRole, INT32 nFocusID) -> decltype(auto) { return static_cast<bool>(self->DoSelectFocus(poRole, nFocusID)); });
    type.set_function("DoCastSpell", [](CRobotMessageHandler* self, CRole* poRole, INT32 nSpellID, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ) -> decltype(auto) { return static_cast<bool>(self->DoCastSpell(poRole, nSpellID, poTarget, nTargetX, nTargetY, nTargetZ)); });
    type.set_function("DoReplayDungeon", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoReplayDungeon(poRole)); });
    type.set_function("DoSelectReward", [](CRobotMessageHandler* self, CRole* poRole, INT32 nType) -> decltype(auto) { return static_cast<bool>(self->DoSelectReward(poRole, nType)); });
    type.set_function("DoQueryLineReq", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoQueryLineReq(poRole)); });
    type.set_function("DoChangeLine", [](CRobotMessageHandler* self, CRole* poRole, UINT8 byLineIndex) -> decltype(auto) { return static_cast<bool>(self->DoChangeLine(poRole, byLineIndex)); });
    type.set_function("DoMstGetRecruit", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoMstGetRecruit(poRole)); });
    type.set_function("DoMstGetSoloList", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoMstGetSoloList(poRole)); });
    type.set_function("DoMstSubmitStudApp", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwTeacherID) -> decltype(auto) { return static_cast<bool>(self->DoMstSubmitStudApp(poRole, dwTeacherID)); });
    type.set_function("DoGuildCreate", [](CRobotMessageHandler* self, CRole * poRole, const char* guild_name_arg, const char* announce_arg) -> decltype(auto) { char* guild_name = const_cast<char*>(guild_name_arg); char* announce = const_cast<char*>(announce_arg); return static_cast<bool>(self->DoGuildCreate(poRole, guild_name, announce)); });
    type.set_function("DoGuildView", [](CRobotMessageHandler* self, CRole * poRole, UINT32 lastGuildID) -> decltype(auto) { return static_cast<bool>(self->DoGuildView(poRole, lastGuildID)); });
    type.set_function("DoFindGuild", [](CRobotMessageHandler* self, CRole * poRole, const char* guild_name_arg) -> decltype(auto) { char* guild_name = const_cast<char*>(guild_name_arg); return static_cast<bool>(self->DoFindGuild(poRole, guild_name)); });
    type.set_function("DoGuildApplyToJoinGuild", [](CRobotMessageHandler* self, CRole * poRole, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->DoGuildApplyToJoinGuild(poRole, dwGuildID)); });
    type.set_function("DoGetApplyGuildList", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoGetApplyGuildList(poRole)); });
    type.set_function("DoGetRevertGuildApp", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byRevertType, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoGetRevertGuildApp(poRole, byRevertType, dwRoleID)); });
    type.set_function("DoInviteToJointGuild", [](CRobotMessageHandler* self, CRole * poRole, const char* szRoleName_arg) -> decltype(auto) { char* szRoleName = const_cast<char*>(szRoleName_arg); return static_cast<bool>(self->DoInviteToJointGuild(poRole, szRoleName)); });
    type.set_function("DoRevertTheInvitation", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byRevertType, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoRevertTheInvitation(poRole, byRevertType, dwRoleID)); });
    type.set_function("DoDisbandGuild", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoDisbandGuild(poRole)); });
    type.set_function("DoGuildChangeNotice", [](CRobotMessageHandler* self, CRole * poRole, const char* pNotice_arg) -> decltype(auto) { char* pNotice = const_cast<char*>(pNotice_arg); return static_cast<bool>(self->DoGuildChangeNotice(poRole, pNotice)); });
    type.set_function("DoGuildForbidChat", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byOp, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoGuildForbidChat(poRole, byOp, dwRoleID)); });
    type.set_function("DoGuildChangePosition", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byPosition, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoGuildChangePosition(poRole, byPosition, dwRoleID)); });
    type.set_function("DoGuildRoleLeave", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoGuildRoleLeave(poRole)); });
    type.set_function("DoGuildBanish", [](CRobotMessageHandler* self, CRole * poRole, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoGuildBanish(poRole, dwRoleID)); });
    type.set_function("DoGuildDemise", [](CRobotMessageHandler* self, CRole * poRole, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoGuildDemise(poRole, dwRoleID)); });
    type.set_function("DoGuildDonation", [](CRobotMessageHandler* self, CRole * poRole, UINT32 dwType, UINT32 dwMoney) -> decltype(auto) { return static_cast<bool>(self->DoGuildDonation(poRole, dwType, dwMoney)); });
    type.set_function("DoGuildStorageRight", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byPosition, UINT16 wRight) -> decltype(auto) { return static_cast<bool>(self->DoGuildStorageRight(poRole, byPosition, wRight)); });
    type.set_function("DoGuildDiplomatApply", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byOpType, UINT8 byTimeType, const char* szGuildName_arg) -> decltype(auto) { char* szGuildName = const_cast<char*>(szGuildName_arg); return static_cast<bool>(self->DoGuildDiplomatApply(poRole, byOpType, byTimeType, szGuildName)); });
    type.set_function("DoGuildGetApplyUnionList", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoGuildGetApplyUnionList(poRole)); });
    type.set_function("DoGuildRevertUnionApp", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byOpType, UINT32 dwGuildID) -> decltype(auto) { return static_cast<bool>(self->DoGuildRevertUnionApp(poRole, byOpType, dwGuildID)); });
    type.set_function("DoGuildDrawSalary", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoGuildDrawSalary(poRole)); });
    type.set_function("DoGuildViewStorage", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byStorageTag) -> decltype(auto) { return static_cast<bool>(self->DoGuildViewStorage(poRole, byStorageTag)); });
    type.set_function("DoGuildPushItem", [](CRobotMessageHandler* self, CRole * poRole, UINT16 wConSlot, UINT16 wItemSlot, UINT8 byConSlot, UINT8 bySlot) -> decltype(auto) { return static_cast<bool>(self->DoGuildPushItem(poRole, wConSlot, wItemSlot, byConSlot, bySlot)); });
    type.set_function("DoGuildPopItem", [](CRobotMessageHandler* self, CRole * poRole, UINT8 byConSlot, UINT8 bySlot, UINT16 wConSlot, UINT16 wItemSlot) -> decltype(auto) { return static_cast<bool>(self->DoGuildPopItem(poRole, byConSlot, bySlot, wConSlot, wItemSlot)); });
    type.set_function("DoGuildMoveItem", [](CRobotMessageHandler* self, CRole * poRole, UINT8 bySourceConSlot, UINT8 bySourceSlot, UINT8 byTargetConSlot, UINT8 byTargetSlot) -> decltype(auto) { return static_cast<bool>(self->DoGuildMoveItem(poRole, bySourceConSlot, bySourceSlot, byTargetConSlot, byTargetSlot)); });
    type.set_function("DoGuildEnterMap", [](CRobotMessageHandler* self, CRole * poRole) -> decltype(auto) { return static_cast<bool>(self->DoGuildEnterMap(poRole)); });
    type.set_function("DoGuildChangeWeather", [](CRobotMessageHandler* self, CRole * poRole, INT8 byWeatherType, INT8 byTimeType) -> decltype(auto) { return static_cast<bool>(self->DoGuildChangeWeather(poRole, byWeatherType, byTimeType)); });
    type.set_function("DoShieldRole", [](CRobotMessageHandler* self, CRole * poRole, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoShieldRole(poRole, dwRoleID)); });
    type.set_function("DoJoinBattle", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwBattleMatch) -> decltype(auto) { return static_cast<bool>(self->DoJoinBattle(poRole, dwBattleMatch)); });
    type.set_function("DoCancelJoinBattleReq", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoCancelJoinBattleReq(poRole)); });
    type.set_function("DoJoinBattleConfirm", [](CRobotMessageHandler* self, CRole* poRole, INT32 nResult) -> decltype(auto) { return static_cast<bool>(self->DoJoinBattleConfirm(poRole, nResult)); });
    type.set_function("DoLeaveScene", [](CRobotMessageHandler* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DoLeaveScene(poRole)); });
    type.set_function("DoTeamAuctionBid", [](CRobotMessageHandler* self, CRole* poRole, INT32 nItemID, UINT32 dwBidMoneyCount) -> decltype(auto) { return static_cast<bool>(self->DoTeamAuctionBid(poRole, nItemID, dwBidMoneyCount)); });
    type.set_function("DoSpiritChangeExp", [](CRobotMessageHandler* self, CRole* poRole, bool bOnline, bool bUseMoney) -> decltype(auto) { return static_cast<bool>(self->DoSpiritChangeExp(poRole, bOnline, bUseMoney)); });
    type.set_function("DoSpiritMoveAir", [](CRobotMessageHandler* self, CRole* poRole, INT32 nSrcBagType, INT32 nSrcIndex, INT32 nTarBagType, INT32 nTarIndex) -> decltype(auto) { return static_cast<bool>(self->DoSpiritMoveAir(poRole, nSrcBagType, nSrcIndex, nTarBagType, nTarIndex)); });
    type.set_function("DoSpiritAddAir", [](CRobotMessageHandler* self, CRole* poRole, INT32 nIndex, sol::optional<INT32> bQuick_arg) -> decltype(auto) { INT32 bQuick = bQuick_arg.value_or(FALSE); return static_cast<bool>(self->DoSpiritAddAir(poRole, nIndex, bQuick)); });
    type.set_function("DoSpiritExchangeAir", [](CRobotMessageHandler* self, CRole* poRole, INT32 nAirId) -> decltype(auto) { return static_cast<bool>(self->DoSpiritExchangeAir(poRole, nAirId)); });
    type.set_function("DoSpiritBuyAirSlot", [](CRobotMessageHandler* self, CRole* poRole, INT32 nBagType, INT32 nCount) -> decltype(auto) { return static_cast<bool>(self->DoSpiritBuyAirSlot(poRole, nBagType, nCount)); });
    type.set_function("DoSpiritMergeAir", [](CRobotMessageHandler* self, CRole* poRole, INT32 nSrcIndex) -> decltype(auto) { return static_cast<bool>(self->DoSpiritMergeAir(poRole, nSrcIndex)); });
    type.set_function("DoSpiritOpenBlood", [](CRobotMessageHandler* self, CRole* poRole, INT32 nPage) -> decltype(auto) { return static_cast<bool>(self->DoSpiritOpenBlood(poRole, nPage)); });
    type.set_function("DoSpiritBrushSlot", [](CRobotMessageHandler* self, CRole* poRole, INT32 nPage, INT32 nIndex) -> decltype(auto) { return static_cast<bool>(self->DoSpiritBrushSlot(poRole, nPage, nIndex)); });
    type.set_function("DoCompleteAchievement", [](CRobotMessageHandler* self, CRole* poRole, INT32 nAchievementID) -> decltype(auto) { return static_cast<bool>(self->DoCompleteAchievement(poRole, nAchievementID)); });
    type.set_function("DoCompareAchievement", [](CRobotMessageHandler* self, CRole* poRole, UINT32 dwRoleID) -> decltype(auto) { return static_cast<bool>(self->DoCompareAchievement(poRole, dwRoleID)); });
    type.set_function("DoRewardAchievement", [](CRobotMessageHandler* self, CRole* poRole, INT32 nAchievementID) -> decltype(auto) { return static_cast<bool>(self->DoRewardAchievement(poRole, nAchievementID)); });
    type.set_function("DoQueryRanklist", [](CRobotMessageHandler* self, CRole* poRole, INT32 nRankType, INT32 nPage) -> decltype(auto) { return static_cast<bool>(self->DoQueryRanklist(poRole, nRankType, nPage)); });
    return 1;
}
