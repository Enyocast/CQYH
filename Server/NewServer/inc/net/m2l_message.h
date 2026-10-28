#ifndef _M2L_MESSAGE_H_
#define _M2L_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum M2L_MESSAGE_ID
    {
        m2l_begin = m2l_message_begin,

        m2l_register_ack,

        m2l_login_query_ack,

        m2l_end = m2l_message_end
    };

    struct M2L_REGISTER_ACK : MESSAGE_HEADER
    {

    };

    struct M2L_LOGIN_QUERY_ACK : MESSAGE_HEADER
    {
        UINT32 dwClientSessionID;
        UINT32 dwError;    // 成功 = 1, 失败 = 0
        char   szUserName[USER_NAME_LEN];
    };

};
#pragma pack(pop)

#endif  // _M2L_MESSAGE_H_