#include "stdafx.h"
#include "exchange_orders.h"
#include "exchange_mgr.h"
#include "exchange_history.h"
#include "db/ms_sql_stmt_list.h"
#include "real_money_shop/oa_bill_mgr.h"
#include "role_data_mgr.h"
#include "money_def.h"
#include "manageserver.h"

BOOL CExchangeOrders::Init()
{
    return TRUE;
}

BOOL CExchangeOrders::UnInit()
{
    m_sell_orders.clear();
    m_buy_orders.clear();

    return TRUE;
}

void CExchangeOrders::AddOrder(Order* order)
{
    LOG_PROCESS_ERROR(order);
    LOG_PROCESS_ERROR(order->m_byOrderType == eotBuy || order->m_byOrderType == eotSell);
    LOG_PROCESS_ERROR(order->m_byOrderStatus == eosEffective);

    if (order->m_byOrderType == eotBuy)
    {
        m_buy_orders[order->m_nPrice].AddOrder(order);
    }
    else
    {
        m_sell_orders[order->m_nPrice].AddOrder(order);
    }

Exit0:
    return;
}

BOOL CExchangeOrders::CancelOrder(Order* order)
{
    LOG_PROCESS_ERROR(order);
    LOG_PROCESS_ERROR(order->m_byOrderType == eotBuy || order->m_byOrderType == eotSell);

    if (order->m_byOrderType == eotBuy)
    {
        BUYING_ORDER_MAP::iterator it = m_buy_orders.find(order->m_nPrice);
        LOG_PROCESS_ERROR(it != m_buy_orders.end());

        {
            OrderList& order_list = it->second;
            order_list.m_nHandCount -= order->m_nCurCount;
            order_list.m_lstOrders.remove(order);
            if (order_list.m_lstOrders.empty())
            {
                LOG_CHECK_ERROR(order_list.m_nHandCount == 0);
                m_buy_orders.erase(it);
            }
        }
    }
    else
    {
        SELLING_ORDER_MAP::iterator it = m_sell_orders.find(order->m_nPrice);
        LOG_PROCESS_ERROR(it != m_sell_orders.end());

        {
            OrderList& order_list = it->second;
            order_list.m_nHandCount -= order->m_nCurCount;
            order_list.m_lstOrders.remove(order);
            if (order_list.m_lstOrders.empty())
            {
                LOG_CHECK_ERROR(order_list.m_nHandCount == 0);
                m_sell_orders.erase(it);
            }
        }
    }

    return TRUE;

Exit0:
    return FALSE;
}

void CExchangeOrders::GetBuyingPrices(UINT8 requirecount, UINT8& count, INT32 price[], INT32 handcount[]) const
{
    count = 0;
    for (BUYING_ORDER_MAP::const_iterator it = m_buy_orders.begin(); it != m_buy_orders.end(); ++it)
    {
        price[count] = it->first;
        handcount[count] = it->second.m_nHandCount;
        count++;

        if (count >= requirecount)
            break;
    }
}

void CExchangeOrders::GetSellingPrices(UINT8 requirecount, UINT8& count, INT32 price[], INT32 handcount[]) const
{
    count = 0;
    for (SELLING_ORDER_MAP::const_iterator it = m_sell_orders.begin(); it != m_sell_orders.end(); ++it)
    {
        price[count] = it->first;
        handcount[count] = it->second.m_nHandCount;
        count++;

        if (count >= requirecount)
            break;
    }
}

void CExchangeOrders::GetCounts(UINT8 ordertype, INT32 price, UINT8 requirecount, UINT8& count, UINT32 roleid[], INT32 handcount[], UINT64 orderid[]) const
{
    count = 0;
    if (ordertype == eotBuy)
    {
        BUYING_ORDER_MAP::const_iterator it = m_buy_orders.find(price);
        if (it != m_buy_orders.end())
        {
            const OrderList& ol = it->second;
            for (std::list<Order*>::const_iterator it2 = ol.m_lstOrders.begin(); it2 != ol.m_lstOrders.end(); ++it2)
            {
                roleid[count] = (*it2)->m_dwRoleID;
                handcount[count] = (*it2)->m_nCurCount;
                orderid[count] = (*it2)->m_qwOrderID;

                count++;
                if (count >= requirecount)
                    break;
            }
        }
    }
    else
    {
        SELLING_ORDER_MAP::const_iterator it = m_sell_orders.find(price);
        if (it != m_sell_orders.end())
        {
            const OrderList& ol = it->second;
            for (std::list<Order*>::const_iterator it2 = ol.m_lstOrders.begin(); it2 != ol.m_lstOrders.end(); ++it2)
            {
                roleid[count] = (*it2)->m_dwRoleID;
                handcount[count] = (*it2)->m_nCurCount;
                orderid[count] = (*it2)->m_qwOrderID;

                count++;
                if (count >= requirecount)
                    break;
            }
        }
    }
}

