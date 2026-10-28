//  Allan Tao[12.8.2014] 

#ifdef _ROBOT

#ifndef _H_ASIMOV_GUILD_H_
#define _H_ASIMOV_GUILD_H_

#include "string_def.h"
#include "guild_def.h"
struct ASIMOV_GUILD_MEMBER 
{
    UINT32      dwRoleID;
    UINT8       byPosition;
    UINT8       byGuildFlag;
    INT32       nSalary;
    UINT32      dwDrawSalaryTime;
};

struct ASIMOV_DIPLOMAT_DATA
{
    UINT32      dwGuildID;
    UINT32      dwEndTime;
};


struct ASIMOV_GUILD_EVENT
{
    UINT8       byType;
    UINT32      param1;
    UINT32      param2;
    UINT32      param3;
    UINT32      param4;
    UINT32      dwTime;
};

struct ASIMOV_GUILD_EVENT_LIST
{
    UINT8       byEventCount;
    ASIMOV_GUILD_EVENT    stEventInfo[50];        // GUILD_DATA_NTF_HISTORY_NUM
};

struct ASIMOV_GUILD_DIPLOMAT
{
    UINT8       byType;         //GUILD_DIPLOMAT_OP_TYPE
    UINT32      dwGuildID;
    UINT32      dwLastTime;
    UINT8       byLevel;
    UINT8       byMemberCount;
    char        szGuildName[GUILD_NAME_LEN];
};

struct ASIMOV_GUILD_BUILDING
{
    UINT64      qwNameID;
    INT32       nType;
    INT32       nLevel;
};

struct ASIMOV_GUILD_BUILDING_UPGRADE
{
    UINT64      qwNameID;
    INT32       nTime;
};

struct ASIMOV_GUILD_DATA 
{
    UINT32      dwGuildID;
    char        szGuildName[GUILD_NAME_LEN];
    UINT8       byLevel;
    UINT8       byMemberCount;          // num of GUILD_MEMBER_INFO
    UINT32      dwGuildMoney;
    UINT32      dwCreateTime;
    UINT32      dwLeaderID;
    char        szLeaderName[ROLE_NAME_LEN];
    char        szCreaterName[ROLE_NAME_LEN];
    char        szNotice[GUILD_NOTICE_LEN];
    // manager
    UINT16      wStorageRight[GUILD_POSITION_COUNT];           // GUILD_POSITION_COUNT
    // history event info
    ASIMOV_GUILD_EVENT_LIST     stEventInfo;
    ASIMOV_GUILD_EVENT_LIST     stChestInfo;
    // diplomat
    UINT8       byAllianceCount;
    ASIMOV_GUILD_DIPLOMAT       stAlliance[GUILD_MAX_ALLIANCE_NUM];
    UINT8       byEnemyCount;
    ASIMOV_GUILD_DIPLOMAT       stEnemy[GUILD_MAX_ENEMY_NUM];

    INT32       nHerb;
    INT32       nWood;
    INT32       nCrystal;
    INT32       nSilver;

    INT32       nProsperity;

    INT32       arrVariables[MAX_GUILD_VARIABLE_COUNT];

    ASIMOV_GUILD_BUILDING   arrBData[GUILD_MAX_BUILDING_NUM];       // 改成变长包 Allan Tao[19.3.2014] 
    ASIMOV_GUILD_BUILDING_UPGRADE   arrBUData[GUILD_MAX_UPGRADE_BUILDING_COUNT];
    INT8        arrWelfareAuraLvl[GUILD_MAX_WELFARE_AURA_COUNT];
    INT8        arrWelfareUpgradeAuraID[GUILD_MAX_UPGRADE_AURA_COUNT];
    INT32       arrWelfareAuraUpgradeTime[GUILD_MAX_UPGRADE_AURA_COUNT];

    ASIMOV_GUILD_MEMBER     arrMemberData[GUILD_MAX_MEMBER_COUNT];
};

class CGSGuild
{
public:
    CGSGuild();
    ~CGSGuild();

public:
    BOOL Init();
    BOOL UnInit();

    BOOL    Load(ASIMOV_GUILD_DATA &data);

    UINT32  GetID()                     { return m_dwID;  }
    const char *GetName()               { return m_szName; }
    INT32   GetState()                  { return m_nState; }
    void    SetState(INT32 nState)      { m_nState = nState; }
    UINT32  GetLeaderID()               { return m_dwLeaderID; }
    void    SetLeaderID(UINT32 dwRoleID){ m_dwLeaderID = dwRoleID; }

    INT32   GetLevel()                  { return m_nLevel; }

