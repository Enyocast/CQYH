#ifndef _AUCTION_MGR_H_
#define _AUCTION_MGR_H_

#include "id_object_pool.h"
#include "../gameworld/item.h"
#include "server_def.h"

struct Auction
{
    UINT32 m_dwAuctionID;
    UINT8 m_byGroupID;
    ItemInfo m_iteminfo;
    const ITEM_DATA* m_pItemData;
    UINT32 m_dwSellerRoleID;
    UINT32 m_dwBuyerRoleID;
    INT64 m_llPrice;
    INT64 m_llBuyoutPrice;
    INT64 m_llDepositPrice;
    UINT32 m_dwStartTime;
    UINT32 m_dwFinishTime;
    UINT8 m_byOpen;
    UINT8 m_byAuctionStatus;

    INT64 GetNextPrice() const;
    void Finish();
    void FinishWaitForPayment();
};

struct MS_ROLE_DATA;
class CAuctionThread;
class CAuctionMgr
{
public:
    CAuctionMgr();
    BOOL Init(UINT32 dwAuctionThreadCount, UINT32 dwAuctionPoolSize);
    BOOL UnInit();
    static CAuctionMgr& GetInstance() { return ms_Instance; }
    Auction* GetAuction(UINT32 auctionid);

    BOOL MainLoop(void);

    INT32 AddItem(MS_ROLE_DATA* role, ItemInfo& iteminfo, UINT8 timetype, UINT8 open, INT64 price, INT64 buyoutprice, INT64 depositprice);
    INT32 CancelItem(MS_ROLE_DATA* role, UINT32 auctionid);
    INT32 BidItem(MS_ROLE_DATA* role, UINT32 auctionid, INT64 price);
    INT32 PaidLeftMoney(Auction* auction);
    INT32 SearchItem(UINT32 sessionid, UINT32 roleid, UINT8 groupid, UINT8 sortby, UINT8 asc, INT32 templateid);
    INT32 SearchType(UINT32 sessionid, UINT32 roleid, UINT8 groupid, UINT8 sortby, UINT8 asc, UINT8 auctiontype);

    typedef std::list<Auction*> AUCTION_LIST;
    const AUCTION_LIST& GetBuyingAuctions(UINT32 roleid) const;
    const AUCTION_LIST& GetSellingAuctions(UINT32 roleid) const;
    const AUCTION_LIST& GetBoughtAuctions(UINT32 roleid) const;
    const AUCTION_LIST& GetSoldAuctions(UINT32 roleid) const;

    BOOL IsBidder(UINT32 auctionid, UINT32 roleid) const;
    BOOL AddDeposit(Auction* auction, UINT32 roleid);
    BOOL DelDeposit(Auction* auction, UINT32 roleid);
    BOOL ReturnDeposit(INT32 itemid, UINT32 roleid, INT64 depositprice);
    UINT32 GetBuyerCount(UINT32 auctionid) const;

    void _UpDateAuction(Auction* auction, UINT8 status);
    void _UpDateAuctionSql(Auction* auction);

private:
    static BOOL _Load(std::list<void*>& rResult, void* pUserData);

    BOOL _LoadAuction(UINT8 groupid, UINT32 auctionid, const char* itembuf, UINT32 itemlen, UINT32 sellerid, UINT32 buyerid, INT64 price, INT64 buyoutprice, INT64 depositprice, UINT32 starttime, UINT32 finishtime, UINT8 open, UINT8 auctionstatus);

    static BOOL _LoadAllDeposit(std::list<void*>& rReslt, void* pUserData);
    BOOL _LoadDeposit(UINT8 groupid, UINT32 auctionid, UINT32 roleid, INT64 depositprice);
    INT32 m_nLoadedCount;

    void _AddSoldAuction(UINT32 roleid, Auction* auction);
    void _AddBoughtAuction(UINT32 roleid, Auction* auction);

    static CAuctionMgr ms_Instance;
    CIDObjectPool<Auction, UINT32> m_AuctionPool;

    UINT32 _GetAuctionID(INT32 nGroupID);
    void _SetAuctionID(INT32 nGroupID, UINT32 AuctionID);
    struct SEED_FINDER
    {
        UINT32 first_id;
        UINT32 last_id;
        UINT32 biggest_gap;
        UINT32 biggest_gap_start_id;

        BOOL CheckID(UINT32 _id);
        UINT32 FindSeed();
    };
    SEED_FINDER seed_finder[MAX_SERVER_GROUP_COUNT];
    UINT32 m_dwSeeds[MAX_SERVER_GROUP_COUNT];

    UINT32 m_dwLastCheck;

    UINT32 m_dwThreadCount;
    CAuctionThread* m_threads;
    UINT32 m_dwSearchThreadIndex;

    // map<RoleID, 参与竞拍的Auction对象列表>
    typedef std::map<UINT32, AUCTION_LIST> ROLE_AUCTION_LIST;
    ROLE_AUCTION_LIST m_role_buying_auction_list;
    ROLE_AUCTION_LIST m_role_bought_auction_list;
    ROLE_AUCTION_LIST m_role_selling_auction_list;
    ROLE_AUCTION_LIST m_role_sold_auction_list;

    // 相当于一个嵌套map => map<AuctionID, map<RoleID, llDepositPrice>>
    typedef std::map<UINT32, INT64> AUCTION_DEPOSIT_MAP;
    typedef std::map<UINT32, AUCTION_DEPOSIT_MAP> ALL_DEPOSIT_MAP;
    ALL_DEPOSIT_MAP m_deposit_map;

    friend struct Auction;
};



#endif // _AUCTION_MGR_H_
