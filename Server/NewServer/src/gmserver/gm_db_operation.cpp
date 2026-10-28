/********************************************************************
	created:	23:12:2013   15:18
	file:		gm_db_operation.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "gm_db_operation.h"

#define LOAD_ITEM_LOG_GUID "SELECT UNIX_TIMESTAMP(LogTime), GroupID, AreaID, ActionType, TemplateID, Guid, ItemCount, SrcRoleID, TargetRoleID, Reason FROM logdata_item WHERE Guid = ?"
#define LOAD_ITEM_LOG_TEMP_ID "SELECT UNIX_TIMESTAMP(LogTime), GroupID, AreaID, ActionType, TemplateID, Guid, ItemCount, SrcRoleID, TargetRoleID, Reason FROM logdata_item WHERE TemplateID = ?"
#define LOAD_ITEM_LOG_ROLE_GUID "SELECT UNIX_TIMESTAMP(LogTime), GroupID, AreaID, ActionType, TemplateID, Guid, ItemCount, SrcRoleID, TargetRoleID, Reason FROM logdata_item WHERE SrcRoleID = ? OR TargetRoleID = ? AND Guid = ?"
#define LOAD_ITEM_LOG_ROLE_TEMP_ID "SELECT UNIX_TIMESTAMP(LogTime), GroupID, AreaID, ActionType, TemplateID, Guid, ItemCount, SrcRoleID, TargetRoleID, Reason FROM logdata_item WHERE SrcRoleID = ? OR TargetRoleID = ? AND TemplateID = ?"
#define LOAD_ITEM_LOG_ROLE "SELECT UNIX_TIMESTAMP(LogTime), GroupID, AreaID, ActionType, TemplateID, Guid, ItemCount, SrcRoleID, TargetRoleID, Reason FROM logdata_item WHERE SrcRoleID = ? OR TargetRoleID = ?"



CDBItemLogWithGuid::CDBItemLogWithGuid() :
m_stmt(NULL),
m_llGuid(0)
{
    memset(&m_bind_param, 0, sizeof(m_bind_param));
    memset(m_bind_result, 0, sizeof(m_bind_result));
}

CDBItemLogWithGuid::~CDBItemLogWithGuid()
{

}

BOOL CDBItemLogWithGuid::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, LOAD_ITEM_LOG_GUID, (unsigned long)strlen(LOAD_ITEM_LOG_GUID));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 1);

    memset(&m_bind_param, 0, sizeof(m_bind_param));
    m_bind_param.buffer_type = MYSQL_TYPE_LONGLONG;
    m_bind_param.buffer = &m_llGuid;
    nRet = mysql_stmt_bind_param(m_stmt, &m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDBItemLogWithGuid::UnInit()
{
    if (m_stmt)
    {
        bool bRet = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
        return 0 == bRet;
    }
    else
        return TRUE;
}

BOOL CDBItemLogWithGuid::DoLoadItemLog(UINT64 llGuid, DB_OP_LOG_ITEM_RESULT *res)
{
    INT32   nRet = 0;
    DB_ITEM_LOG_DATA   data;

    m_llGuid = llGuid;

    nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(0 == nRet);

    memset(m_bind_result, 0, sizeof(m_bind_result));

    m_bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[0].buffer = &data.nLogTime;

    m_bind_result[1].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[1].buffer = &data.bySvrGroupID;

    m_bind_result[2].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[2].buffer = &data.byAreaID;

    m_bind_result[3].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[3].buffer = data.szActionType;
    m_bind_result[3].buffer_length = sizeof(data.szActionType);

    m_bind_result[4].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[4].buffer = &data.dwTemplateID;

    m_bind_result[5].buffer_type = MYSQL_TYPE_LONGLONG;
    m_bind_result[5].buffer = &data.llGuid;

    m_bind_result[6].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[6].buffer = &data.byCount;

    m_bind_result[7].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[7].buffer = &data.dwSrcRoleID;

    m_bind_result[8].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[8].buffer = &data.dwTargetRoleID;

    m_bind_result[9].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[9].buffer = data.szReason;
    m_bind_result[9].buffer_length = sizeof(data.szReason);

    nRet = mysql_stmt_bind_result(m_stmt, m_bind_result);
    LOG_PROCESS_ERROR(0 == nRet);

    res->listItemLogData.clear();
    while (mysql_stmt_fetch(m_stmt) == 0)
    {
        res->listItemLogData.push_back(data);
        memset(&data, 0, sizeof(data));
    }

    return TRUE;
Exit0:
    return FALSE;
}


CDBItemLogWithTempID::CDBItemLogWithTempID() :
m_stmt(NULL),
m_dwTemplateID(0)
{
    memset(&m_bind_param, 0, sizeof(m_bind_param));
    memset(m_bind_result, 0, sizeof(m_bind_result));
}

CDBItemLogWithTempID::~CDBItemLogWithTempID()
{

}

BOOL CDBItemLogWithTempID::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, LOAD_ITEM_LOG_TEMP_ID, (unsigned long)strlen(LOAD_ITEM_LOG_TEMP_ID));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 1);

    memset(&m_bind_param, 0, sizeof(m_bind_param));
    m_bind_param.buffer_type = MYSQL_TYPE_LONG;
    m_bind_param.buffer = &m_dwTemplateID;
    nRet = mysql_stmt_bind_param(m_stmt, &m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDBItemLogWithTempID::UnInit()
{
    if (m_stmt)
    {
        bool bRet = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
        return 0 == bRet;
    }
    else
        return TRUE;
}

BOOL CDBItemLogWithTempID::DoLoadItemLog(UINT32 dwTemplateID, DB_OP_LOG_ITEM_RESULT *res)
{
    INT32   nRet = 0;
    DB_ITEM_LOG_DATA   data;

    m_dwTemplateID = dwTemplateID;

    nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(0 == nRet);

    memset(m_bind_result, 0, sizeof(m_bind_result));

    m_bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[0].buffer = &data.nLogTime;

    m_bind_result[1].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[1].buffer = &data.bySvrGroupID;

    m_bind_result[2].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[2].buffer = &data.byAreaID;

    m_bind_result[3].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[3].buffer = data.szActionType;
    m_bind_result[3].buffer_length = sizeof(data.szActionType);

    m_bind_result[4].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[4].buffer = &data.dwTemplateID;

    m_bind_result[5].buffer_type = MYSQL_TYPE_LONGLONG;
    m_bind_result[5].buffer = &data.llGuid;

    m_bind_result[6].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[6].buffer = &data.byCount;

    m_bind_result[7].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[7].buffer = &data.dwSrcRoleID;

    m_bind_result[8].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[8].buffer = &data.dwTargetRoleID;

    m_bind_result[9].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[9].buffer = data.szReason;
    m_bind_result[9].buffer_length = sizeof(data.szReason);

    nRet = mysql_stmt_bind_result(m_stmt, m_bind_result);
    LOG_PROCESS_ERROR(0 == nRet);

    res->listItemLogData.clear();
    while (mysql_stmt_fetch(m_stmt) == 0)
    {
        res->listItemLogData.push_back(data);
        memset(&data, 0, sizeof(data));
    }

    return TRUE;
Exit0:
    return FALSE;
}


CDBItemLogWithRoleGuid::CDBItemLogWithRoleGuid() :
m_stmt(NULL),
m_llGuid(0),
m_dwRoleID(0)
{
    memset(m_bind_param, 0, sizeof(m_bind_param));
    memset(m_bind_result, 0, sizeof(m_bind_result));
}

CDBItemLogWithRoleGuid::~CDBItemLogWithRoleGuid()
{

}

BOOL CDBItemLogWithRoleGuid::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, LOAD_ITEM_LOG_ROLE_GUID, (unsigned long)strlen(LOAD_ITEM_LOG_ROLE_GUID));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 3);

    memset(m_bind_param, 0, sizeof(m_bind_param));

    m_bind_param[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[0].buffer = &m_dwRoleID;
    m_bind_param[1].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[1].buffer = &m_dwRoleID;
    m_bind_param[2].buffer_type = MYSQL_TYPE_LONGLONG;
    m_bind_param[2].buffer = &m_llGuid;

    nRet = mysql_stmt_bind_param(m_stmt, m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDBItemLogWithRoleGuid::UnInit()
{
    if (m_stmt)
    {
        bool bRet = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
        return 0 == bRet;
    }
    else
        return TRUE;
}

BOOL CDBItemLogWithRoleGuid::DoLoadItemLog(UINT32 dwRoleID, UINT64 llGuid, DB_OP_LOG_ITEM_RESULT *res)
{
    INT32   nRet = 0;
    DB_ITEM_LOG_DATA   data;

    m_dwRoleID = dwRoleID;
    m_llGuid = llGuid;

    nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(0 == nRet);

    memset(m_bind_result, 0, sizeof(m_bind_result));

    m_bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[0].buffer = &data.nLogTime;

    m_bind_result[1].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[1].buffer = &data.bySvrGroupID;

    m_bind_result[2].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[2].buffer = &data.byAreaID;

    m_bind_result[3].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[3].buffer = data.szActionType;
    m_bind_result[3].buffer_length = sizeof(data.szActionType);

    m_bind_result[4].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[4].buffer = &data.dwTemplateID;

    m_bind_result[5].buffer_type = MYSQL_TYPE_LONGLONG;
    m_bind_result[5].buffer = &data.llGuid;

    m_bind_result[6].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[6].buffer = &data.byCount;

    m_bind_result[7].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[7].buffer = &data.dwSrcRoleID;

    m_bind_result[8].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[8].buffer = &data.dwTargetRoleID;

    m_bind_result[9].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[9].buffer = data.szReason;
    m_bind_result[9].buffer_length = sizeof(data.szReason);

    nRet = mysql_stmt_bind_result(m_stmt, m_bind_result);
    LOG_PROCESS_ERROR(0 == nRet);

    res->listItemLogData.clear();
    while (mysql_stmt_fetch(m_stmt) == 0)
    {
        res->listItemLogData.push_back(data);
        memset(&data, 0, sizeof(data));
    }

    return TRUE;
Exit0:
    return FALSE;
}


CDBItemLogWithRoleTempID::CDBItemLogWithRoleTempID() :
m_stmt(NULL),
m_dwTemplateID(0),
m_dwRoleID(0)
{
    memset(m_bind_param, 0, sizeof(m_bind_param));
    memset(m_bind_result, 0, sizeof(m_bind_result));
}

CDBItemLogWithRoleTempID::~CDBItemLogWithRoleTempID()
{

}

BOOL CDBItemLogWithRoleTempID::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, LOAD_ITEM_LOG_ROLE_TEMP_ID, (unsigned long)strlen(LOAD_ITEM_LOG_ROLE_TEMP_ID));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 3);

    memset(m_bind_param, 0, sizeof(m_bind_param));

    m_bind_param[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[0].buffer = &m_dwRoleID;
    m_bind_param[1].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[1].buffer = &m_dwRoleID;
    m_bind_param[2].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[2].buffer = &m_dwTemplateID;

    nRet = mysql_stmt_bind_param(m_stmt, m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDBItemLogWithRoleTempID::UnInit()
{
    if (m_stmt)
    {
        bool bRet = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
        return 0 == bRet;
    }
    else
        return TRUE;
}

BOOL CDBItemLogWithRoleTempID::DoLoadItemLog(UINT32 dwRoleID, UINT32 dwTemplateID, DB_OP_LOG_ITEM_RESULT *res)
{
    INT32   nRet = 0;
    DB_ITEM_LOG_DATA   data;

    m_dwTemplateID = dwTemplateID;
    m_dwRoleID = dwRoleID;

    nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(0 == nRet);

    memset(m_bind_result, 0, sizeof(m_bind_result));

    m_bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[0].buffer = &data.nLogTime;

    m_bind_result[1].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[1].buffer = &data.bySvrGroupID;

    m_bind_result[2].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[2].buffer = &data.byAreaID;

    m_bind_result[3].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[3].buffer = data.szActionType;
    m_bind_result[3].buffer_length = sizeof(data.szActionType);

    m_bind_result[4].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[4].buffer = &data.dwTemplateID;

    m_bind_result[5].buffer_type = MYSQL_TYPE_LONGLONG;
    m_bind_result[5].buffer = &data.llGuid;

    m_bind_result[6].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[6].buffer = &data.byCount;

    m_bind_result[7].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[7].buffer = &data.dwSrcRoleID;

    m_bind_result[8].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[8].buffer = &data.dwTargetRoleID;

    m_bind_result[9].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[9].buffer = data.szReason;
    m_bind_result[9].buffer_length = sizeof(data.szReason);

    nRet = mysql_stmt_bind_result(m_stmt, m_bind_result);
    LOG_PROCESS_ERROR(0 == nRet);

    res->listItemLogData.clear();
    while (mysql_stmt_fetch(m_stmt) == 0)
    {
        res->listItemLogData.push_back(data);
        memset(&data, 0, sizeof(data));
    }

    return TRUE;
Exit0:
    return FALSE;
}





CDBItemLogWithRole::CDBItemLogWithRole() :
m_stmt(NULL),
m_dwRoleID(0)
{
    memset(m_bind_param, 0, sizeof(m_bind_param));
    memset(m_bind_result, 0, sizeof(m_bind_result));
}

CDBItemLogWithRole::~CDBItemLogWithRole()
{

}

BOOL CDBItemLogWithRole::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, LOAD_ITEM_LOG_ROLE, (unsigned long)strlen(LOAD_ITEM_LOG_ROLE));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 2);

    memset(m_bind_param, 0, sizeof(m_bind_param));

    m_bind_param[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[0].buffer = &m_dwRoleID;
    m_bind_param[1].buffer_type = MYSQL_TYPE_LONG;
    m_bind_param[1].buffer = &m_dwRoleID;

    nRet = mysql_stmt_bind_param(m_stmt, m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDBItemLogWithRole::UnInit()
{
    if (m_stmt)
    {
        bool bRet = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
        return 0 == bRet;
    }
    else
        return TRUE;
}

BOOL CDBItemLogWithRole::DoLoadItemLog(UINT32 dwRoleID, DB_OP_LOG_ITEM_RESULT *res)
{
    INT32   nRet = 0;
    DB_ITEM_LOG_DATA   data;

    m_dwRoleID = dwRoleID;

    nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(0 == nRet);

    memset(m_bind_result, 0, sizeof(m_bind_result));

    m_bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[0].buffer = &data.nLogTime;

    m_bind_result[1].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[1].buffer = &data.bySvrGroupID;

    m_bind_result[2].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[2].buffer = &data.byAreaID;

    m_bind_result[3].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[3].buffer = data.szActionType;
    m_bind_result[3].buffer_length = sizeof(data.szActionType);

    m_bind_result[4].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[4].buffer = &data.dwTemplateID;

    m_bind_result[5].buffer_type = MYSQL_TYPE_LONGLONG;
    m_bind_result[5].buffer = &data.llGuid;

    m_bind_result[6].buffer_type = MYSQL_TYPE_TINY;
    m_bind_result[6].buffer = &data.byCount;

    m_bind_result[7].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[7].buffer = &data.dwSrcRoleID;

    m_bind_result[8].buffer_type = MYSQL_TYPE_LONG;
    m_bind_result[8].buffer = &data.dwTargetRoleID;

    m_bind_result[9].buffer_type = MYSQL_TYPE_STRING;
    m_bind_result[9].buffer = data.szReason;
    m_bind_result[9].buffer_length = sizeof(data.szReason);

    nRet = mysql_stmt_bind_result(m_stmt, m_bind_result);
    LOG_PROCESS_ERROR(0 == nRet);

    res->listItemLogData.clear();
    while (mysql_stmt_fetch(m_stmt) == 0)
    {
        res->listItemLogData.push_back(data);
        memset(&data, 0, sizeof(data));
    }

    return TRUE;
Exit0:
    return FALSE;
}















