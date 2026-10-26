#include "stdafx.h"

#include "ms_session_mgr.h"
#include "t2m_message.h"
#include "m2t_message.h"
#include "common_message.h"
#include "m2g_message.h"
#include "m2d_message.h"

#include "time_ex.h"
#include "statis_info.h"
#include "game_world_config.h"
#include "server_config.h"
#include "new_role_config.h"

#include "message_handler.h"
#include "client/usermgr.h"
#include "onlinerole/online_role_data_mgr.h"
#include "scene/scenemgr.h"
#include "scene_data.h"
#include "role_db_def.h"
#include "role_data.h"
#include "team/team.h"
#include "gm/gm_manager.h"
#include "manageserver.h"
#include "role_data_mgr.h"
#include "fcm/fcm.h"
#include "real_money_shop/oa_bill_mgr.h"

using namespace InternalMessage;

VOID CMessageHandler::OnGTEnterGate(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    T2M_ENTER_GATE* pMsg = (T2M_ENTER_GATE*)pPacketBuffer;
    MS_USER* poUser = NULL;

    UINT32 dwOldClientSessionID = CUserMgr::GetInstance().FindSessionIDByUserName(pMsg->szUserName);
    if (dwOldClientSessionID > 0)
    {
        MS_USER* pOldUser = CUserMgr::GetInstance().FindUserBySessionID(dwOldClientSessionID);
        LOG_PROCESS_ERROR(pOldUser);
		INF("user[%s] repeat Login, old user sessionID<%08X> state %d, new user[%s], new user sessionID<%08x>", 
            pOldUser->szUserName, dwOldClientSessionID, pOldUser->eState, pMsg->szUserName, pMsg->dwClientSessionID );

        // 账号重复登录被踢下线
		nRetCode = DoErrorNotify(pOldUser->dwCliSessionID, errLoginRepeatKicked, 0, 0);
		LOG_PROCESS_ERROR(nRetCode);

        KICK_USER(pOldUser->dwCliSessionID, ktImmediately);

        // 账号重复登录
        nRetCode = DoGTEnterGateAck(pMsg->dwClientSessionID, errLoginRepeat);
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        // 玩家被锁定，请稍后再试
		if (CGMManager::GetInstance().IsUserLocked(pMsg->szUserName))
		{
			nRetCode = DoGTEnterGateAck(pMsg->dwClientSessionID, errLoginLocked);
			LOG_PROCESS_ERROR(nRetCode);
		}
		else
		{
			INT32 nServerGroup = GET_GROUP_INDEX_FROM_SESSION_ID(pMsg->dwClientSessionID);
			INT32 nUserCount = CSceneMgr::GetInstance().GetSceneTempRoleCount(nServerGroup, g_NewRoleConfig.nSceneTempID);
			INT32 nWaitUserCount = CUserMgr::GetInstance().GetWaitUserCount(nServerGroup);

			poUser = CUserMgr::GetInstance().NewUser(pMsg->szUserName, pMsg->dwClientSessionID, pMsg->dwIpAddr,
				pMsg->szMac, pMsg->szOASessionID, pMsg->szPGT, pMsg->bAdult, pMsg->bIpWhiteList, pMsg->bUserWhiteList);
			LOG_PROCESS_ERROR(poUser != NULL);

			if (nUserCount >= g_ServerConfig.GroupConfig[nServerGroup].nMaxRoleCount && !poUser->bIpWhiteList)
			{
				poUser->eState = USER_STATE_AUTHED;

				nRetCode = DoGTEnterGateAck(pMsg->dwClientSessionID, errLoginTooManyOnlineRole);
				LOG_PROCESS_ERROR(nRetCode);

				CUserMgr::GetInstance().PushWaitUser(nServerGroup, poUser);
			}
			else
			{
				poUser->eState = USER_STATE_QUEUEFINISHED;

				nRetCode = DoGTEnterGateAck(pMsg->dwClientSessionID, errSuccess);
				LOG_PROCESS_ERROR(nRetCode);

				if (g_ServerConfig.MS.bFcmEnable)
					CFcmMgr::GetInstance().SetOnline(pMsg->szUserName, pMsg->dwIpAddr);

                if (g_ServerConfig.MS.bOABillingEnable)
                    COABillMgr::GetInstance().DoQueryAccount(poUser);

                if (g_ServerConfig.MS.bTimeCardEnabled)
                    COABillMgr::GetInstance().DoQueryTime(poUser);
			}

			poUser->dwLoginTime = CManageServer::GetInstance().GetGameTime();

			nRetCode = DoDLLogin(CManageServer::GetInstance().GetGameTime(), GET_GROUP_INDEX_FROM_SESSION_ID(poUser->dwCliSessionID),
				pMsg->szUserName, poUser->dwClientIp);
			LOG_CHECK_ERROR(nRetCode);
		}
	}

	MS_SYS_LOG_SUCCESS(poUser);

    return;
Exit0:
	MS_SYS_LOG_ERROR(poUser);

    nRetCode = DoGTEnterGateAck(pMsg->dwClientSessionID, errLoginUnknownError);
    LOG_CHECK_ERROR(nRetCode);

    if(poUser)
        CUserMgr::GetInstance().DelUser(poUser);

    return;
}

