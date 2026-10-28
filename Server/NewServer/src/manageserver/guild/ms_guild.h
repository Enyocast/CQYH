/********************************************************************
	created:	2:4:2013   16:27
	file:		ms_guild.h
	author:		Allan Tao
	
	purpose:	Guild
*********************************************************************/


#ifndef _H_MS_GUILD_H_
#define _H_MS_GUILD_H_


#include "guild_def.h"
#include "base_list.h"
#include "ms_guild_member.h"
#include "guild_storage.h"
#include "application_mgr.h"
#include "./timer/time_trigger.h"
#include "linux_map.h"

struct MS_ROLE_DATA;
struct MS_ONLINE_ROLE_DATA;
struct APP_NODE;

struct GUILD_NAME_KEY
{
    UINT64 qwKey0;
    UINT64 qwKey1;
    UINT64 qwKey2;
    UINT32 dwPadding;

    inline bool operator < (GUILD_NAME_KEY& right)
    {
        if (qwKey0 != right.qwKey0)
            return qwKey0 < right.qwKey0;
        if (qwKey1 != right.qwKey1)
            return qwKey1 < right.qwKey1;
        return qwKey2 < right.qwKey2;
    }
    inline bool operator >(GUILD_NAME_KEY& right)
    {
        if (qwKey0 != right.qwKey0)
            return qwKey0 > right.qwKey0;
        if (qwKey1 != right.qwKey1)
            return qwKey1 > right.qwKey1;
        return qwKey2 > right.qwKey2;
    }
};

struct MS_G_B_DATA
{
    MS_G_B_DATA() : qwNameID(0), nType(0), nLevel(0), dwReviveTime(0)   { }

    MS_G_B_DATA(UINT64 qwID, INT32 nT, INT32 nL) :
        qwNameID(qwID), nType(nT), nLevel(nL), dwReviveTime(0)    { }

    MS_G_B_DATA(UINT64 qwID, INT32 nT, INT32 nL, UINT32 dwRT) :
        qwNameID(qwID), nType(nT), nLevel(nL), dwReviveTime(dwRT)    { }

    UINT64      qwNameID;
    INT32       nType;
    INT32       nLevel;
    UINT32      dwReviveTime;
};

struct EVENT_DATA
{
    BASE_LIST_NODE  node;
    INT32       nType;
    UINT32      param1;
    UINT32      param2;
    UINT32      param3;
    UINT32      param4;
    UINT32      dwOccurTime;
};

struct STORAGE_EVENT_DATA
{
    BASE_LIST_NODE  node;
    INT32       nType;
    UINT32      dwRoleID;
    UINT32      dwOccurTime;
    INT32       nBufferSize;
    char        szItemBuffer[GUILD_MAX_ITEM_BUFFER_LENGTH];
};


struct DIPLOMAT_APP_NODE : APP_NODE 
{
    INT32   nTimeType;
};

struct GUILD_UPGRADE_TRIGGER : BASE_TRIGGER_NODE 
{
    UINT32      dwGuildID;
    UINT32      dwRoleID;
    UINT64      qwNameID;
    INT32       nIndex;
    INT32       nType;
};

struct G_B_REVIVE_TRIGGER : BASE_TRIGGER_NODE
{
    UINT32      dwGuildID;
    UINT64      qwNameID;
};

//struct GUILD_WAR_TRIGGER
//{
//    UINT32      dwAttackGuildID;
//    UINT32      dwBeAttackedGuildID;
//    INT32       nStage;
//};

struct DIPLOMAT_DATA
{
    UINT32      dwGuildID;
    UINT32      dwEndTime;
};

struct MS_GUILD_WAR_DATA : BASE_TRIGGER_NODE 
{
    UINT32      dwBeginDayTime;
    UINT32      dwIntruderID;
    UINT32      dwDefenderID;
    INT32       nWarResult;
};

