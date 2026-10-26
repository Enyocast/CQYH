#ifndef __MESSAGE_HANDLER_LOGIN_H__
#define __MESSAGE_HANDLER_LOGIN_H__
public:
	void Login(const TCHAR* strIP, const INT nPort, const TCHAR* UserName,const TCHAR*  Password, UBOOL bConnectBS = TRUE);
	void Send_CreateRole(const TCHAR* Name,INT classid,INT sex, INT hairType, INT hairColor, INT faceType, INT skinColor);
	void Send_DeleteRole( INT RoleListId);
	void Send_CharactorSelect(int roleid  );
    void  LockSendRestrict( int msg );
    void  UnLockSendRestrict( int msg , FString errMag = TEXT("Ok") );
	void Send_UnDeleteRole(INT roleid);
	void Send_DeleteRoleForEver(INT nRoleID);
private:
    M_DECL_PARSE_FUN(b2c_query_gate_ack);
	M_DECL_PARSE_FUN(t2c_error_notify);
	M_DECL_PARSE_FUN(t2c_login_ack);

	M_DECL_PARSE_FUN(t2c_sync_role_list);
	M_DECL_PARSE_FUN(t2c_select_role_ack);
	M_DECL_PARSE_FUN(t2c_create_role_ack);
	M_DECL_PARSE_FUN(t2c_delete_role_ack);
    M_DECL_PARSE_FUN(t2c_return_select_role);
	M_DECL_PARSE_FUN(t2c_undelete_role_ack);
	M_DECL_PARSE_FUN(t2c_forever_delete_role_ack);
	M_DECL_PARSE_FUN(g2c_logout_timer);
	

#define M_INIT_MSGHANDLER_LOGIN  \
MREG_PARSE_FUN(b2c_query_gate_ack);\
MREG_PARSE_FUN(t2c_error_notify); \
MREG_PARSE_FUN(t2c_login_ack); \
MREG_PARSE_FUN(t2c_sync_role_list); \
MREG_PARSE_FUN(t2c_select_role_ack); \
MREG_PARSE_FUN(t2c_create_role_ack); \
MREG_PARSE_FUN(t2c_delete_role_ack); \
MREG_PARSE_FUN(t2c_return_select_role); \
MREG_PARSE_FUN(t2c_undelete_role_ack);\
MREG_PARSE_FUN(t2c_forever_delete_role_ack);\
MREG_PARSE_FUN(g2c_logout_timer);


#endif