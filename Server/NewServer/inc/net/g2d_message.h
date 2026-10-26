#ifndef _G2D_MESSAGE_H_
#define _G2D_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum G2D_MESSAGE_ID
	{
		g2d_begin = g2d_message_begin,

        g2d_register,

		g2d_load_lock_role_data,
        g2d_save_role_data,
		g2d_unlock_role_data,

		g2d_end = g2d_message_end
	};

    struct G2D_REGISTER : MESSAGE_HEADER
    {
        UINT32          dwGSSessionID;
    };

	struct G2D_LOAD_LOCK_ROLE_DATA : MESSAGE_HEADER
	{
        UINT32      dwClientSessionID;
		UINT32      dwRoleID;
	};

	struct G2D_SAVE_ROLE_DATA : MESSAGE_HEADER
	{
        UINT32      dwClientSessionID;
		UINT32      dwRoleID;
        UINT32      dwDataSize;
		char        RoleData[0];
	};

    struct G2D_UNLOCK_ROLE_DATA : MESSAGE_HEADER
    {
        UINT32      dwClientSessionID;
        UINT32      dwRoleID;
    };
};
// tolua_end
#pragma pack(pop)

#endif  // _G2D_MESSAGE_H_