    //const char *GetAnnounce()           { return m_szAnnounce; }
    const char *GetNotice()             { return m_szNotice; }
    INT32   GetMoney()                  { return m_nGuildMoney; }
    void    SetMoney(INT32 nMoney)      { m_nGuildMoney = nMoney; }
    INT32   GetProsperity()             { return m_nProsperity; }
    void    SetProsperity(INT32 nProsperity)   { m_nProsperity = nProsperity; }
    INT32   GetHerb()                   { return m_nHerb; }
    void    SetHerb(INT32 nHerb)        { m_nHerb = nHerb; }
    INT32   GetWood()                   { return m_nWood; }
    void    SetWood(INT32 nWood)        { m_nWood = nWood; }
    INT32   GetCrystal()                { return m_nCrystal; }
    void    SetCrystal(INT32 nCrystal)  { m_nCrystal = nCrystal; }
    INT32   GetSilver()                 { return m_nSilver; }
    void    SetSilver(INT32 nSilver)    { m_nSilver = nSilver; }

    INT32   GetMemberCount()            { return m_listMember.size(); }

    INT32   GetAllianceNum()            { return m_nAllianceNum; }
    INT32   GetEnemyNum()               { return m_nEnemyNum; }

    BOOL    SetName(const char* pcszName);
    BOOL    SetNotice(const char *pcszNotice);

    ASIMOV_GUILD_MEMBER *GetMemberByIndex(INT32 nIndex);
    ASIMOV_GUILD_MEMBER *GetMember(UINT32 dwRoleID);
    BOOL    IsOfficeFull(INT32 nPosition);
    BOOL    AddMember(UINT32 dwRoleID, UINT8 byPosition, UINT8 byFlag, INT32 nSalary);
    BOOL    DelMember(UINT32 dwRoleID);

    BOOL    ChangeStorageRight(INT32 nPosition, UINT16 wRight);


    BOOL    IsAlliance(UINT32 dwGuildID);
    BOOL    IsEnemy(UINT32 dwGuildID);

    BOOL    AddAlliance(UINT32  dwGuildID, UINT32 dwEndTime);
    BOOL    DelAlliance(UINT32 dwGuildID);
    BOOL    AddEnemy(UINT32 dwGuildID, UINT32 dwEndTime, BOOL bIsActive);
    BOOL    DelEnemy(UINT32 dwGuildID);

    UINT32  RandomApplyUnion();
    BOOL    AddUnionApp(UINT32 dwGuildID);
    BOOL    DelUnionApp(UINT32 dwGuildID);
    void    ClearUnionApp();

    BOOL    ClearApp();
    BOOL    AddApp(UINT32 dwRoleID);
    BOOL    DelApp(UINT32 dwRoleID);
    BOOL    AlreadyExistInAppList(UINT32 dwRoleID);
    INT32   GetAppNum();
    UINT32  GetRoleIDByIndexFromAppList(INT32 nIndex);

    //void    ClearViewList();
    //BOOL    AddViewList(UINT32 dwGuildID);

    //INT32   GetViewListNum();
    //UINT32  GetViewListGuildIDByIndex(INT32 nIndex);

    //
    inline void    SetMatchWarCnsptn(INT32 nConsumption)    { m_nMatchWarConsumption = nConsumption; }
    inline void    SetMatchCount(UINT8 byMatchCount)        { m_byMatchCount = byMatchCount; }
    inline INT32   GetMatchWarCnsptn()                      { return m_nMatchWarConsumption; }
    inline UINT8   GetMatchCount()                          { return m_byMatchCount; }

private:
    UINT32      m_dwID;
    char        m_szName[GUILD_NAME_LEN];
    INT32       m_nState;
    UINT32      m_dwLeaderID;
    INT32       m_nLevel;

    //CHAR        m_szAnnounce[GUILD_ANNOUNCE_LEN];        // 家族宣言  todo
    CHAR        m_szNotice[GUILD_NOTICE_LEN];         // 家族公告

    INT32       m_nGuildMoney;
    INT32       m_nProsperity;
    INT32       m_nHerb;
    INT32       m_nWood;
    INT32       m_nCrystal;
    INT32       m_nSilver;

    typedef     std::list<ASIMOV_GUILD_MEMBER>      MEMBER_LIST;
    MEMBER_LIST m_listMember;

    UINT16      m_wStorageRight[GUILD_POSITION_COUNT];

    INT32       m_nAllianceNum;
    INT32       m_nEnemyNum;
    ASIMOV_DIPLOMAT_DATA   m_arrAlliance[GUILD_MAX_ALLIANCE_NUM];
    UINT32      m_dwActiveEnemy;
    ASIMOV_DIPLOMAT_DATA   m_arrEnemy[GUILD_MAX_ENEMY_NUM];

    INT32       m_nUnionAppNum;
    UINT32      m_UnionAppList[GUILD_MAX_APPLY_ALLIANCE_NUM];


    // 
    INT32       m_nAppNum;
    UINT32      m_arrAppRoleID[MAX_APPLY_GUILD_ROLE_NUM];

    //
    //INT32       m_nValidViewGuildNum;
    //UINT32      m_arrViewGuildIDList[MAX_VIEW_GUILD_LIST_COUNT];

    // guild war
    INT32       m_nMatchWarConsumption;
    UINT8       m_byMatchCount;

};


#endif //_H_ASIMOV_GUILD_H_

#endif //_ROBOT
