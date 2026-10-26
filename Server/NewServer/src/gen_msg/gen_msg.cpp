#include "stdafx.h"
#include "external_message_header.h"
#include "internal_message_header.h"

#if defined(WIN32) | defined(WIN64)
    #include <malloc.h>
#endif  // WIN32 | WIN64

#include "zlib.h"

#include "lua_script.h"

#include "gameworld/bt_action.h"
#include "bt_event.h"

extern int tolua_external_message_open (lua_State* tolua_S);
extern int tolua_enum_module_open (lua_State* tolua_S);

static UINT32 s_dwMsgCRC = 0;

static char s_szMsgScript[] = 
"MAX_MESSAGE_ID = 1023;\n"\
"print('#include \"stdafx.h\"\\n\\n')\n"\
"print('//**** gen result begin ****//\\n')\n"\
"s2c = {};c2s = {};\n"\
"for k,v in pairs(ExternalMessage) do\n"\
"   if string.sub(k,2,2) == '2' then\n"\
"       if type(v) == 'number' then\n"\
"           if string.sub(k,5,17) == 'message_begin' or string.sub(k,5,15) == 'message_end' then\n"\
"               \n"\
"           elseif ExternalMessage[string.upper(k)] == nil then\n"\
"               print('// unmatched message id : '..k..'('..v..')\\n')\n"\
"           else\n"\
"--               print('//matched message id : '..k..'('..v..')\\n');\n"\
"           end\n"\
"       elseif type(v) == 'table' then\n"\
"           local msg_id = ExternalMessage[string.lower(k)];\n"\
"           if msg_id == nil then\n"\
"               print('//unmatched message struct : '..k..'\\n')\n"\
"           else\n"\
"               local msg_prefix = string.sub(k,1,3);\n"\
"               if msg_prefix == 'C2G' or msg_prefix == 'C2M' or msg_prefix == 'C2T' or msg_prefix == 'C2B' then\n"\
"                   local msg = v:new_local();\n"\
"                   if msg.wSize ~= nil then\n"\
"                       msg = nil\n"\
"                   end\n"\
"                   local size = get_c2s_size(msg_id, msg)\n"\
"                   if not size then\n"\
"                       print('//cannot get message size : '..k..'\\n')\n"\
"                   else\n"\
"                       c2s[msg_id] = {};\n"\
"                       c2s[msg_id].size = size;\n"\
"                       c2s[msg_id].name = k;\n"\
"--                     print('//message '..k..' size is '..size..'\\n')\n"\
"                   end\n"\
"               elseif msg_prefix == 'G2C' or msg_prefix == 'M2C' or msg_prefix == 'T2C' or msg_prefix == 'B2C' then\n"\
"                   local msg = v:new_local();\n"\
"                   if msg.wSize ~= nil then\n"\
"                       msg = nil\n"\
"                   end\n"\
"                   local size = get_s2c_size(msg_id, msg)\n"\
"                   if not size then\n"\
"                       print('//cannot get message size : '..k..'\\n')\n"\
"                   else\n"\
"                       s2c[msg_id] = {};\n"\
"                       s2c[msg_id].size = size;\n"\
"                       s2c[msg_id].name = k;\n"\
"--                     print('//message '..k..' size is '..size..'\\n')\n"\
"                   end\n"\
"               else\n"\
"                   print('//error message struct : '..k..'\\n')\n"\
"               end\n"\
"           end\n"\
"       end\n"\
"   end\n"\
"end\n"\
"print('//**** gen result end ****//\\n\\n')\n"\
"print('INT32 g_nS2CMessageSize[] = {\\n')\n"\
"for i=0, MAX_MESSAGE_ID do\n"\
"   if s2c[i] then\n"\
"       local s = string.format('    %5d,    // %3d %s\\n', s2c[i].size, i, s2c[i].name);\n"\
"       print(s);\n"\
"   else\n"\
"       print('        0,\\n');\n"\
"   end\n"\
"end\n"\
"print('};\\n\\n')\n"\
"print('INT32 g_nC2SMessageSize[] = {\\n')\n"\
"for i=0, MAX_MESSAGE_ID do\n"\
"   if c2s[i] then\n"\
"       local s = string.format('    %5d,    // %3d %s\\n', c2s[i].size, i, c2s[i].name);\n"\
"       print(s);\n"\
"   else\n"\
"       print('        0,\\n');\n"\
"   end\n"\
"end\n"\
"print('};\\n\\n')\n"\
"print('#if !SHIPPING_PC_GAME\\n')\n"\
"print('char* g_szS2CMessageName[] = {\\n')\n"\
"for i=0, MAX_MESSAGE_ID do\n"\
"   if s2c[i] then\n"\
"       local s = string.format('    \"%s\",\\n', string.lower(s2c[i].name));\n"\
"       print(s);\n"\
"   else\n"\
"       print('    \"undefined s2c message\",\\n');\n"\
"   end\n"\
"end\n"\
"print('};\\n\\n')\n"\
"print('char* g_szC2SMessageName[] = {\\n')\n"\
"for i=0, MAX_MESSAGE_ID do\n"\
"   if c2s[i] then\n"\
"       local s = string.format('    \"%s\",\\n', string.lower(c2s[i].name));\n"\
"       print(s);\n"\
"   else\n"\
"       print('    \"undefined c2s message\",\\n');\n"\
"   end\n"\
"end\n"\
"print('};\\n\\n')\n"\
"print('#endif // !SHIPPING_PC_GAME\\n\\n')\n"\
"print('INT32 g_nMessageVersion = ('..crc()..');\\n\\n')\n";

