#include "stdafx.h"
#include "free_stack.h"

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

