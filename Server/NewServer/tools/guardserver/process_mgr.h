#ifndef _PROCESS_MGR_H_
#define _PROCESS_MGR_H_

#include <list>
#include "server_def.h"

struct SProcessInfo
{
	UINT8 byType;
	UINT8 bySessionID;
	UINT8 bAuto; // mode or manual
    UINT32 dwProcessID;
    UINT32 dwIP;
	FILETIME ftProcessCreationTime;
};

class CProcessMgr
{
public:
    CProcessMgr();
    ~CProcessMgr();

    BOOL Init();
    BOOL UnInit(void);
    static CProcessMgr& GetInstance(void);

	BOOL StartProcess(UINT8 byType, char* szCmdLine, BOOL bView = FALSE, BOOL bRunRelease = FALSE, BOOL bAuto = FALSE);
    BOOL CloseProcess(UINT8 byType);
    
    BOOL StartAllProcess(char* szCmdLine, BOOL bView = FALSE, BOOL bRunRelease = FALSE);
    BOOL CloseAllProcess();

    INT32 CountRuningProcessByType(UINT8 byType);
    BOOL IsProcessRuningByID(UINT32 dwProcessID);
	BOOL MainLoop();
	BOOL AddProcessInfo(UINT8 byType, UINT32 dwProcessID, UINT32 dwIP, BOOL bAuto);
	BOOL SetProcessInfo(UINT32 dwProcessID, UINT8 byType, UINT8 bySessionID);
	
	BOOL SyncProcessInfo(UINT32 nState, UINT32 dwProcessID);
	BOOL SyncAllProcessInfo();
	
	typedef std::list<SProcessInfo>           CSprocessList;
	typedef CSprocessList::iterator           CSprocessListItr;
	CSprocessList& GetProcesses()	{ return m_listProcess; }

private:
	BOOL UpdateServersInfo();
	BOOL UpdateServersStatis(UINT32 dwProcessID);

    static CProcessMgr                        ms_Instance;
	UINT64									  m_qwLastStatisTick;

    CSprocessList                             m_listProcess;	// todo: map PID -> SProcessInfo
};

#endif  // _PROCESS_MGR_H_