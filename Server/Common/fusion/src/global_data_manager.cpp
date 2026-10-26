#include "stdafx.h"
#include "global_data_manager.h"

#include "data_manager.h"

#define MAX_LOAD_DATA_COUNT     (1024)

CGlobalDataManager CGlobalDataManager::ms_Instance;

struct FAKE_DATA
{
	INT32 nData;
    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, FAKE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
    {
        return FALSE;
    }
};

CGlobalDataManager::CGlobalDataManager()
{
    m_bStop = FALSE;
}

CGlobalDataManager::~CGlobalDataManager()
{
    UnInit();
}

BOOL CGlobalDataManager::Init(void)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(m_LoadDataList.empty());
    LOG_PROCESS_ERROR(m_LoadDataMap.empty());

    nRetCode = m_LoadingList.Init(MAX_LOAD_DATA_COUNT);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = m_LoadedList.Init(MAX_LOAD_DATA_COUNT);
    LOG_PROCESS_ERROR(nRetCode);

    m_bStop = FALSE;

    nRetCode = m_LoadThread.Start(CGlobalDataManager::_LoadThread, this);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CGlobalDataManager::UnInit(void)
{
    m_bStop = TRUE;
    m_LoadThread.Wait();

    m_LoadDataList.clear();
    m_LoadDataMap.clear();

    m_LoadingList.UnInit();
    m_LoadedList.UnInit();

    return TRUE;
}

BOOL CGlobalDataManager::MainLoop(void)
{
    INT32 nRetCode = 0;

    if (!m_LoadedList.IsEmpty())
    {
        LOAD_TASK* pLoadTask = (LOAD_TASK*)m_LoadedList.Pop();
        LOG_PROCESS_ERROR(pLoadTask);

        switch (pLoadTask->nTaskType)
        {
        case lttLoadData:
            _LoadedData(pLoadTask);
			m_nLoadedCount++;
            break;
        case lttLoadScript:
            break;
        case lttLoadAI:
            break;
        default:
            break;
        }
    }

	if (m_nLoadedCount == m_LoadDataMap.size())
	{
		PostProcessAllData();
		m_nLoadedCount = 0;
	}

    return TRUE;
Exit0:

    return FALSE;
}

CGlobalDataManager& CGlobalDataManager::GetInstance(void)
{
    return ms_Instance;
}