struct GUILD_DUNGEON 
{
    UINT32      dwTemplateID;
    UINT32      dwOwnerID;
    UINT32      dwLeaderID;
    INT32       nCreateTime;
};

struct GUILD_WAR_PERSONAL_ACHIEVEMENT 
{
    UINT32      dwRoleID;
    INT32       nKillNum;
    INT32       nDeadCount;
    INT32       nSalary;
};

#pragma pack(push, 1)
struct GUILD_DB
{
	UINT32          dwGuildID;
	UINT16          wVersion;
	CHAR            szGuildName[GUILD_NAME_LEN];
	UINT8           bySvrGroup;
	UINT32          dwLeaderID;

	CHAR            szCreaterName[ROLE_NAME_LEN];
	UINT32          dwCreateTime;
	CHAR            szAnnounce[GUILD_ANNOUNCE_LEN];         // Guild announcement
	CHAR            szNotice[GUILD_NOTICE_LEN];             // Guild notice
	char            BlobBuffer[0];
};
#pragma pack(pop)

class CMsGuild
{
public:
    CMsGuild();
    ~CMsGuild();

    BOOL CheckDBDataLength();

    BOOL MainLoop(UINT32 dwCurTime);

    BOOL Init();
    BOOL UnInit();
	BOOL Load(GUILD_DB& db_data);

    void LoadMember(CMsGuildMember &data);
    //BOOL Save(DB_BUFFER &data);

    BOOL Create(UINT32 dwID, INT32 nSvrGroup, UINT32 dwRoleID, const char *pcszRoleName, const char *pcszGuildName, const char *pcszAnnounce);
    BOOL Destory();

    inline UINT32   GetID();
    inline INT32    GetSvrGroup();
    INT32    GetLevel();
    inline const char * GetName();
    LM_MAP_NODE<GUILD_NAME_KEY> &GetNameMapNode() { return GuildNameNode; }
    inline const char * GetCreaterName();
    inline UINT32   GetLeaderID();
    inline UINT32   GetCreateTime();
    inline const char * GetAnnounce();
    void SetNotice(const char *pcszNotice);
    inline const char * GetNotice();

    inline CMsGuildStorage &GetStorage();
    inline BASE_LIST_NODE  &GetLvlRankNode();
    inline  BASE_LIST_NODE &GetLadderNode();

    INT32  GetResourceIncrement(INT32 nType);

    INT32  GetMaxStorage(INT32 nBuildingType);

    inline INT32 GetProsperity();
    BOOL    SetProsperity(INT32 nValue);
    BOOL    InitProsperity();
    BOOL    UpdateBuildingProsperity(INT32 nType, INT32 nLevel);

    inline INT32 GetMoney();
    BOOL   AddMoney(INT32 nMoney, GUILD_HISTORY_EVENT_TYPE eReason, BOOL bIsSave = TRUE);
    BOOL   SubMoney(INT32 nMoney, GUILD_HISTORY_EVENT_TYPE eReason, BOOL bIsSave = TRUE);

    inline INT32    GetWood();
    BOOL    AddWood(INT32 nWood, BOOL bSendMsg = TRUE);
    BOOL    SubWood(INT32 nWood, BOOL bSendMsg = TRUE);

    inline INT32    GetHerb();
    BOOL    AddHerb(INT32 nHerb, BOOL bSendMsg = TRUE);
    BOOL    SubHerb(INT32 nHerb, BOOL bSendMsg = TRUE);

    inline INT32    GetCryStal();
    BOOL    AddCrystal(INT32 nCrystal, BOOL bSendMsg = TRUE);
    BOOL    SubCrystal(INT32 nCrystal, BOOL bSendMsg = TRUE);

    inline INT32    GetSilver();
    BOOL    AddSilver(INT32 nSilver, BOOL bSendMsg = TRUE);
    BOOL    SubSilver(INT32 nSilver, BOOL bSendMsg = TRUE);

