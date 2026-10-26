/********************************************************************
	created:	23:12:2013   15:20
	file:		gm_db_def.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_GM_DB_DEF_H_
#define _H_GM_DB_DEF_H_


#include "mysql.h"
#include "gm_def.h"

#define MAX_ROLE_DB_BUFFER_LENGTH (64*1024)


enum DB_OP
{
    DB_OP_INVALID,

    DB_OP_ITEM_LOG_RES,
    DB_OP_ITEM_LOG_GUID,
    DB_OP_ITEM_LOG_TEMPID,
    DB_OP_ITEM_LOG_ROLE_GUID,
    DB_OP_ITEM_LOG_ROLE_TEMPID,
    DB_OP_ITEM_LOG_ROLE,

    DB_OP_GM_VIEW_ROLE_REQ,
    DB_OP_GM_VIEW_ROLE_RES,

    DB_OP_GM_LOAD_ROLE_REQ,
    DB_OP_GM_LOAD_ROLE_RES,

    DB_OP_GM_SAVE_ROLE_REQ,
    DB_OP_GM_SAVE_ROLE_RES,
};

struct DB_OPERATION_REQUEST
{
    virtual ~DB_OPERATION_REQUEST() {}
    //CMD_DATA_TEMP_BASE   *pCmd;
    UINT8   m_eOp;
};

struct DB_OPERATION_RESULT
{
    virtual ~DB_OPERATION_RESULT() {}
    //CMD_DATA_TEMP_BASE   *pCmd;
    INT32   m_nResult;
    UINT8   m_eOp;
};

struct DB_OP_GM_VIEW_ROLE_REQUEST : DB_OPERATION_REQUEST 
{
    virtual ~DB_OP_GM_VIEW_ROLE_REQUEST()   {}
    UINT32  dwRoleID;
};

struct DB_OP_GM_VIEW_ROLE_RESULT : DB_OPERATION_RESULT 
{
    virtual ~DB_OP_GM_VIEW_ROLE_RESULT()        { }

    UINT32      dwLength;
    char        szRoleData[MAX_ROLE_DB_BUFFER_LENGTH];
};

struct DB_OP_GM_LOAD_ROLE_REQUEST : DB_OPERATION_REQUEST 
{
    virtual ~DB_OP_GM_LOAD_ROLE_REQUEST()
    {

    }
    UINT32      dwRoleID;
};


struct DB_OP_GM_LOAD_ROLE_RESULT : DB_OPERATION_RESULT 
{
    virtual ~DB_OP_GM_LOAD_ROLE_RESULT()
    {

    }

    UINT32      dwLength;
    char        szRoleData[MAX_ROLE_DB_BUFFER_LENGTH];
};

struct DB_OP_GM_SAVE_ROLE_REQUEST : DB_OPERATION_REQUEST 
{
    virtual  ~DB_OP_GM_SAVE_ROLE_REQUEST()
    {

    }

};

struct DB_OP_GM_SAVE_ROLE_RESULT : DB_OPERATION_RESULT 
{
    virtual ~DB_OP_GM_SAVE_ROLE_RESULT()
    {

    }
};



#endif //_H_GM_DB_DEF_H_


















