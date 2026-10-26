#ifndef _COMMON_MESSAGE_H_
#define _COMMON_MESSAGE_H_

#include "internal_message_header.h"
#include "statis_info_def.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum COMMON_MESSAGE_ID
    {
        m2a_begin = m2a_message_begin,
        
        a2a_ping,

        m2a_server_info,
        m2a_all_ready,
        m2a_close,

        a2u_regrister,
        u2m_close,
		u2m_command,
		m2u_command_ack,

		//MT
		n2u_regrister,
		u2n_regrister_ack,
		u2n_sync_processes_summary, 
		n2u_update_process_info, 
		n2u_exec_cmd,	
		u2n_exec_cmd_ack,

        n2u_send_files, 
        u2n_send_files_ack,

		n2u_deploy_server_version,
		u2n_deploy_server_version_ack,

		u2n_update_statis_info,

		n2u_hot_update_patch,
		u2n_hot_update_patch_ack,

		a2u_notify,
		u2n_notify,

		u2n_error,

        m2a_end = m2a_message_end
    };

    enum eProcessState 
    {
		epsUnonnect = 0,	// exist but not connected
        epsNormal,
		epsDestroy,
    };

    struct A2A_PING : MESSAGE_HEADER
    {

    };

    struct SERVER_INFO
    {
        UINT8   byReady;
        UINT32  dwAddr;
        UINT16  wPort;
        INT32   nWorkload;
    };

    struct GT_SERVER_INFO : public SERVER_INFO
    {
		UINT8			byCount;
        UINT32          dwExternalAddr[MAX_EXTERNAL_IP_COUNT];
		UINT16          wExternalPort[MAX_EXTERNAL_IP_COUNT];
    };

    struct M2A_SERVER_INFO : MESSAGE_HEADER
    {
        SERVER_INFO     DB;
        SERVER_INFO     LS;
		SERVER_INFO     BS;
		SERVER_INFO		DL;
		SERVER_INFO		MM;
		SERVER_INFO     GS[MAX_GS_SESSION_COUNT];
		SERVER_INFO     MG[MAX_MG_SESSION_COUNT];
		GT_SERVER_INFO  GT[MAX_GT_SESSION_COUNT];
    };

    struct M2A_ALL_READY : MESSAGE_HEADER
    {

    };

    struct M2A_CLOSE : MESSAGE_HEADER
    {
        UINT32 dwTime;
    };

    struct A2U_REGRISTER : MESSAGE_HEADER
    {
        UINT8  byType;
        UINT8  bySessionID;
        UINT32 dwProcessID;
    };

    struct U2M_CLOSE : MESSAGE_HEADER
    {
    };

    struct U2M_COMMAND : MESSAGE_HEADER
    {
        char            szCommand[0];
    };

	struct M2U_COMMAND_RESPONSE : MESSAGE_HEADER
	{
		char            szResult[0];
	};

	struct A2U_NOTIFY : MESSAGE_HEADER
	{
		UINT8			bySvrType;
		UINT8			bySvrID;
		UINT8			byLevel;
		INT32			nErrorCode;
		char            szContent[0];
	};

	struct U2N_NOTIFY : MESSAGE_HEADER
	{
		UINT8			bySvrType;
		UINT8			bySvrID;
		UINT8			byLevel;
		INT32			nErrorCode;
		char            szContent[0];
	};

	struct U2N_ERROR : MESSAGE_HEADER
	{
		INT32			nErrorCode;
		char            szErrorInfo[128];
	};

	struct N2U_REGRISTER : MESSAGE_HEADER
	{
		CHAR				szName[32];
		CHAR				szPwd[32];
	};

	struct U2N_REGRISTER_ACK : MESSAGE_HEADER
    {
        INT32           nErrorCode;
        CHAR			szVersion[128];	// current server version
		INT32			nMsgVersion;
		CHAR			szBuildVersion[64];
	};

	struct U2N_SYNC_DEFAULT_INFO : MESSAGE_HEADER
	{
		UINT8				nDefaultCount[12];
	};

	struct N2U_UPDATE_SESSION : MESSAGE_HEADER
	{
		UINT8               byType;
		UINT32              dwProcessID;
		INT32				nState;		// eProcessState
		UINT32				dwSessionID;
		BOOL                bAuto;
	};

    struct U2N_UPDATE_STATIS_INFO : MESSAGE_HEADER
    {
        UINT8               byType;
        BOOL				bConnected;
        UINT32				dwSessionID;

        stStatisInfo        oStatisInfo;
    };

	struct N2U_UPDATE_CMD : MESSAGE_HEADER
	{
		char				szCmd[0];
	};

	struct U2N_UPDATE_CMD_ACK : MESSAGE_HEADER
	{
		INT32				nErrorCode;		// invalid field
		char				szResult[0];
	};

	enum eTransFileType
	{
		etftInvalid = -1,
		etftVersion = 0, // zip + config
		etftPatch,
		etftConfig
	};

    struct N2U_SEND_FILES : MESSAGE_HEADER
    {
        //which file
		INT32			nFileType;	//eTransFileType
        CHAR			szFileName[128];
        UINT16			wFileIndex;
        UINT16			wFileTotal;

        //which buffer
        UINT16			wBufferIndex;
        UINT16			wBufferTotal;
        //UINT8			byBufferFinished;   //redundant
        UINT16			wBufferSize;
        CHAR			szBuffer[32768];
    };

    struct U2N_SEND_FILES_ACK : MESSAGE_HEADER
    {
        CHAR			szFileName[128];
        UINT16			wFileIndex;
        UINT16			wFileTotal;

        //which buffer
        UINT16			wBufferIndex;
        UINT16			wBufferTotal;
        INT32			nErrorCode;
    };

	struct N2U_DEPLOY_SERVER_VERSION : MESSAGE_HEADER
	{
		CHAR				szVersion[128];
	};

	struct U2N_DEPLOY_SERVER_VERSION_ACK : MESSAGE_HEADER
	{
		INT32				nErrorCode;
		CHAR				szInfo[128];
	};

	struct N2U_HOT_UPDATE_PATCH : MESSAGE_HEADER
	{
		CHAR				szPatch[128];
	};

	struct U2N_HOT_UPDATE_PATCH_ACK : MESSAGE_HEADER
	{
		INT32				nErrorCode;
		CHAR				szInfo[128];
	};
};
// tolua_end

#define MAINTAIN_TOOLS_MSG_VERSION (0) // manual update

#pragma pack(pop)

#endif  // _COMMON_MESSAGE_H_