    inline INT32  GetState();
    inline INT32 GetStorageRightByPosition(INT32 nPosition);

    INT32   GetVariable(INT32 nIndex);
    void    SetVariable(INT32 nIndex, INT32 nValue);

    BOOL    CanGuildChat(UINT32 dwRoleID);
    BOOL    AddGuildEvent(INT32 nType, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4);
    BOOL    AddGuildChestEvent(INT32 nType, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4);

    // Send only to the guild leader and deputy leader
    BOOL    BroadcastMail(INT32 nMailTemplateID);
    BOOL    BroadcastMail(const char *pcszTitle, const char *pcszContent);

    // guild member Allan Tao[8.5.2013] 
    INT32   GetMaxMemberNum();
    inline INT32    GetMemberNum();
    BOOL    IsMember(UINT32 dwRoleID);
    INT32   AddMember(MS_ROLE_DATA* pRoleData, INT32 nPosition);
    void    DelMember(UINT32 dwRoleID);
    CMsGuildMember* GetMember(UINT32 dwRoleID);
    INT32   GetMemberNumInAPost(UINT8 byPosition);

    // building
    INT32   GetMatchWarCount();
    INT32   GetBuildingMaxLevelByType(INT32 nType);
    INT32   GetBuildingNumByType(INT32 nType);
    INT32   GetUpgradeBuildingNumByType(INT32 nType);
    MS_G_B_DATA *GetFunBuildingDataByType(INT32 nType);
    MS_G_B_DATA *GetBuildingDataByNpcID(UINT64 qwNameID);
    BOOL    IsExistBuilding(UINT64 qwNameID);
    

    GUILD_UPGRADE_TRIGGER *GetUpgradeBuildingByNpcID(UINT64 qwNameID);
    BOOL    IsExistUpgradeBuilding(UINT64 qwNameID);
    BOOL    AddUpgradeBuilding(UINT64 qwNameID, GUILD_UPGRADE_TRIGGER *pTri);
    void    DelUpgradeBuilding(UINT64 qwNameID);

    // welfare
    INT32   BeginUpgradeWelfareBuffer(UINT32 dwRoleID, INT32 nType);
    BOOL    CompleteUpgradeWelfareBuffer(GUILD_UPGRADE_TRIGGER *pTrigger);
    INT32   CancelUpgradeWelfareBuffer(INT32 nType);


    INT32   CreateBuilding(UINT32 dwRoleID, UINT64 qwNpcNameID, INT32 nType);
    INT32   BeginUpgradeBuilding(UINT32 dwRoleID, UINT64 qwNpcNameID, INT32 nType);
    BOOL    CompleteUpgradeBuilding(GUILD_UPGRADE_TRIGGER* pData);
    INT32   CancelUpgradeBuilding(UINT64 qwNpcNameID, INT32 nType);
    INT32   DelBuilding(UINT32 dwRoleID, UINT64 qwNpcNameID, INT32 nType);

    // diplomat
    inline INT32   GetEnemyNum();
    inline INT32   GetAllianceNum();

    BOOL    IsAlliance(UINT32 dwGuildID);
    BOOL    IsEnemy(UINT32 dwGuildID);

    BOOL    AddAlliance(UINT32  dwGuildID, UINT32 dwEndTime);
    BOOL    DelAlliance(UINT32 dwGuildID);

    BOOL    AddEnemy(UINT32 dwGuildID, UINT32 dwEndTime);
    void    DelEnemy(UINT32 dwGuildID);

    // guild war
    BOOL    SetAim(UINT32 dwGuildID, BOOL bAttackCD);
    inline  UINT32 GetAimID();

    BOOL    SetIntruder(UINT32 dwGuildID);
    inline UINT32 GetIntruder();

    BOOL    SetRevengeObj(UINT32 dwGuildID);
    inline  UINT32 GetRevengeObj();

    inline UINT32 GetProtectionTime();
    BOOL  SetProtectionTime(UINT32 dwTime);

