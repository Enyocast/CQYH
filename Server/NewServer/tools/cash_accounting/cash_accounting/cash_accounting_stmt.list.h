#ifndef _CASH_ACCOUNTING_STMT_LIST
#define _CASH_ACCOUNTING_STMT_LIST

#include "sql_mgr.h"

 enum CASH_SQL_STMT_ID
 {
 	caSqlSelectLogoutRole,
 	caSqlSelectRoleMoney,
 
 	caSqlTotal,
 };
 
 extern SQL_STMT_DATA g_CASqlStmtList[caSqlTotal];

#endif	//_CASH_ACCOUNTING_STMT_LIST