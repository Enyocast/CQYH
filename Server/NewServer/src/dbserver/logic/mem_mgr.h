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

    void Push(DB_ROLE_DATA* pData);     //工作线程归还
    DB_ROLE_DATA* Pop(void);            //主线程拿

private:
    CFreeStack m_FreeStack; //主线程从这里拿空闲的内存，工作线程把空闲的内存放到这里
    MemPtr m_memptr;
};

#endif // _MEM_MGR_H_
