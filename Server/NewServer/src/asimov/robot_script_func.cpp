#include "stdafx.h"
#include "sol_bindings.h"

#include "asimov.h"
#include "lua_script.h"
#include "user.h"
#include "user_mgr.h"
#include "role_db_def.h"
#include "m2c_message.h"
#include "g2c_message.h"
#include "role.h"
#include "region.h"
#include "robot_message_handler.h"
#include "npc_data.h"
#include "scene_file_mgr.h"
#include <time.h>

INT32 lua_input(lua_State* L)
{
    char szResult[256];

    const char* pcszValue = lua_tostring(L, -1);
    LOG_PROCESS_ERROR(pcszValue);

    asimov::GetInstance().requireParam(pcszValue, szResult, 256);

    lua_pushstring(L, szResult);

    return 1;
Exit0:
    return 0;
}

INT32 lua_setstatus(lua_State* L)
{
    const char* pcszCaseName = lua_tostring(L, 1);
    LOG_PROCESS_ERROR(pcszCaseName);

    const char* pcszMessage = lua_tostring(L, 2);
    LOG_PROCESS_ERROR(pcszMessage);

    asimov::GetInstance().setCaseStatus(pcszCaseName, pcszMessage);

Exit0:
    return 0;
}

INT32 lua_setresult(lua_State* L)
{
    const char* pcszCaseName = lua_tostring(L, 1);
    LOG_PROCESS_ERROR(pcszCaseName);

    const char* pcszMessage = lua_tostring(L, 2);
    LOG_PROCESS_ERROR(pcszMessage);

    asimov::GetInstance().setCaseResult(pcszCaseName, pcszMessage);

Exit0:
    return 0;
}

INT32 lua_register_msg(lua_State* L)
{
    CUser* poUser = NULL;
    INT32 nRetCode = 0;
    INT32 nIndex = 1;
    CSessionMsgMap oUserMsgMap;
    CSessionMsgMapItr itr;

    const char* pcszCaseName = lua_tostring(L, 1);
    LOG_PROCESS_ERROR(pcszCaseName);

    nRetCode = lua_istable(L, 2);
    LOG_PROCESS_ERROR(nRetCode);

    lua_pushnil(L);
    while (lua_next(L, 2) != 0) 
    {        
        if(nIndex % 2 == 1)
        {
            INT32 nID = lua_tonumber(L, -1);
            itr = oUserMsgMap.find(nID);
            if(itr == oUserMsgMap.end())
            {
                CMsgSet oSetMsg;
                oUserMsgMap.insert(make_pair(nID, oSetMsg));
                itr = oUserMsgMap.find(nID);
            }
        }
        else
        {
            LOG_PROCESS_ERROR(itr != oUserMsgMap.end());
            INT32 wMsgID = lua_tonumber(L, -1);
            itr->second.insert(wMsgID);
        }
        nIndex++;
        lua_pop(L, 1);
    }

    for(itr = oUserMsgMap.begin(); itr != oUserMsgMap.end(); ++itr)
    {
        poUser = CUserMgr::GetInstance().FindUser(itr->first);
        LOG_PROCESS_ERROR(poUser);

        poUser->RegisterMsg(pcszCaseName, itr->second);
    }

Exit0:
    return 0;
}

INT32 lua_un_register_msg(lua_State* L)
{
    CUser* poUser = NULL;
    INT32 nRetCode = 0;
    UINT32 dwSessionID = 0;

    dwSessionID = lua_tonumber(L, 1);
    LOG_PROCESS_ERROR(dwSessionID > 0);

    poUser = CUserMgr::GetInstance().FindUser(dwSessionID);
    LOG_PROCESS_ERROR(poUser);

    poUser->UnRegisterMsg();
    
Exit0:
    return 0;
}

INT32 lua_get_base_data(lua_State* L)
{
    ROLE_DB_BASE_DATA* pBaseData = (ROLE_DB_BASE_DATA*)lua_touserdata(L, 1);
    LOG_PROCESS_ERROR(pBaseData);

    INT32 nIndex = (INT32)lua_tonumber(L, 2);

    cqyh::lua::push_object(L, pBaseData + nIndex, "ROLE_DB_BASE_DATA");

    return 1;
Exit0:
    return 0;
}

