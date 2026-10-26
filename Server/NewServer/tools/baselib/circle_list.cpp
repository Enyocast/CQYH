#include "stdafx.h"
#include "circle_list.h"

CCircleList::CCircleList()
{
    m_dwSize = m_dwHead = m_dwRear = 0;
    m_ppData = NULL;
}

CCircleList::~CCircleList()
{
    UnInit();
}

BOOL CCircleList::Init(UINT32 dwSize)
{
    LOG_PROCESS_ERROR(dwSize > 0);

    m_ppData = new void*[dwSize];
    LOG_PROCESS_ERROR(m_ppData);

    m_dwSize = dwSize;
    m_dwHead = m_dwRear = 0;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCircleList::UnInit(void)
{
    SAFE_DELETE_ARRAY(m_ppData);
    m_dwSize = 0;

    return TRUE;
}

