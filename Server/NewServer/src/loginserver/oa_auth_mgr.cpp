#include "stdafx.h"
#include "oa_auth_mgr.h"
#include "server_config.h"
#include "ls_message_handler.h"

COAAuthMgr COAAuthMgr::ms_Instance;

int SNDACALLBACK AuthorizeCallback(EMsgDirection eMsgType, unsigned int dwRpcID, int nResult, const ISDOCommonMsg* pResponse);

COAAuthMgr::COAAuthMgr()
{
	m_poOAAuth = NULL;
}

COAAuthMgr::~COAAuthMgr()
{
    UnInit();
}

BOOL COAAuthMgr::Init(VOID)
{
    INT32 nRetCode = 0;
	char szOAConfigFullPath[256];

	nRetCode = m_AuthingUserPool.Init(g_ServerConfig.LS.nInitAuthCount);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = m_lstAuthorizedUser.Init(g_ServerConfig.LS.nTotalAuthingCount);
	LOG_PROCESS_ERROR(nRetCode);

	m_poOAAuth = sdoCreateCommonHandler();
	LOG_PROCESS_ERROR(m_poOAAuth);
	
	snprintf(szOAConfigFullPath, 256, "loginserver\\%s", g_ServerConfig.LS.szConfigFile);
    INF("Starting Auth System Using Config: %s", szOAConfigFullPath);
	nRetCode = m_poOAAuth->Initialize(szOAConfigFullPath);
	LOG_PROCESS_ERROR(nRetCode == 0);
	
	m_poOAAuth->RegisterCallback("VerifyServer", AuthorizeCallback);
	
	return TRUE;
Exit0:
	nRetCode = UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return FALSE;
}

BOOL COAAuthMgr::UnInit(VOID)
{
    INT32 nRetCode = 0;

	while(!m_lstAuthorizedUser.IsEmpty())
	{
		SOAAuthorizedUser* poAutherUser = (SOAAuthorizedUser*)m_lstAuthorizedUser.Pop();
		if(poAutherUser)
			SAFE_DELETE(poAutherUser);
	}

	nRetCode = m_lstAuthorizedUser.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = m_AuthingUserPool.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	if(m_poOAAuth)
	{
		m_poOAAuth->Uninitialize();
		m_poOAAuth->Release();
		m_poOAAuth = NULL;
	}
	
	return TRUE;
}

COAAuthMgr& COAAuthMgr::GetInstance(VOID)
{
    return ms_Instance;
}

BOOL COAAuthMgr::MainLoop()
{	
	INT32 nRetCode = 0;
	SOAAuthingUser* pstAuthingUser = NULL;
	SOAAuthorizedUser* pstAuthorizedUser = NULL;
	while(!m_lstAuthorizedUser.IsEmpty())
	{
		INT32 nError = errLoginAuthFailed;

		pstAuthorizedUser = (SOAAuthorizedUser*)m_lstAuthorizedUser.Pop();
		LOG_PROCESS_ERROR(pstAuthorizedUser);
		
		pstAuthingUser = m_AuthingUserPool.Find(pstAuthorizedUser->dwRpcID);
		LOG_PROCESS_ERROR(pstAuthingUser);

		if (pstAuthorizedUser->nError == 0)
			nError = errSuccess;
		else
			INF("session <%08X> oa authorized failed, error code %d", pstAuthingUser->dwSessionID, pstAuthorizedUser->nError);

		// Mobile client
		if (IS_MOBILE_CLIENT(pstAuthingUser->dwSessionID))
		{
			nRetCode = CLSMessageHandler::GetInstance().DoMGLoginAck(pstAuthingUser->dwSessionID, nError,
				pstAuthingUser->szOASessionID, pstAuthorizedUser->szSNDAID, pstAuthorizedUser->szPGT,
				strcmp(pstAuthorizedUser->szAdult, "Y") == 0 ? 1 : 0, 0, NULL);
			LOG_CHECK_ERROR(nRetCode);

			INF("User from session <%08X> get SNDA ID %s, and DoMGLoginAck", pstAuthingUser->dwSessionID, pstAuthorizedUser->szSNDAID);
		}
		// PC client
		else
		{
			nRetCode = CLSMessageHandler::GetInstance().DoGTLoginAck(pstAuthingUser->dwSessionID, nError,
				pstAuthingUser->szOASessionID, pstAuthorizedUser->szSNDAID, pstAuthorizedUser->szPGT,
				strcmp(pstAuthorizedUser->szAdult, "Y") == 0 ? 1 : 0, 0, NULL);
			LOG_CHECK_ERROR(nRetCode);

			INF("User from session <%08X> get SNDA ID %s, and DoGTLoginAck", pstAuthingUser->dwSessionID, pstAuthorizedUser->szSNDAID);
		}
	
		nRetCode = m_AuthingUserPool.Delete(pstAuthingUser);
		LOG_CHECK_ERROR(nRetCode);
	}
	
	return TRUE;
Exit0:
	return FALSE;
}

