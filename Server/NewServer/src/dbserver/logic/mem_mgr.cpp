#include "stdafx.h"
#include "mem_mgr.h"

CMemMgr::CMemMgr()
{
	memset(&m_memptr, 0, sizeof(m_memptr));
}

CMemMgr::~CMemMgr()
{

}

BOOL CMemMgr::Init(UINT32 dwMemCount)
{
	INT32 nRetCode = 0;

	nRetCode = CreateSharedMemory("role_data", (UINT64)MEM_SIZE * dwMemCount, m_memptr);
	LOG_PROCESS_ERROR(nRetCode);
	LOG_PROCESS_ERROR(m_memptr.pSharedMem);
	LOG_PROCESS_ERROR(m_memptr.bIsNew);

	nRetCode = m_FreeStack.Init();
	LOG_PROCESS_ERROR(nRetCode);

	for (UINT32 i = 0; i < dwMemCount; i++)
	{
		m_FreeStack.Push((STACK_NODE*)(m_memptr.pSharedMem + (UINT64)MEM_SIZE * i));
	}

	return TRUE;
Exit0:
	UnInit();

	return FALSE;
}

BOOL CMemMgr::UnInit()
{
	while (m_FreeStack.Pop())
		;

	if (m_memptr.pSharedMem)
		CloseSharedMemory(m_memptr);

	return TRUE;
}

void CMemMgr::Push(DB_ROLE_DATA* pData)
{
	LOG_PROCESS_ERROR(pData);

	m_FreeStack.Push(&pData->CtrlNode.StackNode);

Exit0:
	return;
}

DB_ROLE_DATA* CMemMgr::Pop()
{
	DB_ROLE_DATA* pDataNode = (DB_ROLE_DATA*)m_FreeStack.Pop();
	LOG_PROCESS_ERROR(pDataNode);

	return pDataNode;
Exit0:
	return NULL;
}
