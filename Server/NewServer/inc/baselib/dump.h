#ifndef _DUMP_H_
#define _DUMP_H_

typedef BOOL (*DUMP_CHECK_FUNC)(void);

BOOL StartDumpThread(DUMP_CHECK_FUNC pDumpCheckFunc, BOOL bDumpHost, const char* pDumpFolder);
void SetDumpOption(BOOL bShowDumpDialog);
BOOL StopDumpThread(void);
void SetDumpFolder(const char* pDumpFolder);

BOOL CheckDiskRemainCapacity(void);

void TestDump(void);

#ifdef WIN32
    LONG WINAPI DumpExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionPointers);
#endif  // WIN32


#endif // _dump_h__