BOOL CExchangeOrders::MainLoop()
{
    BOOL bRet = FALSE;
    UINT32 curtime = CManageServer::GetInstance().GetGameTime();

    //处理过期订单
    for (BUYING_ORDER_MAP::iterator it = m_buy_orders.begin(); it != m_buy_orders.end();)
    {
        OrderList& order_list = it->second;
        order_list.ClearExpireOrder();
        if (order_list.m_nHandCount <= 0)
        {
            m_buy_orders.erase(it++);
        }
        else
        {
            ++it;
        }
    }
    for (SELLING_ORDER_MAP::iterator it = m_sell_orders.begin(); it != m_sell_orders.end();)
    {
        OrderList& order_list = it->second;
        order_list.ClearExpireOrder();
        if (order_list.m_nHandCount <= 0)
        {
            m_sell_orders.erase(it++);
        }
        else
        {
            ++it;
        }
    }

    //撮合订单
    while (!m_buy_orders.empty() && !m_sell_orders.empty() && m_buy_orders.begin()->first >= m_sell_orders.begin()->first)
    {
        OrderList& buy_list = m_buy_orders.begin()->second;
        OrderList& sell_list = m_sell_orders.begin()->second;
        INT32 final_price = m_sell_orders.begin()->first;
        LOG_PROCESS_ERROR(final_price > 0);

        while(!buy_list.m_lstOrders.empty() && !sell_list.m_lstOrders.empty())
        {
            Order* buy_order = buy_list.m_lstOrders.front();
            Order* sell_order = sell_list.m_lstOrders.front();

            INT32 tax = (final_price * EXCHANGE_TAX + 99) / 100;
            if (tax < 1)
                tax = 1;
            
            INT32 final_count = buy_order->m_nCurCount;
            if (final_count > sell_order->m_nCurCount)
                final_count = sell_order->m_nCurCount;
            LOG_PROCESS_ERROR(final_count > 0);

            INT32 final_tax = tax * final_count;
            INT32 final_money = final_price * final_count;

            if (sell_order->m_dwRoleID)
            {
                MS_ROLE_DATA* buyer = CRoleDataMgr::GetInstance().FindRole(buy_order->m_dwRoleID);
                LOG_PROCESS_ERROR(buyer);
                
                MS_ROLE_DATA* seller = CRoleDataMgr::GetInstance().FindRole(sell_order->m_dwRoleID);
                LOG_PROCESS_ERROR(seller);

                bRet = COABillMgr::GetInstance().DoTransferCurrency(buy_order->m_qwOrderID, sell_order->m_qwOrderID, buyer, seller,
                    buy_order->m_szBillingOrderID, final_count, final_money, final_tax);
                LOG_PROCESS_ERROR(bRet);
            }
            else
            {
                bRet = COABillMgr::GetInstance().DoConfirmFrozenCurrency(buy_order->m_qwOrderID, sell_order->m_qwOrderID, buy_order->m_dwRoleID, buy_order->m_szBillingOrderID, final_count, final_money);
                LOG_PROCESS_ERROR(bRet);
            }

            bRet = CExchangeHistory::GetInstance().AddPrice(m_byGroupID, final_price, final_count, curtime);
            LOG_PROCESS_ERROR(bRet);

            buy_list.m_nHandCount -= final_count;
            buy_order->m_nCurCount -= final_count;
            buy_order->m_nCurMoney -= final_money;

            bRet = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlUpdateExchangeOrderCount, NULL, NULL, "ddul", buy_order->m_nCurCount, buy_order->m_nCurMoney, buy_order->m_qwOrderID);
            LOG_CHECK_ERROR(bRet);

            if (buy_order->m_nCurCount == 0)
            {
                buy_list.m_lstOrders.pop_front();
                CExchangeMgr::GetInstance().m_role_buying_order_list[buy_order->m_dwRoleID].remove(buy_order);
            }

            sell_list.m_nHandCount -= final_count;
            sell_order->m_nCurCount -= final_count;
            sell_order->m_nCurMoney -= final_count * 10000;
            
            bRet = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlUpdateExchangeOrderCount, NULL, NULL, "ddul", sell_order->m_nCurCount, sell_order->m_nCurMoney, sell_order->m_qwOrderID);
            LOG_CHECK_ERROR(bRet); 
            
            if (sell_order->m_nCurCount == 0)
            {
                sell_list.m_lstOrders.pop_front();
                CExchangeMgr::GetInstance().m_role_selling_order_list[sell_order->m_dwRoleID].remove(sell_order);

                CExchangeMgr::GetInstance()._DeleteOrder(sell_order, eosFinished);
            }

            bRet = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlInsertExchangeLog, NULL, NULL, "ucududuluduldd", m_byGroupID,
                curtime, sell_order->m_dwRoleID, sell_order->m_qwOrderID, buy_order->m_dwRoleID, buy_order->m_qwOrderID, final_price, final_count);
            CExchangeMgr::GetInstance().AddLog(sell_order->m_dwRoleID, sell_order->m_qwOrderID, curtime, eotSell, final_price, final_count);
            CExchangeMgr::GetInstance().AddLog(buy_order->m_dwRoleID, buy_order->m_qwOrderID, curtime, eotBuy, final_price, final_count);
        }

        if (buy_list.m_lstOrders.empty())
        {
            LOG_CHECK_ERROR(buy_list.m_nHandCount == 0);
            m_buy_orders.erase(m_buy_orders.begin());
        }

        if (sell_list.m_lstOrders.empty())
        {
            LOG_CHECK_ERROR(sell_list.m_nHandCount == 0);
            m_sell_orders.erase(m_sell_orders.begin());
        }
    }

    return TRUE;

Exit0:
    return FALSE;
}

void OrderList::ClearExpireOrder()
{
    for (std::list<Order*>::iterator it = m_lstOrders.begin(); it != m_lstOrders.end();)
    {
        Order* order = *it;

        if (order->m_dwRoleID && order->m_dwOrderTime + EXCHANGE_TIME < CManageServer::GetInstance().GetGameTime())
        {
            m_nHandCount -= order->m_nCurCount;
            m_lstOrders.erase(it++);

            if (order->m_byOrderType == eotBuy)
                CExchangeMgr::GetInstance().m_role_buying_order_list[order->m_dwRoleID].remove(order);
            else
                CExchangeMgr::GetInstance().m_role_selling_order_list[order->m_dwRoleID].remove(order);

            //TODO: send msg to client

            CExchangeMgr::GetInstance()._DeleteOrder(order, eosExpired);
        }
        else
        {
            ++it;
        }
    }
}