VOID CMessageHandler::OnGTQueryScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32               nRetCode = 0;
    T2M_QUERY_SCENE*    pMsg = (T2M_QUERY_SCENE*)pPacketBuffer;
    MS_USER*            poUser = NULL;
    MS_ONLINE_ROLE_DATA* pstOnlineRole = NULL;
    MS_ROLE_DATA        *pRoleData = NULL;
	INT32				nServerGroupID = GET_GROUP_INDEX_FROM_SESSION_ID(pMsg->dwClientSessionID);

    // 找不到user是有bug
    // 状态不对也是bug
    poUser = CUserMgr::GetInstance().FindUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(poUser->eState == USER_STATE_QUEUEFINISHED);

    pRoleData = CRoleDataMgr::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(pRoleData);

    // 检测gm 冻结角色
	if (pRoleData->dwLoginFrozenTime > CManageServer::GetInstance().GetGameTime())
    {
        nRetCode = CMessageHandler::GetInstance().DoGTQuerySceneAck(pMsg->dwClientSessionID, pMsg->dwRoleID, 0, errLoginRoleFrozen, pRoleData->dwLoginFrozenTime, 0);
        LOG_CHECK_ERROR(nRetCode);
    }
    // 预创建角色
	else if (g_ServerConfig.GroupConfig[nServerGroupID].bPrecreateRole)
	{
        nRetCode = CMessageHandler::GetInstance().DoGTQuerySceneAck(pMsg->dwClientSessionID, pMsg->dwRoleID, 0, errLoginPrecreate, 0, 0);
		LOG_CHECK_ERROR(nRetCode);
	}
    // 启用月卡功能, 判断时间
    else if (g_ServerConfig.MS.bTimeCardEnabled && poUser->nTimeLeft < 0)
    {
        nRetCode = CMessageHandler::GetInstance().DoGTQuerySceneAck(pMsg->dwClientSessionID, pMsg->dwRoleID, 0, errLoginTimeUnknown, 0, 0);
        LOG_CHECK_ERROR(nRetCode);
    }
	else
	{
		INT32 nPosCount = 0;
		const SCENE_DATA*	pcSceneData = NULL;

		poUser->dwCurRoleID = pMsg->dwRoleID;

		pstOnlineRole = COnlineRoleDataMgr::GetInstance().NewOnlineRole(poUser);  // 新连接的客户
		LOG_PROCESS_ERROR(pstOnlineRole);

		pcSceneData = CDataManager<SCENE_DATA>::GetInstance().GetData(pMsg->nSceneTempID);
		if (pcSceneData)
		{
			if (pcSceneData->nLoginJumpSceneTempID != 0)
			{
				pstOnlineRole->PosList[nPosCount].nSceneTempID = pcSceneData->nLoginJumpSceneTempID;
				pstOnlineRole->PosList[nPosCount].nSceneID = 0;
				pstOnlineRole->PosList[nPosCount].nX = pcSceneData->nLoginJumpX;
				pstOnlineRole->PosList[nPosCount].nY = pcSceneData->nLoginJumpY;
				pstOnlineRole->PosList[nPosCount].nZ = pcSceneData->nLoginJumpZ;
				pstOnlineRole->PosList[nPosCount].nFaceDirection = 0;
				nPosCount++;
			}

			pstOnlineRole->PosList[nPosCount].nSceneTempID = pMsg->nSceneTempID;
			pstOnlineRole->PosList[nPosCount].nSceneID = pMsg->nSceneID;
			pstOnlineRole->PosList[nPosCount].nX = pMsg->nX;
			pstOnlineRole->PosList[nPosCount].nY = pMsg->nY;
			pstOnlineRole->PosList[nPosCount].nZ = pMsg->nZ;
			pstOnlineRole->PosList[nPosCount].nFaceDirection = pMsg->wFaceDirection;
			nPosCount++;
		}

		pstOnlineRole->dwSaveTime = pMsg->dwSaveTime;


		pstOnlineRole->PosList[nPosCount].nSceneTempID = pMsg->nReturnSceneTempID;
		pstOnlineRole->PosList[nPosCount].nSceneID = pMsg->nReturnSceneID;
		pstOnlineRole->PosList[nPosCount].nX = pMsg->nReturnX;
		pstOnlineRole->PosList[nPosCount].nY = pMsg->nReturnY;
		pstOnlineRole->PosList[nPosCount].nZ = pMsg->nReturnZ;
		pstOnlineRole->PosList[nPosCount].nFaceDirection = pMsg->wReturnFaceDirection;
		nPosCount++;

		pstOnlineRole->PosList[nPosCount].nSceneTempID = g_GWConfig.nErrorReturnSceneTempID;
		pstOnlineRole->PosList[nPosCount].nSceneID = 1;
		pstOnlineRole->PosList[nPosCount].nX = CONVERT_LENGTH(g_GWConfig.ErrorReturnPos.x);
		pstOnlineRole->PosList[nPosCount].nY = CONVERT_LENGTH(g_GWConfig.ErrorReturnPos.y);
		pstOnlineRole->PosList[nPosCount].nZ = CONVERT_LENGTH(g_GWConfig.ErrorReturnPos.z);
		pstOnlineRole->PosList[nPosCount].nFaceDirection = 0;
		nPosCount++;

		pstOnlineRole->nPosIndex = 0;
		pstOnlineRole->nPosCount = nPosCount;

		nRetCode = _LoginQuerySceneProc(pstOnlineRole, pMsg->dwRoleID);
		LOG_PROCESS_ERROR(nRetCode);
	}

	MS_SYS_LOG_SUCCESS(poUser);
    return;
