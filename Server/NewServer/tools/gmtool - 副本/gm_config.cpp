/********************************************************************
	created:	7:8:2013   11:32
	file:		gm_config.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "sol_bindings.h"
#include "gm_config.h"
#include "script_mgr.h"
#include "string_ex.h"
#include "sol_gm_config.h"

GM_CONFIG   g_GMConfig;
static char szLoadFileName[256] = {0};
static char szSaveFilePath[256] = {0};


BOOL LoadGMConfig(const char *pcszFileName)
{
    INT32   nRetCode = 0;
    CLuaScript  oScript;
    INT32   nStackTop = 0;

    nRetCode = oScript.Init();
    LOG_PROCESS_ERROR(nRetCode);

    sol_gm_config_open(oScript.GetLuaState());
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.LoadFromFile(pcszFileName);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = oScript.CallFunction("LoadFile", "");

    strxcpy(szLoadFileName, pcszFileName, 256);
    oScript.UnInit();
    return TRUE;
Exit0:
    oScript.UnInit();
    return FALSE;
}




