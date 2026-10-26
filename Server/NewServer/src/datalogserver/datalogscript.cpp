#include "stdafx.h"
#include "datalogserver.h"

extern int tolua_enum_str_open(lua_State* tolua_S);

static char    s_szLuaScript[] =
"cache_list = {};\n" \
"for k, v in pairs(_G) do \n" \
"	if type(v) == 'table' and not getmetatable(v) then \n" \
"		cache_list[k] = {}; \n" \
"		for kk,vv in pairs(v) do \n" \
"			if type(vv) == 'number' and not string.find(string.lower(kk), 'begin', 1, true) and not string.find(string.lower(kk), 'end', 1, true) then \n" \
"				cache_list[k][vv] = kk; \n" \
"			end \n" \
"		end \n" \
"	end \n" \
"end\n" \
"function GetEnumStr(tablename, indexkey) \n" \
"	return cache_list[tablename][indexkey]; \n" \
"end \n" \
"function GetEnumValue(tablename, indexname)\n" \
"	return _G[tablename][indexname];\n" \
"end\n";

//for k, v in pairs(_G) do
//  if type(v) == "table" then
//      local tt = v;
//      local key = k;
//      cache_list[key] = {};
//
//      print(k);
//      for k, v in pairs(tt) do
//          print(k);
//          cache_list[key][v] = k;
//      end
//  end
//end


BOOL CDatalogServer::_InitScript(void)
{
    INT32       nRetCode = 0;
    lua_State*  L;

    nRetCode = m_LuaScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    L = m_LuaScript.GetLuaState();
    LOG_PROCESS_ERROR(L);

    nRetCode = tolua_enum_str_open(L);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = m_LuaScript.LoadFromBuffer("", s_szLuaScript, sizeof(s_szLuaScript) - 1);;
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDatalogServer::_UnInitScript(void)
{
    INT32       nRetCode = 0;
    nRetCode = m_LuaScript.UnInit();
    LOG_PROCESS_ERROR(nRetCode);
    return TRUE;
Exit0:
    return FALSE;
}

std::string CDatalogServer::GetEnumString(const char *pcszEnumName, INT32 nEnumKeyValue)
{
    const INT32 NAME_LENGTH = 256;
    static char szName[NAME_LENGTH];

    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(pcszEnumName);
    memset(szName, 0, NAME_LENGTH);
    nRetCode = m_LuaScript.CallFunction("GetEnumStr", "sd:s", pcszEnumName, nEnumKeyValue, szName, NAME_LENGTH);
    LOG_PROCESS_ERROR(nRetCode);

    return szName;
Exit0:
    if (pcszEnumName)
        ERR("GetEnumString failed, enum name[%s]", pcszEnumName);
    return szName;
}

//CLuaScript  g_LuaScript;
//BOOL ParseStr(const char *pcszStr, INT32 nEnumValue)
//{
//    INT32       nRetCode = 0;
//    
//    lua_State*  L;
//    INT32       nRetValue = 0;
//    INT32       nKeyValue = 0;
//    char        szName[256] = { 0 };
//
//    INT32       nStack = 0;
//    INT32       nTemp = 0;
//
//    LOG_PROCESS_ERROR(pcszStr);
//
//    nRetCode = g_LuaScript.Init();
//    LOG_PROCESS_ERROR(nRetCode);
//
//    L = g_LuaScript.GetLuaState();
//    LOG_PROCESS_ERROR(L);
//
//    nRetCode = tolua_enum_str_open(L);
//    LOG_PROCESS_ERROR(nRetCode);
//
//    nRetCode = g_LuaScript.LoadFromBuffer("", s_szLuaScript, sizeof(s_szLuaScript) - 1);;
//    LOG_PROCESS_ERROR(nRetCode);
//
//    //nRetCode = LuaScript.LoadFromFile("../src/datalogserver/script/str.lua");
//    //LOG_PROCESS_ERROR(nRetCode);
//
//    //nRetCode = g_LuaScript.CallFunction("GetEnumValue", "ss:d", "EItemLog", "ITEMLOG_INVALID", &nRetValue);
//    //LOG_PROCESS_ERROR(nRetCode);
//
//    //nKeyValue = -1;
//    //nRetCode = g_LuaScript.CallFunction("GetEnumStr", "sd:s", "EItemLog", nKeyValue, szName, 256);
//    //LOG_PROCESS_ERROR(nRetCode);
//    
//    nRetValue = g_LuaScript.UnInit();
//    LOG_PROCESS_ERROR(nRetCode);
//    
//    return TRUE;
//Exit0:
//    return FALSE;
//}


