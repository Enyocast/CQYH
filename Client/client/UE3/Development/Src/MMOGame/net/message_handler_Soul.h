#ifndef __MESSAGE_HANDLER_SOUL_H__
#define __MESSAGE_HANDLER_SOUL_H__

public:
 	void Parse_g2c_upgrade_soul(UINT8 byResult);
 	void Parse_g2c_add_soul(UINT8 byResult);
	void Parse_g2c_remove_soul(UINT8 byResult);
public:

void Send_RemoveSoul( UINT wEquipConSlot, UINT wEquipItemSlot, UINT bySocketIndex);
void Send_UpgradeSoul( UINT wTargetConSlot,UINT wTargetItemSlot, UINT bySrcCount, const STLIntVector& wSrcConSlot, const STLIntVector& wSrcItemSlot );
void Send_AddSoul( UINT wEquipConSlot, UINT wEquipItemSlot, UINT bySocketIndex, UINT wSoulConSlot, UINT wSoulItemSlot);

M_DECL_PARSE_FUN(g2c_upgrade_soul);
M_DECL_PARSE_FUN(g2c_add_soul);
M_DECL_PARSE_FUN(g2c_remove_soul);

#define M_INIT_MSGHANDLER_SOUL	\
	MREG_PARSE_FUN(g2c_upgrade_soul);	\
	MREG_PARSE_FUN(g2c_add_soul);		\
	MREG_PARSE_FUN(g2c_remove_soul);		\

#endif