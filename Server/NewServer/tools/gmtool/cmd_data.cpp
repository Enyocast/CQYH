/********************************************************************
	created:	13:1:2014   14:50
	file:		cmd_data.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "cmd_data.h"
#include "string_ex.h"


CCmdData::CCmdData()
{
    m_nUncompleteCount = 0;
    m_dwExeState = CMD_EXE_UNEXECUTE;

    m_Cursor = m_ExecuteSvrList.end();
    m_ExecuteSvrList.clear();
}

CCmdData::~CCmdData()
{
    m_nUncompleteCount = 0;
    m_dwExeState = CMD_EXE_UNEXECUTE;

    m_Cursor = m_ExecuteSvrList.end();
    m_ExecuteSvrList.clear();
}

BOOL CCmdData::Init()
{
    m_nUncompleteCount = 0;
    m_dwExeState = CMD_EXE_UNEXECUTE;

    m_Cursor = m_ExecuteSvrList.end();
    m_ExecuteSvrList.clear();

    return TRUE;
}

BOOL CCmdData::UnInit()
{
    m_nUncompleteCount = 0;
    m_dwExeState = CMD_EXE_UNEXECUTE;
    m_ExecuteSvrList.clear();
    m_Cursor = m_ExecuteSvrList.end();

    return TRUE;
}

INT32 CCmdData::GetSvrNum()
{
    return m_ExecuteSvrList.size();
}

BOOL CCmdData::AddPreExeSvr(UINT32 dwSvrID)
{
    SERVER_CMD_DATA     data;

    data.dwSvrID = dwSvrID;
    data.nResult = errUnknownError;
    data.nState = CMD_EXE_EXECUTING;

    m_ExecuteSvrList.push_back(data);
    ++m_nUncompleteCount;

    return TRUE;
}

void CCmdData::CompleteOne(UINT32 dwSvrID, INT32 nResult)
{
    SVR_LIST::iterator   iter = find(m_ExecuteSvrList.begin(), m_ExecuteSvrList.end(), dwSvrID);
    if (iter != m_ExecuteSvrList.end())
    {
        iter->nState = CMD_EXE_COMPLETE;
        iter->nResult = nResult;
        --m_nUncompleteCount;
    }
}

BOOL CCmdData::IsCompleteAll()
{
    PROCESS_ERROR(0 == m_nUncompleteCount);

    return TRUE;
Exit0:
    return FALSE;
}

SERVER_CMD_DATA* CCmdData::First()
{
    m_Cursor = m_ExecuteSvrList.begin();

    PROCESS_ERROR(m_Cursor != m_ExecuteSvrList.end());

    return &(*m_Cursor);
Exit0:
    return NULL;
}

SERVER_CMD_DATA* CCmdData::Next()
{
    ++m_Cursor;

    PROCESS_ERROR(m_Cursor != m_ExecuteSvrList.end());

    return &(*m_Cursor);
Exit0:
    return NULL;
}



BOOL CCmdGetRoleList::AddNameList(const char *pBuffer, UINT32 dwLength)
{
    LOG_PROCESS_ERROR(pBuffer);

    LOG_PROCESS_ERROR(dwLength < MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);

    strxcpy(m_szBuffer, pBuffer, MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
    m_dwLength = dwLength;


    //char    *pTempBuffer = NULL;
    //char    *pName = NULL;
    //char    ch = ',';
    //LOG_PROCESS_ERROR(pBuffer);

    //pTempBuffer = new char[dwLength + 1];
    //LOG_PROCESS_ERROR(pTempBuffer);

    //strxcpy(pTempBuffer, pBuffer, dwLength+1);

    //pName = strtok(pTempBuffer, &ch);
    //for (INT32 nIndex = 0; pName && nIndex < MAX_SEARCH_ROLE_NUM; ++nIndex)
    //{
    //    sprintf(m_szRoleName[nIndex], pName, ROLE_NAME_LEN);
    //    pName = strtok(NULL, &ch);
    //}

    return TRUE;
Exit0:
    return FALSE;
}

const char *CCmdGetRoleList::FirstName()
{
    m_dwCursor = 0;
    LOG_PROCESS_ERROR(m_dwCount > m_dwCursor);
    LOG_PROCESS_ERROR(m_dwCount > 0);

    return m_szRoleName[m_dwCursor];
Exit0:
    return NULL;
}

const char *CCmdGetRoleList::NextName()
{
    ++m_dwCursor;
    LOG_PROCESS_ERROR(m_dwCursor < m_dwCount);

    return m_szRoleName[m_dwCursor];
Exit0:
    return NULL;
}

void CCmdDelItem::SetName(const char *pcszBuffer)
{
    LOG_PROCESS_ERROR(pcszBuffer);
    strxcpy(szName, pcszBuffer, MAX_ITEM_NAME_LEN);

Exit0:
    return;
}

void CCmdModifyItem::SetName(const char *pcszBuffer)
{
    LOG_PROCESS_ERROR(pcszBuffer);
    strxcpy(szName, pcszBuffer, MAX_ITEM_NAME_LEN);

Exit0:
    return;
}


BOOL CCmdForbidChat::AddNameList(const char *pBuffer, UINT32 dwLength)
{
    LOG_PROCESS_ERROR(pBuffer);

    LOG_PROCESS_ERROR(dwLength < MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);

    strxcpy(m_szBuffer, pBuffer, MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
    m_dwLength = dwLength;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdFreezeRole::AddNameList(const char *pBuffer, UINT32 dwLength)
{
    LOG_PROCESS_ERROR(pBuffer);

    LOG_PROCESS_ERROR(dwLength < MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);

    strxcpy(m_szBuffer, pBuffer, MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
    m_dwLength = dwLength;

    return TRUE;
Exit0:
    return FALSE;
}

//BOOL CCmdUnforbidChat::AddNameList(const char *pBuffer, UINT32 dwLength)
//{
//    LOG_PROCESS_ERROR(pBuffer);
//
//    LOG_PROCESS_ERROR(dwLength < MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
//
//    strxcpy(m_szBuffer, pBuffer, MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
//    m_dwLength = dwLength;
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}
//
//BOOL CCmdUnfreezeRole::AddNameList(const char *pBuffer, UINT32 dwLength)
//{
//    LOG_PROCESS_ERROR(pBuffer);
//
//    LOG_PROCESS_ERROR(dwLength < MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
//
//    strxcpy(m_szBuffer, pBuffer, MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
//    m_dwLength = dwLength;
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}

BOOL CCmdKickRole::AddNameList(const char *pBuffer, UINT32 dwLength)
{
    LOG_PROCESS_ERROR(pBuffer);

    LOG_PROCESS_ERROR(dwLength < MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);

    strxcpy(m_szBuffer, pBuffer, MAX_SEARCH_ROLE_NUM * ROLE_NAME_LEN);
    m_dwLength = dwLength;

    return TRUE;
Exit0:
    return FALSE;
}





//BOOL CCmdSearchRoleList::SetName(const char *pcszName)
//{
//    LOG_PROCESS_ERROR(pcszName);
//    strxcpy(m_szRoleName, pcszName, sizeof(m_szRoleName));
//    return TRUE;
//Exit0:
//    return FALSE;
//}

















BOOL CCmdLogSearchItem::SetRoleName(const char *pcszName)
{
    LOG_PROCESS_ERROR(pcszName);
    strxcpy(m_szRoleName, pcszName, sizeof(m_szRoleName));
    return TRUE;
Exit0:
    return FALSE;
}