#define FLEX_MESSAGE_SIZE   (-1)

static char s_szEnumScript[] = ""\
"print('class ServerEnum extends Object native;\\n\\n')\n"\
"for k,v in pairs(_G) do\n"\
"   if type(v) == 'table' and k ~= 'os' and k ~= 'table' and k ~= 'string' and k ~= 'math' and k ~= 'coroutine' and k ~= '_G' and k ~= 'debug' and k ~= 'package' and k ~= 'tolua' and k ~= 'io'and k ~= 'ERROR_CODE_DEF' and not getmetatable(v) then\n"\
"       print('enum E'..k..'\\n{\\n')\n"\
"       local t = {};\n"\
"       local max = -1;\n"\
"       local prefix;\n"\
"       for kk, vv in pairs(v) do\n"\
"           if t[vv] then\n"\
"               if (not string.find(string.lower(kk), 'begin', 1, true)) and (not string.find(string.lower(kk), 'end', 1, true)) then\n"\
"                   t[vv] = kk\n"\
"                   if vv > max then\n"\
"                       max = vv;\n"\
"                   end\n"\
"               else\n"\
"                   print('// conflicted enum definition '..kk..'('..vv..')\\n');\n"\
"               end\n"\
"           else\n"\
"               t[vv] = kk\n"\
"               if vv > max then\n"\
"                   max = vv;\n"\
"               end\n"\
"           end\n"\
"           if prefix == nil then\n"\
"               prefix = kk;\n"\
"           else\n"\
"               while string.sub(kk, 1, #prefix) ~= prefix and #prefix > 0 do\n"\
"                   prefix = string.sub(prefix, 1, #prefix - 1);\n"\
"               end\n"\
"           end\n"\
"       end\n"\
"       \n"\
"       if prefix == nil then\n"\
"           print('// failed to found enum prefix\\n');\n"\
"       elseif #prefix == 0 then\n"\
"           print('// failed to found enum prefix\\n');\n"\
"       elseif string.sub(prefix, -1) == '_' then\n"\
"           prefix = string.sub(prefix, 1, #prefix - 1);\n"\
"       end\n"\
"       if max > 254 then\n"\
"           max = 254;\n"\
"           print('// max enum definition is over 254\\n');\n"\
"       end\n"\
"       for i=0, max do\n"\
"           local name = t[i];\n"\
"           if name == nil then\n"\
"               name = 'Reserved_'..i\n"\
"           else\n"\
"               name = string.sub(t[i], #prefix + 1, 1000);\n"\
"               if string.sub(name, 1, 1) == '_' then\n"\
"                   name = string.sub(name, 2, 1000);\n"\
"               end\n"\
"           end\n"\
"           name = 'E_'..prefix..'_'..name;\n"\
"           print('\t'..name)\n"\
"           for i=#name,32 do\n"\
"               print(' ')\n"\
"           end\n"\
"           print(' <DisplayName=\"'..name..'\">,\\n')\n"\
"       end\n"\
"       print('\tE_'..prefix..'_MAX\\n')\n"\
"       print('};\\n\\n')\n"\
"   end\n"\
"end\n"\
"\n"\
"";