    inline UINT32   GetWarAttackCD();
    BOOL     SetWarAttackCD(UINT32 dwTime);

    BOOL    BeginMatchWar(UINT32 dwGuildID);
    BOOL    CanBeginNewMatchWar();
    inline void     SetMatchingGuild(UINT32 dwGuildID);
    inline UINT32   GetMatchingGuild();


    //BOOL IsBuildingDisable(UINT32 dwSingleNpcID);
    BOOL DisableBuilding(UINT64 qwNameID, UINT32 dwReviveTime);
    BOOL IsOneLevelBornBuilding(INT32 nType);

    // guild dungeon
    UINT32  AddDungeon(UINT32 dwTemplateID, UINT32 dwOwnerID, UINT32 dwLeaderID);
    BOOL    DelDungeon(UINT32 dwTemplateID);
    BOOL    CheckSameDungeonType(UINT32 dwTemplateID);
    GUILD_DUNGEON   *FindDunGeon(UINT32 dwTemplateID);
    BOOL    FilterDungeon();

    // Iterator
    CMsGuildMember *GetFirstGuildMember();
    CMsGuildMember *GetNextGuildMember();

    APP_NODE *GetFirstRoleJoinGuildApp();
    APP_NODE *GetNextRoleJoinGuildApp(APP_NODE *pNode);

    DIPLOMAT_APP_NODE *GetFirstAllianceApp();
    DIPLOMAT_APP_NODE *GetNextAllianceApp(DIPLOMAT_APP_NODE* pNode);

    EVENT_DATA *GetFirstGuildEventData();
    EVENT_DATA *GetNextGuildEventData(EVENT_DATA *pData);

    EVENT_DATA *FirstChestEvent();
    EVENT_DATA *NextChestEvent(EVENT_DATA *pData);

    MS_G_B_DATA *FirstUnFunBuilding();
    MS_G_B_DATA *NextUnFunBuilding();

    inline DIPLOMAT_DATA *GetEnemyDataByIndex(INT32 nIndex);
    inline DIPLOMAT_DATA *GetAllianceDataByIndex(INT32 nIndex);

    inline INT32  GetWelfareAuraLevelByType(INT32 nType);
    INT32  GetUpgradeWelfareNum();
    GUILD_UPGRADE_TRIGGER* GetUpgradeWelfare(INT32 nIndex);

    INT32       GetUpgradeBuildingNum();
    GUILD_UPGRADE_TRIGGER* GetUpgradeBuilding(INT32 nIndex);
    //INT32         GetBuildingLvlByID(INT32 nID);

    GUILD_DUNGEON* GetFirstDungeon();
    GUILD_DUNGEON* GetNextDungeon();

    // ------------------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------------------

    INT32 RoleDeliverApplication(MS_ONLINE_ROLE_DATA &onlineRoleData);

    INT32 RefuseRoleApply(UINT32 dwRoleID, MS_ONLINE_ROLE_DATA &onlineRoleData);

    INT32 AgreeRoleApply(UINT32 dwInviterID, UINT32 dwRoleID);

    INT32 InviteToJoinGuild(MS_ONLINE_ROLE_DATA &onlineRoleData, const char *pcszRoleName);

    INT32 AgreeToJoinGuild(UINT32 dwInviterID, MS_ONLINE_ROLE_DATA &onlineRoleData);

    INT32 LeaveGuild(MS_ROLE_DATA &roleData);

    INT32 BanishSomebody(MS_ONLINE_ROLE_DATA &onlineRoleData, UINT32 dwRoleID);

    INT32 DisbandGuild(MS_ONLINE_ROLE_DATA &onlineRoleData);

    INT32 Demise(MS_ONLINE_ROLE_DATA &onlineRoleData, UINT32 dwRoleID);

