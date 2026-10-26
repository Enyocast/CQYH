#include "stdafx.h"
#include "npc_pattern.h"

BOOL NPC_PATTERN_DATA::ReadLine(INT32& rnID, const char*& rpcszName, NPC_PATTERN_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("PatternID", nPatternID);
	READ_INT("Exp", nExp);
	READ_INT("Soul", nSoul);

	for (INT32 i = 0; i < pTabConfig->GetColCount(); i++)
	{
		INT32 nNameValue = 0;

		const char* szColName = pTabConfig->GetColName(i);
		LOG_PROCESS_ERROR(szColName);

		if (strlen(szColName) < strlen("cat"))
			continue;

		if (szColName[0] != 'c' || szColName[1] != 'a' || szColName[2] != 't')
			continue;

		nRetCode = g_pReadDataScript->CallFunction("read_int_expr", "s:d", pTabConfig->GetColName(i), &nNameValue);
		LOG_PROCESS_ERROR(nRetCode);

		LOG_PROCESS_ERROR(nNameValue < catTotal);

		nRetCode = pTabConfig->ReadData(i, nRow, pData->nAttrListA[nNameValue]);
		LOG_PROCESS_ERROR(nRetCode);
	}

	READ_END(nPatternID);
}
