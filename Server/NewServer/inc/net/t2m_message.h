#ifndef _T2M_MESSAGE_H_
#define _T2M_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum T2M_MESSAGE_ID
    {
        t2m_begin = t2m_message_begin,

        t2m_register,
        t2m_ready,
        t2m_close_ack,
        
        t2m_client_shutdown,
        t2m_enter_gate,
        t2m_query_scene,
        t2m_return_select_role,
        t2m_change_gs_ack,
		t2m_check_new_name,

        t2m_client_msg,

        t2m_end = t2m_message_end
    };

    struct T2M_REGISTER : MESSAGE_HEADER
    {
        UINT32  dwInternalAddr;
        UINT16  wInternalPort;
		UINT8	byExternalCount;
		UINT32  dwExternalAddr[MAX_EXTERNAL_IP_COUNT];
		UINT16  wExternalPort[MAX_EXTERNAL_IP_COUNT];
    };

    struct T2M_READY : MESSAGE_HEADER
    {

    };

    struct T2M_CLOSE_ACK : MESSAGE_HEADER
    {
    };

    struct T2M_ENTER_GATE : MESSAGE_HEADER
    {
        UINT32      dwClientSessionID;
        UINT32		dwIpAddr;
        char        szMac[MAC_ADDRESS_LEN];
        char        szOASessionID[OA_SESSION_ID_LEN];
		char        szUserName[USER_NAME_LEN];
        char        szPGT[OA_PGT_FIELD_LEN];
        unsigned	bAdult			: 1;
		unsigned	bIpWhiteList	: 1;
		unsigned	bUserWhiteList	: 1;
    };

    struct T2M_QUERY_SCENE : MESSAGE_HEADER
    {
        UINT32           dwClientSessionID;
        UINT32           dwRoleID;
        UINT32           dwSaveTime;

        INT32            nSceneTempID;
        INT32            nSceneID;
        INT32            nX;
        INT32            nY;
        INT32            nZ;
        UINT16           wFaceDirection;

        INT32            nReturnSceneTempID;
        INT32            nReturnSceneID;
        INT32            nReturnX;
        INT32            nReturnY;
        INT32            nReturnZ;
        UINT16           wReturnFaceDirection;
    };

    struct T2M_CLIENT_SHUTDOWN : MESSAGE_HEADER
    {
        UINT32 dwClientSessionID;
		UINT8  byShutDownType;
    };

    struct T2M_RETURN_SELECT_ROLE : MESSAGE_HEADER
    {
        UINT32 dwClientSessionID;   
    };

    struct T2M_CHANGE_GS_ACK : MESSAGE_HEADER
    {
        UINT32           dwClientSessionID;   
    };

    struct T2M_CHECK_NEW_NAME : MESSAGE_HEADER
    {
        UINT32  dwClientSessionID;
		char	szName[COMMON_NAME_LEN];
        char    UserData[USER_DATA_LEN];
    };

    struct T2M_CLIENT_MSG : MESSAGE_HEADER
    {
        UINT32  dwClientSessionID;
        char    szData[0];
    };
};
#pragma pack(pop)

#endif  // _T2M_MESSAGE_H_