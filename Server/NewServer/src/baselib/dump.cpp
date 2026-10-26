#include "stdafx.h"
#include "dump.h"
#include "time_ex.h"
#include "share_mem.h"
#include "dir.h"
#include "report.h"
#include <eh.h>

#define DUMP_INTERVAL           (3000 * 1000)
#define MAX_WAIT_DUMP_TIME      (100)
#define DUMP_MEMORY_NAME        "DumpShareMemory"
#define MAX_DUMP_PROCESS_COUNT  (64)
#define DUMP_SHARE_MEMORY_TAG   'dump'
#define CHECK_PROCESS_INTERVAL  (8 * 1000)

#ifdef __linux__

#endif  // __linux__

#ifdef WIN32

#include <psapi.h>
#include <DbgHelp.h>

struct DUMP_SHARE_MEMORY
{
    UINT32          dwTag;
    struct PROCESS_DATA
    {
        volatile BOOL bUsed;
        struct _EXCEPTION_POINTERS* pExceptionPointers;
        UINT32  dwProcessID;
        UINT32  dwThreadID;
        BOOL    bDump;
        UINT64  qwLastDumpTick;
		UINT64	qwLastCheckAliveTick;
    }       ProcessList[MAX_DUMP_PROCESS_COUNT];
};

static HANDLE s_hDumpThread = NULL;
static BOOL s_bStopDumpThread = FALSE;
static DUMP_CHECK_FUNC s_pDumpCheckFunc = NULL;
static BOOL s_bDumpHost = FALSE;
static char s_szDumpFolder[256] = {0};
static BOOL s_bShowExceptionDialog = FALSE;
static DUMP_SHARE_MEMORY* s_pDumpShareMemory = NULL;
static BOOL s_bLocalDump = FALSE;
static struct _EXCEPTION_POINTERS* s_pExceptionPointers = NULL;
static INT32 s_nProcessIndex = 0;

