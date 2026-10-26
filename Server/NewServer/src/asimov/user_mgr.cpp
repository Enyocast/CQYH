#include "stdafx.h"

#include "user_mgr.h"
#include "lua_script.h"
#include "asimov.h"
#include "robot_message_handler.h"
#include "game_world.h"

extern INet* g_pNet;
extern CPacketAllocator g_PacketAllocator;

CUserMgr CUserMgr::ms_Instance;

CUserMgr::CUserMgr()
{
    m_nUserIndex = 0;
}

CUserMgr::~CUserMgr()
{
    UnInit();
}

BOOL CUserMgr::Init(void)
{
    INT32 nRetCode = 0;

    nRetCode = m_oUserPool.Init(16);
    LOG_PROCESS_ERROR(nRetCode);

    m_qwChatSize = 0;
    m_dwStartChatTick = 0;

	for (INT32 i = 0; i < sizeof(m_aGroupUsers) / sizeof(m_aGroupUsers[0]); ++i)
	{
		m_aGroupUsers[i].clear();
	}
    return TRUE;
Exit0:
    return FALSE;
}

BOOL CUserMgr::UnInit(void)
{
    INT32 nRetCode = 0;

	for (INT32 i = 0; i < sizeof(m_aGroupUsers) / sizeof(m_aGroupUsers[0]); ++i)
	{
		m_aGroupUsers[i].clear();
	}

    for (MAP_ID_2_USER::iterator it = m_mapUser.begin();
        it != m_mapUser.end(); ++it)
    {
        CUser* poUser = it->second;
        LOG_CHECK_ERROR(poUser);

        nRetCode = DelUser(poUser);
        LOG_CHECK_ERROR(nRetCode);
    }

    for (MAP_ID_2_USER::iterator it = m_mapUser.begin();
        it != m_mapUser.end(); ++it)
    {
        CUser* poUser = it->second;
        LOG_CHECK_ERROR(poUser);

        if (poUser)
        {
            nRetCode = poUser->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            m_oUserPool.Delete(poUser);
        }
    }

    m_mapUser.clear();
    m_mapName2User.clear();
    m_mapCName2User.clear();
    m_oUserPool.UnInit();
    return TRUE;
}

