/********************************************************************
	created:	7:8:2013   11:14
	file:		tl_config.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_TL_CONFIG_H_
#define _H_TL_CONFIG_H_


// tolua_begin
#pragma pack(push, 8)


#define PING_SVR_INTERNAL (1000)
#define PING_SVR_TIMEOUT (30000000)
#define RECONNECT_TIME (10000)
#define SMALL_PACKET_COUNT (2048)
#define LARGE_PACKET_COUNT (64)

#define MAX_ACCEPTOR (8)
#define MAX_CONNECTOR (32)
#define MAX_SESSION_COUNT (32)
#define SEND_BUF_SIZE (1024 * 1024 * 1)
#define RECV_BUF_SIZE (1024 * 1024 * 1)
#define PACKET_BUFFER_SIZE (1024 * 1)
#define RELOGIN_INTERNAL (10000)
#define CMD_DATA_POOL_COUNT (100)


#define GM_MAX_SERVER_COUNT (128)

struct GM_GROUP_DATA
{
    char        szGroupName[33];
};


struct  GM_SVR
{
    INT32       nSvrID;
    char        szName[128];
    char        szAddr[128];
    UINT32      dwPort;

    GM_GROUP_DATA   groupList[32];
};


struct TL_CONFIG 
{
    struct GM_SVR_LIST 
    {
        INT32       nSvrNum;

        GM_SVR     arrGMList[GM_MAX_SERVER_COUNT];
    };

    GM_SVR_LIST     ServerList;
};


#pragma pack(pop)

// tolua_end

GM_SVR *GetServer(INT32 nSvrID);


extern TL_CONFIG        g_TLConfig;

BOOL LoadTLConfig(const char *pcszFileName);
BOOL LoadTLConfigFromBuffer(const char *pcScriptName, const char *pcBuffer, UINT32 dwSize);

// tolua_begin
inline TL_CONFIG& GetTLConfig(void) {return g_TLConfig;}   
// tolua_end


#endif //_H_TL_CONFIG_H_






