#ifndef _MT_CONFIG_H_
#define _MT_CONFIG_H_

#include "string_def.h"
#include "server_def.h"
#include "statis_info_def.h"

// tolua_begin
#pragma pack(push, 8)

struct MAINTAIN_CONFIG
{
    UINT32      nLogLevelMask;
    UINT32      nLogOutputMask;
    BOOL        bEnableLogThread;
    BOOL        bFlushFile;

    INT32       nMaxAcceptor;
    INT32       nMaxConnector;
    INT32       nMaxSessionCount;
    INT32       nSendBufSize;
    INT32       nRecvBufSize;
    INT32       nPacketBufferSize;

    INT32       nSmallPacketCount;
    INT32       nLargePacketCount;

    INT32       nPingTimeout;
    INT32       nServerPingInterval;
    BOOL		bPrintThreadID;
    INT32		nReconnectTime;

	char		szVersionPath[COMMON_NAME_LEN];
	char		szPatchPath[COMMON_NAME_LEN];
    char		szAreaConfigPath[COMMON_NAME_LEN];

    struct SAreaConfig
    {
        INT32		 areaID;
        char		 szVersion[COMMON_NAME_LEN];
        char		 szAreaName[COMMON_NAME_LEN];
        char		 szAreaFolderName[COMMON_NAME_LEN];

        struct SRemoteGuard
        {
            char  szAddress[COMMON_NAME_LEN];
            INT32 nPort;
            char  szGuardVersion[COMMON_NAME_LEN];
        };

        SRemoteGuard guardList[MAX_GUARD_COUNT_PER_AREA];
    };
    SAreaConfig   AreaConfig[MAX_AREA_COUNT];
};

#pragma pack(pop)
// tolua_end

extern MAINTAIN_CONFIG g_MTConfig;

#endif  // _MT_CONFIG_H_