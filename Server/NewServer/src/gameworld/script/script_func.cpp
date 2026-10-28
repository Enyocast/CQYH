#include "stdafx.h"
#include "sol_bindings.h"
#include "script_func.h"
#include "script_mgr.h"
#include "math_ex.h"

#include "ai_data.h"
#include "robot_message_handler.h"
#include "message_handler.h"
#include "scene_file_mgr.h"

#include "game_world.h"
#include "bt_manager.h"
#include "sabac_mgr.h"

class CUser;

int lua_getnearpos(lua_State* L)
{
    INT32 nRetCode = 0;
    INT32 nPosList[128][3];
    INT32 nSceneTemplateID = (INT32)lua_tonumber(L, 1);
    INT32 nCenterX = (INT32)lua_tonumber(L, 2);
    INT32 nCenterY = (INT32)lua_tonumber(L, 3);
    INT32 nCenterZ = (INT32)lua_tonumber(L, 4);
    INT32 nMaxRange = (INT32)lua_tonumber(L, 5);
    INT32 nPosCount = (INT32)lua_tonumber(L, 6);
    int nTable = 0;
    CSceneStaticData* pSceneStaticData = NULL;

    LOG_PROCESS_ERROR(nPosCount < 128);

    pSceneStaticData = CSceneFileMgr::GetInstance().GetStaticData(nSceneTemplateID);
    LOG_PROCESS_ERROR(pSceneStaticData);

    lua_newtable(L);
    nTable = lua_gettop(L);

    nRetCode = pSceneStaticData->GetNearestAvailablePos(nCenterX, nCenterY, nCenterZ, nMaxRange, nPosCount, nPosList);
    for (INT32 nIndex = 0; nIndex < nRetCode; nIndex++)
    {
        lua_pushnumber(L, nIndex + 1);
        lua_newtable(L);
        int nPos = lua_gettop(L);

        lua_pushstring(L, "x");
        lua_pushnumber(L, nPosList[nIndex][0]);
        lua_settable(L, nPos);

        lua_pushstring(L, "y");
        lua_pushnumber(L, nPosList[nIndex][1]);
        lua_settable(L, nPos);

        lua_pushstring(L, "z");
        lua_pushnumber(L, nPosList[nIndex][2]);
        lua_settable(L, nPos);

        lua_settable(L, nTable);
    }

//    INF("near pos (%d, %d, %d)", nPosList[0][0] / POINT_PER_CM, nPosList[0][1] / POINT_PER_CM, nPosList[0][2] / POINT_PER_CM);

    return 1;
Exit0:
    return 0;
}

struct NEW_AI_DATA;
extern const NEW_AI_DATA* g_pcLoadingNewAIData;
int lua_load_ai_data(lua_State* L)
{
    if (g_pcLoadingNewAIData)
    {
        cqyh::lua::push_object(L, (void*)g_pcLoadingNewAIData, "NEW_AI_DATA");
        lua_setglobal(L, "d");
        return 1;
    }

    return 0;
}

