#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "role.h"
#include "friend_def.h"
#include "g2m_message.h"
#include "game_world.h"

#ifndef _ROBOT

using namespace ExternalMessage;

void CCliMessageHandler::OnFriendChangeGroupName(CRole* pRole, const char* pData)
{
    C2G_FRIEND_CHANGE_GROUP_NAME* pMsg = (C2G_FRIEND_CHANGE_GROUP_NAME*)pData;
    pRole->GetFriend()->ChangeGroupName(pMsg->byGroupID, pMsg->szGroupName);
}

BOOL CCliMessageHandler::DoSyncFriendGroupName(CRole* poRole)
{
    BOOL nRetCode = FALSE;
    INT32 nSize = sizeof(G2C_FRIEND_GROUP_LIST) + sizeof(FRIEND_GROUP_INFO) * MAX_FRIEND_GROUP_COUNT;
    G2C_FRIEND_GROUP_LIST* pMsg = (G2C_FRIEND_GROUP_LIST*)m_poPacketAllocator->Alloc(nSize);
    char groups[MAX_FRIEND_GROUP_COUNT][FRIEND_GROUP_NAME_LEN];

    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_friend_group_list;
    pMsg->byGroupCount = 0;
    for (UINT8 i=0; i<MAX_FRIEND_GROUP_COUNT; i++)
    {
        const char* group_name = poRole->GetFriend()->GetGroupName(i);
        if (group_name[0])
        {
            pMsg->stGroupInfo[pMsg->byGroupCount].byGroupID = i;
            strxcpy(pMsg->stGroupInfo[pMsg->byGroupCount].szGroupName, group_name, FRIEND_GROUP_NAME_LEN);
			if (g_GWConfig.bFilterCensoredWord)
			{
				nRetCode = CGameWorld::GetInstance().ReplaceCensoredWord(pMsg->stGroupInfo[pMsg->byGroupCount].szGroupName);
				LOG_CHECK_ERROR(nRetCode);
			}
            pMsg->byGroupCount++;
        }
    }

    pMsg->wSize = sizeof(G2C_FRIEND_GROUP_LIST) + sizeof(FRIEND_GROUP_INFO) * pMsg->byGroupCount;
    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}



//////////////////////////////////////////////////////////////////////////
// shield
//////////////////////////////////////////////////////////////////////////
void CCliMessageHandler::OnUnShieldRole(CRole *poRole, const char *pData)
{
    INT32   nRetCode = 0;
    INT32   nResult = errUnknownError;
    CRole   *poTargetRole = NULL;

    C2G_UNSHIELD* pMsg = (C2G_UNSHIELD*)pData;
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);

    LOG_PROCESS_ERROR_RET_CODE(poRole->GetShieldList()->IsAlreadyShielded(pMsg->dwRoleID), errNotFindInShieldList);

    poRole->GetShieldList()->UnShieldRole(pMsg->dwRoleID);

    nRetCode = DoUnShieldAck(poRole, pMsg->dwRoleID);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
    else
		poRole->ErrorCodeNotify(nResult, 0, 0);

    return;
}


BOOL CCliMessageHandler::DoShieldAck(CRole *poRole, UINT32 dwTargetRoleID, char *pTargetRoleName)
{
    INT32 nRetCode = 0;
    G2C_SHIELD_ACK *pMsg = (G2C_SHIELD_ACK*)m_poPacketAllocator->Alloc(sizeof(G2C_SHIELD_ACK));
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(pTargetRoleName);

    pMsg->wMsg = g2c_shield_ack;
    pMsg->dwRoleID = dwTargetRoleID;
    strxcpy(pMsg->szRoleName, pTargetRoleName, ROLE_NAME_LEN);

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SHIELD_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoUnShieldAck(CRole *poRole, UINT32 dwTargetRoleID)
{
    INT32 nRetCode = 0;
    G2C_UNSHIELD_ACK *pMsg = (G2C_UNSHIELD_ACK*)m_poPacketAllocator->Alloc(sizeof(G2C_UNSHIELD_ACK));
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = g2c_unshield_ack;
    pMsg->dwRoleID = dwTargetRoleID;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_UNSHIELD_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncShieldList(CRole *poRole)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;

    G2C_SYNC_SHIELD_LIST* pMsg = NULL; 

    pMsg = (G2C_SYNC_SHIELD_LIST*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_shield_list;
    pMsg->byRoleCount = poRole->GetShieldList()->GetShieldCount();

    LOG_PROCESS_ERROR(sizeof(G2C_SYNC_SHIELD_LIST) + sizeof(UINT32) * pMsg->byRoleCount < MAX_MESSAGE_SIZE);
    for (INT32 i = 0; i < pMsg->byRoleCount; ++i)
    {
        pMsg->arrRoleID[i] = poRole->GetShieldList()->FindShieldedRole(i);
    }

    pMsg->wSize = sizeof(G2C_SYNC_SHIELD_LIST) + sizeof(UINT32) * pMsg->byRoleCount;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}


//////////////////////////////////////////////////////////////////////////
// personal enemy
//////////////////////////////////////////////////////////////////////////
BOOL CCliMessageHandler::DoMSAddBeKilledToList(CRole *poRole, UINT32 dwKillerID)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;

    InternalMessage::G2M_ADD_KILL_LIST *pMsg = (InternalMessage::G2M_ADD_KILL_LIST*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_ADD_KILL_LIST));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_add_kill_list;
    pMsg->dwRoleID = poRole->GetObjID();
    pMsg->dwKillerID = dwKillerID;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_ADD_KILL_LIST));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}



#endif  // _ROBOT
