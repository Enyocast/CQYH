#ifndef __MESSAGE_HANDLER_TRADE_H__
#define __MESSAGE_HANDLER_TRADE_H__

public:

	void Send_RequistTrade(UINT32 roleID);
	void Send_AcceptTradeRequist(UINT32 roleID);
	void Send_TradeSetItem(UINT8 tradeSlot, UINT8 isAdd, UINT16 containerID, UINT16 slotID);
	void Send_TradeSetMoney(INT32 money);
	void Send_TradeLock();
	void Send_TradeUnLock();
	void Send_TradeConfirm();
	void Send_TradeCancel();
	
M_DECL_PARSE_FUN(g2c_trade_state_change);
M_DECL_PARSE_FUN(g2c_trade_set_item);
M_DECL_PARSE_FUN(g2c_trade_set_money);


#define M_INIT_MSGHANDLER_TRADE	\
	MREG_PARSE_FUN(g2c_trade_state_change);\
	MREG_PARSE_FUN(g2c_trade_set_item);\
	MREG_PARSE_FUN(g2c_trade_set_money);\



#endif