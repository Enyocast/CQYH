#ifndef _H_GM_LOG_NOTE_H_
#define _H_GM_LOG_NOTE_H_


#include "data_manager.h"

#define GM_LOG_LENGTH   (64)
#define GM_LOG_NOTE_LENGTH  (256)

struct GM_LOG_NOTE
{
    INT32       nID;
    char        szLog[GM_LOG_LENGTH];
    char        szNote[GM_LOG_NOTE_LENGTH];

    static BOOL HasName(void)	{ return FALSE; }

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GM_LOG_NOTE* pData, CTabFile* pTabConfig, INT32 nRow);
};

typedef std::map<std::string, std::string>  GM_LOG_MAP;

extern GM_LOG_MAP      g_GMLogMap;


#endif //_H_GM_LOG_NOTE_H_