INT32 lua_get_role_name_from_mschat_message(lua_State* L)
{
    INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	ExternalMessage::M2C_CHAT_MESSAGE* pMsg = *(ExternalMessage::M2C_CHAT_MESSAGE**)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(pMsg);

	nMessageSize = strnlen(pMsg->szMessage, MAX_CHAT_MESSAGE_LEN) + 1;
	LOG_PROCESS_ERROR(pMsg->szMessage[nMessageSize - 1] == '\0');

	lua_pushstring(L, pMsg->szMessage + nMessageSize);
	return 1;

Exit0:
	return 0;	
}

INT32 lua_get_drop_list_item_count_from_gsmessage(lua_State* L)
{
	INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	INT32 nCount = 0;
	ExternalMessage::G2C_SYNC_DROP_LIST* pMsg = *(ExternalMessage::G2C_SYNC_DROP_LIST**)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(pMsg);

	nMessageSize = pMsg->wSize - sizeof(ExternalMessage::G2C_SYNC_DROP_LIST);
	nCount = nMessageSize / sizeof(ExternalMessage::DROP_INFO);

	lua_pushnumber(L, nCount);
	return 1;

Exit0:
	return 0;	
}

INT32 lua_get_drop_list_item_from_gsmessage(lua_State* L)
{
	INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	INT32 nCount = 0;
	INT32 nIndex = 0;
	INT32 nSize = 0;
	ExternalMessage::DROP_INFO* pDrop = NULL;

	ExternalMessage::G2C_SYNC_DROP_LIST* pMsg = *(ExternalMessage::G2C_SYNC_DROP_LIST**)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(pMsg);

	nMessageSize = pMsg->wSize - sizeof(ExternalMessage::G2C_SYNC_DROP_LIST);
	nCount = nMessageSize / sizeof(ExternalMessage::DROP_INFO);

	nIndex = lua_tointeger(L, 1);
	LOG_PROCESS_ERROR(nIndex < nCount && nIndex >= 0);

	pDrop = &(pMsg->astDrops[0]) + sizeof(ExternalMessage::DROP_INFO) * nCount;

	cqyh::lua::push_object(L, pDrop, "ExternalMessage::DROP_INFO");
	return 1;

Exit0:
	return 0;	
}


INT32 lua_get_role_name_from_gschat_message(lua_State* L)
{
	INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	ExternalMessage::G2C_CHAT_MESSAGE* pMsg = *(ExternalMessage::G2C_CHAT_MESSAGE**)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(pMsg);

	nMessageSize = strnlen(pMsg->szMessage, MAX_CHAT_MESSAGE_LEN) + 1;
	LOG_PROCESS_ERROR(pMsg->szMessage[nMessageSize - 1] == '\0');

	lua_pushstring(L, pMsg->szMessage + nMessageSize);
	return 1;

Exit0:
	return 0;	
}

INT32 lua_get_chat_content_from_msmessage(lua_State* L)
{
	INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	ExternalMessage::M2C_CHAT_MESSAGE* pMsg = *(ExternalMessage::M2C_CHAT_MESSAGE**)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(pMsg);

	nMessageSize = strnlen(pMsg->szMessage, MAX_CHAT_MESSAGE_LEN) + 1;
	LOG_PROCESS_ERROR(pMsg->szMessage[nMessageSize - 1] == '\0');

	lua_pushstring(L, pMsg->szMessage);
	return 1;

Exit0:
	return 0;	
}

INT32 lua_get_variable_type(lua_State* L)
{
	INT32 nType = (INT32)lua_tonumber(L, 1);
	lua_pushnumber(L, (nType & 0x000F));
	return 1;
}

INT32 lua_get_variable_index(lua_State* L)
{
	INT32 nIndex = (INT32)lua_tonumber(L, 1);
	lua_pushnumber(L, (nIndex & 0xFFF0) >> 4);
	return 1;
}

