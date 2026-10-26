#ifndef _GM_SQL_STMT_LIST_H_
#define _GM_SQL_STMT_LIST_H_

#include "sql_mgr.h"

enum GM_SQL_STMT_ID
{
    // period, average, max
    GMMasterMysqlSelectRoleData,
    GMMasterMysqlSelectMail,
    GMMasterMysqlUpdateRoleData,
    GMMasterMysqlReplaceGM,
    GMMasterMysqlDeleteGM,
    GMMasterMysqlSelectMaxMailID,
    GMMasterMysqlInsertMail,

    GMMasterMysqlDeleteMail,
   

    msqlTotal,
};


enum GM_SLAVER_STMT_ID
{
    GMMysqlSelectRoleID,
    GMMysqlSelectRoleIDByRoleName,
    GMMysqlSelectRoleIDByUserName,
    GMMysqlSelectRoleData,
    GMMysqlSelectGuildID,
    GMMysqlSelectGMForbid,
    GMMysqlSelectMail,
    GMMysqlSelectFreezeTime,
    GMMysqlSelectRoleIDByName,
    GMMysqlSelectGroup,
 
    GMMysqlSelectExchangeLog,
    GMMysqlSelectExchangeHistory,
    GMMysqlSelectSysExchangeOrder,
    GMMysqlSelectSysExchangeLog,

    sSqlTotal,
};

enum GM_LOG_DATA_STMT_ID
{
    GMLogSelectRoleLogin,
    GMLogSelectRoleLogout,
    GMLogSelectItemByGuid,
    GMLogSelectItemByItemID,
    GMLogSelectItemByRoleID,
    GMLogSelectMoneyBySourceRole,
    GMLogSelectMoneyByTargetRole,

    GMLogSelectQuestByRole,
    GMLogSelectQuestByQuest,

    lSqlTotal,
};

extern SQL_STMT_DATA g_GMMasterSqlStmtList[msqlTotal];
extern SQL_STMT_DATA g_GMSlaverStmtList[sSqlTotal];
extern SQL_STMT_DATA g_GMLogDataStmtList[lSqlTotal];

#endif  // _GM_SQL_STMT_LIST_H_