    INT32 ChangeNotice(MS_ONLINE_ROLE_DATA &onlineRoleData, const char *pcszNotice);
    INT32 ChangeAnnounce(MS_ONLINE_ROLE_DATA &onlineRoleData, const char *pcszAnnounce);
    INT32 ForbidChat(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nOperation, UINT32 dwRoleID);

    INT32 ChangePosition(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nPosition, UINT32 dwRoleID);

    // diplomat
    INT32 Diplomat(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nOpType, INT32 nTimeType, CMsGuild *pMsTargetGuild);

    INT32 ReplyDiplomatApp(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nOp, UINT32 dwApplicantID);

    INT32 ChangeStorageRight(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nPosition, UINT16 wRight);

    INT32 DrawSalary(MS_ONLINE_ROLE_DATA &onlineRoleData);
    INT32 ForcedSalariedWithMail(UINT32 dwRoleID);

    INT32 Contribute(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nType, INT32 nMoney);

    // storage
    INT32 PrePushItem(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nSourceConSlot, INT32 nSourceItemSlot, INT32 nConSlot, INT32 nSlot);
    INT32 PushItem(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nGSResult, INT32 nConSlot, INT32 nItemSlot, INT32 nItemSize, char *pbuff);
    INT32 PrePopItem(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nConSlot, INT32 nItemSlot, INT32 nTargetConSlot, INT32 nTargetItemSlot);
    INT32 PopItem(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nGSResult, INT32 nSourceConSlot, INT32 nSourceItemSlot, INT32 nTargetConSlot, INT32 nTargetItemSlot);
    INT32 MoveItem(MS_ONLINE_ROLE_DATA &onlineRoleData, INT32 nSourceConSlot, INT32 nSourceItemSlot, INT32 nTargetConSlot, INT32 nTargetItemSlot);

    // pow
    INT32  GetPow();

    // ------------------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------------------

    // lua
    BOOL    LuaBroadcastMsgNotifyType(INT32 nType);

    BOOL    LuaAddProtectionTime(UINT32 dwTime);

    BOOL    LuaLeaveGuild(INT32 nLeaveType, UINT32 dwRoleID);

    BOOL    LuaBroadcastJoinWar(INT32 nWarCharacter, UINT32 dwTargetGuildID);

    BOOL    LuaAddBuilding(const char *pcszNameID, INT32 nType, INT32 nLevel, UINT32 dwReviveTime);


	inline UINT32 GetSabacEnrollTime(INT32 nIndex);
	void EnrollSabac(UINT32 dwEnrollTime);
	void OccupySabac(BOOL bOccupied);
	inline BOOL IsOccupiedSabac(void);
	BOOL IsEnrolledSabac(void);

    // achievement
    inline const char* GetAchievementData();
    BOOL    CheckAchievement(INT32 nID);

    BOOL    SetAchievementCondition(INT32 nCdtnType, INT32 nIndex);

public:
    BOOL SaveGuild(char *pData, UINT32 &dwSize);

protected:
    BOOL LoadGuild(const char *pcData);
    BOOL LoadGuild_v1(const char *pcData);
    BOOL LoadGuild_v2(const char *pcData);
    BOOL LoadGuild_v3(const char *pcData);
    BOOL LoadGuild_v4(const char *pcData);
    BOOL LoadGuild_v5(const char *pcData);

    BOOL LoadBase_v1(const char *pcData, UINT32 dwSize);
    BOOL LoadBase_v2(const char *pcData, UINT32 dwSize);
    BOOL LoadBase_v3(const char *pcData, UINT32 dwSize);
    BOOL LoadBase_v4(const char *pcData, UINT32 dwSize);
	BOOL LoadWelfare_v1(const char *pcData, UINT32 dwSize);
    BOOL LoadBuilding_v1(const char *pcData, UINT32 dwSize);
    BOOL LoadDiplomat_v1(const char *pcData, UINT32 dwSize);
    BOOL LoadDiplomat_v2(const char *pcData, UINT32 dwSize);
    BOOL LoadDungeon_v1(const char *pcData, UINT32 dwSize);
    BOOL LoadHistory_v1(const char *pcData, UINT32 dwSize);


