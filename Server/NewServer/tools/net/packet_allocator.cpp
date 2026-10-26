#include "stdafx.h"
#include <string.h>
#include "packet_allocator.h"

#include <list>
#include <map>
#include "time_ex.h"

CPacketAllocator::CPacketAllocator()
{
    m_nSmallCount = m_nLargeCount = 0;
}

CPacketAllocator::~CPacketAllocator()
{
    UnInit();
}

BOOL CPacketAllocator::Init(INT32 nSmallPacketCount, INT32 nLargePacketCount)
{
    INT32 nRetCode = 0;

    nRetCode = m_SmallPacketPool.Init(nSmallPacketCount);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = m_LargePacketPool.Init(nLargePacketCount);
    LOG_PROCESS_ERROR(nRetCode);

    m_nSmallCount = m_nLargeCount = 0;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CPacketAllocator::UnInit(void)
{
    INT32 nRetCode = 0;

    nRetCode = m_SmallPacketPool.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = m_LargePacketPool.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

PACKET_BUFFER* CPacketAllocator::Alloc(INT32 nSize)
{
    PACKET_BUFFER* pResult = NULL;

    if (nSize > 0 && nSize <= SMALL_PACKET_SIZE)
    {
        RESERVED_HEADER* pHeader = (RESERVED_HEADER*)m_SmallPacketPool.New();
        LOG_PROCESS_ERROR(pHeader);

        pHeader->dwBufferSize = nSize;
        pHeader->dwState = 0x1234;
#if defined(_DEBUG)
		pHeader->qwAllocateTick = GetTickCountEx();
		pHeader->qwCallAddress = (UINT64)(*(void**)(&nSize - 4));
#endif  // _DEBUG

        pResult = (PACKET_BUFFER*)(pHeader + 1);
		_mm_prefetch(pResult, _MM_HINT_T0);
        m_nSmallCount++;
	}
    else if (nSize > SMALL_PACKET_SIZE && nSize <= LARGE_PACKET_SIZE)
    {
        RESERVED_HEADER* pHeader = (RESERVED_HEADER*)m_LargePacketPool.New();
        LOG_PROCESS_ERROR(pHeader);

		pHeader->dwBufferSize = nSize;
        pHeader->dwState = 0x1234;
#if defined(_DEBUG)
		pHeader->qwAllocateTick = GetTickCountEx();
		pHeader->qwCallAddress = (UINT64)(*(void**)(&nSize - 4));
#endif  // _DEBUG

        pResult = (PACKET_BUFFER*)(pHeader + 1);
		_mm_prefetch(pResult, _MM_HINT_T0);
		m_nLargeCount++;
    }
	else
	{
		LOG_PROCESS_ERROR(FALSE);
	}

#if defined(_DEBUG)
	*(UINT64*)(pResult + nSize) = 0x1234567890ABCDEF;
#endif	// _DEBUG

	return pResult;
Exit0:
    CRI("alloc package error at call address %p", (UINT64)(*(void**)(&nSize-4)));
	_PrintMsg();

    return NULL;
}

void CPacketAllocator::Free(PACKET_BUFFER* pPacketBuffer)
{
    INT32 nRetCode = 0;
    RESERVED_HEADER* pHeader = (RESERVED_HEADER*)pPacketBuffer;

    LOG_PROCESS_ERROR(pHeader);

    --pHeader;
    LOG_PROCESS_ERROR(pHeader->dwState == 0x1234);

#if defined(_DEBUG)
	LOG_CHECK_ERROR(*(UINT64*)(pPacketBuffer + pHeader->dwBufferSize) == 0x1234567890ABCDEF);
#endif	// _DEBUG

    if (pHeader->dwBufferSize <= SMALL_PACKET_SIZE)
    {
        pHeader->dwState = 0;

        nRetCode = m_SmallPacketPool.Delete((SMALL_PACKET_BLOCK*)pHeader);
        LOG_CHECK_ERROR(nRetCode);

        m_nSmallCount--;
    }
    else if (pHeader->dwBufferSize <= LARGE_PACKET_SIZE)
    {
        pHeader->dwState = 0;

        nRetCode = m_LargePacketPool.Delete((LARGE_PACKET_BLOCK*)pHeader);
        LOG_CHECK_ERROR(nRetCode);

        m_nLargeCount--;
    }
    else
    {
        LOG_CHECK_ERROR(FALSE);
    }

	return;
Exit0:
    CRI("free package error at call address %p", (UINT64)*((void**)(&pPacketBuffer - 2)));
    return;
}

BOOL CPacketAllocator::IsAllocated(PACKET_BUFFER* pPacketBuffer)
{
    RESERVED_HEADER* pHeader = (RESERVED_HEADER*)pPacketBuffer;

    LOG_PROCESS_ERROR(pHeader);

    --pHeader;
    PROCESS_ERROR(pHeader->dwState == 0x1234);

    return TRUE;
Exit0:
    return FALSE;
}

UINT32 CPacketAllocator::PrintMemoryStat(void)
{
	INF("packet allocator allocated %d small packet %.2fMB", m_nSmallCount, 
		m_SmallPacketPool.GetSize() * sizeof(SMALL_PACKET_BLOCK) / (1024 * 1024.0f));
	INF("packet allocator allocated %d small packet %.2fMB", m_nLargeCount, 
		m_LargePacketPool.GetSize() * sizeof(LARGE_PACKET_BLOCK) / (1024 * 1024.0f));

	return m_SmallPacketPool.GetSize()  * sizeof(SMALL_PACKET_BLOCK) + m_LargePacketPool.GetSize() * sizeof(LARGE_PACKET_BLOCK);
}

void CPacketAllocator::CheckError(void)
{
#if defined(_DEBUG)
	UINT64 qwCurrentTick = GetTickCountEx();

	char* pDataPool = (char*)m_SmallPacketPool.GetDataPool();
	if (pDataPool)
	{
		intptr_t dwDataSize = m_SmallPacketPool.GetDataSize();
		intptr_t dwDataOffset = m_SmallPacketPool.GetDataOffset();

		for (INT32 nIndex = 0; nIndex < m_SmallPacketPool.GetSize(); nIndex++)
		{
			UINT16* pMsgID = (UINT16*)(pDataPool + nIndex * dwDataSize + dwDataOffset + sizeof(RESERVED_HEADER));
			RESERVED_HEADER* pHeader = (RESERVED_HEADER*)(pDataPool + nIndex * dwDataSize + dwDataOffset);

			if (pHeader->dwState == 0x1234 && pHeader->qwAllocateTick < qwCurrentTick - 1000 * 8)
			{
				CRI("detected small packet leak, msg id %d, call address %llu", *pMsgID, pHeader->qwCallAddress);
			}
		}
	}

	pDataPool = (char*)m_LargePacketPool.GetDataPool();
	if (pDataPool)
	{
		UINT32 dwDataSize = m_LargePacketPool.GetDataSize();
		UINT32 dwDataOffset = (UINT32)m_LargePacketPool.GetDataOffset();

		for (INT32 nIndex = 0; nIndex < m_LargePacketPool.GetSize(); nIndex++)
		{
			UINT16* pMsgID = (UINT16*)(pDataPool + nIndex * dwDataSize + dwDataOffset + sizeof(RESERVED_HEADER));
			RESERVED_HEADER* pHeader = (RESERVED_HEADER*)(pDataPool + nIndex * dwDataSize + dwDataOffset);

			if (pHeader->dwState == 0x1234 && pHeader->qwAllocateTick < qwCurrentTick - 1000 * 8)
			{
				CRI("detected large packet leak, msg id %d, call address %llu", *pMsgID, pHeader->qwCallAddress);
			}
		}
	}
#endif	// _DEBUG

	return;
}

struct MSG_INFO
{
    MSG_INFO() 
    {
        dwCount = 0;
        bSmall = FALSE;
    }
    UINT32                      dwCount;
    BOOL                        bSmall;
    std::map<UINT64, UINT32>    AddressList;
};

void CPacketAllocator::_PrintMsg(void)
{
	std::map<UINT32, MSG_INFO> mapMsgInfo;

	char* pDataPool = (char*)m_SmallPacketPool.GetDataPool();
	if (pDataPool)
	{
		intptr_t dwDataSize = m_SmallPacketPool.GetDataSize();
		intptr_t dwDataOffset = m_SmallPacketPool.GetDataOffset();

		for (INT32 nIndex = 0; nIndex < m_SmallPacketPool.GetSize(); nIndex++)
		{
			UINT16* pMsgID = (UINT16*)(pDataPool + nIndex * dwDataSize + dwDataOffset + sizeof(RESERVED_HEADER));
            RESERVED_HEADER* pHeader = (RESERVED_HEADER*)(pDataPool + nIndex * dwDataSize + dwDataOffset);

            if (pHeader->dwState == 0x1234)
            {
                mapMsgInfo[*pMsgID].dwCount++;
                mapMsgInfo[*pMsgID].bSmall = TRUE;
                mapMsgInfo[*pMsgID].AddressList[pHeader->qwCallAddress]++;
            }
		}
	}

	pDataPool = (char*)m_LargePacketPool.GetDataPool();
	if (pDataPool)
	{
		UINT32 dwDataSize = m_LargePacketPool.GetDataSize();
		UINT32 dwDataOffset = (UINT32)m_LargePacketPool.GetDataOffset();

		for (INT32 nIndex = 0; nIndex < m_LargePacketPool.GetSize(); nIndex++)
		{
			UINT16* pMsgID = (UINT16*)(pDataPool + nIndex * dwDataSize + dwDataOffset + sizeof(RESERVED_HEADER));
            RESERVED_HEADER* pHeader = (RESERVED_HEADER*)(pDataPool + nIndex * dwDataSize + dwDataOffset);

            if (pHeader->dwState == 0x1234)
            {
                mapMsgInfo[*pMsgID].dwCount++;
                mapMsgInfo[*pMsgID].bSmall = FALSE;
                mapMsgInfo[*pMsgID].AddressList[pHeader->qwCallAddress]++;
            }
		}
	}

	for (std::map<UINT32, MSG_INFO>::iterator it = mapMsgInfo.begin();
		it != mapMsgInfo.end(); ++it)
	{
        if (it->second.bSmall)
    		CRI("small msg id %d count %d", it->first, it->second.dwCount);
        else
            CRI("large msg id %d count %d", it->first, it->second.dwCount);
        for (std::map<UINT64, UINT32>::iterator it2 = it->second.AddressList.begin();
            it2 != it->second.AddressList.end(); ++it2)
        {
            CRI("\tcall address %p : %d", it2->first, it2->second);
        }
	}

    CRI("current tick count : %I64d", GetTickCount());
    INT3();

	return;
}
