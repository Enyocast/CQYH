#ifndef _ROLE_LOG_CHECK_H_
#define _ROLE_LOG_CHECK_H_

#include "tabfile.h"
#include "object_pool.h"
#include <time.h>
#include "global_data_manager.h"
#include "simple_list.h"
#include "base_list.h"


#define PROMPT_TEXT_X         (0)
#define PROMPT_TEXT_Y         (20)
#define PROMPT_START_X        (17)
#define PROMPT_START_Y        (20)

#define MONEY_TYPE_GOLD       (1)

#define ACTION_ADD_MONEY      (1)
#define ACTION_SUB_MONEY      (2)

#define GM_ROLE_FLAG_STR          "RoleID["
#define GM_ROLE_FLAG_STR2         "Role["
#define GM_MONEY_TYPE_FLAG_STR    "MoneyType["
#define GM_OLD_MONEY_FLAG_STR     "Old Money["
#define GM_NEW_MONEY_FLAG_STR     "New["

#define FAST_READ_START()                                                            \
    INT32 nRetCode = 0;                                                         \
    INT32 nValue = 0;                                                          

#define FAST_READ_INT(__col__, __var__)                                            \
    nRetCode = pTabConfig->ReadData(__col__, nRow, nValue);             \
    LOG_PROCESS_ERROR(nRetCode);                                   \
    pData->__var__ = nValue;

#define FAST_READ_STR(__col__, __var__)                                                                    \
    nRetCode = pTabConfig->ReadData(__col__, nRow, pData->__var__, sizeof(pData->__var__));     \
    LOG_PROCESS_ERROR(nRetCode);




//String argument: year-month-day hour:minute:second
time_t Str2Time(const char* szTime);
time_t CustomizedStr2Time(const char* szTime);

#pragma pack(push, 1)

struct MONEY_LOG_DATA
{
	INT32 nRoleID;
	UINT32 dwTime;
	INT8 nAction;
	INT8 nMoneyType;
	INT32 nMoneyCount;
	SimpleListNode oMoneyLogNode;

	static INT32 nID;
	static INT32 nSrcRoleID;
	static INT32 nTargetRoleID;
	static char szTime[20];
	static char szAction[20];

	SimpleListNode& GetSimpleListNode(void)
	{
		return oMoneyLogNode;
	}

	static MONEY_LOG_DATA* ParseSimpleListNode(SimpleListNode* pSimpleListNode)
	{
		MONEY_LOG_DATA* pResult = NULL;

		PROCESS_ERROR(pSimpleListNode);

		pResult = node_cast(MONEY_LOG_DATA*, GetSimpleListNode(), pSimpleListNode);
		LOG_PROCESS_ERROR(pResult);

		return pResult;
	Exit0:
		return NULL;
	}

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, MONEY_LOG_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
	{
		FAST_READ_START();       

		FAST_READ_STR(0, szTime);
		pData->dwTime = (UINT32)CustomizedStr2Time(szTime);
		LOG_PROCESS_ERROR(0 != pData->dwTime);

		FAST_READ_INT(3, nSrcRoleID);
		FAST_READ_INT(4, nTargetRoleID);

		FAST_READ_STR(5, szAction);
		if (strcmp(szAction, "Add") == 0)
		{
			pData->nAction = ACTION_ADD_MONEY;
			pData->nRoleID = pData->nTargetRoleID;
		}
		else if (strcmp(szAction, "Sub") == 0)
		{
			pData->nAction = ACTION_SUB_MONEY;
			pData->nRoleID = pData->nSrcRoleID;
		}
		else
		{
			LOG_PROCESS_ERROR(FALSE);
		}

		FAST_READ_INT(6, nMoneyType);
		FAST_READ_INT(7, nMoneyCount);

		READ_END(nID);
	}

};

struct GM_LOG_DATA
{
	INT32 nRoleID;
	UINT32 dwTime;
	INT8 bIsMoneyLog;
	INT8 nAction;
	INT8 nMoneyType;
	INT32 nMoneyCount;
	SimpleListNode oGMLogNode;

	static INT32 nID;
	static char szTime[20];
	static char szContent[2048];

	SimpleListNode& GetSimpleListNode(void)
	{
		return oGMLogNode;
	}

