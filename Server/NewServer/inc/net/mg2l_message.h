#ifndef _MG2L_MESSAGE_H_
#define _MG2L_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum MG2L_MESSAGE_ID
	{
		mg2l_begin = mg2l_message_begin,

		mg2l_register,
		mg2l_login_req,

		mg2l_end = mg2l_message_end
	};

	struct MG2L_REGISTER : MESSAGE_HEADER
	{
		UINT32          dwMGSessionID;
	};

	struct MG2L_LOGIN_REQ : MESSAGE_HEADER
	{
		UINT32          dwClientSessionID;
		char            szUserName[USER_NAME_LEN];
		char			szOASessionID[OA_SESSION_ID_LEN];
	};

};
// tolua_end
#pragma pack(pop)

#endif  // _MG2L_MESSAGE_H_