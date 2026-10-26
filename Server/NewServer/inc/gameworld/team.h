#ifndef _TEAM_MGR_H_
#define _TEAM_MGR_H_

#include "team_def.h"
#include "object_pool.h"
#include "string_def.h"
#include "base_list.h"

struct Item;
class CRole;
class CDrop;
class CScene;


struct TeamMember
{
	char szRoleName[ROLE_NAME_LEN];
	UINT32 dwRoleID;
	INT32 nLevel;
	INT32 nSex;
	INT32 nClass;

	INT32 eBidState;
	INT32 nOfferPrice;
};

//struct GS_TEAM_AUCTION_BID_MEMBER : BASE_LIST_NODE
//{
//	UINT32	dwMemberID;
//	UINT32	dwBidMoney;
//};
//
//struct GS_TEAM_AUCTION_ITEM : BASE_LIST_NODE
//{
//	UINT32	dwCanBidRoleID[MAX_TEAM_MEMBER_COUNT];			//有权拍卖的
//	UINT32	dwCanRewardMoneyRoleID[MAX_TEAM_MEMBER_COUNT];	//有权分钱的
//	UINT32	dwCanRewardMoneyRoleCount;
//	UINT32	dwAbandonRoleID[MAX_TEAM_MEMBER_COUNT];			// 放弃拍卖的
//	UINT32	dwAbandonRoleCount;
//	Item*	pItem;
//	UINT32	nIndex;											// 拍卖序号
//};

struct TeamAuctionItem
{
	UINT32 dwIndex;
	Item* poItem;
	CScene* poScene;

	typedef std::list<UINT32> TIDList;
	TIDList BidRoleList;
	TIDList RewardRoleList;

	UINT32 dwCurrentPrice;
	UINT32 dwWinnerID;
	UINT32 dwEndFrm;
	BOOL bInBidding;

	typedef std::map<UINT32, UINT32> TDepositeMap;
	TDepositeMap DepositeMap;
};

class CTeamInGS
{
public:
	CTeamInGS();
	virtual ~CTeamInGS();

	INT32 Init(void);
	INT32 UnInit(void);

	INT32 Mainloop(void);

	inline INT32 GetGroupID();
	inline void	SetGroupID(INT32 nGroupID);

	inline UINT32 GetTeamID();
	inline void	SetTeamID(UINT32 dwTeamID);

	inline UINT32 GetRoomID();
	inline void	SetRoomID(UINT32 dwRoomID);

	inline INT32 GetAssignType(void);
	inline void	SetAssignType(INT32 eAssignType);

	inline INT32 GetAuctionItemColorLimit(void);
	inline void	SetAuctionItemColorLimit(INT32 nAuctionItemColorLimit);

	inline UINT32 GetLeaderID();
	inline void	SetLeaderID(UINT32 dwLeaderID);

	inline UINT32 GetActivityType();
	inline void SetActivityType(UINT32 dwActivityType);

	inline UINT32 GetActivityID();
	inline void SetActivityID(UINT32 dwActivityID);

	inline char* GetTeamName();

	BOOL AddNewMember(UINT32 dwMemberID, char* szRoleName, INT32 nLevel, INT32 nSex, INT32 nClass);
	BOOL RemoveMember(UINT32 dwMemberID);

	inline UINT32 GetMaxMemberCount();
	inline void	SetMaxMemberCount(UINT32 dwMaxMemberCount);

	inline UINT32 GetMemberCount();
	inline void	SetMemberCount(UINT32 dwMemberCount);

	inline UINT32 GetCreateTime();
	inline void	SetCreateTime(UINT32 dwCreateTime);

	inline TeamMember& GetMemberTable(INT32 nIndex);

	// team auction

	BOOL AddAuctionItem(CDrop* pDrop);
	INT32 DelAuctionItem(TeamAuctionItem* poAuctionItem);

	INT32 CanBeAddedtoBidAuction(Item* pItem);

	INT32 Bid(CRole* pRole, UINT32 dwAuctionIndex, UINT32 dwOfferPrice);
	INT32 BidAbandon(CRole* poRole, UINT32 dwAuctionIndex);

	BOOL HasMasterRelationShip(CRole* poRole, INT64 llDist2);

private:
	INT32 _CanBid(CRole* pRole, TeamAuctionItem* poAuctionItem, UINT32 dwOfferPrice);
	BOOL _AddDeposite(TeamAuctionItem* poItem, UINT32 dwRoleID, UINT32 dwDeposite);

private:
	char			m_szTeamName[TEAM_NAME_LEN];

	INT32           m_nGroupID;
	UINT32          m_dwTeamID;
	UINT32          m_dwRoomID;
	INT32			m_eAssignType;
	INT32			m_nAuctionItemColorLimit;
	UINT32          m_dwLeader;

