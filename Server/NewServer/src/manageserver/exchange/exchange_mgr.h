#ifndef _EXCHANGE_MGR_H_
#define _EXCHANGE_MGR_H_

#include "exchange_orders.h"
#include "id_object_pool.h"
#include "object_pool.h"
#include "server_def.h"
#include "exchange_def.h"

struct MS_ROLE_DATA;
struct MS_ONLINE_ROLE_DATA;

struct ExchangeLog
{
    UINT64 qwOrderID;
    UINT32 dwTime;
    UINT8 byType;
    INT32 nPrice;
    INT32 nCount;
};

class CExchangeMgr
{
public:
    BOOL Init(UINT32 dwOrderPoolSize);
    BOOL UnInit();
    static CExchangeMgr& GetInstance() { return ms_Instance; }

    BOOL MainLoop();
    INT32 AddOrder(MS_ROLE_DATA* role, UINT8 ordertype, INT32 count, INT32 price, const char* billing_order_id);
    INT32 CancelOrder(MS_ONLINE_ROLE_DATA* online_role, UINT64 orderid);

    void AddSystemOrder(UINT32 dwTLUserID, UINT8 groupid, INT32 price, INT32 count);
    void CancelSystemOrder(UINT32 dwTLUserID, UINT8 groupid, UINT64 orderid);

    void GetPrices(UINT8 groupid, UINT8 ordertype, UINT8 requirecount, UINT8& count, INT32 price[], INT32 handcount[]);
    void GetCounts(UINT8 groupid, UINT8 ordertype, INT32 price, UINT8 requirecount, UINT8& count, UINT32 roleid[], INT32 handcount[], UINT64 orderid[]);

    typedef std::list<Order*> ORDER_LIST;
    const ORDER_LIST& GetOrders(UINT8 ordertype, UINT32 roleid) const;
    const ORDER_LIST& GetFinishedOrders(UINT32 roleid) const;

    typedef std::list<ExchangeLog*> LOG_LIST;
    const LOG_LIST& GetLogs(UINT32 roleid) const;
    void AddLog(UINT32 roleid, UINT64 orderid, UINT32 curtime, UINT8 ordertype, INT32 price, INT32 count);

    void GetSystemLimit(UINT32 dwTLUserID, UINT8 groupid);
    void SetSystemLimit(UINT32 dwTLUserID, UINT8 groupid, INT32 high, INT32 low, INT32 single, INT32 daily);

    void OnBillingFreeze(INT32 result, UINT32 roleid, INT32 price, INT32 count, const char* billing_order_id);
    void OnBillingUnfreeze(INT32 result);
    void OnBillingConfirm(INT32 result, UINT64 buying_order_id, UINT32 buyer_roleid, INT32 count, INT32 money, const char* billing_order_id);
    void OnBillingTransfer(INT32 result, UINT64 buying_order_id, UINT32 buyer_roleid, UINT32 seller_roleid, INT32 count, INT32 money, const char* billing_order_id);

private:
    static BOOL _Load(std::list<void*>& rResult, void* pUserData);
    BOOL _LoadOrder(UINT8 groupid, UINT64 orderid, UINT32 ordertime, UINT8 ordertype, UINT8 orderstatus, UINT32 roleid, INT32 price, INT32 count, INT32 curcount, INT32 curmoney, const char* billing_order_id);
    void _DeleteOrder(Order* order, UINT8 status);

    static BOOL _LoadLog(std::list<void*>& rResult, void* pUserData);

    static CExchangeMgr ms_Instance;
    CExchangeOrders m_orders[MAX_SERVER_GROUP_COUNT];
    CIDObjectPool<Order, UINT64> m_order_pool;
    CObjectPool<ExchangeLog> m_log_pool;
    //UINT32 m_dwExchangeIDIndex;
    //UINT32 m_dwTotalOrderCount;
    INT32 m_nLoadedCount;

    typedef std::map<UINT32, ORDER_LIST> ROLE_ORDER_LIST;
    ROLE_ORDER_LIST m_role_buying_order_list, m_role_selling_order_list, m_role_finished_order_list;

    typedef std::map<UINT32, LOG_LIST> ROLE_LOG_LIST;
    ROLE_LOG_LIST m_role_log_list;

    struct LimitParams
    {
        INT32 nPriceHigh;
        INT32 nPriceLow;
        INT32 nSingleOrderLimit;
        INT32 nDailyOrderLimit;
        INT32 nDay;
        INT32 nDailyOrderCurCount;
    };
    LimitParams limit_params[MAX_SERVER_GROUP_COUNT];

    friend class CExchangeOrders;
    friend struct OrderList;
};

#endif // _EXCHANGE_MGR_H_
