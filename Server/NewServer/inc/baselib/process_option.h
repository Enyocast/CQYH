#ifndef _PROCESS_OPTION_H_
#define _PROCESS_OPTION_H_

#define MAX_OPTION_COUNT 16;

BOOL ProcessOption(INT32 argc, TCHAR** argv);

const char* GetServerName(INT32 nEnum);
const char* GetServerShortName(INT32 nEnum);

#endif