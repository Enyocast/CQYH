#ifndef _DB_INIT_H_
#define _DB_INIT_H_

typedef struct st_mysql MYSQL;

BOOL ExistDB(MYSQL* mysql, const char* dbname);
BOOL CreateDB(MYSQL* mysql, const char* dbname);
BOOL UpdateDB(MYSQL* mysql, const char* dbname, const char* dbprefix, INT32 dbversion);

#endif // _DB_INIT_H_
