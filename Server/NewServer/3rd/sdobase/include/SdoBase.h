#ifndef _EXTEN_COMMON_SDK_H_
#define _EXTEN_COMMON_SDK_H_

#define IN 
#define OUT

#if defined(_WIN32) || defined(_WIN64)
#define SNDACALL			__stdcall
#else
#define SNDACALL
#endif

#ifndef interface
#define interface	struct
#endif

#ifndef PURE
#define PURE		= 0
#endif

#define SNDACALLBACK		SNDACALL
#define SNDAMETHOD(Type)	virtual Type SNDACALL
#define SNDAAPI(Type)		extern "C" Type SNDACALL


typedef enum 
{
	E_REQUEST=0xA1,    //请求
	E_RESPONSE=0xA2     //应答
}EMsgDirection;


interface ISDOCommonMsg
{
	SNDAMETHOD(int)	GetValue(IN const char* pKey, OUT void ** pValue, OUT int * pLen) PURE;
	SNDAMETHOD(int)	GetValue(IN const char* pKey, OUT char ** ppValue) PURE;
	SNDAMETHOD(int)	GetValue(IN const char* pKey, OUT int *pValue) PURE;
	
	SNDAMETHOD(void) SetValue(IN const char* pKey, IN const void * pValue, IN int nLen) PURE;
	SNDAMETHOD(void) SetValue(IN const char* pKey, IN const char* pValue) PURE;
	SNDAMETHOD(void) SetValue(IN const char* pKey, IN int nValue) PURE;

	/* for ext head */
	SNDAMETHOD(void) SetExtHead(IN const void * pExtHead, IN int nLen) PURE;
	SNDAMETHOD(void) GetExtHead(OUT void ** pExtHead, OUT int * pLen) PURE;
	
	SNDAMETHOD(char *)	GetMsgName() PURE;
	SNDAMETHOD(void) Release() PURE;
};
SNDAAPI(ISDOCommonMsg*) sdoCreateMsg(IN EMsgDirection eMsgType, IN const char * szMsgName);


typedef int (SNDACALLBACK *CommonSDKCallBack)(OUT EMsgDirection eMsgType, OUT unsigned int dwRpcId, OUT int nResult,  OUT const ISDOCommonMsg* pMsg);
interface ISDOCommonHandler
{
	 SNDAMETHOD(int) Initialize(IN const char *pConfigFile, IN const char *pCallVersion=0) PURE;
	 SNDAMETHOD(void) Uninitialize() PURE;
	 SNDAMETHOD(void) RegisterCallback(IN const char *pServiceName, IN const CommonSDKCallBack pCallBack) PURE;
	 
	 SNDAMETHOD(unsigned int) GetRpcId()PURE;
	 SNDAMETHOD(int) ASyncSendMsg(IN const ISDOCommonMsg* pRequest, IN unsigned int dwRpcId, IN unsigned int dwTimeout = 0) PURE;
	 SNDAMETHOD(int) SyncSendMsg(IN const ISDOCommonMsg* pRequest, OUT ISDOCommonMsg* pResponse, IN unsigned int dwTimeout = 0) PURE;
	 
	 SNDAMETHOD(void) GetGUID(OUT char szGUID[33]) PURE;
	 SNDAMETHOD(void) Release() PURE;
};
SNDAAPI(ISDOCommonHandler*) sdoCreateCommonHandler();
#endif




