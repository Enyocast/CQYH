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

	inline void Push(STACK_NODE* pNode);
	inline STACK_NODE* Pop(void);

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
    volatile STACK_HEAD  m_StackHead;
};

inline void CFreeStack::Push(STACK_NODE* pNode)
{
	INT64 llRetCode;
	volatile STACK_HEAD OldHead;
	volatile STACK_HEAD NewHead;

	LOG_PROCESS_ERROR(pNode);

	do
	{
		NewHead.Int = OldHead.Int = m_StackHead.Int;

		pNode->pNext = (STACK_NODE*)OldHead.pHead;
		NewHead.pHead = pNode;
		NewHead.uIndex = OldHead.uIndex + 1;

		llRetCode = _CAS(&m_StackHead.Int, NewHead.Int, OldHead.Int);
	} while (llRetCode != OldHead.Int);

Exit0:
	return;
}

inline STACK_NODE* CFreeStack::Pop(void)
{
	STACK_NODE* pResult = NULL;
	INT64 llRetCode = 0;
	volatile STACK_HEAD OldHead;
	volatile STACK_HEAD NewHead;

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

#endif  // _INTERLOCK_SLIST_H_