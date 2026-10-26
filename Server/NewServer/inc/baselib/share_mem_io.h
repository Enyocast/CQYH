#ifndef _SHARE_MEM_IO_H_
#define _SHARE_MEM_IO_H_

#include "share_mem.h"

#define SHARED_MEM_TAG 0x6434ABCD

#pragma pack(push, 1)

struct MemHeader
{
	INT32 nMemTag;
	INT32 nBlockSize;
	INT32 nReadOffset;
	INT32 nWriteOffset;
};

#pragma pack(pop)

class CShareMemBuffer
{
public:
	CShareMemBuffer(void);
	~CShareMemBuffer(void);

	BOOL Create(const char* szName, INT32 nSize, INT32 nUserHeaderSize);

	BOOL Open(const char* szName);

	void Clear(void);

	void Destroy(void);

	BOOL Write(const char* pBuff, INT32 nSize);

	BOOL Read(char* pBuff, INT32 nSize);

	inline void* GetUserHeader(void);

	inline const char* GetData(void) const;

private:
	MemPtr m_Ptr;

	MemHeader* m_pHeader;
	char* m_pUserBlock;
	INT32 m_nBlockSize;
	INT32 m_nReadOffset;
	INT32 m_nWriteOffset;
	BOOL m_bEmpty;
	//INT32 m_nReadPtrCycle;
	//INT32 m_nWritePtrCycle;

	INT32 m_nLastVirtualReadPtr;
};

inline void* CShareMemBuffer::GetUserHeader(void)
{
	return m_Ptr.pSharedMem;
}

inline const char* CShareMemBuffer::GetData(void) const
{
	return m_pUserBlock;
}

#endif // _share_mem_io_h__