static char s_szErrcodeScript[] = ""\
"print('#include \"stdafx.h\"\\n\\n')\n"\
"print('//**** gen error code name list begin ****//\\n')\n"\
"print('const char* g_szErrorCodeNameList[] = {\\n')\n"\
"local t = {};\n"\
"local max = -1;\n"\
"for k,v in pairs(ERROR_CODE_DEF) do\n"\
"    if t[v] then\n"\
"        if (not string.find(string.lower(kk), 'begin', 1, true)) and (not string.find(string.lower(kk), 'end', 1, true)) then\n"\
"            t[v] = k\n"\
"            if v > max then\n"\
"                max = v;\n"\
"            end\n"\
"        else\n"\
"            print('// conflicted enum definition '..k..'('..v..')\\n');\n"\
"        end\n"\
"    else\n"\
"        t[v] = k\n"\
"        if v > max then\n"\
"            max = v;\n"\
"        end\n"\
"    end\n"\
"end\n"\
"\n"\
"for i=0, max do\n"\
"    local name = t[i];\n"\
"    if name == nil then\n"\
"        name = 'Reserved_'..i\n"\
"    end\n"\
"    print('\t\"'..name..'\",')\n"\
"    for i=#name,64 do\n"\
"        print(' ')\n"\
"    end\n"\
"    print('// '..i..'\\n')\n"\
"end\n"\
"print('};\\n\\n')\n"\
"print('//**** gen error code name list end ****//\\n\\n')\n"\
"\n"\
"";

static char s_szBTNode[] = ""\
"f = io.open('../../inc/gameworld/bt_action.h');\n"\
"bInBTNode = false;\n"\
"BTEdit = 'BET_Common';\n"\
"BTNodeList = {};\n"\
"BTNode = nil;\n"\
"for line in f:lines() do\n"\
"   if bInBTNode and not string.find(line, '///< %@see') then\n"\
"       if string.find(line, '/%* Common') then \n"\
"           BTEdit = 'BET_Common' \n"\
"       end\n"\
"       if string.find(line, '/%* Role') then \n"\
"           BTEdit = 'BET_Common' \n"\
"       end\n"\
"       if string.find(line, '/%* AI') then \n"\
"           BTEdit = 'BET_AI' \n"\
"       end\n"\
"       if string.find(line, '/%* Char') then \n"\
"           BTEdit = 'BET_Common' \n"\
"       end\n"\
"       if string.find(line, '/%* Scene') then \n"\
"           BTEdit = 'BET_Scene' \n"\
"       end\n"\
"\n"\
"       local _, _, node_name = string.find(line, '%s*(bat%w*)%s*[=,].-///<.-');\n"\
"       if node_name then\n"\
"           BTNode = { name = node_name, type = BTEdit};\n"\
"           table.insert(BTNodeList, BTNode);\n"\
"       end\n"\
"\n"\
"       local _, _, param_name, param_desc = string.find(line, '.-@param%s*(%w+)%s*(.+)%s*[%(%[%c]');\n"\
"       if not param_desc then\n"\
"           _, _, param_name, param_desc = string.find(line, '.-@param%s*(%w+)%s*(.+)');\n"\
"       end\n"\
"\n"\
"       if param_name then\n"\
"           if not BTNode.param then BTNode.param = {}; end\n"\
"           local p = {name = param_name, desc = param_desc};\n"\
"           table.insert(BTNode.param, p);\n"\
"       end\n"\
"   elseif string.find(line, 'enum BT_ACTION_TYPE') then\n"\
"       bInBTNode = true;\n"\
"   end\n"\
"\n"\
"\n"\
"end\n"\
"f:close()\n"\
"\n"\
"print('[BTNodeTypeList]\\n')\n"\
"for k,v in ipairs(BTNodeList) do\n"\
"   print('BTNodeTypeList='..v.name..'\\n')\n"\
"end\n"\
"\n"\
"print('\\n')\n"\
"for k,v in ipairs(BTNodeList) do\n"\
"   print('\\n['..v.name..']\\n')\n"\
"   print('BTEdit='..v.type..'\\n')\n"\
"   if v.param then \n"\
"       for kk, vv in ipairs(v.param) do\n"\
"           print(vv.name..'='..vv.desc..'\\n')\n"\
"       end\n"\
"   end\n"\
"end\n"\
"\n"\
"";


