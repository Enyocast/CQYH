#ifndef _PACKET_ALLOCATOR_H_
#define _PACKET_ALLOCATOR_H_

#include "net.h"
#include "free_object_pool.h"

class CPacketAllocator : public IPacketAllocator
{
public:
    virtual PACKET_BUFFER* Alloc(INT32 nSize);
    virtual void Free(PACKET_BUFFER* pPacketBuffer);

    virtual BOOL IsAllocated(PACKET_BUFFER* pPacketBuffer);
	virtual UINT32 PrintMemoryStat(void);
	virtual void CheckError(void);

public:
    CPacketAllocator();
    virtual ~CPacketAllocator();

    BOOL Init(INT32 nSmallPacketCount, INT32 nLargePacketCount);
    BOOL UnInit(void);

private:
	void _PrintMsg(void);

private:
	struct RESERVED_HEADER
	{
		UINT32  dwBufferSize;
		UINT32  dwState;
		UINT64  qwCallAddress;
		UINT64	qwAllocateTick;
		char    Reserved[PACKET_OVERHEAD_SIZE];
	};
	typedef BYTE                    SMALL_PACKET_BLOCK[sizeof(RESERVED_HEADER) + SMALL_PACKET_SIZE + 8];
	typedef BYTE                    LARGE_PACKET_BLOCK[sizeof(RESERVED_HEADER) + LARGE_PACKET_SIZE + 8];

    CFreeObjectPool<SMALL_PACKET_BLOCK> m_SmallPacketPool;
    CFreeObjectPool<LARGE_PACKET_BLOCK> m_LargePacketPool;
    INT32                   m_nSmallCount;
    INT32                   m_nLargeCount;
};

#endif  // _PACKET_ALLOCATOR_H_