#ifndef _MESSAGE_HANDLE_GOLDSTORE_H_
#define _MESSAGE_HANDLE_GOLDSTORE_H_

public:
	void Send_AddOrder(UINT8 orderType,INT32 itemID,INT32 price ,INT32 count);
	void Send_CancelOrder(UINT64 orderId);
	void Send_ListPrice();
	void Send_List_MyOrder();

	void Send_List_MyLogs();
private:
	M_DECL_PARSE_FUN(m2c_exchange_add_order);
	M_DECL_PARSE_FUN(m2c_exchange_cancel_order);
	M_DECL_PARSE_FUN(m2c_exchange_list_prices);
	M_DECL_PARSE_FUN(m2c_exchange_list_my_orders);
	M_DECL_PARSE_FUN(m2c_exchange_list_my_logs);

#define M_INIT_MSGHANDLER_GOLDSTORE\
	MREG_PARSE_FUN(m2c_exchange_add_order);\
	MREG_PARSE_FUN(m2c_exchange_cancel_order);\
	MREG_PARSE_FUN(m2c_exchange_list_prices);\
	MREG_PARSE_FUN(m2c_exchange_list_my_orders);\
	MREG_PARSE_FUN(m2c_exchange_list_my_logs);\

#endif