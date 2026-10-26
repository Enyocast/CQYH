#ifndef _SCRIPT_MGR_H_
#define _SCRIPT_MGR_H_

#include <list>
#include <map>
#include "lua_script.h"

class CScriptMgr
{
public:
	CScriptMgr(void);
	virtual ~CScriptMgr(void);

    BOOL Init(const char* pcszRootPath);
    BOOL UnInit(void);
	static CScriptMgr& GetInstance(void);
    BOOL Reload(INT32& rnErrorCount);
    BOOL Reload(const char *pcszScriptName);

    CLuaScript* NewScript(const char* pcszScriptName);
    BOOL DelScript(CLuaScript* poScript);
	CLuaScript* FindScript(const char* pcszScriptName);

    BOOL RegisterPackage(const char* pcszPackageName, lua_CFunction pLoadPackage);
    lua_CFunction FindPackage(const char* pcszPackageName);

    BOOL RegisterFuncList(LUA_FUNC* pFuncList);
	void SetRootPath(const char* pcszRootPath);
    const char* GetRootPath(void);

	INT64 PrintMemoryStat(void);

private:
    static INT32 _LoadPackage(lua_State* L);

private:
    static CScriptMgr ms_Instance;

	struct ltstr
	{
		inline bool operator()(const char* str1, const char* str2) const
		{
			return strncmp(str1, str2, SCRIPT_NAME_LEN) < 0;
		}
	};

	typedef std::map<const char*, CLuaScript*, ltstr> MAP_NAME_2_SCRIPT;
	MAP_NAME_2_SCRIPT   m_mapScript;

    typedef std::map<const char*, lua_CFunction, ltstr> MAP_NAME_2_PACKAGE;
    MAP_NAME_2_PACKAGE  m_mapPackage;

    typedef std::list<LUA_FUNC*> LST_LUA_FUNC;
    LST_LUA_FUNC        m_lstLuaFunc;

    BOOL                m_bReload;
    char                m_szRootPath[256];
};

#endif // _script_mgr_h__
