#ifndef _GS_MESSAGE_HANDLER_H_
#define _GS_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"

class CRole;
class IMessageNotifier;

#define NOTIFY_GD(__level__, __str_content__, ...)													\
    do																							\
	{																							\
        CGSMessageHandler::GetInstance().DoGDNotify(__level__, __str_content__, ##__VA_ARGS__);	\
	} while (0)

class CGSMessageHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
    virtual void OnConnected(ISocketSession* pSocketSession);
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
    CGSMessageHandler();
    virtual ~CGSMessageHandler();

    BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator, IMessageNotifier* pNotifier);
    BOOL UnInit(void);
    static CGSMessageHandler& GetInstance(void);

public:
    /************************************************************************/
    // To All
    BOOL DoAllPing(void);
    
    /************************************************************************/
    // To GD
    BOOL DoGDRegister(void);
	BOOL DoGDNotify(UINT8 byLevel, const char* szContent, ...);
    /************************************************************************/
    // To MS
    BOOL DoMSRegister(void);
    BOOL DoMSReady(void);
    BOOL DoMSCloseBeginAck(void);

    BOOL DoMSPreEnterGSAck(UINT32 dwClientSessionID, UINT32 dwRoleID, INT32 nErrCode);
    BOOL DoMSEnterGS(UINT32 dwClientSessionID, UINT32 dwRoleID, INT64 llMasterExp, UINT32 dwMasterCD, UINT32 dwGuildCD, UINT8 byGMLevel, UINT8 byTwitter, UINT32 dwMasterTwitterCD, const char* szSignature);
    BOOL DoMSLeaveGSAck(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoMSCreateSceneAck(UINT8 byGroupID, INT32 nSceneID, INT32 nSceneTempID, INT32 nErrCode);
    BOOL DoMSDestroySceneAck(UINT8 byGroupID, INT32 nSceneID, INT32 nSceneTempID, INT32 nErrCode);
    BOOL DoMSMailCostCheck(INT32 nResult, void* params);
    BOOL DoMSMailGetAttach(INT32 nResult, UINT32 dwMailID);
    BOOL DoMSPreCreateGuildAck(INT32 nResult, UINT32 dwRoleID, const char *pcszGuildName );
    BOOL DoMSQueryRoleLocationAck(UINT32 dwClientSessionID, UINT32 dwRoleID,
		INT32 nSceneTempID, INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ, BOOL bFromItem);

    BOOL DoMSGMLog(UINT32 dwTime, UINT32 dwRoleID, INT32 nResult, const char *pcszCmd);

    BOOL DoMSQueryRealMoneyRole(UINT32 dwClientSessionID, UINT32 dwRoleID, INT64 llRealMoney);

    // 玩家购买商城物品
    BOOL DoMSRoleRealMoneyShopBuyItemAck(UINT32 dwClientSessionID, INT32 nResult, UINT32 dwRoleID, INT32 nItemID, INT32 nItemCount, CHAR* pcszRoleName);

    /************************************************************************/
    // To DB
    BOOL DoDBRegister(void);
    BOOL DoDBLoadLockRoleData(UINT32 dwClientSessionID, UINT32 dwRoleID);
    BOOL DoDBSaveRoleData(CRole* poRole, BOOL bSaveToFile);
    BOOL DoDBUnlockRoleData(CRole* poRole);

    /************************************************************************/
    // To GT
    BOOL DoGTRegister(UINT32 dwGTSessionID);
    BOOL DoGTCloseClientSession(UINT32 dwCliSessionID, BOOL bLogout = FALSE);
    BOOL DoGTReturnSelectRole(UINT32 dwCliSessionID);

	/************************************************************************/
	// To DL
	BOOL DoDLRegister();

	BOOL DoDLCreateScene(UINT32 dwTime, INT32 nGroupID, INT32 nSceneID, INT32 nSceneTemplateID);
	BOOL DoDLDestoryScene(UINT32 dwTime, INT32 nGroupID, INT32 nSceneID, INT32 nSceneTemplateID);

private:
    /************************************************************************/
    // From All
    void OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    /************************************************************************/
    // From MS
    void OnMSRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSServerInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSAllReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSPreEnterGS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSEnterGSAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSLeaveGS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSCreateScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSDestroyScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSCloseScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSQuerySceneAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSChangeScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSSyncRSAKey(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    

	//battle
	void OnMSJoinBattle(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    //team
    void OnMSTeamNew(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSTeamAddMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSTeamRemoveMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSTeamChangeInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSRoomEnterDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // friend
    void OnMSChangeInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSFriendAdd(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSFriendDel(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSMstSyncState(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMstSyncData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMstCreateRelation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMstDelRelation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMstUpdateData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSSubmitTeacherApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMstAgreeTeacherApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSSubmitStudApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMstAgreeStudApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMstCZ(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSMailCostCheck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMailGetSimpleAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSMailGetBufferAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSCallLuaFunction(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);


    // guild 
    void OnMSPreCreateGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSRoleAddGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildAddMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildDelMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildSyncDataNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildDelete(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildAddDiplomat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildDelDiplomat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildSyncGuildAttrNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildSyncVariableNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildDrawSalary(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildPrePushItemAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildPrePopItemAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildPopItemAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildUpgradeBuildingNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildUpdateBuildingLevel(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildDelBuilding(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildSyncBuildingStateNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildUpdateWelfareID(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildUpdateState(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildChangePosition(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildPreOpenDungeonAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildEnterDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildSyncWarRelation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildSyncWarCharacter(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildChangeResAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildWarEnd(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    
    void OnMSGuildSyncMemberSalaryNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSSyncRoleSocialData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildAchievementReward(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSEnrollSabac(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSOccupySabac(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    //arena
    void OnMSJumpArenaScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSArenaReward(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
   
    // shield
    void OnMSShield(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // gm
    void OnMSSyncGMData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// statistic
    void OnMSUpdateStatisticVariable(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSCallGsGMCommand(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // drop limit
    void OnMSDropLimit(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // auction
    void OnMSAuctionSell(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
    void OnMSAuctionBuy(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
    void OnMSAuctionPay(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

	// achievement

    void OnMSCompleteAchievement(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // exchange
    void OnMSExchangeAddOrder(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // adventure
    void OnMSAdventureReward(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    void OnMSQueryRoleLocation(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
    void OnMSQueryRoleLocationAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
    void OnMSTakeRole(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
	void OnMSArrestRole(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // fcm
    void OnMSFcmState(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // FreeMode
    void OnMSFreeMode(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // award
    void OnMSAward(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

	void OnMSSpawnNpc(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

	void OnMSSyncServerVariable(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
	void OnMSUpdateServerVariable(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

	void OnMSUpdateAverageLevel(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    void OnMSGetBlackMarketLimitInfo(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);
    void OnMSCheckBlackMarketProduct(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    void OnMSAddExerciseTime(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);


    // ========== 下面是自己新加代码 begin

    // 玩家查询元宝
    void OnMSQueryRealMoneyRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // 商城购物成功
    void OnMSRealMoneyBuySuccess(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // 玩家购买商城物品
    void OnMSRoleRealMoneyShopBuyItemReq(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession);

    // 玩家购买点卡
    void OnMSCustomRoleBuyTimeReq(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // ========== 下面是自己新加代码 end

    /************************************************************************/
    // From DB
    void OnDBRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBLoadLockRoleDataAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBUnlockRoleDataAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnDBLoadLockRoleDataFailAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    /************************************************************************/
    // From GT
    void OnGTRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTRoleEnter(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGTClientMsg(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	
	// From DL
	void OnDLRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

private:
	inline BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendDL(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendGT(UINT32 dwGTSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

	BOOL _CallDebugGMCommand(CRole* poRole, const char* pcszCommand);
	BOOL _CallFinalGMCommand(CRole* poRole, const char* pcszCommand);

private:
    INet*                               m_pNet;
    IPacketAllocator*                   m_pPacketAllocator;
    IMessageNotifier*                   m_pNotifier;
    static CGSMessageHandler            ms_Instance;

    typedef void (CGSMessageHandler::*MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    MESSAGE_FUNC                        m_MessageFuncList[InternalMessage::max_message_count];
};

#endif  // _GS_MESSAGE_HANDLER_H_
