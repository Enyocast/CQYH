#include "stdafx.h"
#include "friend.h"
#include "friend_def.h"
#include "message_handler.h"
#include "common.h"

CFriend::CFriend()
{
    Clear();
}

void CFriend::Clear()
{
    memset(m_szSignature, 0, sizeof(m_szSignature));
    memset(m_szGroups, 0, sizeof(m_szGroups));
    m_friends.clear();
    m_personalEnemy.clear();
}

void CFriend::SetSignature(const char* szSignature)
{
    strxcpy(m_szSignature, szSignature, SIGNATURE_LEN);
}

const char* CFriend::GetSignature()
{
    return m_szSignature;
}

void CFriend::ChangeGroupName(UINT8 byGroupID, const char* szGroupName)
{
    LOG_PROCESS_ERROR(byGroupID < MAX_FRIEND_GROUP_COUNT);
    LOG_PROCESS_ERROR(szGroupName);

    strxcpy(m_szGroups[byGroupID], szGroupName, FRIEND_GROUP_NAME_LEN);

Exit0:
    return;
}

void CFriend::AddFriend(UINT8 byGroupID, UINT32 dwFriendID)
{
    if (FRIEND_GROUP_ENEMY == byGroupID)
        m_personalEnemy.insert(dwFriendID);
    else
        m_friends.insert(dwFriendID);
}

void CFriend::DelFriend(UINT8 byGroupID, UINT32 dwFriendID)
{
    if (FRIEND_GROUP_ENEMY == byGroupID)
        m_personalEnemy.erase(dwFriendID);
    else
        m_friends.erase(dwFriendID);
}

const char* CFriend::GetGroupName(UINT32 groupid) const
{
    LOG_PROCESS_ERROR(groupid < MAX_FRIEND_GROUP_COUNT);
    return m_szGroups[groupid];

Exit0:
    return NULL;
}

INT32 CFriend::GetFriendCount()
{
	return static_cast<INT32>(m_friends.size());
}

INT32 CFriend::GetPersonalEnemyCount()
{
    return static_cast<INT32>(m_personalEnemy.size());
}


BOOL CFriend::AddBeKilledToList(CRole *poRole, UINT32 dwRoleID)
{
#ifndef _ROBOT

    INT32       nRetCode = 0;
    LOG_PROCESS_ERROR(poRole);
    if (m_friends.end() != m_friends.find(dwRoleID))
    {
        return TRUE;
    }
    if (m_personalEnemy.end() != m_personalEnemy.find(dwRoleID))
    {
        return TRUE;
    }

    nRetCode = CCliMessageHandler::GetInstance().DoMSAddBeKilledToList(poRole, dwRoleID);
    LOG_PROCESS_ERROR(nRetCode);

#endif
    return TRUE;

Exit0:
    return FALSE;
}

UINT32 CFriend::Begin()
{
	m_Iterator = m_friends.begin();
	return Next();
}

UINT32 CFriend::Next()
{
	UINT32 dwFriendID = INVALID_OBJECT_ID;

	if (m_Iterator != m_friends.end())
	{
		dwFriendID = *m_Iterator;
		++m_Iterator;
	}

	return dwFriendID;
}