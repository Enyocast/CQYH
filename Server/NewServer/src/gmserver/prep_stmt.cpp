#include "stdafx.h"
#include "prep_stmt.h"

#include "gmserver.h"

CPrepStmt::CPrepStmt()
:mysql(NULL)
,stmt(NULL)
,query(NULL)
{
}

BOOL CPrepStmt::Init(DBSetting *pDBSetting, const char* szQuery)
{
    INT32 nRet = 0;
    MYSQL* res_mysql = NULL;
    LOG_PROCESS_ERROR(pDBSetting);

    LOG_PROCESS_ERROR(mysql == NULL);
    LOG_PROCESS_ERROR(stmt == NULL);

    mysql = mysql_init(NULL);
    LOG_PROCESS_ERROR(mysql);

    res_mysql = mysql_real_connect(
        mysql,
        pDBSetting->szServerAddr,
        pDBSetting->szLoginName,
        pDBSetting->szPassword,
        pDBSetting->szDBName,
        pDBSetting->dwServerPort,
        NULL,
        0);
    LOG_PROCESS_ERROR(res_mysql);

    if (strlen(pDBSetting->szCharSet))
    {
        INT32 nRetCode = mysql_set_character_set(mysql, pDBSetting->szCharSet);
        LOG_PROCESS_ERROR(nRetCode == 0);
    }

    stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(stmt);

    nRet = mysql_stmt_prepare(stmt, szQuery, (unsigned long)strlen(szQuery));
    LOG_PROCESS_ERROR(nRet == 0);

    nRet = mysql_stmt_execute(stmt);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;

Exit0:
    if (mysql)
        INF("%d: %s", mysql_errno(mysql), mysql_error(mysql));

    return FALSE;
}

BOOL CPrepStmt::UnInit()
{
    LOG_PROCESS_ERROR(mysql);
    LOG_PROCESS_ERROR(stmt);

    if (stmt)
    {
        mysql_stmt_close(stmt);
        stmt = NULL;
    }

    if (mysql)
    {
        mysql_close(mysql);
        mysql = NULL;
    }

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CPrepStmt::BindResult(MYSQL_BIND* pResults)
{
    LOG_PROCESS_ERROR(pResults);
    return mysql_stmt_bind_result(stmt, pResults) == 0;

Exit0:
    return FALSE;
}

INT32 CPrepStmt::Fetch()
{
    return mysql_stmt_fetch(stmt);
}
