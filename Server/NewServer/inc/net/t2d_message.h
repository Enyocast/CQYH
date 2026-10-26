#ifndef _T2D_MESSAGE_H_
#define _T2D_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum T2D_MESSAGE_ID
    {
        t2d_begin = t2d_message_begin,

        t2d_register,

        t2d_query_role_list,
        t2d_create_role,
        t2d_delete_role,
        t2d_undelete_role,
        t2d_forever_delete_role,

        t2d_end = t2d_message_end
    };

    struct T2D_REGISTER : MESSAGE_HEADER
    {
        UINT32          dwGTSessionID;
    };

    struct T2D_QUERY_ROLE_LIST : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
		UINT8			byServerGroup;
        char            szUserName[USER_NAME_LEN];
    };

    struct T2D_CREATE_ROLE : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
        char            szRoleName[ROLE_NAME_LEN];
        UINT8           byClass;
        UINT8           bySex;
        UINT8           byHairType;
        UINT8           byHairColor;
        UINT8           byFaceType;
        UINT8           bySkinColor;
    };

    struct T2D_DELETE_ROLE : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
    };

    struct T2D_UNDELETE_ROLE: MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
    };

    struct T2D_FOREVER_DELETE_ROLE : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
    };

};
// tolua_end
#pragma pack(pop)

#endif  // _T2D_MESSAGE_H_