BOOL CGlobalDataManager::AddDataManager(const char* pcszConfigName, void* pDataManager)
{
    LOG_PROCESS_ERROR(pcszConfigName);
    LOG_PROCESS_ERROR(pDataManager);

    m_LoadDataList.push_back(pcszConfigName);
    m_LoadDataMap[pcszConfigName] = pDataManager;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGlobalDataManager::ReloadAllData(BOOL bThread)
{
    std::map<std::string, void*>::iterator itDataManager;
    CDataManager<FAKE_DATA>* pDataManager = NULL;

	m_nLoadedCount = 0;

    for (std::list<std::string>::iterator it = m_LoadDataList.begin();
        it != m_LoadDataList.end(); ++it)
    {
        itDataManager = m_LoadDataMap.find(it->c_str());
        LOG_CHECK_ERROR(itDataManager != m_LoadDataMap.end());

        if (itDataManager != m_LoadDataMap.end())
        {
            pDataManager = (CDataManager<FAKE_DATA>*)itDataManager->second;
            LOG_CHECK_ERROR(pDataManager);

            if (pDataManager)
                pDataManager->Reload(bThread, FALSE);
        }
    }

	if (!bThread)
		PostProcessAllData();

    return TRUE;
}

BOOL CGlobalDataManager::PostProcessAllData(void)
{
	std::map<std::string, void*>::iterator itDataManager;
	CDataManager<FAKE_DATA>* pDataManager = NULL;

	for (std::list<std::string>::iterator it = m_LoadDataList.begin();
		it != m_LoadDataList.end(); ++it)
	{
		itDataManager = m_LoadDataMap.find(it->c_str());
		LOG_CHECK_ERROR(itDataManager != m_LoadDataMap.end());

		if (itDataManager != m_LoadDataMap.end())
		{
			pDataManager = (CDataManager<FAKE_DATA>*)itDataManager->second;
			LOG_CHECK_ERROR(pDataManager);

			if (pDataManager)
				pDataManager->PostProcessData();
		}
	}

	return TRUE;
}

BOOL CGlobalDataManager::PushTask(LOAD_TASK* pLoadTask)
{
    INT32 nRetCode = 0;

    nRetCode = m_LoadingList.Push(pLoadTask);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

THREAD_DECLARE(CGlobalDataManager::_LoadThread)(void* pParam)
{
    INT32 nRetCode = 0;
    CGlobalDataManager* pThis = NULL;
    LOAD_TASK* pLoadTask = NULL;

    pThis = (CGlobalDataManager*)pParam;
    LOG_PROCESS_ERROR(pThis);

    while (!pThis->m_bStop)
    {
        if (!pThis->m_LoadingList.IsEmpty())
        {
            pLoadTask = (LOAD_TASK*)pThis->m_LoadingList.Pop();
            LOG_PROCESS_ERROR(pLoadTask);

            switch (pLoadTask->nTaskType)
            {
            case lttLoadData:
                pThis->_LoadingData(pLoadTask);
                break;
            case lttLoadScript:
                break;
            case lttLoadAI:
                break;
            default:
                break;
            }
        }
        else
        {
Exit0:
            Sleep(16);
        }
    }

    return 0;
}

void CGlobalDataManager::_LoadingData(LOAD_TASK* pLoadTask)
{
    INT32 nRetCode = 0;
    LOADED_DATA_LIST* pLoadedDataList = NULL;
    std::map<std::string, void*>::iterator it;
    CDataManager<FAKE_DATA>* pDataManager = NULL;

    pLoadedDataList = (LOADED_DATA_LIST*)pLoadTask->pTaskData;

    it = m_LoadDataMap.find(pLoadedDataList->szConfigName);
    LOG_PROCESS_ERROR(it != m_LoadDataMap.end());

    pDataManager = (CDataManager<FAKE_DATA>*)it->second;
    LOG_PROCESS_ERROR(pDataManager);

    nRetCode = pDataManager->_Load(pLoadedDataList);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = m_LoadedList.Push(pLoadTask);
    LOG_PROCESS_ERROR(nRetCode);

    pLoadTask = NULL;
    pLoadedDataList = NULL;

Exit0:
    SAFE_DELETE(pLoadedDataList);
    SAFE_DELETE(pLoadTask);

    return;
}

void CGlobalDataManager::_LoadedData(LOAD_TASK* pLoadTask)
{
    INT32 nRetCode = 0;
    LOADED_DATA_LIST* pLoadedDataList = NULL;
    std::map<std::string, void*>::iterator it;
    CDataManager<FAKE_DATA>* pDataManager = NULL;

    pLoadedDataList = (LOADED_DATA_LIST*)pLoadTask->pTaskData;

    it = m_LoadDataMap.find(pLoadedDataList->szConfigName);
    LOG_PROCESS_ERROR(it != m_LoadDataMap.end());

    pDataManager = (CDataManager<FAKE_DATA>*)it->second;
    LOG_PROCESS_ERROR(pDataManager);

#if !defined(_FINAL)
    if (!pLoadedDataList->bLoaded)
    {
        pLoadedDataList->bOnlyLoadCache = FALSE;

        nRetCode = pDataManager->_Load(pLoadedDataList);
        LOG_PROCESS_ERROR(nRetCode);
    }
#endif

    nRetCode = pDataManager->_Insert(pLoadedDataList);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    SAFE_DELETE(pLoadedDataList);
    SAFE_DELETE(pLoadTask);

    return;
}

void CGlobalDataManager::GetDataCRC(UINT32* pdwCRCList)
{
	CDataManager<FAKE_DATA>* pDataManager = NULL;

	LOG_PROCESS_ERROR(pdwCRCList);

	for (std::map<std::string, void*>::iterator it = m_LoadDataMap.begin();
		it != m_LoadDataMap.end(); ++it)
	{
		pDataManager = (CDataManager<FAKE_DATA>*)it->second;
		LOG_PROCESS_ERROR(pDataManager);

		*pdwCRCList = pDataManager->GetCRC();
		pdwCRCList++;
	}

Exit0:
	return;
}

INT64 CGlobalDataManager::PrintMemoryStat(void)
{
	INT64 llTotalSize = 0;
	CDataManager<FAKE_DATA>* pDataManager = NULL;

	for (std::map<std::string, void*>::iterator it = m_LoadDataMap.begin();
		it != m_LoadDataMap.end(); ++it)
	{
		pDataManager = (CDataManager<FAKE_DATA>*)it->second;
		if (pDataManager == NULL)
			continue;

		llTotalSize += pDataManager->GetDataCount() * pDataManager->GetDataSize();
		INF("%s data manager allocated %d data %.2fMB", it->first.c_str(), 
			pDataManager->GetDataCount(), pDataManager->GetDataCount() * pDataManager->GetDataSize() / (1024 * 1024.0f));
	}

	INF("all data manager allocated %.2fMB", llTotalSize / (1024 * 1024.0f));

	return llTotalSize;
}