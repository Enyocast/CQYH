/********************************************************************
	created:	26:6:2014   14:33
	file:		arena_mgr.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_ARENA_MGR_H_
#define _H_ARENA_MGR_H_

#include <map>
#include "base_list.h"
#include "arena_def.h"
#include "object_pool.h"
#include "timer/time_trigger.h"
#include "server_def.h"

struct COMPETITOR_DATA : BASE_LIST_NODE
{
    UINT32      dwRoleID;
    UINT8       byPointSeasonVictoryTimes;
    INT32       nPointSeasonEndTime;

    COMPETITOR_DATA():dwRoleID(0), byPointSeasonVictoryTimes(0), nPointSeasonEndTime(0) {}

    COMPETITOR_DATA(UINT32 dwID, UINT8 byTimes, INT32 nTime):dwRoleID(dwID), byPointSeasonVictoryTimes(byTimes), nPointSeasonEndTime(nTime) {}

    bool operator > (const COMPETITOR_DATA &rData)
    {
        if (this->byPointSeasonVictoryTimes > rData.byPointSeasonVictoryTimes)
            return true;
        if (this->nPointSeasonEndTime < rData.nPointSeasonEndTime)
            return true;
        return false;
    }

    bool operator < (const COMPETITOR_DATA &rData)
    {
        if (this->byPointSeasonVictoryTimes < rData.byPointSeasonVictoryTimes)
            return true;
        if (this->nPointSeasonEndTime > rData.nPointSeasonEndTime)
            return true;
        return false;
    }
};

struct ARENA_MATCH_DATA : BASE_LIST_NODE
{
    ARENA_MATCH_DATA(): dwRoleID(0), nMatchTime(0)      {}
    ARENA_MATCH_DATA(UINT32 dwID, INT32 nTime): dwRoleID(dwID), nMatchTime(nTime)       {}

    UINT32      dwRoleID;
    INT32       nMatchTime;
};

class CArenaMgr
{
public:
    static  CArenaMgr&  GetInstance();

    BOOL    MainLoop();

    BOOL    Init();
    BOOL    UnInit();

    BOOL    Load(UINT8 byGroup, UINT64 qwFund, ARENA_DB_DATA *pData);

    BOOL    ReInit();

    // common reward list
    BOOL    JoinArena(UINT8 byGroup, UINT32 dwRoleID);
    UINT64  GetFund(UINT8 byGroup);

    // match & fight
    BOOL    Match(UINT8 byGroup, UINT32 dwRoleID);

    // rank
    BOOL    UpdateSeasonInfo(UINT8 byGroup, UINT32 dwRoleID, UINT8 byPointSeasonVictoryTimes, INT32 nPointSeasonEndTime);

    INT32   GetRank(UINT8 byGroup, UINT32 dwRoleID);
    COMPETITOR_DATA* GetStrongest(UINT8 byGroup);

    // reward
    UINT32  GetReward(UINT8 byGroup);
    INT32   GetRewardMoney(UINT8 byGroup, INT32 nRank);
    
    void    Settlement();
    void    End();
    void    Clear();

    // resource
    BOOL    DeleteTriggerData(BASE_TRIGGER_NODE *pNode);


    // lua
    BOOL    LuaBroadcastArenaBegin();

protected:
    static  CArenaMgr   m_Instace;

    CArenaMgr();
    ~CArenaMgr();


    BOOL    _Match(UINT8 byGroup);
    BOOL    _CreateArena(UINT32 dwRoleID1, UINT32 dwRoleID2);

    // init settlement time
    BOOL    _InitTimer();

    // sql
    BOOL    _UpdateFund(UINT8 byGroup);
    BOOL    _UpdateRank(UINT8 byGroup);


private:
    UINT64              m_qwFund[MAX_SERVER_GROUP_COUNT];

    // rank
    CBaseList           m_RankList[MAX_SERVER_GROUP_COUNT];

    // match arena
    //INT32               m_nWaitForMatchNum;
    //ARENA_MATCH_DATA    m_MatchList[MAX_ARENA_MATCH_NUM];

    INT32               m_nMatchingNum[MAX_SERVER_GROUP_COUNT];
    CBaseList           m_MatchList[MAX_SERVER_GROUP_COUNT];
    CBaseList           m_FreeMatchDataList[MAX_SERVER_GROUP_COUNT];


    CObjectPool<BASE_TRIGGER_NODE>   m_settleTriggerPool;

};

INT32 CB_TuesdayBegin(BASE_TRIGGER_NODE *pNode);
INT32 CB_ThursdayBegin(BASE_TRIGGER_NODE *pNode);
INT32 CB_SaturdayBegin(BASE_TRIGGER_NODE *pNode);


INT32 CB_TuesdaySettlement(BASE_TRIGGER_NODE *pNode);
INT32 CB_ThursdaySettlement(BASE_TRIGGER_NODE *pNode);
INT32 CB_SaturdaySettlement(BASE_TRIGGER_NODE *pNode);
INT32 CB_ClearArena(BASE_TRIGGER_NODE *pNode);

BOOL LoadArena(std::list<void*>& rResult, void* pUserData);


#endif //_H_ARENA_MGR_H_


