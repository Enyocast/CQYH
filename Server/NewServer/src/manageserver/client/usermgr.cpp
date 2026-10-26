#include "stdafx.h"
#include "usermgr.h"

#include "message_handler.h"
#include "statis_info.h"
#include "server_config.h"
#include "manageserver.h"
#include "fcm/fcm.h"
#include "real_money_shop/oa_bill_mgr.h"
#include "onlinerole/online_role_data_mgr.h"
#include "role_data.h"
#include "game_world_config.h"

#define QUEUE_INFO_INTERVAL	(8)

CUserMgr CUserMgr::ms_Instance;

CUserMgr::CUserMgr()
{
	memset(m_nUserCount, 0, sizeof(m_nUserCount));
	memset(m_UserWaitList, 0, sizeof(m_UserWaitList));
	memset(m_nWaitListSize, 0, sizeof(m_nWaitListSize));
}

CUserMgr::~CUserMgr()
{
	UnInit();
}

CUserMgr& CUserMgr::GetInstance(void)
{
    return ms_Instance;
}


BOOL CUserMgr::Init(UINT32 dwMaxUsers)
{
    INT32 nRetCode = 0;

    nRetCode = m_oUserPool.Init(dwMaxUsers);
    LOG_PROCESS_ERROR(nRetCode);

	memset(m_nUserCount, 0, sizeof(m_nUserCount));

	for (INT32 nServerGroup = 0; nServerGroup < MAX_SERVER_GROUP_COUNT; nServerGroup++)
		m_UserWaitList[nServerGroup].Clear();
	memset(m_nWaitListSize, 0, sizeof(m_nWaitListSize));

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CUserMgr::UnInit(void)
{
    INT32 nRetCode = 0;

    nRetCode = m_oUserPool.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

UINT32 CUserMgr::Count(void)
{
	if (m_mapUser.size() != m_mapUserKey2Session.size())
	{
		CRI("m_mapUser.size() %d is different from m_mapUserKey2Session.size() %d",
			m_mapUser.size(), m_mapUserKey2Session.size());
	}

    return m_mapUser.size();
}

MS_USER* CUserMgr::NewUser(const CHAR* pcszUserName, UINT32 dwClientSessionID, UINT32 dwClientIp,
	const char* pcszMac, const char* pcszOASessionID, const char* pcszPGT, BOOL bAdult, BOOL bIpWhiteList, BOOL bUserWhiteList)
{
    MS_USER* pResult = NULL;
	INT32 nRetCode = 0;
    std::pair<CSessionID2UserMapItr, bool> InsRet1;
    std::pair<CUserKey2SessionIDMapItr, bool> InsRet2;
	MAP_IP_2_SESSION_ID::iterator InsRet3;
	INT32 nServerGroupID = GET_GROUP_INDEX_FROM_SESSION_ID(dwClientSessionID);

    LOG_PROCESS_ERROR(pcszUserName);

    pResult = m_oUserPool.New();
    LOG_PROCESS_ERROR(pResult);

    memset(pResult, 0, sizeof(*pResult));

	strxcpy(pResult->szUserName, pcszUserName, USER_NAME_LEN);
    pResult->dwCliSessionID = dwClientSessionID;
    pResult->eState = USER_STATE_INVALID;
    pResult->qwTimer = (UINT64)(~0);  // lixg
	pResult->nShutdownType = csdtInvalid;
	pResult->dwClientIp = dwClientIp;
	strxcpy(pResult->szMac, pcszMac, MAC_ADDRESS_LEN);
	strxcpy(pResult->szOASessionID, pcszOASessionID, OA_SESSION_ID_LEN);
	strxcpy(pResult->szPGT, pcszPGT, OA_PGT_FIELD_LEN);
	pResult->bAdult = bAdult;
	pResult->byFcmState = 0;
    pResult->bFreeMode = FALSE;
    pResult->dwFreeModeLastCheckTime = 0;
    pResult->nDianquan = -1;
    pResult->nTimeLeft = -1;
    pResult->dwBeginTime = 0;
	pResult->dwLoginTime = 0;
	pResult->bIpWhiteList = bIpWhiteList;
	pResult->bUserWhiteList = bUserWhiteList;

    InsRet1 = m_mapUser.insert(std::make_pair(dwClientSessionID, pResult));
    LOG_PROCESS_ERROR(InsRet1.second);

    InsRet2 = m_mapUserKey2Session.insert(std::make_pair(pResult->szUserName, dwClientSessionID));
    LOG_PROCESS_ERROR(InsRet2.second);

	InsRet3 = m_mapIP2SessionID.insert(std::make_pair(pResult->dwClientIp, dwClientSessionID));
	LOG_PROCESS_ERROR(InsRet3 != m_mapIP2SessionID.end());

	m_nUserCount[nServerGroupID]++;

    INF("new ms user %s <%08X>, total %d", pResult->szUserName, dwClientSessionID, m_mapUser.size() );

    return pResult;
Exit0:
	if (pResult)
	{
		if (InsRet1.second)
			m_mapUser.erase(InsRet1.first);

		if (InsRet2.second)
			m_mapUserKey2Session.erase(InsRet2.first);

		nRetCode = m_oUserPool.Delete(pResult);
		LOG_CHECK_ERROR(nRetCode);
	}

    return NULL;
}

BOOL  CUserMgr::DelUser(MS_USER* poUser)
{    
    MS_USER* pFindUser = NULL;
    UINT32 dwSessionID = 0;
    UINT32 dwRoleID = 0;
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(poUser);

    INF("delete ms user %s <%08X>, total %d", poUser->szUserName, poUser->dwCliSessionID, m_mapUser.size() - 1);

	m_nUserCount[GET_GROUP_INDEX_FROM_SESSION_ID(poUser->dwCliSessionID)]--;

    {
        CUserKey2SessionIDMapItr it;
        
        it = m_mapUserKey2Session.find(poUser->szUserName);
        LOG_CHECK_ERROR(it != m_mapUserKey2Session.end());

        if (it != m_mapUserKey2Session.end())
            m_mapUserKey2Session.erase(it);
    }

    {
        CSessionID2UserMapItr it;

        it = m_mapUser.find(poUser->dwCliSessionID);
        LOG_CHECK_ERROR(it != m_mapUser.end());

        if (it != m_mapUser.end())
            m_mapUser.erase(it);
    }

	{
		for (MAP_IP_2_SESSION_ID::iterator it = m_mapIP2SessionID.lower_bound(poUser->dwClientIp);
			it != m_mapIP2SessionID.upper_bound(poUser->dwClientIp); ++it)
		{
			if (it->second == poUser->dwCliSessionID)
			{
				m_mapIP2SessionID.erase(it);
				break;
			}
		}
	}

    nRetCode = m_oUserPool.Delete(poUser);
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

MS_USER*  CUserMgr::FindUserBySessionID(UINT32 dwSessionID)
{
    CSessionID2UserMapItr itr = m_mapUser.find(dwSessionID);
    if(itr != m_mapUser.end())
        return itr->second;

    return NULL;
}

UINT32  CUserMgr::FindSessionIDByUserName(const CHAR* pcszUserName)
{
    CUserKey2SessionIDMapItr itr = m_mapUserKey2Session.find(pcszUserName);
    if(itr != m_mapUserKey2Session.end())
        return itr->second;

    return 0;
}

MS_USER* CUserMgr::FindUserByUserName(const CHAR* pcszUserName)
{
    UINT32 sessionid = FindSessionIDByUserName(pcszUserName);

    PROCESS_ERROR(sessionid);

    return FindUserBySessionID(sessionid);

Exit0:
    return NULL;
}

void CUserMgr::ProcessQueue(INT32 nServerGroup)
{
	INT32 nRetCode = 0;

	INT32 nUserCount = CUserMgr::GetInstance().GetCountPerGroup(nServerGroup);
	INT32 nWaitUserCount = CUserMgr::GetInstance().GetWaitUserCount(nServerGroup);
	INT32 nRemainCount = g_ServerConfig.GroupConfig[nServerGroup].nMaxRoleCount - (nUserCount - nWaitUserCount);
	if (nRemainCount < g_GWConfig.nLoginRoleCountPer10Second)
		nRemainCount = g_GWConfig.nLoginRoleCountPer10Second;
	nRemainCount = nRemainCount < nWaitUserCount ? nRemainCount : nWaitUserCount;
	if (nRemainCount > 0)
	{
		for (INT32 nIndex = 0; nIndex < nRemainCount; nIndex++)
		{
			BASE_LIST_NODE* pNode = m_UserWaitList[nServerGroup].PopHead();
			MS_USER* poUser = node_cast(MS_USER*, WaitListNode, pNode);

			if (pNode == NULL)
				break;

			poUser->eState = USER_STATE_QUEUEFINISHED;
			RemoveWaitUser(poUser);

			nRetCode = CMessageHandler::GetInstance().DoGTEnterGateAck(poUser->dwCliSessionID, errSuccess);
			LOG_CHECK_ERROR(nRetCode);

			if (g_ServerConfig.MS.bFcmEnable)
				CFcmMgr::GetInstance().SetOnline(poUser->szUserName, poUser->dwClientIp);

            if (g_ServerConfig.MS.bOABillingEnable)
                COABillMgr::GetInstance().DoQueryAccount(poUser);

            if (g_ServerConfig.MS.bTimeCardEnabled)
                COABillMgr::GetInstance().DoQueryTime(poUser);
		}
	}

	INT32 nPos = 1;
	for (BASE_LIST_NODE* pNode = m_UserWaitList[nServerGroup].Head().pNext;
		pNode != &m_UserWaitList[nServerGroup].Rear(); pNode = pNode->pNext)
	{
		MS_USER* poUser = node_cast(MS_USER*, WaitListNode, pNode);
		if (poUser == NULL)
			continue;

		CMessageHandler::GetInstance().DoClientQueueInfo(poUser->dwCliSessionID, m_nWaitListSize[nServerGroup], nPos);
		nPos++;
	}

Exit0:

	return;
}

void CUserMgr::PushWaitUser(INT32 nServerGroup, MS_USER* poUser)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	m_UserWaitList[nServerGroup].PushRear(&poUser->WaitListNode);
	m_nWaitListSize[nServerGroup]++;
Exit0:
	return;
}

void CUserMgr::RemoveWaitUser(MS_USER* poUser)
{
	INT32 nServerGroup = GET_GROUP_INDEX_FROM_SESSION_ID(poUser->dwCliSessionID);
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	CBaseList::Remove(&poUser->WaitListNode);
	m_nWaitListSize[nServerGroup]--;

Exit0:
	return;
}

BOOL CUserMgr::CheckAllUserTimeCard()
{
    struct TraverseUserCheckTimeCard
    {
        UINT32 dwGameTime;
		UINT32 dwCurrentDay;
        BOOL operator()(UINT32 dwClientSessionID, MS_USER* poUser)
        {
			INT32 nRetCode = 0;

            if (g_ServerConfig.MS.bTimeCardEnabled && poUser->eState == USER_STATE_INGAME && !poUser->bFreeMode && poUser->dwBeginTime && poUser->nTimeLeft > 0 && !poUser->bUserWhiteList &&
                (dwGameTime - poUser->dwBeginTime >= g_ServerConfig.MS.nTimeCardBillingPeriod || dwGameTime - poUser->dwBeginTime >= poUser->nTimeLeft))
            {
                MS_ONLINE_ROLE_DATA* role = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(poUser->dwCurRoleID);
                if (role && role->pRoleData->byLevel > g_GWConfig.nFreeRoleLevel)
                {
                    if (dwGameTime - poUser->dwBeginTime >= poUser->nTimeLeft)
                    {
                        COABillMgr::GetInstance().DoSubTime(role, poUser->dwBeginTime, poUser->dwBeginTime + poUser->nTimeLeft, poUser->nTimeLeft, etbtTimeUp);
                    }
                    else
                    {
                        COABillMgr::GetInstance().DoSubTime(role, poUser->dwBeginTime, dwGameTime, dwGameTime - poUser->dwBeginTime, etbtKeepOnline);
                    }
                    poUser->dwBeginTime = dwGameTime;
                }
            }

            if (g_ServerConfig.MS.bTimeCardEnabled && poUser->eState == USER_STATE_INGAME && poUser->bFreeMode &&
                dwGameTime - poUser->dwFreeModeLastCheckTime >= g_GWConfig.nFreeModeCheckTimePeriod)
            {
                COABillMgr::GetInstance().DoQueryTime(poUser);
                poUser->dwFreeModeLastCheckTime = dwGameTime;
            }

			UINT32 dwLoginDay = (poUser->dwLoginTime + CManageServer::GetInstance().GetTimeZone()) / 86400;
			if (dwLoginDay < dwCurrentDay && (poUser->dwCliSessionID % 1024) == (dwGameTime % 1024))
			{
				nRetCode = CMessageHandler::GetInstance().DoDLLogout(CManageServer::GetInstance().GetGameTime(),
					GET_GROUP_INDEX_FROM_SESSION_ID(poUser->dwCliSessionID),
					poUser->szUserName, poUser->dwClientIp);
				LOG_CHECK_ERROR(nRetCode);

				nRetCode = CMessageHandler::GetInstance().DoDLLogin(CManageServer::GetInstance().GetGameTime(),
					GET_GROUP_INDEX_FROM_SESSION_ID(poUser->dwCliSessionID),
					poUser->szUserName, poUser->dwClientIp);
				LOG_CHECK_ERROR(nRetCode);

				poUser->dwLoginTime = dwGameTime;
			}

            return TRUE;
        }
    };

    TraverseUserCheckTimeCard t;
    t.dwGameTime = CManageServer::GetInstance().GetGameTime();
	t.dwCurrentDay = (CManageServer::GetInstance().GetGameTime() + CManageServer::GetInstance().GetTimeZone() - 60) / 86400;

    return TraverseUser(t);
}
