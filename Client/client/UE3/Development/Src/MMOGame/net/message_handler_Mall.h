#ifndef _MESSAGE_HANDLER_MALL_H_
#define _MESSAGE_HANDLER_MALL_H_

public:

	void Send_MallAskRealMoney();
	void Send_MallAskCRC(INT nCrc);
	void Send_MallBuyGoods(INT nGoodsID,INT nNum);
	void Send_MallGiveFriend(FString roleName, INT nGoodsID,INT nNum);
	void Send_MallReqBuyInfo();

	void Send_RequestExchangeLog();
	
private:

	M_DECL_PARSE_FUN(m2c_sync_real_money);
	M_DECL_PARSE_FUN(m2c_sync_real_money_shop_data);
	M_DECL_PARSE_FUN(m2c_real_money_buy);
	M_DECL_PARSE_FUN(m2c_sale_info);
	M_DECL_PARSE_FUN(m2c_real_money_shop_log);

#define M_INIT_MSGHANDLER_MALL \
	MREG_PARSE_FUN(m2c_sync_real_money);\
	MREG_PARSE_FUN(m2c_sync_real_money_shop_data);\
	MREG_PARSE_FUN(m2c_real_money_buy);\
	MREG_PARSE_FUN(m2c_sale_info);\
	MREG_PARSE_FUN(m2c_real_money_shop_log);
#endif