void CreateDumpFile(struct _EXCEPTION_POINTERS* pExceptionPointers, UINT32 dwProcessID, UINT32 dwThreadID)
{
    INT32 nRetCode = 0;
    char szFileName[MAX_PATH] = { 0 };
    char szModuleName[MAX_PATH] = {0};
	char szWorkingDir[MAX_PATH] = { 0 };
    char* pszModuleName = NULL;

    DWORD dwBufferSize = MAX_PATH;
    HANDLE hDumpFile = INVALID_HANDLE_VALUE;
    HANDLE hProcess = NULL;
	BOOL bSmallDump = FALSE;

    SYSTEMTIME stLocalTime;
    MINIDUMP_EXCEPTION_INFORMATION ExParam;
    GetLocalTime(&stLocalTime);

	GetCurrentDirectory(MAX_PATH, szWorkingDir);

#if defined (_FINAL)
	GetDiskFreeSpaceEx(szWorkingDir, &FreeBytes, NULL, NULL);
	PROCESS_ERROR(FreeBytes.QuadPart > 1024LL * 1024 * 1024 * 16);
	if (FreeBytes.QuadPart < 1024LL * 1024 * 1024 * 32)
		bSmallDump = TRUE;
#endif // _FINAL

	LOG_PROCESS_ERROR(s_szDumpFolder[0] != '\0');
    g_CreateDirectory(s_szDumpFolder, TRUE);

    snprintf(szFileName, MAX_PATH, "%s/%04d_%02d_%02d", 
		s_szDumpFolder,
        stLocalTime.wYear, 
        stLocalTime.wMonth, 
        stLocalTime.wDay);
    g_CreateDirectory(szFileName, TRUE);

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwProcessID);
    if (hProcess == NULL)
        goto Exit0;

    GetProcessImageFileName(hProcess, szModuleName, MAX_PATH);
    pszModuleName = szModuleName + strlen(szModuleName);
    while (*pszModuleName != '.' && pszModuleName > szModuleName)
        pszModuleName--;
    if (*pszModuleName == '.')
    {
        *pszModuleName = 0;
        while (*pszModuleName != '\\' && pszModuleName > szModuleName)
            pszModuleName--;
        pszModuleName++;
    }

    snprintf(szFileName, MAX_PATH, "%s/%04d_%02d_%02d/%s_%d_%04d_%02d_%02d_%02d_%02d_%02d_%03d.dmp", 
		s_szDumpFolder,
        stLocalTime.wYear, 
        stLocalTime.wMonth, 
        stLocalTime.wDay, 
        pszModuleName, 
		dwProcessID,
        stLocalTime.wYear, 
        stLocalTime.wMonth, 
        stLocalTime.wDay, 
        stLocalTime.wHour, 
        stLocalTime.wMinute, 
        stLocalTime.wSecond, 
        stLocalTime.wMilliseconds);

    hDumpFile = CreateFile(szFileName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
    if (hDumpFile == INVALID_HANDLE_VALUE)
        goto Exit0;

    ExParam.ThreadId = dwThreadID;
    ExParam.ExceptionPointers = pExceptionPointers;
    ExParam.ClientPointers = TRUE;

    if (pExceptionPointers == NULL || bSmallDump)
    {
        nRetCode = MiniDumpWriteDump(hProcess, dwProcessID, hDumpFile, 
            (MINIDUMP_TYPE)(MiniDumpNormal | MiniDumpWithThreadInfo), NULL, NULL, NULL);
        if (!nRetCode)
            goto Exit0;
    }
    else
    {
        nRetCode = MiniDumpWriteDump(hProcess, dwProcessID, hDumpFile, 
            (MINIDUMP_TYPE)(MiniDumpNormal | MiniDumpWithDataSegs | MiniDumpWithFullMemory | MiniDumpWithThreadInfo), &ExParam, NULL, NULL);
        if (!nRetCode)
            goto Exit0;

		REPORT(1, "dump file %s for process %d thread %d", szFileName, dwProcessID, dwThreadID);
    }

Exit0:
    if (hDumpFile != INVALID_HANDLE_VALUE)
        CloseHandle(hDumpFile);

    if (hProcess != NULL)
        CloseHandle(hProcess);

    return;
}

