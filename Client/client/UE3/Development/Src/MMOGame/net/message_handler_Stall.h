#ifndef __MESSAGE_HANDLER_STALL_H__
#define __MESSAGE_HANDLER_STALL_H__

//Stall
public:
	void Send_OpenStall();
	void Send_CloseStall();
	void Send_RealOpenStall();
	void Send_RealCloseStall();
	void Send_AddStallItem(UINT8 stallSlot, UINT8 conSlot, UINT8 itemSlot, INT16 itemCount, INT32 price);
	void Send_RemoveStallItem(UINT8 stallSlot);
	void Send_ChangeStallName(const TCHAR* szStallName);
	void Send_ViewStallItem(UINT32 roleId);
	void Send_BuyStallItem(UINT32 roleId, UINT8 stallSlot, INT16 itemCount, INT32 modifyFrame);
	void Send_UpgradeStall(UINT8 timeType);

private:

	//Stall
	M_DECL_PARSE_FUN(g2c_stall_state_change);
	M_DECL_PARSE_FUN(g2c_add_stall_item);
	M_DECL_PARSE_FUN(g2c_remove_stall_item);
	M_DECL_PARSE_FUN(g2c_change_stall_name);
	M_DECL_PARSE_FUN(g2c_view_stall_item);
	M_DECL_PARSE_FUN(g2c_buy_stall_item);
	M_DECL_PARSE_FUN(g2c_sold_stall_item);
	M_DECL_PARSE_FUN(g2c_sync_stall);
	M_DECL_PARSE_FUN(g2c_change_stall_level);

#define M_INIT_MSGHANDLER_STALL  \
    MREG_PARSE_FUN(g2c_stall_state_change); \
    MREG_PARSE_FUN(g2c_add_stall_item); \
    MREG_PARSE_FUN(g2c_remove_stall_item); \
    MREG_PARSE_FUN(g2c_change_stall_name); \
    MREG_PARSE_FUN(g2c_view_stall_item); \
    MREG_PARSE_FUN(g2c_buy_stall_item); \
    MREG_PARSE_FUN(g2c_sold_stall_item);\
	MREG_PARSE_FUN(g2c_sync_stall);\
	MREG_PARSE_FUN(g2c_change_stall_level);

#endif