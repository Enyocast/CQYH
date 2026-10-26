/********************************************************************
	created:	19:12:2013   15:46
	file:		kernel.h
	author:		Allan Tao
	
	purpose:	control how to exe cmd
*********************************************************************/

#ifndef _H_KERNEL_H_
#define _H_KERNEL_H_

#include "gm_def.h"
#include "server_def.h"

struct CMD_DATA_BASE;

class CKernel
{
protected:
    CKernel();
    ~CKernel();

    static CKernel  m_Instance;

public:
    static  CKernel&    GetInstance();

public:
    BOOL            PushCmd(CMD_DATA_BASE *pCmd);
    BOOL            PopCmd(CMD_DATA_BASE *pCmd);
    CMD_DATA_BASE   *FindCmd(UINT32 dwSerialID);

    BOOL            MainLoop();


    //INT32   ExecuteBegin(CMD_DATA_TEMP_BASE *pCmd);
    //BOOL    ExecuteEnd(CMD_DATA_TEMP_BASE *pCmd);

    //BOOL    PreLockRole(UINT32 dwTLUserID, CMD_DATA_TEMP_BASE *pCmd);
    //BOOL    LockRole(CMD_DATA_TEMP_BASE *pCmd);

    //BOOL    PreUnlockRole(UINT32 dwTLUserID, CMD_DATA_TEMP_BASE *pCmd);
    //BOOL    UnlockRole(CMD_DATA_TEMP_BASE *pCmd);


    //INT32   DispatchCmd(CMD_DATA_TEMP_BASE *pCmd);
    //INT32   DispatchMSCmd(CMD_DATA_TEMP_BASE *pCmd);




private:

    //CMD_DATA_TEMP_BASE*        m_LockRoleCmdList[MAX_GM_TL_SESSION_COUNT];

    typedef     std::list<CMD_DATA_BASE*>   CMD_LIST;
    CMD_LIST        m_CmdList;

    INT32           m_nTicket;

};












#endif //_H_KERNEL_H_




