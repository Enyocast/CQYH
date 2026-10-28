#ifndef _GUARD_CONFIG_H_
#define _GUARD_CONFIG_H_

#include "string_def.h"
#include "server_def.h"
#pragma pack(push, 8)

struct GUARD_LOG_CONFIG
{
	UINT32      nLogLevelMask;
	UINT32      nLogOutputMask;
	BOOL        bEnableLogThread;
	BOOL        bPrintThreadID;
	BOOL        bFlushFile;
};

struct GUARD_NET_CONFIG
{
	INT32       nMaxAcceptor;
	INT32       nMaxConnector;

	INT32       nSendBufSize;
	INT32       nRecvBufSize;
	INT32       nPacketBufferSize;

	INT32       nMaxSessionCount;
	INT32       nSmallPacketCount;
	INT32       nLargePacketCount;

	INT32		nMaxOperationPerLoop;	// used by iocp
	INT32		nSendLoopBufferSize;
	INT32		nRecvLoopBufferSize;
};

struct GUARD_CONFIG
{
	GUARD_LOG_CONFIG  Log;
	GUARD_NET_CONFIG  Net;

	char        szAddress[COMMON_NAME_LEN];
	UINT32      dwPort;

	INT32       nRegisterGuardTimeout;
	INT32       nPingGuardTimeout;

	INT32		nServerPingInterval;
	INT32		nServerPingTimeout;
	INT32		nShareMemDisconnectTimeout; 

	INT32       nLocalGSCount;
	INT32       nLocalGTCount;
	INT32       nLocalBSCount;
	INT32		nLocalDLCount;
	INT32       nLocalLSCount;
	INT32       nLocalDBCount;
	INT32       nLocalMSCount;
	INT32       nLocalGMCount;
	INT32		nLocalMMCount;
	INT32		nLocalMGCount;

	char		szMTUser[COMMON_NAME_LEN];
	char		szMTPwd[COMMON_NAME_LEN];
	char		szReportAbsolutePath[PATH_LEN];

	char		szServerVersionPath[PATH_LEN];
	char		szServerPatchPath[PATH_LEN];
	char		szServerRunPath[PATH_LEN];

	char		szGuardPath[PATH_LEN];
	INT32		nLogCleanThreshold;	 // unit:GByte
};

#pragma pack(pop)

extern GUARD_CONFIG g_GuardConfig;

#endif  // _GUARD_CONFIG_H_