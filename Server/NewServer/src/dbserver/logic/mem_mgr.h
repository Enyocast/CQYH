#ifndef _MEM_MGR_H_
#define _MEM_MGR_H_

#include "share_mem.h"
#include "free_stack.h"

struct CTRL_NODE
{
    STACK_NODE StackNode;
    UINT32 dwDataSize;
    UINT64 LastModified;
    UINT64 LastSaved;
    UINT32 Reading;
};

static const UINT32 MEM_SIZE = 16*1024;
static const UINT32 DATA_SIZE = MEM_SIZE - sizeof(CTRL_NODE);

struct DB_ROLE_DATA
{
    CTRL_NODE CtrlNode;
    char RoleData[DATA_SIZE];
};

class CMemMgr
{
public:
    CMemMgr();
    ~CMemMgr();

    BOOL Init(UINT32 dwMemCount);
    BOOL UnInit();

    void Push(DB_ROLE_DATA* pData);     //Returned by worker thread
    DB_ROLE_DATA* Pop(void);            //Acquired by main thread

private:
    CFreeStack m_FreeStack; //Main thread acquires free memory here; worker thread returns free memory here
    MemPtr m_memptr;
};

#endif // _MEM_MGR_H_
