#ifndef ACCOUNT_LOGOUT
#define ACCOUNT_LOGOUT

#include "stdafx.h"
#include "object_pool.h"
#include "base_list.h"

#define USER_NAME_LEN			(64)
#define MAX_DB_FILE_LEN			(64)
#define MAX_DB_FILE_NAME_LEN	(64)
#define MAX_READLINE_LEN		(1024)
#define DB_FILE_PATH			".//account_logout//db_file"
#define DL_FILE_NAME			"/AccountLogin_2014_08_22"

struct SESSION_2_USERNAME_NODE : BASE_LIST_NODE
{
	UINT32	dwSessionID;
	char	szName[USER_NAME_LEN];
};

class CAccountLogout
{
public:
	CAccountLogout();
	~CAccountLogout();

	static CAccountLogout& GetInstance(void);

	INT32 Init();
	INT32 Uninit();
	BOOL  MainLoop(void);

	UINT32 HextoDec(char* pstring);
	void DeleteSpace(char* pstring);

private:
	static CAccountLogout ms_Instance;
	FILE*  m_pFile;
	CObjectPool<SESSION_2_USERNAME_NODE> m_Session2UserNamePool;
	CBaseList m_Session2UserNameList;

	CObjectPool<SESSION_2_USERNAME_NODE> m_ActualLogoutSessionPool;
	CBaseList m_ActualLogoutSessionList;
};

#endif // !ACCOUNT_LOGOUT
