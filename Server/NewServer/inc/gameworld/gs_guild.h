/********************************************************************
	created:	13:11:2013   10:36
	file:		gs_guild.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GS_GUILD_H_
#define _H_GS_GUILD_H_

#include "gs_guild_data.h"

#ifndef _ROBOT

#include "string_def.h"
#include "guild_def.h"
struct GS_GUILD_MEMBER 
{
    UINT32      dwRoleID;
    INT32       nPosition;

    GS_GUILD_MEMBER() : dwRoleID(0), nPosition(0)  {}
    GS_GUILD_MEMBER(UINT32 dwID, INT32 nP) : dwRoleID(dwID), nPosition(nP)  {}

    bool operator == (UINT32 dwRoleID)
    {
        return dwRoleID == dwRoleID;
    }
};

class CScene;


class CGSGuild
{
public:
    CGSGuild();
    ~CGSGuild();

public:
    BOOL Init();
    BOOL UnInit();

    BOOL    Create(UINT32 dwGuildID, INT32 nState, UINT32 dwLeaderID, const char *pcszGuildName, 
        INT32 nAllianceNum, UINT32 arrAlliance[], INT32 nEnemyNum, UINT32 arrEnemy[], 
        INT8 *arrWelfareLvl, INT32 *arrVariable, INT32 nServerGroup);
    BOOL    Destory();

    inline  UINT32 GetID();
    inline  INT32 GetLevel();
    inline  const char *GetName();
    inline  INT32 GetState();
    inline  void  SetState(INT32 nState);
    inline  UINT32 GetLeaderID();
    inline  void  SetLeaderID(UINT32 dwRoleID);
	inline	INT32 GetServerGroup(void);

    GS_GUILD_MEMBER *GetMember(UINT32 dwRoleID);
    INT32   GetMaxMemberCount();
    BOOL    AddMember(UINT32 dwRoleID, INT32 nPosition);
    BOOL    DelMember(UINT32 dwRoleID);
    BOOL    IsMember(UINT32 dwRoleID);
	UINT32	GetFirstMember(void);
	UINT32	GetNextMember(void);

    INT32   GetWelfareLevelByType(INT32 nType);
    BOOL    SetWelfareLevelByType(INT32 nType, INT32 nLevel);
    BOOL    IsActiveWelfareBuffer(INT32 nType);

    
    INT32   GetBuildingNumByType(INT32 nType);
    INT32   GetBuildingMaxLevelByType(INT32 nType);
    BOOL    IsBuildingEnable(NAMEID qwNameID);

    //GS_G_B_DATA*    GetMaxLevelBuildingDataByType(INT32 nType);
    GS_G_B_DATA*    GetFunBuildingDataByType(INT32 nType);
    GS_G_B_DATA*    GetBuildingDataByNpcID(NAMEID qwNpcNameID);
    GS_G_B_DATA*    GetBuildingDataByString(const char *pcszNameID);
    BOOL    AddBuilding(NAMEID qwNameID, INT32 nType, INT32 nLevel);
    void    DelBuilding(NAMEID qwNameID);

    GS_G_B_DATA*    FirstUnFunBuilding();
    GS_G_B_DATA*    NextUnFunBuilding();

    GS_G_B_DATA*    GetUpgradBuildingDataByNpcID(NAMEID qwNpcNameID);
    BOOL    AddUpgradeBuilding(NAMEID qwNameID, INT32 nType, INT32 nLevel);
    void    DelUpgradeBuilding(NAMEID qwNameID);
    GS_G_B_DATA*    FirstUpgradeBuilding();
    GS_G_B_DATA*    NextUpgradeBuilding();


    // todo_tq 联盟敌对关系，考虑是不是放在mgr里面， 目前看来用双BaseList或者单BaseList是不划算的，或者有查询障碍的 Allan Tao[14.11.2013] 
    BOOL    AddAlliance(UINT32 dwTargetID);
    BOOL    DelAlliance(UINT32 dwTargetID);
    BOOL    IsAlliance(UINT32 dwTargetID);

    BOOL    AddEnemy(UINT32 dwTargetID);
    BOOL    DelEnemy(UINT32 dwTargetID);
    BOOL    IsEnemy(UINT32 dwTargetID);

    INT32   GetVariable(INT32 nIndex);
    BOOL    SetVariable(INT32 nIndex, INT32 nValue);    // cannot register to lua

    inline INT32   GetMoney();
    inline void    SetMoney(INT32 nMoney);

    inline INT32   GetHerb();
    inline void    SetHerb(INT32 nHerb);

    inline INT32   GetWood();
    inline void    SetWood(INT32 nWood);

    inline INT32   GetCrystal();
    inline void    SetCrystal(INT32 nCrystal);

    inline INT32   GetSilver();
    inline void    SetSilver(INT32 nSilver);

    INT32   GetRes(INT32 nResType);
    INT32   GetMaxRes(INT32 nResType);
    INT32   GetMaxStorage(INT32 nType);

	inline UINT32 GetSabacEnrollTime(INT32 nIndex);
	void SetSabacEnrollTime(UINT32 dwTime);
	BOOL HasEnrolledSabac(void);
	BOOL IsJoinSabacToday(void);

	inline BOOL IsOccupiedSabac(void);
	inline void OccupySabac(BOOL bOccupied);

    // war
    inline BOOL IsWarTime();
    inline void SetWarCharacter(INT32 nCharacter);
    inline INT32 GetWarCharacter();

    // activity
    BOOL    IsActivityOpen(INT32 nActivityID);
    INT32   GetActivityMaxRepeatNum(INT32 nActivityID);
private:
    UINT32      m_dwID;
    char        m_szName[GUILD_NAME_LEN];
    INT32       m_nState;
    UINT32      m_dwLeaderID;
	UINT32		m_dwSabacEnrollTime[MAX_SABAC_ENROLL_COUNT];
	BOOL		m_bOccupiedSabac;
	INT32		m_nServerGroup;

    typedef     std::list<GS_GUILD_MEMBER>   MEMBER_LIST;
    MEMBER_LIST    m_MemberList;
	MEMBER_LIST::iterator m_MemberIterator;
 
    GS_G_B_DATA        m_FunBuildingList[GUILD_B_FUNATIONAL_NUM];
    typedef std::map<NAMEID, GS_G_B_DATA>   GS_G_BUILDING_MAP;
    GS_G_BUILDING_MAP  m_BuildingList;
    INT32               m_nBIndex;
    GS_G_BUILDING_MAP::iterator    m_BCursor;

    typedef std::map<NAMEID, GS_G_B_DATA>   GS_U_G_BUILDING_MAP;
    GS_U_G_BUILDING_MAP  m_arrUBuildingList;
    GS_U_G_BUILDING_MAP::iterator    m_UBCursor;

    INT8        m_arrWelfareAuraLevel[GUILD_MAX_WELFARE_AURA_COUNT];

    // res
    INT32       m_nMoney;
    INT32       m_nHerb;
    INT32       m_nWood;
    INT32       m_nCrystal;
    INT32       m_nSilver;

    // diplomat
    INT32       m_nAllianceNum;
    UINT32      m_arrAlliance[GUILD_MAX_ALLIANCE_NUM];
    INT32       m_nEnemyNum;
    UINT32      m_arrEnemy[GUILD_MAX_ENEMY_NUM];
    INT32       m_arrVariables[MAX_GUILD_VARIABLE_COUNT];

    // war
    INT32       m_nWarCharacter;
};




#include "gs_guild_inl.h"


#else
#include "asimov_guild.h"

#endif // !_ROBOT


#endif //_H_GS_GUILD_H_


