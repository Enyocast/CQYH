/********************************************************************
	created:	19:12:2013   15:34
	file:		cmd_mgr.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_CMD_MGR_H_
#define _H_CMD_MGR_H_

#include "gm_def.h"
#include "gm_svr_def.h"

class CTLUser;
struct CMD_DATA_BASE;

BOOL EchoTLError(UINT32 dwTLSessionID, const char *pcszErrorStr, ...);

#define LOG_ECHO_ERROR(condition, SessionID, ErrorStr, ...)							\
	do																\
                        	{																\
		if (!(condition))										\
                                                		{															\
                        EchoTLError(SessionID, ErrorStr, ##__VA_ARGS__);   \
            ERR("LOG_PROCESS_ERROR("#condition") at line %d in function %s() file \"%s\"", \
                __LINE__, __FUNCTION__, __FILE__);                  \
			goto Exit0;												\
                                                		}															\
                        	} while (0)

class CCmdMgr
{
protected:
    CCmdMgr();
    ~CCmdMgr();

    static CCmdMgr  m_Instance;

public:
    static  CCmdMgr&    GetInstance();

    BOOL    Init();
    BOOL    UnInit();


public:
    CMD_DATA_BASE   *NewCmd(GM_COMMAND eCmd);
    void    DeleteCmd(CMD_DATA_BASE *pCmd);

    //BOOL    CheckExecutePermission(CTLUser *pTLUser, GM_COMMAND eCmd);




public:
    //INT32   CmdGetRoleList(CMD_DATA_TEMP_BASE *pCmd);
    //INT32   CmdViewRoleData(CMD_DATA_TEMP_BASE *pCmd);
    //INT32   CmdLoadRoleData(CMD_DATA_TEMP_BASE *pCmd);

    //INT32   CmdForbidChat(CMD_DATA_TEMP_BASE *pCmd);
    //INT32   CmdFreezeRole(CMD_DATA_TEMP_BASE *pCmd);


    //BOOL    CmdSearchItemLog(CMD_DATA_TEMP_BASE *pCmd);
    //
    //BOOL    CmdSaveRoleData(CMD_DATA_TEMP_BASE *pCmd);


private:

    UINT32      m_SerialID;



};

class CRoleNameParse
{
public:
    CRoleNameParse();
    ~CRoleNameParse();

    BOOL Init();
    BOOL Uninit();


    BOOL    AddNameList(const char *pBuffer, UINT32 dwLength);

    const char *FirstName();
    const char *NextName();


private:
    UINT32      m_dwCursor;
    UINT32      m_dwCount;
    char        m_szRoleName[MAX_GET_ROLE_LIST_NAME_NUM][ROLE_NAME_LEN];




};


BOOL CB_PreQueryRoleID(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_QueryRoleID(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_QueryRoleData(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_ForbiddenChat(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_FreezeRole(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_KickRole(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_SendMail(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_Announce(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_GetAnnounceList(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_DelAnnounce(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_Log(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_ExeGMStr(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_LoadRoleData(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_ModifyRoleData(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);
BOOL CB_RoleExeCmd(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);

BOOL CB_QueryNameToID(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);

// exchange
BOOL CB_QuerySysExchangeInfo(CTLUser *pTLUser, CMD_DATA_BASE *pCmd);


#endif //_H_CMD_MGR_H_








