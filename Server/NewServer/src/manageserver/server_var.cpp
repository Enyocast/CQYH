#include "stdafx.h"
#include "server_var.h"

#include "time_ex.h"
#include "db/ms_sql_stmt_list.h"
#include "server_config.h"
#include "manageserver.h"

CServerVar CServerVar::ms_Instance;

CServerVar::CServerVar()
{
}

CServerVar::~CServerVar()
{
    UnInit();
}

BOOL CServerVar::Init(void)
{
    INT32 nRetCode = 0;
    UINT64 qwStartTick = GetTickCountEx();

    INF("loading server variable...");

    nRetCode = CManageServer::GetInstance().GetSqlMgr().SyncExecSqlStmt(msqlSelectServerVar, _Load, NULL, "");
	LOG_PROCESS_ERROR(nRetCode);

	for (INT32 nServerGroup = 0; nServerGroup < MAX_SERVER_GROUP_COUNT; nServerGroup++)
	{
        if (IsValidGroup(nServerGroup) && g_ServerConfig.GroupConfig[nServerGroup].bClearGlobalData)
		{
			m_VarList[nServerGroup].clear();
		}
	}

    INF("loaded server variable successfully(%d ms)", (INT32)(GetTickCountEx() - qwStartTick));

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CServerVar::UnInit(void)
{
    return TRUE;
}

CServerVar& CServerVar::GetInstance(void)
{
    return ms_Instance;
}

INT32 CServerVar::GetVariable(INT32 nServerGroup, UINT64 qwKey)
{
	SERVER_VAR_MAP::iterator it;

	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);
	LOG_PROCESS_ERROR(IsValidGroup(nServerGroup));
	
	it = m_VarList[nServerGroup].find(qwKey);
	PROCESS_ERROR(it != m_VarList[nServerGroup].end());

	// 判断 是不是运2项链专属ServerGroup
	//if (nServerGroup == g_ServerConfig.CC.nItemDropLimitLuck2NecklaceServerGroup)
	//{
	//	it = m_Luck2NecklaceVarList[nServerGroup].find(qwKey);
	//	PROCESS_ERROR(it != m_Luck2NecklaceVarList[nServerGroup].end());
	//}
	//else
	//{
	//	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);
	//	LOG_PROCESS_ERROR(IsValidGroup(nServerGroup));
	//
	//	it = m_VarList[nServerGroup].find(qwKey);
	//	PROCESS_ERROR(it != m_VarList[nServerGroup].end());
	//}

    return it->second;
Exit0:
    return 0;
}

void CServerVar::SetVariable(INT32 nServerGroup, UINT64 qwKey, INT32 nValue)
{
    INT32 nRetCode = 0;
	SERVER_VAR_MAP::iterator it;

	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);
	LOG_PROCESS_ERROR(IsValidGroup(nServerGroup));
	
	it = m_VarList[nServerGroup].find(qwKey);
	if (it == m_VarList[nServerGroup].end())
	{
		nRetCode = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlInsertServerVar, NULL, NULL, "uculd", nServerGroup, qwKey, nValue);
		LOG_CHECK_ERROR(nRetCode);
	}
	else
	{
		nRetCode = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlUpdateServerVar, NULL, NULL, "ducul", nValue, nServerGroup, qwKey);
		LOG_CHECK_ERROR(nRetCode);
	}
	
	m_VarList[nServerGroup][qwKey] = nValue;
	
	nRetCode = CMessageHandler::GetInstance().DoGSUpdateServerVariable(nServerGroup, qwKey, nValue);
	LOG_CHECK_ERROR(nRetCode);

	// 判断 是不是运2项链专属ServerGroup
	//if (nServerGroup == g_ServerConfig.CC.nItemDropLimitLuck2NecklaceServerGroup)
	//{
	//	it = m_Luck2NecklaceVarList[nServerGroup].find(qwKey);
	//	if (it == m_Luck2NecklaceVarList[nServerGroup].end())
	//	{
	//		nRetCode = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlInsertServerVar, NULL, NULL, "uculd", nServerGroup, qwKey, nValue);
	//		LOG_CHECK_ERROR(nRetCode);
	//	}
	//	else
	//	{
	//		nRetCode = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlUpdateServerVar, NULL, NULL, "ducul", nValue, nServerGroup, qwKey);
	//		LOG_CHECK_ERROR(nRetCode);
	//	}
	//
	//	m_Luck2NecklaceVarList[nServerGroup][qwKey] = nValue;
	//
	//	nRetCode = CMessageHandler::GetInstance().DoGSUpdateServerVariable(nServerGroup, qwKey, nValue);
	//	LOG_CHECK_ERROR(nRetCode);
	//}
	//else
	//{
	//	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);
	//	LOG_PROCESS_ERROR(IsValidGroup(nServerGroup));
	//
	//	it = m_VarList[nServerGroup].find(qwKey);
	//	if (it == m_VarList[nServerGroup].end())
	//	{
	//		nRetCode = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlInsertServerVar, NULL, NULL, "uculd", nServerGroup, qwKey, nValue);
	//		LOG_CHECK_ERROR(nRetCode);
	//	}
	//	else
	//	{
	//		nRetCode = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlUpdateServerVar, NULL, NULL, "ducul", nValue, nServerGroup, qwKey);
	//		LOG_CHECK_ERROR(nRetCode);
	//	}
	//
	//	m_VarList[nServerGroup][qwKey] = nValue;
	//
	//	nRetCode = CMessageHandler::GetInstance().DoGSUpdateServerVariable(nServerGroup, qwKey, nValue);
	//	LOG_CHECK_ERROR(nRetCode);
	//}

	return;
Exit0:
	CRI("failed to set server variable %d-%ul to %d", nServerGroup, qwKey, nValue);
	return;
}

BOOL CServerVar::_Load(std::list<void*>& rResult, void* pUserData)
{
    INT32 nRetCode = 0;
#pragma pack(push, 1)
    struct LOAD_RESULT
    {
        UINT8   byServerGroupID;
        UINT64  qwKey;
        INT32   nValue;
    };
#pragma pack(pop)

    for (std::list<void*>::iterator it = rResult.begin();
        it != rResult.end(); ++it)
    {
        LOAD_RESULT* pLoadResult = (LOAD_RESULT*)*it;

		if (!IsValidGroup(pLoadResult->byServerGroupID))
		{
			CRI("detected server variable data in invalid group %d", pLoadResult->byServerGroupID);
			return FALSE;
		}

        if (g_ServerConfig.GroupConfig[pLoadResult->byServerGroupID].bClearGlobalData)
            CServerVar::ms_Instance.m_VarList[pLoadResult->byServerGroupID][pLoadResult->qwKey] = 0;
		else
            CServerVar::ms_Instance.m_VarList[pLoadResult->byServerGroupID][pLoadResult->qwKey] = pLoadResult->nValue;
    }

Exit0:
    return TRUE;
}