BOOL CUserMgr::MainLoop( CLuaScript* poScript )
{
    INT32 nRetCode = 0;
    UINT64 qwCurrentTick = GetTickCountEx();

    for (MAP_ID_2_USER::iterator it = m_mapUser.begin(); it != m_mapUser.end();)
    {
        MAP_ID_2_USER::iterator itNext = it;
        ++itNext;

        CUser* poUser = it->second;
        LOG_PROCESS_ERROR(poUser);

		//if (poUser->IsConnected() && g_Random(10) == 0)
		//{
		//	nRetCode = poUser->SendRandomMessage();
		//	LOG_CHECK_ERROR(nRetCode);
		//}

        if (poUser->IsDeleted() && !poUser->IsConnected() && poUser->GetCoroutineName()[0] == '\0' && !poUser->IsWaitLoginCallback())
        {
            // call script
            if ( poScript )
            {
                if ( poScript->IsFuncExist(FUNC_ON_ROLE_DELETE))
                {
                    BOOL nReSult = FALSE;
                    nRetCode = poScript->CallFunction(FUNC_ON_ROLE_DELETE, "o:d", poUser, "CUser", &nReSult );
                    LOG_CHECK_ERROR( nRetCode );
                }
            }

            if (poUser->GetPlayingRole())
                asimov::GetInstance().RemovePlayingRole(poUser->GetPlayingRole());

            // clear roles
            CRole** pRoleList = poUser->GetRoleList();
            for (INT32 nIndex = 0; nIndex < MAX_ROLE_PER_USER; nIndex++)
            {
                if (pRoleList[nIndex] == NULL)
                    continue;

                CScene* pRoleScene = pRoleList[nIndex]->GetScene();
                if (pRoleScene != NULL)
                    pRoleScene->RemoveRole(pRoleList[nIndex]);

                asimov::GetInstance().DeleteRoleWidget(pRoleList[nIndex]);

                nRetCode = pRoleList[nIndex]->UnInit();
                LOG_CHECK_ERROR(nRetCode);

                nRetCode = CGameWorld::GetInstance().DelRole(pRoleList[nIndex]);
                LOG_CHECK_ERROR(nRetCode);

                pRoleList[nIndex] = NULL;
            }

            poUser->SetPlayingRole(NULL);

            // clear user
            asimov::GetInstance().RefreshUserWidget(poUser);
            asimov::GetInstance().DeleteUserWidget(poUser);

            INF("CUserMgr::MainLoop found user %s IsDeleted, UnInit it", poUser->GetUserName());
            nRetCode = poUser->UnInit();
            LOG_PROCESS_ERROR(nRetCode);

            nRetCode = m_oUserPool.Delete(poUser);
            LOG_CHECK_ERROR(nRetCode);

            m_mapName2User.erase( poUser->GetUserName() );
            m_mapUser.erase(it);
        }	
        else if(poUser->GetUserState() == usConnected 
                || poUser->GetUserState() == usSelectRole
                || poUser->GetUserState() == usCreatingRole
                || poUser->GetUserState() == usDeletingRole
                || poUser->GetUserState() == usPlaying
                )
        {
            if(poUser->GetPingTick() < qwCurrentTick)
            {
                nRetCode = poUser->DoGatePing(qwCurrentTick);
                LOG_CHECK_ERROR(nRetCode);

                if (poUser->GetUserState() == usPlaying)
                {
                    nRetCode = poUser->DoGamePing(qwCurrentTick);
                    LOG_CHECK_ERROR(nRetCode);
                }
                poUser->SetPingTick(qwCurrentTick + 8000);
            }
        }
        else if(poUser->GetUserState() == usConnectingGT
                && !poUser->CheckHasLoginReq()
                && poUser->CheckPassedAuth() && !poUser->IsWaitLoginCallback())
        {
            poUser->LoginReq();
        }
        it = itNext;
    }

	LOG_PROCESS_ERROR(g_pNet);

    nRetCode = g_pNet->MainLoop();
    LOG_PROCESS_ERROR(nRetCode);

    

    return TRUE;
Exit0:
    return FALSE;
}

CUserMgr& CUserMgr::GetInstance(void)
{
    return ms_Instance;
}

CUser* CUserMgr::NewUser(const char* pcszUserName, const char* pcszUserType, const char* pcszPassword, UINT8 byGroupID)
{
    CUser* poUser = NULL;
    INT32 nRetCode = 0;

	LOG_PROCESS_ERROR( byGroupID >= 0 && byGroupID < MAX_SERVER_GROUP_COUNT );
   
    poUser = m_oUserPool.New();
    LOG_PROCESS_ERROR(poUser);

    m_nUserIndex++;

    nRetCode = poUser->Init(g_pNet, &g_PacketAllocator, m_nUserIndex, pcszUserName, pcszUserType, pcszPassword, byGroupID);
    LOG_PROCESS_ERROR(nRetCode);

    m_mapUser.insert(make_pair(poUser->GetSessionID(), poUser));
    m_mapName2User.insert(make_pair(poUser->GetUserName(), poUser));

    asimov::GetInstance().AddUserWidget(poUser);

	if (byGroupID >= 0 && byGroupID < MAX_SERVER_GROUP_COUNT)
	{
		BOOL bFound = FALSE;
		INT32 nGroupUserNum = m_aGroupUsers[byGroupID].size();
		for (size_t i = 0; i < nGroupUserNum; i++)
		{
			if (m_aGroupUsers[byGroupID][i] == poUser)
			{
				bFound = TRUE;
				break;
			}
		}
		LOG_PROCESS_ERROR(!bFound);
	}
	m_aGroupUsers[byGroupID].push_back(poUser);

    return poUser;
Exit0:
    if(poUser)
    {
        poUser->UnInit();
        m_oUserPool.Delete(poUser);
    }

    return NULL;
}

