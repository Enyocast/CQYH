#include "stdafx.h"
#include "guardserver.h"

#include "shellapi.h"
#include "shlwapi.h"

#include <algorithm>

//#include "version.h"
//#include "net.h"
//#include "ifile.h"
#include "statis_info.h"
#include "dump.h"
#include "report.h"
#include "time_ex.h"
#include "process_option.h"	//GetServerShortName
//
#include "gd_session_mgr.h"

#include "process_mgr.h"
#include "cmd_mgr.h"
#include "guard_config.h"
#include "global_config.h"	//LoadGuardConfig
#include "dir.h"
#include "ifile.h"

#include "direct.h"
#include "shellapi.h"
#include "shlwapi.h"

//#include "report.h"
//#include "statis_info.h"


const char* s_szFixHeader = 
"********       ********        ********        ********        ********\n"\
"   id            type          session           state            mode \n";

const char* s_szFixLineContent = 
"%6d\t\t%4s\t\t%2d\t%15s\t\t%6s\n";

const char* s_szFixTail = 
"********       ********        ********        ********        ********\n";

const char* s_szEmptyLine =
"                                                                     ";

static char s_szCmd[1024]={0};
static INT32 s_nCmdLen = 0;

CGuardServer CGuardServer::ms_Instance;
CGuardServer::CGuardServer()
{
    m_pNet = NULL;
    m_pSocketAcceptor = NULL;
	m_bRun = FALSE;
	m_qwLatestTickCheckDiskSpace = 0LL;
}

CGuardServer::~CGuardServer()
{
    UnInit();
}

CGuardServer& CGuardServer::GetInstance(void)
{
    return ms_Instance;
}

BOOL CGuardServer::Init(INetEventHandler* poNetEventHandler)
{
    INT32 nRetCode = 0;
    UINT32 dwAddr;
    m_bRun = TRUE;
	m_qwLatestTickCheckDiskSpace = 0LL;
	memset(m_szProcessingVersion, 0, sizeof(m_szProcessingVersion));
	memset(m_szProcessingPatch, 0, sizeof(m_szProcessingPatch));
    INTRANET_INIT_PARAM IntranetInitParam;
    SIMPLE_INIT_PARAM SimpleInitParam;

    nRetCode = m_PacketAllocator.Init(g_GuardConfig.Net.nSmallPacketCount,
        g_GuardConfig.Net.nLargePacketCount);
    LOG_PROCESS_ERROR(nRetCode);

    // internal
#if defined(WIN32)
    IntranetInitParam.nMaxAcceptor = g_GuardConfig.Net.nMaxAcceptor;
    IntranetInitParam.nMaxConnector = g_GuardConfig.Net.nMaxConnector;
    IntranetInitParam.nMaxSessionCount = g_GuardConfig.Net.nMaxSessionCount;
    IntranetInitParam.nSendBufSize = g_GuardConfig.Net.nSendBufSize;
    IntranetInitParam.nRecvBufSize = g_GuardConfig.Net.nRecvBufSize;
    IntranetInitParam.nPacketBufferSize = g_GuardConfig.Net.nPacketBufferSize;
	IntranetInitParam.nDisconnectTimeout = g_GuardConfig.nShareMemDisconnectTimeout;
    m_pNet = g_CreateNetInterface(netSimple, &m_PacketAllocator, poNetEventHandler, &IntranetInitParam);
#else
    SimpleInitParam.nMaxAcceptor = g_GuardConfig.Net.nMaxAcceptor;
    SimpleInitParam.nMaxConnector = g_GuardConfig.Net.nMaxConnector;
    SimpleInitParam.nMaxSessionCount = g_GuardConfig.Net.nMaxSessionCount;
    SimpleInitParam.nSendBufSize = g_GuardConfig.Net.nSendBufSize;
    SimpleInitParam.nRecvBufSize = g_GuardConfig.Net.nRecvBufSize;
    SimpleInitParam.nPacketBufferSize = g_GuardConfig.Net.nPacketBufferSize;
    m_pNet = g_CreateNetInterface(netSimple, &m_PacketAllocator, poNetEventHandler, &SimpleInitParam);
#endif
    LOG_PROCESS_ERROR(m_pNet);

    m_pSocketAcceptor = m_pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(m_pSocketAcceptor);

    dwAddr = inet_addr(g_GuardConfig.szAddress);
    LOG_PROCESS_ERROR(dwAddr != INADDR_NONE);

	nRetCode = m_pSocketAcceptor->Open(dwAddr, g_GuardConfig.dwPort);
	if (!nRetCode)
	{
		INF("failed to open listen port at %s:%d", g_GuardConfig.szAddress, g_GuardConfig.dwPort);
		LOG_PROCESS_ERROR(nRetCode);
	}

    INF("opened listen port at %s:%d", g_GuardConfig.szAddress, g_GuardConfig.dwPort);

    INF("Guard initialized successfully");

    return TRUE;
Exit0:
    UnInit();

    return FALSE;
}

