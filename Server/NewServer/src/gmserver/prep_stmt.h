#ifndef _PREP_STMT_H_
#define _PREP_STMT_H_

#include "mysql.h"


struct DBSetting;


class CPrepStmt
{
public:
    CPrepStmt();
    BOOL Init(DBSetting *pDBSetting, const char* szQuery);
    BOOL UnInit();
    BOOL BindResult(MYSQL_BIND* pResults);
    INT32 Fetch();
    MYSQL_STMT* GetStmt() const { return stmt; }

private:
    MYSQL* mysql;
    MYSQL_STMT* stmt;
    char* query;
};

#endif // _PREP_STMT_H_
