#ifndef __MESSAGE_HANDLER_MAIL_H__
#define __MESSAGE_HANDLER_MAIL_H__


public:
	
    void Send_WriteMail(const FString& toPalyer, const FString& subject, const FString& content);
	void Send_RecvMailList();
	void Send_ReadMail(UINT32 mailID);
	void Send_DeleteMail(UINT32 mailID);
	void Send_GetMailAttach(UINT32 mailID);

	
M_DECL_PARSE_FUN(m2c_mail_write_success);
M_DECL_PARSE_FUN(m2c_mail_list_recv);
M_DECL_PARSE_FUN(m2c_mail_read);
M_DECL_PARSE_FUN(m2c_mail_delete_success);
M_DECL_PARSE_FUN(m2c_mail_new_count);
M_DECL_PARSE_FUN(m2c_mail_get_attach_success);

#define M_INIT_MSGHANDLER_MAIL	\
	MREG_PARSE_FUN(m2c_mail_write_success); \
	MREG_PARSE_FUN(m2c_mail_list_recv); \
	MREG_PARSE_FUN(m2c_mail_read); \
	MREG_PARSE_FUN(m2c_mail_delete_success); \
	MREG_PARSE_FUN(m2c_mail_new_count);\
	MREG_PARSE_FUN(m2c_mail_get_attach_success);

#endif