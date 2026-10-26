#ifndef _DB_LOAD_ROLE_H_
#define _DB_LOAD_ROLE_H_

#include "mysql.h"

class CDBLoadRole
{
public:
    CDBLoadRole();
    ~CDBLoadRole();

    BOOL Init(MYSQL* mysql);
    BOOL UnInit();

    BOOL DoLoadRole(char* buf, UINT32 bufsize, UINT32& outsize);

    UINT32 m_dwRoleID;

    MYSQL_STMT* m_stmt;

private:
    MYSQL_BIND m_bind_param;
    MYSQL_BIND m_bind_result;
};

#endif // _DB_LOAD_ROLE_H_
