#include "stdafx.h"
#include "script_mgr.h"

#include <time.h>
#include "ifile.h"
#include "lstate.h"
#include "lmem.h"

CScriptMgr CScriptMgr::ms_Instance;

CScriptMgr::CScriptMgr(void)
{
    m_bReload = FALSE;
    m_szRootPath[0] = 0;
}

CScriptMgr::~CScriptMgr(void)
{
    UnInit();
}

BOOL CScriptMgr::Init(const char* pcszRootPath)
{
	INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pcszRootPath);

    m_bReload = FALSE;
    strxcpy(m_szRootPath, pcszRootPath, 256);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CScriptMgr::UnInit(void)
{
    for (MAP_NAME_2_PACKAGE::iterator it = m_mapPackage.begin();
        it != m_mapPackage.end(); ++it)
    {
        const char* pcszPackageName = it->first;
        SAFE_DELETE_ARRAY(pcszPackageName);
    }

    for (MAP_NAME_2_SCRIPT::iterator it = m_mapScript.begin();
        it != m_mapScript.end(); ++it)
    {
        it->second->UnInit();

        SAFE_DELETE(it->second);
    }

    m_mapPackage.clear();
    m_mapScript.clear();
    m_lstLuaFunc.clear();
	memset(m_szRootPath, 0, 256);

    return TRUE;
}

CScriptMgr& CScriptMgr::GetInstance(void)
{
    return ms_Instance;
}

