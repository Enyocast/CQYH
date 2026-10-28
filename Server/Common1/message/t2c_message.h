#ifndef _T2C_MESSAGE_H_
#define _T2C_MESSAGE_H_

#include "external_message_header.h"

#pragma pack(push, 1)
namespace ExternalMessage
{
    enum T2C_MESSAGE_ID
    {
        t2c_message_begin = 1000,

        t2c_error_notify,

        t2c_login_ack,
        t2c_select_role_ack,

        t2c_sync_role_list,
        t2c_create_role_ack,
        t2c_delete_role_ack,
        t2c_undelete_role_ack,
        t2c_forever_delete_role_ack,
        
        t2c_return_select_role,

        //ping
        t2c_ping_ack,
        t2c_message_end = 1024,
    };

    struct T2C_ERROR_NOTIFY : MESSAGE_HEADER
    {
        INT32            nErrCode;
        INT32            nParam1;
        INT32            nParam2;
    };

    struct T2C_LOGIN_ACK : FLEX_MESSAGE_HEADER
    {
        char                szUserName[USER_NAME_LEN];
        UINT8               bAdult;
		UINT8				byEncryptCode;
		UINT32				dwClientOption;
		char				szMessageSize[0];
    };

    struct LOGIN_ROLE_DATA
    {
        UINT32  dwRoleID;
        char	szRoleName[ROLE_NAME_LEN];
        char    szGuildName[GUILD_NAME_LEN];
        UINT8	byClass;
        UINT8	bySex;
        UINT8	byHairType;
        UINT8	byHairColor;
        UINT8	byFaceType;
        UINT8	bySkinColor;
        UINT8	byLevel;
        INT32	nSceneTempID;
        UINT8   byRefineFx;
        INT32   nAvatar[NES_VISIBLE_TOTAL];
        UINT32	dwSaveTime;
        UINT32  dwDeleteTime;
    };

    struct T2C_SYNC_ROLE_LIST : MESSAGE_HEADER
    {
        UINT8               byCount;
        LOGIN_ROLE_DATA     RoleData[MAX_ROLE_PER_USER];
    };

    struct T2C_SELECT_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

    struct T2C_CREATE_ROLE_ACK : MESSAGE_HEADER
    {
        LOGIN_ROLE_DATA     RoleData;
    };

    struct T2C_DELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

    struct T2C_UNDELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

    struct T2C_FOREVER_DELETE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

    struct T2C_RETURN_SELECT_ROLE : MESSAGE_HEADER
    {

    };

    struct T2C_PING_ACK : MESSAGE_HEADER
    {
        UINT32   dwPingTick;
    };
};
#pragma pack(pop)

#endif  // _T2C_MESSAGE_H_