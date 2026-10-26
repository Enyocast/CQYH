#ifndef _MESSAGE_HANDLE_TEAMAUCTION_H_
#define _MESSAGE_HANDLE_TEAMAUCTION_H_

public:

	void Send_TeamAuctionBid( INT itemTempId , INT bidMoney , INT index );
	void Send_TeamAuctionAbandonBid( INT itemTempId , INT itemIndex );

private:
	M_DECL_PARSE_FUN(g2c_team_auction_begin); 
	M_DECL_PARSE_FUN(g2c_team_auction_add_item); 
	M_DECL_PARSE_FUN(g2c_team_auction_notify);
	M_DECL_PARSE_FUN(g2c_team_auction_end);
	M_DECL_PARSE_FUN(g2c_team_auction_abandon);
		

#define M_INIT_MSGHANDLER_TEAM_AUCTION\
	MREG_PARSE_FUN(g2c_team_auction_begin);\
	MREG_PARSE_FUN(g2c_team_auction_add_item);\
	MREG_PARSE_FUN(g2c_team_auction_notify);\
	MREG_PARSE_FUN(g2c_team_auction_end);\
	MREG_PARSE_FUN(g2c_team_auction_abandon);

#endif