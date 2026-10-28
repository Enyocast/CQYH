#include "stdafx.h"
#include "rolelogcheck.h"
#include "time_ex.h"
#include "global_data_manager.h"

CRoleLogCheck CRoleLogCheck::ms_Instance;

CRoleLogCheck::CRoleLogCheck(void)
{
	m_byFileIndex = 0;
}

CRoleLogCheck::~CRoleLogCheck(void)
{
	UnInit();
}

CRoleLogCheck& CRoleLogCheck::GetInstance(void)
{
	return ms_Instance;
}

BOOL CRoleLogCheck::Init(void)
{
	INT32 nRetCode = 0;

	nRetCode = m_oMoneyLogDataPool.Init(5000000);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = m_oGMLogDataPool.Init(100000);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = m_oRoleLogoutBasicDataPool.Init(200000);
	LOG_PROCESS_ERROR(nRetCode);
	
	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRoleLogCheck::UnInit(void)
{
	INT32 nRetCode = 0;

	_ReleaseLogCache();

	nRetCode = m_oMoneyLogDataPool.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = m_oGMLogDataPool.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = m_oRoleLogoutBasicDataPool.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;
}

BOOL CRoleLogCheck::DoCheckLog(const char* pszDirectory, const char* pszDate1, const char* pszDirectory2, const char* pszDate2)
{
	INT32 nRetCode = 0;
	char szFileName[MAX_PATH];

	LOG_PROCESS_ERROR(NULL != pszDirectory && NULL != pszDate1);
	LOG_PROCESS_ERROR(NULL == pszDirectory2 && NULL == pszDate2 ||
						NULL != pszDirectory2 && NULL != pszDate2);

	_ReleaseLogCache();

	// Load the money log file
	if (NULL != pszDirectory2)
	{
		snprintf(szFileName, MAX_PATH, "%s\\Money_%s.txt", pszDirectory2, pszDate2);
		++m_byFileIndex;
		LOG_PROCESS_ERROR(m_mapIndex2FileName.insert(std::make_pair(m_byFileIndex, szFileName)).second);
		nRetCode = _LoadMoneyLog(szFileName, m_byFileIndex);
		LOG_PROCESS_ERROR(nRetCode);
	}
	snprintf(szFileName, MAX_PATH, "%s\\Money_%s.txt", pszDirectory, pszDate1);
	++m_byFileIndex;
	LOG_PROCESS_ERROR(m_mapIndex2FileName.insert(std::make_pair(m_byFileIndex, szFileName)).second);
	nRetCode = _LoadMoneyLog(szFileName, m_byFileIndex);
	LOG_PROCESS_ERROR(nRetCode);

	// Load the GM log file
	if (NULL != pszDirectory2)
	{
		snprintf(szFileName, MAX_PATH, "%s\\gmmoney_%s.txt", pszDirectory2, pszDate2);
		++m_byFileIndex;
		LOG_PROCESS_ERROR(m_mapIndex2FileName.insert(std::make_pair(m_byFileIndex, szFileName)).second);
		nRetCode = _LoadGMLog(szFileName, m_byFileIndex);
		LOG_PROCESS_ERROR(nRetCode);
	}
	snprintf(szFileName, MAX_PATH, "%s\\gmmoney_%s.txt", pszDirectory, pszDate1);
	++m_byFileIndex;
	LOG_PROCESS_ERROR(m_mapIndex2FileName.insert(std::make_pair(m_byFileIndex, szFileName)).second);
	nRetCode = _LoadGMLog(szFileName, m_byFileIndex);
	LOG_PROCESS_ERROR(nRetCode);

	// Load the RoleLogout Basic log file
	if (NULL != pszDirectory2)
	{
		snprintf(szFileName, MAX_PATH, "%s\\RoleLogout_Basic_%s.txt", pszDirectory2, pszDate2);
		++m_byFileIndex;
		LOG_PROCESS_ERROR(m_mapIndex2FileName.insert(std::make_pair(m_byFileIndex, szFileName)).second);
		nRetCode = _LoadBasicLog(szFileName, m_byFileIndex);
		LOG_PROCESS_ERROR(nRetCode);
	}
	snprintf(szFileName, MAX_PATH, "%s\\RoleLogout_Basic_%s.txt", pszDirectory, pszDate1);
	++m_byFileIndex;
	LOG_PROCESS_ERROR(m_mapIndex2FileName.insert(std::make_pair(m_byFileIndex, szFileName)).second);
	nRetCode = _LoadBasicLog(szFileName, m_byFileIndex);
	LOG_PROCESS_ERROR(nRetCode);

	//Analyze data
	nRetCode = _CheckLog();
	LOG_PROCESS_ERROR(nRetCode);

	_ReleaseLogCache();

	return TRUE;

Exit0:

	_ReleaseLogCache();

	return FALSE;
}

BOOL CRoleLogCheck::_LoadMoneyLog(const char* pszFilePath, UINT8 byFileIndex)
{

#define ADD_MONEY_LOG_DATA(_roleId) \
	m_mapRoleMoneyLogDataIter = m_mapRoleMoneyLogData.find(_roleId);\
	if (m_mapRoleMoneyLogDataIter != m_mapRoleMoneyLogData.end())\
	{\
		m_mapRoleMoneyLogDataIter->second.Push(&pMoneyLogData->GetSimpleListNode());\
	}\
	else\
	{\
		rmlInsRet = m_mapRoleMoneyLogData.insert(std::make_pair(_roleId, CSimpleList()));\
		LOG_PROCESS_ERROR(rmlInsRet.second);\
		m_mapRoleMoneyLogDataIter = m_mapRoleMoneyLogData.find(_roleId);\
		LOG_PROCESS_ERROR(m_mapRoleMoneyLogDataIter != m_mapRoleMoneyLogData.end());\
		m_mapRoleMoneyLogDataIter->second.Push(&pMoneyLogData->GetSimpleListNode());\
	}

	INT32 nRetCode = 0;
	INT32 nRowIndex = 0;
	const char* pcszName = NULL;
	CTabFile oTabFile;
	MONEY_LOG_DATA* pMoneyLogData = NULL;

	INT32 nID = -1;
	INT32 nIndex = 0;
	double dProgressCount = 0;
	double dTotalCount = 0;
	INT32 nPercent = 0;
	static INT32 nLastPercent = -1;
	
	MAP_INDEX_2_FILE_NAME::iterator fnIter;
	MAP_INDEX_2_FILE_NAME::iterator fnIter2;
	std::pair<MAP_ROLE_MONEY_LOG_DATA::iterator, bool> rmlInsRet;

	LOG_PROCESS_ERROR(pszFilePath);
	COutput::GetInstance().Printf("Opening file %s", pszFilePath);
	nRetCode = oTabFile.Init(pszFilePath, 0);
	if (!nRetCode)
	{
		COutput::GetInstance().Printf("Open file failed, file=%s", pszFilePath);
	}
	LOG_PROCESS_ERROR(nRetCode);

	COutput::GetInstance().Printf("Start loading ...");
	for (nIndex = 0, nRowIndex = oTabFile.GetRowCount() - 1; nRowIndex >= 0; --nRowIndex, ++nIndex)
	{
		pMoneyLogData = NewMoneyLogData();
		LOG_PROCESS_ERROR(pMoneyLogData);
		memset(pMoneyLogData, 0, sizeof(MONEY_LOG_DATA));

		nRetCode = MONEY_LOG_DATA::ReadLine(nID, pcszName, pMoneyLogData, &oTabFile, nRowIndex);
		if (!nRetCode)
		{
			ERR("Failed to read data at row %d in %s data file", nRowIndex + 2, pszFilePath);
			DelMoneyLogData(pMoneyLogData);
			continue;
		}

		LOG_PROCESS_ERROR(ACTION_ADD_MONEY == pMoneyLogData->nAction || ACTION_SUB_MONEY == pMoneyLogData->nAction);
		ADD_MONEY_LOG_DATA(pMoneyLogData->nRoleID);

		pMoneyLogData = NULL;

		dProgressCount = double(nIndex + 1);
		dTotalCount = double(oTabFile.GetRowCount());
		nPercent = INT32((dProgressCount / dTotalCount) * 100);

		if (nLastPercent != nPercent)
		{
			COutput::GetInstance().PrintfLoadingProgress(nPercent);
			nLastPercent = nPercent;
		}
	}

	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;

Exit0:

	nRetCode = DelMoneyLogData(pMoneyLogData);
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return FALSE;
}

BOOL CRoleLogCheck::_LoadGMLog(const char* pszFilePath, UINT8 byFileIndex)
{
	INT32 nRetCode = 0;
	CTabFile oTabFile;
	INT32 nRowIndex = 0;
	GM_LOG_DATA* pGMLogData = NULL;
	MONEY_LOG_DATA* pMoneyLogData = NULL;
	INT32 nID = -1;
	const char* pcszName = NULL;

	char* pMoneyTypeStr = NULL;
	char* pOldMoneyStr = NULL;
	char* pNewMoneyStr = NULL;
	char* pRoleIDStr = NULL;
	INT32 nNewMoney = 0;
	INT32 nOldMoney = 0;

	INT32 nIndex = 0;
	double dProgressCount = 0;
	double dTotalCount = 0;
	INT32 nPercent = 0;
	static INT32 nLastPercent = -1;

	pMoneyLogData = NewMoneyLogData();
	LOG_PROCESS_ERROR(pMoneyLogData);

	LOG_PROCESS_ERROR(pszFilePath);
	COutput::GetInstance().Printf("Opening file %s", pszFilePath);
	nRetCode = oTabFile.Init(pszFilePath, 0);
	if (!nRetCode)
	{
		COutput::GetInstance().Printf("Open file failed, file=%s", pszFilePath);
	}
	LOG_PROCESS_ERROR(nRetCode);

	COutput::GetInstance().Printf("Start loading ...");
	for (nIndex = 0, nRowIndex = oTabFile.GetRowCount() - 1; nRowIndex >= 0; --nRowIndex, ++nIndex)
	{
		nRetCode = MONEY_LOG_DATA::ReadLine(nID, pcszName, pMoneyLogData, &oTabFile, nRowIndex);
		if (!nRetCode)
		{
			ERR("Failed to read data at row %d in %s data file", nRowIndex + 2, pszFilePath);
			continue;
		}

		if (MONEY_TYPE_GOLD != pMoneyLogData->nMoneyType)
		{
			continue;
		}

		pGMLogData = NewGMLogData();
		LOG_PROCESS_ERROR(pGMLogData);
		memset(pGMLogData, 0, sizeof(GM_LOG_DATA));

		pGMLogData->nRoleID = pMoneyLogData->nRoleID;
		pGMLogData->dwTime = pMoneyLogData->dwTime;
		pGMLogData->bIsMoneyLog = TRUE;
		pGMLogData->nAction = pMoneyLogData->nAction;
		pGMLogData->nMoneyType = pMoneyLogData->nMoneyType;
		pGMLogData->nMoneyCount = pMoneyLogData->nMoneyCount;

		m_mapRoleGMLogDataIter = m_mapRoleGMLogData.find(pGMLogData->nRoleID);
		if (m_mapRoleGMLogDataIter != m_mapRoleGMLogData.end())
		{
			m_mapRoleGMLogDataIter->second.Push(&pGMLogData->GetSimpleListNode());
		}
		else
		{
			LOG_PROCESS_ERROR(m_mapRoleGMLogData.insert(std::make_pair(pGMLogData->nRoleID, CSimpleList())).second);
			m_mapRoleGMLogDataIter = m_mapRoleGMLogData.find(pGMLogData->nRoleID);
			LOG_PROCESS_ERROR(m_mapRoleGMLogDataIter != m_mapRoleGMLogData.end());
			m_mapRoleGMLogDataIter->second.Push(&pGMLogData->GetSimpleListNode());
		}

		pGMLogData = NULL;

		dProgressCount = double(nIndex + 1);
		dTotalCount = double(oTabFile.GetRowCount());
		nPercent = INT32((dProgressCount / dTotalCount) * 100);

		if (nLastPercent != nPercent)
		{
			COutput::GetInstance().PrintfLoadingProgress(nPercent);

			nLastPercent = nPercent;
		}
	}

	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	DelMoneyLogData(pMoneyLogData);

	return TRUE;

Exit0:

	nRetCode = DelGMLogData(pGMLogData);
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	DelMoneyLogData(pMoneyLogData);

	return FALSE;
}

BOOL CRoleLogCheck::_LoadBasicLog(const char* pszFilePath, UINT8 byFileIndex)
{
	INT32 nRetCode = 0;
	CTabFile oTabFile;
	INT32 nRowIndex = 0;
	ROLE_LOGOUT_BASIC_DATA* pRoleLogoutBasicData = NULL;
	INT32 nID = -1;
	const char* pcszName = NULL;

	INT32 nIndex = 0;
	double dProgressCount = 0;
	double dTotalCount = 0;
	INT32 nPercent = 0;
	static INT32 nLastPercent = -1;

	LOG_PROCESS_ERROR(pszFilePath);
	COutput::GetInstance().Printf("Opening file %s", pszFilePath);
	nRetCode = oTabFile.Init(pszFilePath, 0);
	if (!nRetCode)
	{
		COutput::GetInstance().Printf("Open file failed, file=%s", pszFilePath);
	}
	LOG_PROCESS_ERROR(nRetCode);

	COutput::GetInstance().Printf("Start loading ...");
	for (nIndex = 0, nRowIndex = oTabFile.GetRowCount() - 1; nRowIndex >= 0; --nRowIndex, ++nIndex)
	{
		pRoleLogoutBasicData = NewRoleLogoutBasicData();
		LOG_PROCESS_ERROR(pRoleLogoutBasicData);
		memset(pRoleLogoutBasicData, 0, sizeof(ROLE_LOGOUT_BASIC_DATA));

		nRetCode = ROLE_LOGOUT_BASIC_DATA::ReadLine(nID, pcszName, pRoleLogoutBasicData, &oTabFile, nRowIndex);
		if (!nRetCode)
		{
			ERR("Failed to read data at row %d in %s data file", nRowIndex + 2, pszFilePath);
			DelRoleLogoutBasicData(pRoleLogoutBasicData);
			continue;
		}

		m_mapRoleLogoutBasicDataIter = m_mapRoleLogoutBasicData.find(pRoleLogoutBasicData->nRoleID);
		if (m_mapRoleLogoutBasicDataIter != m_mapRoleLogoutBasicData.end())
		{
			m_mapRoleLogoutBasicDataIter->second.Push(&pRoleLogoutBasicData->oLogoutLogNode);
		}
		else
		{
			LOG_PROCESS_ERROR(m_mapRoleLogoutBasicData.insert(std::make_pair(pRoleLogoutBasicData->nRoleID, CSimpleList())).second);
			m_mapRoleLogoutBasicDataIter = m_mapRoleLogoutBasicData.find(pRoleLogoutBasicData->nRoleID);
			LOG_PROCESS_ERROR(m_mapRoleLogoutBasicDataIter != m_mapRoleLogoutBasicData.end());
			m_mapRoleLogoutBasicDataIter->second.Push(&pRoleLogoutBasicData->oLogoutLogNode);
		}

		pRoleLogoutBasicData = NULL;

		dProgressCount = double(nIndex + 1);
		dTotalCount = double(oTabFile.GetRowCount());
		nPercent = INT32((dProgressCount / dTotalCount) * 100);

		if (nLastPercent != nPercent)
		{
			COutput::GetInstance().PrintfLoadingProgress(nPercent);

			nLastPercent = nPercent;
		}
	}

	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;

Exit0:

	nRetCode = DelRoleLogoutBasicData(pRoleLogoutBasicData);
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = oTabFile.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return FALSE;
}

BOOL CRoleLogCheck::_CheckLog()
{
	INT32 nRetCode = 0;
	MONEY_LOG_DATA* pMoneyLogData = NULL;
	GM_LOG_DATA* pGMLogData = NULL;
	ROLE_LOGOUT_BASIC_DATA* pRoleLogoutBasicData = NULL;

	INT32 nIndex = 0;
	double dProgressCount = 0;
	double dTotalCount = 0;
	INT32 nPercent = 0;
	INT32 nLastPercent = -1;

	INT32 nTempLogoutDataCount = 0;
	INT32 nTotalLogoutDataCount = 0;
	INT32 nDiscardLogoutDataCount = 0;

	BOOL bTimeAtThisLogoutTime = FALSE;
	BOOL bTimeAtLastLogoutTime = FALSE;
	INT32 nLastLogoutMoney = 0;
	INT32 nLogoutMoney = 0;
	UINT32 dwLastLogoutTime = 0;
	UINT32 dwLogoutTime = 0;
	INT32 nDiffMoney = 0;
	INT32 nCheckMoney = 0;
	INT32 nErrorCheckCount = 0;

	CSimpleList* pLstLogoutData = NULL;
	SimpleListNode* pLogoutLogNode = NULL;

	CSimpleList* pLstMoneyData = NULL;
	SimpleListNode* pMoneyLogNode = NULL;

	CSimpleList* pLstGMData = NULL;
	SimpleListNode* pGMLogNode = NULL;

	char szLogoutTime[64];
	char szLastLogoutTime[64];

	COutput::GetInstance().Printf("Start checking ...");
	dTotalCount = (double)m_mapRoleLogoutBasicData.size();
	for (m_mapRoleLogoutBasicDataIter = m_mapRoleLogoutBasicData.begin();
		m_mapRoleLogoutBasicDataIter != m_mapRoleLogoutBasicData.end();
		++m_mapRoleLogoutBasicDataIter)
	{
		++nIndex;

		pLstMoneyData = NULL;
		pLstGMData = NULL;
		pLstLogoutData = &(m_mapRoleLogoutBasicDataIter->second);
		nTotalLogoutDataCount += (INT32)pLstLogoutData->Size();

		m_mapRoleMoneyLogDataIter = m_mapRoleMoneyLogData.find(m_mapRoleLogoutBasicDataIter->first);
		if (m_mapRoleMoneyLogDataIter != m_mapRoleMoneyLogData.end())
		{
			pLstMoneyData = &(m_mapRoleMoneyLogDataIter->second);
		}

		m_mapRoleGMLogDataIter = m_mapRoleGMLogData.find(m_mapRoleLogoutBasicDataIter->first);
		if (m_mapRoleGMLogDataIter != m_mapRoleGMLogData.end())
		{
			pLstGMData = &(m_mapRoleGMLogDataIter->second);
		}

		if (pLstLogoutData->IsEmpty() || 
			(NULL == pLstMoneyData && NULL == pLstGMData) ||
			(pLstMoneyData->IsEmpty() && pLstGMData->IsEmpty()))
		{
			continue;
		}

		//Ignore data before the character’s first logout
		pLogoutLogNode = pLstLogoutData->Top();
		LOG_PROCESS_ERROR(pLogoutLogNode);

		pRoleLogoutBasicData = ROLE_LOGOUT_BASIC_DATA::ParseSimpleListNode(pLogoutLogNode);
		LOG_PROCESS_ERROR(pRoleLogoutBasicData);
		nLastLogoutMoney = pRoleLogoutBasicData->nMoney2;
		dwLastLogoutTime = pRoleLogoutBasicData->dwTime;
		pLogoutLogNode = pLogoutLogNode->pNext;

		nTempLogoutDataCount = 0;
		bTimeAtThisLogoutTime = FALSE;
		bTimeAtLastLogoutTime = FALSE;
		if (NULL != pLstMoneyData) pMoneyLogNode = pLstMoneyData->Top();
		if (NULL != pLstGMData) pGMLogNode = pLstGMData->Top();
		for (; NULL != pLogoutLogNode;)
		{
			++nTempLogoutDataCount;
			pRoleLogoutBasicData = ROLE_LOGOUT_BASIC_DATA::ParseSimpleListNode(pLogoutLogNode);
			LOG_PROCESS_ERROR(pRoleLogoutBasicData);
			nLogoutMoney = pRoleLogoutBasicData->nMoney2;
			dwLogoutTime = pRoleLogoutBasicData->dwTime;

			nDiffMoney = 0;

			if (NULL != pLstMoneyData)
			{
				for (; NULL != pMoneyLogNode;)
				{
					pMoneyLogData = MONEY_LOG_DATA::ParseSimpleListNode(pMoneyLogNode);
					LOG_PROCESS_ERROR(pMoneyLogData);

					if (MONEY_TYPE_GOLD != pMoneyLogData->nMoneyType)
					{
						pMoneyLogNode = pMoneyLogNode->pNext;
						continue;
					}

					if (pMoneyLogData->dwTime > dwLogoutTime)
					{
						if (!bTimeAtThisLogoutTime)
						{
							break;
						}

						++nTempLogoutDataCount;
						pLogoutLogNode = pLogoutLogNode->pNext;
						if (NULL == pLogoutLogNode)
						{
							break;
						}

						bTimeAtThisLogoutTime = FALSE;
						pRoleLogoutBasicData = ROLE_LOGOUT_BASIC_DATA::ParseSimpleListNode(pLogoutLogNode);
						LOG_PROCESS_ERROR(pRoleLogoutBasicData);
						nLogoutMoney = pRoleLogoutBasicData->nMoney2;
						dwLogoutTime = pRoleLogoutBasicData->dwTime;
					}

					if (pMoneyLogData->dwTime > dwLogoutTime)
					{
						break;
					}

					if (dwLastLogoutTime == pMoneyLogData->dwTime)
					{
						bTimeAtLastLogoutTime = TRUE;
						pLogoutLogNode = pLogoutLogNode->pNext;
						if (NULL == pLogoutLogNode)
						{
							break;
						}

						nDiscardLogoutDataCount += 1;
						bTimeAtLastLogoutTime = FALSE;
						nLastLogoutMoney = pRoleLogoutBasicData->nMoney2;
						dwLastLogoutTime = pRoleLogoutBasicData->dwTime;

						pRoleLogoutBasicData = ROLE_LOGOUT_BASIC_DATA::ParseSimpleListNode(pLogoutLogNode);
						LOG_PROCESS_ERROR(pRoleLogoutBasicData);
						nLogoutMoney = pRoleLogoutBasicData->nMoney2;
						dwLogoutTime = pRoleLogoutBasicData->dwTime;
						nDiffMoney = 0;
					}

					if (dwLastLogoutTime < pMoneyLogData->dwTime && pMoneyLogData->dwTime <= dwLogoutTime)
					{
						if (ACTION_ADD_MONEY == pMoneyLogData->nAction)
						{
							nDiffMoney += pMoneyLogData->nMoneyCount;
						}
						else
						{
							nDiffMoney -= pMoneyLogData->nMoneyCount;
						}

						if (pMoneyLogData->dwTime == dwLogoutTime)
						{
							bTimeAtThisLogoutTime = TRUE;
						}
					}

					pMoneyLogNode = pMoneyLogNode->pNext;
				}
			}

			//Discard
			if (bTimeAtLastLogoutTime)
			{
				nDiscardLogoutDataCount += 1;
				break;
			}
			if (bTimeAtThisLogoutTime)
			{
				nDiscardLogoutDataCount += nTempLogoutDataCount;
				break;
			}

			if (NULL != pLstGMData)
			{
				for (; NULL != pGMLogNode;)
				{
					pGMLogData = GM_LOG_DATA::ParseSimpleListNode(pGMLogNode);
					LOG_PROCESS_ERROR(pGMLogData);

					if (pGMLogData->dwTime > dwLogoutTime)
					{
						break;
					}
					else if (dwLastLogoutTime < pGMLogData->dwTime && pGMLogData->dwTime <= dwLogoutTime && MONEY_TYPE_GOLD == pGMLogData->nMoneyType)
					{
						if (ACTION_ADD_MONEY == pGMLogData->nAction)
						{
							nDiffMoney += pGMLogData->nMoneyCount;
						}
						else
						{
							nDiffMoney -= pGMLogData->nMoneyCount;
						}
					}
					else
					{
					}

					pGMLogNode = pGMLogNode->pNext;
				}
			}

			nCheckMoney = nLastLogoutMoney + nDiffMoney;
			if (nCheckMoney != nLogoutMoney)
			{
				snprintf(szLogoutTime, 63, "%s", get_time_str(dwLogoutTime));
				snprintf(szLastLogoutTime, 63, "%s", get_time_str(dwLastLogoutTime));

				ERR("*** log data error, role_id=%d, last_logout_time=%s, logout_time=%s, last_logout_money=%d, logout_money=%d, check_money=%d, diff_money=%d ***",
					pRoleLogoutBasicData->nRoleID, szLastLogoutTime, szLogoutTime, nLastLogoutMoney, nLogoutMoney, nCheckMoney, nDiffMoney);
				nCheckMoney = nCheckMoney;

				++nErrorCheckCount;
			}

			nLastLogoutMoney = pRoleLogoutBasicData->nMoney2;
			dwLastLogoutTime = pRoleLogoutBasicData->dwTime;

			nTempLogoutDataCount = 0;

			if (NULL != pLogoutLogNode)
			{
				pLogoutLogNode = pLogoutLogNode->pNext;
			}
		}

		dProgressCount = double(nIndex);
		LOG_PROCESS_ERROR(dTotalCount);
		nPercent = INT32((dProgressCount / dTotalCount) * 100);
		if (nLastPercent != nPercent)
		{
			COutput::GetInstance().PrintfLoadingProgress(nPercent);

			nLastPercent = nPercent;
		}
	}
	if (nPercent != 100 && nIndex == dTotalCount)
	{
		nPercent = 100;
		COutput::GetInstance().PrintfLoadingProgress(nPercent);
	}

	if (nErrorCheckCount > 0)
	{
		COutput::GetInstance().Printf("*** check finish, error log count %d ***", nErrorCheckCount);
	}
	else
	{
		COutput::GetInstance().Printf("check finish, error log count %d.", nErrorCheckCount);
	}
	
	COutput::GetInstance().Printf("logout data discard %d, total %d.", nDiscardLogoutDataCount, nTotalLogoutDataCount);

	return TRUE;

Exit0:

	return FALSE;
}

void CRoleLogCheck::_ReleaseLogCache()
{
	SimpleListNode* pSimpleListNode = NULL;
	MAP_ROLE_MONEY_LOG_DATA::iterator moneyIt;
	MAP_ROLE_GM_LOG_DATA::iterator gmIt;
	MAP_ROLE_LOGOUT_BASIC_DATA::iterator logoutIt;

	m_byFileIndex = 0;
	m_mapIndex2FileName.clear();

	for (moneyIt = m_mapRoleMoneyLogData.begin(); moneyIt != m_mapRoleMoneyLogData.end(); ++moneyIt)
	{
		CSimpleList& lstMoney = moneyIt->second;
		pSimpleListNode = lstMoney.Pop();
		while (pSimpleListNode)
		{
			DelMoneyLogData(MONEY_LOG_DATA::ParseSimpleListNode(pSimpleListNode));
			pSimpleListNode = lstMoney.Pop();
		}

		lstMoney.Clear();
	}
	m_mapRoleMoneyLogData.clear();

	for (gmIt = m_mapRoleGMLogData.begin(); gmIt != m_mapRoleGMLogData.end(); ++gmIt)
	{
		CSimpleList& lstGM = gmIt->second;
		pSimpleListNode = lstGM.Pop();
		while (pSimpleListNode)
		{
			DelGMLogData(GM_LOG_DATA::ParseSimpleListNode(pSimpleListNode));
			pSimpleListNode = lstGM.Pop();
		}

		lstGM.Clear();
	}
	m_mapRoleGMLogData.clear();

	for (logoutIt = m_mapRoleLogoutBasicData.begin(); logoutIt != m_mapRoleLogoutBasicData.end(); ++logoutIt)
	{
		CSimpleList& lstLogout = logoutIt->second;
		pSimpleListNode = lstLogout.Pop();
		while (pSimpleListNode)
		{
			DelRoleLogoutBasicData(ROLE_LOGOUT_BASIC_DATA::ParseSimpleListNode(pSimpleListNode));
			pSimpleListNode = lstLogout.Pop();
		}
		
		lstLogout.Clear();
	}
	m_mapRoleLogoutBasicData.clear();
}

void CRoleLogCheck::ShowUsage()
{
	COutput::GetInstance().Printf("usage:");
	COutput::GetInstance().Printf("\t1. param1=dir1 param2=date1 [param3=dir2 param4=date2]");
	COutput::GetInstance().Printf("\t2. date2 should laster then date1");
	COutput::GetInstance().Printf("\t3. eg: logdata\\2015-08-07 2015_08_07 logdata\\2015-08-08 2015_08_08");
	COutput::GetInstance().Printf(" ");
}

BOOL CRoleLogCheck::CheckParam(INT32 argc, char** argv)
{
	INT32 nRetCode = 0;

	if (3 != argc && 5 != argc)
	{
		COutput::GetInstance().Printf("Params error!");
		ShowUsage();
		PROCESS_ERROR(FALSE);
	}

	if (5 == argc)
	{
		if (strcmp(argv[2], argv[4]) != -1)
		{
			ShowUsage();
			PROCESS_ERROR(FALSE);
		}
	}

	return TRUE;

Exit0:

	return FALSE;
}

INT32 MONEY_LOG_DATA::nID = -1;
char MONEY_LOG_DATA::szTime[20] = "";
char MONEY_LOG_DATA::szAction[20] = "";

time_t Str2Time(const char* szTime)
{
	time_t tTime = 0;
	tm t = { 0 };

	LOG_PROCESS_ERROR(szTime);
	
	sscanf(szTime, "%d-%02d-%02d %02d:%02d:%02d", &t.tm_year, &t.tm_mon, &t.tm_mday,
		&t.tm_hour, &t.tm_min, &t.tm_sec);

	t.tm_year -= 1900;
	t.tm_mon -= 1;
	tTime = mktime(&t);

Exit0:
	return tTime;
}

time_t CustomizedStr2Time(const char* szTime)
{
	static time_t tLastTime = 0;
	static tm lastTm = { 0 };
	static char szLastTime[] = "0000-00-00 00:00:00";

	time_t tTime = 0;
	tm t = { 0 };
	BOOL bHaveDiff = FALSE;

	LOG_PROCESS_ERROR(szTime);

	if (szLastTime[0] != szTime[0] ||
		szLastTime[1] != szTime[1] ||
		szLastTime[2] != szTime[2] ||
		szLastTime[3] != szTime[3])
	{
		bHaveDiff = TRUE;
		memcpy(szLastTime + 0, szTime + 0, 4);
		lastTm.tm_year = atoi(szTime + 0);
	}

	if (szLastTime[5] != szTime[5] ||
		szLastTime[6] != szTime[6])
	{
		bHaveDiff = TRUE;
		memcpy(szLastTime + 5, szTime + 5, 2);
		lastTm.tm_mon = atoi(szTime + 5);
	}

	if (szLastTime[8] != szTime[8] ||
		szLastTime[9] != szTime[9])
	{
		bHaveDiff = TRUE;
		memcpy(szLastTime + 8, szTime + 8, 2);
		lastTm.tm_mday = atoi(szTime + 8);
	}

	if (szLastTime[11] != szTime[11] ||
		szLastTime[12] != szTime[12])
	{
		bHaveDiff = TRUE;
		memcpy(szLastTime + 11, szTime + 11, 2);
		lastTm.tm_hour = atoi(szTime + 11);
	}

	if (szLastTime[14] != szTime[14] ||
		szLastTime[15] != szTime[15])
	{
		bHaveDiff = TRUE;
		memcpy(szLastTime + 14, szTime + 14, 2);
		lastTm.tm_min = atoi(szTime + 14);
	}

	if (szLastTime[17] != szTime[17] ||
		szLastTime[18] != szTime[18])
	{
		bHaveDiff = TRUE;
		memcpy(szLastTime + 17, szTime + 17, 2);
		lastTm.tm_sec = atoi(szTime + 17);
	}

	if (bHaveDiff)
	{
		t.tm_year = lastTm.tm_year;
		t.tm_mon = lastTm.tm_mon;
		t.tm_mday = lastTm.tm_mday;
		t.tm_hour = lastTm.tm_hour;
		t.tm_min = lastTm.tm_min;
		t.tm_sec = lastTm.tm_sec;

		t.tm_year -= 1900;
		t.tm_mon -= 1;

		tTime = mktime(&t);
		tLastTime = tTime;
	}
	else
	{
		tTime = tLastTime;
	}

Exit0:
	return tTime;
}

INT32 ROLE_LOGOUT_BASIC_DATA::nID;
char ROLE_LOGOUT_BASIC_DATA::szTime[20];

COutput::COutput(void)
{

}

COutput::~COutput(void)
{

}

COutput& COutput::GetInstance(void)
{
	return ms_Instance;
}

void COutput::Cls(void)
{
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the
									 cursor */
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in
									 the current buffer */

	/* get the number of character cells in the current buffer */
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	LOG_PROCESS_ERROR(hConsole);

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	LOG_PROCESS_ERROR(bSuccess);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */

	bSuccess = FillConsoleOutputCharacter(hConsole, (CHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);
	LOG_PROCESS_ERROR(bSuccess);

	/* get the current text attribute */

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	LOG_PROCESS_ERROR(bSuccess);

	/* now set the buffer's attributes accordingly */

	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);
	LOG_PROCESS_ERROR(bSuccess);

	/* put the cursor at (0, 0) */

	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	LOG_PROCESS_ERROR(bSuccess);

Exit0:
	return;
}

void COutput::Goto(SHORT x, SHORT y)
{
	BOOL bSuccess;

	COORD coord;
	coord.X = x;
	coord.Y = y;

	/* get the number of character cells in the current buffer */
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	LOG_PROCESS_ERROR(hConsole);

	bSuccess = SetConsoleCursorPosition(hConsole, coord);
	LOG_PROCESS_ERROR(bSuccess);

Exit0:
	return;
}

void COutput::Printf(const char * _Format, ...)
{
	INT32 nRetCode = 0;
	static char szMsg[2048];

	va_list args;
	va_start(args, _Format);
	nRetCode = vsnprintf_s(szMsg, sizeof(szMsg) - 1, sizeof(szMsg) - 1, _Format, args);
	LOG_CHECK_ERROR(nRetCode);
	va_end(args);

	printf("%s\n", szMsg);

	ERR(szMsg);
}

void COutput::PrintfLoadingProgress(INT32 nPercent)
{
	printf("\r");
	printf("                                                                               ");
	printf("\r");
	if (100 == nPercent)
	{
		printf("Progressing %d%% ...\n", nPercent);
	}
	else
	{
		printf("Progressing %d%% ...", nPercent);
	}
}

COutput COutput::ms_Instance;

INT32 GM_LOG_DATA::nID = -1;
char GM_LOG_DATA::szTime[20] = "";

char GM_LOG_DATA::szContent[2048] = "";

INT32 MONEY_LOG_DATA::nSrcRoleID;

INT32 MONEY_LOG_DATA::nTargetRoleID;
