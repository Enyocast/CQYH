#include "stdafx.h"
#include "enum_string.h"

extern int tolua_enumstr_open(lua_State* tolua_S);

static char    s_szLuaScript[] =
"cache_list = {};\n" \
"for k, v in pairs(_G) do \n" \
"	if type(v) == 'table' and not getmetatable(v) then \n" \
"		cache_list[k] = {}; \n" \
"		for kk,vv in pairs(v) do \n" \
"			local bf_bp, bf_ep = string.find(string.lower(kk), 'begin', 1, true);" \
"			local ef_bp, ef_ep = string.find(string.lower(kk), 'end', 1, true);" \
"			if type(vv) == 'number' and string.len(kk) ~= bf_ep and string.len(kk) ~= ef_ep  then \n" \
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



CEnumString CEnumString::ms_Instance;

CEnumString::CEnumString()
{

}

CEnumString::~CEnumString()
{
	UnInit();
}

BOOL CEnumString::Init(void)
{
	INT32       nRetCode = 0;
	lua_State*  L;

	nRetCode = m_LuaScript.Init();
	LOG_PROCESS_ERROR(nRetCode);

	L = m_LuaScript.GetLuaState();
	LOG_PROCESS_ERROR(L);

	nRetCode = tolua_enumstr_open(L);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = m_LuaScript.LoadFromBuffer("", s_szLuaScript, sizeof(s_szLuaScript) - 1);;
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CEnumString::UnInit(void)
{
	INT32       nRetCode = 0;

	nRetCode = m_LuaScript.UnInit();
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

CEnumString& CEnumString::GetInstance(void)
{
	return ms_Instance;
}

std::string CEnumString::GetEnumString(const char *pcszEnumName, INT32 nEnumKeyValue)
{
	const INT32 NAME_LENGTH = 256;
	char szName[NAME_LENGTH] = { 0 };

	INT32       nRetCode = 0;

	LOG_PROCESS_ERROR(pcszEnumName);
	memset(szName, 0, NAME_LENGTH);
	nRetCode = m_LuaScript.CallFunction("GetEnumStr", "sd:s", pcszEnumName, nEnumKeyValue, szName, NAME_LENGTH);
	LOG_PROCESS_ERROR(nRetCode);

	return szName;
Exit0:
	return szName;
}
