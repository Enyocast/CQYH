#ifndef _DB_OPERATION_H_
#define _DB_OPERATION_H_

#include "mysql.h"

enum DB_OP
{
    DB_OP_INVALID,

};

struct DB_OPERATION_REQUEST
{
    virtual ~DB_OPERATION_REQUEST() {}
    UINT8 m_eOp;
};

struct DB_OPERATION_RESULT
{
    virtual ~DB_OPERATION_RESULT() {}
    INT32 m_nResult;
    UINT8 m_eOp;
};

#endif // _DB_OPERATION_H_
