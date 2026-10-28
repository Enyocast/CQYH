#include "stdafx.h"
#include "sol_bindings.h"
#include "read_data_helper.h"

#include "script/sol_enum.h"
#include "script/sol_string_table.h"

CLuaScript* g_pReadDataScript = NULL;
char g_szErrorMsg[16 * 1024] = {0};
INT32 g_nErrorMsgSize = 0;

INT32 _VoidFunc(lua_State* L)
{
    return 0;
}

BOOL g_InitReadDataScript(const char* pcszConfigPath, const char* pcszScriptName)
{
    INT32 nRetCode = 0;
    char szFileName[MAX_PATH];
    LUA_FUNC LuaFunc;

    LOG_PROCESS_ERROR(pcszConfigPath);
    LOG_PROCESS_ERROR(pcszScriptName);

    snprintf(szFileName, MAX_PATH, "%s/%s", pcszConfigPath, pcszScriptName);

    g_pReadDataScript = new CLuaScript;
    LOG_PROCESS_ERROR(g_pReadDataScript);

    nRetCode = g_pReadDataScript->Init();
    LOG_PROCESS_ERROR(nRetCode);

    sol_enum_open(g_pReadDataScript->GetLuaState());
    sol_string_table_open(g_pReadDataScript->GetLuaState());

    LuaFunc.pcszFuncName = "LoadPackage";
    LuaFunc.pFunc = _VoidFunc;
    nRetCode = g_pReadDataScript->RegisterFunc(&LuaFunc, 1);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_pReadDataScript->LoadFromFile(szFileName);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    SAFE_DELETE(g_pReadDataScript);

    return FALSE;
}

BOOL g_UnInitReadDataScript(void)
{
    if (g_pReadDataScript)
    {
        g_pReadDataScript->UnInit();
        SAFE_DELETE(g_pReadDataScript);
    }

    return TRUE;
}

void g_AppendErrorMsg(const char* pcszErrorMessage, ...)
{
    INT32 nRetCode = 0;
    va_list valist;
    extern char g_szErrorMsg[];
    extern INT32 g_nErrorMsgSize;

    va_start(valist, pcszErrorMessage);
    nRetCode = vsnprintf(g_szErrorMsg + g_nErrorMsgSize, 16 * 1024 - g_nErrorMsgSize, pcszErrorMessage, valist);
    PROCESS_ERROR(nRetCode);

    g_nErrorMsgSize += nRetCode;

    va_end(valist);

Exit0:
    return;
}
