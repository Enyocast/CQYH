#ifndef _D2M_MESSAGE_H_
#define _D2M_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum D2M_MESSAGE_ID
    {
        d2m_begin = d2m_message_begin,

        d2m_register,
        d2m_ready,
        d2m_close_ack,
        
        d2m_create_role,
        d2m_can_delete_role,
        d2m_delete_role,
        d2m_leave_db_ack,
        d2m_clear_role_cache_ack,

        d2m_end = d2m_message_end
    };

    struct D2M_REGISTER : MESSAGE_HEADER
    {
        UINT32              dwAddr;
        UINT16              wPort;
    };

    struct D2M_READY : MESSAGE_HEADER
    {

    };

    struct D2M_CLOSE_ACK : MESSAGE_HEADER
    {

    };

    struct D2M_CREATE_ROLE : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;
        char                szUserName[USER_NAME_LEN];
		UINT8				byServerGroup;
        char                BaseData[0];
    };

    struct D2M_CAN_DELETE_ROLE : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;
        UINT32              dwRoleID;
    };

    struct D2M_DELETE_ROLE : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;
        UINT32              dwRoleID;
    };

    struct D2M_LEAVE_DB_ACK : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;      
    };

    struct D2M_CLEAR_ROLE_CACHE_ACK : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
        UINT32              dwTLUserID;
        UINT32              dwCmdSerialID;
        UINT8               byResult; //1³É¹¦ 0Ê§°Ü
    };
};
#pragma pack(pop)

#endif  // _D2G_MESSAGE_H_