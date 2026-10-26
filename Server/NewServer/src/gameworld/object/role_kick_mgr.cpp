#include "stdafx.h"

#ifndef _ROBOT
#include "message_handler.h"
#include "role_kick_mgr.h"
#include "role.h"

CRoleKickMgr::CRoleKickMgr()
{
	m_lstKickRole.clear();
}

CRoleKickMgr CRoleKickMgr::ms_Instance;

CRoleKickMgr& CRoleKickMgr::GetInstance()
{
	return ms_Instance;
}

BOOL CRoleKickMgr::AddToKickList(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INF("add role %d to kick list ", dwRoleID);
	m_lstKickRole.push_back(dwRoleID);

	return TRUE;
}

BOOL CRoleKickMgr::KickPendingRoles(void)
{
	INT32 nRetCode = 0;
	INT32 nKickCount = 16; // g_GWConfig.nKickRoleCountPerFrame;
	UINT32 dwRoleID = 0;
	std::list<UINT32>::iterator itr;

	PROCESS_SUCCESS(m_lstKickRole.size() == 0);

	itr = m_lstKickRole.begin();
	while (itr != m_lstKickRole.end() && nKickCount > 0)
	{
		dwRoleID = *itr;

		nRetCode = CCliMessageHandler::GetInstance().RealKickUser(dwRoleID);
		LOG_CHECK_ERROR( nRetCode );

		m_lstKickRole.pop_front();

		--nKickCount;
		itr = m_lstKickRole.begin();
	}

Exit1:
	return TRUE;
Exit0:
	return FALSE;
}

#endif	// _ROBOT