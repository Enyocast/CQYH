#ifndef __MESSAGE_HANDLER_PLAYERINFO_H__
#define __MESSAGE_HANDLER_PLAYERINFO_H__

public:
 	//void Parse_g2c_upgrade_soul(UINT8 byResult);
 	//void Parse_g2c_add_soul(UINT8 byResult);
	//void Parse_g2c_remove_soul(UINT8 byResult);


	void Send_QueryRoleDetailInfo( INT roleId , INT roleCRC , INT equipCRC , INT spellCRC , INT spiritCRC );
	void Send_QueryPower( INT roleId );
	void Send_SignInToday();

M_DECL_PARSE_FUN(g2c_sync_role_attr_data);
M_DECL_PARSE_FUN(g2c_sync_role_equip_data);
M_DECL_PARSE_FUN(g2c_sync_role_pow);
M_DECL_PARSE_FUN(g2c_sync_role_spirit_data);
M_DECL_PARSE_FUN(g2c_sync_role_spell_data);
M_DECL_PARSE_FUN(m2c_time_info);
M_DECL_PARSE_FUN(m2c_buy_time);
M_DECL_PARSE_FUN(g2c_checkin);
M_DECL_PARSE_FUN(g2c_sync_checkin_info);

#define M_INIT_MSGHANDLER_PLAYERINFO	\
	MREG_PARSE_FUN(g2c_sync_role_attr_data);	\
	MREG_PARSE_FUN(g2c_sync_role_equip_data);		\
	MREG_PARSE_FUN(g2c_sync_role_pow); \
	MREG_PARSE_FUN(g2c_sync_role_spirit_data);\
	MREG_PARSE_FUN(g2c_sync_role_spell_data);\
	MREG_PARSE_FUN(m2c_time_info);\
	MREG_PARSE_FUN(m2c_buy_time);\
	MREG_PARSE_FUN(g2c_checkin);\
	MREG_PARSE_FUN(g2c_sync_checkin_info);

#endif