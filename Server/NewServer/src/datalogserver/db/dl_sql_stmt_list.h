#ifndef _DL_SQL_STMT_LIST_H_
#define _DL_SQL_STMT_LIST_H_

#include "sql_mgr.h"

enum DL_SQL_STMT_ID
{
	dsqlInsertLogin,			
	//dsqlInsertChat,			
	//dsqlInsertTeam,			
	dsqlInsertItem,			
	dsqlInsertQuest,			
	//dsqlInsertLevelUp,		
	//dsqlInsertScene,			
	//dsqlInsertConslot,		
	dsqlInsertMoney,		
	//dsqlInserRolePosition,	
	//dsqlInsertMaster,
	//dsqlInsertDie,
	dsqlInsertRoleLogoutBasic,
	dsqlInsertGm,
	//dsqlInsertServerMonitorRealMoney,
	//dsqlInsertServerMonitorQuestComplete,
	//dsqlInsertServerMonitorNpcDie,
	//dsqlInsertServerMonitorMoney,
	//dsqlInsertServerMonitorMomentaryKillNpc,
	//dsqlInsertServerMonitorConsecutiveKillNpc,
    //dsqlInsertServerMonitorItem,
	//dsqlInsertFriend,
	//dsqlInsertRoleLogoutItembagDefault,
	//dsqlInsertRoleLogoutItembagEquipped,	

	dsqlTotal
};

extern SQL_STMT_DATA g_DLSqlStmtList[dsqlTotal];

#endif  // _DL_SQL_STMT_LIST_H_