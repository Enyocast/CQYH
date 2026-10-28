/********************************************************************
	created:	23:12:2013   15:11
	file:		gm_query_thread.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_GM_QUERY_THREAD_H_
#define _H_GM_QUERY_THREAD_H_

#include "thread.h"
#include "gm_db_def.h"
#include "circle_list.h"
#include "gm_db_operation.h"
#include "../dbserver/db/db_load_role.h"
#include "../dbserver/db/db_save_role.h"

struct MYSQL;
struct DBSetting;

class CGMQueryThread : public CThread
{
public:
    CGMQueryThread();
    virtual ~CGMQueryThread();

    BOOL Init(UINT32 dwResultCount);
    BOOL UnInit();
    BOOL ReInit();

    //BOOL    LoadItemLogWithGuid(CMD_DATA_TEMP_BASE *pCmd, UINT64 llGuid);
    //BOOL    LoadItemLogWithTempID(CMD_DATA_TEMP_BASE *pCmd, UINT32 dwTemplateID);
    //BOOL    LoadItemLogWithRoleGuid(CMD_DATA_TEMP_BASE *pCmd, UINT32 dwRoleID, UINT64 llGuid);
    //BOOL    LoadItemLogWithRoleTempID(CMD_DATA_TEMP_BASE *pCmd, UINT32 dwRoleID, UINT32 dwTemplateID);
    //BOOL    LoadItemLogWithRole(CMD_DATA_TEMP_BASE *pCmd, UINT32 dwRoleID);

    //BOOL    ViewRoleData(CMD_DATA_TEMP_BASE *pCmd);
    //BOOL    LoadRoleData(CMD_DATA_TEMP_BASE *pCmd);
    //BOOL    SaveRoleData(CMD_DATA_TEMP_BASE* pCmd);

    DB_OPERATION_RESULT* GetResult();

protected:
    virtual VOID ThrdProc();

private:
    INT32 _CheckSqlResult(BOOL bRet, MYSQL_STMT* stmt);

    BOOL m_bServerOK;

    CCircleList m_requests;
    CCircleList m_results;

    CDBItemLogWithGuid      m_DBItemLogWithGuid;
    CDBItemLogWithTempID    m_DBItemLogWithTempID;
    CDBItemLogWithRoleGuid  m_DBItemLogWithRoleGuid;
    CDBItemLogWithRoleTempID    m_DBItemLogWithRoleTempID;
    CDBItemLogWithRole      m_DBItemLogWithRole;

    CDBLoadRole             m_DBLoadRole;
    CDBSaveRole             m_DBSaveRole;
};














#endif //_H_GM_QUERY_THREAD_H_





















