#include "stdafx.h"
#include "fcm.h"
#include "FCMsdkBase.h"
#include "server_config.h"
#include "client/usermgr.h"
#include "role_data.h"
#include "onlinerole/online_role_data_mgr.h"
#include "message_handler.h"

int func_callbk(const char* szUserID, const char* szRoleID, int iOnlineMinutes, int iOfflineMinutes);
void func_switch(int iNeedFCM);
void func_Querycallback(const char* szUserID, const char* szRoleID, int istate, int iOnlineMinutes, int iOfflineMinutes);

BOOL CFcmMgr::Init()
{
    bool bRes;
    BOOL bRet;

    LOG_PROCESS_ERROR(g_ServerConfig.MS.bFcmEnable);

    INF("Starting FCM...");

    m_poFCM = CreateSDKInstance();
    LOG_PROCESS_ERROR(m_poFCM);

    bRes = m_poFCM->initFCMSDK(FCM_APPID, g_ServerConfig.Common.nAreaID, 0, func_callbk, func_switch, func_Querycallback);
    LOG_PROCESS_ERROR(bRes);

    bRet = m_callback_pool.Init(g_ServerConfig.MS.nFcmCallbackCount);
    LOG_PROCESS_ERROR(bRet);

    bRet = m_callback_list.Init(g_ServerConfig.MS.nFcmCallbackCount);
    LOG_PROCESS_ERROR(bRet);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CFcmMgr::UnInit()
{
    BOOL bRet;

    LOG_PROCESS_ERROR(g_ServerConfig.MS.bFcmEnable);

    bRet = m_callback_pool.UnInit();
    LOG_PROCESS_ERROR(bRet);

    bRet = m_callback_list.UnInit();
    LOG_PROCESS_ERROR(bRet);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CFcmMgr::MainLoop()
{
    FCM_CALLBACK* cb = (FCM_CALLBACK*)m_callback_list.Pop();
    while (cb)
    {
        MS_USER* user = CUserMgr::GetInstance().FindUserByUserName(cb->szUserName);
        if (user && !user->bAdult)
        {
            MS_ONLINE_ROLE_DATA* role = NULL;

            if (cb->nOnlineMinutes >= 300)
                user->byFcmState = 2;// fcmsNone;
            else if (cb->nOnlineMinutes >= 180)
                user->byFcmState = 1;// fcmsHalf;
            else
                user->byFcmState = 0;// fcmsFull;

            role = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(user->dwCurRoleID);
            if (role)
            {

                CMessageHandler::GetInstance().DoGSFcmState(role->dwGSSessionID, role->pRoleData->dwRoleID, user->byFcmState);

                CMessageHandler::GetInstance().DoClientFcmState(role->dwCliSessionID, cb->nOnlineMinutes, cb->nOfflineMinutes);
            }
        }

        m_callback_pool.Delete(cb);
        cb = (FCM_CALLBACK*)m_callback_list.Pop();
    }

    return TRUE;
}

void CFcmMgr::SetOnline(const char* szUserID, UINT32 dwIP)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(g_ServerConfig.MS.bFcmEnable);

    nRetCode = m_poFCM->FCMIDOnline(szUserID, "a", inet_ntoa(*(in_addr*)(&dwIP)));
    LOG_PROCESS_ERROR(nRetCode == 1010);

Exit0:
    return;
}

void CFcmMgr::SetOffline(const char* szUserID, UINT32 dwIP)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(g_ServerConfig.MS.bFcmEnable);

    nRetCode = m_poFCM->FCMIDOffline(szUserID, "a", inet_ntoa(*(in_addr*)(&dwIP)));
    LOG_PROCESS_ERROR(nRetCode == 1010);

Exit0:
    return;
}

void CFcmMgr::QueryFcmState(const char* szUserID, UINT32 dwIP)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(g_ServerConfig.MS.bFcmEnable);

    nRetCode = m_poFCM->FCMQueryStateNoBlock(szUserID, "a", inet_ntoa(*(in_addr*)(&dwIP)));
    LOG_PROCESS_ERROR(nRetCode == 1010);

Exit0:
    return;
}

BOOL CFcmMgr::PushCallback(const char* szUserID, INT32 nOnlineMinutes, INT32 nOfflineMinutes)
{
    BOOL bRet;

    FCM_CALLBACK* cb = m_callback_pool.New();
    LOG_PROCESS_ERROR(cb);

    strxcpy(cb->szUserName, szUserID, USER_NAME_LEN);
    cb->nOnlineMinutes = nOnlineMinutes;
    cb->nOfflineMinutes = nOfflineMinutes;

    bRet = m_callback_list.Push(cb);
    LOG_PROCESS_ERROR(bRet);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CFcmMgr::PopCallback(FCM_CALLBACK& cb)
{
    return TRUE;
}

int func_callbk(const char* szUserID, const char* szRoleID, int iOnlineMinutes, int iOfflineMinutes)
{
    BOOL bRet = CFcmMgr::GetInstance().PushCallback(szUserID, iOnlineMinutes, iOfflineMinutes);
    LOG_PROCESS_ERROR(bRet);

Exit0:
    DBG("func_callbk: %s, %d, %d", szUserID, iOnlineMinutes, iOfflineMinutes);
    return 0;
}

void func_switch(int iNeedFCM)
{
    DBG("func_switch: %d", iNeedFCM);
}

void func_Querycallback(const char* szUserID, const char* szRoleID, int istate, int iOnlineMinutes, int iOfflineMinutes)
{
    BOOL bRet = CFcmMgr::GetInstance().PushCallback(szUserID, iOnlineMinutes, iOfflineMinutes);
    LOG_PROCESS_ERROR(bRet);

Exit0:
    DBG("func_Querycallback: %s, %d, %d", szUserID, iOnlineMinutes, iOfflineMinutes);
}
