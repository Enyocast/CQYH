#ifndef _MESSAGE_HANDLER_HEAVEN_H_
#define _MESSAGE_HANDLER_HEAVEN_H_

public:

	void Send_HeavenConverter();
	void Send_HeavenNormalConverter();
	void Send_OutLineConverter();
	void Send_PractiseGasOneKey();
	void Send_NormalPractiseGas(INT nIndex);

	void Send_BuyGasSlot(INT nContainerID,INT nSlotID);
	void Send_MergeGasOneKey(INT destSlotID);

	void Send_EquipGasItem(INT nEquipSlot,INT nSlotIndex,INT nContaineID);
	void Send_UnequipGasItem(INT nEquipSlot,INT nSlotIndex,INT nContaineID);
	void Send_MoveGasItem(INT destSlotID,INT nDestContainerID,INT srcSlotID,INT nSrcContainerID);

	void Send_GasExchange(INT nGasID);

	void Send_HeavenBloodLevel(INT nIndex, INT nTypeIndex);
	void Send_HeavenBloodOpen(INT nPage);

	public:
		M_DECL_PARSE_FUN(g2c_sync_spirit);
		M_DECL_PARSE_FUN(g2c_spirit_exp_change);
		M_DECL_PARSE_FUN(g2c_spirit_up);
		M_DECL_PARSE_FUN(g2c_spirit_air_change);
		M_DECL_PARSE_FUN(g2c_spirit_air_levelup);
		M_DECL_PARSE_FUN(g2c_spirit_brush_slot);
		M_DECL_PARSE_FUN(g2c_spirit_slot_size_change);
		M_DECL_PARSE_FUN(g2c_spirit_notify_exp_change_time);
		M_DECL_PARSE_FUN(g2c_spirit_blood_open);

#define M_INIT_MSGHANDLER_HEAVEN	\
	MREG_PARSE_FUN(g2c_sync_spirit); \
	MREG_PARSE_FUN(g2c_spirit_exp_change); \
	MREG_PARSE_FUN(g2c_spirit_up); \
	MREG_PARSE_FUN(g2c_spirit_air_change);\
	MREG_PARSE_FUN(g2c_spirit_air_levelup);\
	MREG_PARSE_FUN(g2c_spirit_brush_slot);\
	MREG_PARSE_FUN(g2c_spirit_slot_size_change);\
	MREG_PARSE_FUN(g2c_spirit_notify_exp_change_time);\
	MREG_PARSE_FUN(g2c_spirit_blood_open);

#endif
