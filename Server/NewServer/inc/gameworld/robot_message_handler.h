#ifndef _ROBOT_MESSAGE_HANDLER_H_
#define _ROBOT_MESSAGE_HANDLER_H_

#ifdef _ROBOT

#include <map>

#include "net.h"
#include "external_message_header.h"

#include "g2c_message.h"
#include "c2g_message.h"
#include "m2c_message.h"
#include "c2m_message.h"

class IRobotMessageNotifier;
class CRole;
class CNpc;
class CCharacter;
class CTeamInGS;
struct ItemInfo;

typedef std::map<UINT32, UINT32>				ROLE_INFO_CACHE;
typedef std::map<UINT32, ExternalMessage::G2C_SYNC_ROLE_DATA>    ROLE_DATA_CACHE;
typedef std::map<UINT32, ExternalMessage::G2C_SYNC_NPC_DATA>     NPC_DATA_CACHE;

struct GUILD_CACHE
{
    UINT32		dwGuildID;
    char		szGuildName[GUILD_NAME_LEN];
    UINT32		dwLeaderID;
    UINT32      dwCreateTime;
    UINT8		byMemberCount;
    UINT8		byMainLevel;
    UINT8		byHouseLevel;
    unsigned	bySabacState;
};
typedef     std::map<UINT32, GUILD_CACHE>   GUILD_DATA_CACHE_MAP;
typedef     std::map<UINT32, UINT32>        GUILD_INFO_CACHE;
struct ROLE_CACHE
{
    ROLE_INFO_CACHE		RoleInfoCache;
    ROLE_DATA_CACHE		RoleDataCache;
    NPC_DATA_CACHE		NpcDataCache;
    GUILD_INFO_CACHE    GuildInfoCache;
    GUILD_DATA_CACHE_MAP    GuildDataCache;
};

extern ROLE_CACHE	s_RoleCache;

class CRobotMessageHandler
{
public:
    CRobotMessageHandler();
    virtual ~CRobotMessageHandler();

    virtual BOOL Init(IRobotMessageNotifier* poNotifier, IPacketAllocator* poPacketAllocator);
    virtual BOOL UnInit(void);
    static CRobotMessageHandler& GetInstance(void);

    void OnRecv(CRole* pRole, const char* pData);

	BOOL DoLogout(CRole* poRole);
	BOOL DoLogoutCancel(CRole* poRole);
    BOOL DoUpdatePos(CRole* poRole);
    BOOL DoQueryRoleData(CRole* poRole, CRole* poQueryRole);
    BOOL DoQueryNpcData(CRole* poRole, CNpc* poQueryNpc);
    BOOL DoLeaveScene(CRole* poRole);
    BOOL DoRoleWalk(CRole* poRole);
	BOOL DoRoleRun(CRole* poRole);
	BOOL DoRoleRotate(CRole* poRole, INT32 nDirection);

	BOOL DoSelectFocus(CRole* poRole, INT32 nFocusID);	
	BOOL DoLearnSpell(CRole* poRole, INT32 nSpellID, INT32 nSpellLevel);
    BOOL DoCastSpell(CRole* poRole, INT32 nSpellID, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ);
    BOOL DoDirectCastSpell(CRole* poRole, INT32 nSpellID, INT32 nSpellLevel, UINT32 dwTargetID, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ);
	BOOL DoCancelCast(CRole* poRole);
	BOOL DoChangePkMode(CRole* poRole);

	BOOL DoPickUpItem(CRole* poRole, UINT32 dwDropID, UINT8 byPickMode);
    BOOL DoUseItem(CRole* poRole, UINT8 conslot, UINT8 itemslot);
    BOOL DoMoveItem(CRole* poRole, UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot);
    BOOL DoSplitItem(CRole* poRole, UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot, INT16 itemcount);
    BOOL DoDeleteItem(CRole* poRole, UINT8 conslot, UINT8 itemslot, INT16 itemcount);