BOOL COAAuthMgr::DoAuthorize(INT32 nSessionID, const CHAR* pcszAuthingStr)
{
	INT32 nRetCode = 0;
	ISDOCommonMsg* pMsg = NULL;
	UINT32 dwRpcID = 0;
	SOAAuthingUser* pAuthUser = NULL;

	LOG_PROCESS_ERROR(pcszAuthingStr);
	LOG_PROCESS_ERROR(m_poOAAuth);

	dwRpcID = m_poOAAuth->GetRpcId();
	pAuthUser = m_AuthingUserPool.New(dwRpcID);
	LOG_PROCESS_ERROR(pAuthUser);
	pAuthUser->dwSessionID = nSessionID;
    strxcpy(pAuthUser->szOASessionID, pcszAuthingStr, OA_SESSION_ID_LEN);

	pMsg = sdoCreateMsg(E_REQUEST, "VerifyServer.ReserveNotify");
	LOG_PROCESS_ERROR(pMsg);
	
	pMsg->SetValue("sessionId", pcszAuthingStr);
	pMsg->SetValue("areaId", g_ServerConfig.Common.nAreaID);
	pMsg->SetValue("appId", SNDA_APPID);
	
	nRetCode = m_poOAAuth->ASyncSendMsg(pMsg, dwRpcID);
	LOG_PROCESS_ERROR(nRetCode == 0);

	pMsg->Release();

	return TRUE;
Exit0:
	
	if(pMsg)
		pMsg->Release();

	return FALSE;
}

VOID COAAuthMgr::OnAuthorized(SOAAuthorizedUser* pstAuthorizedUser)
{
	INT32 nRetCode = 0;
	LOG_PROCESS_ERROR(pstAuthorizedUser);

	nRetCode = m_lstAuthorizedUser.Push((VOID*)pstAuthorizedUser);
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return ;
}

#define dbg_auth_str(a) pAuthUser->GetValue(a, &pszMsg); DBG("%s: %s", a, pszMsg);
#define dbg_auth_int(a) pAuthUser->GetValue(a, &debug_int); DBG("%s: %d", a, debug_int);
int SNDACALLBACK AuthorizeCallback(EMsgDirection eMsgType, unsigned int dwRpcID, int nResult, const ISDOCommonMsg* pResponse)
{
	SOAAuthorizedUser* pstAuthorizedUser = NULL;
	char* pszMsg = NULL;
	ISDOCommonMsg* pAuthUser = NULL;
	
	LOG_PROCESS_ERROR(pResponse);

	pAuthUser = (ISDOCommonMsg*)pResponse;
	LOG_PROCESS_ERROR(pAuthUser);

	pstAuthorizedUser = new SOAAuthorizedUser;
	LOG_PROCESS_ERROR(pstAuthorizedUser);

    memset(pstAuthorizedUser, 0, sizeof(SOAAuthorizedUser));

	pstAuthorizedUser->dwRpcID = dwRpcID;
	pstAuthorizedUser->nError = nResult;

	pAuthUser->GetValue("sndaId", &pszMsg);
	if(pszMsg != NULL)
	{
		strxcpy(pstAuthorizedUser->szSNDAID, pszMsg, USER_NAME_LEN);
		pszMsg = NULL;
	}

	pAuthUser->GetValue("adult", &pszMsg);
	if(pszMsg != NULL)
	{
		strxcpy(pstAuthorizedUser->szAdult, pszMsg, OA_ADULT_FIELD_LEN);
		pszMsg = NULL;
	}

	pAuthUser->GetValue("applingAdult", &pszMsg);
	if(pszMsg != NULL)
    {
		strxcpy(pstAuthorizedUser->szApplingAdult, pszMsg, OA_ADULT_FIELD_LEN);
        pszMsg = NULL;
    }

    pAuthUser->GetValue("proxyTicket", &pszMsg);
    if(pszMsg != NULL)
    {
        strxcpy(pstAuthorizedUser->szPGT, pszMsg, OA_PGT_FIELD_LEN);
        pszMsg = NULL;
    }

	COAAuthMgr::GetInstance().OnAuthorized(pstAuthorizedUser);

Exit0:
	return 0;
}
