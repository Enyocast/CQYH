#ifndef __MESSAGE_HANDLER_NPC_H__
#define __MESSAGE_HANDLER_NPC_H__

//add by jimzhang 2012.7.12
M_DECL_PARSE_FUN(g2c_play_action);
M_DECL_PARSE_FUN(g2c_sync_npc_data);
M_DECL_PARSE_FUN(g2c_sync_npc_ex_data);
M_DECL_PARSE_FUN(g2c_interact_result);

public:

	void ConvertDialog( struct DialogContext* Dialog, struct  FDialogContent& FDialog);
	void Send_InteractNpc( INT serverID );
	void Send_StopNPCInteract();

#define M_INIT_MSGHANDLER_NPC	\
	MREG_PARSE_FUN(g2c_play_action);	\
	MREG_PARSE_FUN(g2c_sync_npc_data);		\
	MREG_PARSE_FUN(g2c_sync_npc_ex_data);		\
	MREG_PARSE_FUN(g2c_interact_result);	\

#endif