INT32 lua_get_localtime_ex(lua_State* L)
{
	INT64 llTime = (INT64)lua_tonumber(L, 1);
	tm* tm1 = localtime(&llTime);
	
	lua_newtable(L);
	INT32 nTable = lua_gettop(L);

	lua_pushstring(L, "tm_year");
	lua_pushnumber(L, tm1->tm_year);
	lua_settable(L, nTable);

	lua_pushstring(L, "tm_mon");
	lua_pushnumber(L, tm1->tm_mon);
	lua_settable(L, nTable);

	lua_pushstring(L, "tm_mday");
	lua_pushnumber(L, tm1->tm_mday);
	lua_settable(L, nTable);

	lua_pushstring(L, "tm_wday");
	lua_pushnumber(L, tm1->tm_wday);
	lua_settable(L, nTable);

	lua_pushstring(L, "tm_hour");
	lua_pushnumber(L, tm1->tm_hour);
	lua_settable(L, nTable);

	return 1;
}

INT32 lua_create_user(lua_State* L)
{
    INT32 nRetCode = 0;
    CUser* poUser = NULL;

    const char* pcszUserName = lua_tostring(L, 1);
    const char* pcszUserType = lua_tostring(L, 2);
    const char* pcszPassword = lua_tostring(L, 3);
    UINT8 byServerGroupID = lua_tonumber(L, 4);
    const char* pcszCoroutineName = lua_tostring(L, 5);

    poUser = CUserMgr::GetInstance().NewUser(pcszUserName, pcszUserType, pcszPassword, byServerGroupID);
    LOG_PROCESS_ERROR(poUser);

    nRetCode = CUserMgr::GetInstance().AttachUserToCoroutine(poUser, pcszCoroutineName);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poUser->AttachToCoroutine(pcszCoroutineName);
    LOG_PROCESS_ERROR(nRetCode);

    cqyh::lua::push_object(L, poUser, "CUser");

    return 1;
Exit0:
    if (poUser)
    {
        poUser->DetachFromCorouine();
        CUserMgr::GetInstance().DetachUserFromCoroutine(pcszCoroutineName);
        CUserMgr::GetInstance().DelUser(poUser);
    }

    return 0;
}

INT32 lua_rand_another_user(lua_State* L)
{
	INT32 nRetCode = 0;
	CUser* poUser = NULL;

	CUser* poSelfUser = sol::stack::get<CUser*>(L, 1);
	LOG_PROCESS_ERROR(poSelfUser);

	poUser = CUserMgr::GetInstance().RandAnotherUser(poSelfUser);
	LOG_PROCESS_ERROR(poUser);

	cqyh::lua::push_object(L, poUser, "CUser");

	return 1;
Exit0:

	//lua_pushnil(L);
	return 0;
}

INT32 lua_destory_user(lua_State* L)
{
    INT32 nRetCode = 0;

    CUser* poUser = sol::stack::get<CUser*>(L, 1);
    LOG_PROCESS_ERROR(poUser);

    const char* pcszCoroutineName = lua_tostring(L, 2);
    LOG_CHECK_ERROR(strcmp(pcszCoroutineName, poUser->GetCoroutineName()) == 0);

    poUser->DetachFromCorouine();

    CUserMgr::GetInstance().DetachUserFromCoroutine(pcszCoroutineName);

    nRetCode = CUserMgr::GetInstance().DelUser(poUser);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return 0;
}

INT32 lua_detach_coroutine(lua_State* L)
{
    CUser* poUser = NULL;

    const char* pcszCoroutineName = lua_tostring(L, 1);

    poUser = CUserMgr::GetInstance().FindUserByCoroutineName(pcszCoroutineName);
    LOG_PROCESS_ERROR(poUser);

    CUserMgr::GetInstance().DetachUserFromCoroutine(pcszCoroutineName);
    poUser->DetachFromCorouine();

    INF("user %s detach_coroutine %s", poUser->GetUserName(), pcszCoroutineName);

Exit0:
    return 0;
}

INT32 lua_get_npc(lua_State* L)
{
	CSceneStaticData* poStaticData = NULL;
	INT32 nSingleNpcID = 0;
	CNpc* poNpc = NULL;

	poStaticData = *(CSceneStaticData**)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(poStaticData != NULL);

	nSingleNpcID = lua_tonumber(L, 2);
	PROCESS_ERROR(nSingleNpcID < poStaticData->GetSingleNpcCount());

	{
		INT32 nTemplateID = 0;
		NPC_DATA* poNpcData = NULL;

		const NPC_SPAWN_POINT* pt = poStaticData->GetSingleNpc(nSingleNpcID);
		LOG_PROCESS_ERROR(pt);

		nTemplateID = pt->RandNpc.Rand();

		poNpcData = (NPC_DATA*)CDataManager<NPC_DATA>::GetInstance().GetData(nTemplateID);
		LOG_PROCESS_ERROR(poNpcData);

		cqyh::lua::push_object(L, (void*)pt, "NPC_SPAWN_POINT");
		cqyh::lua::push_object(L, poNpcData, "NPC_DATA");
	}

	return 2;

Exit0:
	return 0;
}

