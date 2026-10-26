#include "stdafx.h"
#include "log.h"

#include "time_ex.h"
#include "utf8.h"
#include "dir.h"
#include "mutex.h"
#include "dump.h"

#define LOG_BUFFER_SIZE			(10 * 1024 * 1024)
#define MAX_MESSAGE_LEN			(4 * 1024)
#define MAX_LOG_MESSAGE_COUNT	(64 * 1024)

struct LOG_MESSAGE
{
	INT32 nLevelIndex;
	INT32 nMessageSize;
	char szMessage[MAX_MESSAGE_LEN];
};

CLog CLog::ms_Instance;

char g_szLevelString[32] = 
{
    'D',
    'I',
    'W',
    'E',
    'C',
    'S',
    'M',
    'L',
	'P',
	'Y',
};

#if defined(WIN32)
INT32 g_nLevelColor[32] =
{
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
    FOREGROUND_GREEN,
    FOREGROUND_GREEN | FOREGROUND_RED,
    FOREGROUND_RED,
    FOREGROUND_RED,

    FOREGROUND_BLUE,
    FOREGROUND_BLUE | FOREGROUND_RED,
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
	
	FOREGROUND_BLUE | FOREGROUND_GREEN,
	FOREGROUND_BLUE | FOREGROUND_RED
};
#endif //WIN32

CLog::CLog()
{
    m_szModuleName[0] = 0;
	m_szCurrentFileFolder[0] = 0;
	m_szCurrentFilePath[0] = 0;
    m_dwProcessID = 0;
    m_eLogLevelMask = lltAll;
    m_eLogOutputMask = lotConsole;

    m_bPrintThreadID = FALSE;
    m_bFlushFile = FALSE;

    m_pFile = NULL;
    m_nCurrentSize = 0;
	m_dwLastUpdateCount = 0;
	m_dwLastFlushCount = 0;
#if defined(WIN32)
    m_hConsole = NULL;
#endif // WIN32
	m_pLogThread = NULL;
	m_dwThreadCount = 0;
	m_bStopThread = FALSE;
	m_pOutputFunc = NULL;
}

CLog::~CLog()
{
    UnInit();
}

CLog& CLog::GetInstance(void)
{
    return ms_Instance;
}

const char* CLog::GetModuleName(void)
{
	return m_szModuleName;
}

const char* CLog::GetLogFileFolder(void)
{
	return m_szCurrentFileFolder;
}

const char* CLog::GetLogFilePath(void)
{
	return m_szCurrentFilePath;
}

BOOL WINAPI HanlderRouting(DWORD CtrlType)
{
    return FALSE;
}

BOOL CLog::Init(const char* pcszModuleName, INT32 eLogLevelMask, INT32 eLogOutputMask, BOOL bLogThread, BOOL bPrintThreadID, BOOL bFlushFile)
{
    INT32 nRetCode = 0;

    PROCESS_ERROR(pcszModuleName);

#if defined(WIN32)
    m_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
    LOG_PROCESS_ERROR(m_hConsole != INVALID_HANDLE_VALUE);

	{
		CONSOLE_FONT_INFOEX FontInfo;
		SetConsoleOutputCP(CP_UTF8);
		FontInfo.cbSize = sizeof(FontInfo);
		FontInfo.dwFontSize.X = 8;
		FontInfo.dwFontSize.Y = 16;
		wcsncpy(FontInfo.FaceName, L"Consolas", LF_FACESIZE);
		FontInfo.FontFamily = FF_DONTCARE;
		FontInfo.FontWeight = 500;
		FontInfo.nFont = 1;
		SetCurrentConsoleFontEx(m_hConsole, FALSE, &FontInfo);
        SetConsoleMode(m_hConsole, ENABLE_INSERT_MODE);
        SetConsoleCtrlHandler(HanlderRouting, TRUE);
        HMENU hMenu = GetSystemMenu(GetConsoleWindow(), FALSE);
        EnableMenuItem(hMenu, SC_CLOSE, MF_GRAYED);
	}
#endif //WIN32

    strxcpy(m_szModuleName, pcszModuleName, MAX_MODULE_NAME);
	memset(m_szCurrentFileFolder, 0, sizeof(m_szCurrentFileFolder));
	memset(m_szCurrentFilePath, 0, sizeof(m_szCurrentFilePath));
    m_dwProcessID = GetCurrentProcessId();
    m_eLogLevelMask = eLogLevelMask;
    m_eLogOutputMask = eLogOutputMask;
    m_bPrintThreadID = bPrintThreadID;
    m_bFlushFile = bFlushFile;
	m_dwLastUpdateCount = 0;
	m_dwLastFlushCount = 0;

	if (bLogThread)
	{
		for (INT32 nIndex = 0; nIndex < MAX_LOG_THREAD_COUNT; nIndex++)
		{
			nRetCode = m_LogList[nIndex].Init(MAX_LOG_MESSAGE_COUNT);
			PROCESS_ERROR(nRetCode);
		}

		m_pLogThread = new CThread;
		PROCESS_ERROR(m_pLogThread);

		m_pLogThread->Start(&CLog::_LogThreadProc, this);
	}

    return TRUE;
Exit0:
    UnInit();

    return FALSE;
}

