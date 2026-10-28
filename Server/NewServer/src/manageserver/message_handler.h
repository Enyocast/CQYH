#ifndef _MS_MESSAGE_HANDLER_H_
#define _MS_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"
#include "external_message_header.h"
#include "common_message.h"
#include "server_def.h"
#include "error_def.h"
#include "base_list.h"
#include "mail/mail.h"

struct SMSSession;
struct MS_USER;
class  CTeam;
struct MS_ROLE_DATA;
struct MS_ONLINE_ROLE_DATA;
struct SCENE_INFO;
struct SArenaTeam;
class CMsGuild;
struct MS_GUILD_MEMBER_DATA;
struct ItemInfo;
struct DB_OP_LOG_ITEM_RESULT;
struct Auction;
struct Order;
struct GUILD_WAR_PERSONAL_ACHIEVEMENT;
struct MS_TEACHER_DATA;
struct SCENE_DATA;

#define KICK_USER(__session_id__, __kick_type__)                                                                    \
    do                                                                                                              \
    {                                                                                                               \
        CMessageHandler::GetInstance()._KickUser(__session_id__, __kick_type__, __FILE__, __FUNCTION__, __LINE__);  \
    } while (0)

#define NOTIFY_GD(__level__, __str_content__, ...)												\
    do																							\
	{																							\
        CMessageHandler::GetInstance().DoGDNotify(__level__, __str_content__, ##__VA_ARGS__);	\
	} while (0)

struct CreateGuildParam
{
    UINT32      dwRoleID;
    BOOL        bConsumeItem;
    char        szGuildName[GUILD_NAME_LEN];
    char        szAnnounce[GUILD_ANNOUNCE_LEN];
};


class CMessageHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
    virtual void OnConnected(ISocketSession* pSocketSession);
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
    CMessageHandler();
    ~CMessageHandler();

    BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator, ISocketAcceptor* poGTAcceptor,
        ISocketAcceptor* poGSAcceptor, ISocketAcceptor* poLSAcceptor, ISocketAcceptor* poDBAcceptor, 
		ISocketAcceptor* poBSAcceptor, ISocketAcceptor* poDLAcceptor, ISocketAcceptor* poMMAcceptor,
		ISocketAcceptor* poMonitorForRoleNumber);
    BOOL UnInit(void);
    static CMessageHandler& GetInstance(void);

    void _KickUser(UINT32 dwClientSessionID, INT32 eKickType,
        const char* pcszFileName, const char* pcszFuncName, INT32 nLineNum);
    
    BOOL CheckAllClose(void);