BOOL CGuardServer::UnInit(void)
{
    INT32 nRetCode = 0;

    if (m_pSocketAcceptor)
    {
        nRetCode = m_pSocketAcceptor->Close();
        LOG_CHECK_ERROR(nRetCode);

        nRetCode = m_pNet->DestroyAcceptor(m_pSocketAcceptor);
        LOG_CHECK_ERROR(nRetCode);

        m_pSocketAcceptor = NULL;
    }

    if (m_pNet)
    {
        nRetCode = m_pNet->UnInit();
        LOG_CHECK_ERROR(nRetCode);

#if defined(WIN32)
        nRetCode = g_DestroyNetInterface(netSimple, m_pNet);
#elif defined(__linux__)
        nRetCode = g_DestroyNetInterface(netSimple, m_pNet);
#endif
        LOG_CHECK_ERROR(nRetCode);
        m_pNet = NULL;
    }

    nRetCode = m_PacketAllocator.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE; 
}

BOOL CGuardServer::Close(void)
{
    m_bRun = FALSE;
    return TRUE;
}

#define CHECK_DISK_SPACE_INTERVAL (10 * 1000)
#define ASYNC_DELETE_RESULT_FILENAME "ASYNC_DELETE_RESULT.TEXT"

BOOL _AsyncDeleteDirectory(const char *dirName)
{
	INT32 nRetCode = 0;

	char szParam[MAX_PATH] = { 0 };
	sprintf(szParam, "/C \"echo %s 1>%s  && rmdir /S /Q %s && del /Q /F %s\"",
		dirName, ASYNC_DELETE_RESULT_FILENAME, dirName, ASYNC_DELETE_RESULT_FILENAME);
	INF("cmd.exe %s", szParam);
	nRetCode = (INT32)ShellExecute(NULL, "open", "cmd.exe", szParam, NULL, SW_HIDE);
	LOG_CHECK_ERROR(nRetCode > 32);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGuardServer::_AsyncEraseOldestLogSubFolders(std::string strSubFolderName)
{
	INT32 nRetCode = 0;

	ULARGE_INTEGER FreeBytes;
	char szLog[256] = { 0 };

	// delete
	std::string path = std::string();
	path = g_GuardConfig.szServerRunPath + std::string("\\log\\") + strSubFolderName;

	nRetCode = _AsyncDeleteDirectory(path.c_str());
	if (nRetCode)
	{
		// remove directory
		nRetCode = RemoveDirectory(path.c_str());
		LOG_CHECK_ERROR(nRetCode);

		// 
		snprintf(szLog, sizeof(szLog), "asnyc deleting files under %s", path.c_str());
		CRI(szLog);
		REPORT(1, szLog);
		GD_ALERT_MT(szLog);

		// leave a mark
		path += std::string("_cleard_by_guard");
		nRetCode = g_CreateDirectory(path.c_str(), TRUE);
		LOG_CHECK_ERROR(nRetCode);
	}

	return TRUE;
Exit0:
	return FALSE;
}

struct CFileDeleter
{
	std::string FolderPath;

	BOOL RequireDirectory()	{ return FALSE; }

	BOOL operator()(const char* szFileName)
	{
		std::string path = std::string();
		path = FolderPath + std::string("\\") + szFileName;

		DeleteFile(path.c_str());

		return TRUE;
	}
};

BOOL CGuardServer::_EraseOldestLogSubFolders(std::string strSubFolderName)
{
	INT32 nRetCode = 0;

	ULARGE_INTEGER FreeBytes;
	char szLog[256] = { 0 };

	// delete
	std::string path = std::string();
	path = g_GuardConfig.szServerRunPath + std::string("\\log\\") + strSubFolderName;

	CFileDeleter op;
	op.FolderPath = path;
	nRetCode = g_DirectoryTraverse(path.c_str(), op);
	if (nRetCode)
	{
		// remove directory
		nRetCode = RemoveDirectory(path.c_str());
		LOG_CHECK_ERROR(nRetCode);
	}

	// 
	snprintf(szLog, sizeof(szLog), "deleting files under %s", path.c_str());
	CRI(szLog);
	REPORT(1, szLog);
	GD_ALERT_MT(szLog);

	// leave a mark
	path += std::string("_cleard_by_guard");
	nRetCode = g_CreateDirectory(path.c_str(), TRUE);
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGuardServer::MainLoop(void)
{
	INT32 nRetCode = 0;
	FILE* fp = NULL;
	ULARGE_INTEGER FreeBytes;
	INT32 nLogCleanThreshold = g_GuardConfig.nLogCleanThreshold;
	nLogCleanThreshold = nLogCleanThreshold > 0 ? nLogCleanThreshold : 16; // unit: GByte

    UINT64 qwStartTick = GetTickCountEx();
    static UINT64 s_qwLastUpdateTick = 0;

    nRetCode = m_pNet->MainLoop();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CGDSessionMgr::GetInstance().MainLoop();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CProcessMgr::GetInstance().MainLoop();
    LOG_PROCESS_ERROR(nRetCode);

	//version check
	nRetCode = 	ProcessDeployServerVersion();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = ProcessHotUpdatePatch();
	LOG_CHECK_ERROR(nRetCode);
	
	BOOL bCheckDiskSpace = FALSE;
	if (qwStartTick - m_qwLatestTickCheckDiskSpace > CHECK_DISK_SPACE_INTERVAL)
	{
		bCheckDiskSpace = TRUE;
		m_qwLatestTickCheckDiskSpace = qwStartTick;
	}
	else
	{
		//// disk space check
		//if (fp = fopen(ASYNC_DELETE_RESULT_FILENAME, "r"))
		//{
		//	fclose(fp);
		//	fp = NULL;
		//	// deleting, do nothing
		//}
		//else
		//{
		//	bCheckDiskSpace = TRUE;
		//}
	}

	if (bCheckDiskSpace)
	{
		nRetCode = GetDiskFreeSpaceEx(g_GuardConfig.szServerRunPath, &FreeBytes, NULL, NULL);
		if (nRetCode)// not zero
		{
			if (FreeBytes.QuadPart <= 1024LL * 1024 * 1024 * nLogCleanThreshold)
			{
				if (m_roLogFolderEntries.empty())
				{
					nRetCode = _GetLogSubFolders(g_GuardConfig.szServerRunPath);
					LOG_CHECK_ERROR(nRetCode);
				}

				if (!m_roLogFolderEntries.empty())
				{
					char szLog[256] = { 0 };
					snprintf(szLog, sizeof(szLog), "server path %s disk space less than %d G, now clear some oldest log folders", g_GuardConfig.szServerRunPath, nLogCleanThreshold);
					CRI(szLog);
					REPORT(1, szLog);
					GD_ALERT_MT(szLog);

					//nRetCode = _AsyncEraseOldestLogSubFolders(*(m_roLogFolderEntries.begin()));
					nRetCode = _EraseOldestLogSubFolders(*(m_roLogFolderEntries.begin()));
					LOG_CHECK_ERROR(nRetCode);

					m_roLogFolderEntries.erase(m_roLogFolderEntries.begin());
				}
			}
		}
	}

    if (kbhit())
    {
        char ch = getch();
        if (ch == '\r')
        {
			nRetCode = CCmdMgr::GetInstance().ExecOPCmd(s_szCmd);
			LOG_CHECK_ERROR(nRetCode);

            s_nCmdLen = 0;
            s_szCmd[s_nCmdLen] = 0;
            
        }
        else if(ch == '\b')
        {
            s_nCmdLen--;
            if(s_nCmdLen >= 0 && s_nCmdLen < sizeof(s_szCmd) )
                s_szCmd[s_nCmdLen] = 0;
            else
                s_nCmdLen = 0;
        }
        else if(ch > 0)
        {
            if ( s_nCmdLen + 1 >= sizeof(s_szCmd) )
            {
                s_nCmdLen = 0;
            }
            s_szCmd[s_nCmdLen++] = ch;
            s_szCmd[s_nCmdLen] = 0;
        }
        else
        {

        }
        PrintCmdPrompt();
    }

    if (qwStartTick - s_qwLastUpdateTick > 500)
	{
		g_MainloopStatisInfo();

        _UpdateScreen();
        s_qwLastUpdateTick = qwStartTick;
    }

    UINT64 qwEndTick = GetTickCountEx();
    if (qwEndTick - qwStartTick < (1000 / GAME_FPS))
        Sleep(1);
    else
        CRI("too slow main loop %d", (INT32)(qwEndTick - qwStartTick));

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGuardServer::PrintCmdPrompt()
{
    printf("\r%s", s_szEmptyLine);
    printf("\rcmd:%s", s_szCmd);

    return TRUE;
}

void CGuardServer::Cls()
 {
    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */ 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */ 

    /* get the number of character cells in the current buffer */
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	LOG_PROCESS_ERROR(hConsole );
    
	bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
	LOG_PROCESS_ERROR(bSuccess);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */ 

    bSuccess = FillConsoleOutputCharacter( hConsole, (CHAR) ' ',
       dwConSize, coordScreen, &cCharsWritten );
	LOG_PROCESS_ERROR(bSuccess);

    /* get the current text attribute */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
	LOG_PROCESS_ERROR(bSuccess);

    /* now set the buffer's attributes accordingly */ 

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
       dwConSize, coordScreen, &cCharsWritten );
	LOG_PROCESS_ERROR(bSuccess);

    /* put the cursor at (0, 0) */ 

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
	LOG_PROCESS_ERROR(bSuccess);

Exit0:
    return;
}

struct CLogSubFolderCollector
{
	std::vector<std::string> &m_roLogFolderEntries;
	CLogSubFolderCollector(std::vector<std::string> &oEntries):m_roLogFolderEntries(oEntries){}

	BOOL RequireDirectory()	{ return TRUE; }

	BOOL operator()(const char* szVersionEntryName)
	{
		INT32 nRetCode = 0;
		INT32 nYear = -1;
		INT32 nMonth = -1;
		INT32 nDay = -1;
		PROCESS_ERROR(strlen(szVersionEntryName) == strlen("2015_07_01") );

		nRetCode = sscanf(szVersionEntryName, "%04d_%02d_%02d", &nYear, &nMonth, &nDay);
		PROCESS_ERROR(nRetCode == 3);

		m_roLogFolderEntries.push_back(szVersionEntryName);
	Exit0:
		return TRUE;
	}
};

BOOL CGuardServer::_GetLogSubFolders(const char* pszTargetDir)
{
	INT32 nRetCode = 0;
	char szDir[MAX_PATH] = {0};
	snprintf(szDir, sizeof(szDir),"%s\\log", pszTargetDir);

	m_roLogFolderEntries.clear();
	CLogSubFolderCollector stChecker(m_roLogFolderEntries);

	nRetCode = g_DirectoryExists(szDir);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = g_DirectoryTraverse(szDir, stChecker);
	LOG_PROCESS_ERROR(nRetCode);

	sort(m_roLogFolderEntries.begin(), m_roLogFolderEntries.end());

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGuardServer::_PrintProcessContent()
{
	char stSessionContent[256] = { 0 };

	CProcessMgr::CSprocessList& rList = CProcessMgr::GetInstance().GetProcesses();

	for (CProcessMgr::CSprocessListItr itr = rList.begin(); itr != rList.end(); ++itr)
	{
		LOG_PROCESS_ERROR(itr->byType >= stMS && itr->byType < stClient);

		BOOL bConnected = FALSE; 
		if (itr->bySessionID > 0)
		{
			bConnected = CGDSessionMgr::GetInstance().CheckSocketConnected(itr->byType, itr->bySessionID);
		}
		char* szState = bConnected ? "normal" : "unconnect";
		char* szMode = itr->bAuto ? "auto" : "manul";

		snprintf(stSessionContent, sizeof(stSessionContent), s_szFixLineContent,
			itr->dwProcessID, GetServerShortName(itr->byType), itr->bySessionID, szState, szMode);
		printf("%s", stSessionContent);
	}

	return TRUE;
Exit0:
	return FALSE;
}

extern BOOL g_bStartFromCmd;
BOOL CGuardServer::_UpdateScreen()
{
    INT32 nRetCode = 0;

	if (g_bStartFromCmd)
	{
		Cls();
	}
    printf("%s", s_szFixHeader);
    
    nRetCode = _PrintProcessContent();
    LOG_PROCESS_ERROR(nRetCode);

    printf("%s", s_szFixTail);

    nRetCode = CCmdMgr::GetInstance().PrintCmdDescribe();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = PrintCmdPrompt();
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGuardServer::ReloadConfig()
{
	int nRetCode = 0;
	char szTmpPath[PATH_LEN] = {0};

	INF("ReloadConfig(), g_GuardConfig.szServerRunPath before reload: %s", g_GuardConfig.szServerRunPath);

	nRetCode = LoadGuardConfig("guard_config.lua");
	LOG_PROCESS_ERROR(nRetCode);

	if (PathIsRelative(g_GuardConfig.szServerRunPath))
	{
		snprintf(szTmpPath, sizeof(szTmpPath),"%s", g_GuardConfig.szServerRunPath);
		snprintf(g_GuardConfig.szServerRunPath, sizeof(g_GuardConfig.szServerRunPath), "%s\\%s", _getcwd(NULL, 0), szTmpPath);
	}
	//if (PathIsRelative(g_GuardConfig.szServerVersionPath))
	//{
	//	snprintf(szTmpPath, sizeof(szTmpPath), "%s", g_GuardConfig.szServerVersionPath);
	//	snprintf(g_GuardConfig.szServerVersionPath, sizeof(g_GuardConfig.szServerVersionPath), "%s\\%s", _getcwd(NULL, 0), szTmpPath);
	//}
	//if (PathIsRelative(g_GuardConfig.szServerPatchPath))
	//{
	//	snprintf(szTmpPath, sizeof(szTmpPath), "%s", g_GuardConfig.szServerPatchPath);
	//	snprintf(g_GuardConfig.szServerPatchPath, sizeof(g_GuardConfig.szServerPatchPath), "%s\\%s", _getcwd(NULL, 0), szTmpPath);
	//}
	snprintf(g_GuardConfig.szServerVersionPath, sizeof(g_GuardConfig.szServerVersionPath), "%s\\%s", _getcwd(NULL, 0), "version");
	snprintf(g_GuardConfig.szServerPatchPath, sizeof(g_GuardConfig.szServerPatchPath), "%s\\%s", _getcwd(NULL, 0), "patch");

	if (!g_DirectoryExists(g_GuardConfig.szServerRunPath))
	{
		nRetCode = g_CreateDirectory(g_GuardConfig.szServerRunPath, TRUE);
		LOG_PROCESS_ERROR(nRetCode);
	}
	if (!g_DirectoryExists(g_GuardConfig.szServerVersionPath))
	{
		nRetCode = g_CreateDirectory(g_GuardConfig.szServerVersionPath, TRUE);
	}
	if (!g_DirectoryExists(g_GuardConfig.szServerPatchPath))
	{
		nRetCode = g_CreateDirectory(g_GuardConfig.szServerPatchPath, TRUE);
	}

	snprintf(szTmpPath, sizeof(szTmpPath), "%s\\log", g_GuardConfig.szServerRunPath);
	SetDumpFolder(szTmpPath);

	INF("g_GuardConfig.szServerRunPath after reload: %s", g_GuardConfig.szServerRunPath);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGuardServer::FetchCurrentVersion( char* pcszCurrentVersion, int nLen  )
{
    INT32 nRetCode = 0;
	FILE* pFileHandle = NULL;

	char szCurrentVersionFilePath[PATH_LEN] = { 0 };
	snprintf(szCurrentVersionFilePath, sizeof(szCurrentVersionFilePath), "%s\\%s", g_GuardConfig.szGuardPath, CURRENT_VERSION_FILE_NAME);
    char szFileContent[128] = {0};

    LOG_PROCESS_ERROR( pcszCurrentVersion );

    // open file
	pFileHandle = fopen(szCurrentVersionFilePath, "r+t");
    LOG_PROCESS_ERROR(pFileHandle != NULL); 

    nRetCode = fread(szFileContent, sizeof(char), sizeof(szFileContent), pFileHandle);
    LOG_PROCESS_ERROR(nRetCode > 0);
	szFileContent[nRetCode] = '\0';

    nRetCode = fclose(pFileHandle);
    pFileHandle = NULL;
    LOG_PROCESS_ERROR(nRetCode == 0);

    nRetCode = strlen(szFileContent);
    for (int i=0; i<nRetCode; ++i)
    {
		if (szFileContent[i] == '\n' || szFileContent[i] == '\r' || szFileContent[i] == ' ')
        {
            szFileContent[i] = '\0';
            break;
        }
    }
    strxcpy(pcszCurrentVersion, szFileContent, nLen);

    return TRUE;
Exit0:
	if (pFileHandle)
	{
		nRetCode = fclose(pFileHandle);
		pFileHandle = NULL;
	}
    strxcpy(pcszCurrentVersion, "", nLen);
    return FALSE;
}

BOOL CGuardServer::ProcessDeployServerVersion()
{
	INT32 nRetCode = 0;
	FILE* pFileHandle = NULL;

	char szResultFilePath[PATH_LEN] = { 0 };
	snprintf(szResultFilePath, sizeof(szResultFilePath), "%s\\%s", ".", DEPLOY_RESULT_FILE_NAME);
	char szResultContent[COMMON_NAME_LEN] = {0};

	PROCESS_SUCCESS(m_szProcessingVersion[0] == 0);

    // open file
	{

		pFileHandle = fopen(szResultFilePath, "rb");
	    PROCESS_SUCCESS(pFileHandle == NULL); 

	    nRetCode = fread(szResultContent, 1, sizeof(szResultContent), pFileHandle);
	    LOG_PROCESS_ERROR(nRetCode > 0);

        nRetCode = fclose(pFileHandle);
        pFileHandle = NULL;
        LOG_PROCESS_ERROR(nRetCode == 0);
    }

    //LOG_PROCESS_ERROR(strnicmp(m_szTargetVersion, szVersion, strlen(m_szTargetVersion)) == 0);
    if(strnicmp(m_szProcessingVersion, szResultContent, strlen(m_szProcessingVersion)) == 0)
    {
		//nRetCode = ReloadConfig(); // move ahead
		//LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CGDMessageHandler::GetInstance().DoMTSyncProcessSummary();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = _unlink(szResultFilePath);
		LOG_PROCESS_ERROR(nRetCode == 0);

        nRetCode = CGDMessageHandler::GetInstance().DoMTDeployServerVersionAck(errSuccess, m_szProcessingVersion);
        LOG_PROCESS_ERROR(nRetCode);

        memset(m_szProcessingVersion, 0, sizeof(m_szProcessingVersion));
	}
    else
    {
		nRetCode = _unlink(szResultFilePath);
        LOG_PROCESS_ERROR(nRetCode == 0);

		nRetCode = CGDMessageHandler::GetInstance().DoMTDeployServerVersionAck(errUnknownError, szResultContent);
        LOG_PROCESS_ERROR(nRetCode);

        //memset(m_szTargetVersion, 0, sizeof(m_szTargetVersion));
    }

Exit1:
	return TRUE;
Exit0:
	if(pFileHandle)
	{
		nRetCode = fclose(pFileHandle);
		LOG_CHECK_ERROR(nRetCode == 0);
    }

    nRetCode = CGDMessageHandler::GetInstance().DoMTDeployServerVersionAck(errCritical, m_szProcessingVersion);
    LOG_CHECK_ERROR(nRetCode);

	return FALSE;
}

BOOL CGuardServer::ProcessHotUpdatePatch()
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;
	FILE* pFileHandle = NULL;
	char szPatchResultFile[PATH_LEN] = { 0 };
	snprintf(szPatchResultFile, sizeof(szPatchResultFile), "%s\\%s", g_GuardConfig.szGuardPath, HOT_UPDATE_PATCH_RESULT_FILE_NAME);
	char szResultContent[128] = { 0 };

	PROCESS_SUCCESS(m_szProcessingPatch[0] == 0);

	// open file
	{
		pFileHandle = fopen(szPatchResultFile, "rb");
		PROCESS_SUCCESS(pFileHandle == NULL);

		nRetCode = fread(szResultContent, 1, sizeof(szResultContent), pFileHandle);
		LOG_PROCESS_ERROR(nRetCode > 0);

		nRetCode = fclose(pFileHandle);
		pFileHandle = NULL;
		LOG_PROCESS_ERROR(nRetCode == 0);
	}

	//LOG_PROCESS_ERROR(strnicmp(m_szTargetVersion, szVersion, strlen(m_szTargetVersion)) == 0);
	if (strnicmp(m_szProcessingPatch, szResultContent, strlen(m_szProcessingPatch)) == 0)
	{
		memset(m_szProcessingPatch, 0, sizeof(m_szProcessingPatch));

		nRetCode = _unlink(szPatchResultFile);
		LOG_PROCESS_ERROR(nRetCode == 0);

		//nRetCode = ReloadConfig(); // hot patch only affect server but not guard self
		//LOG_PROCESS_ERROR_RET_CODE(nRetCode, errGMExecuteFailed);

		nRetCode = CGDMessageHandler::GetInstance().DoMTSyncProcessSummary();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CCmdMgr::GetInstance().ExecOPCmd("reload");
		LOG_PROCESS_ERROR_RET_CODE(nRetCode, errGMGSExecute);

		nRetCode = CGDMessageHandler::GetInstance().DoMTHotUpdatePatchAck(errSuccess, m_szProcessingPatch);
		LOG_PROCESS_ERROR(nRetCode);

	}
	else
	{
		nRetCode = _unlink(szPatchResultFile);
		LOG_PROCESS_ERROR(nRetCode == 0);

		nRetCode = CGDMessageHandler::GetInstance().DoMTHotUpdatePatchAck(errCritical, szResultContent);
		LOG_PROCESS_ERROR(nRetCode);
	}

Exit1:
	return TRUE;
Exit0:
	if (pFileHandle)
	{
		nRetCode = fclose(pFileHandle);
		LOG_CHECK_ERROR(nRetCode == 0);

		pFileHandle = NULL;
	}

	nRetCode = CGDMessageHandler::GetInstance().DoMTHotUpdatePatchAck(nResult, m_szProcessingPatch);
	LOG_CHECK_ERROR(nRetCode);

	return nResult;
}


/*

BOOL _InitServer(void)
{
    INT32 nRetCode = 0;
    CGDMessageHandler& rMessageHandler = CGDMessageHandler::GetInstance();

    CGuardServer& rGuardServer = CGuardServer::GetInstance();

    nRetCode = CLog::GetInstance().Init("guard_server", 
        g_GuardConfig.Log.nLogLevelMask, 
        g_GuardConfig.Log.nLogOutputMask, 
        g_GuardConfig.Log.bEnableLogThread,
        g_GuardConfig.Log.bPrintThreadID,
        g_GuardConfig.Log.bFlushFile);
	LOG_PROCESS_ERROR(nRetCode);
	g_InitReportSetting("GD", 1, g_GuardConfig.szReportAbsolutePath);

    INF("initializing guard server %d.%d.%d", MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER);

    nRetCode = rGuardServer.Init(&rMessageHandler);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CGDSessionMgr::GetInstance().Init(rGuardServer.GetNetInterface());
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = rMessageHandler.Init(rGuardServer.GetNetInterface(), rGuardServer.GetPacketAllocator());
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CProcessMgr::GetInstance().Init();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CCmdMgr::GetInstance().Init();
    LOG_PROCESS_ERROR(nRetCode);

    //save globalconfig
    //nRetCode = SaveGlobalConfig("globalconfig");
    //LOG_PROCESS_ERROR(nRetCode);
    return TRUE;
Exit0:
    return FALSE;
}

BOOL _UnInitServer(void)
{
    INT32 nRetCode = 0;

    nRetCode = CCmdMgr::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = CProcessMgr::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = CGDMessageHandler::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);
	
    nRetCode = CGDSessionMgr::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = CGuardServer::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = CLog::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

INT32 main(INT32 argc, TCHAR** argv) 
{ 
    INT32 nRetCode = 0;
    UINT64 qwCurrentTick = GetTickCountEx();
    INT32 nCmdStartIndex = 1;

#if defined(WIN32)
    nRetCode = StartDumpThread(NULL, TRUE);
    PROCESS_ERROR(nRetCode);
#endif    

    // initialize
	nRetCode = LoadGuardConfig("guard_config.lua");
	LOG_PROCESS_ERROR(nRetCode);

	g_InitStatisInfo(GetCurrentProcessId());

	nRetCode = _InitServer();
    LOG_PROCESS_ERROR(nRetCode);

	// process options
	nCmdStartIndex = ProcessOption(argc, argv);
	LOG_PROCESS_ERROR(nCmdStartIndex >= 1);

    if(argc > nCmdStartIndex)
    {
        char szCmd[COMMON_NAME_LEN] = {0};
        for(INT32 i = nCmdStartIndex; i < argc; ++i)
        {
			strxcat(szCmd, argv[i], sizeof(szCmd));
			strxcat(szCmd, " ", sizeof(szCmd));
        }

		nRetCode = CCmdMgr::GetInstance().ExecOPCmd(szCmd);
		LOG_CHECK_ERROR( nRetCode );
    }

#if (defined(WIN32) || defined(WIN64))
    {
        char szTitle[MAX_PATH];
        snprintf(szTitle, MAX_PATH, "Guard Server, ver %d.%d.%d", MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER);
        SetConsoleTitle(szTitle);
        INF(szTitle);
    }
#endif  // WIN32

    // main loop
    while (CGuardServer::GetInstance().IsRuning())
    {
        nRetCode = CGuardServer::GetInstance().MainLoop();
        LOG_PROCESS_ERROR(nRetCode);

        Sleep(1);
    }

    CGDSessionMgr::GetInstance().CloseAllSocketSession();
    while (CGDSessionMgr::GetInstance().CheckHasSocketSession())
    {
        nRetCode = CGuardServer::GetInstance().MainLoop();
        LOG_PROCESS_ERROR(nRetCode);

        Sleep(1);
    }

    // exit
    INF("Guard is exiting");
Exit0:
	INF("Guard has exited");

	nRetCode = _UnInitServer();
    LOG_CHECK_ERROR(nRetCode);

#if defined(WIN32)
    StopDumpThread();
#endif

    return 0; 
}

*/