DWORD WINAPI DumpThreadProc(void* pParam)
{
	INT32 nRetCode = 0;
	UINT64 qwLastCheckTick = 0;
	MemPtr mp = { 0 };

    if (s_bDumpHost)
    {
        nRetCode = CreateSharedMemory(DUMP_MEMORY_NAME, sizeof(DUMP_SHARE_MEMORY), mp);
        LOG_PROCESS_ERROR(nRetCode);

        s_pDumpShareMemory = (DUMP_SHARE_MEMORY*)mp.pSharedMem;
        memset(s_pDumpShareMemory, 0, sizeof(DUMP_SHARE_MEMORY));

        s_pDumpShareMemory->ProcessList[0].bUsed = TRUE;
        s_pDumpShareMemory->ProcessList[0].dwProcessID = GetCurrentProcessId();

        s_pDumpShareMemory->dwTag = DUMP_SHARE_MEMORY_TAG;
    }

    while (!s_bStopDumpThread)
    {
        if (s_bDumpHost)
        {
            for (INT32 nIndex = 0; nIndex < MAX_DUMP_PROCESS_COUNT; nIndex++)
            {
                if (!s_pDumpShareMemory->ProcessList[nIndex].bUsed)
                    continue;

                UINT64 qwCurrentTick = GetTickCountEx();

                if (s_pDumpShareMemory->ProcessList[nIndex].bDump)
                {
                    if (qwCurrentTick - s_pDumpShareMemory->ProcessList[nIndex].qwLastDumpTick > DUMP_INTERVAL ||
                        s_pDumpShareMemory->ProcessList[nIndex].pExceptionPointers == NULL)
                    {
                        CreateDumpFile(s_pDumpShareMemory->ProcessList[nIndex].pExceptionPointers,
                            s_pDumpShareMemory->ProcessList[nIndex].dwProcessID,
                            s_pDumpShareMemory->ProcessList[nIndex].dwThreadID);
                        s_pDumpShareMemory->ProcessList[nIndex].qwLastDumpTick = qwCurrentTick;
						INF("created dump for process %d", s_pDumpShareMemory->ProcessList[nIndex].dwProcessID);
                    }
                    s_pDumpShareMemory->ProcessList[nIndex].bDump = FALSE;
                }

				if (qwCurrentTick - s_pDumpShareMemory->ProcessList[nIndex].qwLastCheckAliveTick > CHECK_PROCESS_INTERVAL)
                {
                    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, s_pDumpShareMemory->ProcessList[nIndex].dwProcessID);
                    if (hProcess == NULL)
                    {
                        s_pDumpShareMemory->ProcessList[nIndex].bUsed = FALSE;
                    }
                    else
                    {
                        CloseHandle(hProcess);
                    }
					s_pDumpShareMemory->ProcessList[nIndex].qwLastCheckAliveTick = qwCurrentTick;
                }
            }
        }
        else
        {
            UINT64 qwCurrentTick = GetTickCountEx();

            if ((s_pDumpShareMemory == NULL || !s_pDumpShareMemory->ProcessList[s_nProcessIndex].bUsed) && qwCurrentTick - qwLastCheckTick > CHECK_PROCESS_INTERVAL)
            {
				if (mp.pSharedMem)
					CloseSharedMemory(mp);

                nRetCode = OpenSharedMemory(DUMP_MEMORY_NAME, mp);
                if (mp.pSharedMem && ((DUMP_SHARE_MEMORY*)mp.pSharedMem)->dwTag == DUMP_SHARE_MEMORY_TAG)
                {
                    s_pDumpShareMemory = (DUMP_SHARE_MEMORY*)mp.pSharedMem;

                    for (INT32 nIndex = 0; nIndex < MAX_DUMP_PROCESS_COUNT; nIndex++)
                    {
                        if (!s_pDumpShareMemory->ProcessList[nIndex].bUsed)
                        {
                            nRetCode = InterlockedCompareExchange((volatile long*)&s_pDumpShareMemory->ProcessList[nIndex].bUsed, TRUE, FALSE);
                            if (nRetCode == FALSE)
                            {
                                s_nProcessIndex = nIndex;
                                break;
                            }
                        }
                    }
                    LOG_PROCESS_ERROR(s_nProcessIndex < MAX_DUMP_PROCESS_COUNT);
                }
                qwLastCheckTick = qwCurrentTick;
            }

            if (s_bLocalDump)
            {
                CreateDumpFile(s_pExceptionPointers, GetCurrentProcessId(), GetCurrentThreadId());
                s_bLocalDump = FALSE;
            }

            if (s_pDumpCheckFunc && s_pDumpCheckFunc())
            {
                INT32 nWaitTimer = 0;

                if (s_pDumpShareMemory && s_pDumpShareMemory->dwTag)
                {
                    s_pDumpShareMemory->ProcessList[s_nProcessIndex].pExceptionPointers = NULL;
                    s_pDumpShareMemory->ProcessList[s_nProcessIndex].dwProcessID = GetCurrentProcessId();
                    s_pDumpShareMemory->ProcessList[s_nProcessIndex].dwThreadID = GetCurrentThreadId();
                    s_pDumpShareMemory->ProcessList[s_nProcessIndex].bDump = TRUE;

                    while (s_pDumpShareMemory->ProcessList[s_nProcessIndex].bDump && nWaitTimer < MAX_WAIT_DUMP_TIME)
                    {
                        nWaitTimer++;
                        Sleep(50);
                    }
                }
				else
				{
					CreateDumpFile(NULL, GetCurrentProcessId(), GetCurrentThreadId());
				}
            }
        }

        Sleep(16);
    }

Exit0:
    return 0;
}

