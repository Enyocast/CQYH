#ifndef _IOCP_MGR_H_
#define _IOCP_MGR_H_

#include <map>
#include "circle_list.h"

#define IOCP_THREAD_COUNT   (32)

typedef std::map<std::string, UINT32> ERROR_MAP;

enum EWorkingMode
{
	wmInvalid = 0,
	wmExtractError,
	wmExtractNetworkFlow,

	wmTotal,
};

struct IOCP_TASK : OVERLAPPED
{
	char		szFilePath[MAX_PATH];
	HANDLE		hFile;
	UINT64		qwFileSize;
	char*		pFileData;
	ERROR_MAP*	pErrorMap;
	UINT64		dwSubmitTick;
	UINT64		dwCreateTick;
	UINT64		dwReadTick;
	UINT64		dwProcessTick;
	UINT64		dwFetchTick;
	INT32		eWorkingMode;
};

class CIocpMgr
{
public:
    CIocpMgr();
    ~CIocpMgr();

    BOOL Init(void);
    BOOL UnInit(void);
    static inline CIocpMgr& GetInstance(void);

    BOOL SubmitTask(IOCP_TASK* pTask);
    IOCP_TASK* FetchResult(void);
    INT32 GetUncompletedTaskCount(void);

    inline HANDLE GetIocpHandle(void);

private:
    static DWORD WINAPI _IocpThreadFunc(void* pParam);
    
private:
    static CIocpMgr ms_Instance;
    HANDLE          m_hIOCP;
    HANDLE          m_ThreadList[IOCP_THREAD_COUNT];
    CCircleList     m_ResultList[IOCP_THREAD_COUNT];
    INT32           m_nSubmitCount;
    INT32           m_nFetchCount;
};

inline CIocpMgr& CIocpMgr::GetInstance(void)
{
    return ms_Instance;
}

inline HANDLE CIocpMgr::GetIocpHandle(void)
{
    return m_hIOCP;
}

#endif  // _IOCP_MGR_H_