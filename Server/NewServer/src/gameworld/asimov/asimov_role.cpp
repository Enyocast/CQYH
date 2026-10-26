
#include "stdafx.h"
#include "asimov_role.h"
#include "role.h"


#ifdef _ROBOT
CAsimovRole::CAsimovRole()
{
    m_nGuildAppNum = 0;
    memset(m_dwGuildApp, 0, sizeof(m_dwGuildApp));
    m_dwInviteGuildRoleID = 0;
    m_nValidViewGuildNum = 0;
    memset(m_arrViewGuildIDList, 0, sizeof(m_arrViewGuildIDList));
    m_poRole = NULL;

    m_nCompleteAchievementNum = 0;
    memset(m_arrAchievementList, 0, sizeof(m_arrAchievementList));
}

CAsimovRole::~CAsimovRole()
{
    m_nGuildAppNum = 0;
    memset(m_dwGuildApp, 0, sizeof(m_dwGuildApp));
    m_dwInviteGuildRoleID = 0;
    m_nValidViewGuildNum = 0;
    memset(m_arrViewGuildIDList, 0, sizeof(m_arrViewGuildIDList));
    m_poRole = NULL;
    m_nCompleteAchievementNum = 0;
    memset(m_arrAchievementList, 0, sizeof(m_arrAchievementList));
}

BOOL CAsimovRole::Init(CRole *poRole)
{
    LOG_PROCESS_ERROR(poRole);

    m_poRole = poRole;
    m_nCompleteAchievementNum = 0;
    memset(m_arrAchievementList, 0, sizeof(m_arrAchievementList));

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CAsimovRole::UnInit()
{
    m_nCompleteAchievementNum = 0;
    memset(m_arrAchievementList, 0, sizeof(m_arrAchievementList));

    return TRUE;
}


UINT32 CAsimovRole::RandShieldRole()
{
    UINT32      dwRoleID = 0;
    INT32       nShieldCount = 0;
    INT32       nRandIndex = 0;
    LOG_PROCESS_ERROR(m_poRole);

    nShieldCount = m_poRole->GetShieldList()->GetShieldCount();
    PROCESS_ERROR(0 != nShieldCount);

    nRandIndex = g_Random(nShieldCount);
    dwRoleID = m_poRole->GetShieldList()->FindShieldedRole(nRandIndex);

    return dwRoleID;
Exit0:
    return 0;
}

INT32 CAsimovRole::RandCompleteAchievement()
{
    INT32       nRandIndex = 0;
    if (0 == m_nCompleteAchievementNum)
        return 0;

    nRandIndex = g_Random(m_nCompleteAchievementNum);

    return m_arrAchievementList[nRandIndex];
}

BOOL CAsimovRole::AddCompleteAchievement(INT32 nAchievementID)
{
    LOG_PROCESS_ERROR(m_nCompleteAchievementNum < ACHIEVEMENT_MAX);
    m_arrAchievementList[m_nCompleteAchievementNum++] = nAchievementID;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CAsimovRole::DelCompleteAchievement(INT32 nAchievementID)
{
    for (INT32 nIndex = 0; nIndex < m_nCompleteAchievementNum; ++nIndex)
    {
        if (m_arrAchievementList[nIndex] == nAchievementID)
        {
            m_arrAchievementList[nIndex] = m_arrAchievementList[m_nCompleteAchievementNum - 1];
            --m_nCompleteAchievementNum;
            return TRUE;
        }
    }

    return TRUE;
}

BOOL CAsimovRole::DelGuildApp(UINT32 dwGuildID)
{
    for (INT32 i = 0; i < m_nGuildAppNum; ++i)
    {
        if (m_dwGuildApp[i] == dwGuildID)
        {
            m_dwGuildApp[i] = m_dwGuildApp[m_nGuildAppNum - 1];
            --m_nGuildAppNum;
            return TRUE;
        }
    }
    return TRUE;
}

void CAsimovRole::SetInviteGuildRoleID(UINT32 dwGuildID)
{
    m_dwInviteGuildRoleID = dwGuildID;
}

UINT32 CAsimovRole::GetInviteGuildRoleID()
{
    return m_dwInviteGuildRoleID;
}

void CAsimovRole::ClearViewList()
{
    m_nValidViewGuildNum = 0;
}

BOOL CAsimovRole::AddViewList(UINT32 dwGuildID)
{
    LOG_PROCESS_ERROR(m_nValidViewGuildNum < MAX_VIEW_GUILD_LIST_COUNT);

    m_arrViewGuildIDList[m_nValidViewGuildNum++] = dwGuildID;

    return TRUE;
Exit0:
    return FALSE;
}

INT32 CAsimovRole::GetViewListNum()
{
//    DBG("asimov view list num %d", m_nValidViewGuildNum);
    return m_nValidViewGuildNum;
}

UINT32 CAsimovRole::GetViewListGuildIDByIndex(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex < m_nValidViewGuildNum);

    return m_arrViewGuildIDList[nIndex];
Exit0:
    return 0;
}


BOOL CAsimovRole::LuaClearGuildApp()
{
    m_nGuildAppNum = 0;
    return TRUE;
}

BOOL CAsimovRole::LuaIsInGuildAppList(UINT32 dwGuildID)
{
    for (INT32 i = 0; i < m_nGuildAppNum; ++i)
    {
        if (m_dwGuildApp[i] == dwGuildID)
            return TRUE;
    }

    return FALSE;
}

INT32 CAsimovRole::LuaGetGuildAppNum()
{
    DBG("asimov guild app num %d", m_nGuildAppNum);
    return m_nGuildAppNum;
}

UINT32 CAsimovRole::LuaGetGuildAppByIndex(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex < m_nGuildAppNum);
    return m_dwGuildApp[nIndex];
Exit0:
    return 0;
}

BOOL CAsimovRole::LuaAddGuildApp(UINT32 dwGuildID)
{
    INT32       nRetCode = 0;

    for (INT32 i = 0; i < m_nGuildAppNum; ++i)
    {
        if (m_dwGuildApp[i] == dwGuildID)
            return TRUE;
    }

    LOG_PROCESS_ERROR(m_nGuildAppNum < ROLE_MAX_APPLICATION);

    m_dwGuildApp[m_nGuildAppNum++] = dwGuildID;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CAsimovRole::LuaDelGuildApp(UINT32 dwGuildID)
{
    INT32       nRetCode = 0;
    INT32       nIndex = 0;
    for (INT32 i = 0; i < m_nGuildAppNum; ++i)
    {
        if (m_dwGuildApp[i] == dwGuildID)
        {
            nIndex = 0;
            break;
        }
    }

    if (0 != nIndex)
    {
        m_dwGuildApp[nIndex] = m_dwGuildApp[--m_nGuildAppNum];
    }

    return TRUE;
Exit0:
    return FALSE;
}

#endif //_ROBOT