LONG WINAPI DumpExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionPointers)
{
    INT32 nWaitTimer = 0;

    if (s_pDumpShareMemory && s_pDumpShareMemory->dwTag)
    {
        s_pDumpShareMemory->ProcessList[s_nProcessIndex].pExceptionPointers = pExceptionPointers;
        s_pDumpShareMemory->ProcessList[s_nProcessIndex].dwProcessID = GetCurrentProcessId();
        s_pDumpShareMemory->ProcessList[s_nProcessIndex].dwThreadID = GetCurrentThreadId();
        s_pDumpShareMemory->ProcessList[s_nProcessIndex].bDump = TRUE;

        while (s_pDumpShareMemory->ProcessList[s_nProcessIndex].bDump && nWaitTimer < MAX_WAIT_DUMP_TIME)
        {
            nWaitTimer++;
            Sleep(50);
        }
    }
    else
    {
        s_pExceptionPointers = pExceptionPointers;
        s_bLocalDump = TRUE;
        while (s_bLocalDump && nWaitTimer < MAX_WAIT_DUMP_TIME)
        {
            nWaitTimer++;
            Sleep(50);
        }
    }

    CRI("exception code %08X, address %p", 
        pExceptionPointers->ExceptionRecord->ExceptionCode, pExceptionPointers->ExceptionRecord->ExceptionAddress);

    if (!IsDebuggerPresent() && s_bShowExceptionDialog)
    {
        MessageBox(NULL, "exception detected", NULL, 0);
    }

    if (IsDebuggerPresent())
    {
        INT3();
    }

    return EXCEPTION_EXECUTE_HANDLER;
}

#if defined(WIN32) | defined (WIN64)

void DisableSetUnhandledExceptionFilter(void)
{
    HMODULE hModule = NULL;

    hModule = LoadLibrary("kernel32.dll");
    LOG_PROCESS_ERROR(hModule);

    void *addr = (void*)GetProcAddress(hModule, "SetUnhandledExceptionFilter");
    LOG_PROCESS_ERROR(addr);

    unsigned char code[16];
    int size = 0;
	code[size++] = 0x33;
	code[size++] = 0xC0;
	code[size++] = 0xC2;
#if defined(WIN64)
    code[size++] = 0x00;
#else
	code[size++] = 0x04;
#endif	// WIN64
    code[size++] = 0x00;

    DWORD dwOldFlag, dwTempFlag;
    VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
    WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
    VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);

Exit0:
    if (hModule)
        FreeLibrary(hModule);

    return;
}

#pragma optimize("", off)

typedef DWORD(*THREAD_PROC)(void* pUserData);
static THREAD_PROC s_pThreadProcList[1024] = { 0 };
static void* s_pThreadUserDataList[1024] = { 0 };
static INT32 s_nThreadCount = 0;

DWORD WINAPI SafeThreadProc(void* pUserData)
{
	DWORD dwResult = 0;
	INT32 nThreadIndex = (INT32)pUserData;

	LOG_PROCESS_ERROR(nThreadIndex >= 0 && nThreadIndex < s_nThreadCount);
	LOG_PROCESS_ERROR(s_pThreadProcList[nThreadIndex] != NULL);

	INF("start safe thread %d", nThreadIndex);

	__try
	{
		dwResult = s_pThreadProcList[nThreadIndex](s_pThreadUserDataList[nThreadIndex]);
	}
	__except (DumpExceptionFilter(GetExceptionInformation()))
	{
		CRI("exception in thread %d", nThreadIndex);
	}

Exit0:

	return dwResult;
}

extern "C" void _ReplaceThreadProc(int a, int b, void* pThreadFunc, void* pUserData);

INT32 ReplaceThreadProc(int a, int b, void* pThreadFunc, void* pUserData)
{
	s_pThreadProcList[s_nThreadCount] = (THREAD_PROC)pThreadFunc;
	s_pThreadUserDataList[s_nThreadCount] = pUserData;

	_ReplaceThreadProc(0, 0, SafeThreadProc, (void*)s_nThreadCount);

	s_nThreadCount++;
	return s_nThreadCount - 1;
}

