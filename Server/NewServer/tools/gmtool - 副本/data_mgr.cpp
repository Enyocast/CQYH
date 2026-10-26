/********************************************************************
	created:	19:2:2014   10:42
	file:		data_mgr.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#include "stdafx.h"
#include "data_mgr.h"
#include "string_ex.h"



CDataMgr CDataMgr::m_Instance;

CDataMgr::CDataMgr() 
{
}

CDataMgr::~CDataMgr()
{

}

CDataMgr& CDataMgr::GetInstance()
{
    return m_Instance;
}

BOOL CDataMgr::Init()
{
    INT32       nRetCode = 0;

    nRetCode = m_RolePool.Init(128);
    LOG_PROCESS_ERROR(nRetCode);

    m_ItemMap->clear();

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDataMgr::UnInit()
{
    INT32       nRetCode = 0;

    nRetCode = m_RolePool.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}


// role data
GM_ROLE_DATA* CDataMgr::NewRole(UINT32 dwRoleID)
{
    INT32       nRetCode = 0;
    GM_ROLE_DATA *pRole = m_RolePool.Find(dwRoleID);
    if (pRole)
    {
        nRetCode = DeleteRole(pRole);
        LOG_PROCESS_ERROR(nRetCode);
    }

    pRole = m_RolePool.New(dwRoleID);
    LOG_PROCESS_ERROR(pRole);
    pRole->dwRoleID = dwRoleID;
    return pRole;
Exit0:
    return NULL;
}

BOOL CDataMgr::DeleteRole(GM_ROLE_DATA* pRole)
{
    LOG_PROCESS_ERROR(pRole);
    return m_RolePool.Delete(pRole);
Exit0:
    return FALSE;
}

BOOL CDataMgr::ClearRole()
{
    INT32       nRetCode = 0;
    nRetCode = m_RolePool.UnInit();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = m_RolePool.Init(128);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

GM_ROLE_DATA* CDataMgr::FindRole(UINT32 dwRoleID)
{
    GM_ROLE_DATA *pRole = m_RolePool.Find(dwRoleID);
    if (pRole)
        return pRole;
    return NULL;
}

// item template
void CDataMgr::ClearItemMap(UINT32 dwSessionID)
{
    LOG_PROCESS_ERROR(dwSessionID < MAX_GM_SESSION_COUNT);
    m_ItemMap[dwSessionID].clear();
Exit0:
    return;
}

BOOL CDataMgr::AddItem(UINT32 dwSessionID, UINT32 dwItemID, const char *pcszName)
{
    ITEM_TEMPLATE_DATA  data;

    LOG_PROCESS_ERROR(pcszName);
    LOG_PROCESS_ERROR(dwSessionID < MAX_GM_SESSION_COUNT);

    data.dwTempID = dwItemID;
    strxcpy(data.szName, pcszName, sizeof(data.szName));

    m_ItemMap[dwSessionID].insert(std::make_pair(data.dwTempID, data));

    return TRUE;
Exit0:
    return FALSE;
}

void CDataMgr::ItemMapBegin(UINT32 dwSessionID)
{
    m_ItemMap_Cursor[dwSessionID] = m_ItemMap[dwSessionID].begin();
}

ITEM_TEMPLATE_DATA* CDataMgr::ItemMapNext(UINT32 dwSessionID)
{
    ITEM_MAP::iterator iter = m_ItemMap_Cursor[dwSessionID];

    PROCESS_ERROR(iter != m_ItemMap[dwSessionID].end());

    ++m_ItemMap_Cursor[dwSessionID];

    return &(iter->second);
Exit0:
    return NULL;
}



// announce
BOOL CDataMgr::DelAnnounceFromList(UINT32 dwAnnounceSerial)
{
    for (INT32 i = 0; i < m_AnnounceList.nCount; ++i)
    {
        if (m_AnnounceList.data[i].dwSerial == dwAnnounceSerial)
        {
            m_AnnounceList.data[i].dwIntervalTime = m_AnnounceList.data[m_AnnounceList.nCount - 1].dwIntervalTime;
            m_AnnounceList.data[i].dwRepeatNum = m_AnnounceList.data[m_AnnounceList.nCount - 1].dwRepeatNum;
            m_AnnounceList.data[i].dwSerial = m_AnnounceList.data[m_AnnounceList.nCount - 1].dwSerial;
            strxcpy(m_AnnounceList.data[i].szText, m_AnnounceList.data[m_AnnounceList.nCount - 1].szText, sizeof(m_AnnounceList.data[i].szText));
            --m_AnnounceList.nCount;
            break;
        }
    }

    return TRUE;
}




