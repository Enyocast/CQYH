#ifndef _T2L_MESSAGE_H_
#define _T2L_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum T2L_MESSAGE_ID
    {
        t2l_begin = t2l_message_begin,

        t2l_register,
        t2l_login_req,

        t2l_end = t2l_message_end
    };

    struct T2L_REGISTER : MESSAGE_HEADER
    {
        UINT32          dwGTSessionID;
    };

    struct T2L_LOGIN_REQ : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        char            szUserName[USER_NAME_LEN];
        char            szPassword[USER_PASSWORD_LEN];
		char			szOASessionID[OA_SESSION_ID_LEN];
    };

};
#pragma pack(pop)

#endif  // _T2L_MESSAGE_H_