#include "stdafx.h"
#include "cash_accounting_stmt.list.h"

SQL_STMT_DATA g_CASqlStmtList[caSqlTotal] =
{
	{0, caSqlSelectLogoutRole, "SELECT UNIX_TIMESTAMP(LogTime{d}), RoleID{d}, Money1{d}, Money2{d}, Name{s21} FROM logdata_rolelogout_basic"},
	{0, caSqlSelectRoleMoney,  "SELECT SourceID{d}, TargetID{d}, MoneyType{c}, MoneyCount{d} FROM logdata_money WHERE (SourceID = [d] or TargetID = [d]) AND (LogTime >= FROM_UNIXTIME([d]) AND LogTime <= FROM_UNIXTIME([d]))"},
};