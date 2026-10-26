#ifndef _INTERLOCK_SLIST_H_
#define _INTERLOCK_SLIST_H_

#include "cas.h"

struct STACK_NODE
{
    STACK_NODE* pNext;
    void*       pData;
};

class CFreeStack
{
public:
    CFreeStack();
    ~CFreeStack();

    BOOL Init(void);
    BOOL UnInit(void);

    void Push(STACK_NODE* pNode);
    STACK_NODE* Pop(void);

private:
    union STACK_HEAD
    {
        STACK_NODE*     pHead;
        struct  
        {
            unsigned    Reserved1 : 32;
            unsigned    Reserved2 : 16;
            unsigned    uIndex    : 16;
        };
        INT64           Int;
    };
    STACK_HEAD  m_StackHead;

    FCriticalSection m_Lock;
};

#endif  // _INTERLOCK_SLIST_H_