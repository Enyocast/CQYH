#include "stdafx.h"
#include "db_init.h"

#include "ifile.h"
#include "mysql.h"

BOOL ExistDB(MYSQL* mysql, const char* dbname)
{
    BOOL found = FALSE;
    MYSQL_RES* mysql_result = mysql_list_dbs(mysql, dbname);
    LOG_PROCESS_ERROR(mysql_result);

    while (mysql_fetch_row(mysql_result))
    {
        found = TRUE;
    }

Exit0:
    if (mysql_result)
        mysql_free_result(mysql_result);

    return found;
}

INT32 GetDBVersion(MYSQL* mysql)
{
	INT32 nResult = 0;
	INT32 nRetCode = 0;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = NULL;

	nRetCode = mysql_query(mysql, "select number from version where id = \"all\";");
	LOG_PROCESS_ERROR(nRetCode == 0);

	result = mysql_store_result(mysql);
	LOG_PROCESS_ERROR(result);

	row = mysql_fetch_row(result);
	LOG_PROCESS_ERROR(row);

	nResult = atoi(row[0]);

	if (result)
		mysql_free_result(result);

	return nResult;
Exit0:
	if (result)
		mysql_free_result(result);

	if (mysql_error(mysql))
		CRI(mysql_error(mysql));

	return -1;
}

BOOL ExecuteSqlFile(MYSQL* mysql, const char* dbprefix, INT32 nVersion)
{
	INT32 nRetCode = 0;
	IFile* pFile = NULL;
	char filename[512];
	INT32 filesize = 0;
	char* filecontent = NULL;
	MYSQL_RES* result = NULL;

	snprintf(filename, 512, "commonconfig/sql/%s%d.sql", dbprefix, nVersion);

	pFile = g_OpenFile(filename, "rt");
	LOG_PROCESS_ERROR(pFile);

	filesize = pFile->Size();
	LOG_PROCESS_ERROR(filesize > 0);

	filesize += 32;
	filecontent = new char[filesize];
	memset(filecontent, 0, filesize);

	nRetCode = pFile->Read(filecontent, filesize);
	LOG_PROCESS_ERROR(nRetCode > 0);

	nRetCode = mysql_query(mysql, filecontent);
	LOG_PROCESS_ERROR(nRetCode == 0);

	do
	{
		result = mysql_store_result(mysql);
		if (result == NULL)
		{
			LOG_PROCESS_ERROR(mysql_field_count(mysql) == 0);
		}
		else
		{
			mysql_free_result(result);
		}
	} while (!mysql_next_result(mysql));

	pFile->Close();
	pFile = NULL;
	SAFE_DELETE_ARRAY(filecontent);

	INF("executed sql file %s%d.sql successfully", dbprefix, nVersion);

	return TRUE;

Exit0:
	CRI("failed to execute sql file %d.sql", nVersion);

	if (mysql_error(mysql))
		CRI(mysql_error(mysql));

	if (pFile)
		pFile->Close();

	if (filecontent)
		SAFE_DELETE_ARRAY(filecontent);

	return FALSE;
}

BOOL CreateDB(MYSQL* mysql, const char* dbname)
{
    char db_sql[512];
    INT32 nRetCode = 0;

    snprintf(db_sql, 512, "CREATE DATABASE %s;", dbname);

    nRetCode = mysql_query(mysql, db_sql);
    LOG_PROCESS_ERROR(nRetCode == 0);

	return TRUE;
Exit0:
	CRI("MYSQL Err: %s", mysql_error(mysql));

    return FALSE;
}

BOOL UpdateDB(MYSQL* mysql, const char* dbname, const char* dbprefix, INT32 dbversion)
{
	INT32 nRetCode = 0;
	char db_sql[512];

	snprintf(db_sql, 512, "USE %s;", dbname);

	nRetCode = mysql_query(mysql, db_sql);
	LOG_PROCESS_ERROR(nRetCode == 0);

    INT32 nIndex = GetDBVersion(mysql);
    if (nIndex > dbversion)
    {
        INF("Current DB Version is %d. (Newer Than Required)", nIndex);
        return FALSE;
    }
    if (nIndex == dbversion)
    {
        INF("Current DB Version is %d. (Already Up To Date)", nIndex);
        return TRUE;
    }

    nIndex++;
    for (; nIndex <= dbversion; nIndex++)
	{
        nRetCode = ExecuteSqlFile(mysql, dbprefix, nIndex);
        if (nRetCode)
            INF("Updated DB Version To %d Successfully.", nIndex);
        else
        {
            INF("Update DB Version To %d Failed.", nIndex);
            return FALSE;
        }
	}

	return TRUE;

Exit0:
    CRI("MYSQL Err: %s", mysql_error(mysql));

    return FALSE;
}
