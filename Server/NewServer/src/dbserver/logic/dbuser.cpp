#include "stdafx.h"
#include "dbuser.h"
#include "dbrole.h"
#include "dbrole_mgr.h"
#include "dbserver.h"
#include "db_message_handler.h"
#include <time.h>

CDBUser::CDBUser()
{
    m_byRoleCount = 0;
    memset(m_BaseData, 0, sizeof(m_BaseData));
    for (INT32 i=0; i<MAX_ROLE_PER_USER; i++)
    {
        m_pDBRole[i] = NULL;
    }

    m_bRoleListCached = FALSE;
    m_pPlayingRole = NULL;
    m_state = dusInvalid;
    m_dbstate = dtsFree;
    m_nResult = 0;
    m_dwClientSessionID = 0;
}

CDBUser::~CDBUser()
{

}

void CDBUser::OnListRole()
{
    BOOL bRet = FALSE;

    LOG_PROCESS_ERROR(m_bRoleListCached == FALSE);
    LOG_PROCESS_ERROR(m_state == dusAuthed || m_state == dusLogout);
    LOG_PROCESS_ERROR(m_dbstate == dtsListing);
    m_dbstate = dtsFree;

    if (m_nResult != errSuccess)
    {
        CDBServer::GetInstance().m_usermgr.DelFromUserNameMap(this);
        m_state = dusInvalid;
    }
    LOG_PROCESS_ERROR(m_nResult == errSuccess);

    m_bRoleListCached = TRUE;

    if (m_state == CDBUser::dusAuthed)
    {
        bRet = CDBMessageHandler::GetInstance().DoGTSyncRoleList(this);
        LOG_PROCESS_ERROR(bRet);
    }

    return;

Exit0:
    CDBMessageHandler::GetInstance().DoGTCloseClientSession(m_dwClientSessionID);
}

BOOL CDBUser::RemoveRole(CDBRole* pRole, BOOL bDelete)
{
    BOOL bRet = FALSE;
    UINT8 rolepos = 0;
    CDBRoleMgr& rolemgr = CDBServer::GetInstance().m_rolemgr;

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(pRole->m_lockstate == CDBRole::LOCK_STATE_INVALID || pRole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);
    LOG_PROCESS_ERROR(m_byRoleCount > 0);
    LOG_PROCESS_ERROR(m_pPlayingRole != pRole);
    LOG_PROCESS_ERROR(pRole->m_dbuser == this);

    for(; rolepos<m_byRoleCount; rolepos++)
    {
        if (m_pDBRole[rolepos] == pRole)
            break;
    }
    LOG_PROCESS_ERROR(rolepos < MAX_ROLE_PER_USER);
    LOG_PROCESS_ERROR(m_pDBRole[rolepos]);

    if (pRole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED)
    {
        bRet = rolemgr.DelDBRole(pRole);
        LOG_PROCESS_ERROR(bRet);

        bRet = pRole->ClearCache(TRUE);
        LOG_PROCESS_ERROR(bRet);

        pRole->m_lockstate = CDBRole::LOCK_STATE_INVALID;
    }

    m_pDBRole[rolepos] = NULL;

    bRet = rolemgr.Push(pRole);
    LOG_PROCESS_ERROR(bRet);

    if (bDelete)
    {
        for(; rolepos<m_byRoleCount-1; rolepos++)
        {
            m_dwRoleID[rolepos] = m_dwRoleID[rolepos+1];
            m_BaseData[rolepos] = m_BaseData[rolepos+1];
            m_pDBRole[rolepos] = m_pDBRole[rolepos+1];
        }
        m_dwRoleID[rolepos] = 0;
        m_pDBRole[rolepos] = NULL;
        m_byRoleCount--;
    }

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDBUser::RemoveAllRoles()
{
    BOOL bRet = FALSE;
    CDBRoleMgr& rolemgr = CDBServer::GetInstance().m_rolemgr;

    LOG_PROCESS_ERROR(m_state == dusLogout);
    LOG_PROCESS_ERROR(m_dbstate == dtsFree);
    LOG_PROCESS_ERROR(m_pPlayingRole == NULL);

    for(UINT8 rolepos=0; rolepos<m_byRoleCount; rolepos++)
    {
        CDBRole* dbrole = m_pDBRole[rolepos];
        if (dbrole)
        {
            LOG_PROCESS_ERROR(dbrole->m_dbtask == CDBRole::DB_TASK_FREE);
            LOG_PROCESS_ERROR(dbrole->m_lockstate == CDBRole::LOCK_STATE_UNLOCKED);

            bRet = CDBServer::GetInstance().m_rolemgr.DelDBRole(dbrole);
            LOG_CHECK_ERROR(bRet);

            dbrole->m_dbuser = NULL;
            bRet = dbrole->ClearCache(TRUE);
            LOG_CHECK_ERROR(bRet);

            dbrole->m_lockstate = CDBRole::LOCK_STATE_INVALID;
        }
    }

    m_byRoleCount = 0;
    m_bRoleListCached = FALSE;
    memset(m_BaseData, 0, sizeof(m_BaseData));
    memset(m_pDBRole, 0, sizeof(m_pDBRole));

    return TRUE;

Exit0:
    return FALSE;
}
