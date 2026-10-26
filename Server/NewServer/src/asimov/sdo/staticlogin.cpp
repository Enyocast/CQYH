#include "stdafx.h"
#include "staticlogin.h"
#include "string_ex.h"
#include "../user_mgr.h"

using namespace std;

const char* URLSTART = "http://cas.sdo.com/authen/staticLogin.jsonp?callback=staticLogin_JSONPMethod";
const char* URLEND = "appId=991002359&areaId=999&serviceUrl=http%3A%2F%2Fwww.sdo.com&productVersion=1.0.0&frameType=1&locale=zh_CN&version=21&authenSource=1&productId=30";

COAStaticLoginMgr COAStaticLoginMgr::ms_Instance;

COAStaticLoginMgr::COAStaticLoginMgr()
{
    m_hSession = NULL;
}

COAStaticLoginMgr::~COAStaticLoginMgr()
{
	UnInit();
}

static BOOL _GetSessionID(char* LoginStr, char* szSessionID)
{
    INT32 nRetCode = 0;
    char* pszStart;
    char* pszEnd;
    char  szTempStr[256] = {0};

    char* pszIndex = strstr(LoginStr, "\"return_code\": ");
    LOG_PROCESS_ERROR(pszIndex);

    pszStart = pszIndex + strlen("\"return_code\": ");
    pszEnd = strchr(pszStart, ',');
    LOG_PROCESS_ERROR(pszEnd);

    strxcpy(szTempStr, pszStart, pszEnd - pszStart + 1);

    nRetCode = atoi(szTempStr);
    LOG_PROCESS_ERROR(nRetCode == 0);

    pszIndex = strstr(LoginStr,"\"ticket\": \"");
    LOG_PROCESS_ERROR(pszIndex);

    pszStart = pszIndex + strlen("\"ticket\": \"");
    pszEnd = strchr(pszStart, '\"');
    LOG_PROCESS_ERROR(pszEnd);
    strxcpy(szSessionID, pszStart, pszEnd - pszStart + 1);

    return TRUE;
Exit0:
    return FALSE;
}

VOID CALLBACK InternetStatusCallback(
  __in HINTERNET hInternet,
  __in_opt DWORD_PTR dwContext,
  __in DWORD dwInternetStatus,
  __in_opt LPVOID lpvStatusInformation,
  __in DWORD dwStatusInformationLength)
{
    INT32 nRetCode = -1;
    char szLoginSessionId[OA_SESSION_ID_LEN] = {0};

    char szFile[10240] = {0};
    char buff[1024] = {0};
    DWORD dwReadSize = 1024;

    CUser* poUser = NULL;
    INTERNET_ASYNC_RESULT* pRes = NULL;
    HINTERNET hFile = NULL;// = hInternet;

    poUser = (CUser*)dwContext;
    LOG_PROCESS_ERROR(poUser);

    if( dwInternetStatus == INTERNET_STATUS_REQUEST_COMPLETE )
    {
        pRes = (INTERNET_ASYNC_RESULT*)lpvStatusInformation;
        LOG_PROCESS_ERROR( pRes );
        hFile = (HINTERNET)pRes->dwResult;

        do 
        {
            nRetCode = InternetReadFile(
                hFile,
                buff,
                1024,
                &dwReadSize);
            strxcat(szFile, buff, 10240);
        } while (nRetCode && dwReadSize);

        LOG_PROCESS_ERROR(poUser->IsWaitLoginCallback());
        LOG_PROCESS_ERROR(!poUser->CheckPassedAuth() && !poUser->CheckHasLoginReq() );

        INF("user %s InternetReadFile, get content:%s", poUser->GetUserName(), szFile);

        nRetCode = _GetSessionID(szFile, szLoginSessionId);
        if(!nRetCode)
        {
            INF("User %s failed parse Auth data", poUser->GetUserName());
            LOG_PROCESS_ERROR( FALSE );
        }

        poUser->SetAuthID(szLoginSessionId, sizeof(szLoginSessionId));
        poUser->EndWaitLoginCallback();

        INF("user %s session<%08x> has gotten auth data!", poUser->GetUserName(), poUser->GetSessionID());
        InternetCloseHandle(hFile);// will result in reenter dwInternetStatus() with INTERNET_STATUS_HANDLE_CLOSING
    }
    else if( dwInternetStatus == INTERNET_STATUS_HANDLE_CLOSING )
    {
        //LOG_CHECK_ERROR( poUser->IsWaitLoginCallback() );
        //poUser->EndWaitLoginCallback();
    }
    else if( dwInternetStatus == INTERNET_STATUS_CONNECTION_CLOSED )
    {
        LOG_CHECK_ERROR( poUser->IsWaitLoginCallback() );
        poUser->EndWaitLoginCallback();
    }

    return;
Exit0:
    if( poUser )
    {
        INF("user %s session<%08x> received auth data failed!", poUser->GetUserName(), poUser->GetSessionID());
        poUser->EndWaitLoginCallback();
    }

    if(hFile)
    {
        InternetCloseHandle(hFile);
    }

    return;
}

