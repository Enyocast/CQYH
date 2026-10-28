#include "stdafx.h"

#include "c2m_message.h"
#include "m2c_message.h"
#include "g2c_message.h"
#include "t2c_message.h"
#include "b2c_message.h"

#include "robot_message_handler.h"
#include "user_mgr.h"
#include "asimov.h"
#include "role_db_def.h"
#include "game_world.h"

#include "zlib.h"

using namespace ExternalMessage;
CAsimovMessageHandler CAsimovMessageHandler::ms_AsimovInstance;

void CAsimovMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    LOG_PROCESS_ERROR(pSocketSession);
    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;    
    LOG_PROCESS_ERROR(pSocketSession);

    CUser* poUser = (CUser*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(poUser);

    if(poUser->GetUserState() == usConnectingBS)
    {
        poUser->OnBSConnected();
    }
    else if(poUser->GetUserState() == usConnectingGT)
    {
        poUser->OnConnected();
    }

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CAsimovMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    CUser* poUser = NULL;
    MESSAGE_HEADER* pHeader = NULL;
    pHeader = (MESSAGE_HEADER*)pPacketBuffer;

    LOG_PROCESS_ERROR(pSocketSession);
    LOG_PROCESS_ERROR(pPacketBuffer);

    poUser = (CUser*)pSocketSession->GetUserData();
    PROCESS_SUCCESS(!poUser);

	if (poUser->GetEncryptCode() > 0)
	{
		for (INT32 nIndex = sizeof(FLEX_MESSAGE_HEADER); nIndex < dwSize; nIndex++)
		{
			pPacketBuffer[nIndex] ^= poUser->GetEncryptCode();
		}
	}

    if (pHeader->wMsg >= g2c_message_begin && pHeader->wMsg < m2c_message_end)
    {
		if (poUser->GetPlayingRole()) // Ignore the packet if already offline; a server packet may arrive after logout. Allan Tao [5.6.2013]
        {			
			CRobotMessageHandler::GetInstance().OnRecv(poUser->GetPlayingRole(), (const char*)pPacketBuffer);
        }
    }

    if (m_AsimovMessageFuncList[pHeader->wMsg])
        (this->*m_AsimovMessageFuncList[pHeader->wMsg])(poUser, pPacketBuffer, dwSize);

    poUser->LuaRecvMsg(pHeader->wMsg, pPacketBuffer, dwSize);

    m_pPacketAllocator->Free(pPacketBuffer);
    return;
Exit1:
    m_pPacketAllocator->Free(pPacketBuffer);
    return;
Exit0:
    CRI("unknown message id %d size %d", pHeader->wMsg, dwSize);

    if (pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);

    return;
}

void CAsimovMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
    INT32 nRetCode = 0;
    LOG_PROCESS_ERROR(pSocketSession);

    CUser* poUser = (CUser*)pSocketSession->GetUserData();
    PROCESS_ERROR(poUser);

    if(poUser->GetUserState() == usConnectingBS)
    {
        poUser->OnBSDisConnected();
    }
    else
    {
        poUser->OnDisconnected();
    }
    
    return;
Exit0:
    return;
}

CAsimovMessageHandler::CAsimovMessageHandler()
{
    m_poNet = NULL;
    m_pPacketAllocator = NULL;
}

CAsimovMessageHandler::~CAsimovMessageHandler()
{
    UnInit();
}

