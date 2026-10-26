#ifndef _PACKET_ALLOCATOR_H_
#define _PACKET_ALLOCATOR_H_

#include "net.h"
#include "base/free_object_pool.h"

#define LARGE_PACKET_SIZE       (64 * 1024)
#define SMALL_PACKET_SIZE       (1024)

class CPacketAllocator : public IPacketAllocator
{
public:
    virtual PACKET_BUFFER* Alloc(INT32 nSize);
//     virtual PACKET_BUFFER* AllocCopy(PACKET_BUFFER* pPacketBuffer);
    virtual void Free(PACKET_BUFFER* pPacketBuffer);

public:
    BOOL Init(INT32 nSmallPacketSize, INT32 nLargePacketSize);
    BOOL UnInit(void);

private:
    struct RESERVED_HEADER
    {
        UINT32  dwBufferSize;
        UINT32  dwState;
        INT32   nOffset;
        INT32   nNetSimpleUse;
        INT32   nReserved[2];
    };
    typedef BYTE                    SMALL_PACKET_BLOCK[sizeof(RESERVED_HEADER) + SMALL_PACKET_SIZE];
    typedef BYTE                    LARGE_PACKET_BLOCK[sizeof(RESERVED_HEADER) + LARGE_PACKET_SIZE];

    //CFreeObjectPool<SMALL_PACKET_BLOCK> m_SmallPacketPool;
    //CFreeObjectPool<LARGE_PACKET_BLOCK> m_LargePacketPool;
};

#endif  // _PACKET_ALLOCATOR_H_