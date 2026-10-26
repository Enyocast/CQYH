#ifndef _STATIS_INFO_
#define _STATIS_INFO_

#include "statis_info_def.h"

#define STATIS_MEMORY_NAME        "StatisShareMemory"
#define STATIS_MEMORY_TAG         'stat'

struct stStatisInfoShm
{
    UINT32          dwTag;
    INT32           nSize;

	stStatisInfo    oInfo;
};

stStatisInfoShm* g_GetStatisInfoShm( void );

BOOL g_InitStatisInfo( UINT32 dwProcessID );
BOOL g_MainloopStatisInfo();
void g_ResetStatisInfo(void);
INT32 g_GetProcessStatisIndex(UINT32 dwProcessID);
BOOL g_SetProcessStatisInfo(INT32 nStatisProcessIndex, INT32 nEnum, INT64 llValue);

INT32   g_GetStatisEnumCount();
const char* g_GetStatisName( INT32 nEnum );

extern stStatisProcess* s_pCurrentStatisProcess;

inline BOOL g_ChangeStatisInfo(INT32 nEnum, INT32 nValue)
{
	LOG_PROCESS_ERROR(nEnum > statInvalid && nEnum < statTotal);
	PROCESS_ERROR(s_pCurrentStatisProcess);

	s_pCurrentStatisProcess->qwStatisEntry[nEnum] += nValue;
	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL g_SetStatisInfo(INT32 nEnum, INT32 nValue)
{
	LOG_PROCESS_ERROR(nEnum > statInvalid && nEnum < statTotal);
	PROCESS_ERROR(s_pCurrentStatisProcess);

	s_pCurrentStatisProcess->qwStatisEntry[nEnum] = nValue;

	return TRUE;
Exit0:
	return FALSE;
}

#endif //_STATIS_INFO_