/********************************************************************
	created:	5:8:2013   15:26
	file:		gm_manager.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GM_MANAGER_H_
#define _H_GM_MANAGER_H_

//#include "sdthread.h"
#include "packet_allocator.h"
#include "predefine.h"
#include <list>
#include "string_def.h"
//#include "message_notifier.h"


class gmtool;
class loader;


struct ROLE_DATA 
{
    INT32   nSvrID;
    //CRole   *poRole;

    ROLE_DATA(INT32 svrID):
    nSvrID(svrID)
    {

    }
};

BOOL IsRoleDataEqual(ROLE_DATA &data1, ROLE_DATA &data2);

struct SERVER_DATA 
{
    BOOL        byIsLogin;
    UINT32      dwSessionID;
};



class CGMManager
{
protected:
    CGMManager();
    virtual ~CGMManager();

    static CGMManager   m_Instance;
public:
    static CGMManager &GetInstance();

    BOOL Init();
    BOOL UnInit();

    BOOL MainLoop();

    gmtool          *GetGMToolDialog();

    void    SetGMDialogState(GM_DIALOG_STATE nGMDialogState);
    GM_DIALOG_STATE   GetGMDialogState();

    const char *GetUserName();
    const char *GetUserPwd();
    void    SetUserName(const char *pcszName);
    void    SetUserPwd(const char *pcszPwd);



protected:
    //BOOL    _CheckGMConfig();

    
    CPacketAllocator    m_PacketAllocator;
    //CMessageNotifier    m_Notifier;
    INet                *m_pNet;

    char        m_szUserName[ROLE_NAME_LEN];
    char        m_szUserPwd[GM_TOOL_PASSWORD_LEN];

    GM_DIALOG_STATE       m_eGMDialogState;

    struct RELOGIN_DATA
    {
        INT32   nSvrID;
        INT32   nReloginTime;
    };
    typedef std::list<INT32>    SVRID_LIST;
    typedef std::list<RELOGIN_DATA>   RELOGIN_DATA_LIST;

    SVRID_LIST          m_PreloginList;
    SVRID_LIST          m_LoginList;
    SVRID_LIST::iterator    m_LoginListIter;
    RELOGIN_DATA_LIST   m_ReloginList;

    //////////////////////////////////////////////////////////////////////////

    SVRID_LIST          m_PreExecuteList;
    SVRID_LIST::iterator    m_PreExecuteListIter;

    typedef std::list<ROLE_DATA>    ROLE_LIST;
    ROLE_LIST           m_PreExecuteRoleList;
    //////////////////////////////////////////////////////////////////////////
    


};










#endif//_H_GM_MANAGER_H_














