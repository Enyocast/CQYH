#ifndef _EXCHANGE_ORDERS_H_
#define _EXCHANGE_ORDERS_H_

#include <functional>
#include "item_def.h"
#include "string_def.h"

struct Order
{
    UINT64 m_qwOrderID;
    UINT32 m_dwOrderTime;
    UINT8 m_byOrderType;
    UINT8 m_byOrderStatus;
    UINT32 m_dwRoleID;
    INT32 m_nPrice;
    INT32 m_nCount;         //用户提交的总手数，真正有效的手数是下面的CurCount，此Count仅用于客户端显示用
    INT32 m_nCurCount;      //当前剩余手数
    INT32 m_nCurMoney;

    INT32 m_nBillingCount;  //由于计费平台并非先到先处理，因此必须等到所有的tranfer的回复后才可以unfreeze，此变量仅记录平台中Freeze的笔数，大部分情况下此数值应等同于CurCount
    char m_szBillingOrderID[OA_BILLING_ORDER_ID_LEN];
};

struct OrderList
{
    INT32 m_nHandCount;
    std::list<Order*> m_lstOrders;

    OrderList():m_nHandCount(0) {}

    void AddOrder(Order* order)
    {
        m_lstOrders.push_back(order);
        m_nHandCount += order->m_nCurCount;
    }

    void ClearExpireOrder();
};

class CExchangeOrders
{
public:
    BOOL Init();
    BOOL UnInit();

    void AddOrder(Order* order);
    BOOL CancelOrder(Order* order);
    void GetBuyingPrices(UINT8 requirecount, UINT8& count, INT32 price[], INT32 handcount[]) const;
    void GetSellingPrices(UINT8 requirecount, UINT8& count, INT32 price[], INT32 handcount[]) const;
    void GetCounts(UINT8 ordertype, INT32 price, UINT8 requirecount, UINT8& count, UINT32 roleid[], INT32 handcount[], UINT64 orderid[]) const;
    BOOL MainLoop();

    UINT8 m_byGroupID;

private:
    typedef std::map<INT32, OrderList, std::less<INT32> > SELLING_ORDER_MAP;
    typedef std::map<INT32, OrderList, std::greater<INT32> > BUYING_ORDER_MAP;

    SELLING_ORDER_MAP m_sell_orders;
    BUYING_ORDER_MAP m_buy_orders;
};


#endif // _EXCHANGE_ORDERS_H_
