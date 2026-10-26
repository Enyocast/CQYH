#include "stdafx.h"
#include <time.h>

#include "cash_accounting.h"
#include "sql_mgr.h"
#include "cash_accounting_stmt.list.h"

CCashAccounting CCashAccounting::ms_Instance;

CCashAccounting::CCashAccounting()
{
	
}

CCashAccounting::~CCashAccounting()
{

}

 CCashAccounting& CCashAccounting::GetInstance(void)
 {
 	return ms_Instance;
 }

 BOOL CCashAccounting::Init(void)
 {
 	INT32 nRetCode = 0; 
 	m_pLogHandler = NULL;
 
 	m_AccountingRoleList.Clear();
 	
 	strxcpy(m_dbsetting.szServerAddr, "172.30.66.24", DB_SETTING_STRING_LEN);
 	strxcpy(m_dbsetting.szLoginName, "Jiutian", DB_SETTING_STRING_LEN);
 	strxcpy(m_dbsetting.szPassword, "JiutianSky", DB_SETTING_STRING_LEN);
 	strxcpy(m_dbsetting.szDBName, "sh_zhangm03_d", DB_SETTING_STRING_LEN);
 	strxcpy(m_dbsetting.szDBNameLogData, "jtdb_logdata", DB_SETTING_STRING_LEN);
 	strxcpy(m_dbsetting.szCharSet, "utf8", DB_SETTING_STRING_LEN);
 	m_dbsetting.dwServerPort = 3306;
 
 	nRetCode = m_AccountingRolePool.Init(8192);
 	LOG_PROCESS_ERROR(nRetCode);
 
 	nRetCode = CSqlMgr::GetInstance().Init(
 		m_dbsetting.szServerAddr,
 		m_dbsetting.szLoginName,
 		m_dbsetting.szPassword,
 		m_dbsetting.szDBName,
 		m_dbsetting.szCharSet,
 		m_dbsetting.dwServerPort,
 		g_CASqlStmtList, caSqlTotal);
 
 	LOG_PROCESS_ERROR(nRetCode);
 
  	nRetCode = CSqlMgr::GetInstance().SyncExecSqlStmt(caSqlSelectLogoutRole, _Load, NULL, "");
  	LOG_PROCESS_ERROR(nRetCode);

 	m_pLogHandler = fopen("money_accounting", "a+");
 	LOG_PROCESS_ERROR(m_pLogHandler);
 
	return TRUE;
Exit0:
	return FALSE;
}
 
 BOOL CCashAccounting::UnInit(void)
 {
	INT32 nRetCode = 0;

	nRetCode = CSqlMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = m_AccountingRolePool.UnInit();
	LOG_CHECK_ERROR(nRetCode);

 	m_AccountingRoleList.Clear();
	
	fclose(m_pLogHandler);

 	return TRUE;
 }
 
 BOOL CCashAccounting::MainLoop(void)
 {
 	INT32 nRetCode = 0;
 	ACCOUNTING_ROLE* poAccountingRole = NULL;
 
 	while (!ms_Instance.m_AccountingRoleList.IsEmpty())
 	{
		BASE_LIST_NODE* pNode = NULL;

 		poAccountingRole = (ACCOUNTING_ROLE*)m_AccountingRoleList.Head().pNext;
 		LOG_PROCESS_ERROR(poAccountingRole);
 
 		for (pNode = m_AccountingRoleList.Head().pNext->pNext; pNode != (ACCOUNTING_ROLE*)&m_AccountingRoleList.Rear();)
 		{
	 		ACCOUNTING_ROLE* pRole = (ACCOUNTING_ROLE*)pNode;
			LOG_PROCESS_ERROR(pRole);

 			if (pRole->dwRoleID == poAccountingRole->dwRoleID)
 			{
				RoleMoneyUserData stRoleMoneyUserData;

				stRoleMoneyUserData.dwBeginLogTime = poAccountingRole->dwLogTime;
				stRoleMoneyUserData.dwEndLogTime = pRole->dwLogTime;
				stRoleMoneyUserData.nBeginMoney0 = poAccountingRole->nMoney0;
				stRoleMoneyUserData.nBeginMoney1 = poAccountingRole->nMoney1;
				stRoleMoneyUserData.nEndMoney0 = pRole->nMoney0;
				stRoleMoneyUserData.nEndMoney1 = pRole->nMoney1;
				stRoleMoneyUserData.dwRoleID = poAccountingRole->dwRoleID;
				strxcpy(stRoleMoneyUserData.szRoleName, poAccountingRole->szName, sizeof(stRoleMoneyUserData.szRoleName));

 				nRetCode = CSqlMgr::GetInstance().SyncExecSqlStmt(caSqlSelectRoleMoney, _Check, (void*)&stRoleMoneyUserData, "dddd", poAccountingRole->dwRoleID, poAccountingRole->dwRoleID, poAccountingRole->dwLogTime, pRole->dwLogTime);
 				LOG_CHECK_ERROR(nRetCode);

				break;
 			}

 			pNode = pNode->pNext;
 		}

		m_AccountingRoleList.Remove(poAccountingRole);
 	}
 
 	return TRUE;
 Exit0:
 	return FALSE;
 }

 void CCashAccounting::_Load(std::list<void*>& rResult, void* pUserData)
 {
 	INT32 nRetCode = 0;
 	ACCOUNTING_ROLE* pAccountingRole = NULL;
 
 #pragma pack(push, 1)
 	struct LOAD_RESULT
 	{
		UINT32	dwLogTime;
 		INT32	nRoleID;
 		INT32	nMoney0;
 		INT32	nMoney1;
		char	czName[21];
 	};
 #pragma pack(pop)

 	for (std::list<void*>::iterator it = rResult.begin();
 		it != rResult.end(); ++it)
 	{
 		LOAD_RESULT* pLoadResult = (LOAD_RESULT*)*it;
 		
 		pAccountingRole = ms_Instance.m_AccountingRolePool.New();
 		LOG_PROCESS_ERROR(pAccountingRole);

		pAccountingRole->pNext = NULL;
		pAccountingRole->pPrev = NULL;

		pAccountingRole->dwLogTime = pLoadResult->dwLogTime;
 		pAccountingRole->dwRoleID = pLoadResult->nRoleID;
 		pAccountingRole->nMoney0 = pLoadResult->nMoney0;
 		pAccountingRole->nMoney1 = pLoadResult->nMoney1;
		strxcpy(pAccountingRole->szName, pLoadResult->czName, sizeof(pAccountingRole->szName));

 		ms_Instance.m_AccountingRoleList.PushRear(pAccountingRole);
 	}

	return;
 Exit0:
 	return;
 }
 
 void CCashAccounting::_Check(std::list<void*>& rResult, void* pUserData)
 {
 	INT32 nRetCode = 0;
	INT32 nBeginMoney0 = 0;
	INT32 nEndMoney0 = 0;
	INT32 nBeginMoney1 = 0;
	INT32 nEndMoney1 = 0;

 #pragma pack(push, 1)
 	struct LOAD_RESULT
 	{
 		INT32 nSourceID;
 		INT32 nTargetID;
 		INT8  byMoenyType;
 		INT32 nMoneyCount;
 	};
 #pragma pack(pop)
 
	RoleMoneyUserData* pRoleMoneyUserData = (RoleMoneyUserData*)pUserData;
	LOG_PROCESS_ERROR(pRoleMoneyUserData);

	nBeginMoney0 = pRoleMoneyUserData->nBeginMoney0;
	nEndMoney0 = pRoleMoneyUserData->nEndMoney0;
	nBeginMoney1 = pRoleMoneyUserData->nBeginMoney1;
	nEndMoney1 = pRoleMoneyUserData->nEndMoney1;

 	for (std::list<void*>::iterator it = rResult.begin();
 		it != rResult.end(); ++it)
 	{
 		LOAD_RESULT* pLoadResult = (LOAD_RESULT*)*it;
 		if (pLoadResult->nSourceID == pRoleMoneyUserData->dwRoleID  && pLoadResult->byMoenyType == 0)
 		{
 			nBeginMoney0 -= pLoadResult->nMoneyCount;
 		}
 		else if (pLoadResult->nTargetID == pRoleMoneyUserData->dwRoleID && pLoadResult->byMoenyType == 0)
 		{
 			nBeginMoney0 += pLoadResult->nMoneyCount;
 		}
		else if (pLoadResult->nSourceID == pRoleMoneyUserData->dwRoleID  && pLoadResult->byMoenyType == 1)
		{
			nBeginMoney1 -= pLoadResult->nMoneyCount;
		}
		else if (pLoadResult->nTargetID == pRoleMoneyUserData->dwRoleID && pLoadResult->byMoenyType == 1)
		{
			nBeginMoney1 += pLoadResult->nMoneyCount;
		}
 	}
 
 	if (nBeginMoney0 == nEndMoney0)
 	{
 		nRetCode = CCashAccounting::GetInstance()._WriteLog(pRoleMoneyUserData->dwRoleID, pRoleMoneyUserData->szRoleName, pRoleMoneyUserData->dwBeginLogTime, pRoleMoneyUserData->dwEndLogTime,
			0, pRoleMoneyUserData->nBeginMoney0, pRoleMoneyUserData->nEndMoney0, TRUE);
 		LOG_PROCESS_ERROR(nRetCode);
 	}
 	else
 	{
		nRetCode = CCashAccounting::GetInstance()._WriteLog(pRoleMoneyUserData->dwRoleID, pRoleMoneyUserData->szRoleName, pRoleMoneyUserData->dwBeginLogTime, pRoleMoneyUserData->dwEndLogTime, 
			0, pRoleMoneyUserData->nBeginMoney0, pRoleMoneyUserData->nEndMoney0, FALSE);
 		LOG_PROCESS_ERROR(nRetCode);
 	}

	if (nBeginMoney1 == nEndMoney1)
	{
		nRetCode = CCashAccounting::GetInstance()._WriteLog(pRoleMoneyUserData->dwRoleID, pRoleMoneyUserData->szRoleName, pRoleMoneyUserData->dwBeginLogTime, pRoleMoneyUserData->dwEndLogTime,
			1, pRoleMoneyUserData->nBeginMoney1, pRoleMoneyUserData->nEndMoney1, TRUE);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else
	{
		nRetCode = CCashAccounting::GetInstance()._WriteLog(pRoleMoneyUserData->dwRoleID, pRoleMoneyUserData->szRoleName, pRoleMoneyUserData->dwBeginLogTime, pRoleMoneyUserData->dwEndLogTime, 
			1, pRoleMoneyUserData->nBeginMoney1, pRoleMoneyUserData->nEndMoney1, FALSE);
		LOG_PROCESS_ERROR(nRetCode);
	}

 	return;
 Exit0:
 	return;
}
 
 BOOL CCashAccounting::_WriteLog(INT32 dwRoleID, char* pRoleName, UINT32 dwBeginTime, UINT32 dwEndTime, INT8 byMoneyType, INT32 nBeginMoney, INT32 nEndMoney, INT32 nResult)
{
 	char szMessage[256];
 	INT32 nMessageSize = 0;
	char szBeginTime[128];
	char szEndTime[128];

 	memset(szMessage, 0, sizeof(szMessage));
 	memset(szBeginTime, 0, sizeof(szBeginTime));
 	memset(szEndTime, 0, sizeof(szEndTime));

	time_t llBeginTime = (time_t)dwBeginTime;
	struct tm* stBeginTime = localtime(&llBeginTime);

	snprintf(szBeginTime, sizeof(szBeginTime), "%d-%d-%d %d:%d:%d", (stBeginTime->tm_year+1900), (stBeginTime->tm_mon+1), stBeginTime->tm_mday, 
		stBeginTime->tm_hour, stBeginTime->tm_min, stBeginTime->tm_sec);

	time_t llEndTime = (time_t)dwEndTime;
	struct tm* stEndTime = localtime(&llEndTime);
 
	snprintf(szEndTime, sizeof(szEndTime), "%d-%d-%d %d:%d:%d", (stEndTime->tm_year+1900), (stEndTime->tm_mon+1), stEndTime->tm_mday, 
		stEndTime->tm_hour, stEndTime->tm_min, stEndTime->tm_sec);

 	if (nResult)
 	{
		snprintf(szMessage, sizeof(szMessage), "RoleID: %d\tRoleName:%10s\tBeginTime:%s\tEndTime:%s\tMoneyType:%d\t\tBeginMoney:%10d\tEndMoney:%10d\tMoneyChangeCount:%10d\tAccountint Result: Success!\n", 
			dwRoleID, pRoleName, szBeginTime, szEndTime, byMoneyType, nBeginMoney, nEndMoney, (nEndMoney-nBeginMoney));
 	}
 	else
 	{
		snprintf(szMessage, sizeof(szMessage), "RoleID: %d\tRoleName:%10s\tBeginTime:%s\tEndTime:%s\tMoneyType:%d\t\tBeginMoney:%10d\tEndMoney:%10d\tMoneyChangeCount:%10d\tAccountint Result: Fail!\n", 
			dwRoleID, pRoleName, szBeginTime, szEndTime, byMoneyType, nBeginMoney, nEndMoney, (nEndMoney-nBeginMoney));
	}
 
 	nMessageSize = (INT32)strlen(szMessage);
 
 	fwrite(szMessage, nMessageSize, 1, m_pLogHandler);
 
 	fflush(m_pLogHandler);
 
 	return TRUE;
 }