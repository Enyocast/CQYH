/********************************************************************
	created:	7:8:2013   11:14
	file:		gm_config.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GM_CONFIG_H_
#define _H_GM_CONFIG_H_


// tolua_begin
#pragma pack(push, 8)



struct SVR_ADDR 
{
    INT32   nSvrID;
    char    szName[128];
    char    szAddr[256];
    UINT32  dwPort; 
};


struct GM_CONFIG 
{
    struct GM_COMMON_CONFIG 
    {
        INT32       nPingSvrInternal;
        INT32       nPingSvrTimeout;
        INT32       nSmallPacketCount;
        INT32       nLargePacketCount;

        INT32       nMaxAcceptor;
        INT32       nMaxConnector;
        INT32       nMaxSessionCount;
        INT32       nSendBufSize;
        INT32       nRecvBufSize;
        INT32       nPacketBufferSize;

        INT32       nReLoginInternal;
    }GMCommonConfig;

    struct SVR_LIST 
    {
        INT32           nSvrNum;
        SVR_ADDR        arrSvrList[128];
    }SvrList;
};



#pragma pack(pop)


// tolua_end


extern GM_CONFIG        g_GMConfig;


BOOL LoadGMConfig(const char *pcszFileName);


// tolua_begin
inline GM_CONFIG& GetGMConfig(void) {return g_GMConfig;}   
// tolua_end


#endif //_H_GM_CONFIG_H_