INT32 lua_goto_npc(lua_State* L)
{
    CUser* user = NULL;
    CRole* role = NULL;
    INT32 npcid = 0;
    const char* func_name = NULL;
    const NPC_POSITION* npc_pos = NULL;
    char gmcommand[256];
    BOOL bRet = FALSE;

    user = sol::stack::get<CUser*>(L, 1);
    LOG_PROCESS_ERROR(user);

    role = user->GetPlayingRole();
    LOG_PROCESS_ERROR(role);

    npcid = lua_tonumber(L, 2);
    LOG_PROCESS_ERROR(npcid);

    func_name = lua_tostring(L, 3);
    LOG_PROCESS_ERROR(func_name);

    npc_pos = CSceneFileMgr::GetInstance().GetNpcPosition(npcid);
    LOG_PROCESS_ERROR(npc_pos);

    memset(gmcommand, 0, sizeof(gmcommand));
    snprintf(gmcommand, 256, "g_oGameWorld:JumpTo(TargetRole, %d, 0, %d, %d, %d, TargetRole:GetFaceDirection());",
        npc_pos->nSceneTemplateID, npc_pos->nX, npc_pos->nY, npc_pos->nZ);

    bRet = user->GMCommand(gmcommand);
    LOG_PROCESS_ERROR(bRet);

    role->SetCBFuncName(func_name);
    role->SetWaitNpcTemplateID(npcid);

Exit0:
    return 0;
}

INT32 lua_select_focus(lua_State* L)
{
	CRegion* poRegion = NULL;

	struct Traverse9Region
	{
		UINT32 dwFocusID;

		BOOL operator()(CRegion* poRegion)
		{
			INT32 nRetCode = 0;

			nRetCode = poRegion->TraverseCharacter(*this);
			LOG_PROCESS_ERROR(nRetCode);
			return TRUE;
Exit0:
			return FALSE;
		}

		BOOL operator()(CCharacter* poChar)
		{
			dwFocusID = poChar->GetObjID(); 
			return FALSE;
		}
	};

	Traverse9Region trav;
	trav.dwFocusID = 0;

    CRole* poRole = sol::stack::get<CRole*>(L, 1);
    LOG_PROCESS_ERROR(poRole);

	poRegion = poRole->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	poRegion->Traverse9Region(trav);

	lua_pushnumber(L, trav.dwFocusID);

Exit0:
	return 0;
}



LUA_FUNC g_RobotLuaScriptFuncTable[] =
{
    {"input", lua_input},
    {"setstatus", lua_setstatus},
    {"setresult", lua_setresult},
    {"register_msg", lua_register_msg},
    {"un_register_msg", lua_un_register_msg},
    {"get_base_data", lua_get_base_data},
	{"get_role_name_from_msmessage", lua_get_role_name_from_mschat_message},
	{"get_role_name_from_gsmsmessage", lua_get_role_name_from_gschat_message},
	{"get_chat_content_from_msmessage", lua_get_chat_content_from_msmessage},
	{"get_variable_type", lua_get_variable_type},
	{"get_variable_index", lua_get_variable_index},
	{"get_localtime_ex", lua_get_localtime_ex},
    {"_create_user", lua_create_user},
	{"_destory_user", lua_destory_user },
	{"rand_another_user", lua_rand_another_user },
    {"detach_coroutine", lua_detach_coroutine},
    {"get_drop_list_item_from_gsmessage", lua_get_drop_list_item_from_gsmessage},
    {"get_drop_list_item_count_from_gsmessage", lua_get_drop_list_item_count_from_gsmessage},
    {"get_npc", lua_get_npc},
    {"goto_npc", lua_goto_npc},
    {"select_focus", lua_select_focus},

    {0, 0}
};