	// trade
	void SetTradeTendency(INT32 nSuccTradeTendency){ m_nSuccTradeTendency = nSuccTradeTendency; } // 0<= value <= 10000
	BOOL DoTradeAsk(CRole* pRole, UINT32 dwTargetRoleID);
	BOOL DoTradeAccept(CRole* pRole, UINT32 dwTargetRoleID);
	BOOL DoTradeSetMoney(CRole* pRole, INT32 nMoneyCount);
	BOOL DoTradeSetItem(CRole* pRole, UINT8 bAdd, UINT8 byTradeSlot, UINT8 byConSlot, UINT8 byItemSlot);
	BOOL DoTradeLock(CRole* pRole);
	BOOL DoTradeUnlock(CRole* pRole);
	BOOL DoTradeConfirm(CRole* pRole);
	BOOL DoTradeCancel(CRole* pRole);

    //team
    void SetTeamAuto(BOOL bAuto){m_bTeamAuto = bAuto;}
    BOOL DoTeamJoinRand(CRole* poRole);

    BOOL DoTeamJoin(CRole* poRole, UINT32 dwTargetRoleID);
    BOOL DoTeamLeave(CRole* poRole, UINT32 dwLeaveRoleID);
    BOOL DoTeamAnswer(CRole* poRole, UINT32 dwAnswerReqRoleID, UINT8 byType, UINT8 byAnswerResult);
    BOOL DoTeamChangeInfo(CRole* poRole, INT32 nTeamMemberLimit, UINT8 byAssignType, UINT8 dwLeadID, UINT8 byAuctionItemColorLimit);
    
	BOOL DoTeamChangeActivityInfo(CRole* poRole, UINT32 dwActivityType,INT32 nActivityID);	
    BOOL DoTeamQueryActivityTeam(CRole* poRole, UINT32 dwActivityType,INT32 nActivityID, INT32 nPgae);	
    BOOL DoTeamRemoveActivityTeam(CRole* poRole);	

    BOOL DoAdjacentNoTeamRole(CRole* poRole);
    BOOL DoAdjacentTeam(CRole* poRole);

	// team auction
    BOOL DoTeamAuctionBid(CRole* poRole, INT32 nItemID, UINT32 dwBidMoneyCount);

    // master
    BOOL DoMstGetRecruit(CRole *poRole);
    BOOL DoMstGetSoloList(CRole *poRole);

    BOOL DoMstSubmitStudApp(CRole* poRole, UINT32 dwTeacherID);
    BOOL DoMstAgreeStudApp(CRole* poRole, UINT32 dwStudentID);
    BOOL DoMstCancelStudApp(CRole* poRole, UINT32 dwMasterID);
    BOOL DoMstRefuseStudApp(CRole* poRole, UINT32 dwStudentID);
    //BOOL DoMstLeaveMaster(CRole* poRole);
    BOOL DoMstFireStudent(CRole* poRole, UINT32 dwStudentID);
    //BOOL DoMstCongLevelUp(CRole* poRole, UINT32 dwStudentID, UINT8 byCongType);

    // guild
    BOOL DoGuildCreate(CRole *poRole, char *guild_name, char *announce);
    BOOL DoGuildView(CRole *poRole, UINT32 lastGuildID);
    BOOL DoFindGuild(CRole *poRole, char *guild_name);
    BOOL DoGuildApplyToJoinGuild(CRole *poRole, UINT32 dwGuildID);
    BOOL DoGetApplyGuildList(CRole *poRole);
    BOOL DoGetRevertGuildApp(CRole *poRole, UINT8 byRevertType, UINT32 dwRoleID);
    BOOL DoInviteToJointGuild(CRole *poRole, char *szRoleName);
    BOOL DoRevertTheInvitation(CRole *poRole, UINT8 byRevertType, UINT32 dwRoleID);
    BOOL DoDisbandGuild(CRole *poRole);
    BOOL DoGuildChangeNotice(CRole *poRole, char *pNotice);
    BOOL DoGuildForbidChat(CRole *poRole, UINT8 byOp, UINT32 dwRoleID);
    BOOL DoGuildChangePosition(CRole *poRole, UINT8 byPosition, UINT32 dwRoleID);
    BOOL DoGuildRoleLeave(CRole *poRole);
    BOOL DoGuildBanish(CRole *poRole, UINT32 dwRoleID);
    BOOL DoGuildDemise(CRole *poRole, UINT32 dwRoleID);
    BOOL DoGuildDonation(CRole *poRole, UINT32 dwType, UINT32 dwMoney);
    BOOL DoGuildStorageRight(CRole *poRole, UINT8 byPosition, UINT16 wRight);
    BOOL DoGuildDiplomatApply(CRole *poRole, UINT8 byOpType, UINT8 byTimeType, char *szGuildName);
    BOOL DoGuildGetApplyUnionList(CRole *poRole);
    BOOL DoGuildRevertUnionApp(CRole *poRole, UINT8 byOpType, UINT32 dwGuildID);

