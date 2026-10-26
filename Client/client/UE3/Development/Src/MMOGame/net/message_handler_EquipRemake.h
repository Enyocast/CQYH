#ifndef __MESSAGE_HANDLER_EQUIPREMAKE_H__
#define __MESSAGE_HANDLER_EQUIPREMAKE_H__
public:
	void Send_Remake(UINT uGambleType,UINT uGambleLevel);
	void Send_RemakeBook();
	void Send_RemakeMedicine();

	M_DECL_PARSE_FUN(g2c_gamble);
	M_DECL_PARSE_FUN(g2c_spell_book_gamble);
	M_DECL_PARSE_FUN(g2c_potion_gamble);
private:

#define  M_INIT_MSGHANDLER_EQUIPREMAKE \
	MREG_PARSE_FUN(g2c_gamble); \
	MREG_PARSE_FUN(g2c_spell_book_gamble); \
	MREG_PARSE_FUN(g2c_potion_gamble);

#endif