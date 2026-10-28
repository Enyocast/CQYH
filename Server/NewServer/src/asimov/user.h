#ifndef _USER_H_
#define _USER_H_

#include "string_def.h"
#include "team_def.h"
#include "guild_def.h"
#include "role_def.h"
#include "net.h"
#include "role_def.h"
enum USER_STATE
{
	usInvalid = 0,

	usUnconnected,
	usConnectingBS,
	usConnectingGT,
	usConnected,
	usSelectRole,
	usCreatingRole,
	usDeletingRole,
	usPlaying,

	usTotal
};

class CRole;
class QTreeWidgetItem;

typedef std::set<UINT16> CMsgSet;
typedef CMsgSet::iterator  CMsgSetItr;
typedef std::map<UINT32, CMsgSet> CSessionMsgMap;
typedef CSessionMsgMap::iterator CSessionMsgMapItr;
typedef struct rsa_st RSA;

class CUser
{
public:
	CUser();
	virtual ~CUser();

	BOOL Init(INet* poNet, IPacketAllocator* poPacketAllocator, INT32 nUserID, const char* pcszUserName,
		const char* pcszUserType, const char* pcszPassword, UINT8 byGroupID);
	BOOL UnInit(void);
public:
	void OnConnected();
	void OnBSConnected();
	void OnBSDisConnected();
	void OnDisconnected();
public:
	BOOL ConnectServer(UINT32 dwIP, UINT16 wPort, BOOL bConnectBS, BOOL bAutoLogin = TRUE);
	BOOL ConnectServer(const char* pcszIP, UINT16 wPort, BOOL bConnectBS, BOOL bAutoLogin = TRUE);
	BOOL IsConnected();
	BOOL Login();
	BOOL LoginReq();

	inline void SetEncryptCode(UINT8 byCode);
	inline UINT8 GetEncryptCode(void);

	BOOL AttachToCoroutine(const char* pcszCoroutineName);
	void DetachFromCorouine(void);
	const char* GetCoroutineName(void);

	void BeginWaitLoginCallback(void);
	void EndWaitLoginCallback(void);
	BOOL IsWaitLoginCallback(void);

	BOOL CheckHasLoginReq();
	BOOL CheckPassedAuth();
	BOOL SetAuthID(char* szAuthID, INT32 nAuthLen);

	BOOL Teleport(UINT32 dwTelportID);
	BOOL CreateRole(const char* pcszRoleName, INT32 eSex,
		INT32 eFaceType, INT32 eHairType, INT32 eHairColor, INT32 eClass);
	BOOL DeleteRole(UINT32 dwRoleID);
	BOOL SelectRole(UINT32 dwRoleID);
	BOOL LeaveGame(UINT32 dwRoleID);
	BOOL Logout();
	BOOL LogoutCancel();
	BOOL SendRandomMessage(void);

	BOOL CancelCutScene(void);
	BOOL SelectFocus(UINT32 dwCharID);

	BOOL MoveTo(INT32 nDestX, INT32 nDestY);
	BOOL LearnSpell(INT32 nSpellID, INT32 nSpellLevel);

	BOOL CastSpell(INT32 nSlotID, UINT32 dwTargetID, INT32 nX, INT32 nY, INT32 nZ);
	BOOL CastSwitchSpell(INT32 nSwitchSlotID, UINT32 dwTargetID, INT32 nX, INT32 nY, INT32 nZ);
	BOOL DirectlyCastSpell(UINT16 wSpellID, INT32 nSpellLevel, UINT32 dwTargetID, INT32 nX, INT32 nY, INT32 nZ);

	BOOL EquipSpell(INT32 nSlot, INT32 nSpellID);
	BOOL CancelSpell(INT32 nSlot);
	BOOL AdjustTargetPt(INT32 nX, INT32 nY, INT32 nZ);
	BOOL CombatPoseSwitch(BOOL bPoseOn);
	BOOL CancelAura(UINT32 dwInstanceID);
	BOOL OnMount(INT32 nMountID);
	BOOL OffMount(void);


	BOOL GMCommand(const char* pcszGmcmd);

	BOOL InteractNpc(UINT32 dwNpcID);