    BOOL DoGuildDrawSalary(CRole *poRole);
    BOOL DoGuildViewStorage(CRole *poRole, UINT8 byStorageTag);
    BOOL DoGuildPushItem(CRole *poRole, UINT16 wConSlot, UINT16 wItemSlot,UINT8 byConSlot, UINT8 bySlot);
    BOOL DoGuildPopItem(CRole *poRole, UINT8 byConSlot, UINT8 bySlot, UINT16 wConSlot, UINT16 wItemSlot);
    BOOL DoGuildMoveItem(CRole *poRole, UINT8 bySourceConSlot, UINT8 bySourceSlot, UINT8 byTargetConSlot, UINT8 byTargetSlot);

    BOOL DoGuildEnterMap(CRole *poRole);
    BOOL DoGuildChangeWeather(CRole *poRole, INT8 byWeatherType, INT8 byTimeType);

    // shield list
    BOOL DoShieldRole(CRole *poRole, UINT32 dwRoleID);
	BOOL DoRoleRevive(CRole* pRole);

	// chat
	BOOL DoSendChatToGS(CRole* poSrcRole, UINT32 dwTargetID, const char* chMessage);
	BOOL DoSendChatToMS(CRole* poSrcRole, UINT32 dwTargetID, const char* pcszMessage);
    
    //score
    BOOL DoReplayDungeon(CRole* poRole);
    BOOL DoSelectReward(CRole* poRole, INT32 nType);

	//line
	BOOL DoQueryLineReq(CRole* poRole);
	BOOL DoChangeLine(CRole* poRole, UINT8 byLineIndex);

	////arena_team
	//BOOL DoCreateArenaTeam(CRole* poRole, UINT16 wIConID, const char* pzArenaTeamName);
	//BOOL DoJoinArenaTeam(CRole* poRole, UINT32 dwInviteRoleID);
	//BOOL DoJoinArenaTeamAnswer(CRole* poRole, UINT32 dwInviteRoleID, UINT8 byAnswer);
	//BOOL DoLeaveArenaTeam(CRole* poRole, UINT32 dwLeaveRoleID);
	//BOOL DoQueryArenaTeamInfo(CRole* poRole);
	//BOOL DoJoinArena(CRole* poRole, INT32 nArenaType);
	//BOOL DoCancelJoinArenaReq(CRole* poRole);
	//BOOL DoJoinArenaConfirm(CRole* poRole, INT32 nResult);

	//battle
	BOOL DoJoinBattle(CRole* poRole, UINT32 dwBattleMatch);
	BOOL DoCancelJoinBattleReq(CRole* poRole);
	BOOL DoJoinBattleConfirm(CRole* poRole, INT32 nResult);
   
	//spirit
	BOOL DoSpiritChangeExp(CRole* poRole, BOOL bOnline, BOOL bUseMoney);
	BOOL DoSpiritMoveAir(CRole* poRole, INT32 nSrcBagType, INT32 nSrcIndex, INT32 nTarBagType, INT32 nTarIndex);
	BOOL DoSpiritAddAir(CRole* poRole, INT32 nIndex, INT32 bQuick = FALSE);
	BOOL DoSpiritExchangeAir(CRole* poRole, INT32 nAirId);
	BOOL DoSpiritBuyAirSlot(CRole* poRole, INT32 nBagType, INT32 nCount);
	BOOL DoSpiritMergeAir(CRole* poRole, INT32 nSrcIndex);

	BOOL DoSpiritOpenBlood(CRole* poRole, INT32 nPage);
	BOOL DoSpiritBrushSlot(CRole* poRole, INT32 nPage, INT32 nIndex);