#pragma optimize("", on)

void HookCreateThread(void)
{
	HMODULE hModule = NULL;
	DWORD dwOldFlag, dwTempFlag;
	INT32 nEntryOffset = 0x152;
	INT32 nOffset1, nOffset2, nOffset3;

	hModule = LoadLibrary("kernel32.dll");
	LOG_PROCESS_ERROR(hModule);

	unsigned char *addr = (unsigned char*)GetProcAddress(hModule, "CreateThread") - nEntryOffset;
	LOG_PROCESS_ERROR(addr);

	VirtualProtect(addr, nEntryOffset + 4, PAGE_READWRITE, &dwOldFlag);

	if (*(UINT32*)(addr + nEntryOffset) == 0x48EC8348)
	{
		nOffset1 = 0x62;
		nOffset2 = 0xE0;
		nOffset3 = 0x148;

		LOG_PROCESS_ERROR(*(UINT64*)(addr + nOffset1) == 0x9090909090909090);
		LOG_PROCESS_ERROR(*(UINT64*)(addr + nOffset2) == 0x9090909090909090);
		LOG_PROCESS_ERROR(*(UINT64*)(addr + nOffset2 + 8) == 0x9090909090909090);

		*(UINT64*)(addr + nOffset1) = (UINT64)&ReplaceThreadProc;

		addr[nOffset2++] = 0x48;
		addr[nOffset2++] = 0x83;
		addr[nOffset2++] = 0xEC;
		addr[nOffset2++] = 0x48;
		addr[nOffset2++] = 0xE8;
		addr[nOffset2++] = 0x5F;
		addr[nOffset2++] = 0x00;
		addr[nOffset2++] = 0x00;
		addr[nOffset2++] = 0x00;
		addr[nOffset2++] = 0xEB;
		addr[nOffset2++] = (nEntryOffset + 4) - (nOffset2 + 1);

		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0x25;
		addr[nOffset3++] = 0x14;
		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0xEB;
		addr[nOffset3++] = 0x8C;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0x90;
	}
	else if (*(UINT32*)(addr + nEntryOffset) == 0x48DC8B4C)
	{
		nOffset1 = 0x62;
		nOffset2 = 0xE0;
		nOffset3 = 0x148;

		LOG_PROCESS_ERROR(*(UINT64*)(addr + nOffset1) == 0x9090909090909090);
		LOG_PROCESS_ERROR(*(UINT64*)(addr + nOffset2) == 0x9090909090909090);
		LOG_PROCESS_ERROR(*(UINT64*)(addr + nOffset2 + 8) == 0x9090909090909090);

		*(UINT64*)(addr + nOffset1) = (UINT64)&ReplaceThreadProc;

		addr[nOffset2++] = 0x8B;
		addr[nOffset2++] = 0xDC;
		addr[nOffset2++] = 0x48;
		addr[nOffset2++] = 0x90;
		addr[nOffset2++] = 0xE8;
		addr[nOffset2++] = 0x5F;
		addr[nOffset2++] = 0x00;
		addr[nOffset2++] = 0x00;
		addr[nOffset2++] = 0x00;
		addr[nOffset2++] = 0xEB;
		addr[nOffset2++] = 0x6B;

		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0x25;
		addr[nOffset3++] = 0x14;
		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0xFF;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0x90;
		addr[nOffset3++] = 0xEB;
		addr[nOffset3++] = 0x8C;
		addr[nOffset3++] = 0x90;
	}
	else
	{
		LOG_PROCESS_ERROR(FALSE);
	}

	VirtualProtect(addr, nEntryOffset + 4, dwOldFlag, &dwTempFlag);

Exit0:
	if (hModule)
		FreeLibrary(hModule);

	return;
}
#endif	// WIN32 | WIN64

void _crt_handler(void)
{
	INT3();
}