BOOL CAsimovMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pNet);
    LOG_PROCESS_ERROR(pPacketAllocator);
    
    m_poNet = pNet;
    m_pPacketAllocator = pPacketAllocator;
    memset(m_AsimovMessageFuncList, 0, sizeof(m_AsimovMessageFuncList));
    
    m_AsimovMessageFuncList[t2c_login_ack] = &CAsimovMessageHandler::OnLoginAck;
    m_AsimovMessageFuncList[t2c_select_role_ack] = &CAsimovMessageHandler::OnSelectRoleAck;
    m_AsimovMessageFuncList[t2c_sync_role_list] = &CAsimovMessageHandler::OnSyncRoleList;
    m_AsimovMessageFuncList[t2c_create_role_ack] = &CAsimovMessageHandler::OnCreateRoleAck;
    m_AsimovMessageFuncList[t2c_delete_role_ack] = &CAsimovMessageHandler::OnDeleteRoleAck;
    m_AsimovMessageFuncList[g2c_leave_scene] = &CAsimovMessageHandler::OnLeaveScene;
    m_AsimovMessageFuncList[g2c_sync_game_data_end] = &CAsimovMessageHandler::OnSyncGameDataEnd;
    m_AsimovMessageFuncList[t2c_error_notify] = &CAsimovMessageHandler::OnGTErrorNotify;
    m_AsimovMessageFuncList[g2c_changescene_enter] = &CAsimovMessageHandler::OnChangeSceneEnter;
	m_AsimovMessageFuncList[b2c_query_gate_ack] = &CAsimovMessageHandler::OnQueryGateAck;
    m_AsimovMessageFuncList[t2c_ping_ack] = &CAsimovMessageHandler::OnGatePingAck;
    m_AsimovMessageFuncList[g2c_ping_ack] = &CAsimovMessageHandler::OnGamePingAck;
	m_AsimovMessageFuncList[m2c_error_notify] = &CAsimovMessageHandler::OnMSErrorNotify;
	m_AsimovMessageFuncList[g2c_error_notify] = &CAsimovMessageHandler::OnGSErrorNotify;
   
	m_AsimovMessageFuncList[g2c_sync_role_attr_data] = &CAsimovMessageHandler::OnSyncRoleAttrData;
	m_AsimovMessageFuncList[g2c_sync_role_equip_data] = &CAsimovMessageHandler::OnSyncRoleEquipData;
	m_AsimovMessageFuncList[g2c_sync_role_attr_data] = &CAsimovMessageHandler::OnSyncRoleAttrData;
	m_AsimovMessageFuncList[g2c_sync_role_attr_data] = &CAsimovMessageHandler::OnSyncRoleAttrData;
	m_AsimovMessageFuncList[g2c_sync_role_attr_data] = &CAsimovMessageHandler::OnSyncRoleAttrData;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CAsimovMessageHandler::UnInit(void)
{
    INT32 nRetCode = 0;

    nRetCode = CRobotMessageHandler::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    m_poNet = NULL;
    m_pPacketAllocator = NULL;

    return TRUE;
}

CAsimovMessageHandler& CAsimovMessageHandler::GetInstance(void)
{
    return ms_AsimovInstance;
}

void CAsimovMessageHandler::OnGTErrorNotify(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    T2C_ERROR_NOTIFY* pMsg = (T2C_ERROR_NOTIFY*)pPacketBuffer;
    INF("usr %s session<%08x> got t2c_error_notify %d %d %d", poUser->GetUserName(), poUser->GetSessionID(), pMsg->nErrCode, pMsg->nParam1, pMsg->nParam2);
}

void CAsimovMessageHandler::OnMSErrorNotify(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	M2C_ERROR_NOTIFY* pMsg = (M2C_ERROR_NOTIFY*)pPacketBuffer;
	INF("m2c_error_notify %d %d %d", pMsg->nErrorCode, pMsg->nParam1, pMsg->nParam2);
}

void CAsimovMessageHandler::OnGSErrorNotify(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	G2C_ERROR_NOTIFY* pMsg = (G2C_ERROR_NOTIFY*)pPacketBuffer;
	INF("g2c_error_notify %d %d %d", pMsg->nErrCode, pMsg->nParam1, pMsg->nParam2);

	if (pMsg->nErrCode == errSpellWeaponTypeError)
		poUser->GMCommand("EquipWeapon()");
}

