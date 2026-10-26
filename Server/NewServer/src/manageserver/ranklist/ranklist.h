#ifndef _RANKLIST_H_
#define _RANKLIST_H_

#include "server_def.h"
#include "base_list.h"
#include "object_pool.h"
#include "ranklist_def.h"

struct SArenaTeam;
struct MS_ONLINE_ROLE_DATA;
class  CMsGuild;

struct RANK_NODE : BASE_LIST_NODE
{
	INT64	llKey;
	INT64	llValue;
	INT32	nSelfRank;
	INT32	nLastRank;
};

class CRankListMgr
{
public:
	CRankListMgr();
	virtual ~CRankListMgr();

	BOOL	Init();
	BOOL	UnInit();

	static CRankListMgr& GetInstance(void);
	
	INT32	UpdateGuildRank(CMsGuild* pGuild);
	INT32	UpdateRoleRank(UINT32 dwClientSessionID, UINT32 dwRoleID, INT32 nLevel, INT32 nArmerPower, INT32 nSpiritPower, 
        INT32 nTotalPower, INT32 nMoney, INT32 nAchievement, INT32 nMaster, INT32 nPkValue, INT32 nTotalKillCount, 
		INT32 nClass, INT32 nExp, INT32 nItemPower);
	INT32	UpdateRankNode(INT32 nServerGroupID, INT32 nRankListType, INT64 llKey, INT64 llValue);
	BOOL	UpdateLastRank(INT32 nServerGroupID, INT32 nRankListType);

	RANK_NODE* GetSelfRank(INT32 nServerGroupID, INT32 nRankListType, INT64 llKey);
	INT32	GetRankNodeCount(INT32 nServerGroupID, INT32 nRankListType);
	BOOL	DelRankNode(INT32 nServerGroupID, INT64 llKey);

	CBaseList* GetRankList(INT32 nServerGroupID, INT32 nRankListType);

	void	AddRankAchievementID(INT32 nRankAchID);
	void	DelRankAchievementID(INT32 nRankAchID);

	void	BeginRankAchievementID(void);
	INT32	NextRankAchievementID(void);

	BOOL	UpdateAverageLevel(void);
	inline INT32* GetAverageLevel(void);

    // lua
    BOOL DelGuildRankNode(INT32 nServerGroupID, UINT32 dwGuildID);

private:
    static BOOL	_Load(std::list<void*>& rResult, void* pUserData);

	BOOL	_SetLastRank(INT32 nServerGroupID, INT32 nRankListType, INT64 llKey, INT32 nLastRank);

private:
    static CRankListMgr	ms_Instance;

    BOOL    m_bLoading;
    INT32   m_nLoadedCount;
	INT32	m_nAverageLevel[MAX_SERVER_GROUP_COUNT];

	CObjectPool<RANK_NODE>	m_RankPool;
	CBaseList m_RankList[MAX_SERVER_GROUP_COUNT][rlTotal];	// °ñÊ×°ñÎ²

	typedef std::map<INT64, RANK_NODE*> MAP_KEY_2_RANKING;
	typedef MAP_KEY_2_RANKING::iterator Iter_MapKey2RankNode;

	MAP_KEY_2_RANKING m_Map_Key_2_Rank[MAX_SERVER_GROUP_COUNT][rlTotal]; 

	typedef std::set<INT32> TRankAchievementList;
	TRankAchievementList m_AchievementList;
	TRankAchievementList::iterator m_AchItr;
};

inline INT32* CRankListMgr::GetAverageLevel(void)
{
	return m_nAverageLevel;
}


#endif //_RANKLIST_H_