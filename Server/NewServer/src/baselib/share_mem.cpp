#include "stdafx.h"
#include "share_mem.h"

#ifdef __linux__

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

MemPtr CreateSharedMemory(const char* szName, UINT64 qwSize)
{
	void* mem_ptr = NULL;
	BOOL is_new = FALSE;
	INT32 ret = 0;
	MemPtr ptr;
	ptr.pFd = NULL;
	ptr.pSharedMem = NULL;

    INT32 fd = -1;
	//INT32 fd = shm_open(szName, O_RDWR, 0);
    shm_unlink( szName );

	if(fd < 0)
	{
		is_new = TRUE;
		fd = shm_open(szName, O_RDWR | O_CREAT | O_EXCL, S_IRUSR|S_IWUSR|S_IXUSR);
        if ( fd > 0 )
        {
            ret = ftruncate( fd, qwSize );
            LOG_PROCESS_ERROR( ret == 0 );
        }
	}

	LOG_PROCESS_ERROR(fd);

	if(!is_new)
	{
		struct stat sb;
		ret = fstat(fd, &sb);
		LOG_PROCESS_ERROR(ret >= 0);

		if(qwSize < sb.st_size)
			qwSize = sb.st_size;
	}

	mem_ptr = mmap(NULL, qwSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	LOG_PROCESS_ERROR(mem_ptr != MAP_FAILED); 

    ptr.bIsNew = is_new;
	ptr.pSharedMem = (char *)mem_ptr;
	ptr.pFd = (void*)fd;
	ptr.qwSize = qwSize;
Exit0:
	return ptr;
}

void CloseSharedMemory(MemPtr& ptr)
{
	INT32 nRetCode = 0;

	nRetCode = munmap(ptr.pSharedMem, ptr.qwSize);
	LOG_PROCESS_ERROR(nRetCode >= 0);

	nRetCode = close( (unsigned long int)ptr.pFd );
	LOG_PROCESS_ERROR(nRetCode >= 0);

Exit0:
	return;
}

#else	// windows

#include <winternl.h>

BOOL CreateSharedMemory(const char* szName, UINT64 qwSize, MemPtr& RetPtr)
{
	HANDLE hMapFile = NULL;
	BOOL bIsNew = FALSE;
	void* pResult = NULL;

	RetPtr.pSharedMem = NULL;
	RetPtr.pFd = NULL;
	RetPtr.bIsNew = TRUE;

	ShareMemHeader* pHeader = NULL;

	qwSize += sizeof(ShareMemHeader);

	UINT32 dwSizeHi = (UINT32)(qwSize >> 32);
	UINT32 dwSizeLo = (UINT32)(qwSize & 0x00000000FFFFFFFF);

	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, dwSizeHi, dwSizeLo, szName);
	LOG_PROCESS_ERROR(hMapFile);

	if(GetLastError() == ERROR_ALREADY_EXISTS)
		RetPtr.bIsNew = FALSE;

	pResult = MapViewOfFile(hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	LOG_PROCESS_ERROR(pResult);

	pHeader = (ShareMemHeader*)pResult;
	
	if(pHeader->nTag != SHARED_MEM_HEAD_TAG)
	{
		pHeader->nTag = SHARED_MEM_HEAD_TAG;
		pHeader->qwSize = qwSize - sizeof(ShareMemHeader);
	}
	else
	{
		UINT64 qwFileSize = pHeader->qwSize + sizeof(ShareMemHeader);

		UnmapViewOfFile(pResult);

		pResult = MapViewOfFile(hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
		LOG_PROCESS_ERROR(pResult);

		pHeader = (ShareMemHeader*)pResult;
	}

	RetPtr.pSharedMem = (char*)pResult + sizeof(ShareMemHeader);
	RetPtr.pFd = hMapFile;
	RetPtr.qwSize = pHeader->qwSize;

	return TRUE;
Exit0:

	DWORD dwLastError = GetLastError();
	CRI("CreateSharedMemory Failed, SysError: %u", dwLastError);

	UnmapViewOfFile(pResult);

	if(hMapFile)
		CloseHandle(hMapFile);

	return FALSE;
}

BOOL OpenSharedMemory(const char* szName, MemPtr& RetPtr)
{
	HANDLE hMapFile = NULL;
	void* pResult = NULL;
	INT32 nRetCode = 0;
	UINT64 qwFileSize = 0;

	RetPtr.pSharedMem = NULL;
	RetPtr.pFd = NULL;
	RetPtr.bIsNew = FALSE;

	ShareMemHeader* pHeader = NULL;

	hMapFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, szName);
	PROCESS_ERROR(hMapFile);

	pResult = MapViewOfFile(hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	LOG_PROCESS_ERROR(pResult);

	pHeader = (ShareMemHeader*)pResult;
	LOG_PROCESS_ERROR(pHeader->nTag == SHARED_MEM_HEAD_TAG);
	qwFileSize = pHeader->qwSize + sizeof(ShareMemHeader);

	UnmapViewOfFile(pResult);

	pResult = MapViewOfFile(hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	LOG_PROCESS_ERROR(pResult);

	pHeader = (ShareMemHeader*)pResult;
	LOG_PROCESS_ERROR(pHeader->nTag == SHARED_MEM_HEAD_TAG);

	RetPtr.pSharedMem = (char*)pResult + sizeof(ShareMemHeader);
	RetPtr.pFd = hMapFile;
	RetPtr.qwSize = pHeader->qwSize;

	return TRUE;
Exit0:
	DWORD dwLastError = GetLastError();

	UnmapViewOfFile(pResult);

	if(hMapFile)
		CloseHandle(hMapFile);
	return FALSE;
}


void CloseSharedMemory(MemPtr& ptr)
{
	UnmapViewOfFile(ptr.pSharedMem - sizeof(ShareMemHeader));
	CloseHandle(ptr.pFd);

	ptr.pSharedMem = NULL;
	ptr.pFd = NULL;
}

typedef NTSTATUS (__stdcall *NT_QUERYOBJECT)(_In_opt_ HANDLE, _In_ ULONG, _Out_opt_ PVOID, _In_ ULONG, _Out_opt_ PULONG);

void QuerySharedMemory(MemPtr& ptr)
{
	HMODULE hDll = GetModuleHandle("ntdll.dll");


	NT_QUERYOBJECT NtQueryObject = (NT_QUERYOBJECT)GetProcAddress(hDll, "NtQueryObject");

	typedef struct _HANDLE_STATE
	{
		DWORD r1;
		DWORD GrantedAccess;
		DWORD HandleCount;
		DWORD RefCount;
		DWORD r5;
		DWORD r6;
		DWORD r7;
		DWORD r8;
		DWORD r9;
		DWORD r10;
		DWORD r11;
		DWORD r12;
		DWORD r13;
		DWORD r14;
	} HANDLE_STATE;

	HANDLE_STATE st;

	ULONG ulOut;

	DWORD dwRetCode = NtQueryObject(ptr.pSharedMem, 0, &st, 38, &ulOut);

}

BOOL IsShareMemoryExists(const char* szName)
{
	HANDLE hMapFile = NULL;

	hMapFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, szName);
	PROCESS_ERROR(hMapFile);

	CloseHandle(hMapFile);
	return TRUE;
Exit0:
	CloseHandle(hMapFile);
	return FALSE;
}

#endif


