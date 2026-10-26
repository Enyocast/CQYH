#ifndef _D2T_MESSAGE_H_
#define _D2T_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum D2T_MESSAGE_ID
    {
        d2t_begin = d2t_message_begin,

        d2t_register_ack,

        d2t_sync_role_list,
        d2t_create_role_ack,
        d2t_delete_role_ack,
        d2t_undelete_role_ack,
        d2t_forever_delete_role_ack,

        d2t_close_client_session,

        d2t_end = d2t_message_end
    };

    struct D2T_REGISTER_ACK : MESSAGE_HEADER
    {

    };

    struct D2T_CREATE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        INT32           nErrCode;
        char            BaseData[0];
    };

    struct D2T_DELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
        INT32           nErrCode;
    };

    struct D2T_UNDELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
        INT32           nErrCode;
    };

    struct D2T_FOREVER_DELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
        INT32           nErrCode;
    };

    struct D2T_SYNC_ROLE_LIST : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        INT32           nErrCode;
        UINT8           byRoleCount;
        char            BaseData[0];
    };

    struct D2T_CLOSE_CLIENT_SESSION : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
    };

};
// tolua_end
#pragma pack(pop)

#endif  // _D2T_MESSAGE_H_