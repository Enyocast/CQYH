#ifndef _MESSAGE_HANDLE_AUCTION_H_
#define _MESSAGE_HANDLE_AUCTION_H_

public:
	void Send_AuctionSearch(C2M_AUCTION_SEARCH* dt);
	void Send_AuctionQuery(UINT32 id);
	void Send_AuctionSell(C2M_AUCTION_SELL* info);
	void Send_AuctionCancelSell(UINT32 id);
	void Send_AuctionBuy(UINT32 id, INT64 price);
	void Send_AuctionListMySelling();
	void Send_AuctionListMyBuying();
	void Send_AuctionQueryByType(UINT8 mainType, UINT8 subType, UINT8 bySortBy, UINT8 byAscending);
	void Send_AucrionPayLeftMoney(UINT32 auctionId);

private:
	M_DECL_PARSE_FUN(m2c_auction_search);
	M_DECL_PARSE_FUN(m2c_auction_query);
	M_DECL_PARSE_FUN(m2c_auction_sell);
	M_DECL_PARSE_FUN(m2c_auction_cancel_sell);
	M_DECL_PARSE_FUN(m2c_auction_buy);
	M_DECL_PARSE_FUN(m2c_auction_list_my_selling);
	M_DECL_PARSE_FUN(m2c_auction_list_my_buying);
	M_DECL_PARSE_FUN(m2c_auction_finished);
	M_DECL_PARSE_FUN(m2c_auction_pay_left_money);

#define M_INIT_MSGHANDLER_AUCTION\
	MREG_PARSE_FUN(m2c_auction_search);\
	MREG_PARSE_FUN(m2c_auction_query);\
	MREG_PARSE_FUN(m2c_auction_sell);\
	MREG_PARSE_FUN(m2c_auction_cancel_sell);\
	MREG_PARSE_FUN(m2c_auction_buy);\
	MREG_PARSE_FUN(m2c_auction_list_my_selling);\
	MREG_PARSE_FUN(m2c_auction_list_my_buying);\
	MREG_PARSE_FUN(m2c_auction_finished);\
	MREG_PARSE_FUN(m2c_auction_pay_left_money);\
	
#endif