	BOOL MoveItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot);
	BOOL SplitItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot, INT16 itemcount);
	BOOL DeleteItem(UINT8 conslot, UINT8 itemslot, INT16 itemcount);
	BOOL PickUpItem(UINT32 dwDropID);
	BOOL BuyItem(INT32 nShopID, INT32 nShopItemIndex, INT32 nItemCount);
	BOOL SellItem(UINT8 conslot, UINT8 itemslot);
	BOOL UseItem(UINT8 conslot, UINT8 itemslot);

	BOOL ViewSoldItem(void);
	BOOL BuyBackItem(UINT8 slot);
	BOOL RepairItem(UINT8 conslot, UINT8 itemslot);
	BOOL RepairAllEquippedItem(void);
	BOOL Refine(UINT8 nRefineSlot, BOOL bAddEquip, UINT8 byConSlot, UINT8 byItemSlot);
	BOOL BuyContainerSlot(UINT8 byConSlot, UINT8 byCount);
	BOOL OrganizeBag(UINT8 byConSlot);
	BOOL IdentifyItem(UINT8 byConSlot, UINT8 byItemSlot);
	BOOL RandomizeItem(UINT8 byConSlot, UINT8 byItemSlot);
	BOOL ConfirmRandomizeItem(void);
	BOOL UseMoneyType01Only(BOOL bValue);
	BOOL CheckNpcShopData(UINT32 dwCrc);

	// Spirit fusion
	//        c2g_upgrade_soul,
	//        c2g_add_soul,
	//        c2g_remove_soul,
	//
	//        // Soul forging
	//        c2g_rune_open_slot,
	//        c2g_rune_close_slot,
	//        c2g_rune_add,
	//        c2g_rune_remove,
	//
	//        // Equipment dismantling and combining
	//        c2g_decompose,
	//        c2g_compose,

	BOOL UpgradeSoul(UINT8 byTargetConSlot, UINT8 byTargetItemSlot, UINT8 bySrcCount, UINT8* bySrcConSlot, UINT8* bySrcItemSlot);
	BOOL AddSoul(UINT8 byEquipConSlot, UINT8 byEquipItemSlot, UINT8 bySocketIndex, UINT8 bySoulConSlot, UINT8 bySoulItemSlot);
	BOOL RemoveSoul(UINT8 byConSlot, UINT8 byItemSlot, UINT8 bySocketIndex);

	BOOL OpenStall();
	BOOL CloseStall();
	BOOL RealOpenStall();
	BOOL RealCloseStall();
	BOOL AddStallItem(UINT8 stallslot, UINT8 conslot, UINT8 itemslot, INT16 itemcount, INT32 price);
	BOOL ViewStallItem(UINT32 roleid);
	BOOL BuyStallItem(UINT32 roleid, UINT8 stallslot, INT16 itemcount, UINT32 modifytime);
	BOOL ChangeStallName(const char* stallname);
	BOOL RemoveStallItem(UINT8 slot);
	BOOL UpgradeStall(UINT8 upgradetype);
	BOOL VerifyItem(UINT32 dwSrcRoleId, char* pText);
	BOOL AddFriend(UINT32 friendid, const char* friendname);
	BOOL DelFriend(UINT32 friendid);
	BOOL ChangeFriendGroup(UINT32 friendid, UINT8 groupid);
	BOOL AskTrade(UINT32 roleid);
	BOOL AcceptTrade(UINT32 roleid);
	BOOL CancelTrade();
	BOOL LockTrade();
	BOOL ConfirmTrade();
	BOOL UnlockTrade();
	BOOL ExploreZone();
	BOOL TalkToNpc(INT32 nQuestID, INT32 nTalkNpcID);
	BOOL SetTradeMoney(INT32 money);
	BOOL SetTradeItem(UINT8 tradeslot, UINT8 bAdd, UINT8 conslot, UINT8 itemslot);
	BOOL SendMail(const char* rolename, const char* subject, const char* content);
	BOOL ListMail();
	BOOL ReadMail(UINT32 mailid);
	BOOL DeleteMail(UINT32 mailid);
	BOOL GetMailAttach(UINT32 mailid);
	BOOL DoGatePing(UINT32 dwTick);
	BOOL DoGamePing(UINT32 dwTick);

	BOOL FireHero(void);
	BOOL SummonHero(void);
	BOOL RecallHero(void);
	BOOL QueryHeroAttrList(void);
	BOOL ChangeHeroAi(INT32 nAiType);


	BOOL AddRole(CRole* poRole);
	BOOL RemoveRole(UINT32 dwRoleID);

	const char* GetUserName(void){ return m_szUserName; }
	const char* GetPassword(void){ return m_szPassword; }
	//const char* GetUserType(void){return m_szUserType;}
	INT32 GetUserState(void){ return m_eUserState; }
	void SetUserState(INT32 eUserState){ m_eUserState = eUserState; }
	CRole** GetRoleList(){ return m_poRoleList; }

	const UINT32 GetServerAddress(void);
	UINT16 GetServerPort(void);
	void SetServerContent(UINT32 dwAddress, UINT16 wPort){ m_dwServerAddress = dwAddress; m_wServerPort = wPort; }

	CRole* GetPlayingRole(void);
	void SetPlayingRole(CRole* poRole);

	void SetPingTick(UINT64 qwTick){ m_qwLastPingTick = qwTick; }
	UINT64 GetPingTick(){ return m_qwLastPingTick; }

	BOOL SendMsg(PACKET_BUFFER* pBuffer, UINT32 dwSize);

	CRole* GetRoleByID(UINT32 dwRoleID);
	CRole* GetRoleByIndex(INT32 nIndex);
	INT32 GetRoleCount(void);

	BOOL IsAutoLogin(void) { return m_bAutoLogin; }

	void SetDeleteFlag(void);
	BOOL IsDeleted(void){ return m_bDeleted; }

	// Quest related.
	BOOL AcceptQuest(INT32 nQuestID, INT32 nAcceptType, INT32 nSrcID);
	BOOL AbandonQuest(INT32 nQuestID);
	BOOL CompleteQuest(INT32 nQuestID, INT32 nSelectedIdx);
	BOOL ShareQuest(INT32 nQuestID, INT32 nShareType);
	BOOL ConfirmPublishQuest(INT32 nQuestID, INT32 nMasterID);
	BOOL GenerateCircleQuest();

	// Achievement related
	BOOL CompleteAchievement(INT32 nAchievementID);
	BOOL GetAchievementReward(INT32 nAchievementID);
	BOOL CompareAchievement(UINT32 dwRoleID);

	// Diag related.
	BOOL InteractWithNpc(UINT32 dwNpcID);
	BOOL SelectDialogOption(INT32 nParam);

	// test doodad
	BOOL OperateDoodad(UINT32 dwDoodadID);

	// ranklist related
	BOOL QueryRanklist(INT32 nPage, INT32 nRanklistID);

	// spirit related
	BOOL ChangeSoul2Pts(BOOL bUseMoney, BOOL bIsOnline);
	BOOL SpiritAddAir(BOOL bQuick);
	BOOL MergeAir(INT32 nSrcSlot);
	BOOL MoveAir(INT32 nSrcType, INT32 nSrcSlot, INT32 nTarType, INT32 nTarSlot);
	BOOL BuyAirSlot(INT32 nBagType);
	BOOL BrushSlot(INT32 nPage, INT32 nIndex);

	// award related
	BOOL AwardUseNumber(char* pAwardNumber);

	// team related
	BOOL SendLoadFinsh();

	BOOL SelectDungeonDifficulty(UINT32 nDifficulty);
	BOOL EnterDungeon(UINT32 nDifficulty);
	BOOL LeaveScene(void);

	BOOL QueryRoleDetailData(UINT32 dwRoleID);
	BOOL QueryRolePow(UINT32 dwRoleID);
	BOOL ChangeLine(INT32 nSceneID);
	BOOL UpdateClientVariable(INT32 nVarIndex, INT32 nVarValue);

	void UpdateRoleAttrCRC(UINT32 dwRoleID, UINT32 dwCRC);
	void UpdateRoleEquipCRC(UINT32 dwRoleID, UINT32 dwCRC);
	void UpdateRoleSpiritCRC(UINT32 dwRoleID, UINT32 dwCRC);
	void UpdateRoleSpellCRC(UINT32 dwRoleID, UINT32 dwCRC);

	void LuaRecvMsg(INT32 nMsgID, void* pData, UINT32 dwDataLen);
	void RegisterMsg(const char* pcszCaseName, CMsgSet& oMsgSet);
	void UnRegisterMsg();
	UINT32 GetSessionID(){ return m_nSessionID; }
	ISocketSession* GetSocketSession(void) { return m_poSocketSession; }
	QTreeWidgetItem* m_pUserWidget;

	void SetRecvStartTick(UINT32 dwTick){ m_qwStartRecvTick = dwTick; }
	void SetSendStartTick(UINT32 dwTick){ m_qwStartSendTick = dwTick; }
	UINT32 GetRecvStartTick(){ return m_qwStartRecvTick; }
	UINT32 GetSendStartTick(){ return m_qwStartSendTick; }

	void AddRecvDataSize(UINT32 dwSize){ m_dwReceiveSize += dwSize; m_dwTotalRecvSize += dwSize; }
	void AddSendDataSize(UINT32 dwSize){ m_dwSendSize += dwSize; m_dwTotalSendSize += dwSize; }
	UINT32 GetRecvDataSize(){ return m_dwReceiveSize; }
	UINT32 GetSendDataSize(){ return m_dwSendSize; }

	void ResetRecvData();
	void ResetSendData();

	UINT32 GetTotalRecvDataSize(){ return m_dwTotalRecvSize; }
	UINT32 GetTotalSendDataSize(){ return m_dwTotalSendSize; }
	UINT32 GetBeginTick(){ return m_qwBeginTick; }

	void AddPingPackage(UINT32 dwPingTick);

	void AddChatCount(){ m_dwChatCount++; }
	void ResetChatData();
	UINT32 GetChatCount(){ return m_dwChatCount; }
	UINT32 GetStartChatTick(){ return m_qwStartChatTick; }
	UINT8 GetGroupID(){ return m_byGroupID; }

	//////////////////////////////////////////////////////////////////////////
	// title
	BOOL EquipTitle(UINT8 byTitleID);
	BOOL UnEquipTitle();

	// master
	BOOL GetMasterInfo();
	BOOL GetMasterRecruitList();
	BOOL GetMasterSoloList();
	BOOL ApplyTeacher(UINT32 dwRoleID);
	BOOL TeacherAgreeApp(UINT32 dwStudentID);
	BOOL TeacherRefuseApp(UINT32 dwStudID);
	BOOL SoloCancelApp(UINT32 dwTeacherID);

	BOOL ApplyToStudent(UINT32 dwStudentID);
	BOOL SoloAgreeApp(UINT32 dwTeacherID);
	BOOL SoloRefuseApp(UINT32 dwTeacherID);
	BOOL TeacherCancelApp(UINT32 dwStudentID);

	BOOL LeaveTeacher();
	BOOL FireStudent(UINT32 dwStudentID);

	BOOL MasterCZ(UINT32 dwSelfID, UINT32 dwTargetID, UINT8 byCZType, const char *pcszText);

	BOOL DesireGraduate();
	BOOL AgreeGraduate(UINT32 dwStudentID);
	BOOL ForceGraduate();

    // auction
    BOOL AuctionSearchType(UINT8 byAuctionType, UINT8 byAuctionSubType);
    BOOL AuctionSearch(UINT8 bySortBy, INT32 nItemID);
    BOOL AuctionQuery(UINT32 dwAuctionID);
    BOOL AuctionSell(UINT8 byConSlot, UINT8 byItemSlot, INT32 nPrice, INT32 nBuyoutPrice);
    BOOL AuctionCancelSell(UINT32 dwAuctionID);
    BOOL AuctionBuy(UINT32 dwAuctionID, INT32 nPrice);
    BOOL AuctionListMySelling();
    BOOL AuctionListMyBuying();

	// vip
	BOOL SubscribeVIP(INT32 nVIPLevel, INT32 nMonth);

    BOOL ShieldRole(UINT32  dwRoleID);
    BOOL UnShieldRole(UINT32  dwRoleID);

    // guild
    BOOL    QueryGuildInfo(UINT32 dwGuildID);
    BOOL    CreateGuild(const char *pcszGuildName, const char *pcszAnnounce);
    BOOL    GetGuildMoreInfo();

    BOOL    ViewGuildList(UINT32 dwLastGuildID);
    //BOOL    FindGuild(const char *pcszName);
    BOOL    FindGuild(UINT32 dwGuildID);
    BOOL    ApplyToJoinGuild(UINT32 dwGuildID);
    BOOL    GetGuildAppList();
    BOOL    RefuseGuildApp(UINT32 dwRoleID);
    BOOL    AgreeGuildApp(UINT32 dwRoleID);
    BOOL    RevertGuildApp(UINT8 byRevertType, UINT32 dwRoleID);
    BOOL    InviteToJoinGuild(const char *pcszRoleName);
    BOOL    RevertGuildInvitation(UINT8 byResult, UINT32 dwRoleID);
    BOOL    DisbandGuild();
    BOOL    ChangeNotice(const char *pStr);
    BOOL    ChangePosition(UINT32 dwRoleID, INT32 nPosition);
    BOOL    LeaveGuild();
    BOOL    BanishRole(UINT32 dwRoleID);
    BOOL    Demise(UINT32 dwRoleID);
    BOOL    DrawSalary();
    BOOL    ContributeFund(INT32 nType, INT32 nMoney);
    BOOL    ForbidChat(INT32 nOP, UINT32 dwRoleID);
    BOOL    ChangeWeather(INT32 nWeatherType, INT32 nTimeType);
    BOOL    MoreHistory();
    BOOL    MoreChest();
    BOOL    ChangeStorageRight(INT32 nPosition, INT32 nRight);
    BOOL    DiplomatApp(INT32 nOP, INT32 nTimeType, const char *pcszGuildName);
    BOOL    GetApplyUnionList();
    BOOL    ReplyUnionApp(INT32 nOP, UINT32 dwGuildID);


	// lua
	INT32   LuaMasterGetRecruitNum();
	UINT32  LuaMasterGetRecruitRoleByIndex(INT32 nIndex);
	INT32   LuaMasterGetSoloNum();
	UINT32  LuaMasterGetSoloRoleByIndex(INT32 nIndex);
	INT32   LuaMasterGetSendListNum();
	UINT32  LuaMasterGetSendRoleIDByIndex(INT32 nIndex);
	INT32   LuaMasterGetRecvAppNum();
	UINT32  LuaMasterGetRecvRoleIDByIndex(INT32 nIndex);
	BOOL    LuaMasterIsSendListFull();
	BOOL    LuaMasterClearSendList();
	BOOL    LuaMasterIsRecvListFull();
	BOOL    LuaMasterClearRecvLIst();
    BOOL    LuaMasterCanCZTeacher();
    BOOL    LuaMasterCanCZStudent(UINT32 dwRoleID);
	BOOL    LuaMasterSetGraduateRoleID(UINT32 dwRoleID);
	UINT32  LuaMasterGetGraduateRoleID();


    //INT32   LuaGGetViewListNum();
    //UINT32  LuaGGetViewListGuildIDByIndex(INT32 nIndex);

    


