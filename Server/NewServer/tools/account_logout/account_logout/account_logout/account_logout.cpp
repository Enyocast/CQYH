#include <stdio.h>
#include <windows.h>
#include "stdafx.h"
#include "account_logout.h"
#include "log.h"

CAccountLogout CAccountLogout::ms_Instance;

CAccountLogout::CAccountLogout()
{

}

CAccountLogout::~CAccountLogout()
{
	m_Session2UserNamePool.UnInit();
	m_ActualLogoutSessionPool.UnInit();

	m_ActualLogoutSessionList.Clear();
	m_Session2UserNameList.Clear();
}

CAccountLogout& CAccountLogout::GetInstance(void)
{
	return ms_Instance;
}

INT32 CAccountLogout::Init()
{
	INT32 nRetCode = 0;

	m_pFile = NULL;

	nRetCode = m_Session2UserNamePool.Init(65535);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = m_ActualLogoutSessionPool.Init(65535);
	LOG_PROCESS_ERROR(nRetCode);

	m_Session2UserNameList.Clear();
	m_ActualLogoutSessionList.Clear();

	//nRetCode = CLog::GetInstance().Init("account_result", lltAll, (lotConsole + lotFile + lotTrace), FALSE, FALSE, TRUE);
	//LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CAccountLogout::Uninit()
{
	INT32 nRetCode = 0;

	nRetCode = m_Session2UserNamePool.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	m_Session2UserNameList.Clear();

	return TRUE;
}

BOOL CAccountLogout::MainLoop(void)
{
	char szReadLine[MAX_READLINE_LEN];
	FILE* pFile = NULL;
	BASE_LIST_NODE* pNode = NULL;

	INT32 nUserSize = 0;
	INT32 nSessionSize = 0;

	memset(szReadLine, 0, sizeof(szReadLine));

	sprintf(szReadLine, "%s", "..//account_logout//db_file//session.txt");

	// session file

	pFile = fopen(szReadLine, "r+");
	LOG_PROCESS_ERROR(pFile);

	while (fgets(szReadLine, MAX_READLINE_LEN, pFile))
	{
		SESSION_2_USERNAME_NODE* pNewRole = m_Session2UserNamePool.New();
		LOG_PROCESS_ERROR(pNewRole);

		pNewRole->dwSessionID = HextoDec(szReadLine);
		memset(szReadLine, 0, sizeof(szReadLine));
		memset(pNewRole->szName, 0, sizeof(pNewRole->szName));

		pNewRole->pNext = NULL;
		pNewRole->pPrev = NULL;

		m_Session2UserNameList.PushRear(pNewRole);

		nSessionSize++;
	}

	fclose(pFile);
	pFile = NULL;

	// user file

	sprintf(szReadLine, "%s", "..//account_logout//db_file//user.txt");

	// session file

	pFile = fopen(szReadLine, "r+");
	LOG_PROCESS_ERROR(pFile);

	LOG_PROCESS_ERROR(!m_Session2UserNameList.IsEmpty());
	pNode = m_Session2UserNameList.Head().pNext;
	memset(szReadLine, 0, sizeof(szReadLine));

	while (fgets(szReadLine, MAX_READLINE_LEN, pFile))
	{
		LOG_PROCESS_ERROR(pNode != &(m_Session2UserNameList.Rear()));

		DeleteSpace(szReadLine);
		strxcpy(((SESSION_2_USERNAME_NODE*)pNode)->szName, szReadLine, USER_NAME_LEN);
		memset(szReadLine, 0, sizeof(szReadLine));

		nUserSize++;

		pNode = pNode->pNext;
	}

	pNode = NULL;

	fclose(pFile);
	pFile = NULL;

	LOG_PROCESS_ERROR(nUserSize == nSessionSize);

	// already connected from sessionid 2 username

	memset(szReadLine, 0, sizeof(szReadLine));
	sprintf(szReadLine, "%s", "..//account_logout//db_file//logout.txt");

	// session file

	pFile = fopen(szReadLine, "r+");
	LOG_PROCESS_ERROR(pFile);

	memset(szReadLine, 0, sizeof(szReadLine));

	while (fgets(szReadLine, MAX_READLINE_LEN, pFile))
	{
		SESSION_2_USERNAME_NODE* pNewRole = m_ActualLogoutSessionPool.New();
		LOG_PROCESS_ERROR(pNewRole);

		DeleteSpace(szReadLine);

		pNewRole->dwSessionID = HextoDec(szReadLine);
		memset(szReadLine, 0, sizeof(szReadLine));

		pNewRole->pNext = NULL;
		pNewRole->pPrev = NULL;

		m_ActualLogoutSessionList.PushRear(pNewRole);
	}

	fclose(pFile);
	pFile = NULL;

	// load and check dl file

	memset(szReadLine, 0, sizeof(szReadLine));
	sprintf(szReadLine, "%s", "..//account_logout//dl_file//AccountLogin.txt");

	// session file

	pFile = fopen(szReadLine, "r+");
	LOG_PROCESS_ERROR(pFile);

	LOG_PROCESS_ERROR(!m_ActualLogoutSessionList.IsEmpty());
	pNode = m_ActualLogoutSessionList.Head().pNext;

	memset(szReadLine, 0, sizeof(szReadLine));

	while (fgets(szReadLine, MAX_READLINE_LEN, pFile))
	{
		UINT32 dwSessionID = 0;
		BOOL bFound = FALSE;
		DeleteSpace(szReadLine);

		for (BASE_LIST_NODE* pFindNode = m_Session2UserNameList.Head().pNext; pFindNode != &(m_Session2UserNameList.Rear()); pFindNode = pFindNode->pNext)
		{
			if (strcmp(szReadLine, ((SESSION_2_USERNAME_NODE*)pFindNode)->szName) == 0)
			{
				dwSessionID = ((SESSION_2_USERNAME_NODE*)pFindNode)->dwSessionID;
				break;
			}
		}

		if (dwSessionID == 0)
		{
			printf("Can not find UserName : %s in db login file?\n", szReadLine);
		}

		for (BASE_LIST_NODE* pActualNode = m_ActualLogoutSessionList.Head().pNext; pActualNode != &(m_ActualLogoutSessionList.Rear()); pActualNode = pActualNode->pNext)
		{
			if (dwSessionID == (((SESSION_2_USERNAME_NODE*)pActualNode)->dwSessionID))
			{
				printf("Session : %lx, UserName : %s Found!\n", dwSessionID, szReadLine);
				bFound = TRUE;
				break;
			}
		}

		if (!bFound)
		{
			printf("SessionID : %lx in , UserName : %s in dl file, not found in db file?\n", dwSessionID, szReadLine);
		}
		
		bFound = FALSE;
		memset(szReadLine, 0, sizeof(szReadLine));
	}

	fclose(pFile);

	return TRUE;
Exit0:

	if (pFile)
	{
		fclose(pFile);
	}
	return FALSE;
}

UINT32 CAccountLogout::HextoDec(char* pstring)
{
	return strtol(pstring, (char**)NULL, 16);
}

void CAccountLogout::DeleteSpace(char* pstring)
{
	char* pChar = pstring;
	LOG_PROCESS_ERROR(pstring);

	for (INT32 nSize = 0; nSize < MAX_DB_FILE_NAME_LEN; nSize++, pChar++)
	{
		if (*pChar == ' ' || *pChar == '\n' || *pChar == '\t')
		{
			*pChar = '\0';
			break;
		}
	}

	return;
Exit0:
	return;
}