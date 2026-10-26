#include "stdafx.h"
#include "gm_log_note.h"

#include <map>
#include <string>

using namespace std;

GM_LOG_MAP      g_GMLogMap;

BOOL GM_LOG_NOTE::ReadLine(INT32& rnID, const char*& rpcszName, GM_LOG_NOTE* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("ID", nID);
    READ_STR("LOG", szLog);
    READ_STR("Note", szNote);

    READ_END(nID);
}



