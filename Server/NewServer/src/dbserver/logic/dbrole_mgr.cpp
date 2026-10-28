#include "stdafx.h"
#include "dbrole_mgr.h"
#include "dbrole.h"
#include "dbuser.h"

CDBRoleMgr::CDBRoleMgr()
{
    m_freerolelist.Clear();
}

CDBRoleMgr::~CDBRoleMgr()
{

}

BOOL CDBRoleMgr::Init(UINT32 dwRoleCount)
{
    CDBRole* dbrole;
    for (UINT32 i=0; i<dwRoleCount; i++)
    {
        dbrole = new CDBRole;
        LOG_PROCESS_ERROR(dbrole);
        ClearNode(dbrole);
        m_freerolelist.PushRear(dbrole);
    }
    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDBRoleMgr::UnInit()
{
    CDBRole* dbrole = NULL;
    while(dbrole = (CDBRole*)m_freerolelist.PopHead())
    {
        if (dbrole->m_dbtask == CDBRole::DB_TASK_INVALID)
            delete dbrole;
    }

    for (ROLEMAP::iterator it=m_rolemap.begin(); it!=m_rolemap.end(); ++it)
    {
        delete it->second;
    }
    m_rolemap.clear();

    return TRUE;
}

BOOL CDBRoleMgr::AddDBRole(CDBRole* dbrole)
{
    BOOL bRet = m_rolemap.insert(ROLEMAP::value_type(dbrole->m_dwRoleID, dbrole)).second;
    LOG_CHECK_ERROR(bRet);
    return bRet;
}

BOOL CDBRoleMgr::DelDBRole(CDBRole* dbrole)
{
    ROLEMAP::iterator it = m_rolemap.find(dbrole->m_dwRoleID);
    LOG_PROCESS_ERROR(it != m_rolemap.end());

    m_rolemap.erase(it);

    return TRUE;

Exit0:
    return FALSE;
}

CDBRole* CDBRoleMgr::GetDBRoleByID(UINT32 dwRoleID)
{
    ROLEMAP::iterator it = m_rolemap.find(dwRoleID);
    if (it == m_rolemap.end())
    {
        return NULL;
    }
    else
    {
        return it->second;
    }
}

CDBRole* CDBRoleMgr::Pop()
{
    CDBRole* dbrole = (CDBRole*)m_freerolelist.PopHead();

    LOG_PROCESS_ERROR(dbrole);
    LOG_PROCESS_ERROR(dbrole->m_dbtask == CDBRole::DB_TASK_FREE);
    LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_INVALID || dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);

    if (dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED)
    {
        LOG_PROCESS_ERROR(dbrole->m_dbuser);
        dbrole->m_dbuser->RemoveRole(dbrole, FALSE);

        //RemoveRole returns dbrole to freerolelist; retrieve it again here
        BOOL bRet = CBaseList::Remove(dbrole);
        LOG_PROCESS_ERROR(bRet);
    }
    return dbrole;

Exit0:
    return NULL;
}

BOOL CDBRoleMgr::Pop(CDBRole* dbrole)
{
    BOOL bRet = 0;

    LOG_PROCESS_ERROR(dbrole);
    LOG_PROCESS_ERROR(dbrole->m_dbtask == CDBRole::DB_TASK_FREE);
    LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);

    bRet = CBaseList::Remove(dbrole);
    LOG_PROCESS_ERROR(bRet);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDBRoleMgr::Push(CDBRole* dbrole)
{
    BOOL bRet = FALSE;
    LOG_PROCESS_ERROR(dbrole);
    LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_INVALID || dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);

    bRet = m_freerolelist.PushRear(dbrole);
    LOG_PROCESS_ERROR(bRet);

    return TRUE;

Exit0:
    return FALSE;
}

