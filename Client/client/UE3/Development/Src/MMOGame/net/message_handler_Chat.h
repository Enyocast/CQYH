#ifndef __MESSAGE_HANDLER_CHAT_H__
#define __MESSAGE_HANDLER_CHAT_H__

public:
	void Send_Chat( INT ChannelId ,  UINT32 TypeId , const FString& Content   );
	void Send_ChatChannel( INT ChannelId , UINT32 TypeId ,const FString& Content ,UINT8 location);
	bool CheckIsDuplicateChatContent( FString &Content );


private:
M_DECL_PARSE_FUN(m2c_chat_message);
M_DECL_PARSE_FUN(g2c_chat_message);

#define M_INIT_MSGHANDLER_CHAT \
	MREG_PARSE_FUN(m2c_chat_message);\
	MREG_PARSE_FUN(g2c_chat_message);\

#endif