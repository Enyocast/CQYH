#include "stdafx.h"
#include "db_load_role.h"
#include "../logic/mem_mgr.h"
#include "zlib.h"

#define LOAD_ROLE "SELECT RoleData FROM role WHERE RoleID = ?"

CDBLoadRole::CDBLoadRole()
{
    m_stmt = NULL;
    m_dwRoleID = 0;
    memset(&m_bind_param, 0, sizeof(m_bind_param));
    memset(&m_bind_result, 0, sizeof(m_bind_result));
}

CDBLoadRole::~CDBLoadRole()
{

}

BOOL CDBLoadRole::Init(MYSQL* mysql)
{
    INT32 nRet = 0;
    UINT32 param_count = 0;

    LOG_PROCESS_ERROR(mysql);

    m_stmt = mysql_stmt_init(mysql);
    LOG_PROCESS_ERROR(m_stmt);

    nRet = mysql_stmt_prepare(m_stmt, LOAD_ROLE, (unsigned long)strlen(LOAD_ROLE));
    LOG_PROCESS_ERROR(nRet == 0);

    param_count = mysql_stmt_param_count(m_stmt);
    LOG_PROCESS_ERROR(param_count == 1);

    memset(&m_bind_param, 0, sizeof(m_bind_param));
    m_bind_param.buffer_type = MYSQL_TYPE_LONG;
    m_bind_param.buffer = &m_dwRoleID;
    nRet = mysql_stmt_bind_param(m_stmt, &m_bind_param);
    LOG_PROCESS_ERROR(nRet == 0);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDBLoadRole::UnInit()
{
    my_bool res = 0;
    if (m_stmt)
    {
        res = mysql_stmt_close(m_stmt);
        m_stmt = NULL;
    }
    return res == 0;
}

BOOL CDBLoadRole::DoLoadRole(char* buf, UINT32 bufsize, UINT32& outsize)
{
    INT32 nRet = 0;
    unsigned char zipped_role_data[MEM_SIZE];
    unsigned long zipped_role_data_len = MEM_SIZE;
    unsigned long out_len = bufsize;

    LOG_PROCESS_ERROR(buf);

    nRet = mysql_stmt_execute(m_stmt);
    LOG_PROCESS_ERROR(nRet == 0);

    memset(&m_bind_result, 0, sizeof(m_bind_result));
    m_bind_result.buffer_type = MYSQL_TYPE_BLOB;
    m_bind_result.buffer = zipped_role_data;
    m_bind_result.buffer_length = zipped_role_data_len;
    m_bind_result.length = &zipped_role_data_len;
    nRet = mysql_stmt_bind_result(m_stmt, &m_bind_result);
    LOG_PROCESS_ERROR(nRet == 0);

    nRet = mysql_stmt_fetch(m_stmt);
    LOG_PROCESS_ERROR(nRet == 0);

    nRet = uncompress((unsigned char*)buf, &out_len, zipped_role_data, zipped_role_data_len);
    //debug
    if (nRet != Z_OK)
    {
        DBG("unzip failed, roleid:%u, zipped data len:%u, zipped data crc:%X", m_dwRoleID, zipped_role_data_len,
            crc32(0, (const Bytef*)zipped_role_data, zipped_role_data_len));
    }
    //end debug

    {
        INT32 nMoreDataCount = 0;
        while(mysql_stmt_fetch(m_stmt) == 0)
            nMoreDataCount++;
        LOG_PROCESS_ERROR(nMoreDataCount == 0);
    }

    LOG_PROCESS_ERROR(nRet == Z_OK);

    outsize = out_len;
    return TRUE;

Exit0:
    DBG("%d, %s", mysql_stmt_errno(m_stmt), mysql_stmt_error(m_stmt));
    return FALSE;
}
