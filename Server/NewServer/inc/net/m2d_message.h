#ifndef _M2D_MESSAGE_H_
#define _M2D_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum M2D_MESSAGE_ID
    {
        m2d_begin = m2d_message_begin,
        
        m2d_register_ack,

        m2d_create_role_ack,
        m2d_can_delete_role_ack,
        m2d_delete_role_ack,
        m2d_leave_db,
        m2d_clear_role_cache,
		m2d_gm_command,

        m2d_end = m2d_message_end
    };

    struct M2D_REGISTER_ACK : MESSAGE_HEADER
    {
        char szServerAddr[64];
        char szLoginName[64];
        char szPassword[64];
        char szDBName[64];
        char szCharSet[64];
        UINT32 dwServerPort;
    };

    struct M2D_CREATE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;
        char                BaseData[0];
    };

    struct M2D_CAN_DELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;
        UINT32              dwRoleID;
        INT32               nResult;
    };

    struct M2D_DELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;
        UINT32              dwRoleID;
    };

    struct M2D_LEAVE_DB : MESSAGE_HEADER
    {
        UINT32              dwClientSessionID;
    };

    struct M2D_CLEAR_ROLE_CACHE : MESSAGE_HEADER
    {
        UINT32              dwTLUserID;
        UINT32              dwRoleID;
        UINT32              dwCmdSerialID;
    };

	struct M2D_GM_COMMAND : MESSAGE_HEADER
	{
		char				szGMCommand[0];
	};

};
#pragma pack(pop)

#endif  // _D2G_MESSAGE_H_