Exit0:
	MS_SYS_LOG_ERROR(poUser);
    poUser->dwCurRoleID = 0;

    if(pstOnlineRole)
        COnlineRoleDataMgr::GetInstance().DelOnlineRole(pstOnlineRole);

    KICK_USER(pMsg->dwClientSessionID, ktImmediately);

    return;
}

VOID CMessageHandler::OnGTClientShutDown(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode;
    MS_USER* poUser = NULL;

    T2M_CLIENT_SHUTDOWN* pMsg = (T2M_CLIENT_SHUTDOWN*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    // 找不到User是合理异常
    poUser = CUserMgr::GetInstance().FindUserBySessionID(pMsg->dwClientSessionID);
    PROCESS_ERROR(poUser);

    poUser->nShutdownType = pMsg->byShutDownType;

    //pstOnlineRole = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(poUser->dwCurRoleID);
    //if(pstOnlineRole && pstOnlineRole->stRoleData->dwTeamID > 0)
    //{
    //    CTeam* pstTeam = g_TeamMgr.Find(pstOnlineRole->stRoleData->dwTeamID);
    //    LOG_CHECK_ERROR(pstTeam);
    //    if(pstTeam && pstTeam->GetLeader() == pstOnlineRole->stRoleData->dwRoleID)
    //    {
    //        nRetCode = pstTeam->SelectLeader(FALSE);
    //        LOG_CHECK_ERROR(nRetCode);

    //        if(pstTeam->GetLeader() != pstOnlineRole->stRoleData->dwRoleID)
    //        {
    //            nRetCode = DoClientTeamChangeInfo(pstTeam);
    //            LOG_CHECK_ERROR(nRetCode);

    //            nRetCode = DoGSTeamChangeInfo(pstTeam);
    //            LOG_PROCESS_ERROR(nRetCode);
    //        }
    //    }
    //}
    INF("session<%08X>, user[%s], state[%d] before _ShutdownClient", poUser->dwCliSessionID, poUser->szUserName, poUser->eState );
    nRetCode = _ShutdownClient(poUser);
    LOG_PROCESS_ERROR(nRetCode);

	nRetCode = DoDLLogout(CManageServer::GetInstance().GetGameTime(), GET_GROUP_INDEX_FROM_SESSION_ID(poUser->dwCliSessionID), 
		poUser->szUserName, poUser->dwClientIp);
	LOG_CHECK_ERROR(nRetCode);

	MS_SYS_LOG_SUCCESS(poUser);
    return;
Exit0:

	MS_SYS_LOG_ERROR(poUser);
    return;
}

VOID CMessageHandler::OnGTChangeGSAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    T2M_CHANGE_GS_ACK* pMsg = (T2M_CHANGE_GS_ACK*)pPacketBuffer;
    MS_USER* poUser = NULL;
    MS_ONLINE_ROLE_DATA* pstOnlineRole = NULL;

    // 找不到user和状态不对都是有BUG
    poUser = CUserMgr::GetInstance().FindUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(poUser->eState == USER_STATE_JUMP_ENTER_TARGET);

    pstOnlineRole = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(poUser->dwCurRoleID);
    LOG_PROCESS_ERROR(pstOnlineRole);
    LOG_PROCESS_ERROR(pstOnlineRole->pRoleData);

    
    nRetCode = DoGSChangeScene(pstOnlineRole->dwTargetGSSessionID, pstOnlineRole->dwCliSessionID, pstOnlineRole->pRoleData->dwRoleID);
    LOG_PROCESS_ERROR(nRetCode);

    pstOnlineRole->dwGSSessionID = pstOnlineRole->dwTargetGSSessionID;
	pstOnlineRole->dwTargetGSSessionID = 0;
    poUser->eState = USER_STATE_JUMP_GSREADY;

	MS_SYS_LOG_SUCCESS(poUser);
    return;
Exit0:
	MS_SYS_LOG_ERROR(poUser);
    return;
}