void _invalid_param_handler(const wchar_t* pcszExpression, const wchar_t* pcszFunction,
	const wchar_t* pcszFile, unsigned int dwLine, uintptr_t reserved)
{
	INT3();
}

int __cdecl MyReportHook(int, char* pszMessage, int *)
{
	INT3();
	return 0;
}

BOOL StartDumpThread(DUMP_CHECK_FUNC pDumpCheckFunc, BOOL bDumpHost, const char* pDumpFolder)
{
    DWORD dwThreadID;
	char szWorkingDir[MAX_PATH] = { 0 };
	ULARGE_INTEGER FreeBytes;

    s_bStopDumpThread = FALSE;

#if defined(WIN32) | defined (WIN64)
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	SetUnhandledExceptionFilter(DumpExceptionFilter);
	//DisableSetUnhandledExceptionFilter();
	_set_purecall_handler(_crt_handler);
	set_terminate(_crt_handler);
	set_unexpected(_crt_handler);
	_set_invalid_parameter_handler(_invalid_param_handler);
	//HookCreateThread();
	timeBeginPeriod(1);
#endif	// WIN32 | WIN64

#if defined (_FINAL)
	GetCurrentDirectory(MAX_PATH, szWorkingDir);
	GetDiskFreeSpaceEx(szWorkingDir, &FreeBytes, NULL, NULL);
	LOG_PROCESS_ERROR(FreeBytes.QuadPart > 1024LL * 1024 * 1024 * 36);
#endif // _FINAL

#if defined(_DEBUG)
//	_CrtSetReportHook(MyReportHook);
#endif // _DEBUG

    s_bDumpHost = bDumpHost;
	strxcpy(s_szDumpFolder, pDumpFolder, sizeof(s_szDumpFolder) );
    s_pDumpCheckFunc = pDumpCheckFunc;

    s_hDumpThread = CreateThread(NULL, 0, DumpThreadProc, NULL, 0, &dwThreadID);
    PROCESS_ERROR(s_hDumpThread);

    return TRUE;
Exit0:
    StopDumpThread();

    return FALSE;
}

void SetDumpOption(BOOL bShowDumpDialog)
{
    s_bShowExceptionDialog = bShowDumpDialog;
}

void SetDumpFolder(const char* pDumpFolder)
{
	strxcpy(s_szDumpFolder, pDumpFolder, sizeof(s_szDumpFolder));
}

BOOL StopDumpThread(void)
{
    if (s_hDumpThread)
    {
        s_bStopDumpThread = TRUE;
        WaitForSingleObject(s_hDumpThread, INFINITE);
        CloseHandle(s_hDumpThread);
    }
#if defined(WIN32) | defined (WIN64)
	timeEndPeriod(1);
#endif	// WIN32 | WIN64

    return TRUE;
}

BOOL CheckDiskRemainCapacity(void)
{
#ifdef _FINAL
	char szWorkingDir[MAX_PATH] = { 0 };
	ULARGE_INTEGER FreeBytes;
	GetCurrentDirectory(MAX_PATH, szWorkingDir);
	GetDiskFreeSpaceEx(szWorkingDir, &FreeBytes, NULL, NULL);
	LOG_PROCESS_ERROR(FreeBytes.QuadPart < 32LL * 1024 * 1024 * 1024);
#endif	// _FINAL

	return TRUE;
Exit0:
	return FALSE;
}

#endif  // WIN32

void TestDump(void)
{
	{
		int i = 0;
		int j = j / i;
	}

	{
		class _CBase
		{
		public:
			_CBase(_CBase* pDerived) { m_pDerived = pDerived; }
			~_CBase() { m_pDerived->func(); }
			virtual void func(void) = 0;

		protected:
			_CBase* m_pDerived;
		};

		class _CDerived : public _CBase
		{
		public:
			_CDerived() : _CBase(this) {}
			virtual void func(void) {}
		};

		_CDerived();
	}

}
