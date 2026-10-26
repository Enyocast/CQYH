#ifndef _TEAM_H_
#define _TEAM_H_

#include "string_def.h"
#include "team_def.h"
#include "id_object_pool.h"

struct MS_ROLE_DATA;

class CTeam
{
public:
    CTeam();
    virtual ~CTeam();

    BOOL	Init(UINT8 byGroupID, UINT32 dwTeamID, const CHAR* pszTeamName, UINT32 dwMemberCount, UINT8 byAssignType, UINT8 byAuctionItemColorLimit);
    BOOL	UnInit();

    inline UINT32          GetTeamID(){return m_dwTeamID;}
    inline UINT8           GetGroupID(){return m_byGroupID;}

    inline const CHAR*     GetTeamName(){return m_szTeamName;}
    inline VOID            SetTeamName(const CHAR* szTeamName){strxcpy(m_szTeamName, szTeamName, TEAM_NAME_LEN);}

	inline UINT8           GetAssignType(){return m_byAssignType;}
	inline VOID            SetAssignType(INT32 byAssignType){m_byAssignType = byAssignType;}

	inline UINT8           GetAuctionItemColorLimit(){return m_byAuctionItemColorLimit;}
	inline VOID            SetAuctionItemColorLimit(INT32 byAuctionItemColorLimit){m_byAuctionItemColorLimit = byAuctionItemColorLimit;}

	inline VOID            SetMemberSizeLimit(INT32 nMemberSizeLimit) {m_nMemberSizeLimit = nMemberSizeLimit;}
    inline INT32           GetMemberSizeLimit(void) {return m_nMemberSizeLimit;}
    inline INT32           GetMemberCount(void) {return m_nMemberCount;}

    inline VOID            SetLeader(UINT32 dwLeaderID){m_dwLeaderID = dwLeaderID;}
    inline UINT32          GetLeader(){return m_dwLeaderID;}
    
	inline INT32           GetDungeonTempID(void){return m_nDungeonTempID;}
	inline INT32           GetDungeonID(void){return m_nDungeonID;}

	inline void            SetDungeonTempID(UINT32 nDungeonTempID){m_nDungeonTempID = nDungeonTempID;}
	inline void            SetDungeonID(UINT32 nDungeonID){m_nDungeonID = nDungeonID;}

	inline UINT32*         GetMemberIDList(){return m_dwMemberIDList;}
	inline UINT32          GetCreateTime(){return m_dwCreateTime;}

	inline void            SetActivityID(UINT32 dwActivityID){m_dwActivityID = dwActivityID;}
	inline UINT32          GetActivityID(){return m_dwActivityID;}

	inline void            SetActivityType(UINT32 dwActivityType){m_dwActivityType = dwActivityType;}
	inline UINT32          GetActivityType(){return m_dwActivityType;}

    BOOL			AddMember(UINT32 dwRoleID);
    MS_ROLE_DATA*   FindMember(UINT32 dwRoleID);
    MS_ROLE_DATA*   GetMember(INT32 nMemberIndex);
    UINT32          GetMemberID(INT32 nMemberIndex);
    BOOL            DelMember(UINT32 dwRoleID);
	BOOL            SelectLeader(BOOL bLeaveTeam);

protected:
    UINT8           m_byGroupID;
    UINT32          m_dwTeamID;
    CHAR			m_szTeamName[TEAM_NAME_LEN];
    INT32           m_nMemberSizeLimit;
    UINT8           m_byAssignType;
	UINT8			m_byAuctionItemColorLimit;

    UINT32          m_dwLeaderID;

    INT32           m_nMemberCount;
    UINT32          m_dwMemberIDList[MAX_TEAM_MEMBER_COUNT];

    INT32           m_nDungeonTempID;
    INT32           m_nDungeonID;
    UINT32          m_dwCreateTime;

    UINT32          m_dwActivityID;
	UINT32			m_dwActivityType;
};

class  CTeamMgr
{
public:
	CTeamMgr();
	~CTeamMgr();

	static CTeamMgr& GetInstance();

	BOOL Init(INT32 nInitSize);
	BOOL UnInit();

	CTeam* New(UINT32 dwTeamID);
	CTeam* Find(UINT32 dwTeamID);
    BOOL Delete(CTeam* pTeam);
	
	template<class TFunc>
	inline BOOL Traverse(TFunc& rFunc);

	// activity team 
	INT32 AddActivityTeam(UINT32 dwActivityType, INT32 nActivityID, INT32 nTeamID);
	INT32 DeleteActivityTeam(UINT32 dwActivityType, INT32 nActivityID, INT32 nTeamID);

	INT32* GetActivityTeamHead(UINT32 dwActivityType, INT32 nActivityID);

private:

	static CTeamMgr m_Instance;

	INT32	nActivityTeam[MAX_TEAM_ACTIVITY][MAX_TEAM_COUNT_PER_ACTIVITY];
	INT32	nDungeonTeam[MAX_TEAM_DUNGEON][MAX_TEAM_COUNT_PER_ACTIVITY];

	typedef std::map<INT32, INT32*> MAP_ID_2_TEAM;
	typedef MAP_ID_2_TEAM::iterator Iter_MapId2Team;

	MAP_ID_2_TEAM	MapActivityTeam;	
	MAP_ID_2_TEAM	MapDungeonTeam;

	CIDObjectPool<CTeam, UINT32> m_TeamMgr;
};


template<class TFunc>
inline BOOL CTeamMgr::Traverse(TFunc& rFunc)
{
	return m_TeamMgr.Traverse(rFunc);
}

struct CTraverseTeamToGS
{
    UINT32 dwGSSessionID;
    BOOL operator()(UINT32 dwTeamID, CTeam* poTeam);
};

extern UINT32 GenerateTeamID();
extern UINT32 g_TeamIndex;



#endif