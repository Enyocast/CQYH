#ifndef _MESSAGE_HANDLER_KILLRECORD_H_
#define _MESSAGE_HANDLER_KILLRECORD_H_


private:

	M_DECL_PARSE_FUN(g2c_update_consecutive_kill_npc_count);
	M_DECL_PARSE_FUN(g2c_update_consecutive_kill_npc_end);
	M_DECL_PARSE_FUN(g2c_update_momentary_kill_npc_end);
	M_DECL_PARSE_FUN(g2c_update_consecutive_kill_player_count);

#define M_INIT_MSGHANDLER_KILLRECORD \
	MREG_PARSE_FUN(g2c_update_consecutive_kill_npc_count);\
	MREG_PARSE_FUN(g2c_update_consecutive_kill_npc_end);\
	MREG_PARSE_FUN(g2c_update_momentary_kill_npc_end);\
	MREG_PARSE_FUN(g2c_update_consecutive_kill_player_count);
#endif