static char s_szBTEvent[] = ""\
"f = io.open('../../inc/gameworld/bt_event.h');\n"\
"bInBTEvent = false;\n"\
"BTEdit = 'BET_Both';\n"\
"BTEventList = {};\n"\
"BTEvent = nil;\n"\
"for line in f:lines() do\n"\
"   if bInBTEvent and not string.find(line, '///< %@see') then\n"\
"       if string.find(line, '/%* AI') then \n"\
"           BTEdit = 'BET_AI' \n"\
"       end\n"\
"       if string.find(line, '/%* Scene') then \n"\
"           BTEdit = 'BET_Scene' \n"\
"       end\n"\
"\n"\
"       local _, _, node_name = string.find(line, '%s*(evt%w*)%s*[=,].-///<.-');\n"\
"       if node_name then\n"\
"           BTEvent = { name = node_name, type = BTEdit};\n"\
"           table.insert(BTEventList, BTEvent);\n"\
"       end\n"\
"\n"\
"       local _, _, param_name, param_desc = string.find(line, '.-@param%s*(%w+)%s*(.+)%s*[%(%[%c]');\n"\
"       if not param_desc then\n"\
"           _, _, param_name, param_desc = string.find(line, '.-@param%s*(%w+)%s*(.+)');\n"\
"       end\n"\
"\n"\
"       if param_name then\n"\
"           if not BTEvent.param then BTEvent.param = {}; end\n"\
"           local p = {name = param_name, desc = param_desc};\n"\
"           table.insert(BTEvent.param, p);\n"\
"       end\n"\
"   elseif string.find(line, 'enum BT_EVENT_TYPE') then\n"\
"       bInBTEvent = true;\n"\
"   end\n"\
"\n"\
"\n"\
"end\n"\
"f:close()\n"\
"\n"\
"print('[BTEventTypeList]\\n')\n"\
"for k,v in ipairs(BTEventList) do\n"\
"   print('BTEventTypeList='..v.name..'\\n')\n"\
"end\n"\
"\n"\
"print('\\n')\n"\
"for k,v in ipairs(BTEventList) do\n"\
"   print('\\n['..v.name..']\\n')\n"\
"   print('BTEdit='..v.type..'\\n')\n"\
"   if v.param then \n"\
"       for kk, vv in ipairs(v.param) do\n"\
"           print(vv.name..'='..vv.desc..'\\n')\n"\
"       end\n"\
"   end\n"\
"end\n"\
"\n"\
"";

INT32 LuaPrint(lua_State* L)
{
    const char* s = lua_tostring(L, 1);
    printf("%s", s);
	s_dwMsgCRC = crc32(s_dwMsgCRC, (const Bytef*)s, (UINT32)strlen(s));
    return 0;
}

INT32 LuaCRC(lua_State* L)
{
    lua_pushnumber(L, s_dwMsgCRC);
    return 1;
}

INT32 LuaGetC2SSize(lua_State* L)
{
    INT32 nSize = 0;
    INT32 nMessageID = (INT32)lua_tonumber(L, 1);

    void** ppMessage = (void**)lua_touserdata(L, 2);
    if (ppMessage)
    {
#if defined(WIN32) | defined(WIN64)
        nSize = (INT32)_msize(*ppMessage);
#elif defined(__linux__)
        nSize = malloc_usable_size(*ppMessage);
#endif
    }
    else
        nSize = -1;

    lua_pushnumber(L, nSize);

    return 1;
}

INT32 LuaGetS2CSize(lua_State* L)
{
    INT32 nSize = 0;
    INT32 nMessageID = (INT32)lua_tonumber(L, 1);

    void** ppMessage = (void**)lua_touserdata(L, 2);
    if (ppMessage)
    {
#if defined(WIN32)
        nSize = (INT32)_msize(*ppMessage);
#elif defined(__linux__)
        nSize = malloc_usable_size(*ppMessage);
#endif
    }
    else
        nSize = -1;

    lua_pushnumber(L, nSize);

    return 1;
}

