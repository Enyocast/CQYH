#ifndef _LUA_SCRIPT_H_
#define _LUA_SCRIPT_H_

#define tolua_readonly

extern "C"
{
	#include "lualib.h"
	#include "lauxlib.h"
}

#define SCRIPT_NAME_LEN	(256)

struct LUA_FUNC
{
	const char*		pcszFuncName;
	lua_CFunction	pFunc;
};

class CLuaScript
{
public:
	CLuaScript();
	virtual ~CLuaScript();

	BOOL Init(void);
	BOOL UnInit(void);

	BOOL LoadFromFile(const char* pcszFileName);
	BOOL LoadFromBuffer(const char* pcszScriptName, const char* pcszBuffer, UINT32 dwSize);

	BOOL RegisterFunc(LUA_FUNC FuncList[], INT32 nFuncCount);

	BOOL CallFunction(const char* pcszFuncName, const char* pcszFormat, ...);
    BOOL Execute(void);

    BOOL IsFuncExist(const char* pcszFuncName);
    BOOL IsTableExist(const char* pcszTableName);

	const char* GetScriptName(void);
	lua_State* GetLuaState(void);
	static CLuaScript* GetScriptFromState(lua_State* L);

    BOOL CollectGarbage(INT32 nGCSize);

    UINT32 GetCRC(void);

private:
    BOOL _CallFunction(const char* pcszFuncName, const char* pcszFormat, va_list valist );
    void _GetCRC(const char* pcszFileName, INT32 nLevel);

private:
	char				m_szScriptName[SCRIPT_NAME_LEN];
	lua_State*			m_pLuaState;
    UINT32              m_dwCRC;

	static INT32 _Include(lua_State* L);
    static INT32 _LuaErrFunc(lua_State* L);
    static void _EnumTable(lua_State* L, int nTableIndex, int nTableDepth);
    static INT32 _Print(lua_State* L);
};

#endif	// _LUA_SCRIPT_H_
