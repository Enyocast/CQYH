#include "stdafx.h"
#include "iocp_mgr.h"

#define MAX_STREAM_RESULT_COUNT     (1024 * 1024 * 16)

CIocpMgr CIocpMgr::ms_Instance;
extern INT32 g_nStartIndex;
extern UINT32 g_dwMark;

extern BOOL _ReadFileData(IOCP_TASK* pTask);
extern void _ProcessFile(IOCP_TASK* pTask);

CIocpMgr::CIocpMgr()
{
	m_hIOCP = NULL;
	memset(m_ThreadList, 0, sizeof(m_ThreadList));
	m_nSubmitCount = m_nFetchCount = 0;
}

CIocpMgr::~CIocpMgr()
{
	UnInit();
}

BOOL CIocpMgr::Init(void)
{
	INT32 nRetCode = 0;
	DWORD dwThreadID = 0;

	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	LOG_PROCESS_ERROR(m_hIOCP);

	for (INT32 nIndex = 0; nIndex < IOCP_THREAD_COUNT; nIndex++)
	{
		m_ThreadList[nIndex] = CreateThread(NULL, 0, _IocpThreadFunc, (void*)nIndex, 0, &dwThreadID);
		LOG_PROCESS_ERROR(m_ThreadList[nIndex]);

		nRetCode = SetThreadPriority(m_ThreadList[nIndex], THREAD_PRIORITY_HIGHEST);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = m_ResultList[nIndex].Init(MAX_STREAM_RESULT_COUNT);
		LOG_PROCESS_ERROR(nRetCode);
	}

	m_nSubmitCount = m_nFetchCount = 0;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CIocpMgr::UnInit(void)
{

	return TRUE;
}

BOOL CIocpMgr::SubmitTask(IOCP_TASK* pTask)
{
	INT32 nRetCode = 0;

	pTask->dwSubmitTick = GetTickCount64();

	nRetCode = PostQueuedCompletionStatus(m_hIOCP, 0, NULL, pTask);
	LOG_PROCESS_ERROR(nRetCode);

	m_nSubmitCount++;

//	INF("submit %s", pTask->szFilePath);

	return TRUE;
Exit0:
	return FALSE;
}

IOCP_TASK* CIocpMgr::FetchResult(void)
{
	for (INT32 nIndex = 0; nIndex < IOCP_THREAD_COUNT; nIndex++)
	{
		if (!m_ResultList[nIndex].IsEmpty())
		{
			m_nFetchCount++;
			IOCP_TASK* pResult = (IOCP_TASK*)m_ResultList[nIndex].Pop();
			_ProcessFile(pResult);

			pResult->dwFetchTick = GetTickCount64();

			return pResult;
		}
	}
	return NULL;
}

INT32 CIocpMgr::GetUncompletedTaskCount(void)
{
	return m_nSubmitCount - m_nFetchCount;
}

DWORD WINAPI CIocpMgr::_IocpThreadFunc(void* pParam)
{
	INT32 nRetCode = 0;
	BOOL bOperateResult = FALSE;
	BOOL bStop = FALSE;
	INT32 nThreadIndex = (INT32)pParam;
	CIocpMgr* pThis = (CIocpMgr*)&CIocpMgr::GetInstance();

	while (!bStop)
	{
		DWORD* lpCompletionKey = NULL;
		DWORD dwIoSize = 0;
		IOCP_TASK* pTask = NULL;

		bOperateResult = GetQueuedCompletionStatus(pThis->m_hIOCP, &dwIoSize,
			(PULONG_PTR)&lpCompletionKey, (LPOVERLAPPED*)&pTask, INFINITE);
		if (!bOperateResult && pTask == NULL)
		{
			bStop = TRUE;
			continue;
		}

		if (pTask->hFile == INVALID_HANDLE_VALUE)
		{
			nRetCode = _ReadFileData(pTask);
			if (!nRetCode)
			{
				nRetCode = pThis->m_ResultList[nThreadIndex].Push(pTask);
				LOG_PROCESS_ERROR(nRetCode);
			}
		}
		else if (pTask->pFileData)
		{
			nRetCode = pThis->m_ResultList[nThreadIndex].Push(pTask);
			LOG_PROCESS_ERROR(nRetCode);
		}

		continue;
	Exit0:
		continue;
	}

	WRN("Iocp work thread quit");

	return 0;
}
