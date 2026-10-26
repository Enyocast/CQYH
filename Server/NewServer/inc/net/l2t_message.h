#ifndef _L2T_MESSAGE_H_
#define _L2T_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum L2T_MESSAGE_ID
    {
        l2t_begin = l2t_message_begin,

        l2t_register_ack,

        l2t_login_ack,

        l2t_end = l2t_message_end
    };

    struct L2T_REGISTER_ACK : MESSAGE_HEADER
    {

    };

    struct L2T_LOGIN_ACK : MESSAGE_HEADER
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
// tolua_end
#pragma pack(pop)

#endif  // _L2T_MESSAGE_H_