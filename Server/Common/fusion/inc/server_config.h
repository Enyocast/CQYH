#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include "string_def.h"
#include "server_def.h"
#include "global_config.h"
#include "gm_svr_def.h"
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
		UINT32		dwLCPort;
		UINT32		dwGpkPort;

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

		// line scene recycle
		INT32		nLineSceneRecycleWarnTime;		//unit : ms
		INT32		nLineSceneRecyclePeriod;		//unit : ms
		INT32		nLineSceneRecycleLowThreshold;	//unit : percentage
		INT32		nLineSceneRecycleHighThreshold;	//unit : percentage

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
        UINT32      dwWaitCloseTime;

        // time
        BOOL        bTimeCardEnabled;
        BOOL        bMonthCardEnabled;
        INT32       nTimeCardBillingPeriod;

		// oa reward
		BOOL		bOAAwardEnable;

		// fcm
		BOOL		bFcmEnable;
		INT32       nFcmCallbackCount;

		// lc
		char        szLaunchServerAddress[COMMON_NAME_LEN];
		INT32		nLaunchServerReportInterval;
	} MS;

	struct SERVER_GROUP_CONFIG
	{
		INT32	nMaxRoleCount;
		INT32	nMaxNewRoleCount;
		INT32	nMaxUserCount;
		BOOL	bPrecreateRole;
		char	szStartDate[COMMON_NAME_LEN];
		UINT32	dwStartDate;

		INT32	nMappedGroupID;
		BOOL	bClearGlobalData;

        BOOL    bUseAllowBits;
        INT32   nAllowBits;
		BOOL	bAllowZeroBits;
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

        char        szSlaverLogDBIPAddress[COMMON_NAME_LEN];
        UINT32      dwSlaverLogDBPort;
        char        szSlaverLogDBAccount[COMMON_NAME_LEN];
        char        szSlaverLogDBPassword[COMMON_NAME_LEN];
        char        szSlaverLogDBName[COMMON_NAME_LEN];
        char        szSlaverLogDBCharset[COMMON_NAME_LEN];

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

		UINT32 dwPort;

		INT32 nStartHour;
		INT32 nFetchCountPerLoop;

		INT32 nStoneWarID;
		INT32 nStoneMagID;
		INT32 nStoneTaoID;
		INT32 nStoneRankTopCount;

		struct RENAME_DB_CONFIG
		{
			char        ip[COMMON_NAME_LEN];
			UINT32      port;
			char        account[COMMON_NAME_LEN];
			char        password[COMMON_NAME_LEN];
			char        db_name[COMMON_NAME_LEN];
			char        charset[COMMON_NAME_LEN];

		};

		struct RENAME_CONFIG
		{
			RENAME_DB_CONFIG	NameDB;
			RENAME_DB_CONFIG	RoleDB[6];
		};

		RENAME_CONFIG RenameConfig;
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

    struct MAC_DATA 
    {
        char        szMac[128];
    };

    struct GM_SECURITY 
    {
        struct GM_USER 
        {
            UINT32      dwUserID;
            char        szName[USER_NAME_LEN];
            char        szPwd[GM_TOOL_PASSWORD_LEN];
            INT32       nPermission;
            MAC_DATA    MacList[8];
        };

        struct GM_CMD_DATA 
        {
            char        szDescript[GM_CMD_NAME_LEN];
            INT32       nPermission;
        };

        struct CRM_IP_ADDR
        {
            char		szIP[COMMON_NAME_LEN];
            char		szMask[COMMON_NAME_LEN];
        };
        

        INT32           nGMUserNum;
        GM_USER         gmUserList[MAX_GM_USER];
        INT32           nLDUserNum;
        GM_USER         LDUserList[MAX_GM_USER];

        INT32           nCRMNum;
        GM_USER         CRMList[MAX_GM_USER];

        CRM_IP_ADDR		IpWhiteList[256];

        GM_CMD_DATA     gmCmdList[GM_CMD_NUM];
    } GM_PWD;

	// 自定义配置
	struct CUSTOM_CONFIG
	{
		BOOL               bGmComandEnable;         // 自定义[GM命令开关]
		GM_CUSTOM_CONFIG   GmRoleName;              // 自定义[GM角色名字]

		BOOL               bCustomGameTimeCardEnable;            // 自定义[点卡功能开关]
		INT32              nCustomFreeRoleLevel;                 // 自定义[自由人物等级]
		INT32              nCustomGameTimeCardTemplateID[10];    // 自定义[点卡道具物品ID]

		INT32              nLuck2NecklaceItemID[5];        // 运2运2项链物品ID
		INT32              nMinLuck2AttributelID;          // attribute.txt 配置中, "幸运2"属性的最小ID值
		INT32              nMaxLuck2AttributelID;          // attribute.txt 配置中, "幸运2"属性的最大ID值
		INT32			   nItemDropLimitLuck2NecklaceDuration;  // 限制时间/数量
		INT32			   nItemDropLimitLuck2NecklaceCount;


	} CC;

};

extern SERVER_CONFIG g_ServerConfig;
extern char g_GmRoleName[10][ROLE_NAME_LEN];

inline BOOL IsValidGroup(INT32 nGroup)
{
    if (nGroup < 1 || nGroup > 31)
        return FALSE;

    return g_ServerConfig.MS.nInitGroup & (1 << nGroup);
}

#pragma pack(pop)

#endif  // _SERVER_CONFIG_H_