	//achievement
	BOOL DoCompleteAchievement(CRole* poRole, INT32 nAchievementID);
	BOOL DoCompareAchievement(CRole* poRole, UINT32 dwRoleID);
	BOOL DoRewardAchievement(CRole* poRole, INT32 nAchievementID);	

	// ranklist
	BOOL DoQueryRanklist(CRole* poRole, INT32 nRankType, INT32 nPage);	

	// activity
	BOOL DoActivityReward(CRole* poRole, INT32 nRewardIndex);

	BOOL DoQueryRoleInfo(CRole* poRole, UINT32 dwTargetRoleID);
    BOOL DoQueryGuildInfo(CRole* poRole, UINT32 dwGuildID);
	// quest
	BOOL DoAcceptQuest(CRole* poRole, INT32 nQuestID, INT32 nAcceptType, INT32 nAcceptSrcID);
	BOOL DoCompleteQuest(CRole* poRole, INT32 nQuestID, INT32 nSelectedAwardIdx);
	BOOL DoAbandonQuest(CRole* poRole, INT32 nQuestID);
	BOOL DoInteractWithNpc(CRole* poRole, UINT32 dwNpcID);
	BOOL DoOperateDoodad(CRole* poRole, UINT32 dwDoodadID);

private:
    void OnCharAppear(CRole* pRole, const char* pData);
    void OnSyncCharList(CRole* pRole, const char* pData);
    void OnObjectDisappear(CRole* pRole, const char* pData);
	void OnObjectDisappearList(CRole* pRole, const char* pData);
    void OnCharWalk(CRole* pRole, const char* pData);
	void OnCharRun(CRole* pRole, const char* pData);
	void OnCharStop(CRole* pRole, const char* pData);
	void OnObjectRotate(CRole* poRole, const char* pData);
    void OnCharPassiveMove(CRole* pRole, const char* pData);
    void OnCharDie(CRole* pRole, const char* pData);
    void OnCharRevive(CRole* pRole, const char* pData);
	//void OnReviveResponse(CRole* pRole, const char* pData);

    void OnSyncRoleData(CRole* pRole, const char* pData);
    void OnSyncNpcData(CRole* pRole, const char* pData);
    void OnSyncClientVariables(CRole* pRole, const char* pData);
	void OnRoleLevelUp(CRole* pRole, const char* pData);
	void OnSyncDropList(CRole* pRole, const char* pData);

    void OnSyncFrame(CRole* pRole, const char* pData);
    void OnEnterScene(CRole* pRole, const char* pData);
    void OnLeaveScene(CRole* pRole, const char* pData);
    void OnSyncRolePos(CRole* pRole, const char* pData);
    void OnSyncAttrList(CRole* pRole, const char* pData);
    void OnSyncAttrChange(CRole* pRole, const char* pData);
	void OnSyncFaction(CRole* pRole, const char* pData);
	void OnSyncPkMode(CRole* pRole, const char* pData);
	void OnSyncPkValue(CRole* pRole, const char* pData);

    void OnSyncSpellBook(CRole* pRole, const char* pData);
    void OnRoleLearnSpell(CRole* pRole, const char* pData);
    void OnSyncSpellSlot(CRole* pRole, const char* pData);
	void OnCharEquipSpell(CRole* pRole, const char* pData);

    void OnCharPrepareSpell(CRole* pRole, const char* pData);
    void OnCharCastSpell(CRole* pRole, const char* pData);
    void OnCharSpellEffect(CRole* pRole, const char* pData);
    void OnCastOver(CRole* pRole, const char* pData);
    void OnBreakCast(CRole* pRole, const char* pData);


    void OnNewAura(CRole* pRole, const char* pData);
    void OnAuraChange(CRole* pRole, const char* pData);
    void OnDelAura(CRole* pRole, const char* pData);
    void OnCharSelectFocus(CRole* pRole, const char* pData);

    void OnSyncGameDataBegin(CRole* pRole, const char* pData);
    void OnSyncGameDataEnd(CRole* pRole, const char* pData);
    void OnChangeSceneEnter(CRole* pRole, const char* pData);
    void OnSyncMoney(CRole* pRole, const char* pData);
	void OnSyncContainerSizes(CRole* pRole, const char* pData);
	void OnContainerSizeChange(CRole* pRole, const char* pData);
    void OnSyncItemBag(CRole* pRole, const char* pData);
    void OnMoneyChange(CRole* pRole, const char* pData);
    void OnItemChange(CRole* pRole, const char* pData);
    void OnItemSwap(CRole* pRole, const char* pData);
	void OnItemDelete(CRole* pRole, const char* pData);
	

