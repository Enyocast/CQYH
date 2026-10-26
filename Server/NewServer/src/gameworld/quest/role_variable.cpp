#include "stdafx.h"
#include "role_variable.h"

CRoleVariable::CRoleVariable()
{
}

CRoleVariable::~CRoleVariable()
{
    UnInit();
}

BOOL CRoleVariable::Init(void)
{
    return TRUE;
}

BOOL CRoleVariable::UnInit(void)
{
    return TRUE;
}

BOOL CRoleVariable::Load(const char* pData, UINT32 dwSize)
{
    INT32* pnCount = NULL;
    INT16* pwIndex = NULL;
    INT32* pnValue = NULL;

    LOG_PROCESS_ERROR(pData);

    memset(m_nVarList, 0, sizeof(m_nVarList));

    pnCount = (INT32*)pData;
    pData += sizeof(INT32);
    LOG_PROCESS_ERROR(dwSize >= sizeof(INT32) + *pnCount * (sizeof(INT16) + sizeof(INT32)));

    for (INT32 nIndex = 0; nIndex < *pnCount; nIndex++)
    {
        pwIndex = (INT16*)pData;
        pData += sizeof(INT16);

        pnValue = (INT32*)pData;
        pData += sizeof(INT32);

        LOG_PROCESS_ERROR(*pwIndex >= 0 && *pwIndex < MAX_ROLE_VAR_COUNT);
        m_nVarList[*pwIndex] = *pnValue;
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CRoleVariable::Save(char* pData, UINT32& rdwSize)
{
    INT32* pnCount = NULL;
    INT16* pwIndex = NULL;
    INT32* pnValue = NULL;
    char* pEnd = pData + rdwSize;

    LOG_PROCESS_ERROR(pData);

    pnCount = (INT32*)pData;
    pData += sizeof(INT32);
    rdwSize -= sizeof(INT32);
    LOG_PROCESS_ERROR(pData < pEnd);

    *pnCount = 0;
    for (INT32 nIndex = 0; nIndex < MAX_ROLE_VAR_COUNT; nIndex++)
    {
        pwIndex = (INT16*)pData;
        pData += sizeof(INT16);
        rdwSize -= sizeof(INT16);

        pnValue = (INT32*)pData;
        pData += sizeof(INT32);
        rdwSize -= sizeof(INT32);

        LOG_PROCESS_ERROR(pData < pEnd);

        if (m_nVarList[nIndex] != 0)
        {
            *pwIndex = nIndex;
            *pnValue = m_nVarList[nIndex];
            (*pnCount)++;
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

void CRoleVariable::SetValue(INT32 nIndex, INT32 nValue)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_ROLE_VAR_COUNT);

    m_nVarList[nIndex] = nValue;

Exit0:
    return;
}

INT32 CRoleVariable::GetValue(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_ROLE_VAR_COUNT);

    return m_nVarList[nIndex];

Exit0:
    return 0;
}
