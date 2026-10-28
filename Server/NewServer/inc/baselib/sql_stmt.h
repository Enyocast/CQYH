#ifndef _SQL_STMT_H_
#define _SQL_STMT_H_

#include "base_list.h"

struct SQL_STMT_DATA;
class CSqlStmt;
class CSqlMgr;

typedef BOOL (*SQL_STMT_CALLBACK_FUNC)(std::list<void*>& rResult, void* pUserData);

class CSqlStmt : public BASE_LIST_NODE
{
public:
    BOOL PushParam(INT8 chValue);
    BOOL PushParam(INT16 shValue);
    BOOL PushParam(INT32 nValue);
    BOOL PushParam(INT64 llValue);

    BOOL PushParam(UINT8 byValue);
    BOOL PushParam(UINT16 wValue);
    BOOL PushParam(UINT32 dwValue);
    BOOL PushParam(UINT64 qwValue);

    BOOL PushTime(time_t tValue);
    BOOL PushParam(const char* pcszValue);
    BOOL PushParam(UINT8* pbyValue, UINT32 dwValueSize);
    BOOL PushParamZ(UINT8* pbyValue, UINT32 dwValueSize);

public:
    CSqlStmt();
    ~CSqlStmt();

    BOOL Init(CSqlMgr *pSqlMgr, INT32 nSqlStmtID);
    BOOL UnInit(void);

private:
    const SQL_STMT_DATA*    m_pSqlStmtData;
    INT32                   m_nParamCount;
    UINT8*                  m_pbyParamBuffer;
    INT32                   m_nParamBufferSize;
    std::list<void*>        m_ResultList;
    SQL_STMT_CALLBACK_FUNC  m_pCallbackFunc;
    void*                   m_pUserData;
    INT32                   m_nExecuteCount;

    friend class CSqlMgr;
    CSqlMgr*                 m_pSqlMgr;
};

#endif  // _SQL_STMT_H_