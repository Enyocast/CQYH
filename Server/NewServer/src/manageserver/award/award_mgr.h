#ifndef _H_REWARD_MANAGER_H_
#define _H_REWARD_MANAGER_H_

#include <vector>
#include <string>
#include "../3rd/award/Include/sotsapi.h"

typedef INT32 (*FunRmInitialize)(const char *configFileName,pSotsMsgHandler handler);
typedef INT32 (*FunRmTerminate)();
typedef ULONG (*FunRmAsynCall)(const char *serviceName, const void* data, INT32 dataLen, UINT32 flags);
typedef INT32 (*FunRmGetSotsUniqueId)(char *orderId,INT32 len);

#define AWARD_SOTS_DLL_PATH	"..\\3rd\\award\\Dll\\sotsapi.dll"
#define AWARD_CONFIG_PATH "..\\award\\ToolGetConfig.ini"

typedef std::vector<std::string> VecSerialNumber;

struct MS_ONLINE_ROLE_DATA;

class CAwardManager
{
public:
	CAwardManager();
	~CAwardManager();

	static CAwardManager		m_Instance;
	static CAwardManager		&GetInstance();

	BOOL    Init();
	BOOL    UnInit();

	inline SOTSCLIENTINFO& GetClientInfo();

	/****** send msg to ump platform ******/ 
	BOOL	SendAwardReq(MS_ONLINE_ROLE_DATA* pOnlineUserData, INT32 nAwardType, char* chAwardNumber=NULL);
	BOOL	SendAwardAck(INT32 nResult, INT32 nUserType, char* pUserID, char* pOrderID, INT32 nReason);
	BOOL	SendS2cAck(char* pOrderID, char* pMsgID, INT32 nVersion, INT32 nResult);

private: 
	FunRmInitialize         m_pRmInitialize;
	FunRmTerminate          m_pRmTerminate;
	FunRmAsynCall           m_pRmAsynCall;
	FunRmGetSotsUniqueId    m_pRmGetSotsUniqueId;

	SOTSCLIENTINFO			m_cltinfo;
};

inline SOTSCLIENTINFO& CAwardManager::GetClientInfo()
{
	return m_cltinfo;
}

#endif // _H_REWARD_MANAGER_H_