public:
    /************************************************************************/
    // To All Server
    BOOL DoServerInfo(void);
    BOOL DoAllReady(void);
    BOOL DoAllPing(void);
    BOOL DoClose(void);
    /************************************************************************/
    // To GD Server
	BOOL DoGDRegrister();
	BOOL DoGDCommandAck(const char* szResult);
	BOOL DoGDNotify(UINT8 byLevel, const char* szResult, ...);

    // To GM Server
    BOOL DoGMRegister();
    BOOL DoGMClearRoleCacheAck(INT32 nResult, UINT32 dwTLUserID, UINT32 dwCmdSerialID);
    BOOL DoGMUnlockRoleAck(INT32 nResult, UINT32 dwRoleID);
    BOOL DoGMQueryRoleDataAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID, INT32 nResult, UINT32 dwLogoutTime);
    BOOL DoGMForbidChatAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID, INT32 nResult);
    BOOL DoGMFreezeRoleAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID, INT32 nResult);
    BOOL DoGMKickRoleAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID, INT32 nResult);
    BOOL DoGMSendMailAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID, INT32 nResult);
    BOOL DoGMAnnounceAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, INT32 nResult);
    BOOL DoGMGetAnnounceListAck(INT32 nGroupID, UINT32 dwTLUserID, UINT32 dwCmdSerialID, INT32 nResult);
    BOOL DoGMDelAnnounceAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, INT32 nResult, UINT32 dwAnnounceSerial);
    BOOL DoGMExeGMStrAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, INT32 nResult);

    BOOL DoGMStrCmdLog(UINT32 dwTime, INT32 nGroupID, UINT32 dwIP, UINT32 dwRoleID, const char *pcszRoleName, const char *pcszCmd, INT32 nResult);
    BOOL DoGMDelMailAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwMailID, INT32 nResult, MailInfo *pMailInfo);
    BOOL DoGMCheckRoleFreezeAck(UINT32 dwTLUserID, UINT32 dwCmdSerialID, INT32 nResult);
    BOOL DoGMGetExchangePriceAck(UINT8 byGroupID);
    BOOL DoGMGetExchangePriceDetailAck(UINT8 byGroupID, UINT8 byOrderType, INT32 nPrice, UINT32 dwTLUserID);
    BOOL DoGMAddSystemOrderAck(UINT32 dwTLUserID, UINT8 byGroupID, UINT64 qwOrderID, INT32 nResult, INT32 nPrice, INT32 nCount);
    BOOL DoGMCancelSystemOrderAck(UINT32 dwTLUserID, UINT8 byGroupID, UINT64 qwOrderID, INT32 nResult, INT32 nPrice, INT32 nCount);
    BOOL DoGMGetExchangeLimitAck(UINT32 dwTLUserID, UINT8 byGroupID, INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit);
    BOOL DoGMSetExchangeLimitAck(UINT32 dwTLUserID, UINT8 byGroupID, INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit);

    /************************************************************************/
    // To GT
    BOOL DoGTRegisterAck(UINT32 dwGTSessionID);

    BOOL DoGTEnterGateAck(UINT32 dwClientSessionID, INT32 nErrorCode);
	BOOL DoGTQuerySceneAck(UINT32 dwClientSessionID, UINT32 dwRoleID, UINT32 dwGSSessionID, INT32 nErrorCode, INT32 nErrCodeParam1, INT32 nErrCodeParam2);
	BOOL DoGTCloseClientSession(UINT32 dwClientSessionID);
	BOOL DoGTReturnSelectRole(UINT32 dwClientSessionID);
	BOOL DoGTChangeGS(UINT32 dwClientSessionID, UINT32 dwGSSessionID);
	BOOL DoGTSwitchServerGroupState(INT32 nServerGroupID, BOOL bOpened);
	BOOL DoGTGMCommand(const char* pcszGMCommand);
	BOOL DoGTCheckNewName(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwID, const char* szName, const char* UserData, UINT32 dwUserDataLen);

    /************************************************************************/
    // To GS
    BOOL DoGSRegisterAck(UINT32 dwGSSessionID);

	BOOL DoGSPreEnterGS(INT32 dwGSSessionID, MS_USER* poUser, UINT32 dwRoleID, INT32 nSceneTempID,
        INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ, INT32 nFaceDirection);
    BOOL DoGSEnterGSAck(INT32 dwGSSessionID, INT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoGSLeaveGS(INT32 dwGSSessionID, INT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoGSCreateScene(INT32 dwGSSessionID, INT32 nServerGroupID, INT32 nSceneTempID, INT32 nSceneID);
    BOOL DoGSDestroyScene(INT32 dwGSSessionID, INT32 nServerGroupID, INT32 nSceneTempID, INT32 nSceneID);
	BOOL DoGSCloseScene(INT32 dwGSSessionID, INT32 nServerGroupID, INT32 nSceneTempID, INT32 nSceneID);
	BOOL DoGSChangeScene(INT32 dwGSSessionID, INT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoGSRoomEnterDungeon(INT32 dwGSSessionID, UINT32 dwRoleID, INT32 nSceneTempID, INT32 nSceneID);
	BOOL DoGSSpawnNpc(INT32 nSceneTempID, INT32 nX, INT32 nY, INT32 nZ, INT32 nRange, 
		INT32 nNpcTemplateID, INT32 nNpcCount, UINT32 dwSuicideTime);

    BOOL DoGSQuerySceneAck(INT32 dwGSSessionID, INT32 dwClientSessionID, INT32 nErrorCode, UINT32 dwRoleID, 
        INT32 nSceneTempID, INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ, INT32 nFaceDirection);

    BOOL DoGSTeamInfo(INT32 dwGSSessionID, CTeam* poTeam);

    BOOL DoGSTeamNew(CTeam* poTeam);
    BOOL DoGSTeamAddMember(MS_ROLE_DATA* pstNewMember, CTeam* poTeam);
    BOOL DoGSTeamChangeInfo(CTeam* poTeam);
    BOOL DoGSTeamRemoveMember(UINT32 dwDelMemberID, CTeam* poTeam);

    BOOL DoGSChangeInfo(UINT32 dwGSSessionID, UINT32 dwCliSessionID, UINT32 dwRoleID, const char* szSignature);
    BOOL DoGSAddFriend(UINT32 dwGSSessionID, UINT32 dwCliSessionID, UINT32 dwRoleID, UINT32 dwFriendID, UINT8 byGroupID);
    BOOL DoGSDelFriend(UINT32 dwGSSessionID, UINT32 dwCliSessionID, UINT32 dwRoleID, UINT32 dwFriendID, UINT8 byGroupID);

    // master
    BOOL DoGSSubmitTeacherApp(UINT32 dwGSSessionID, UINT8 bySourceType, UINT32 dwTeacherID, UINT32 dwStudentID);
    BOOL DoGSMstAgreeTeacherApp(UINT32 dwGSSessionID, UINT32 dwTeacherID, UINT32 dwStudentID);
    BOOL DoGSSubmitStudApp(UINT32 dwGSSessionID, UINT32 dwTeacherID, UINT32 dwStudentID);
    BOOL DoGSMstAgreeStudApp(UINT32 dwGSSessionID, UINT32 dwTeacherID, UINT32 dwStudentID);
    BOOL DoGSMstCZ(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwTargetID, INT32 nCZType, INT32 nCZLevel, INT32 nMoneyConsumption, const char *pcszText);
    BOOL DoGSMstSyncState(UINT32 dwGSSessionID, UINT32 dwRoleID, INT32 nState);
    BOOL DoGSMstSyncData(UINT32 dwGSSessionID, UINT32 dwCliSessionID, UINT32 dwRoleID, MS_TEACHER_DATA &teacher);
    BOOL DoGSMstCreateRelationNtf(UINT32 dwTeacherID, UINT32 dwStudentID);
    BOOL DoGSMstDelRelationNtf(UINT32 dwTeacherID, UINT32 dwStudentID);
    BOOL DoGSMstUpdateData(UINT32 dwRoleID, INT32 nType, INT32 nValue);

    BOOL DoGSMailCostCheck(UINT32 dwGSSessionID, UINT32 dwSenderRoleID, UINT32 dwReceiverRoleID, const char* subject, const char* content);
    BOOL DoGSGetSimpleAttach(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwMailID, INT32 nItemID, INT32 nItemCount);
    BOOL DoGSGetBufferAttach(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwMailID, const char* buffer);

	BOOL DoGSCallLuaFunction(UINT32 dwGSSessionID, char* pcszScriptName, char* pcszFuncName, INT32 nValue1, INT32 nValue2, INT32 nValue3);

	BOOL DoGSJoinBattle(INT32 dwGSSessionID, UINT32 dwCliSessionID, UINT32 dwRoleID, UINT32 dwSceneTempID, UINT32 dwSceneID, UINT8 bySide);

    // guild
    BOOL DoGSPreCreateGuild(INT32 dwGSSessionID, UINT32 dwRoleID, const char *pcszGuildName, INT32 nIsNeedToConsume);
    BOOL DoGSRoleAddGuildNtf(CMsGuild *pMsGuild);
    BOOL DoGSDeleteGuildNtf(UINT32 dwGuildID);
    BOOL DoGSGuildAddMemberNtf(UINT32 dwRoleID, INT32 nPosition, UINT32 dwGuildID);
    BOOL DoGSGuildDelMemberNtf(UINT32 dwRoleID, UINT32 dwGuildID, UINT32 dwCD);
    BOOL DoGSSyncGuildDataNtf(UINT32 dwGSSessionID, CMsGuild *pMsGuild);
    BOOL DoGSSyncGuildAttrNtf(UINT32 dwGuildID, INT32 nAttrType, UINT32 dwAttrValue);
    BOOL DoGSGuildSyncVariableNtf(UINT32 dwGuildID, INT32 nIndex, INT32 nValue);
    BOOL DoGSGuildDrawSalary(INT32 dwGSSessionID, UINT32 dwRoleID, INT32 nSalary);
    BOOL DoGSGuildAddDiplomat(UINT8 byType, UINT32 dwGuildID, UINT32 dwTargetGuildID);
    BOOL DoGSGuildDelDiplomat(UINT8 byType, UINT32 dwGuildID, UINT32 dwTargetGuildID);
    BOOL DoGSGuildPrePushItemAck(INT32 dwGSSessionID, UINT32 dwRoleID, UINT16 wSourceConSlot, UINT16 wSourceSlot, UINT8 byTargetConSlot, UINT8 byTargetSlot);
    BOOL DoGSGuildPrePopItemAck(INT32 dwGSSessionID, UINT32 dwRoleID, UINT16 wConSlot, UINT16 wSlot, UINT8 byConSlot, UINT8 bySlot);
    BOOL DoGSGuildPopItemAck(INT32 dwGSSessionID, UINT32 dwRoleID, UINT16 wConSlot, UINT16 wSlot, INT32 nLength, const char *pcszBuffer);
    BOOL DoGSGuildUpgradeBuildingNtf(UINT32 dwGuildID, UINT64 qwNameID, INT32 nType, INT32 nLevel);
    BOOL DoGSGuildUpdateBuilding(UINT32 dwGuildID, UINT64 qwNameID, INT32 nType, INT32 nLevel);
    BOOL DoGSGuildDelBuilding(UINT32 dwGuildID, UINT64 qwNameID, INT32 nType);
    BOOL DoGSGuildUpdateWelfareID(UINT32 dwGuildID, INT32 nType, INT32 nLevel);
    BOOL DoGSGuildUpdateState(UINT32 dwGuildID, INT32 nState);
    BOOL DoGSGuildChangePosition(UINT32 dwGuildID, UINT32 dwRoleID, INT32 nPosition);
    BOOL DoGSGuildPreOpenDungeonAck(INT32 dwGSSessionID, UINT32 dwTemplateID, UINT32 dwOwnerID, UINT32 dwLeaderID, INT32 nConsumeMoney);
    BOOL DoGSGuildEnterDungeon(INT32 dwGSSessionID, UINT32 dwTemplateID, UINT32 dwRoleID, UINT32 dwDungeonLeaderID);
    BOOL DoGSGuildSyncWarRelation(UINT32 dwIntruderID, UINT32 dwDefenderID);
    BOOL DoGSGuildSyncWarCharacter(UINT32 dwGuildID, INT32 nCharacter);
    BOOL DoGSGuildChangeRes(UINT32 dwNpcID, UINT32 dwGuildID, BOOL bAdd, INT32 nResType, INT32 nCount, INT32 nCtxType);
    BOOL DoGSGuildWarEnd(UINT32 dwDefenderID);
    BOOL DoGSGuildSyncBuildingStateNtf(UINT32 dwGuildID, UINT64 qwNameID, UINT32 dwReviveTime);
    BOOL DoGSGuildSyncMemberSalaryNtf(UINT32 dwGuildID, UINT32 dwRoleID, INT32 nSalary);
    BOOL DoGSSyncRoleSocialData(MS_ONLINE_ROLE_DATA *pstOnlineRoleData);
    BOOL DoGSGuildAchievementReward(INT32 dwGSSessionID, UINT32 dwRoleID, INT32 nID);
	BOOL DoGSEnrollSabac(UINT32 dwGuildID, UINT32 dwEnrollTime);
	BOOL DoGSOccupySabac(UINT32 dwOldGuildID, UINT32 dwNewGuildID);

    // arena
    BOOL DoGSJumpArenaScene(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwSceneTempID, UINT32 dwSceneID, UINT8 bySide);
    BOOL DoGSArenaReward(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwItemID, INT32 nMoney);

    BOOL DoGSCallGMCommand(UINT32 dwRoleID, const char *pcszGMCommand);

    // shield
    BOOL DoGSShield(INT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwTargetRoleID, char *pTargetRoleName);

    // gm
    BOOL DoGSSyncGMData(INT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwForbidChatTime);

	// statistic
	BOOL DoGSUpdateStatisticVariable(INT32 dwGSSessionID, UINT32 dwID, UINT32 dwType, UINT32 dwIndex, INT32 nValue);

    // drop limit
    BOOL DoGSDropLimit(UINT32 dwGSSessionID, INT32 nItemID, INT32 nItemCount);
    BOOL BroadcastGSDropLimit(INT32 nItemID, INT32 nItemCount);

    // auction
    BOOL DoGSAuctionSell(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT8 byConSlot, UINT8 byItemSlot, UINT8 byAuctionTimeType, UINT8 byOpen, INT64 llPrice, INT64 llBuyoutPrice, INT64 llDepositePrice);
    BOOL DoGSAuctionBuy(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwAuctionID, INT64 llBidPrice, INT64 llAuctionPrice, INT64 llDepositPrice, UINT8 byBuyType);
    BOOL DoGSAuctionPay(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwAuctionID, INT64 llPrice);

    // exchange
    BOOL DoGSExchangeAddOrder(UINT32 dwGSSessionID, UINT32 dwRoleID, INT32 nItemIDRequire, INT32 nItemCountRequire,
        UINT8 byOrderType, INT32 nPriceOrder, INT32 nCountOrder);
    // adventure
    BOOL DoGSAdventureAward(UINT32 dwGSSessionID, INT32 nServerGroup, UINT32 dwRoleID, INT32 nAdventureID);

	// achievement
    BOOL DoGSCompleteAchievement(UINT32 dwGSSessionID, UINT32 dwRoleID, INT32 nAchID);

    BOOL DoGSQueryRoleLocation(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwClientSessionID, UINT32 dwTargetRoleID, BOOL bFromItem);
    BOOL DoGSQueryRoleLocationAck(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwClientSessionID, 
        INT32 nSceneTempID, INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ, BOOL bFromItem);
    BOOL DoGSTakeRole(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwClientSessionID, 
        INT32 nSceneTempID, INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ);
	BOOL DoGSArrestRole(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT32 dwClientSessionID, INT32 nDuration);

    BOOL DoGSRealMoneyBuySuccess(UINT32 dwGSSessionID, UINT32 dwRoleID, INT32 nItemID, INT32 nStackCount, INT32 nItemCount, INT32 nOriginalPrice, const char* szGiver, UINT32 dwGiverID);

    BOOL DoGSFcmState(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT8 byFcmState);

    BOOL DoGSFreeMode(UINT32 dwGSSessionID, UINT32 dwRoleID, UINT8 byFreeMode);

    BOOL DoGSAward(UINT32 dwGSSessionID, UINT32 dwRoleID, INT32 nItemID, INT32 nItemCount);

	BOOL DoGSSyncServerVariable(UINT32 dwGSSessionID, INT32 nServerGroup);
	BOOL DoGSUpdateServerVariable(INT32 nServerGroup, UINT64 qwKey, INT32 nValue);

	BOOL DoGSUpdateAverageLevel(UINT32 dwGSSessionID, INT32 nAverageLevel[]);

    BOOL DoGSGetBlackMarketLimitInfo(INT32 dwGSSessionID, UINT32 dwRoleID);
    BOOL DoGSCheckBlackMarketProduct(INT32 dwGSSessionID, UINT32 dwRoleID, INT32 nProductID, INT32 nResult, INT32 nCount);

    BOOL DoGSAddExerciseTime(INT32 dwGSSessionID, UINT32 dwRoleID, INT32 nHour, INT32 nResult);

    // ===== 下面全是自己新加代码 =====

    // 玩家查询元宝
    BOOL DoGSQueryYuanBao(INT32 dwGSSessionID, UINT32 dwCliSessionID, UINT32 dwRoleID);
    
    // 玩家购买商城物品
    BOOL DoGSRoleRealMoneyShopBuyItemReq(INT32 dwGSSessionID, UINT32 dwCliSessionID, CHAR* pcszRoleName, UINT32 dwRoleID, INT32 nTotalCost, INT32 nItemID, INT32 nItemCount);

    // 玩家购买点卡
    BOOL DoGSCustomRoleBuyTime(INT32 dwGSSessionID, UINT32 dwCliSessionID, UINT32 dwRoleID, UINT32 dwBuyTimeCost);

    /************************************************************************/
    // To LS
    BOOL DoLSRegisterAck(void);
    BOOL DoLSLoginQueryAck(UINT32 dwClientSessionID, UINT32 dwError, CHAR* szUserName);

	/************************************************************************/
	// To BS
	BOOL DoBSRegisterAck(void);

	/************************************************************************/
	// To DL
	BOOL DoDLRegisterAck(void);
	BOOL DoDLReload(void);

	BOOL DoDLChatMessage(UINT32 dwTime, INT32 nGroupID, UINT32 dwSrcID, UINT32 dwTargetID, const char* pcszMessage, INT32 nMessageSize);

    BOOL DoDLLogItem(UINT32 dwRoleID, INT32 nGroupID, INT64 Guid,
        INT32 nTemplateID, INT32 nItemCount, INT32 nReason, INT32 nAction, UINT64 qwUserDefinedID);
    BOOL DoDLStatItem(INT32 nGroupID, INT32 nItemTemplateID, INT32 nItemCount, INT32 nAction);

	BOOL DoDLCreateTeam(UINT32 dwTime, INT32 nGroupID, UINT32 dwSrcID, UINT32 dwTeamID);
	BOOL DoDLJoinTeam(UINT32 dwTime, INT32 nGroupID, UINT32 dwSrcID, UINT32 dwTeamID, UINT32 dwLeaderID, INT32 nMemberCount);
	BOOL DoDLLeaveTeam(UINT32 dwTime, INT32 nGroupID, UINT32 dwSrcID, UINT32 dwTeamID, UINT32 dwLeaderID, INT32 nMemberCount);
	BOOL DoDLBreakDwonTeam(UINT32 dwTime, INT32 nGroupID, UINT32 dwTeamID);	

	BOOL DoDLEnterScene(UINT32 dwTime, INT32 nGroupID, INT32 nSceneID, INT32 nSceneTemplateID, UINT32 dwRoleID);	
	BOOL DoDLLeaveScene(UINT32 dwTime, INT32 nGroupID, INT32 nSceneID, INT32 nSceneTemplateID, UINT32 dwRoleID);	

	BOOL DoDLLogin(UINT32 dwTime, INT32 nGroupID, const char* szUserName, UINT32 dwIP);
	BOOL DoDLLogout(UINT32 dwTime, INT32 nGroupID, const char* szUserName, UINT32 dwIP);

    BOOL DoDLGmCommand(INT32 nGroup, UINT32 dwRoleID, const char * pcszRoleName, UINT32 dwGameTime, const char* szCommand, BOOL bResult);

	BOOL DoDLRealMoney2Money02(UINT32 dwGameTime, UINT8 byGroup, INT32 nMoneyCount);
	BOOL DoDLRealMoney2Item(UINT32 dwGameTime, UINT8 byGroup, INT32 nMoneyCount);

    BOOL DoDLKickUser(INT32 eKickType, const char* pcszUserName, UINT32 dwClientSessionID, const char* pcszRoleName, UINT32 dwRoleID, 
        const char* pcszFileName, INT32 nLineNum, const char* pcszFuncName);

    BOOL DoDLGuildEvent(INT32 nGroupID, UINT32 dwGameTime, INT32 dwGuildID, INT32 nActionType, UINT32 dwValue1, UINT32 dwValue2, UINT32 dwValue3, UINT32 dwValue4, BOOL bGM = FALSE);
    BOOL DoDLGuildChest(INT32 nGroupID, UINT32 dwGameTime, INT32 dwGuildID, INT32 nValue, INT32 nReason);
    BOOL DoDLGuildStat(UINT32 dwGameTime, GUILD_STAT *pStatList);

    BOOL DoDLBillingRequest(
        INT32 nGroupID, INT32 nAction, UINT32 dwRpcID,
        const char* szUserName, const char* szUserName2,
        const char* szUniqueID, const char* szUniqueID2,
        UINT32 dwRoleID, UINT32 dwRoleID2,
        UINT64 qwOrderID, UINT64 qwOrderID2,
        INT32 nAmount, INT32 nParam);
    BOOL DoDLBillingResult(INT32 nGroupID, INT32 nAction, UINT32 dwRpcID, const char* szUniqueID, INT32 nResult);

	/************************************************************************/

    /************************************************************************/
    // To DB
    BOOL DoDBRegisterAck(void);

    BOOL DoDBCreateRoleAck(INT32 dwClientSessionID, CHAR szBaseData[]);
    BOOL DoDBCanDeleteRoleAck(INT32 dwClientSessionID, UINT32 dwRoleID, INT32 nResult);
    BOOL DoDBDeleteRoleAck(INT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoDBLeaveDB(INT32 dwClientSessionID);

    BOOL DoDBClearCache(UINT32 dwRoleID, UINT32 dwTLUserID, UINT32 dwCmdSerialID);
	BOOL DoDBGMCommand(const char* pcszGMCommand);

	/************************************************************************/
	// To MM
	BOOL DoMMRegisterAck(void);

    /************************************************************************/
    // To Client
    //BOOL DoRoleLogout(UINT32 dwRoleID);
    BOOL DoErrorNotify(UINT32 dwClientSessionID, INT32 nErrorCode, INT32 nParam1, INT32 nParam2);
	BOOL DoClientQueueInfo(UINT32 dwClientSessionID, INT32 nTotal, INT32 nSelfPos);
    BOOL DoClientSyncRoleInfo(UINT32 dwClientSessionID, MS_ROLE_DATA* pRoleData, const char* pGuildName, UINT32 dwCRC);

    // 组队
	BOOL DoClientTeamJoin(UINT32 dwClientSessionID, CTeam* poTeam);
    BOOL DoClientTeamAnswer(UINT32 dwClientSessionID, UINT8 byType, UINT32 dwRequestRoleID, const CHAR* pcszRoleName);
    BOOL DoClientTeamLeave(UINT32 dwClientSessionID, UINT32 dwTeamID);
    
    BOOL DoClientTeamAddMember(MS_ONLINE_ROLE_DATA* poNewMember, CTeam* poTeam);
    BOOL DoClientTeamChangeInfo(CTeam* poTeam);
    BOOL DoClientRemoveMember(UINT32 dwDelMemberID, CTeam* poTeam);
    BOOL DoClientTeamSyncMemberInfo(MS_ONLINE_ROLE_DATA* pstRoleData, INT32 nX, INT32 nY, INT32 nZ, CTeam* poTeam);
	BOOL DoClientTeamSyncMemberState(UINT32 dwRoleID, UINT8 byState, CTeam* poTeam);

	BOOL DoClientActivityQueryTeam(UINT32 dwClientSessionID, BOOL bActivity, INT32 nActivityID, INT32 nPage);
	BOOL DoClientActivityChangeDungeon(CTeam* pTeam, UINT32 dwActivityType, INT32 nActivityID, BOOL bResult);

    BOOL DoClientTeamSyncTeamInfo(UINT32 dwTeamID, const char* szTeamName, UINT8  byAuctionItemColorLimit, UINT32 dwLeaderID, MS_ONLINE_ROLE_DATA* pstRoleData);

    // 
    BOOL DoClientSelfInfo(MS_ONLINE_ROLE_DATA* pstOnlineRole);
    BOOL DoClientFriendList(MS_ONLINE_ROLE_DATA* pstOnlineRole);
    BOOL DoClientFriendInfoChange(UINT32 dwClientSessionID, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    BOOL DoClientFriendInfoChange(UINT32 dwClientSessionID, MS_ROLE_DATA* pstRole);
    BOOL DoClientFriendOffline(UINT32 dwClientSessionID, MS_ROLE_DATA* pstRole);
    BOOL DoClientFriendAdd(UINT32 dwClientSessionID, UINT32 dwRoleID, const char* szRoleName, UINT8 bMutual);
    BOOL DoClientFriendDel(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoClientFriendAddedBy(UINT32 dwClientSessionID, UINT32 dwRoleID, const char* szRoleName);
    BOOL DoClientFriendDeletedBy(UINT32 dwClientSessionID, UINT32 dwRoleID, const char* szRoleName);
    BOOL DoClientPersonalEnemyAdd(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoClientPersonalEnemyDel(UINT32 dwClientSessionID, UINT32 dwRoleID);

    BOOL DoClientChatMessageToTarget(UINT32 dwTargetSessionID, const char* pSrcName, UINT32 dwSrcID, UINT32 dwTargetID, 
        UINT32 dwLocation, const char* pcszMessage, INT32 nServerGroupID);
	BOOL DoClientChatMessage(const char* pSrcName, UINT32 dwSrcID, UINT32 dwTargetID, UINT32 dwLocation, 
		const char* pcszMessage, INT32 nServerGroupID, BOOL bGM);
	BOOL DoClientPublishQuest(UINT32 dwClientSessionID, UINT32 dwMasterRoleID, INT32 nQuestID);

	BOOL DoClientQueryLineAck(UINT32 dwClientSessionID, UINT32 dwSceneTempID, UINT32 dwLineCount, UINT32* plstLineID);
    // master
    BOOL DoClinetMstTwitterAck(UINT32 dwClientSessionID, UINT8 byTwitter);
    BOOL DoClientMstHelloTeacher(UINT32 dwClientSessionID, UINT32 dwRoleID, UINT8 byLevel);
    BOOL DoClientMstGetRecruitList(UINT32 dwClientSessionID, MS_ONLINE_ROLE_DATA *pstOnlineRole);
    //BOOL DoClientMstRecruitAck(UINT32 dwClientSessionID, UINT32 dwType);
    BOOL DoClientMstGetSoloList(MS_ONLINE_ROLE_DATA *pstOnlineRole);

    BOOL DoClientMasterInfo(UINT32 dwClientSessionID, UINT32 dwRoleID, MS_TEACHER_DATA &data);
    BOOL DoClientMasterSyncLvl(MS_TEACHER_DATA &data, UINT32 dwRoleID, INT32 nLevel);
    
    BOOL DoClientMstStudSubmitAppAck(UINT32 dwClientSessionID, UINT32 dwMasterID);
    BOOL DoClientMstStudSubmitAppNtf(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstAgreeStudAppAck(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstRefuseAppAck(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstRefuseAppNtf(UINT32 dwClientSessionID, UINT32 dwTeacherID);
    BOOL DoClientMstCancelAppAck(UINT32 dwClientSessionID, UINT32 dwTeacherID);
    BOOL DoClientMstCancelAppNtf(UINT32 dwClientSessionID, UINT32 dwStudentID);

    BOOL DoClientMstTeacherSubmitAppAck(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstTeacherSubmitAppNtf(UINT32 dwClientSessionID, INT32 nAppSourceType, UINT32 dwTeacherID, INT32 nLevel, INT32 nMasterExp);
    BOOL DoClientMstAgreeTeacherAppAck(UINT32 dwClientSessionID, UINT32 dwTeacherID);
    BOOL DoClientMstRefuseTeacherAppAck(UINT32 dwClientSessionID, UINT32 dwTeacherID);
    BOOL DoClientMstRefuseTeacherAppNtf(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstCancelTeacherAppAck(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstCancelTeacherAppNtf(UINT32 dwClientSessionID, UINT32 dwTeacherID);

    BOOL DoClientMstAddStudentNtf(MS_TEACHER_DATA &data, UINT32 dwStudentID);
    BOOL DoClientMstDelStudentNtf(MS_TEACHER_DATA &data, UINT32 dwStudentID);
    BOOL DoClientMstClearInfo(UINT32 dwClientSessionID);
    BOOL DoClientMstCZLevel(UINT32 dwClientSessionID, UINT32 dwRoleID, INT32 nCZLevel);
    BOOL DoClientMstCZAck(UINT32 dwClientSessionID, UINT32 dwTargetRoleID);
    BOOL DoClientMstGrad(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstGradNtf(MS_TEACHER_DATA &data, UINT32 dwStudentID);

    BOOL DoClientMstLeaveTeacherAck(UINT32 dwClientSessionID);
    BOOL DoClientMstLeaveTeacherNtf(MS_TEACHER_DATA &data, UINT32 dwStudentID);

    BOOL DoClientMstFireStudentAck(UINT32 dwClientSessionID, UINT32 dwStudentID);
    BOOL DoClientMstFireStudentNtf(MS_TEACHER_DATA &data, UINT32 dwStudentID, UINT32 dwExceptRoleID);

    BOOL DoClientMailWriteSuccess(UINT32 dwClientSessionID);
    BOOL DoClientMailListRecv(UINT32 dwClientSessionID, CBaseList& lstMails, UINT32 dwMaxMailCount);
    BOOL DoClientMailRead(UINT32 dwClientSessionID, const MailInfo* mail);
    BOOL DoClientMailDeleteSuccess(UINT32 dwClientSessionID, UINT32 dwMailID);
    BOOL DoClientMailNewCount(UINT32 dwClientSessionID, CBaseList& lstMails);
    BOOL DoClientMailGetAttachAccess(UINT32 dwClientSessionID, UINT32 dwMailID);

	BOOL DoClientJoinBattleQueue(UINT32 dwClientSessionID);
	BOOL DoClientCancelJoinBattleAck(UINT32 dwClientSessionID, UINT32 dwCancelJoinRoleID);
    BOOL DoClientJoinBattleConfirmReq(UINT32 dwClientSessionID, UINT32 dwSceneTempID);

    // guild
    BOOL DoNSCreateGuild(UINT32 dwRoleID, const char *pcszGuildName, const char *pcszAnnounce, BOOL bConsumeItem);
    BOOL DoClientGuildQueryName(UINT32 dwClientSessionID, CMsGuild *poMSGuild, UINT32 dwCRC);
    BOOL DoClientCreateGuild(UINT32 dwClientSessionID, const char *pGuildName);
    BOOL DoClientViewGuildListAck(UINT32 dwClientSessionID, UINT8 byGroup, UINT8 byViewType, UINT32 dwLastGuildID);
    BOOL DoClientMoreGuildInfoAck(UINT32 dwClientSessionID, CMsGuild *poMSGuild);
    BOOL DoClientFindGuildAck(UINT32 dwClientSessionID, UINT8 byGroup, CMsGuild *pData, char *szLeaderName);
    BOOL DoClientGetGuildDataNtf(UINT32 dwClientSessionID, CMsGuild *pData, char *szLeaderName);
    BOOL DoClientApplyToJoinGuildAck(UINT32 dwClientSessionID, UINT32 dwGuildID);
    BOOL DoClientGetApplyGuildListAck(UINT32 dwClientSessionID, CMsGuild *pData);
    BOOL DoClientRevertGuildApplyAck(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoClientDelGuildApp(UINT32 dwClientSessionID, UINT32 dwGuildID);
    BOOL DoClientGuildAddMemberNtf(CMsGuild *pData, MS_ROLE_DATA &roleData, UINT8 byPosition, INT32 nNextSalary, UINT8 byFlag);
    BOOL DoClientGuildDelMemberNtf(CMsGuild *pMsGuild, UINT32 dwRoleID);
    BOOL DoClientBeInvitedToJoinGuild(UINT32 dwClientSessionID, UINT32 dwRoleID, char *pRoleName, char* pGuildName);
    BOOL DoCLientInviteToJoinGuildAck(UINT32 dwClientSessionID, char *pRoleName, INT32 nReplyType);
    BOOL DoClientDisbandGuildNtf(CMsGuild *pMsGuild);
    BOOL DoClientGuildNoticeChangeNtf(CMsGuild *pMsGuild);
    BOOL DoClientGuildForbidChatNtf(CMsGuild *pMsGuild, UINT32 dwRoleID, INT32 nOp);
    BOOL DoClientGuildChangePositionNtf(CMsGuild *pMsGuild, UINT32 dwRoleID, INT32 nPosition);
    BOOL DoClientGuildRoleLeaveNtf(CMsGuild *pMsGuild, UINT32 dwRoleID);
    BOOL DoClientGuildRoleLeaveAck(UINT32 dwClientSessionID, INT32 nLeaveType);
    BOOL DoClientGuildDemiseNtf(CMsGuild *pMsGuild, UINT32 dwOldLeaderID, UINT32 dwNewLeaderID);
    BOOL DoClientGuildContributeAck(UINT32 dwClientSessionID, INT32 nType, INT32 nValue);
    BOOL DoClientGuildAttrModifyNtf(CMsGuild *pMsGuild, INT32 nAttrType, UINT32 dwAttrValue);
    BOOL DoClientGuildApplyAllianceAck(UINT32 dwClientSessionID, UINT32 dwGuildID);
    BOOL DoClientGetApplyUnionListAck(UINT32 dwClientSessionID, CMsGuild *pMsGuild);
    BOOL DoClientGuildReplyUnionAppAck(UINT32 dwClientSessionID, UINT32 dwGuildID);
    BOOL DoClientGuildAddDiplomatNtf(UINT8 byType, CMsGuild *pMsGuild, UINT32 dwGuildID, UINT32 dwLastTime, UINT8 byLevel ,UINT8 byMemberCount, char * szGuildName);
    BOOL DoClientGuildDelDiplomatNtf(UINT8 byType, CMsGuild *pMsGuild, UINT32 dwGuildID);

    BOOL DoClientGuildNotifyNtf(CMsGuild *poMSGuild, INT32 nType, INT32 nRight);
    BOOL DoClientGuildChangeStorageRightNtf(CMsGuild *pMsGuild, INT32 nPosition, UINT16 wRight);
    BOOL DoClientGuildViewStorage(UINT32 dwClientSessionID, CMsGuild *pMsGuild, UINT8 byStorageTag);
    BOOL DoClientGuildStoraveEvent(UINT32 dwClientSessionID, CMsGuild *pMsGuild);
    BOOL DoClientGuildPushItemAck(UINT32 dwClientSessionID, INT32 nConSlot, INT32 nSlot, INT32 nItemSize, const char *pItemData);
    BOOL DoClientGuildPopItem(UINT32 dwClientSessionID, UINT8 byConSlot, UINT8 bySlot);
    BOOL DoClientGuildMoveItem(UINT32 dwClientSessionID, INT32 nSourceConSlot, INT32 nSourceItemSlot, INT32 nTargetConSlot, INT32 nTargetItemSlot);
    BOOL DoClientAddHistoryEventNtf(CMsGuild *pMsGuild, UINT8 byType, UINT32 dwParam1, UINT32 dwParam2, UINT32 dwParam3, UINT32 dwParam4, UINT32 dwOccurTime);
    BOOL DoClientAddStorageEventNtf(CMsGuild *pMsGuild, UINT8 byType, UINT32 dwRoleID, UINT32 dwOccurTime, INT32 nLength, const char *pcszItemBuffer);
    BOOL DoClientGuildMemberSalaryChange(UINT32 dwClientSessionID, UINT32 dwSalary);
    BOOL DoClientSyncSocialAttrNtf(CMsGuild *pMsGuild, UINT32 dwRoleID, UINT8 byLevel, UINT32 dwValue);
    BOOL DoClientGuildMoreHistoryAck(UINT32 dwClientSessionID, UINT32 dwGuildID);
    BOOL DoClientGuildMoreChestAck(UINT32 dwClientSessionID, UINT32 dwGuildID);
    BOOL DoClientGuildJoinGuildAck(UINT32 dwClientSessionID, const char *pcszGuildName);
    BOOL DoClientGuildUpgradeWelfareNtf(CMsGuild *pMsGuild, INT32 nType, INT32 nTime);
    BOOL DoClientGuildUpdateWelfareNtf(CMsGuild *pMsGuild, INT32 nType, UINT8 byLevel);
    BOOL DoClientGuildCancelWelfareUpgradeNtf(CMsGuild *pMsGuild, UINT32 dwID);
    BOOL DoClientGuildUpgradeBuildingNtf(CMsGuild *pMsGuild, UINT64 qwNameID, INT32 nType, INT32 nTime);
    BOOL DoClientGuildUpdateBuildingNtf(CMsGuild *pMsGuild, UINT64 qwNameID, INT32 nType);
    BOOL DoClientGuildCancelBuildingUpgradeNtf(CMsGuild *pMsGuild, UINT64 qwNameID, INT32 nType);
    BOOL DoClientGuildDelBuildingNtf(CMsGuild *poMSGuild, UINT64 qwNameID, INT32 nType);
    BOOL DoClientGuildGetDungeonListAck(MS_ONLINE_ROLE_DATA *pstonlineRoleData, CMsGuild *pMsGuild);
    BOOL DoClientGuildOpenDungeonAck(UINT32 dwClientSessionID);
    BOOL DoClientGuildDungeonAwardNtf(SCENE_INFO *poMsScene, UINT32 dwOwnerID, INT32 nCount, UINT32 arrItemID[], UINT32 arrItemCount[]);
    BOOL DoClientBattleAchievementNtf(CMsGuild *pMsGuild, INT32 nNum, GUILD_WAR_PERSONAL_ACHIEVEMENT arrInfo[]);
    BOOL DoClientGuildSyncBuildingStateNtf(CMsGuild *poMsGuild, UINT64 qwNameID, UINT32 dwReviveTime);
    BOOL DoClientGuildSyncWarCDNtf(CMsGuild *poMsGuild, UINT32 dwCD);
    BOOL DoClientGuildMatchGuildAck(UINT32 dwClientSessionID, CMsGuild *poMatchingGuild);
    BOOL DoClientGuildAchievementAck(UINT32 dwClientSessionID, CMsGuild *poMsGuild);

    BOOL DoClientGuildJoinWarNtf(CMsGuild *poGuild, INT32 nWarCharacter, UINT32 dwTargetGuildID);

	BOOL DoClientEnrollSabac(INT32 nServerGroup, UINT32 dwGuildID);
	BOOL DoClientOccupySabac(UINT32 dwCliSessionID, INT32 nServerGroup, UINT32 dwOldGuildID, UINT32 dwNewGuildID);
	BOOL DoClientErectStatue(INT32 nServerGroup, UINT32 dwCliSessionID);
	BOOL DoClientSabacWinnerLogin(MS_ONLINE_ROLE_DATA* pOnlineRoleData);

    // arena
    BOOL DoClientArenaGetDataAck(UINT32 dwClientSessionID, UINT64 qwTotalFund, UINT8 byMaxVictoryTimes, UINT8 byRank, INT32 nRewardMoney, UINT32 dwRewardItemID);
    BOOL DoClientArenaEnd(UINT32 dwClientSessionID);
    BOOL DoClientArenaMatchBeginNtf();

    // auction
    BOOL DoClientAuctionSearchResult(UINT32 dwClientSessionID, ExternalMessage::FLEX_MESSAGE_HEADER* pMsg);
    BOOL DoClientAuctionQuery(UINT32 dwClientSessionID, Auction* pAuction, MS_ROLE_DATA* pSellerRole);
    BOOL DoClientAuctionSell(UINT32 dwClientSessionID, Auction* pAuction);
    BOOL DoClientAuctionCancelSell(UINT32 dwClientSessionID, UINT32 dwAuctionID);
    BOOL DoClientAuctionBuy(UINT32 dwClientSessionID, Auction* pAuction);
    BOOL DoClientAuctionFinished(UINT32 dwClientSessionID, UINT32 dwAuctionID, UINT8 bySuccess);
    BOOL DoClientAuctionListMySelling(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoClientAuctionListMyBuying(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoClientAuctionPayLeftMoney(UINT32 dwClientSessionID, UINT32 dwAuctionID);

    // exchange
    BOOL DoClientExchangeAddOrder(UINT32 dwClientSessionID, Order* pOrder);
    BOOL DoClientExchangeCancelOrder(UINT32 dwClientSessionID, UINT64 qwOrderID);
    BOOL DoClientExchangeListPrices(UINT32 dwClientSessionID, UINT8 byGroupID);
    BOOL DoClientExchangeListMyOrders(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoClientExchangeListMyLogs(UINT32 dwClientSessionID, UINT32 dwRoleID);

    // real money shop
    BOOL DoClientSyncRealMoney(UINT32 dwClientSessionID, INT32 nBalance);
    BOOL DoClientRealMoneyBuy(UINT32 dwClientSessionID, INT32 nItemID, INT32 nMoneyCost);
    BOOL DoClientRealMoneyShopLog(MS_ONLINE_ROLE_DATA* pstOnlineRole);
    BOOL DoClientSaleInfo(UINT32 dwClientSessionID);

	// ranklist
	BOOL DoQueryRanklist(MS_ONLINE_ROLE_DATA* pOnlineRole, INT32 nRankListType, INT32 nPageNum);

    // fcm
    BOOL DoClientFcmState(UINT32 dwClientSessionID, INT32 nOnlineMinutes, INT32 nOfflineMinutes);

    // time
    BOOL DoClientTimeInfo(UINT32 dwClientSessionID, INT32 nPlayTimeLeft);
    BOOL DoClientBuyTime(UINT32 dwClientSessionID, UINT8 bAuto, UINT8 byResult);
    BOOL DoClientFreeMode(UINT32 dwClientSessionID, UINT8 bFreeMode);

    /************************************************************************/
    // To NS 
	BOOL DoNSMessageVersion(void);
    BOOL DoNSNewName(INT32 nNameType, UINT32 dwSessionID, const char* szName, const char* UserData, UINT32 dwUserDataLen);

private:
    /************************************************************************/
    // From All
    void OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    
    // From GD
	void OnGDClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGDCommand(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // From GM
    void OnGMRegisterAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMClearRoleCache(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMUnlockRole(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMQueryRoleData(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMForbidChat(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMFreezeRole(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMKickRole(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMSendMail(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMAnnounce(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMGetAnnounceList(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMDelAnnounce(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMExeGMStr(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMDelMail(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMCheckRoleFreeze(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMGetExchangePrice(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMGetExchangePriceDetail(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMAddSystemOrder(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMCancelSystemOrder(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMGetExchangeLimit(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGMSetExchangeLimit(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    
    /************************************************************************/
    // From GT
    void OnGTRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGTEnterGate(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTQueryScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTClientShutDown(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTReturnSelectRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTChangeGSAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTClientMsg(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTCheckNewName(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    /************************************************************************/
    // From GS
	void OnGSRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSBroadcastGroupClient(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSPreEnterGSAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSEnterGS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSQueryScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSLeaveGSAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSCreateSceneAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSDestroySceneAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSCloseScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSTeamSyncMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    
	void OnGSChatMessage(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSLeaveTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSClearTeamDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSPublishQuest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSUpdateRoleInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // mail
    void OnGSMailCostCheck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSSendSystemMail(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSSendSystemMailWithSimpleAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSSendSystemMailWithBufferAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSMailGetAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	// call lua_function
	void OnGSCallLuaFunction(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // master
    void OnGSSubmitTeacherAppAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSAgreeTeacherAppAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSSubmitStudAppAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSAgreeStudAppAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSSyncMasterExp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSMasterCZ(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSTryToFindTeacher(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSMasterTwitter(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // guild
    void OnGSGuildCreate(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSPreCreateGuildAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildDrawSalary(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildContribute(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildViewStorage(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildPrePushItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildPushItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildPrePopItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildPopItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildCreateBuilding(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildUpgradeBuilding(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildDelBuilding(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildPreOpenDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildOpenDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildEnterDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildCloseDungeonCommission(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSGuildChangeRes(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildEndWar(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildChangeBuildingState(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    //void OnGSGuildBattleScore(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildAchievementReward(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSGuildLeaveGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSEnrollSabac(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSOccupySabac(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSErectStatue(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    //void OnGSGuildMoveItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // arena
    void OnGSArenaSyncData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSArenaJoinSeason(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSArenaMatch(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSArenaWin(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSArenaDefeated(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSArenaReward(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    
    // personal enemy
    void OnGSAddKillList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // gm
    void OnGSGMLog(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSCSCommandAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // drop limit
    void OnGSDropLimit(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // auction
    void OnGSAuctionSell(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSAuctionBuy(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSAuctionPay(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // exchange
    void OnGSExchangeAddOrder(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// ranklist
	void OnGSUpdateRankListData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSUpdateRankListNode(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // adventure
    void OnGSAdventureTrigger(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// award
	void OnGSSendAwardToUmp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSQueryRoleLocation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSQueryRoleLocationAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSTakeRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSRecallTeamMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSSetServerVariable(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSGetBlackMarketLimitInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSCheckBlackMarketProduct(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSAddExerciseTime(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSFreezeLogin(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSTemporaryCharge(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSQueryRealMoneyAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnGSRoleRealMoneyShopBuyItemAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    /************************************************************************/
    // From LS
    void OnLSRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnLSReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnLSCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnLSLoginQueryReq(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    /************************************************************************/
	/************************************************************************/
	// From DL
	void OnDLRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnDLReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnDLCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	/************************************************************************/

    // From DB
    void OnDBRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnDBCreateRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBCanDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBDeleteRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBLeaveDBAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBClearRoleCacheAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    
    /************************************************************************/
	// From BS
	void OnBSRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnBSCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnBSReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    /************************************************************************/
    // From NS
    void OnNSNewNameResult(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	/************************************************************************/
	// From MM
	void OnMMRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMMCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMMReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // From Client
    void OnClientQueryRoleInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // 组队
    void OnClientTeamJoin(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientTeamLeave(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientTeamAnswer(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientTeamChangeInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    void OnClientActivityTeamChangeDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientActivityTeamQueryTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientActivityTeamRemove(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // c2m_team_query, c2m_team_invite
    void OnClientTeamQuery(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientTeamInvite(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // 好友
    void OnClientFriendAdd(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientFriendDel(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientFriendChangeGroup(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientChangeInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientFriendChat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientPersonalEnemyAdd(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientPersonalEnemyDel(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

	void OnClientChatMessage(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

	void OnClientQueryLineReq(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

	//battle
	void OnClientJoinBattle(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
	void OnClientCancelJoinBattleReq(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
	void OnClientJoinBattleConfirm(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);


    // master
    void OnClientMstTeacherIgnore(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstGetRecruitList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstGetSoloList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    void OnClientMstStudSubmitApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstAgreeStudApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstRefuseStudApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstCancelStudApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    void OnClientMstTeacherSubmitApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstAgreeTeacherApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstRefuseTeacherApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstCancelTeacherApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    void OnClientMstLeaveTeacher(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstFireStud(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstCZ(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMstGrad(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);


    //void OnClientMstGetMasterInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    //void OnClientMstCongUpLevel(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    // mail
    void OnClientMailWrite(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMailListRecv(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMailRead(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMailDelete(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMailGetAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // guild
    void OnClientGuildQueryName(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientViewGuildList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientMoreGuildInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientFindGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientApplyToJoinGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGetApplyGuildList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientRevertGuildApply(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientInviteToJoinGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientRevertGuildInvitation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientDisbandGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildNoticeChange(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildAnnounceChange(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildForbidChat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildChangePosition(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildLeave(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildBanishRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildDemise(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildDiplomatApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGetApplyUnion(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientReplyUnionApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientCancelAlliance(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientChangeStorageRight(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildMoveItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildMoreHistory(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildMoreChest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildUpgradeWelfare(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildCancelWelfareUpgrade(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    //void OnClientGuildUpgradeBuilding(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildCancelBuildingUpgrade(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    //void OnClientGuildDelBuilding(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildGetDungeonList(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildDeclareWar(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    void OnClientGuildAchievement(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientGuildActivity(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // auction
    void OnClientAuctionSearchType(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionSearch(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionQuery(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionSell(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionCancelSell(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionBuy(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionListMySelling(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionListMyBuying(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientAuctionPayLeftMoney(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // exchange
    void OnClientExchangeAddOrder(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientExchangeCancelOrder(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientExchangeListPrices(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientExchangeListMyOrders(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientExchangeListMyLogs(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // real money shop
    void OnClientCheckRealMoney(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientCheckRealMoneyShopData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientRealMoneyBuy(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientRealMoneyShopLog(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    void OnClientSaleInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // arena
    void OnClientArenaGetData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // shield
    void OnClientShield(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    void OnClientGMCommand(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // gm
    //void OnGMToolLogin(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    //void OnGMToolExecuteCommand(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    //void OnGMLogItem(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
    //void OnGMToolTest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// ranklist
    void OnClientQueryRanklist(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

	// award
    void OnClientAwardUseNumber(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // time
    void OnClientBuyTime(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

	void OnClientChangeRecallState(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // c2m_dynamic_auth
    void OnDynamicAuth(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

    // c2m_arena_fund
    void OnArenaFund(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);

private:
	BOOL _TryLoginQueryScene(MS_ONLINE_ROLE_DATA* pstOnlineRole, UINT32 dwRoleID, const SCENE_DATA* pcSceneData);
    BOOL _LoginQuerySceneProc(MS_ONLINE_ROLE_DATA* pstOnlineRole, UINT32 dwRoleID);

    INT32 _CreateNewScene(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, 
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection, INT32 nTargetState, INT32 nSceneID);
    INT32 _ChangeScene(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID, 
        INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);

    INT32 _HandleStaticScene(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID, 
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);
    INT32 _HandleDungeon(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID,
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);
	INT32 _HandleSoloDungeon(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID,
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);
	INT32 _HandleLineScene(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID,
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);
    INT32 _HandleGuildScene(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID,
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);
    INT32 _HandleBattlefield(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID,
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);
    INT32 _HandleArena(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID,
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);
	INT32 _HandleGuildDungeon(MS_ONLINE_ROLE_DATA* pstOnlineRole, INT32 nSceneTempID, INT32 nSceneID,
		INT32 nDestX, INT32 nDestY, INT32 nDestZ, INT32 nFaceDirection);

private:
    BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _SendNS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _SendGT(UINT32 dwGTSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _SendGS(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _SendLS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	BOOL _SendDL(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _SendDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	BOOL _SendBS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _SendClient(UINT32 dwClientSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _SendGM(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	BOOL _SendMM(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

    BOOL _BroadcastGT(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _BroadcastGS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _BroadcastAll(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

    BOOL _BroadcastScene(SCENE_INFO *poMsScene, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _BroadcastTeam(CTeam* poTeam, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _BroadcastGuild(CMsGuild *poMsGuild, PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, UINT32 exceptRoleID = 0, INT32 nOffset = 0);
    BOOL _BroadcastGuildCheckRight(CMsGuild *poMsGuild, PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, INT32 nRight, UINT32 exceptRoleID = 0, INT32 nOffset = 0);
    BOOL _BroadcastMaster(MS_TEACHER_DATA *pTeacherData, PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, UINT32 exceptRoleID = 0, INT32 nOffset = 0);
    BOOL _BroadcastGTClient(UINT32 dwGTSessionID, UINT32 dwClientSessionList[], INT32 nSessionCount, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _BroadcastGroupClient(UINT8 byGroupID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL _BroadcastAllClient(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

    void _CheckAllReady(void);

    BOOL _ShutdownClient(MS_USER* poUser);

	BOOL _DoLoadOrSyncInfo(MS_ONLINE_ROLE_DATA* pstRoleData);
    BOOL _DoLoginSyncInfo(MS_ONLINE_ROLE_DATA* pstRoleData);

    //BOOL _PreEnterScene(MS_ONLINE_ROLE_DATA* pstRoleData, SCENE_INFO* pstSceneInfo, UINT8 bySide);
    //BOOL _EnterScene(MS_ONLINE_ROLE_DATA* pstRoleData, SCENE_INFO* pstSceneInfo);
    //BOOL _LeaveScene(MS_ONLINE_ROLE_DATA* pstRoleData, SCENE_INFO* pstSceneInfo, BOOL bNormalLeave);
	
    BOOL _ProcessMonitorForRoleNumber(ISocketSession* pSocketSession);

	BOOL _CallDebugGMCommand(MS_ONLINE_ROLE_DATA* pstOnlineRole, const char* pcszCommand);
	BOOL _CallFinalGMCommand(MS_ONLINE_ROLE_DATA* pstOnlineRole, const char* pcszCommand, INT32 nGMFrom);

private: 
    struct STraverseOnlineRole
    {
        UINT32 (*dwGateSessionList)[MAX_CLIENT_SESSION_COUNT];
        UINT32*  dwClientSessionCount;
        BOOL operator()(UINT32 dwRoleID, MS_ONLINE_ROLE_DATA* poOnlineRole);
    } m_TraverseOnlineRole;

    struct CKickAllUserOnGT
    {
        UINT32      m_dwGTSessionID;
        BOOL operator()(UINT32 dwClientSessionID, MS_USER* poUser);
    };

    struct CKickAllRoleOnGS
    {
        UINT32      m_dwGSSessionID;
        BOOL operator()(UINT32 dwRoleID, MS_ONLINE_ROLE_DATA* pOnlineRole);
    };

    //struct CCheckRoleOnGS
    //{
    //    UINT32    m_dwGSSessionID;
    //    BOOL      m_bHasRole;
    //    BOOL operator()(UINT32 dwRoleID, MS_ONLINE_ROLE_DATA* pOnlineRole);
    //};

    struct CDeleteAllSceneOnGS
    {
        UINT32      m_dwGSSessionID;
        BOOL operator()(UINT64 dwSceneID, SCENE_INFO* pSceneInfo);
    };
private:
    INet*                               m_pNet;
    IPacketAllocator*                   m_pPacketAllocator;
    static CMessageHandler              ms_Instance;

    ISocketAcceptor*                    m_poGTAcceptor;
    ISocketAcceptor*                    m_poGSAcceptor;
    ISocketAcceptor*                    m_poLSAcceptor;
    ISocketAcceptor*                    m_poDBAcceptor;
	ISocketAcceptor*					m_poBSAcceptor;
	ISocketAcceptor*					m_poDLAcceptor;
	ISocketAcceptor*					m_poMMAcceptor;

	ISocketAcceptor*					m_poMonitorForRNAcceptor;

    InternalMessage::M2A_SERVER_INFO    m_ServerInfo;
	UINT32*								m_pCRCList;
	INT32								m_nCRCDataCount;

    typedef void (CMessageHandler::*INTERNAL_MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    INTERNAL_MESSAGE_FUNC               m_InternalMessageFuncList[InternalMessage::max_message_count];
    typedef void (CMessageHandler::*EXTERNAL_MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, MS_ONLINE_ROLE_DATA* pstOnlineRole);
    EXTERNAL_MESSAGE_FUNC               m_ExternalMessageFuncList[ExternalMessage::max_message_count];
};

#endif  // _MESSAGE_HANDLER_H_
