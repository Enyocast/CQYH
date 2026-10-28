#ifndef _L2MG_MESSAGE_H_
#define _L2MG_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
	enum L2MG_MESSAGE_ID
	{
		l2mg_begin = l2mg_message_begin,

		l2mg_register_ack,

		l2mg_login_ack,

		l2mg_end = l2mg_message_end
	};

	struct L2MG_REGISTER_ACK : MESSAGE_HEADER
	{

	};

	struct L2MG_LOGIN_ACK : MESSAGE_HEADER
	{
		UINT32      dwClientSessionID;
		INT32       nErrorCode;
		char        szOASessionID[OA_SESSION_ID_LEN];
		char        szUserName[USER_NAME_LEN];
		char        szPGT[OA_PGT_FIELD_LEN];
		UINT8       bAdult;
		UINT16      wInfoLen;
		BYTE        abyInfo[0];
	};

};
#pragma pack(pop)

#endif  // _L2MG_MESSAGE_H_