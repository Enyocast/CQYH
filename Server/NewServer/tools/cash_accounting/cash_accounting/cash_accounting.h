#include "stdafx.h"
#include "object_pool.h"
#include "base_list.h"

#define DB_SETTING_STRING_LEN 64
struct DBSetting
{
	char szServerAddr[DB_SETTING_STRING_LEN];
	char szLoginName[DB_SETTING_STRING_LEN];
	char szPassword[DB_SETTING_STRING_LEN];
	char szDBName[DB_SETTING_STRING_LEN];
	char szCharSet[DB_SETTING_STRING_LEN];
	char szDBNameLogData[DB_SETTING_STRING_LEN];
	UINT32 dwServerPort;
};

struct RoleMoneyUserData
{
	INT32	nBeginMoney0;
	INT32	nEndMoney0;
	INT32	nBeginMoney1;
	INT32	nEndMoney1;
	UINT32  dwBeginLogTime;
	UINT32  dwEndLogTime;
	UINT32	dwRoleID;
	char	szRoleName[21];
};

struct ACCOUNTING_ROLE : BASE_LIST_NODE
{
	INT32	dwRoleID;
	INT32	nMoney0;
	INT32	nMoney1;
	UINT32	dwLogTime;
	char	szName[21];
};

class CCashAccounting
{
public:
	CCashAccounting();
	~CCashAccounting();

	static CCashAccounting& GetInstance(void);

 	BOOL Init(void);
 	BOOL UnInit(void);
 
 	BOOL MainLoop(void);

 private:
    static void	_Load(std::list<void*>& rResult, void* pUserData);
    static void	_Check(std::list<void*>& rResult, void* pUserData);	
 
 	BOOL	_WriteLog(INT32 dwRoleID, char* pName, UINT32 dwBeginTime, UINT32 dwEndTime, INT8 byMoneyType, INT32 nBeginMoney, INT32 nEndMoney, INT32 nResult);
 
 private:
 	FILE*							m_pLogHandler;
 
 	static CCashAccounting			ms_Instance;
 	DBSetting						m_dbsetting;
 
 	CObjectPool<ACCOUNTING_ROLE>	m_AccountingRolePool;
 	CBaseList m_AccountingRoleList;
};