	UINT32          m_nMaxMemberCount;
	UINT32          m_nMemberCount;
	TeamMember		m_MemberTable[MAX_TEAM_MEMBER_COUNT];

	UINT32          m_dwTgtSceneTempID;
	UINT32          m_dwTgtSceneID;
	INT32           m_nTgtX;
	INT32           m_nTgtY;
	INT32           m_nTgtZ;

	UINT32          m_dwCreateTime;
	UINT32			m_dwAuctionItemIndex;

	UINT32			m_dwAcitivtyType;
	UINT32			m_dwAcitivtyID;

	// team auction 
//	typedef std::vector<GS_TEAM_AUCTION_ITEM> VecTeamAuctionContainer;
//	typedef VecTeamAuctionContainer::iterator IterVecTeamAuctionContainer;
//	VecTeamAuctionContainer	m_VecTeamAuctionContainer;	// 管理拍卖物品
//
//	CObjectPool<GS_TEAM_AUCTION_BID_MEMBER>	m_BidMumberPool; // 管理出价者，维护有序
//	CBaseList m_BidMemberList;

	typedef std::list<TeamAuctionItem*> TAuctionItemList;
	TAuctionItemList m_AuctionItemList;

};

struct GS_SCENE_TEAM_MEMBER
{
	UINT32 dwRoleID;
	INT32  nSyncFrame;
};

struct GS_SCENE_TEAM
{
	UINT64					qwBattleTeamID;
	UINT8					byMemberCount;
	GS_SCENE_TEAM_MEMBER	dwMemberID[MAX_TEAM_MEMBER_COUNT];
};

inline INT32 CTeamInGS::GetGroupID()
{
	return m_nGroupID;
}

inline void CTeamInGS::SetGroupID(INT32 nGroupID)
{
	m_nGroupID = nGroupID;
}

inline UINT32 CTeamInGS::GetTeamID()
{
	return m_dwTeamID;
}

inline void	CTeamInGS::SetTeamID(UINT32 dwTeamID)
{
	m_dwTeamID = dwTeamID;
}

inline UINT32 CTeamInGS::GetRoomID()
{
	return m_dwRoomID;
}

inline void	CTeamInGS::SetRoomID(UINT32 dwRoomID)
{
	m_dwRoomID = dwRoomID;
}

inline char* CTeamInGS::GetTeamName()
{
	return m_szTeamName;
}

inline INT32 CTeamInGS::GetAssignType(void)
{
	return m_eAssignType;
}

inline void	CTeamInGS::SetAssignType(INT32 eAssignType)
{
	m_eAssignType = eAssignType;
}

inline INT32 CTeamInGS::GetAuctionItemColorLimit(void)
{
	return m_nAuctionItemColorLimit;
}

inline void	CTeamInGS::SetAuctionItemColorLimit(INT32 nAuctionItemColorLimit)
{
	m_nAuctionItemColorLimit = nAuctionItemColorLimit;
}

inline UINT32 CTeamInGS::GetLeaderID()
{
	return m_dwLeader;
}

inline void	CTeamInGS::SetLeaderID(UINT32 dwLeaderID)
{
	m_dwLeader = dwLeaderID;
}

inline UINT32 CTeamInGS::GetMaxMemberCount()
{
	return m_nMaxMemberCount;
}

inline void	CTeamInGS::SetMaxMemberCount(UINT32 dwMaxMemberCount)
{
	m_nMaxMemberCount = dwMaxMemberCount;
}

inline UINT32 CTeamInGS::GetMemberCount()
{
	return m_nMemberCount;
}

inline void	CTeamInGS::SetMemberCount(UINT32 dwMemberCount)
{
	m_nMemberCount = dwMemberCount;
}

inline UINT32 CTeamInGS::GetCreateTime()
{
	return m_dwCreateTime;
}

inline void	CTeamInGS::SetCreateTime(UINT32 dwCreateTime)
{
	m_dwCreateTime = dwCreateTime;
}

inline TeamMember& CTeamInGS::GetMemberTable(INT32 nIndex)
{
	return m_MemberTable[nIndex];
}

inline UINT32 CTeamInGS::GetActivityType()
{
	return m_dwAcitivtyType;
}

inline void CTeamInGS::SetActivityType(UINT32 dwActivityType)
{
	m_dwAcitivtyType = dwActivityType;
}

inline UINT32 CTeamInGS::GetActivityID()
{
	return m_dwAcitivtyID;
}

inline void CTeamInGS::SetActivityID(UINT32 dwActivityID)
{
	m_dwAcitivtyID = dwActivityID;
}

#endif