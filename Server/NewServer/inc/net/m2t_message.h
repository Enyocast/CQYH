#ifndef _M2T_MESSAGE_H_
#define _M2T_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum M2T_MESSAGE_ID
    {
        m2t_begin = m2t_message_begin,

        m2t_register_ack,

        m2t_enter_gate_ack,
        m2t_query_scene_ack,
        m2t_close_client_session,
        m2t_return_select_role,

        m2t_change_gs,

        m2t_client_msg,
        m2t_broadcast_client_msg,

		m2t_switch_server_group_state,
		m2t_gm_command,

		m2t_check_new_name,

        m2t_end = m2t_message_end
    };

    struct M2T_REGISTER_ACK : MESSAGE_HEADER
    {
        UINT32           dwGTSessionID;
    };

    struct M2T_ENTER_GATE : MESSAGE_HEADER
    {
        UINT32          dwSessionID;
        INT32           nErrCode;
        UINT32          dwQueueLen;
    };

    struct M2T_QUERY_SCENE_ACK : MESSAGE_HEADER
    {
        INT32           dwClientSessionID;
        UINT32          dwRoleID;
        UINT32          dwGSSessionID;
		INT32			nErrorCode;
        INT32           nErrCodeParam1;
        INT32           nErrCodeParam2;
    };

    struct M2T_RETURN_SELECT_ROLE : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
    };

    struct  M2T_CHANGE_GS : MESSAGE_HEADER
    {
        UINT32           dwClientSessionID;
        UINT32           dwGSSessionID;
    };


    struct M2T_CLIENT_MSG : MESSAGE_HEADER
    {
        UINT32      dwSessionID;
        char        szData[0];
    };

    struct M2T_BROADCAST_CLIENT_MSG : MESSAGE_HEADER
    {
        UINT16      wSessionCount;
        UINT32      dwSessionIDList[0];
    };

    struct M2T_CLOSE_CLIENT_SESSION : MESSAGE_HEADER
    {
        UINT32      dwClientSessionID;
    };

	struct M2T_SWITCH_SERVER_GROUP_STATE : MESSAGE_HEADER
	{
		UINT8		byServerGroup;
		UINT8		byOpened;
	};

	struct M2T_GM_COMMAND : MESSAGE_HEADER
	{
		char        szGMCommand[0];
	};

	struct M2T_CHECK_NEW_NAME : MESSAGE_HEADER
	{
		INT32	nErrorCode;
        UINT32  dwClientSessionID;
		UINT32	dwID;
		char	szName[COMMON_NAME_LEN];
        char    UserData[USER_DATA_LEN];
	};
};
// tolua_end
#pragma pack(pop)

#endif  // _M2T_MESSAGE_H_