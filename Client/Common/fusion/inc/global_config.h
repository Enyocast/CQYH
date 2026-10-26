#ifndef _GLOBAL_CONFIG_H_
#define _GLOBAL_CONFIG_H_

// tolua_begin

struct LOG_CONFIG
{
    UINT32      nLogLevelMask;
    UINT32      nLogOutputMask;
    BOOL        bEnableLogThread;
    BOOL        bPrintThreadID;
    BOOL        bFlushFile;
};

struct NET_CONFIG
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

struct GM_CUSTOM_CONFIG
{
    char szRoleName0[25];    // ROLE_NAME_LEN
    char szRoleName1[25];    // ROLE_NAME_LEN
    char szRoleName2[25];    // ROLE_NAME_LEN
    char szRoleName3[25];    // ROLE_NAME_LEN
    char szRoleName4[25];    // ROLE_NAME_LEN
    char szRoleName5[25];    // ROLE_NAME_LEN
    char szRoleName6[25];    // ROLE_NAME_LEN
    char szRoleName7[25];    // ROLE_NAME_LEN
    char szRoleName8[25];    // ROLE_NAME_LEN
    char szRoleName9[25];    // ROLE_NAME_LEN
};

// tolua_end

BOOL LoadGlobalConfig(const char* pcszFileName);
BOOL SaveGlobalConfig(const char* pcszFilePath);

BOOL LoadMTConfig(const char* pcszFileName);
BOOL LoadGuardConfig(const char* pcszFileName);

BOOL LoadAreaGroupData(const char* pcszFileName);

extern char g_szGlobalConfigFileName[MAX_PATH];

#endif  // _GLOBAL_CONFIG_H_
