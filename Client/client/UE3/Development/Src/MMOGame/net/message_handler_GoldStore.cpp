#include "stdafx.h"
#include "message_handler.h"
#include "MMOGoldStoreManager.h"
#include "ClientActionConditionCheck.h"

void CMessageHandler::Send_AddOrder(UINT8 orderType,INT32 itemID,INT32 price, INT32 count)
{
	FClientActionConditionContex contex(ECACCT_MainPlayer_Is_Trading);	
	if(!CheckClientActionCondition(contex))
	{
		return;
	}

	C2M_EXCHANGE_ADD_ORDER msg;
	msg.wMsg = c2m_exchange_add_order;
	msg.byOrderType = orderType;
	msg.nItemID = itemID;
	msg.nPrice = price;
	msg.nCount = count;
	_Send(&msg, sizeof(msg));
}

void CMessageHandler::Send_CancelOrder(UINT64 orderId)
{
	C2M_EXCHANGE_CANCEL_ORDER msg;
	msg.wMsg = c2m_exchange_cancel_order;
	msg.qwOrderID = orderId;
	_Send(&msg, sizeof(msg));
}

void CMessageHandler::Send_ListPrice()
{
	C2M_EXCHANGE_LIST_PRICES msg;
	msg.wMsg = c2m_exchange_list_prices;
	//msg.byOrderType = orderType;
	//msg.nItemID = itemID;
	_Send(&msg, sizeof(msg));
}
void CMessageHandler::Send_List_MyOrder()
{
	C2M_EXCHANGE_LIST_MY_ORDERS msg;
	msg.wMsg = c2m_exchange_list_my_orders;
	//msg.byOrderType = orderType;
	//msg.byMoneyOrder = moneyOrder;
	_Send(&msg, sizeof(msg));
}

void CMessageHandler::Send_List_MyLogs()
{
	C2M_EXCHANGE_LIST_MY_LOGS msg;
	msg.wMsg = c2m_exchange_list_my_logs;
	_Send(&msg,sizeof(msg));
}


void CMessageHandler::Parse_m2c_exchange_add_order(const char* buf, UINT32 size)
{
	M2C_EXCHANGE_ADD_ORDER* msg = (M2C_EXCHANGE_ADD_ORDER*)buf;
	if(msg == NULL)
		return;
	MMOGoldStoreManager::getSingleton().OnServer_AddOrder(&msg->stOrder);
}

void CMessageHandler::Parse_m2c_exchange_cancel_order(const char* buf, UINT32 size)
{
	M2C_EXCHANGE_CANCEL_ORDER* msg = (M2C_EXCHANGE_CANCEL_ORDER*)buf;
	if(msg == NULL)
		return;
	MMOGoldStoreManager::getSingleton().OnServer_CancelSell(msg->qwOrderID);
}
void CMessageHandler::Parse_m2c_exchange_list_prices(const char* buf, UINT32 size)
{
	M2C_EXCHANGE_LIST_PRICES* msg = (M2C_EXCHANGE_LIST_PRICES*) buf;
	if(msg == NULL)
		return;
	MMOGoldStoreManager::getSingleton().OnServer_Listprices(msg->bySellCount,msg->byBuyCount,(EXCHANGE_PRICE_INFO*)msg->stPrices);
}

void CMessageHandler::Parse_m2c_exchange_list_my_orders(const char* buf, UINT32 size)
{
	M2C_EXCHANGE_LIST_MY_ORDERS* msg = (M2C_EXCHANGE_LIST_MY_ORDERS*) buf;
	if(msg == NULL)
		return;
	MMOGoldStoreManager::getSingleton().Onserver_ListMyOrders(msg->byOrderType,msg->byCount,(EXCHANGE_ORDER_INFO*)msg->stOrders);
}

void CMessageHandler::Parse_m2c_exchange_list_my_logs(const char* buf, UINT32 size)
{
	//ASSERT_CHECK_ERROR_RETURN(buf && size == sizeof(M2C_EXCHANGE_LIST_MY_LOGS));
	M2C_EXCHANGE_LIST_MY_LOGS* msg = (M2C_EXCHANGE_LIST_MY_LOGS*)buf;
	if(msg == NULL)
		return;
	MMOGoldStoreManager::getSingleton().AddMyLogs(msg->nCount,msg->stLogs);
	MMOGoldStoreManager::getSingleton().NotifyUpdateMyLogs();
}