void CAsimovMessageHandler::OnLoginAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    T2C_LOGIN_ACK* pMsg = (T2C_LOGIN_ACK*)pPacketBuffer;
    //For now there are no validation failures

	poUser->SetEncryptCode(pMsg->byEncryptCode);

    poUser->SetUserState(usConnected);
    INF("user %s login to %d:%d successfully", 
        poUser->GetUserName(), poUser->GetServerAddress(), poUser->GetServerPort());

    //if (SUCCESS == pMsg->byAckType)
    //{
    //    poUser->SetUserState(usConnected);
    //    INF("user %s login to %s:%d successfully", 
    //        poUser->GetUserName(), poUser->GetServerAddress(), poUser->GetServerPort());
    //}
    //else
    //{
    //    poUser->SetUserState(usUnconnected);
    //    CRI("user %s failed to login to %s:%d (err %d)", 
    //        poUser->GetUserName(), poUser->GetServerAddress(), poUser->GetServerPort(), LoginAck->byAckType);
    //}
    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnSelectRoleAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    T2C_SELECT_ROLE_ACK* pMsg = (T2C_SELECT_ROLE_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR(poUser);

    //if (SUCCESS != pMsg->)
    //{
    //    CRI("user %s failed to select role %d", poUser->GetUserName(), pMsg->dwRoleID);
    //    return FALSE;
    //}
    //else
    //{
        CRole * poRole = poUser->GetRoleByID(pMsg->dwRoleID);
        LOG_PROCESS_ERROR(poRole != NULL);
        
        poUser->SetPlayingRole(poRole);
        poUser->SetUserState(usPlaying);
        asimov::GetInstance().AddRoleWidget(poRole);
        INF("user %s select role %d successfully", poUser->GetUserName(), pMsg->dwRoleID);
    //}

    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnSyncRoleList(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    CRole* poRoleList[MAX_ROLE_PER_USER];
    T2C_SYNC_ROLE_LIST* pMsg = (T2C_SYNC_ROLE_LIST*)pPacketBuffer;
    LOG_PROCESS_ERROR(poUser);

    //LOG_PROCESS_ERROR(pMsg->nErrCode == errLoginSuccess);
    LOG_PROCESS_ERROR(pMsg->byCount <= MAX_ROLE_PER_USER);

    for (INT32 nIndex = 0; nIndex < pMsg->byCount; nIndex++)
    {
        LOGIN_ROLE_DATA* pLoginRoleData = pMsg->RoleData + nIndex;
        LOG_PROCESS_ERROR(pLoginRoleData);
        
		poRoleList[nIndex] = CGameWorld::GetInstance().FindRole(pLoginRoleData->dwRoleID);
		if(poRoleList[nIndex])
		{
			CScene* poOldScene = poRoleList[nIndex]->GetScene();
			if(poOldScene)
			{
                INF("user %s remove role %d from poOldScene (%d, %d) when OnSyncRoleList", 
                    poUser->GetUserName(), pLoginRoleData->dwRoleID, poOldScene->GetSceneTempID(), poOldScene->GetSceneID() );
				nRetCode = poOldScene->RemoveRole(poRoleList[nIndex]);
				LOG_CHECK_ERROR(nRetCode);
            }
            INF("user %s OnSyncRoleList Find role %d, obj id = %d, UnInit it", poUser->GetUserName(), pLoginRoleData->dwRoleID );
            poRoleList[nIndex]->UnInit();
		}

		if(!poRoleList[nIndex])
		{
			poRoleList[nIndex] = CGameWorld::GetInstance().NewRole(pLoginRoleData->dwRoleID);
			LOG_PROCESS_ERROR(poRoleList[nIndex]);
		}

        nRetCode = poRoleList[nIndex]->Init(pLoginRoleData->dwRoleID, poUser->GetSessionID());
        LOG_PROCESS_ERROR(nRetCode);
        INF("user %s OnSyncRoleList Init role %d, session id = %d", 
            poUser->GetUserName(), poRoleList[nIndex]->GetObjID(), poUser->GetSessionID() );
        
        poRoleList[nIndex]->SetServerGroup(poUser->GetGroupID());
        poRoleList[nIndex]->SetName(pLoginRoleData->szRoleName);
        //poRoleList[nIndex]->SetLevel(pLoginRoleData->byLevel);
        poRoleList[nIndex]->SetSex(pLoginRoleData->bySex);
        poRoleList[nIndex]->SetClass(pLoginRoleData->byClass);

    }

    poUser->SetUserState(usSelectRole);
    asimov::GetInstance().OnSyncRoleList(poUser, poRoleList, pMsg->byCount);

    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnCreateRoleAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    CRole * poRole = NULL;
    T2C_CREATE_ROLE_ACK* pMsg = (T2C_CREATE_ROLE_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR(poUser);

    poRole = CGameWorld::GetInstance().NewRole(pMsg->RoleData.dwRoleID);
    LOG_PROCESS_ERROR(poRole);

    nRetCode = poRole->Init(pMsg->RoleData.dwRoleID, poUser->GetSessionID());
    LOG_PROCESS_ERROR(nRetCode);

    INF("user %s OnCreateRoleAck Init role %d, obj id = %d, session id = %d", 
        poUser->GetUserName(), poRole->GetObjID(), poUser->GetSessionID() );

    poRole->SetName(pMsg->RoleData.szRoleName);
    //poRole->SetLevel(pMsg->RoleData.byLevel);
    poRole->SetSex(pMsg->RoleData.bySex);
    poRole->SetClass(pMsg->RoleData.byClass);
	poRole->SetServerGroup(poUser->GetGroupID());

    poUser->SetUserState(usSelectRole);

    asimov::GetInstance().OnCreateRole(poUser, poRole, TRUE);

    return;
Exit0:
    return;
}
void CAsimovMessageHandler::OnDeleteRoleAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    CRole * poRole = NULL;
    T2C_DELETE_ROLE_ACK* pMsg = (T2C_DELETE_ROLE_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR(poUser);

    //if (pMsg->nErrCode != SUCCESS)
    //{
    //    CRI("user %s failed to delete role %d", poUser->GetUserName(), pMsg->dwRoleID);
    //    asimov::GetInstance().OnDeleteRole(poUser, pMsg->dwRoleID, FALSE);

    //    return FALSE;
    //}

    asimov::GetInstance().OnDeleteRole(poUser, pMsg->dwRoleID, TRUE);
    poUser->SetUserState(usSelectRole);

    return;
Exit0:
    return;
}
void CAsimovMessageHandler::OnLeaveScene(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    G2C_LEAVE_SCENE* pMsg = (G2C_LEAVE_SCENE*)pPacketBuffer;
    LOG_PROCESS_ERROR(poUser);

    //if (SUCCESS == pstLeaveGameAck->nErrCode)
    //{
//        nRetCode = poUser->ReturnSelectRole();
//        LOG_PROCESS_ERROR(nRetCode);

        INF("user %s Leave %d:%d successfully", 
            poUser->GetUserName(), poUser->GetServerAddress(), poUser->GetServerPort());
    //}
    //else
    //{
    //    CRole* poRole = poUser->GetPlayingRole();
    //    LOG_PROCESS_ERROR(poRole);
    //    poRole->SetState(InScene);

    //    CRI("user %s failed to Leave to %s:%d (err %d)", 
    //        poUser->GetUserName(), poUser->GetServerAddress(), poUser->GetServerPort(), pstLeaveGameAck->nErrCode);
    //}
    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnSyncGameDataEnd(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    G2C_SYNC_GAME_DATA_END* pRoleInfo = (G2C_SYNC_GAME_DATA_END*)pPacketBuffer;
    LOG_PROCESS_ERROR(poUser);

    if(poUser->IsAutoLogin())
    {
        nRetCode = poUser->SendLoadFinsh();
        LOG_PROCESS_ERROR(nRetCode);
    }

    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnChangeSceneEnter(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    CRole* poRole = NULL;
    G2C_CHANGESCENE_ENTER* pMsg = (G2C_CHANGESCENE_ENTER*)pPacketBuffer;
    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(poUser->GetUserState() == usPlaying);

    if(poUser->IsAutoLogin())
    {
        nRetCode = poUser->SendLoadFinsh();
        LOG_PROCESS_ERROR(nRetCode);
    }
    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnQueryGateAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
    B2C_QUERY_GATE_ACK* pMsg = (B2C_QUERY_GATE_ACK*)pPacketBuffer;

    poUser->SetServerContent(pMsg->dwAddr, pMsg->wPort);
    return;
}

void CAsimovMessageHandler::OnGatePingAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    T2C_PING_ACK* pMsg = (T2C_PING_ACK*)pPacketBuffer;
    PROCESS_ERROR(poUser);
 
    poUser->AddPingPackage(GetTickCountEx() - pMsg->dwPingTick);
    if (GetTickCountEx() - pMsg->dwPingTick > 1000)
		WRN("session %08X t2c_ping %u %d", poUser->GetSocketSession(), pMsg->dwPingTick, GetTickCountEx() - pMsg->dwPingTick);
	DBG("session %08X t2c_ping %u %d", poUser->GetSocketSession(), pMsg->dwPingTick, GetTickCountEx() - pMsg->dwPingTick);

    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnGamePingAck(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    INT32 nRetCode = 0;
    G2C_PING_ACK* pMsg = (G2C_PING_ACK*)pPacketBuffer;

    if (GetTickCountEx() - pMsg->dwPingTick > 1000)
		WRN("g2c_ping %u %d", pMsg->dwPingTick, GetTickCountEx() - pMsg->dwPingTick);
	DBG("g2c_ping %u %d", pMsg->dwPingTick, GetTickCountEx() - pMsg->dwPingTick);

	PROCESS_ERROR(poUser->GetPlayingRole());
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poUser->GetPlayingRole()->GetAchievementList(), adCreateTime, 0);

    return;
Exit0:
    return;
}

void CAsimovMessageHandler::OnSyncRoleAttrData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	G2C_SYNC_ROLE_ATTR_DATA* pMsg = (G2C_SYNC_ROLE_ATTR_DATA*)pPacketBuffer;
	poUser->UpdateRoleAttrCRC(pMsg->dwRoleID, crc32(0, (const Bytef*)pMsg, dwSize));
}

void CAsimovMessageHandler::OnSyncRoleEquipData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	G2C_SYNC_ROLE_EQUIP_DATA* pMsg = (G2C_SYNC_ROLE_EQUIP_DATA*)pPacketBuffer;
	poUser->UpdateRoleEquipCRC(pMsg->dwRoleID, crc32(0, (const Bytef*)pMsg, dwSize));
}

void CAsimovMessageHandler::OnSyncRoleSpiritData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	G2C_SYNC_ROLE_SPIRIT_DATA* pMsg = (G2C_SYNC_ROLE_SPIRIT_DATA*)pPacketBuffer;
	poUser->UpdateRoleSpiritCRC(pMsg->dwRoleID, crc32(0, (const Bytef*)pMsg, dwSize));
}

void CAsimovMessageHandler::OnSyncRoleSpellData(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	G2C_SYNC_ROLE_SPELL_DATA* pMsg = (G2C_SYNC_ROLE_SPELL_DATA*)pPacketBuffer;
	poUser->UpdateRoleSpellCRC(pMsg->dwRoleID, crc32(0, (const Bytef*)pMsg, dwSize));
}

void CAsimovMessageHandler::OnSyncRolePow(CUser* poUser, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	G2C_SYNC_ROLE_POW* pMsg = (G2C_SYNC_ROLE_POW*)pPacketBuffer;
}





