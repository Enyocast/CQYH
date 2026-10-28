/********************************************************************
	created:	4:12:2013   15:29
	file:		cmd_manager.h
	author:		Allan Tao
	
	purpose:	命令管理器 UI层和逻辑层交互
*********************************************************************/

#ifndef _H_CMD_MANAGER_H_
#define _H_CMD_MANAGER_H_


#include <list>
//#include "object_pool.h"
#include "predefine.h"
#include "cmd_data.h"





class CCmdManager
{
public:
    static CCmdManager &GetInstance();

protected:
    static CCmdManager     m_Instance;

    CCmdManager();
    ~CCmdManager();

public:

    BOOL    Init();
    BOOL    UnInit();
    BOOL    MainLoop();

    BOOL        Success(CMD_BASE *pCmd);
    BOOL        Washout(CMD_BASE *pCmd);

    CMD_BASE*   NewCmd(INT32 nType);
    BOOL        DelCmd(CMD_BASE *pCmd);

    BOOL        AddSvr(UINT32 dwSvrID);
    void        ClearSvrList()           { m_PreExecuteSvrList.clear(); }
    UINT32      GetSvrNum()                 { return m_PreExecuteSvrList.size(); }
    UINT32      First();
    UINT32      Next();

    BOOL        IsCompleteAll();

    INT32       GetResult()     { return m_nResult; }
    void        SetResult(INT32 nResult)     { m_nResult = nResult; }

public:
    BOOL        PreQuery(INT32 nCmdType, const char *pcszRoleName, CMD_BASE *pCmd);
    BOOL        QueryRoleID(INT32 nType, const char *pcszName);
    BOOL        QueryRoleData(CMD_BASE *pCmd);
    BOOL        ForbidChat(CMD_BASE *pCmd);
    BOOL        FreezeRole(CMD_BASE *pCmd);
    BOOL        KickRole(CMD_BASE *pCmd);
    BOOL        SendMail(CMD_BASE *pCmd);
    BOOL        SendAnnounce(INT32 nGroupID, UINT32 dwBeginTime, INT32 nIntervalTime, INT32 nRepeatNum, const char *pcszAnnounce);
    BOOL        QueryAnnounceList(INT32 nGroupID);
    BOOL        DelAnnounce(INT32 nGroupID, INT32 nAnnounceSerial);
    BOOL        QueryNameToID(std::map<INT32, ROLE_NAME_DATA> &map);
    BOOL        SendGMStrCmd(const char *pcszCmdStr);

    BOOL        LoadRoleData(CMD_BASE *pCmd);
    BOOL        ModifyRole(UINT32 dwRoleID, UINT32 dwTargetRoleID, INT32 nLength, const char *pcszData, const char *pcszReason);

    BOOL        ExeRoleGMCmd(CMD_BASE *pCmd);


    // log
    BOOL        QueryLog(INT32 nLogType, UINT32 dwBeginTime, UINT32 dwEndTime, const char *pcszQueryStr);


    // cmd 
    CMD_BASE*   GetCurrentCmd()     { return m_pCmd; }
    BOOL        SetExeServerNum(INT32 nSvrNum);
    BOOL        IsCmdExecuting(BOOL isModifyRoleCmd = FALSE);
    void        CmdEnd();


private:
    INT32           m_nState;
    INT32           m_nResult;
    BOOL            m_IsCmdComplete;

    CMD_BASE    *m_pCmd;

    typedef     std::list<UINT32>        SVR_LIST;
    SVR_LIST::iterator      m_Cursor;
    SVR_LIST    m_PreExecuteSvrList;
};




#endif //_H_CMD_MANAGER_H_



