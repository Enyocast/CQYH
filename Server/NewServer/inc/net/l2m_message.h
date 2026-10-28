#ifndef _L2M_MESSAGE_H_
#define _L2M_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum L2M_MESSAGE_ID
    {
        l2m_begin = l2m_message_begin,

        l2m_register,
        l2m_ready,
        l2m_close_ack,

        l2m_login_query_req,

        l2m_end = l2m_message_end
    };

    struct L2M_REGISTER : MESSAGE_HEADER
    {
        UINT32      dwAddr;
        UINT16      wPort;
    };

    struct L2M_READY : MESSAGE_HEADER
    {

    };

    struct L2M_CLOSE_ACK : MESSAGE_HEADER
    {
    };

    struct L2M_LOGIN_QUERY_REQ : MESSAGE_HEADER
    {
        UINT32 dwClientSessionID;
        char   szUserName[USER_NAME_LEN];
        char   szPassword[USER_PASSWORD_LEN];
    };

};
#pragma pack(pop)

#endif  // _L2M_MESSAGE_H_