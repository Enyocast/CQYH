#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include "string_def.h"
#include "server_def.h"
#include "global_config.h"
#include "gm_svr_def.h"

// tolua_begin
#pragma pack(push, 8)

struct SERVER_CONFIG
{
	struct COMMON
	{
		char        szAreaName[COMMON_NAME_LEN];
		INT32       nAreaID;

		BOOL        bShowDumpDialog;
		INT32       nReconnectTime;
		INT32       nServerPingInterval;
		INT32       nServerPingTimeout;
		INT32       nShareMemDisconnectTimeout;
		char        szIntranetAddr[16];
		char        szIntranetMask[16];
		char		szPakFolder[COMMON_NAME_LEN];
		char        szCertServerAddr[COMMON_NAME_LEN];
		UINT32      dwCSPort;

		char        szGuardAddr[COMMON_NAME_LEN];
		UINT32      dwGuardPort;
		INT32		nRegisterGuardTimeout;
		INT32		nPingGuardTimeout;
		char        szReportAbsolutePath[PATH_LEN];

		struct IP_ADDR
		{
			char		szIP[COMMON_NAME_LEN];
			char		szMask[COMMON_NAME_LEN];
		};
		IP_ADDR		IpWhiteList[256];

		char		szSuperGMUserName[COMMON_NAME_LEN];
		struct USER_NAME
		{
			char		szUserName[COMMON_NAME_LEN];
		};
		USER_NAME		UserWhiteList[256];

	} Common;