VOID CMessageHandler::OnGTReturnSelectRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode;
    T2M_RETURN_SELECT_ROLE* pMsg = (T2M_RETURN_SELECT_ROLE*)pPacketBuffer;
    MS_USER* poUser = NULL;
    MS_ONLINE_ROLE_DATA* pstOnlineRole = NULL;

    poUser = CUserMgr::GetInstance().FindUserBySessionID(pMsg->dwClientSessionID);
    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(poUser->eState == USER_STATE_INGAME || poUser->eState == USER_STATE_LOGIN_GSREADY || poUser->eState == USER_STATE_JUMP_GSREADY);

    pstOnlineRole = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(poUser->dwCurRoleID);
    LOG_PROCESS_ERROR(pstOnlineRole);
    LOG_PROCESS_ERROR(pstOnlineRole->pRoleData);

    nRetCode = CMessageHandler::GetInstance().DoGSLeaveGS(pstOnlineRole->dwGSSessionID, pstOnlineRole->dwCliSessionID, pstOnlineRole->pRoleData->dwRoleID);
    LOG_PROCESS_ERROR(nRetCode);

    poUser->eState = USER_STATE_EXIT_GS_RETURN;

    return;
Exit0:
    CRI("client (%d) failed to return select role", pMsg->dwClientSessionID);
    return;
}

