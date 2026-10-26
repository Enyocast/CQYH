#ifndef _H_SERVER_LIST_H_
#define _H_SERVER_LIST_H_

#include "string_def.h"
#include "server_def.h"
#include "data_manager.h"



//tolua_begin

struct GROUP_DATA 
{
    INT32   nGroupID;
    char    szGroupName[MS_NAME_LEN];
};

struct SERVER_LIST_DATA
{
    INT32       nServerID;
    char        szName[128];
    char        szAddr[256];
    UINT32      dwPort;
    GROUP_DATA  groupList[MAX_SERVER_GROUP_COUNT];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SERVER_LIST_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};
//tolua_end

struct SERVER_LIST 
{
    INT32               nSvrNum;
    SERVER_LIST_DATA    svrList[128];
};


extern SERVER_LIST  g_ServerList;

//BOOL g_InitServerList();

#endif //_H_SERVER_LIST_H_







