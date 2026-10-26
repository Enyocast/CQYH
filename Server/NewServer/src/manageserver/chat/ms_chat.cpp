#include "stdafx.h"
#include "ms_chat.h"
#include "string_def.h"
#include "role_data.h"
#include "onlinerole/online_role_data_mgr.h"
#include "message_handler.h"

CMSChatMgr CMSChatMgr::ms_Instance;

CMSChatMgr::CMSChatMgr()
{
}

CMSChatMgr::~CMSChatMgr()
{
	Uninit();
}

BOOL CMSChatMgr::Init(const char* pcszScriptPath)
{
	return TRUE;
}

BOOL CMSChatMgr::Uninit()
{
	INT32 nRetCode = 0;

	return TRUE;
}

CMSChatMgr & CMSChatMgr::GetInstance()
{
	return ms_Instance;
}

INT32 CMSChatMgr::Say(UINT32 dwSourceRoleID, UINT32 dwTargetRoleID, INT32 nShowLocation, const char* pText, INT32 nGroupID)
{
	INT32 nRetCode = 0;

	MS_ONLINE_ROLE_DATA *pstSourceRoleData = NULL;
	MS_ONLINE_ROLE_DATA *pstTargetRoleData = NULL;

	char szRoleName[ROLE_NAME_LEN] = {0};

	LOG_PROCESS_ERROR(pText);

	pstSourceRoleData = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(dwSourceRoleID);
	if(pstSourceRoleData)
	{
		strxcpy(szRoleName, pstSourceRoleData->pRoleData->szRoleName, ROLE_NAME_LEN);
	}

	nRetCode = CMessageHandler::GetInstance().DoClientChatMessage(szRoleName, dwSourceRoleID, dwTargetRoleID, 
		nShowLocation, pText, nGroupID, FALSE);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}
