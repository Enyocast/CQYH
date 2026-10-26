#ifndef _CMD_MGR_H_
#define _CMD_MGR_H_

#define MAX_GUARD_CMD_COUNT (16)

class CCmdMgr
{
public:
    CCmdMgr();
    ~CCmdMgr();

    BOOL Init();
    BOOL UnInit(void);
	static CCmdMgr& GetInstance(void);
	BOOL PrintCmdDescribe();

	INT32 ExecGMCmd(const char* szFullCmd);
	INT32 ExecOPCmd(const char* szFullCmd);
private:
	BOOL ParseCmd(const char* szParam);

	BOOL QuitGuard(INT32 nCount, const char* pcszParam);
	BOOL StartServer(INT32 nCount, const char* pcszParam);
	BOOL StopServer(INT32 nCount, const char* pcszParam);
	BOOL CloseServer(INT32 nCount, const char* pcszParam);
	BOOL CheckServerConfig(INT32 nCount, const char* pcszParam);
	BOOL ReloadServerConfig(INT32 nCount, const char* pcszParam);

private:
    static CCmdMgr  ms_Instance;

    typedef BOOL (CCmdMgr::*CMD_FUNC)(INT32 nCount, const char* pcszParam);
    struct SGuardCommand
    {
        char        szCommandName[32];
        CMD_FUNC    pProc; 
    };

    SGuardCommand   m_CmdFuncList[MAX_GUARD_CMD_COUNT];

    CMD_FUNC        m_szCmdProc;
    INT32           m_szParamCount;
    char            m_szCmdParam[256];

    BOOL            m_bNeedPrintCmdDes;
};


#endif  // _CMD_MGR_H_