BOOL CLog::UnInit(void)
{
    INT32 nRetCode = 0;

	if (m_pLogThread)
	{
		m_bStopThread = TRUE;
		m_pLogThread->Wait();
		SAFE_DELETE(m_pLogThread);

		for (INT32 nIndex = 0; nIndex < MAX_LOG_THREAD_COUNT; nIndex++)
		{
			m_LogList[nIndex].UnInit();
		}
	}
	
	m_pOutputFunc = NULL;

    if (m_pFile)
    {
        fclose(m_pFile);
        m_pFile = NULL;
    }

    m_eLogLevelMask = m_eLogOutputMask = 0;

    return TRUE;
}

bool CLog::WriteLog(INT32 eLogLevel, const char* pcszMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;

    va_start(valist, pcszMessage);
    nRetCode = _WriteLog(eLogLevel, pcszMessage, valist);
    PROCESS_ERROR(nRetCode);
    va_end(valist);

    return true;
Exit0:
    return false;
}

void CLog::SetOutputMask(INT32 eLogOutputMask)
{
    m_eLogOutputMask = eLogOutputMask;
}

void CLog::SetLevelMask(INT32 eLogLevelMask)
{
	m_eLogLevelMask = eLogLevelMask;
}

INT32 CLog::GetLevelMask(void)
{
	return m_eLogLevelMask;
}

BOOL CLog::_WriteLog(INT32 eLogLevel, const char* pcszMessage, va_list valist)
{
    INT32 nRetCode = 0;
    static CMutex s_Mutex;
	LOG_MESSAGE* pLogMessage = NULL;
	LOG_MESSAGE LogMessage;
    char szMessage[MAX_MESSAGE_LEN];
    char cLevel = '?';
    INT32 nFreeSize = 0;
    const tm_ex* pNow = NULL;
    INT32 offset = 0;
	__declspec(thread) static UINT32 s_dwThreadIndex = -1;

    if ((eLogLevel & m_eLogLevelMask) == 0)
        return TRUE;

    PROCESS_ERROR(pcszMessage);

	if (m_pLogThread)
		pLogMessage = new LOG_MESSAGE;
	else
		pLogMessage = &LogMessage;
	PROCESS_ERROR(pLogMessage);
	pLogMessage->szMessage[0] = 0;
	pLogMessage->nMessageSize = 0;
	pLogMessage->nLevelIndex = 0;

    for (INT32 nIndex = 0; nIndex < 32; nIndex++)
    {
        if ((1 << nIndex) == eLogLevel)
        {
            if (g_szLevelString[nIndex] != 0)
				pLogMessage->nLevelIndex = nIndex;
            break;
        }
    }
	cLevel = g_szLevelString[pLogMessage->nLevelIndex];

    pNow = localtime_ex();
    if (m_bPrintThreadID)
    {
		offset = snprintf(pLogMessage->szMessage, MAX_MESSAGE_LEN,
            "%d-%02d-%02d %02d:%02d:%02d.%03d\t[%c] [%08X] ", 
            pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
            pNow->tm_hour, pNow->tm_min, pNow->tm_sec,
            pNow->tm_msec, cLevel, 
            CThread::GetThreadID()
        );
    }
    else
    {
		offset = snprintf(pLogMessage->szMessage, MAX_MESSAGE_LEN,
            "%d-%02d-%02d %02d:%02d:%02d.%03d\t[%c] ", 
            pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
            pNow->tm_hour, pNow->tm_min, pNow->tm_sec,
            pNow->tm_msec, cLevel);
    }

	vsnprintf(pLogMessage->szMessage + offset, MAX_MESSAGE_LEN - offset,
                  pcszMessage, valist);

	pLogMessage->nMessageSize = strnlen(pLogMessage->szMessage, MAX_MESSAGE_LEN) * sizeof(char);
	PROCESS_ERROR(pLogMessage->nMessageSize < MAX_MESSAGE_LEN);

	pLogMessage->szMessage[pLogMessage->nMessageSize++] = '\r';
	pLogMessage->szMessage[pLogMessage->nMessageSize++] = '\n';
	pLogMessage->szMessage[pLogMessage->nMessageSize] = 0;

	if (m_pLogThread)
	{
		if (s_dwThreadIndex == -1)
		{
            s_dwThreadIndex = InterlockedIncrement(&m_dwThreadCount) - 1;
		}
		if (s_dwThreadIndex >= MAX_LOG_THREAD_COUNT)
		{
			m_dwThreadCount = MAX_LOG_THREAD_COUNT;
			PROCESS_ERROR(s_dwThreadIndex < MAX_LOG_THREAD_COUNT);
		}

		nRetCode = m_LogList[s_dwThreadIndex].Push(pLogMessage);
		PROCESS_ERROR(nRetCode);
	}
	else
    {
        s_Mutex.Lock();

        if (m_eLogOutputMask & lotConsole)
			_Log2Console(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);
        if (m_eLogOutputMask & lotFile)
			_Log2File(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);
        if (m_eLogOutputMask & lotTrace)
			_Log2Trace(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);
        if (m_eLogOutputMask & lotCustom)
			_Log2Custom(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);

        s_Mutex.Unlock();
    }

    return TRUE;
Exit0:
	printf("Log write error!\n");
	if (pLogMessage && pLogMessage != &LogMessage)
        SAFE_DELETE(pLogMessage);

    return FALSE;
}

