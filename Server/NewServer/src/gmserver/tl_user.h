/********************************************************************
	created:	19:12:2013   14:46
	file:		tl_user.h
	author:		Allan Tao
	
	purpose:	tl user
*********************************************************************/

#ifndef _H_TL_USER_H_
#define _H_TL_USER_H_

#include "gm_def.h"
#include "gm_svr_def.h"

struct CMD_DATA_BASE;

class CTLUser
{

public:
    CTLUser();
    ~CTLUser();


    BOOL Init();
    BOOL UnInit();

    inline UINT32  GetID();
    inline void    SetID(UINT32 dwID);

    inline const char*GetUserName();
    inline void SetUserName(const char *pcszName);

    inline UINT32  GetSessionID();
    inline void    SetSessionID(UINT32 dwSessionID);

    inline BOOL     IsBusy();
    inline BOOL     SetBusy();
    inline BOOL     SetIdel();

    //inline INT32   GetState();
    //inline void    SetState(INT32 nState);

    inline UINT32  GetIP();
    inline void    SetIP(UINT32 dwIP);

    inline UINT16  GetPort();
    inline void    SetPort(UINT16 wPort);

    inline const char *GetComputerName();
    inline void    SetComputerName(const char *pcszName);

    inline GM_PERMISSION   GetPermission();
    inline void    SetPermission(GM_PERMISSION ePermission);

    inline void     SetLD();
    inline BOOL     IsLD();

    inline  BOOL   CanExecuteCmd();
    inline CMD_DATA_BASE*   GetCmd();
    inline void     SetCmd(CMD_DATA_BASE *pCmd);
    inline void     ClearCmd();

private:
    UINT32      m_dwUserID;
    UINT32      m_dwSessionID;
    INT32       m_nState;
    UINT32      m_dwIP;
    UINT16      m_wPort;
    char        m_szComputerName[128];
    char        m_szUserName[ROLE_NAME_LEN];
    BOOL        m_bLD;

    GM_PERMISSION   m_ePermission;

    CMD_DATA_BASE*  m_pCmd;


};



#include "tl_user_inl.h"




#endif //_H_TL_USER_H_