    BOOL SaveBase(char *pData, UINT32 &dwSize);
    BOOL SaveWelfare(char *pData, UINT32 &dwSize);
    BOOL SaveBuilding(char *pData, UINT32 &dwSize);
    BOOL SaveDiplomat(char *pData, UINT32 &dwSize);
    BOOL SaveDungeon(char *pData, UINT32 &dwSize);
    BOOL SaveHistory(char *pData, UINT32 &dwSize);


protected:
    BOOL    _AddMember(UINT32 dwRoleID, INT32 nPosition);

    BOOL    _CalculateOfflineData();

    BOOL    _DiplomatWashOut( UINT32 dwCurrentTime, UINT32 dwCheckTime );

    INT32   _LeaveGuild(INT32 nLeaveType, UINT32 dwRoleID );

    INT32   _DiplomatAlliance(MS_ONLINE_ROLE_DATA &onlineRoleData, CMsGuild *pMsTargetGuild, INT32 nTimeType);

    INT32   _DiplomatEnemy(MS_ONLINE_ROLE_DATA &onlineRoleData, CMsGuild *pMsTargetGuild, INT32 nTimeType);

    INT32   _AgreeApplyAlliance(MS_ONLINE_ROLE_DATA &onlineRoleData, CMsGuild *pApplicantGuild);

    INT32   _RefuseApplyAlliance(MS_ONLINE_ROLE_DATA &onlineRoleData, CMsGuild *pMsTargetGuild);

    // role apply to join guild
    BOOL    _IsInGuildAppList(UINT32 dwRoleID);
    BOOL    _AddRoleJoinGuildApp(UINT32 dwRoleID);
    BOOL    _DelRoleJoinGuildApp(UINT32 dwRoleID);

    BOOL    _IsInAllianceAppList(UINT32 dwApplicantID);
    INT32   _GetAllianceAppTimeType(UINT32 dwApplicantID);
    BOOL    _AddAllianceApplication(UINT32 dwApplicantID, INT32 nTimeType);
    BOOL    _DelAllianceApplication(UINT32 dwApplicantID);


    void    _DelBuilding(UINT64 qwNpcNameID);

private:
    UINT32          m_dwID;
    union 
    {
        CHAR            m_szGuildName[GUILD_NAME_LEN];
        LM_MAP_NODE<GUILD_NAME_KEY>  GuildNameNode;
    };
    INT32           m_nSvrGroupID;
    UINT32          m_dwLeaderID;
    CHAR            m_szCreaterName[ROLE_NAME_LEN];

    UINT32          m_dwCreateTime;
    INT32           m_nGuildMoney;

    INT32           m_nProsperity;

    INT32           m_nHerb;
    INT32           m_nWood;
    INT32           m_nCrystal;
    INT32           m_nSilver;
    UINT32          m_dwCalculateResourceTime;

    INT32           m_nState;
    UINT32          m_dwRoutineConsumeTime;

    CHAR            m_szAnnounce[GUILD_ANNOUNCE_LEN];        // Guild announcement
    CHAR            m_szNotice[GUILD_NOTICE_LEN];         // Guild notice

    UINT16          m_wStorageRight[GUILD_POSITION_COUNT];

    INT32           m_nAllianceNum;
    INT32           m_nEnemyNum;
    DIPLOMAT_DATA   m_arrAlliance[GUILD_MAX_ALLIANCE_NUM];
    DIPLOMAT_DATA   m_arrEnemy[GUILD_MAX_ENEMY_NUM];

    // guild variables
    INT32           m_arrVariables[MAX_GUILD_VARIABLE_COUNT];

    // guild war
    UINT32          m_dwAttackCD;
    UINT32          m_dwAimID;
    UINT32          m_dwIntruderID;
    UINT32          m_dwProtectionTime;
    UINT32          m_dwRevengeGuildID;