	static GM_LOG_DATA* ParseSimpleListNode(SimpleListNode* pSimpleListNode)
	{
		GM_LOG_DATA* pResult = NULL;

		PROCESS_ERROR(pSimpleListNode);

		pResult = node_cast(GM_LOG_DATA*, GetSimpleListNode(), pSimpleListNode);
		LOG_PROCESS_ERROR(pResult);

		return pResult;
	Exit0:
		return NULL;
	}

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GM_LOG_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
	{
		INT32 nNewMoney = 0;
		INT32 nOldMoney = 0;
		char* pRoleIDStr = NULL;
		char* pOldMoneyStr = NULL;
		char* pNewMoneyStr = NULL;
		char* pMoneyTypeStr = NULL;

		FAST_READ_START();         

		FAST_READ_STR(0, szTime);
		pData->dwTime = (UINT32)CustomizedStr2Time(szTime);
		LOG_PROCESS_ERROR(0 != pData->dwTime);

		FAST_READ_STR(4, szContent);

		pMoneyTypeStr = strstr(szContent, GM_MONEY_TYPE_FLAG_STR);
		if (NULL == pMoneyTypeStr)
		{
			pData->bIsMoneyLog = FALSE;
		}
		else
		{
			pData->bIsMoneyLog = TRUE;
			pMoneyTypeStr += strlen(GM_MONEY_TYPE_FLAG_STR);
			pData->nMoneyType = atoi(pMoneyTypeStr);

			pRoleIDStr = strstr(szContent, GM_ROLE_FLAG_STR);
			if (NULL == pRoleIDStr)
			{
				pRoleIDStr = strstr(szContent, GM_ROLE_FLAG_STR2);
				LOG_PROCESS_ERROR(pRoleIDStr);
				pRoleIDStr += strlen(GM_ROLE_FLAG_STR2);
			}
			else
			{
				pRoleIDStr += strlen(GM_ROLE_FLAG_STR);
			}

			pData->nRoleID = atoi(pRoleIDStr);
			LOG_PROCESS_ERROR(pData->nRoleID > 0);

			pOldMoneyStr = strstr(szContent, GM_OLD_MONEY_FLAG_STR);
			pNewMoneyStr = strstr(szContent, GM_NEW_MONEY_FLAG_STR);
			LOG_PROCESS_ERROR(NULL != pOldMoneyStr && NULL != pNewMoneyStr);
			pOldMoneyStr += strlen(GM_OLD_MONEY_FLAG_STR);
			pNewMoneyStr += strlen(GM_NEW_MONEY_FLAG_STR);

			nOldMoney = atoi(pOldMoneyStr);
			nNewMoney = atoi(pNewMoneyStr);
			LOG_PROCESS_ERROR(nOldMoney >= 0 && nNewMoney >= 0);

			if (nNewMoney > nOldMoney)
			{
				pData->nAction = ACTION_ADD_MONEY;
				pData->nMoneyCount = nNewMoney - nOldMoney;
			}
			else if (nNewMoney <= nOldMoney)
			{
				pData->nAction = ACTION_SUB_MONEY;
				pData->nMoneyCount = nOldMoney - nNewMoney;
			}
		}

		READ_END(nID);
	}

};

struct  ROLE_LOGOUT_BASIC_DATA
{
	INT32 nRoleID;
	UINT32 dwTime;
	INT32 nMoney2;
	SimpleListNode oLogoutLogNode;

	static INT32 nID;
	static char szTime[20];

	SimpleListNode& GetSimpleListNode(void)
	{
		return oLogoutLogNode;
	}

	static ROLE_LOGOUT_BASIC_DATA* ParseSimpleListNode(SimpleListNode* pSimpleListNode)
	{
		ROLE_LOGOUT_BASIC_DATA* pResult = NULL;

		PROCESS_ERROR(pSimpleListNode);

		pResult = node_cast(ROLE_LOGOUT_BASIC_DATA*, GetSimpleListNode(), pSimpleListNode);
		LOG_PROCESS_ERROR(pResult);

		return pResult;
	Exit0:
		return NULL;
	}

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ROLE_LOGOUT_BASIC_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
	{
		FAST_READ_START();       

		FAST_READ_STR(0, szTime);
		pData->dwTime = (UINT32)CustomizedStr2Time(szTime);
		LOG_PROCESS_ERROR(0 != pData->dwTime);

		FAST_READ_INT(3, nRoleID);
		FAST_READ_INT(13, nMoney2);

		READ_END(nID);
	}
};

#pragma pack(pop)

class CRoleLogCheck
{
public:
	CRoleLogCheck(void);
	~CRoleLogCheck(void);

	static CRoleLogCheck& GetInstance(void);

	BOOL Init(void);
	BOOL UnInit(void);

	BOOL CheckParam(INT32 argc, char** argv);
	void ShowUsage();
	BOOL DoCheckLog(const char* pszDirectory, const char* pszDate1, const char* pszDirectory2, const char* pszDate2);