private:
	char                m_szUserName[COMMON_NAME_LEN];
	//char                m_szUserType[COMMON_NAME_LEN];
	char                m_szPassword[COMMON_NAME_LEN];
	char			    m_szAuthID[OA_SESSION_ID_LEN];
	BOOL                m_bHasLoginReq;
	char                m_szCoroutineName[COMMON_NAME_LEN];
	BOOL                m_bWaitLoginCallback;
	UINT8				m_byEncryptCode;

	INT32               m_eUserState;
	CRole*              m_poPlayingRole;
	CRole*              m_poRoleList[MAX_ROLE_PER_USER];
	static char         m_szRobotUserType[3];
	BOOL                m_bAutoLogin;
	BOOL                m_bDeleted;
	INT32               m_nSessionID;

	UINT32              m_dwServerAddress;
	UINT32              m_wServerPort;

	ISocketSession*     m_poSocketSession;
	BOOL                m_bConnected;
	INet*               m_poNet;
	IPacketAllocator*   m_poPacketAllocator;

	char                m_szCaseName[256];
	CMsgSet             m_oSetMsg;
	char                m_szTempData[65536];
	UINT32              m_dwTempIndex;

	UINT64              m_qwLastPingTick;

	UINT32              m_dwReceiveSize;
	UINT64              m_qwStartRecvTick;

	UINT32              m_dwSendSize;
	UINT64              m_qwStartSendTick;

	UINT64              m_qwBeginTick;
	UINT32              m_dwTotalSendSize;
	UINT32              m_dwTotalRecvSize;

	UINT32              m_dwMinPing;
	UINT32              m_dwMaxPing;
	UINT64              m_qwPingValue;
	UINT64              m_qwPingCount;

	UINT64              m_qwStartChatTick;
	UINT32              m_dwChatCount;

	UINT8               m_byGroupID;

	UINT64				m_LastResetRecvFrame;
	UINT32				m_dwRecvMsgList[1024];

	typedef std::map<UINT32, UINT32>	CACHE_MAP;
	CACHE_MAP			m_AttrCacheMap;
	CACHE_MAP			m_EquipCacheMap;
	CACHE_MAP			m_SpiritCacheMap;
	CACHE_MAP			m_SpellCacheMap;

};

inline void CUser::SetEncryptCode(UINT8 byCode)
{
	m_byEncryptCode = byCode;
}

inline UINT8 CUser::GetEncryptCode(void)
{
	return m_byEncryptCode;
}


#endif  // _USER_H_
