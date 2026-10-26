#include "stdafx.h"
#include "packet_allocator.h"
#include "base/process_error.h"

BOOL CPacketAllocator::Init(INT32 nSmallPacketSize, INT32 nLargePacketSize)
{
//     INT32 nRetCode = 0;
// 
//     nRetCode = m_SmallPacketPool.Init(nSmallPacketSize);
//     LOG_PROCESS_ERROR(nRetCode);
// 
//     nRetCode = m_LargePacketPool.Init(nLargePacketSize);
//     LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
// Exit0:
//     return FALSE;
}

BOOL CPacketAllocator::UnInit(void)
{
//     INT32 nRetCode = 0;
// 
//     nRetCode = m_SmallPacketPool.UnInit();
//     LOG_CHECK_ERROR(nRetCode);
// 
//     nRetCode = m_LargePacketPool.UnInit();
//     LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}


PACKET_BUFFER* CPacketAllocator::Alloc(INT32 nSize)
{
//	DBG("Alloc : %d", nSize);
    PACKET_BUFFER* pResult = NULL;

    if (nSize > 0 && nSize <= SMALL_PACKET_SIZE)
    {
        RESERVED_HEADER* pHeader = (RESERVED_HEADER*)appMalloc(nSize + sizeof(RESERVED_HEADER));//(RESERVED_HEADER*)m_SmallPacketPool.New();
        LOG_PROCESS_ERROR(pHeader);
        memset(pHeader, 0, sizeof(RESERVED_HEADER));

        pHeader->dwBufferSize = SMALL_PACKET_SIZE;
        pHeader->dwState = 0x1234;
        pResult = (PACKET_BUFFER*)(pHeader + 1);
    }
    else if (nSize > SMALL_PACKET_SIZE && nSize <= LARGE_PACKET_SIZE)
    {
        RESERVED_HEADER* pHeader = (RESERVED_HEADER*)appMalloc(nSize + sizeof(RESERVED_HEADER));//(RESERVED_HEADER*)m_LargePacketPool.New();
        LOG_PROCESS_ERROR(pHeader);
        memset(pHeader, 0, sizeof(RESERVED_HEADER));

        pHeader->dwBufferSize = LARGE_PACKET_SIZE;
        pHeader->dwState = 0x1234;
        pResult = (PACKET_BUFFER*)(pHeader + 1);
    }

    //debugf( TEXT("[CPacketAllocator::Alloc] %x"), (void*)pResult);

    return pResult;

Exit0:
    return NULL;
}
// 
// PACKET_BUFFER* CPacketAllocator::AllocCopy(PACKET_BUFFER* pPacketBuffer)
// {
//     PACKET_BUFFER* pResult = NULL;
//     INT32 nSize = 0;
//     RESERVED_HEADER* pHeader = NULL;
//     RESERVED_HEADER* pNewHeader = NULL;
//     LOG_PROCESS_ERROR(pPacketBuffer);
//     
//     pHeader = (RESERVED_HEADER*)pPacketBuffer;
//     LOG_PROCESS_ERROR(pHeader);
//     --pHeader;
//     LOG_PROCESS_ERROR(pHeader->dwState == 0x1234);
//     nSize = pHeader->dwBufferSize;
// 
//     if (nSize > 0 && nSize <= SMALL_PACKET_SIZE)
//     {
//         pNewHeader = (RESERVED_HEADER*)m_SmallPacketPool.New();
//         LOG_PROCESS_ERROR(pNewHeader);
//     }
//     else if (nSize > SMALL_PACKET_SIZE && nSize <= LARGE_PACKET_SIZE)
//     {
//         pNewHeader = (RESERVED_HEADER*)m_LargePacketPool.New();
//         LOG_PROCESS_ERROR(pNewHeader);
//     }
//     memcpy(pNewHeader, pHeader, nSize);
//     pResult = (PACKET_BUFFER*)(pNewHeader + 1);
// 
//     return pResult;
// Exit0:
//     return NULL;
// }


void CPacketAllocator::Free(PACKET_BUFFER* pPacketBuffer)
{
    INT32 nRetCode = 0;
    RESERVED_HEADER* pHeader = (RESERVED_HEADER*)pPacketBuffer;

    LOG_PROCESS_ERROR(pHeader);

    --pHeader;
    LOG_PROCESS_ERROR(pHeader->dwState == 0x1234);

    //debugf( TEXT("[CPacketAllocator::Free] %x"), (void*)pPacketBuffer);

    if (pHeader->dwBufferSize == SMALL_PACKET_SIZE)
    {
        pHeader->dwState = 0;

        appFree((void*)pHeader);//m_SmallPacketPool.Delete((SMALL_PACKET_BLOCK*)pHeader);
        //LOG_CHECK_ERROR(nRetCode);
    }
    else if (pHeader->dwBufferSize == LARGE_PACKET_SIZE)
    {
        pHeader->dwState = 0;

        appFree((void*)pHeader);//m_LargePacketPool.Delete((LARGE_PACKET_BLOCK*)pHeader);
        //LOG_CHECK_ERROR(nRetCode);
    }
    else
    {
        LOG_CHECK_ERROR(FALSE);
    }

//	DBG("alloc: free : %u", pHeader->dwBufferSize);
	return;
Exit0:
    return;
}