BOOL GenerateMsgSize(void)
{
    INT32 nRetCode = 0;
    CLuaScript LuaScript;
    lua_State* L;
    LUA_FUNC LuaFunc;

    nRetCode = LuaScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    L = LuaScript.GetLuaState();
    LOG_PROCESS_ERROR(L);

    nRetCode = tolua_external_message_open(L);
    LOG_PROCESS_ERROR(nRetCode);

    LuaFunc.pcszFuncName = "get_c2s_size";
    LuaFunc.pFunc = LuaGetC2SSize;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    LuaFunc.pcszFuncName = "get_s2c_size";
    LuaFunc.pFunc = LuaGetS2CSize;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    LuaFunc.pcszFuncName = "print";
    LuaFunc.pFunc = LuaPrint;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    LuaFunc.pcszFuncName = "crc";
    LuaFunc.pFunc = LuaCRC;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = LuaScript.LoadFromBuffer("", s_szMsgScript, sizeof(s_szMsgScript) - 1);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL GenerateEnum(void)
{
    INT32 nRetCode = 0;
    CLuaScript LuaScript;
    lua_State* L;
    LUA_FUNC LuaFunc;

    nRetCode = LuaScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    L = LuaScript.GetLuaState();
    LOG_PROCESS_ERROR(L);

    tolua_enum_module_open(L);

    LuaFunc.pcszFuncName = "print";
    LuaFunc.pFunc = LuaPrint;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    LuaFunc.pcszFuncName = "crc";
    LuaFunc.pFunc = LuaCRC;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = LuaScript.LoadFromBuffer("", s_szEnumScript, sizeof(s_szEnumScript) - 1);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL GenerateErrcode(void)
{
	INT32 nRetCode = 0;
	CLuaScript LuaScript;
	lua_State* L;
	LUA_FUNC LuaFunc;

	nRetCode = LuaScript.Init();
	LOG_PROCESS_ERROR(nRetCode);

	L = LuaScript.GetLuaState();
	LOG_PROCESS_ERROR(L);

	tolua_enum_module_open(L);

	LuaFunc.pcszFuncName = "print";
	LuaFunc.pFunc = LuaPrint;
	nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
	LOG_PROCESS_ERROR(nRetCode);

	LuaFunc.pcszFuncName = "crc";
	LuaFunc.pFunc = LuaCRC;
	nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = LuaScript.LoadFromBuffer("", s_szErrcodeScript, sizeof(s_szErrcodeScript) - 1);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL GenerateBTNode(void)
{
    INT32 nRetCode = 0;
    CLuaScript LuaScript;
    lua_State* L;
    LUA_FUNC LuaFunc;

    nRetCode = LuaScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    L = LuaScript.GetLuaState();
    LOG_PROCESS_ERROR(L);

    tolua_enum_module_open(L);

    LuaFunc.pcszFuncName = "print";
    LuaFunc.pFunc = LuaPrint;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = LuaScript.LoadFromBuffer("", s_szBTNode, sizeof(s_szBTNode) - 1);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
};

BOOL GenerateBTEvent(void)
{
    INT32 nRetCode = 0;
    CLuaScript LuaScript;
    lua_State* L;
    LUA_FUNC LuaFunc;

    nRetCode = LuaScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    L = LuaScript.GetLuaState();
    LOG_PROCESS_ERROR(L);

    tolua_enum_module_open(L);

    LuaFunc.pcszFuncName = "print";
    LuaFunc.pFunc = LuaPrint;
    nRetCode = LuaScript.RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = LuaScript.LoadFromBuffer("", s_szBTEvent, sizeof(s_szBTEvent) - 1);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
};

int main(int argc, char* argv[])
{
    INT32 nRetCode = 0;

	nRetCode = CLog::GetInstance().Init("gen_msg", 0, 0, FALSE, FALSE, FALSE);
    LOG_PROCESS_ERROR(nRetCode);

    if (argc > 1 && strcmp(argv[1], "enum") == 0)
    {
        GenerateEnum();
    }
    else if (argc > 1 && strcmp(argv[1], "msg") == 0)
    {
        GenerateMsgSize();
	}
	else if (argc > 1 && strcmp(argv[1], "errcode") == 0)
	{
		GenerateErrcode();
	}
    else if (argc > 1 && strcmp(argv[1], "btnode") == 0)
    {
        GenerateBTNode();
    }
    else if (argc > 1 && strcmp(argv[1], "btevent") == 0)
    {
        GenerateBTEvent();
    }

	nRetCode = CLog::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

Exit0:

	return 0;
}

