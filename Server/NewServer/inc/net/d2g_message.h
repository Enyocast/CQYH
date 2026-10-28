#ifndef _D2G_MESSAGE_H_
#define _D2G_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum D2G_MESSAGE_ID
    {
        d2g_begin = d2g_message_begin,

        d2g_register_ack,

		d2g_load_lock_role_data_ack,
        d2g_unlock_role_data_ack,
        d2g_load_lock_role_data_fail_ack,

        d2g_end = d2g_message_end
    };

    struct D2G_REGISTER_ACK : public MESSAGE_HEADER
    {

    };

	struct D2G_LOAD_LOCK_ROLE_DATA_ACK : public MESSAGE_HEADER
	{
        UINT32      dwClientSessionID;
		UINT32      dwRoleID;
		UINT32      dwDataSize;
		char        RoleData[0];
	};

    struct D2G_UNLOCK_ROLE_DATA_ACK : public MESSAGE_HEADER
    {
        INT32		nError;
		UINT32      dwClientSessionID;
        UINT32      dwRoleID;
    };

    struct D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK : public MESSAGE_HEADER
    {
        UINT32      dwClientSessionID;
        UINT32      dwRoleID;
    };
};
#pragma pack(pop)

#endif  // _D2G_MESSAGE_H_