	inline MONEY_LOG_DATA* NewMoneyLogData(void);
	inline BOOL DelMoneyLogData(MONEY_LOG_DATA* poMoneyLogData);

	inline GM_LOG_DATA* NewGMLogData(void);
	inline BOOL DelGMLogData(GM_LOG_DATA* poGMLogData);

	inline ROLE_LOGOUT_BASIC_DATA* NewRoleLogoutBasicData(void);
	inline BOOL DelRoleLogoutBasicData(ROLE_LOGOUT_BASIC_DATA* poRoleLogoutBasicData);

private:
	BOOL _LoadMoneyLog(const char* pszFilePath, UINT8 byFileIndex);
	BOOL _LoadGMLog(const char* pszFilePath, UINT8 byFileIndex);
	BOOL _LoadBasicLog(const char* pszFilePath, UINT8 byFileIndex);
	BOOL _CheckLog();
	void _ReleaseLogCache();

private:
	static CRoleLogCheck  ms_Instance;

	typedef std::map<UINT8, std::string> MAP_INDEX_2_FILE_NAME;
	UINT8                                   m_byFileIndex;
	MAP_INDEX_2_FILE_NAME                   m_mapIndex2FileName;

	typedef std::map<UINT32, CSimpleList> MAP_ROLE_MONEY_LOG_DATA;
	MAP_ROLE_MONEY_LOG_DATA                 m_mapRoleMoneyLogData;
	MAP_ROLE_MONEY_LOG_DATA::iterator       m_mapRoleMoneyLogDataIter;

	typedef std::map<UINT32, CSimpleList> MAP_ROLE_GM_LOG_DATA;
	MAP_ROLE_GM_LOG_DATA                    m_mapRoleGMLogData;
	MAP_ROLE_GM_LOG_DATA::iterator          m_mapRoleGMLogDataIter;

	typedef std::map<UINT32, CSimpleList> MAP_ROLE_LOGOUT_BASIC_DATA;
	MAP_ROLE_LOGOUT_BASIC_DATA              m_mapRoleLogoutBasicData;
	MAP_ROLE_LOGOUT_BASIC_DATA::iterator    m_mapRoleLogoutBasicDataIter;

	CObjectPool<MONEY_LOG_DATA>             m_oMoneyLogDataPool;
	CObjectPool<GM_LOG_DATA>                m_oGMLogDataPool;
	CObjectPool<ROLE_LOGOUT_BASIC_DATA>     m_oRoleLogoutBasicDataPool;
};


inline MONEY_LOG_DATA* CRoleLogCheck::NewMoneyLogData(void)
{
	return m_oMoneyLogDataPool.New();

	//return new MONEY_LOG_DATA();
}

inline BOOL CRoleLogCheck::DelMoneyLogData(MONEY_LOG_DATA* poMoneyLogData)
{
	if (NULL == poMoneyLogData)
	{
		return TRUE;
	}

	return m_oMoneyLogDataPool.Delete(poMoneyLogData);

	//if (NULL != poMoneyLogData) delete poMoneyLogData;
	//return TRUE;
}

inline GM_LOG_DATA* CRoleLogCheck::NewGMLogData(void)
{
	return m_oGMLogDataPool.New();

	//return new GM_LOG_DATA();
}

inline BOOL CRoleLogCheck::DelGMLogData(GM_LOG_DATA* poGMLogData)
{
	if (NULL == poGMLogData)
	{
		return TRUE;
	}

	return m_oGMLogDataPool.Delete(poGMLogData);

	//if (NULL != poGMLogData) delete poGMLogData;
	//return TRUE;
}


inline ROLE_LOGOUT_BASIC_DATA* CRoleLogCheck::NewRoleLogoutBasicData(void)
{
	return m_oRoleLogoutBasicDataPool.New();

	//return new ROLE_LOGOUT_BASIC_DATA();
}

inline BOOL CRoleLogCheck::DelRoleLogoutBasicData(ROLE_LOGOUT_BASIC_DATA* poRoleLogoutBasicData)
{
	if (NULL == poRoleLogoutBasicData)
	{
		return TRUE;
	}

	return m_oRoleLogoutBasicDataPool.Delete(poRoleLogoutBasicData);

	//if (NULL != poRoleLogoutBasicData) delete poRoleLogoutBasicData;
	//return TRUE;
}

class COutput
{
public:
	COutput(void);
	~COutput(void);

	static COutput& GetInstance(void);

	void Cls(void);
	void Goto(SHORT x, SHORT y);
	void Printf(const char * _Format, ...);
	void PrintfLoadingProgress(INT32 nPercent);

private:
	static COutput  ms_Instance;
};

#endif // _ROLE_LOG_CHECK_H_
