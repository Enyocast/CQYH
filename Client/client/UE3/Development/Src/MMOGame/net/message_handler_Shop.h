#ifndef __MESSAGE_HANDLER_SHOP_H__
#define __MESSAGE_HANDLER_SHOP_H__

public:
	//shop
    void Send_BuyShopItem( INT ShopItemId , INT ItemCount , INT ItemTempId,INT ShopId );
    void Send_SellItem( INT ConSlot , INT ItemSlot , INT ItemCount , INT TemplateId );
	void Send_ViewSoldItems();
	void Send_BuybackItem(UINT8 bySlot);

	void Send_RequestShop( UINT32 crc );

	void Send_BlackMarketListInfo();
	void Send_BlackMarketBuy(INT nBlackMarketProductID);

	void Send_BlackMarketItemCoolDown();

M_DECL_PARSE_FUN(g2c_view_sold_items);
M_DECL_PARSE_FUN(g2c_sync_npc_shop_data);
M_DECL_PARSE_FUN(g2c_black_market_limit_info);
M_DECL_PARSE_FUN(g2c_black_market_buy);
M_DECL_PARSE_FUN(g2c_black_market_cooldown_info);


#define M_INIT_MSGHANDLER_SHOP	\
	MREG_PARSE_FUN(g2c_view_sold_items);\
	MREG_PARSE_FUN(g2c_sync_npc_shop_data);\
	MREG_PARSE_FUN(g2c_black_market_limit_info);\
	MREG_PARSE_FUN(g2c_black_market_buy);\
	MREG_PARSE_FUN(g2c_black_market_cooldown_info);\

#endif