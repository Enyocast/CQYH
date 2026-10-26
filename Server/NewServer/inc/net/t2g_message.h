#ifndef _T2G_MESSAGE_H_
#define _T2G_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum T2G_MESSAGE_ID
    {
        t2g_begin = t2g_message_begin,

        t2g_register_ack,

        t2g_role_enter,

        t2g_client_msg,

        t2g_end = t2g_message_end
    };

    struct T2G_REGISTER_ACK : MESSAGE_HEADER
    {
        UINT32          dwGTSessionID;
    };

	struct T2G_ROLE_ENTER : MESSAGE_HEADER
	{
        UINT32         dwClientSessionID;
		UINT32         dwRoleID;
	};

    struct T2G_CLIENT_MSG : MESSAGE_HEADER
    {
        UINT32         dwSessionID;
        char           szData[0];
    };

};
// tolua_end
#pragma pack(pop)

#endif  // _T2G_MESSAGE_H_