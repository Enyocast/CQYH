
#include "stdafx.h"
#include "general_mgr.h"

#ifdef _ROBOT

#include "robot_message_handler.h"

CGeneralMgr  CGeneralMgr::m_Instance;

CGeneralMgr& CGeneralMgr::GetInstance()
{
    return m_Instance;
}

CGeneralMgr::CGeneralMgr()
{
    m_nRandRoleNum = 0;
    memset(m_arrRandRole, 0, sizeof(m_arrRandRole));
}

CGeneralMgr::~CGeneralMgr()
{
    m_nRandRoleNum = 0;
    memset(m_arrRandRole, 0, sizeof(m_arrRandRole));
}

BOOL CGeneralMgr::Init()
{
    m_nRandRoleNum = 0;
    memset(m_arrRandRole, 0, sizeof(m_arrRandRole));

    return TRUE;
}

BOOL CGeneralMgr::UnInit()
{
    m_nRandRoleNum = 0;
    memset(m_arrRandRole, 0, sizeof(m_arrRandRole));

    return TRUE;
}

BOOL CGeneralMgr::IsValidRandRoleExist()
{
    return m_nRandRoleNum > 0;
}

RAND_ROLE_DATA* CGeneralMgr::GetRandRole(UINT32 dwRoleID)
{
    INT32       nIndex = 0;

    LOG_PROCESS_ERROR(m_nRandRoleNum > 0);

    nIndex = rand();
    nIndex = nIndex % m_nRandRoleNum;

    if (m_arrRandRole[nIndex].dwRoleID == dwRoleID)
    {
        nIndex = (nIndex + 1) % m_nRandRoleNum;
    }

    return &(m_arrRandRole[nIndex]);
Exit0:
    return NULL;
}

void CGeneralMgr::AddRandRole(UINT32 dwRoleID, const char *pcszName)
{
    INT32       nIndex = 0;

    LOG_PROCESS_ERROR(pcszName);

    for (INT32 i = 0; i < m_nRandRoleNum; ++i)
        PROCESS_ERROR(dwRoleID != m_arrRandRole[i].dwRoleID);

    if (m_nRandRoleNum < MAX_RAND_USER_NUM)
    {
        m_arrRandRole[m_nRandRoleNum].dwRoleID = dwRoleID;
        strxcpy(m_arrRandRole[m_nRandRoleNum].szRoleName, pcszName, ROLE_NAME_LEN);
        ++m_nRandRoleNum;
    }
    else
    {
        nIndex = rand();
        nIndex = nIndex % m_nRandRoleNum;
        m_arrRandRole[nIndex].dwRoleID = dwRoleID;
        strxcpy(m_arrRandRole[nIndex].szRoleName, pcszName, ROLE_NAME_LEN);
    }

Exit0:
    return;
}


extern ROLE_CACHE	s_RoleCache;

const char* CGeneralMgr::GetRandomGuild()
{
    GUILD_DATA_CACHE_MAP::iterator  iter;
    GUILD_DATA_CACHE_MAP::iterator  end_iter = s_RoleCache.GuildDataCache.end();
    INT32       nGuildNum = s_RoleCache.GuildDataCache.size();
    INT32       nIndex = 0;
    INT32       i = 0;
    nIndex = g_Random(nGuildNum);

    for (iter = s_RoleCache.GuildDataCache.begin(); iter != end_iter; ++iter, i++)
    {
        if (nIndex == i)
        {
            return iter->second.szGuildName;
        }
    }

Exit0:
    return NULL;
}

#endif //_ROBOT

