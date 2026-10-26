#ifndef _M2O_MESSAGE_H_
#define _M2O_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
	enum M2O_MESSAGE_ID
	{
		m2o_begin = m2o_message_begin,
		
		m2o_register_ack,
		m2o_reload,

		m2o_chat_message,

        m2o_log_item,
        m2o_stat_item,

		m2o_create_team,
		m2o_join_team,
		m2o_leave_team,
		m2o_breakdown_team,

		m2o_enter_scene,
		m2o_leave_scene,

		m2o_login,
		m2o_logout,

        m2o_gm_command,

		m2o_realmoney_money02,
		m2o_realmoney_item,

        m2o_guild_event,
        m2o_guild_chest,
        m2o_guild_stat,

        m2o_billing_request,
        m2o_billing_result,

		m2o_end = m2o_message_end
	};

	struct ML_MESSAGE_HEADER : MESSAGE_HEADER
	{
		UINT32	dwTime;
		INT32	nGroupID;
	};

	struct M2O_REGISTER_ACK : MESSAGE_HEADER
	{

	};

	struct M2O_RELOAD : MESSAGE_HEADER
	{
	};

	struct M2O_CHAT_MESSAGE : ML_MESSAGE_HEADER
	{
		UINT32	dwSrcID;
		UINT32	dwTargetID;
		INT32	nMessageSize;
		char	chMessage[0];
	};

    struct M2O_LOG_ITEM : ML_MESSAGE_HEADER
    {
        UINT64      qwItemGuid;
        UINT32      dwRoleID;
        INT32       nItemTemplateID;
        INT32       nItemCount;
        INT32       nReason;
        INT32       nAction;
        UINT64      qwUserDefinedID;
    };

    struct M2O_STAT_ITEM : ML_MESSAGE_HEADER
    {
        INT32       nItemTemplateID;
        INT32       nItemCount;
        INT32       nAction;
    };

	struct M2O_CREATE_TEAM : ML_MESSAGE_HEADER
	{
		UINT32	dwTime;
		UINT32	dwTeamID;
		UINT32	dwRoleID;
	};

	struct M2O_JOIN_TEAM : ML_MESSAGE_HEADER
	{
		UINT32	dwRoleID;
		UINT32	dwTeamID;
		UINT32	dwLeaderID;
		INT32	nMemberCount;
	};

	struct M2O_LEAVE_TEAM : ML_MESSAGE_HEADER
	{
		UINT32	dwTeamID;
		UINT32	dwRoleID;
		UINT32	dwLeaderID;
		INT32	nMemberCount;
	};

	struct M2O_LOGIN : ML_MESSAGE_HEADER
	{
		UINT32	dwIP;
		char	szUserName[USER_NAME_LEN];
	};

	struct M2O_LOGOUT : ML_MESSAGE_HEADER
	{
		UINT32	dwIP;
		char	szUserName[USER_NAME_LEN];
	};

	struct M2O_BREAKDOWN_TEAM : ML_MESSAGE_HEADER
	{
		UINT32	dwTeamID;
	};

	struct M2O_ENTER_SCENE : ML_MESSAGE_HEADER
	{
		INT32		nSceneID;
		INT32		nTemplateID;
		UINT32		dwRoleID;
	};

	struct M2O_LEAVE_SCENE : ML_MESSAGE_HEADER
	{
		INT32		nSceneID;
		INT32		nTemplateID;
		UINT32		dwRoleID;
	};

    struct M2O_GM_COMMAND : ML_MESSAGE_HEADER
    {
        UINT32		dwRoleID;
        BOOL		bResult;
        char		szName[ROLE_NAME_LEN];
        char		szCommand[0];
    };

	struct M2O_REALMONEY_MONEY02 : ML_MESSAGE_HEADER
	{
		INT32		nCount;
	};

	struct M2O_REALMONEY_ITEM : ML_MESSAGE_HEADER
	{
		INT32		nCount;
	};

    struct M2O_GUILD_EVENT : ML_MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        INT32       nActionType;
        UINT32      dwValue1;
        UINT32      dwValue2;
        UINT32      dwValue3;
        UINT32      dwValue4;
        UINT8       bGM;
    };

    struct M2O_GUILD_CHEST : ML_MESSAGE_HEADER 
    {
        UINT32      dwGuildID;
        INT32       nValue;
        INT32       nReason;
    };

    struct M2O_GUILD_STAT : ML_MESSAGE_HEADER 
    {
        GUILD_STAT  stat[MAX_SERVER_GROUP_COUNT];
    };

    struct M2O_BILLING_REQUEST : ML_MESSAGE_HEADER
    {
        INT32       nAction;
        UINT32      dwRpcID;
        char        szUserName[USER_NAME_LEN];
        char        szUserName2[USER_NAME_LEN];
        char        szUniqueID[OA_BILLING_UNIQUE_ID_LEN];
        char        szUniqueID2[OA_BILLING_UNIQUE_ID_LEN];
        UINT32      dwRoleID;
        UINT32      dwRoleID2;
        UINT64      qwOrderID;
        UINT64      qwOrderID2;
        INT32       nAmount;
        INT32       nParam;
    };

    struct M2O_BILLING_RESULT : ML_MESSAGE_HEADER
    {
        INT32       nAction;
        UINT32      dwRpcID;
        char        szUniqueID[OA_BILLING_UNIQUE_ID_LEN];
        INT32       nResult;
    };
};
// tolua_end
#pragma pack(pop)

#endif  // _M2O_MESSAGE_H_
