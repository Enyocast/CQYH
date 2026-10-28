#include "stdafx.h"
#include "db_list_role.h"
#include "../logic/dbuser.h"
#include "server_def.h"
#include "role_db_base_data_conv.h"

#define LIST_ROLE "SELECT RoleID, BaseData, COALESCE(UNIX_TIMESTAMP(DeleteTime), 0) FROM role WHERE UserName = ? AND GroupID = ? AND RoleDeleted = 0 ORDER BY CreateTime"

CDBListRole::CDBListRole()
{
    m_stmt = NULL;
    memset(m_bind_param, 0, sizeof(m_bind_param));
    memset(m_bind_result, 0, sizeof(m_bind_result));
}

CDBListRole::~CDBListRole()
{

}

BOOL CDBListRole::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, LIST_ROLE, (unsigned long)strlen(LIST_ROLE));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 2);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDBListRole::UnInit()
{
    bool res = 0;
    if (m_stmt)
    {
        res = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
    }
    return res == 0;
}

BOOL CDBListRole::DoListRole(CDBUser* dbuser)
{
    unsigned long user_name_len = (unsigned long)strlen(dbuser->m_szUserName);
    INT32 nRet = 0;
    UINT32 roleid;
    UINT32 deletetime;
    char base_data[1024];
    unsigned long base_data_len = sizeof(base_data);
	UINT8 byGroupID = (UINT8)dbuser->m_nServerGroup;
    BOOL bTooManyRoles = FALSE;

    dbuser->m_byRoleCount = 0;

    memset(m_bind_param, 0, sizeof(m_bind_param));

    m_bind_param[0].buffer_type = MYSQL_TYPE_STRING;
    m_bind_param[0].buffer = dbuser->m_szUserName;
    m_bind_param[0].buffer_length = user_name_len;
    m_bind_param[0].length = &user_name_len;

    m_bind_param[1].buffer_type = MYSQL_TYPE_TINY;
    m_bind_param[1].buffer = &byGroupID;

    nRet = mysql_stmt_bind_param(m_stmt, m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(nRet == 0);

    memset(&m_bind_result, 0, sizeof(m_bind_result));

    m_bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[0].buffer = &roleid;

    m_bind_result[1].buffer_type = MYSQL_TYPE_BLOB;
    m_bind_result[1].buffer = &base_data;
    m_bind_result[1].buffer_length = base_data_len;
    m_bind_result[1].length = &base_data_len;

    m_bind_result[2].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[2].buffer = &deletetime;

    nRet = mysql_stmt_bind_result(m_stmt, m_bind_result);
    LOG_PROCESS_ERROR(nRet == 0);

    while ((nRet = mysql_stmt_fetch(m_stmt)) != MYSQL_NO_DATA)
    {
        if (nRet == 0 && dbuser->m_byRoleCount < MAX_ROLE_PER_USER)
        {
            dbuser->m_dwRoleID[dbuser->m_byRoleCount] = roleid;

            nRet = ConvertToBaseDataCurrentVersion(&dbuser->m_BaseData[dbuser->m_byRoleCount], base_data, base_data_len);
            LOG_PROCESS_ERROR(nRet);

            dbuser->m_BaseData[dbuser->m_byRoleCount].dwRoleID = roleid;
            dbuser->m_BaseData[dbuser->m_byRoleCount].dwDeleteTime = deletetime;
            dbuser->m_byRoleCount++;
        }
        else
        {
            bTooManyRoles = TRUE;
        }
    }
    LOG_CHECK_ERROR(!bTooManyRoles);

    return TRUE;

Exit0:
    //DBG("%d, %s", mysql_stmt_errno(m_stmt), mysql_stmt_error(m_stmt));
    return FALSE;
}