BOOL CScriptMgr::Reload(INT32& rnErrorCount)
{
    INT32 nRetCode = 0;

    m_bReload = FALSE;
    rnErrorCount = 0;

    for (MAP_NAME_2_SCRIPT::iterator it = m_mapScript.begin();
        it != m_mapScript.end(); ++it)
    {
        CLuaScript* poScript = it->second;

        nRetCode = poScript->LoadFromFile(it->first);
        LOG_CHECK_ERROR(nRetCode);
        if (!nRetCode)
            rnErrorCount++;
    }

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CScriptMgr::Reload(const char *pcszScriptName)
{
    INT32       nRetCode = 0;
    CLuaScript* poScript = NULL;
    MAP_NAME_2_SCRIPT::iterator     iter;
    LOG_PROCESS_ERROR(pcszScriptName);

    iter = m_mapScript.find(pcszScriptName);
    LOG_PROCESS_ERROR(iter != m_mapScript.end());

    poScript = iter->second;

    nRetCode = poScript->LoadFromFile(iter->first);
    LOG_PROCESS_ERROR(nRetCode );

    return TRUE;
Exit0:
    return FALSE;
}

INT32 CScriptMgr::_LoadPackage(lua_State* L)
{
    const CHAR * pcszPackageName = NULL;
    lua_CFunction pLoadPackage = NULL;

    LOG_PROCESS_ERROR(lua_gettop(L) > 0);

    pcszPackageName = lua_tostring(L, 1);
    LOG_PROCESS_ERROR(pcszPackageName);

    pLoadPackage = CScriptMgr::GetInstance().FindPackage(pcszPackageName);
    LOG_PROCESS_ERROR(pLoadPackage);

    return pLoadPackage(L);

Exit0:
    if (pcszPackageName)
        CRI("failed to load package %s", pcszPackageName);

    return 0;
}

CLuaScript* CScriptMgr::NewScript(const char* pcszScriptFile)
{
	INT32 nRetCode = FALSE;
    char szFileName[SCRIPT_NAME_LEN];
    CLuaScript* poScript = NULL;
    std::pair<MAP_NAME_2_SCRIPT::iterator, bool> InsRet;

    LOG_PROCESS_ERROR(pcszScriptFile);

	poScript = new CLuaScript();
    LOG_PROCESS_ERROR(poScript);

	nRetCode = poScript->Init();
	LOG_PROCESS_ERROR(nRetCode);

    lua_register(poScript->GetLuaState(), "LoadPackage", _LoadPackage);

    for (LST_LUA_FUNC::iterator it = m_lstLuaFunc.begin();
        it != m_lstLuaFunc.end(); ++it)
    {
        nRetCode = poScript->RegisterFunc(*it, 0);
        LOG_PROCESS_ERROR(nRetCode);
    }

	snprintf(szFileName, SCRIPT_NAME_LEN, "%s/%s", m_szRootPath, pcszScriptFile);
	nRetCode = poScript->LoadFromFile(szFileName);
	LOG_PROCESS_ERROR(nRetCode);

    InsRet = m_mapScript.insert(std::make_pair(poScript->GetScriptName(), poScript));
    LOG_PROCESS_ERROR(InsRet.second);

	return poScript;
Exit0:
    if (poScript)
    {
        poScript->UnInit();
        SAFE_DELETE(poScript);
    }

	return NULL;
}

BOOL CScriptMgr::DelScript(CLuaScript* poScript)
{
    MAP_NAME_2_SCRIPT::iterator it;
	PROCESS_ERROR(poScript);

    it = m_mapScript.find(poScript->GetScriptName());
    LOG_PROCESS_ERROR(it != m_mapScript.end());
    SAFE_DELETE(it->second);

	m_mapScript.erase(it);

    return TRUE;
Exit0:

    return FALSE;
}

CLuaScript* CScriptMgr::FindScript(const char* pcszScriptName)
{
    char szFileName[SCRIPT_NAME_LEN];

    snprintf(szFileName, SCRIPT_NAME_LEN, "%s/%s", m_szRootPath, pcszScriptName);
    MAP_NAME_2_SCRIPT::iterator it = m_mapScript.find(szFileName);
    PROCESS_ERROR(it != m_mapScript.end());

	return it->second;
Exit0:
	return NULL;
}

BOOL CScriptMgr::RegisterPackage(const char* pcszPackageName, lua_CFunction pLoadPackage)
{
    char* pszPackageName = NULL;
    std::pair<MAP_NAME_2_PACKAGE::iterator, bool> InsRet;

    LOG_PROCESS_ERROR(pcszPackageName);
    LOG_PROCESS_ERROR(pLoadPackage);

    pszPackageName = new char[SCRIPT_NAME_LEN];
    LOG_PROCESS_ERROR(pszPackageName);

    strxcpy(pszPackageName, pcszPackageName, SCRIPT_NAME_LEN);

    InsRet = m_mapPackage.insert(std::make_pair(pszPackageName, pLoadPackage));
    LOG_PROCESS_ERROR(InsRet.second);

    return TRUE;
Exit0:
    SAFE_DELETE_ARRAY(pszPackageName);

    return FALSE;
}

lua_CFunction CScriptMgr::FindPackage(const char* pcszPackageName)
{
    MAP_NAME_2_PACKAGE::iterator it;

    it = m_mapPackage.find(pcszPackageName);
    LOG_PROCESS_ERROR(it != m_mapPackage.end());

    return it->second;
Exit0:
    return NULL;
}

BOOL CScriptMgr::RegisterFuncList(LUA_FUNC* pFuncList)
{
    LOG_PROCESS_ERROR(pFuncList);

    m_lstLuaFunc.push_back(pFuncList);

    return TRUE;
Exit0:
    return FALSE;
}

void CScriptMgr::SetRootPath(const char* pcszRootPath)
{
	if (pcszRootPath == NULL)
		m_szRootPath[0] = 0;
	else
		strxcpy(m_szRootPath, pcszRootPath, 256);
}

const char* CScriptMgr::GetRootPath(void)
{
    return m_szRootPath;
}

INT64 CScriptMgr::PrintMemoryStat(void)
{
	INT64 llTotalSize = 0;

	for (MAP_NAME_2_SCRIPT::iterator it = m_mapScript.begin();
		it != m_mapScript.end(); ++it)
	{
		lua_State* L = it->second->GetLuaState();
		INF("script %s allocated %.2fMB used %.2f", it->first, L->l_G->totalbytes / (1024 * 1024.0f),
			L->l_G->estimate / (1024 * 1024.0f));
		llTotalSize += (L->l_G->totalbytes + sizeof(CLuaScript));
	}

	INF("all scripts allocated %.2fMB", llTotalSize / (1024 * 1024.0f));

	return llTotalSize;
}
