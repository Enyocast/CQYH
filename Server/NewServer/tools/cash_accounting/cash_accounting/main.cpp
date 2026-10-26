#include "stdafx.h"
#include "cash_accounting.h"

int _tmain(int argc, _TCHAR* argv[])
{
 	INT32 nRetCode = 0;
 
 	nRetCode = CCashAccounting::GetInstance().Init();
 	LOG_PROCESS_ERROR(nRetCode);
 
 	nRetCode = CCashAccounting::GetInstance().MainLoop();
 	LOG_PROCESS_ERROR(nRetCode);	
 
	nRetCode = CCashAccounting::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

 	return TRUE;
 Exit0:
 	return FALSE;
}

