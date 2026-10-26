#include "stdafx.h"
#include "p4.h"

#include "p4/clientapi.h"

BOOL check_out(const char* pcszFilePath)
{
	ClientUser ui;
	ClientApi client;
	StrBuf msg;
	Error e;

	LOG_PROCESS_ERROR(pcszFilePath);

	client.Init( &e );
	LOG_PROCESS_ERROR(!e.Test());

	client.SetArgv(1, (char* const*)&pcszFilePath);
	client.Run("edit", &ui);

	client.Final( &e );
	LOG_PROCESS_ERROR(!e.Test());

	return TRUE;
Exit0:
	return FALSE;
}