	void OnRefine(CRole* pRole, const char* pData);

    // chat
    void OnMSChatMsg(CRole* poRole, const char* pData);

     // title
    void OnSyncTitle(CRole* poRole, const char* pData);
    void OnAddTitle(CRole* poRole, const char* pData);
    void OnDelTitle(CRole* poRole, const char* pData);
    void OnSyncEquipTitle(CRole* poRole, const char* pData);

    // attribute
    void OnExpChange(CRole* pRole, const char* pData);
	void OnModifyReputation(CRole* pRole, const char* pData);

	// stall
	void OnStallStateChange(CRole* pRole, const char* pData);
	void OnAddStallItem(CRole* pRole, const char* pData);
	void OnRemoveStallItem(CRole* pRole, const char* pData);
	void OnChangeStallName(CRole* pRole, const char* pData);
	void OnBuyStallItem(CRole* pRole, const char* pData);
	void OnSoldStallItem(CRole* pRole, const char* pData);
	void OnSyncStallLevel(CRole* pRole, const char* pData);
	void OnViewStallItem(CRole* pRole, const char* pData);

	// quest
    void OnCompleteQuest(CRole* pRole, const char* pData);

	// variables
	void OnUpdateVariable(CRole* pRole, const char* pData);

	// trade
	void OnGSTradeSetMoney(CRole* pRole, const char* pData);
	void OnGSTradeSetItem(CRole* pRole, const char* pData);
	void OnGSTradeStateChange(CRole* pRole, const char* pData);

    //team
    void OnMSTeamJoin(CRole* pRole, const char* pData);
    void OnMSTeamLeave(CRole* pRole, const char* pData);
    void OnMSTeamAnswer(CRole* pRole, const char* pData);
    void OnMSTeamAddMember(CRole* pRole, const char* pData);
    void OnMSTeamRemoveMember(CRole* pRole, const char* pData);
    void OnMSTeamChangeInfo(CRole* pRole, const char* pData);
    void OnMSTeamSyncMemberInfo(CRole* pRole, const char* pData);
	void OnMSTeamSyncMemberState(CRole* pRole, const char* pData);
	void OnGSTeamSyncMemberInfo(CRole* pRole, const char* pData);

	void OnGSBattleTeamJoin(CRole* pRole, const char* pData);
	void OnGSBattleTeamAddMember(CRole* pRole, const char* pData);
	void OnGSBattleTeamRemoveMember(CRole* pRole, const char* pData);

    void OnAdjacentNoTeamRole(CRole* pRole, const char* pData);
    void OnAdjacentTeam(CRole* pRole, const char* pData);

    void OnMSErrorNotify(CRole* pRole, const char* pData);

    void OnGSCompleteAchievement(CRole* pRole, const char* pData);

    void OnShieldRole(CRole* pRole, const char* pData);
    void OnUnshieldRole(CRole* pRole, const char* pData);

    // master
    void OnMasterSync(CRole *poRole, const char *pData);
    void OnMasterInfo(CRole *poRole, const char *pData);
    void OnMasterLvlUp(CRole *poRole, const char *pData);
    void OnMSGetRecruitList(CRole *poRole, const char *pData);
    void OnMSGetSoloList(CRole *poRole, const char *pData);

    void OnMSTeacherAddStudent(CRole *poRole, const char *pData);
    void OnMSTeacherDelStudent(CRole *poRole, const char *pData);

    void OnMSApplyTeacherAck(CRole *poRole, const char *pData);
    void OnMSApplyTeacherNtf(CRole *poRole, const char *pData);
    void OnMSTeacherAgreeAppAck(CRole *poRole, const char *pData);
    void OnMSTeacherRefuseAppAck(CRole *poRole, const char *pData);
    void OnMSStudBeRefusedAppAck(CRole *poRole, const char *pData);
    void OnMSSoloCancelAppAck(CRole *poRole, const char *pData);
    void OnMSSoloCancelAppNtf(CRole *poRole, const char *pData);