BOOL CLog::_Log2Console(INT32 nLevelIndex, const char* pcszMessage, INT32 nMessageSize)
{
#if defined(WIN32)
    if(nLevelIndex < 32)
        ::SetConsoleTextAttribute(m_hConsole, g_nLevelColor[nLevelIndex]);
#endif //WIN32

    printf(pcszMessage);

    return TRUE;
}

BOOL CLog::_Log2File(INT32 nLevelIndex, const char* pcszMessage, INT32 nMessageSize)
{
    INT32 nRetCode = 0;
    size_t uWriteSize;

    if (m_nCurrentSize >= LOG_BUFFER_SIZE)
    {
		if (m_pFile)
	        fclose(m_pFile);
        m_pFile = NULL;
        m_nCurrentSize = 0;
    }

    if (m_pFile == NULL)
    {
        const tm_ex* pNow = localtime_ex();
		snprintf(m_szCurrentFileFolder, sizeof(m_szCurrentFileFolder), "log/%04d_%02d_%02d", pNow->tm_year, pNow->tm_mon, pNow->tm_mday);

        g_CreateDirectory("log", TRUE);
		g_CreateDirectory(m_szCurrentFileFolder, TRUE);

		snprintf(m_szCurrentFilePath, sizeof(m_szCurrentFilePath), "log/%04d_%02d_%02d/%s_%d_%04d_%02d_%02d_%02d_%02d_%02d_%03d.log",
            pNow->tm_year, pNow->tm_mon, pNow->tm_mday, m_szModuleName, m_dwProcessID, pNow->tm_year, pNow->tm_mon, 
            pNow->tm_mday, pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec);
        m_pFile = fopen(m_szCurrentFilePath, "wb");
        if (m_pFile == NULL)
            printf("failed to create log file");
        PROCESS_ERROR(m_pFile);
    }

    uWriteSize = fwrite(pcszMessage, 1, nMessageSize, m_pFile);
    PROCESS_ERROR(uWriteSize == nMessageSize);

    if (m_bFlushFile)
        fflush(m_pFile);

    m_nCurrentSize += nMessageSize;
	m_dwLastUpdateCount++;

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CLog::_Log2Trace(INT32 nLevelIndex, const char* pcszMessage, INT32 nMessageSize)
{
#if defined(WIN32) | defined(WIN64)
    OutputDebugString(pcszMessage);
#endif  // WIN32

    return TRUE;
}

BOOL CLog::_Log2Custom(INT32 nLevelIndex, const char* pcszMessage, INT32 nMessageSize)
{
    if (m_pOutputFunc)
    {
#if defined(WIN32)
        if (nLevelIndex < 32)
            ::SetConsoleTextAttribute(m_hConsole, g_nLevelColor[nLevelIndex]);
#endif //WIN32
        m_pOutputFunc(nLevelIndex, pcszMessage, nMessageSize);
    }

    return TRUE;
}

void CLog::SetCustomOutput(CUSTOM_OUTPUT_FUNC pFunc)
{
    m_pOutputFunc = pFunc;
}

//#if defined(WIN32)
BOOL CLog::DbgLog(const char* pcszMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;

    va_start(valist, pcszMessage);
    nRetCode = _WriteLog(lltDebug, pcszMessage, valist);
    PROCESS_ERROR(nRetCode);
    va_end(valist);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLog::InfLog(const char* pcszMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;

    va_start(valist, pcszMessage);
    nRetCode = _WriteLog(lltInfo, pcszMessage, valist);
    PROCESS_ERROR(nRetCode);
    va_end(valist);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLog::WrnLog(const char* pcszMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;

    va_start(valist, pcszMessage);
    nRetCode = _WriteLog(lltWarning, pcszMessage, valist);
    PROCESS_ERROR(nRetCode);
    va_end(valist);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLog::ErrLog(const char* pcszMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;

    va_start(valist, pcszMessage);
    nRetCode = _WriteLog(lltError, pcszMessage, valist);
    PROCESS_ERROR(nRetCode);
    va_end(valist);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLog::CriLog(const char* pcszMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;

    va_start(valist, pcszMessage);
    nRetCode = _WriteLog(lltCritical, pcszMessage, valist);
    PROCESS_ERROR(nRetCode);
    va_end(valist);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLog::SplLog(const char* pcszMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;

    va_start(valist, pcszMessage);
    nRetCode = _WriteLog(lltSpell, pcszMessage, valist);
    PROCESS_ERROR(nRetCode);
    va_end(valist);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLog::SYSLogT(const char* pcszMessage, ...)
{
	INT32 nRetCode = 0;
	va_list valist;

	va_start(valist, pcszMessage);
	nRetCode = _WriteLog(lltSys, pcszMessage, valist);
	PROCESS_ERROR(nRetCode);
	va_end(valist);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CLog::SYSLogF(const char* pcszMessage, ...)
{
	INT32 nRetCode = 0;
	va_list valist;

	va_start(valist, pcszMessage);
	nRetCode = _WriteLog(lltSys, pcszMessage, valist);
	PROCESS_ERROR(nRetCode);
	va_end(valist);

	return TRUE;
Exit0:
	return FALSE;
}

THREAD_DECLARE(CLog::_LogThreadProc)(void* pParam)
{
	INT32 nRetCode = 0;
	CLog* pThis = (CLog*)pParam;
	BOOL bHasMessage = FALSE;

	while (!pThis->m_bStopThread || bHasMessage)
	{
		__try
		{
			bHasMessage = FALSE;
			for (INT32 nIndex = 0; nIndex < pThis->m_dwThreadCount; nIndex++)
			{
				if (pThis->m_LogList[nIndex].Check())
				{
                    LOG_MESSAGE* pLogMessage = (LOG_MESSAGE*)pThis->m_LogList[nIndex].Pop();
					PROCESS_ERROR(pLogMessage);

					if (pThis->m_eLogOutputMask & lotConsole)
						pThis->_Log2Console(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);
					if (pThis->m_eLogOutputMask & lotFile)
						pThis->_Log2File(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);
					if (pThis->m_eLogOutputMask & lotTrace)
						pThis->_Log2Trace(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);
					if (pThis->m_eLogOutputMask & lotCustom)
						pThis->_Log2Custom(pLogMessage->nLevelIndex, pLogMessage->szMessage, pLogMessage->nMessageSize);

					SAFE_DELETE(pLogMessage);

					bHasMessage = TRUE;

                    SAFE_DELETE(pLogMessage);
				}
			}

			if (!bHasMessage)
			{
				if (pThis->m_pFile && (pThis->m_dwLastUpdateCount != pThis->m_dwLastFlushCount))
				{
					nRetCode = fflush(pThis->m_pFile);
					LOG_CHECK_ERROR(nRetCode == 0);

					pThis->m_dwLastFlushCount = pThis->m_dwLastUpdateCount;
				}

				Sleep(16);
			}
		}
		__except (DumpExceptionFilter(GetExceptionInformation()))
		{
			goto Exit0;
		}
		continue;
	Exit0:
		printf("detected error in log thread");
	}

	return 0;
}

//#endif // WIN32