int lua_find_ai_data(lua_State* L)
{
    INT32 nAIID = (INT32)lua_tonumber(L, 1);
    const NEW_AI_DATA* pData = CDataManager<NEW_AI_DATA>::GetInstance().GetData(nAIID);
    if ( pData )
    {
        cqyh::lua::push_object(L, (void*)pData, "NEW_AI_DATA" );
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

int lua_memory(lua_State* L)
{
	const char* pcszString = lua_tostring(L, 1);

	if (pcszString)
	{
		if (stricmp(pcszString, "world") == 0)
			CGameWorld::GetInstance().PrintMemoryStat();
		else if (stricmp(pcszString, "npc") == 0)
			CGameWorld::GetInstance().PrintNpcPool();
		else if (stricmp(pcszString, "role") == 0)
			CGameWorld::GetInstance().PrintRolePool();
		else if (stricmp(pcszString, "detail") == 0)
			CGameWorld::GetInstance().PrintScenePool(TRUE);
		else if (stricmp(pcszString, "scene") == 0)
			CGameWorld::GetInstance().PrintScenePool(FALSE);
		else if (stricmp(pcszString, "script") == 0)
			CScriptMgr::GetInstance().PrintMemoryStat();
		else if (stricmp(pcszString, "data") == 0)
			CGlobalDataManager::GetInstance().PrintMemoryStat();
	}
	else
	{
		INT64 llTotalSize = 0;
		llTotalSize += CGameWorld::GetInstance().PrintMemoryStat();
		llTotalSize += CScriptMgr::GetInstance().PrintMemoryStat();
		llTotalSize += CGlobalDataManager::GetInstance().PrintMemoryStat();

		INF("total memory allocated %.2fMB", llTotalSize / (1024 * 1024.0f));
	}

    return 0;
}

int lua_msg(lua_State* L)
{
	int nMsgID = (int)lua_tonumber(L, 1);
#ifndef _ROBOT
	if (lua_isnil(L, 2))
	{
		int nState = CCliMessageHandler::GetInstance().GetMsgPrintState(nMsgID);
		lua_pushnumber(L, nState);

		return 1;
	}
	else
	{
		int nState = (int)lua_tonumber(L, 2);
		CCliMessageHandler::GetInstance().SetMsgPrintState(nMsgID, nState);

		return 0;
	}
#endif
	return -1;
}

int lua_sin(lua_State* L)
{
    int nDirection = (int)lua_tonumber(L, 1);

    lua_pushnumber(L, g_Sin(nDirection));

    return 1;
}

int lua_cos(lua_State* L)
{
    int nDirection = (int)lua_tonumber(L, 1);

    lua_pushnumber(L, g_Cos(nDirection));

    return 1;
}

int lua_create_bt_node(lua_State* L)
{
    BTNod* pNode = NULL;
    BTNod* pParent = NULL;

    pParent = (BTNod*)lua_touserdata(L, 1);
    INT32 nType = (INT32)lua_tonumber(L, 2);
    const char* pcszName = lua_tostring(L, 3);
    INT32 nParam0 = (INT32)lua_tonumber(L, 4);
    INT32 nParam1 = (INT32)lua_tonumber(L, 5);
    INT32 nParam2 = (INT32)lua_tonumber(L, 6);
    INT32 nParam3 = (INT32)lua_tonumber(L, 7);
    INT32 nLuaParam = (INT32)lua_tonumber(L, 8);

    pNode = CBTManager::GetInstance().CreateBTNod(pParent, nType, 0, pcszName, nParam0, nParam1, nParam2, nParam3, nLuaParam);
    LOG_PROCESS_ERROR(pNode);

    lua_pushlightuserdata(L, pNode);

    return 1;
Exit0:
    return 0;
}

int lua_destroy_behavior_tree(lua_State* L)
{
    INT32 nRetCode = 0;

    BTNod* pNode = (BTNod*)lua_touserdata(L, 1);
    LOG_PROCESS_ERROR(pNode);

    nRetCode = CBTManager::GetInstance().DestroyBT(pNode);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return 0;
}

int lua_find_bt_action_id(lua_State* L)
{
    const char* pcszName = lua_tostring(L, 1);

    INT32 nActionID = CBTManager::GetInstance().FindBTActionByName(pcszName);
    PROCESS_ERROR(nActionID != btInvalid);

    lua_pushnumber(L, nActionID);

    return 1;
Exit0:
    return 0;
}

int lua_register_bt_action(lua_State* L)
{
    const char* pcszName = lua_tostring(L, 1);

    INT32 nActionID = CBTManager::GetInstance().RegisterBTAction(pcszName);

    lua_pushnumber(L, nActionID);

    return 1;
}

int lua_print_bt(lua_State* L)
{
    BTNod* pNode = (BTNod*)lua_touserdata(L, 1);

    CBTManager::GetInstance().PrintBT(pNode, 0);

    return 0;
}

extern char g_StringTable[STRING_TABLE_STR_COUNT][STRING_TABLE_STR_LEN];

int lua_clear_string_table(lua_State* L)
{
    memset(g_StringTable, 0, sizeof(g_StringTable));
    return 0;
}

int lua_register_string(lua_State* L)
{
    UINT32 dwIndex = (INT32)lua_tonumber(L, 1) - SERVER_STRING_START_ID;
    const char* szStr = lua_tostring(L, 2);
    LOG_CHECK_ERROR(szStr);

    LOG_PROCESS_ERROR( dwIndex < STRING_TABLE_STR_COUNT );
    LOG_PROCESS_ERROR( g_StringTable[dwIndex][0] == '\0' );

    strxcpy( g_StringTable[ dwIndex ], szStr, STRING_TABLE_STR_LEN);

    lua_pushboolean(L, TRUE);

    return 1;
Exit0:
    return 0;
}

int lua_call_ms_func(lua_State* L)
{
#ifndef _ROBOT

    const char* pcszVMName = lua_tostring(L, 1);
    const char* pcszFuncName = lua_tostring(L, 2);
    INT32 nParam1 = lua_tonumber(L, 3);
    INT32 nParam2 = lua_tonumber(L, 4);
    INT32 nParam3 = lua_tonumber(L, 5);


    CCliMessageHandler::GetInstance().DoMSCallLuaFunction(pcszVMName, pcszFuncName, nParam1, nParam2, nParam3);

    lua_pushboolean(L, TRUE);

#endif // _ROBOT
    return 1;
}

int lua_call_bt_action(lua_State* L)
{
    INT32 nResult = brvError;
    INT32 nNodeType;
    INT32 nParam[MAX_BT_PARAM];

    nNodeType = (INT32)lua_tonumber(L, 1);
    nParam[0] = (INT32)lua_tonumber(L, 2);
    nParam[1] = (INT32)lua_tonumber(L, 3);
    nParam[2] = (INT32)lua_tonumber(L, 4);
    nParam[3] = (INT32)lua_tonumber(L, 5);

    nResult = CBTManager::GetInstance().CallBTAction(nNodeType, nParam);

    lua_pushboolean(L, nResult);

    return 1;
}

int lua_test_bt_action(lua_State* L)
{
    INT32 nResult = brvError;
    CRole* poRole = NULL;
    INT32 nNodeType;
    INT32 nParam[MAX_BT_PARAM];

    poRole = sol::stack::get<CRole*>(L, 1);
    nNodeType = (INT32)lua_tonumber(L, 2);
    nParam[0] = (INT32)lua_tonumber(L, 3);
    nParam[1] = (INT32)lua_tonumber(L, 4);
    nParam[2] = (INT32)lua_tonumber(L, 5);
    nParam[3] = (INT32)lua_tonumber(L, 6);

    nResult = CBTManager::GetInstance().TestBTAction(poRole, nNodeType, nParam);

	lua_pushboolean(L, nResult);

    return 1;
}

int lua_get_ctx_role_id(lua_State* L)
{
    UINT32      dwRoleID = 0;

    dwRoleID  = CBTManager::GetInstance().GetCtxRoleID();

    lua_pushnumber(L, dwRoleID);

    return 1;
}

int lua_occupy_sabac(lua_State* L)
{
	INT32 nRetCode = 0;

	CRole* poRole = sol::stack::get<CRole*>(L, 1);
	LOG_PROCESS_ERROR(poRole);

	CSabacMgr::GetInstance().SetOccupyGuildID(poRole->GetServerGroup(), poRole->GetGuildID());
#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoMSOccupySabac(poRole->GetServerGroup(),
		CSabacMgr::GetInstance().GetOccupyGuildID(poRole->GetServerGroup()),
		CSabacMgr::GetInstance().GetOccupyGuildID(poRole->GetServerGroup()));
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CCliMessageHandler::GetInstance().DoSabacStateChange(poRole->GetServerGroup(), FALSE);
	LOG_CHECK_ERROR(nRetCode);
#endif //_ROBOT
Exit0:

	return 0;
}

// Lua函数表 G表
LUA_FUNC g_LuaScriptFuncTable[] =
{
    {"get_near_pos",            lua_getnearpos},
    {"sin",                     lua_sin},
    {"cos",                     lua_cos},
    {"create_bt_node",          lua_create_bt_node},
    {"destroy_behavior_tree",   lua_destroy_behavior_tree},
    {"find_bt_action_id",       lua_find_bt_action_id},
    {"register_bt_action",      lua_register_bt_action},
    {"print_bt",                lua_print_bt},
    {"clear_string_table",		lua_clear_string_table },
    {"register_string",         lua_register_string},
    {"call_ms_func",            lua_call_ms_func},
    {"call_bt_action",          lua_call_bt_action},
    {"test_bt_action",          lua_test_bt_action},
    {"get_ctx_role_id",         lua_get_ctx_role_id},
    {"load_ai_data",            lua_load_ai_data}, 
    {"find_ai_data",            lua_find_ai_data}, 
    {"memory",                  lua_memory},
	{"msg",						lua_msg},				
	{"occupy_sabac",			lua_occupy_sabac },
    {0, 0}
};