	struct GS_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;
	} GS;

	struct MS_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		// object init count
		INT32       nInitSceneCount;
		INT32       nInitRoleCount;
		INT32       nInitUserCount;

		// net
		char        szAddress[COMMON_NAME_LEN];
		UINT32      dwGSPort;
		UINT32      dwGTPort;
		UINT32      dwLSPort;
		UINT32      dwDBPort;
		UINT32		dwBSPort;
		UINT32		dwDLPort;
		UINT32      dwGMPort;
		UINT32		dwMMPort;
		UINT32		dwOnlineRoleNumPort;

		// gm
		BOOL        bNeedConnectGMServer;
		char        szRemoteGMAddress[COMMON_NAME_LEN];
		UINT32      dwRemoteGMPort;

		// scene
		INT32       nInitGSCount;
		INT32       nInitGTCount;
		INT32		nInitBSCount;
		INT32		nInitDLCount;
		INT32		nInitMMCount;

		INT32		nSceneCleanTime;
		//team
		INT32       nInitTeamCount;
		INT32       nInitOnlineRoleCount;

		//group
		BOOL		bDBRegisterGroup;
		INT32       nInitGroup;

		// oa bill
		BOOL		bOABillingEnable;
		INT32		nOABillingRequestCount;
		INT32		nOABillingResultCount;
		char		szConfigFile[256];

        // time
        BOOL        bTimeCardEnabled;
        BOOL        bMonthCardEnabled;
        INT32       nTimeCardBillingPeriod;

		// oa reward
		BOOL		bOAAwardEnable;

		// fcm
		BOOL		bFcmEnable;
		INT32       nFcmCallbackCount;
	} MS;

	struct SERVER_GROUP_CONFIG
	{
		INT32	nMaxRoleCount;
		INT32	nMaxUserCount;
		BOOL	bPrecreateRole;
		char	szStartDate[COMMON_NAME_LEN];
		UINT32	dwStartDate;

		INT32	nMappedGroupID;
		BOOL	bClearGlobalData;
	};
	SERVER_GROUP_CONFIG	GroupConfig[MAX_SERVER_GROUP_COUNT];

	struct MG_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		INT32       nMaxClientSessionCount;
		INT32       nWorkThreadCount;
		UINT32      dwStartExternalPort;
		UINT32      dwStartInternalPort;
	} MG;

	struct MM_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		char        szAddress[COMMON_NAME_LEN];
		UINT32      dwMGPort;
		INT32		nInitMGCount;
	} MM;

	struct DB_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		UINT32      dwPort;

		// mysql db
		BOOL        bUseIndependentDB;

		char        szDBIPAddress[COMMON_NAME_LEN];
		UINT32      dwDBPort;
		char        szDBAccount[COMMON_NAME_LEN];
		char        szDBPassword[COMMON_NAME_LEN];
		char        szDBName[COMMON_NAME_LEN];
		char        szDBCharset[COMMON_NAME_LEN];

        char        szLogDBIPAddress[COMMON_NAME_LEN];
        UINT32      dwLogDBPort;
        char        szLogDBAccount[COMMON_NAME_LEN];
        char        szLogDBPassword[COMMON_NAME_LEN];
        char        szLogDBName[COMMON_NAME_LEN];
        char        szLogDBCharset[COMMON_NAME_LEN];

        char        szSlaverDBIPAddress[COMMON_NAME_LEN];
        UINT32      dwSlaverDBPort;
        char        szSlaverDBAccount[COMMON_NAME_LEN];
        char        szSlaverDBPassword[COMMON_NAME_LEN];
        char        szSlaverDBName[COMMON_NAME_LEN];
        char        szSlaverDBCharset[COMMON_NAME_LEN];

		// logic
		UINT32      dwMaxCache;
		UINT32      dwThreadCount;
		UINT32      dwProcessCount; //to be deleted
		UINT32      dwDBCloseTimeout;
	} DB;

	struct LS_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		UINT32      dwPort;

		BOOL		bOAAuthorizeEnable;
		INT32		nInitAuthCount;
		INT32       nTotalAuthingCount;
		char		szConfigFile[COMMON_NAME_LEN];
	} LS;

	struct GT_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		INT32       nMaxClientSessionCount;
		INT32       nWorkThreadCount;
		UINT32      dwStartExternalPort;
		UINT32      dwStartInternalPort;

		INT32       nLoginAuthTimeout;
		INT32       nRoleOperateTimeout;
		INT32       nPlayingTimeout;

		BOOL		bLogMessage;
		INT32		nEncryptCode;
		UINT32		dwClientOption;
	} GT;

	struct BS_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		INT32       nMaxClientSessionCount;
		INT32       nWorkThreadCount;
		UINT32      dwExternalPort;
		UINT32      dwInternalPort;
		//
		INT32		nGTReportTime;
		INT32		nHoldCliSessionTime;
	} BS;

	struct DL_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		UINT32      dwPort;
	} DL;

	struct NS_CONFIG
	{
		LOG_CONFIG  Log;
		NET_CONFIG  Net;

		char        szAddress[COMMON_NAME_LEN];
		UINT32      dwPort;

		char        szDBIPAddress[COMMON_NAME_LEN];
		UINT32      dwDBPort;
		char        szDBAccount[COMMON_NAME_LEN];
		char        szDBPassword[COMMON_NAME_LEN];
		char        szDBName[COMMON_NAME_LEN];
		char        szDBCharset[COMMON_NAME_LEN];
		INT32		nDBPoolSize;

	} NS;

    struct GM_CONFIG 
    { 
        UINT32      nLogLevelMask;
        UINT32      nLogOutputMask;
        BOOL        bEnableLogThread;
        BOOL        bPrintThreadID;
        BOOL        bFlushFile;

        INT32       nMaxAcceptor;
        INT32       nMaxConnector;
        INT32       nMaxSessionCount;
        INT32       nSendBufSize;
        INT32       nRecvBufSize;
        INT32       nPacketBufferSize;

        INT32       nSmallPacketCount;
        INT32       nLargePacketCount;

        // 
        INT32       nRolePoolNum;

        // net
        char        szAddress[256];
        UINT32      dwMSPort;
        UINT32      dwTLPort;
    } GM;

    struct GM_SECURITY 
    {
        struct GM_USER 
        {
            UINT32      dwUserID;
            char        szName[USER_NAME_LEN];
            char        szPwd[GM_TOOL_PASSWORD_LEN];
            INT32       nPermission;
        };

        struct GM_CMD_DATA 
        {
            char        szDescript[GM_CMD_NAME_LEN];
            INT32       nPermission;
        };

        INT32           nGMUserNum;
        GM_USER         gmUserList[MAX_GM_USER];
        INT32           nLDUserNum;
        GM_USER         LDUserList[MAX_GM_USER];
        GM_CMD_DATA     gmCmdList[GM_CMD_NUM];
    } GM_PWD;
};

extern SERVER_CONFIG g_ServerConfig;

inline BOOL IsValidGroup(INT32 nGroup)
{
    if (nGroup < 1 || nGroup > 31)
        return FALSE;

    return g_ServerConfig.MS.nInitGroup & (1 << nGroup);
}

#pragma pack(pop)
// tolua_end

#endif  // _SERVER_CONFIG_H_