CUser* CUserMgr::RandAnotherUser(CUser* poSelfUser)
{
	CUser* poResult = NULL;
	MAP_ID_2_USER::iterator it;
	INT32 nRandValue = 0;
	INT32 nGroupUserNum = 0;

	UINT8 byGroupID = poSelfUser->GetGroupID();
	LOG_PROCESS_ERROR(byGroupID >= 0 && byGroupID < MAX_SERVER_GROUP_COUNT);

	nGroupUserNum = m_aGroupUsers[byGroupID].size();
	LOG_PROCESS_ERROR(nGroupUserNum > 0);
	if (nGroupUserNum == 1)
	{
		LOG_PROCESS_ERROR(m_aGroupUsers[byGroupID][0] == poSelfUser);
	}

	if (nGroupUserNum > 1)
	{
		nRandValue = g_Random(nGroupUserNum);

		poResult = m_aGroupUsers[byGroupID][nRandValue];

		if (poResult == poSelfUser)
		{
			poResult = NULL;

			nRandValue = (nRandValue + 1) % nGroupUserNum;
			poResult = m_aGroupUsers[byGroupID][nRandValue];
		}
	}

	return poResult;
Exit0:
	return NULL;
}

CUser* CUserMgr::FindUser(INT32 nUserID)
{
    MAP_ID_2_USER::iterator it;
    CUser* poUser = NULL;

    it = m_mapUser.find(nUserID);
    LOG_PROCESS_ERROR(it != m_mapUser.end());

    poUser = it->second;
    LOG_PROCESS_ERROR(poUser != NULL);
         
    return poUser;
Exit0:
    return NULL;
}

CUser* CUserMgr::FindUserByName(const char* szUserName)
{
    MAP_STR_2_USER::iterator it;
    CUser* poUser = NULL;

    it = m_mapName2User.find(szUserName);
    LOG_PROCESS_ERROR(it != m_mapName2User.end());

    poUser = it->second;
    LOG_PROCESS_ERROR(poUser != NULL);

    return poUser;
Exit0:
    return NULL;
}

CUser* CUserMgr::FindUserByCoroutineName(const char* pcszCoroutineName)
{
    MAP_CNAME_2_USER::iterator it;
    CUser* poUser = NULL;

    it = m_mapCName2User.find(pcszCoroutineName);
    LOG_PROCESS_ERROR(it != m_mapCName2User.end());

    poUser = it->second;
    LOG_PROCESS_ERROR(poUser != NULL);

    return poUser;
Exit0:
    return NULL;
}

BOOL CUserMgr::AttachUserToCoroutine(CUser* poUser, const char* pcszCoroutineName)
{
    MAP_CNAME_2_USER::iterator it;

    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(pcszCoroutineName);

    it = m_mapCName2User.insert(std::make_pair(pcszCoroutineName, poUser));
    LOG_PROCESS_ERROR(it != m_mapCName2User.end());

    return TRUE;
Exit0:
    return FALSE;
}

void CUserMgr::DetachUserFromCoroutine(const char* pcszCoroutineName)
{
    LOG_PROCESS_ERROR(pcszCoroutineName);
    m_mapCName2User.erase(pcszCoroutineName);

Exit0:
    return;
}

BOOL CUserMgr::DelUser(CUser* poUser)
{
    LOG_PROCESS_ERROR(poUser);

	if (poUser->IsConnected()) //(poUser->GetSocketSession())
	{
		LOG_PROCESS_ERROR(poUser->GetSocketSession());
		poUser->GetSocketSession()->Close();
	}

	// no more to choose as another user
	UINT8 byGroupID = poUser->GetGroupID();
	LOG_CHECK_ERROR(byGroupID >= 0 && byGroupID < MAX_SERVER_GROUP_COUNT);
	if (byGroupID >= 0 && byGroupID < MAX_SERVER_GROUP_COUNT)
	{
		BOOL bFound = FALSE;
		INT32 nGroupUserNum = m_aGroupUsers[byGroupID].size();
		for (size_t i = 0; i < nGroupUserNum; i++)
		{
			if (m_aGroupUsers[byGroupID][i] == poUser)
			{
				m_aGroupUsers[byGroupID][i] = m_aGroupUsers[byGroupID].back();
				m_aGroupUsers[byGroupID].pop_back();

				bFound = TRUE;
				break;
			}
		}
		LOG_CHECK_ERROR(bFound);
	}

    poUser->SetDeleteFlag();

    return TRUE;
Exit0:
    return FALSE;
}