    void OnMSApplyToSoloAck(CRole *poRole, const char *pData);
    void OnMSApplyToSoloNtf(CRole *poRole, const char *pData);
    void OnMSSoloAgreeAppAck(CRole *poRole, const char *pData);
    void OnMSSoloRefuseAppAck(CRole *poRole, const char *pData);
    void OnMSSoloRefuseAppNtf(CRole *poRole, const char *pData);
    void OnMSTeacherCancelAppAck(CRole *poRole, const char *pData);
    void OnMSTeacherCancelAppNtf(CRole *poRole, const char *pData);

    void OnMSStudentClear(CRole *poRole, const char *pData);
    void OnMSStudentLeaveTeacherAck(CRole *poRole, const char *pData);
    void OnMSStudentLeaveTeacherNtf(CRole *poRole, const char *pData);

    void OnMSFireStudentAck(CRole *poRole, const char *pData);
    void OnMSFireStudentNtf(CRole *poRole, const char *pData);

    void OnMSMasterCZAck(CRole *poRole, const char *pData);
    void OnMSCZCount(CRole *poRole, const char *pData);

    void OnMSDesireGraduateAck(CRole *poRole, const char *pData);
    void OnMSDesireGraduateNtf(CRole *poRole, const char *pData);
    void OnMSAgreeGraduate(CRole *poRole, const char *pData);

    // guild
    void OnMSGQueryInfo(CRole *poRole, const char *pData);
    void OnMSGuildInfo(CRole *poRole, const char *pData);
    void OnMSGMoreInfoAck(CRole *poRole, const char *pData);
    void OnMSGViewListAck(CRole *poRole, const char *pData);
    void OnMSGFindAck(CRole *poRole, const char *pData);
    void OnMSCreateGuildAck(CRole *poRole, const char *pData);
    void OnMSGApplyToJoinAck(CRole *poRole, const char *pData);
    void OnMSGuildGetAppList(CRole *poRole, const char *pData);
    void OnMSGuildDelGuildApp(CRole *poRole, const char *pData);
    void OnMSGRevertAppAck(CRole *poRole, const char *pData);
    void OnMSGInviteToJoinGuild(CRole *poRole, const char *pData);
    void OnMSGRevertGuildInvitationAck(CRole *poRole, const char *pData);

    void OnMSGuildDisband(CRole *poRole, const char *pData);
    void OnMSGuildChangeNotice(CRole *poRole, const char *pData);
    void OnMSGuildChangePosition(CRole *poRole, const char *pData);
    void OnMSGuildLeaveGuildAck(CRole *poRole, const char *pData);
    void OnMSDelMemberNtf(CRole *poRole, const char *pData);
    void OnMSAddMemberNtf(CRole *poRole, const char *pData);

    void OnMSDemise(CRole *poRole, const char *pData);

    void OnGuildCongAck(CRole *poRole, const char *pData);
    void OnGuildAttrModifyAck(CRole *poRole, const char *pData);
    void OnGuildGetUnionAppListAck(CRole *poRole, const char *pData);

    //friend
	void OnMSFriendList(CRole* pRole, const char* pData);
	void OnMSFriendAdd(CRole* pRole, const char* pData);
    
    //scene
    void OnQuerySceneDifficulty(CRole* pRole, const char* pData);
    //score
    void OnGSSceneFinish(CRole* pRole, const char* pData);
    void OnGSDungeonFinishScore(CRole* pRole, const char* pData);
    void OnGSDungeonReward(CRole* pRole, const char* pData);

	//void OnGSArenaFinishScore(CRole* pRole, const char* pData);
	//arena_team
	void OnJoinArenaTeam(CRole* pRole, const char* pData);
	void OnJoinArenaTeamAsk(CRole* pRole, const char* pData);
	void OnLeaveArenaTeam(CRole* pRole, const char* pData);
	void OnArenaTeamInfo(CRole* pRole, const char* pData);
	void OnJoinArenaQueue(CRole* pRole, const char* pData);
	void OnCancelJoinArenaAck(CRole* pRole, const char* pData);
	void OnJoinArenaConfirmReq(CRole* pRole, const char* pData);