BOOL COAStaticLoginMgr::Init(VOID)
{
	INT32 nRetCode = 0;
    INT32 nTimeOut = 20000;
    INTERNET_STATUS_CALLBACK pCallback = NULL;

    m_hSession = InternetOpen("MX", INTERNET_OPEN_TYPE_PRECONFIG, NULL, INTERNET_INVALID_PORT_NUMBER, INTERNET_FLAG_ASYNC);
    LOG_PROCESS_ERROR(m_hSession);

    pCallback = InternetSetStatusCallback(m_hSession, InternetStatusCallback);
    LOG_PROCESS_ERROR(pCallback != INTERNET_INVALID_STATUS_CALLBACK);

    InternetSetOption(m_hSession, INTERNET_OPTION_CONNECT_TIMEOUT, &nTimeOut, sizeof(nTimeOut));
    InternetSetOption(m_hSession, INTERNET_OPTION_SEND_TIMEOUT, &nTimeOut, sizeof(nTimeOut));
    InternetSetOption(m_hSession, INTERNET_OPTION_RECEIVE_TIMEOUT, &nTimeOut, sizeof(nTimeOut));

    return TRUE;
Exit0:
	nRetCode = UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return FALSE;
}

BOOL COAStaticLoginMgr::UnInit(VOID)
{
    if(m_hSession)
        InternetCloseHandle(m_hSession);

	return TRUE;
}

COAStaticLoginMgr& COAStaticLoginMgr::GetInstance(VOID)
{
	return ms_Instance;
}

BOOL COAStaticLoginMgr::_ProcessUrlAndGetSession(CUser* poUser, const char* pcszURL)
{
	INT32 nRetCode = 0;

	//HANDLE 
    HINTERNET hFile = NULL;

    //INF("before InternetOpenUrl URL=%s", pcszURL);
	hFile = InternetOpenUrl(
		m_hSession,
		pcszURL,
		NULL,
		0,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_COOKIES,
		(DWORD_PTR)poUser);
    INF("after InternetOpenUrl URL=%s", pcszURL);

    return TRUE;

Exit0:
	if(hFile)
		InternetCloseHandle(hFile);

	return FALSE;
}

BOOL COAStaticLoginMgr::DoLogin(CUser* poUser)
{
	INT32 nRetCode = 0;
    char szURL[1024] = {0};

    LOG_PROCESS_ERROR(poUser);

	sprintf(szURL, "%s&inputUserId=%s&password=%s&%s", URLSTART, poUser->GetUserName(), poUser->GetPassword(), URLEND);

    poUser->BeginWaitLoginCallback();

	nRetCode = _ProcessUrlAndGetSession(poUser, szURL);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
    if (poUser)
        poUser->EndWaitLoginCallback();
	return FALSE;
}	


//bool SDStaticLogin(char *outbuff,char *userid,char *PassWord)
//{
//
//    string url = "http://test4rift.cas.sdo.com/authen/staticLogin.jsonp?callback=staticLogin_JSONPMethod&inputUserId=";
//    url += userid;
//    url += "&password=";
//    url += PassWord;
//    url += "&appId=122&areaId=999&serviceUrl=http%3A%2F%2Fwww.sdo.com%2Findex.php%3Fr%3Dcommon%2Fuserinfos&productVersion=3.1.0&frameType=3&locale=zh_CN&version=21&tag=20&authenSource=2&productId=2&autoLoginFlag=0&_=1355138263577";
//    string str = GetUrlData(url);
//    if (str.length()==0)
//    {
//        return false;
//    }
//    strcpy(outbuff, str.c_str());
//    return true;
//}

