#include "stdafx.h"
#include "rolelogcheck.h"
#include "dump.h"

#include <time.h>
#include "time_ex.h"
#include "report.h"
#include "ifile.h"
#include "math_ex.h"

#include "global_config.h"
#include "server_config.h"
#include "process_option.h"
#include "version.h"
#include "statis_info.h"
#include <conio.h>


/************************************************************************/
BOOL _InitServer(void)
{
    INT32 nRetCode = 0;

    nRetCode = CLog::GetInstance().Init("role_log_check", 
		lltAll,
		lotFile,
        TRUE, 
		TRUE,
        TRUE);
	LOG_PROCESS_ERROR(nRetCode);
	g_InitReportSetting(GetServerShortName(stGS), 0, g_ServerConfig.Common.szReportAbsolutePath);

	nRetCode = CRoleLogCheck::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL _UnInitServer(void)
{
    INT32 nRetCode = 0;

	nRetCode = CRoleLogCheck::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

BOOL CheckGameFrame(void)
{
    static UINT32 s_qwLastDumpTick = 0;

    return FALSE;
}

INT32 main(INT32 argc, char** argv)
{
    INT32 nRetCode = 0;

#if defined(WIN32)

	nRetCode = StartDumpThread(CheckGameFrame, FALSE, "log");
	LOG_PROCESS_ERROR(nRetCode);

    SetDumpOption(g_ServerConfig.Common.bShowDumpDialog);

#endif

    /************************************************************************/
	// initialize
	nRetCode = _InitServer();
    LOG_PROCESS_ERROR(nRetCode);

	/************************************************************************/

	nRetCode = CRoleLogCheck::GetInstance().CheckParam(argc, argv);
	LOG_PROCESS_ERROR(nRetCode);

	__try
	{
		if (argc > 3)
		{
			nRetCode = CRoleLogCheck::GetInstance().DoCheckLog(argv[1], argv[2], argv[3], argv[4]);
		}
		else
		{
			nRetCode = CRoleLogCheck::GetInstance().DoCheckLog(argv[1], argv[2], NULL, NULL);
		}

		if (!nRetCode)
		{
			COutput::GetInstance().Printf("*** log file parse fail ***");
		}
		else
		{
			COutput::GetInstance().Printf("log file parse complete.");
		}

	}
	__except (DumpExceptionFilter(GetExceptionInformation()))
	{
	}

    /************************************************************************/
    // exit
    INF("Server is exiting");
	PROCESS_SUCCESS(TRUE);

Exit0:
	INF("Server has exited");
Exit1:

#if defined(WIN32)
    StopDumpThread();
#endif

	//COutput::GetInstance().Printf("Enter any key to exit !");
	//getch();

	nRetCode = _UnInitServer();
	LOG_CHECK_ERROR(nRetCode);
	
	//COutput::GetInstance().Printf("...");

    return 0; 
}