	void OnMSSyncArenaScoreForRole(CRole* pRole, const char* pData);
	void OnMSSyncArenaScoreForTeam(CRole* pRole, const char* pData);
	//battle
	void OnJoinBattleQueue(CRole* pRole, const char* pData);
	void OnCancelJoinBattleAck(CRole* pRole, const char* pData);
	void OnJoinBattleConfirmReq(CRole* pRole, const char* pData);
	
	//logout
	void OnLogoutInfo(CRole* pRole, const char* pData);
	
	// achievement
	void OnCompleteAchievement(CRole* pRole, const char* pData);
	void OnCompareAchievement(CRole* pRole, const char* pData); 
	void OnRewardAchievement(CRole* pRole, const char* pData);
	void OnUpdateAchievementVariable(CRole* pRole, const char* pData); 
	void OnSyncAchievementList(CRole* pRole, const char* pData);
	void OnActivateHandBook(CRole* pRole, const char* pData);

	// spirit
	void OnSpiritBloodOpen(CRole* pRole, const char* pData);
	void OnSpiritExpChange(CRole* pRole, const char* pData);
	void OnSpiritUp(CRole* pRole, const char* pData);
	void OnSpiritAirChange(CRole* pRole, const char* pData);
	void OnSpiritAirLevelUp(CRole* pRole, const char* pData);
	void OnSpiritSlotSizeChange(CRole* pRole, const char* pData);
	void OnSpiritBrushSlot(CRole* pRole, const char* pData);
	void OnSpiritNotiryExpChangeTime(CRole* pRole, const char* pData);

	//hero
	void OnHireHero(CRole* pRole, const char* pData);
	void OnHeroLevelUp(CRole* pRole, const char* pData);

	// 铸魂
	void OnRuneItem(CRole* pRole, const char* pData);

	// vip
	void OnSyncVipState(CRole* pRole, const char* pData);
	void OnSyncVipLevel(CRole* pRole, const char* pData);

    // mail
    void OnMailWriteSuccess(CRole* pRole, const char* pData);
    void OnMailListRecv(CRole* pRole, const char* pData);
    void OnMailRead(CRole* pRole, const char* pData);
    void OnMailDeleteSuccess(CRole* pRole, const char* pData);
    void OnMailNewCount(CRole* pRole, const char* pData);
    void OnMailGetAttachSuccess(CRole* pRole, const char* pData);

    // auction
    void OnAuctionSearchType(CRole* pRole, const char* pData);
    void OnAuctionSearch(CRole* pRole, const char* pData);
    void OnAuctionQuery(CRole* pRole, const char* pData);
    void OnAuctionSell(CRole* pRole, const char* pData);
    void OnAuctionCancelSell(CRole* pRole, const char* pData);
    void OnAuctionBuy(CRole* pRole, const char* pData);
    void OnAuctionFinished(CRole* pRole, const char* pData);
    void OnAuctionListMySelling(CRole* pRole, const char* pData);
    void OnAuctionListMyBuying(CRole* pRole, const char* pData);

	void OnMSSyncRoleInfo(CRole* pRole, const char* pData);

	// mount
	void OnActivateMount(CRole* pRole, const char* pData);
	void OnOnMount(CRole* pRole, const char* pData);
	void OnOffMount(CRole* pRole, const char* pData);

private:
    BOOL _OnCharAppear(CRole* poRole, ExternalMessage::CHAR_APPEAR_DATA* pAppearData);

private:
    static CRobotMessageHandler	ms_Instance;
    IPacketAllocator*	        m_pPacketAllocator;
    IRobotMessageNotifier*      m_poNotifier;
	BOOL                        m_bTeamAuto;
	INT32                       m_nSuccTradeTendency;

    typedef void (CRobotMessageHandler::*ROBOT_MESSAGE_FUNC)(CRole* poRole, const char* pData);
    ROBOT_MESSAGE_FUNC  m_RobotMessageFuncList[ExternalMessage::max_message_count];

    struct CTraverseTeam
    {
        INT32		m_nIndex;
		UINT32		m_dwLeaderID;
		UINT32		m_dwSessionID;
        BOOL operator()(UINT32 dwTeamID, CTeamInGS* pstTeam);
    };
};

#endif

#endif  // _ROBOT_MESSAGE_HANDLER_H_