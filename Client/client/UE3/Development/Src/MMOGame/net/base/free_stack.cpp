#include "stdafx.h"
#include "free_stack.h"
#include "process_error.h"

CFreeStack::CFreeStack()
{
    m_StackHead.Int = 0;
}

CFreeStack::~CFreeStack()
{
    UnInit();
}

BOOL CFreeStack::Init(void)
{
    m_StackHead.Int = 0;

    return TRUE;
}

BOOL CFreeStack::UnInit(void)
{
    LOG_CHECK_ERROR((m_StackHead.Int & 0xFFFFFFFFFFFF) == 0);

    m_StackHead.Int = 0;

    return TRUE;
}

void CFreeStack::Push(STACK_NODE* pNode)
{
    INT64 llRetCode;
    volatile STACK_HEAD OldHead;
    volatile STACK_HEAD NewHead;

    LOG_PROCESS_ERROR(pNode);

    {
		FScopeLock Scope(&m_Lock);

        do 
        {
            NewHead.Int = OldHead.Int = m_StackHead.Int;

            pNode->pNext = (STACK_NODE*)OldHead.pHead;
            NewHead.pHead = pNode;
            NewHead.uIndex = OldHead.uIndex + 1;

            llRetCode = _CAS(&m_StackHead.Int, NewHead.Int, OldHead.Int);
        } while (llRetCode != OldHead.Int);
    }

Exit0:
    return;
}

STACK_NODE* CFreeStack::Pop(void)
{
    STACK_NODE* pResult = NULL;
    INT64 llRetCode = 0;
    volatile STACK_HEAD OldHead;
    volatile STACK_HEAD NewHead;

	FScopeLock Scope(&m_Lock);

    do 
    {
        NewHead.Int = OldHead.Int = m_StackHead.Int;

        pResult = (STACK_NODE*)(OldHead.Int & 0xFFFFFFFFFFFF);
        PROCESS_ERROR(pResult);

        NewHead.pHead = pResult->pNext;
        NewHead.uIndex = OldHead.uIndex + 1;

        llRetCode = _CAS(&m_StackHead.Int, NewHead.Int, OldHead.Int);
    } while (llRetCode != OldHead.Int);
    
Exit0:
    return pResult;
}