void CMessageHandler::OnGTRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    T2M_REGISTER* pMsg = (T2M_REGISTER*)pPacketBuffer;
    UINT32 dwGTSessionID = 0;

    SGTSession* pGTSession = (SGTSession*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGTSession);
    LOG_PROCESS_ERROR(CMSSessionMgr::GetInstance().GetServerState() != sgsClosing);

    dwGTSessionID = pGTSession->dwSessionID;

    m_ServerInfo.GT[dwGTSessionID].dwAddr = pMsg->dwInternalAddr;
    m_ServerInfo.GT[dwGTSessionID].wPort = pMsg->wInternalPort;

	m_ServerInfo.GT[dwGTSessionID].byCount = pMsg->byExternalCount;
	for (INT32 nIndex = 0; nIndex < pMsg->byExternalCount; nIndex++)
	{
		m_ServerInfo.GT[dwGTSessionID].dwExternalAddr[nIndex] = pMsg->dwExternalAddr[nIndex];
		m_ServerInfo.GT[dwGTSessionID].wExternalPort[nIndex] = pMsg->wExternalPort[nIndex];
	}

    nRetCode = DoGTRegisterAck(dwGTSessionID);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = DoServerInfo();
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

void CMessageHandler::OnGTReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    UINT32 dwGTSessionID = 0;

    SGTSession* pGTSession = (SGTSession*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGTSession);
    dwGTSessionID = pGTSession->dwSessionID;

    m_ServerInfo.GT[dwGTSessionID].byReady = true;

    INF("GT %d is ready", dwGTSessionID);

    _CheckAllReady();

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();
    return;
}

VOID CMessageHandler::OnGTCloseAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    UINT32 dwGTSessionID = 0;

    SGTSession* pGTSession = (SGTSession*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pGTSession);
    dwGTSessionID = pGTSession->dwSessionID;

    INF("GT %d is closed", dwGTSessionID);

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();
    return;
}

