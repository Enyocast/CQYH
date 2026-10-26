#ifndef _G2T_MESSAGE_H_
#define _G2T_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum G2T_MESSAGE_ID
    {
        g2t_begin = g2t_message_begin,

        g2t_register,

        g2t_client_msg,
        g2t_broadcast_client_msg,
        g2t_close_client_session,
		g2t_return_role_select,

        g2t_end = g2t_message_end
    };

    struct G2T_REGISTER : MESSAGE_HEADER
    {
        UINT32      dwGSSessionID;
    };

    struct G2T_CLIENT_MSG : MESSAGE_HEADER
    {
        UINT32      dwSessionID;
        char        szData[0];
    };

    struct G2T_BROADCAST_CLIENT_MSG : MESSAGE_HEADER
    {
        UINT16       wSessionCount;
        UINT32      dwSessionIDList[0];
    };

	struct G2T_RETURN_ROLE_SELECT : MESSAGE_HEADER
	{
        UINT32      dwClientSessionID;
	};

	struct G2T_CLOSE_CLIENT_SESSION : MESSAGE_HEADER
	{
		UINT32      dwClientSessionID;
		UINT8		byLogout;
	};
};
// tolua_end
#pragma pack(pop)

#endif  // _G2T_MESSAGE_H_