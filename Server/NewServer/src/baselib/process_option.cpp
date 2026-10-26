#include "stdafx.h"
#include "process_option.h"
#include "server_def.h"

static UINT32 g_nCmdStartIndex = 1;

extern char g_szGlobalConfigFileName[MAX_PATH];

BOOL ProcessConfigOption(const char* pcszConfigName)
{
    INT32 nRetCode = 0;

    strxcpy(g_szGlobalConfigFileName, pcszConfigName, MAX_PATH);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL ProcessViewOption(INT32 nTop, INT32 nLeft)
{
#if (defined(WIN32) || defined(WIN64))
        SetWindowPos(GetConsoleWindow(), HWND_TOP, nTop, nLeft, 0, 0, SWP_NOSIZE);
#endif  
    return TRUE;
}

INT32 ProcessOption(INT32 argc, TCHAR** argv)
{
	INT32 nResult = 1;
    INT32 nRetCode = 0;
    for(INT32 i = 1 ; i < argc; ++i)
    {
        if(strcmp("config", argv[i]) == 0)
        {
			LOG_PROCESS_ERROR(i + 1 < argc && argv[i + 1]);

            nRetCode = ProcessConfigOption(argv[i+1]);
            LOG_PROCESS_ERROR(nRetCode);

			++i;
        }
        else if(strcmp("view", argv[i]) == 0)
        {
            INT32 nTop = 0;
            INT32 nLeft = 0;

            LOG_PROCESS_ERROR(argv[i+1]);
            LOG_PROCESS_ERROR(argv[i+2]);

            nTop = atoi(argv[i+1]);
            nLeft = atoi(argv[i+2]);

            nRetCode = ProcessViewOption(nTop, nLeft);
            LOG_PROCESS_ERROR(nRetCode);

            i += 2;
        }
        else if(strcmp("cmd", argv[i]) == 0)
        {
			nResult = i + 1;
        }
    }

	return nResult;
Exit0:
	return nResult;
}



///////////////////////////////////////////////////////////////////////////////////
// TODO: gen_msg generate
static struct {
	const char* szName;
	const char* szShortName;
} s_ServerEnum2Names[] =
{
	{ "invalid", "" },   //stInvalid
	{ "guardserver", "" },   //stGD
	{ "manageserver", "MS" }, //stMS
	{ "dbserver", "DB" }, //stDB
	{ "balanceserver", "BS" }, //stBS
	{ "loginserver", "LS" }, //stLS
	{ "gateserver", "GT" }, //stGT
	{ "gameserver", "GS" }, //stGS
	{ "gmserver", "GM" }, //stGM
	{ "datalogserver", "DL" }, //stDL
	{ "mobileserver", "MM" }, //stMM
	{ "mgateserver", "MG" }, //stMG
	{ "asimov", "" },   //stClient
	{ "invalid", "" },   //stMT
	{ "invalid", "" },   //stCS
	{ "invalid", "" },   //stTL
	{ "invalid", "" },   //stAll
	{ "invalid", "" },   //stTotal
};

const char* GetServerName(INT32 nEnum)
{
	LOG_PROCESS_ERROR(nEnum >= stMS && nEnum < stClient);
	return s_ServerEnum2Names[nEnum].szName;
Exit0:
	return NULL;
}

const char* GetServerShortName(INT32 nEnum)
{
	LOG_PROCESS_ERROR(nEnum >= stMS && nEnum < stClient);
	return s_ServerEnum2Names[nEnum].szShortName;
Exit0:
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////
