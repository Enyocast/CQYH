#ifndef _C2T_MESSAGE_H_
#define _C2T_MESSAGE_H_

#include "external_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace ExternalMessage
{
    enum C2T_MESSAGE_ID
    {
        c2t_message_begin = 1000,

        c2t_login_req,
        c2t_create_role,
        c2t_delete_role,
        c2t_forever_delete_role,
        c2t_undelete_role,
		c2t_select_role,

        c2t_ping,

        c2t_message_end = 1024,
    };

    struct C2T_LOGIN_REQ : MESSAGE_HEADER
    {
        char            szUserName[USER_NAME_LEN];
        char            szPassword[USER_PASSWORD_LEN];
        UINT8           byGroup;
		UINT16			wMajorVersion;
		UINT16			wMinorVersion;
		char			szSessionID[OA_SESSION_ID_LEN];
        char            szMac[MAC_ADDRESS_LEN];
		UINT32			dwCRC;
	};

    struct C2T_SELECT_ROLE : MESSAGE_HEADER
    {
        UINT32           dwRoleID;
    };

    struct C2T_CREATE_ROLE : MESSAGE_HEADER
    {
        char            szRoleName[ROLE_NAME_LEN];
        UINT8           bySex;
        UINT8           byClass;
        UINT8           byHairType;
        UINT8           byHairColor;
        UINT8           byFaceType;
        UINT8           bySkinColor;
    };

    struct C2T_DELETE_ROLE : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
    };

    struct C2T_UNDELETE_ROLE : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
    };

    struct C2T_FOREVER_DELETE_ROLE : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
    };

    struct C2T_PING : MESSAGE_HEADER
    {
        UINT32   dwPingTick;
    };

};
// tolua_end
#pragma pack(pop)

#endif  // _C2T_MESSAGE_H_