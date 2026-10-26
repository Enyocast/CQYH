#include "stdafx.h"
#include "account_logout.h"

int main()
{
	INT32 nRetCode = 0;

	nRetCode = CAccountLogout::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CAccountLogout::GetInstance().MainLoop();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CAccountLogout::GetInstance().Uninit();
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}