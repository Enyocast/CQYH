#include "stdafx.h"
#include "db_update_role_delete_time.h"

#define DELETE_ROLE "UPDATE role SET DeleteTime = FROM_UNIXTIME(NULLIF(?, 0)) WHERE RoleID = ?"

CDBUpdateRoleDeleteTime::CDBUpdateRoleDeleteTime()
{
    m_stmt = NULL;
    m_dwRoleID = 0;
    m_dwDeleteTime = 0;
    memset(m_bind_param, 0, sizeof(m_bind_param));
}

CDBUpdateRoleDeleteTime::~CDBUpdateRoleDeleteTime()
{

}

BOOL CDBUpdateRoleDeleteTime::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, DELETE_ROLE, (unsigned long)strlen(DELETE_ROLE));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 2);

    memset(m_bind_param, 0, sizeof(m_bind_param));

    m_bind_param[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[0].buffer = &m_dwDeleteTime;

    m_bind_param[1].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[1].buffer = &m_dwRoleID;

    nRet = mysql_stmt_bind_param(m_stmt, m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDBUpdateRoleDeleteTime::UnInit()
{
    bool res = 0;
    if (m_stmt)
    {
        res = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
    }
    return res == 0;
}

BOOL CDBUpdateRoleDeleteTime::DoUpdate()
{
    INT32 nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;

Exit0:
    DBG("%d, %s", mysql_stmt_errno(m_stmt), mysql_stmt_error(m_stmt));
    return FALSE;
}