BOOL CMessageHandler::DoGTRegisterAck(UINT32 dwGTSessionID)
{
    INT32 nRetCode = 0;
    M2T_REGISTER_ACK* pMsg = (M2T_REGISTER_ACK*)m_pPacketAllocator->Alloc(sizeof(M2T_REGISTER_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = m2t_register_ack;
    pMsg->dwGTSessionID = dwGTSessionID;

    nRetCode = _SendGT(dwGTSessionID, (PACKET_BUFFER*)pMsg, sizeof(M2T_REGISTER_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
	if(pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CMessageHandler::DoGTEnterGateAck(UINT32 dwClientSessionID, INT32 nErrorCode)
{
    INT32 nRetCode = 0;
    INT32 nSize = sizeof(M2T_ENTER_GATE);
    M2T_ENTER_GATE* pMsg = (M2T_ENTER_GATE*)m_pPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);
    
    pMsg->wMsg = m2t_enter_gate_ack;
    pMsg->nErrCode = nErrorCode;
    pMsg->dwSessionID = dwClientSessionID;

    nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
	if(pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CMessageHandler::DoGTQuerySceneAck(UINT32 dwClientSessionID, UINT32 dwRoleID, UINT32 dwGSSessionID, INT32 nErrorCode, INT32 nErrCodeParam1, INT32 nErrCodeParam2)
{
    INT32 nRetCode = 0;

    M2T_QUERY_SCENE_ACK* pMsg = (M2T_QUERY_SCENE_ACK*)m_pPacketAllocator->Alloc(sizeof(M2T_QUERY_SCENE_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = m2t_query_scene_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;
    pMsg->dwGSSessionID = dwGSSessionID;
	pMsg->nErrorCode = nErrorCode;
    pMsg->nErrCodeParam1 = nErrCodeParam1;
    pMsg->nErrCodeParam2 = nErrCodeParam2;

    nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, sizeof(M2T_QUERY_SCENE_ACK));
    LOG_PROCESS_ERROR(nRetCode);
    
    return TRUE;
Exit0:
	if(pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CMessageHandler::DoGTCloseClientSession(UINT32 dwClientSessionID)
{
    INT32 nRetCode;

    M2T_CLOSE_CLIENT_SESSION* pMsg = (M2T_CLOSE_CLIENT_SESSION*)m_pPacketAllocator->Alloc(sizeof(M2T_CLOSE_CLIENT_SESSION));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = m2t_close_client_session;
    pMsg->dwClientSessionID = dwClientSessionID;

    nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, sizeof(M2T_CLOSE_CLIENT_SESSION));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
	if(pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CMessageHandler::DoGTReturnSelectRole(UINT32 dwClientSessionID)
{
    INT32 nRetCode;

    M2T_RETURN_SELECT_ROLE* pMsg = (M2T_RETURN_SELECT_ROLE*)m_pPacketAllocator->Alloc(sizeof(M2T_RETURN_SELECT_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = m2t_return_select_role;
    pMsg->dwClientSessionID = dwClientSessionID;

    nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, sizeof(M2T_RETURN_SELECT_ROLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
	if(pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CMessageHandler::DoGTChangeGS(UINT32 dwClientSessionID, UINT32 dwGSSessionID)
{
    INT32 nRetCode;
    INT32 nSize = sizeof(M2T_CHANGE_GS);

    M2T_CHANGE_GS* pMsg = (M2T_CHANGE_GS*)m_pPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = m2t_change_gs;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwGSSessionID = dwGSSessionID;

    nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
	if(pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CMessageHandler::DoGTSwitchServerGroupState(INT32 nServerGroupID, BOOL bOpened)
{
	INT32 nRetCode;
	INT32 nSize = sizeof(M2T_SWITCH_SERVER_GROUP_STATE);

	M2T_SWITCH_SERVER_GROUP_STATE* pMsg = (M2T_SWITCH_SERVER_GROUP_STATE*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = m2t_switch_server_group_state;
	pMsg->byServerGroup = (UINT8)nServerGroupID;
	pMsg->byOpened = (UINT8)bOpened;

	nRetCode = _BroadcastGT((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CMessageHandler::DoGTGMCommand(const char* pcszGMCommand)
{
	INT32 nRetCode = 0;
	M2T_GM_COMMAND* pMsg = NULL;
	INT32 nCommandLen = 0;

	LOG_PROCESS_ERROR(pcszGMCommand);

	nCommandLen = strlen(pcszGMCommand) + 1;

	pMsg = (M2T_GM_COMMAND*)m_pPacketAllocator->Alloc(sizeof(M2T_GM_COMMAND) + nCommandLen);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = m2t_gm_command;
	strxcpy(pMsg->szGMCommand, pcszGMCommand, nCommandLen);

	nRetCode = _BroadcastGT((PACKET_BUFFER*)pMsg, sizeof(M2T_GM_COMMAND) + nCommandLen);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

void CMessageHandler::OnGTCheckNewName(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;

    T2M_CHECK_NEW_NAME* pMsg = (T2M_CHECK_NEW_NAME*)pPacketBuffer;

	nRetCode = DoNSNewName(ntRoleName, pMsg->dwClientSessionID, pMsg->szName, pMsg->UserData, sizeof(pMsg->UserData));
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return;
}

BOOL CMessageHandler::DoGTCheckNewName(UINT32 dwClientSessionID, INT32 nErrCode, UINT32 dwID, const char* szName, const char* UserData, UINT32 dwUserDataLen)
{
    INT32 nRetCode;
    INT32 nSize = sizeof(M2T_CHECK_NEW_NAME);

    M2T_CHECK_NEW_NAME* pMsg = (M2T_CHECK_NEW_NAME*)m_pPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = m2t_check_new_name;
    pMsg->dwClientSessionID = dwClientSessionID;
	pMsg->dwID = dwID;
	pMsg->nErrorCode = nErrCode;
	strncpy(pMsg->szName, szName, sizeof(pMsg->szName) - 1);
	memcpy(pMsg->UserData, UserData, dwUserDataLen);

    nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID), (PACKET_BUFFER*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
	if(pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}
