#ifndef _SHARE_MEM_H_
#define _SHARE_MEM_H_

#define SHARED_MEM_HEAD_TAG 0x1234FEDC

#pragma pack(push, 1)
struct ShareMemHeader
{
	INT32 nTag;
	UINT64 qwSize;
};
#pragma pack(pop)

struct MemPtr
{
	BOOL bIsNew;
	char* pSharedMem;
	void* pFd;
	UINT64 qwSize;
};

BOOL CreateSharedMemory(const char* szName, UINT64 qwSize, MemPtr& RetPtr);

BOOL OpenSharedMemory(const char* szName, MemPtr& RetPtr);

void CloseSharedMemory(MemPtr& ptr);

BOOL IsShareMemoryExists(const char* szName);

// for debug use only
void QuerySharedMemory(MemPtr& ptr);

#endif // _share_mem_h__


