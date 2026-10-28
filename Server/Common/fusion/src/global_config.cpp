#include "stdafx.h"
#include "sol_bindings.h"
#include "global_config.h"

#include "ifile.h"
#include "script_mgr.h"
#include "string_ex.h"
#include "script/sol_global_config.h"

#include "asimov_config.h"
#include "game_world_config.h"
#include "guild_config.h"
#include "mt_config.h"
#include "new_role_config.h"
#include "obj_pool_config.h"
#include "server_config.h"
#include "guard_config.h"

#if defined(__linux__)
#include <fpu_control.h>
#endif  // __linux__

 int sol_data_manager_open(lua_State* L);

ASIMOV_CONFIG       g_AsimovConfig;
GAME_WORLD_CONFIG   g_GWConfig;
GUILD_CONFIG        g_GuildConfig;
NEW_ROLE_CONFIG     g_NewRoleConfig;
OBJ_POOL_CONFIG     g_ObjPoolConfig;
SERVER_CONFIG       g_ServerConfig;
MAINTAIN_CONFIG     g_MTConfig;
GUARD_CONFIG		g_GuardConfig;

char g_GmRoleName[10][ROLE_NAME_LEN] = {};

char g_szGlobalConfigFileName[MAX_PATH] = "global_config.lua";

BOOL LoadGlobalConfig(const char* pcszFileName)
{
    INT32 nRetCode = 0;
    CLuaScript oScript;
    INT32 nStackTop = 0;
	char szRootPath[256] = { 0 };

#if defined(__linux__)
    fpu_control_t cw; 
    _FPU_GETCW(cw); 
    cw &= ~_FPU_EXTENDED; 
    cw |= _FPU_DOUBLE; 
    _FPU_SETCW(cw); 
#endif  // __linux__

	strxcpy(szRootPath, CScriptMgr::GetInstance().GetRootPath(), 256);
	CScriptMgr::GetInstance().SetRootPath(NULL);
	
    nRetCode = oScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    sol_global_config_open(oScript.GetLuaState());

    nRetCode = oScript.LoadFromFile(pcszFileName);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "os", &g_AsimovConfig, "ASIMOV_CONFIG", "AsimovConfig");
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "os", &g_GWConfig, "GAME_WORLD_CONFIG", "GameWorldConfig");
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "os", &g_GuildConfig, "GUILD_CONFIG", "GuildConfig");
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "os", &g_NewRoleConfig, "NEW_ROLE_CONFIG", "NewRoleConfig");
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "os", &g_ObjPoolConfig, "OBJ_POOL_CONFIG", "ObjPoolConfig");
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "os", &g_ServerConfig, "SERVER_CONFIG", "ServerConfig");
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.UnInit();
    LOG_CHECK_ERROR(nRetCode);

	CScriptMgr::GetInstance().SetRootPath(szRootPath);

	for (INT32 nServerGroup = 0; nServerGroup < MAX_SERVER_GROUP_COUNT; nServerGroup++)
	{
        if (IsValidGroup(nServerGroup) && g_ServerConfig.GroupConfig[nServerGroup].dwStartDate == 0)
		{
			g_ServerConfig.GroupConfig[nServerGroup].dwStartDate = 0xFFFFFFFF;
			LOG_PROCESS_ERROR(g_ServerConfig.GroupConfig[nServerGroup].dwStartDate);
		}
	}

    // 初始化Gm角色名字
    strxcpy(g_GmRoleName[0], g_ServerConfig.CC.GmRoleName.szRoleName0, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[1], g_ServerConfig.CC.GmRoleName.szRoleName1, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[2], g_ServerConfig.CC.GmRoleName.szRoleName2, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[3], g_ServerConfig.CC.GmRoleName.szRoleName3, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[4], g_ServerConfig.CC.GmRoleName.szRoleName4, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[5], g_ServerConfig.CC.GmRoleName.szRoleName5, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[6], g_ServerConfig.CC.GmRoleName.szRoleName6, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[7], g_ServerConfig.CC.GmRoleName.szRoleName7, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[8], g_ServerConfig.CC.GmRoleName.szRoleName8, ROLE_NAME_LEN);
    strxcpy(g_GmRoleName[9], g_ServerConfig.CC.GmRoleName.szRoleName9, ROLE_NAME_LEN);

    return TRUE;
Exit0:

    oScript.UnInit();

	CScriptMgr::GetInstance().SetRootPath(szRootPath);

    return FALSE;
}

BOOL SaveGlobalConfig(const char* pcszFilePath)
{
    INT32 nRetCode = 0;
    CLuaScript oScript;
    INT32 nStackTop = 0;

    //LOG_PROCESS_ERROR(pcszFilePath);

    //nRetCode = oScript.Init();
    //LOG_PROCESS_ERROR(nRetCode);
    //
    //sol_global_config_open(oScript.GetLuaState());

    //nRetCode = oScript.LoadFromFile(szLoadFileName);
    //LOG_PROCESS_ERROR(nRetCode);

    //strxcpy(szSaveFilePath, pcszFilePath, 256);

    //nRetCode = oScript.CallFunction("SaveFile", "");
    //LOG_PROCESS_ERROR(nRetCode);

    //oScript.UnInit();
    return TRUE;
Exit0:

    oScript.UnInit();

    return FALSE;
}


BOOL LoadMTConfig(const char* pcszFileName)
{
    INT32 nRetCode = 0;
    CLuaScript oScript;
    INT32 nStackTop = 0;

#if defined(__linux__)
    fpu_control_t cw; 
    _FPU_GETCW(cw); 
    cw &= ~_FPU_EXTENDED; 
    cw |= _FPU_DOUBLE; 
    _FPU_SETCW(cw); 
#endif  // __linux__

    nRetCode = oScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    sol_global_config_open(oScript.GetLuaState());

    nRetCode = oScript.LoadFromFile(pcszFileName);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "os", &g_MTConfig, "MAINTAIN_CONFIG", "MaintainConfig");
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
Exit0:

    oScript.UnInit();

    return FALSE;
}

BOOL LoadGuardConfig(const char* pcszFileName)
{
	INT32 nRetCode = 0;
	CLuaScript oScript;
	INT32 nStackTop = 0;

	nRetCode = oScript.Init();
	LOG_PROCESS_ERROR(nRetCode);

	sol_global_config_open(oScript.GetLuaState());

	nRetCode = oScript.LoadFromFile(pcszFileName);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = oScript.CallFunction("LoadFile", "os", &g_GuardConfig, "GUARD_CONFIG", "GuardConfig");
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = oScript.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;
Exit0:

	oScript.UnInit();

	return FALSE;
}

BOOL LoadAreaGroupData(const char* pcszFileName)
{
	INT32 nRetCode = 0;
	CLuaScript oScript;
	INT32 nStackTop = 0;
	char szRootPath[256] = { 0 };

	strxcpy(szRootPath, CScriptMgr::GetInstance().GetRootPath(), 256);
	CScriptMgr::GetInstance().SetRootPath(NULL);

	nRetCode = oScript.Init();
	LOG_PROCESS_ERROR(nRetCode);

	sol_global_config_open(oScript.GetLuaState());
	sol_data_manager_open(oScript.GetLuaState());

	nRetCode = oScript.LoadFromFile(pcszFileName);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = oScript.CallFunction("SetAreaGroupData", "");
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = oScript.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	CScriptMgr::GetInstance().SetRootPath(szRootPath);

	return TRUE;
Exit0:

	oScript.UnInit();

	CScriptMgr::GetInstance().SetRootPath(szRootPath);

	return FALSE;
}