    INT32           m_nMatchWarCount;
    UINT32          m_dwMatchWarTime;
    UINT32          m_dwMatchingGuild;

    INT32           m_nHistoryNum;
    INT32           m_nChestHistoryNum;
    CBaseList       m_History;
    CBaseList       m_ChestHistory;

    // Guild sorting
    BASE_LIST_NODE      m_NodeSortByLvl;
    BASE_LIST_NODE      m_LadderNode;

    CMsGuildStorage     m_storage;

    // member
    typedef std::list<CMsGuildMember>   MEMBER_LIST;
    MEMBER_LIST      m_memberList;
    MEMBER_LIST::iterator m_memberListCursor;

    // welfare
    INT8            m_arrWelfareAuraLvl[GUILD_MAX_WELFARE_AURA_COUNT];
    INT32           m_nUpgradeWelfareAuraCount;
    GUILD_UPGRADE_TRIGGER    *m_paWelfareUpgradeData[GUILD_MAX_UPGRADE_AURA_COUNT];

    // building
    MS_G_B_DATA     m_FunBuilding[GUILD_B_FUNATIONAL_NUM];
    typedef std::map<UINT64, MS_G_B_DATA>   G_BUILDING_MAP;
    G_BUILDING_MAP  m_BuildingList;
    G_BUILDING_MAP::iterator    m_BCursor;
    INT32           m_nUpgradeBuildingNum;
    GUILD_UPGRADE_TRIGGER   *m_pUpgradeBuilding[GUILD_MAX_UPGRADE_BUILDING_COUNT];


    // guild dungeon
    typedef std::list<GUILD_DUNGEON>    GUILD_DUNGEON_LIST;
    GUILD_DUNGEON_LIST   m_listDungeon;
    GUILD_DUNGEON_LIST::iterator m_DungeonListCursor;
    INT32           m_nDungeonUpdateTime;

    // memory data
	UINT32			m_dwSabacEnrollTime[MAX_SABAC_ENROLL_COUNT];
	BOOL			m_bOccupiedSabac;

    // guild achievement
    char            m_Achievement[GUILD_ACHI_TYPE_NUM];


    //////////////////////////////////////////////////////////////////////////
    // war

public:
    inline BOOL CheckCharacter(INT32 nC);
    inline INT32    GetWarCharacter();
    BOOL SetWarCharacter(INT32 nC);
    BOOL ClearWarCharacter(INT32 nC);

    BOOL    AddIntruder(UINT32 dwGuildID);
    BOOL    ClearIntruder();
    inline INT32 GetIntruderNum();
    UINT32  FirstIntruder();
    UINT32  NextIntruder();

private:

    UINT8           m_byWarCharacter;

    typedef std::set<UINT32>    INTRUDER_SET;
    INTRUDER_SET    m_IntruderSet;
    INTRUDER_SET::iterator  m_IntruderCursor;
};


inline INT32 GetMaxOfferInPosition(INT32 nPosition)
{
    LOG_PROCESS_ERROR(nPosition > GUILD_POSITION_LEADER && nPosition < GUILD_POSITION_TOTAL);
    return ARR_GUILD_POS_HUMAN_NUM[nPosition - 1];
Exit0:
    return 0;
}


BOOL    SqlUpdateGuild(CMsGuild *poMsGuild);



void CB_GuildAppTimeout(APP_NODE *pNode);

void CB_DiplomatAppTimeout(APP_NODE *pNode);

INT32 CB_UpgradeWelfareTimeout(BASE_TRIGGER_NODE *pNode);

INT32 CB_UpgradeBuildingTimeout(BASE_TRIGGER_NODE *pNode);

INT32 CB_BuildingEnable(BASE_TRIGGER_NODE *pNode);

#include "ms_guild_inl.h"



#endif //_H_MS_GUILD_H_






 
