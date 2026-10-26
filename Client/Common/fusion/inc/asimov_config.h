#ifndef _ASIMOV_CONFIG_H_
#define _ASIMOV_CONFIG_H_

#include "global_config.h"

// tolua_begin
#pragma pack(push, 8)

struct ASIMOV_CONFIG
{
    LOG_CONFIG  Log;
    NET_CONFIG  Net;

    char        szAddress[256];
    UINT32      dwPort;

    INT32       nMaxSessionCount;
    INT32       nWorkThreadCount;
};

#pragma pack(pop)
// tolua_end

extern ASIMOV_CONFIG g_AsimovConfig;

#endif  // _ASIMOV_CONFIG_H_
