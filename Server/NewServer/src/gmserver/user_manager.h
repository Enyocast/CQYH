/********************************************************************
	created:	3:12:2013   17:05
	file:		tl_manager.h
	author:		Allan Tao
	
	purpose:	gm tool manager
*********************************************************************/

#ifndef _H_TL_MANAGER_H_
#define _H_TL_MANAGER_H_

#include "server_def.h"
#include "tl_user.h"
#include "id_object_pool.h"

class CUserManager
{
public:
    static  CUserManager  &GetInstance();
protected:
    static CUserManager       m_Instance;

    CUserManager();
    ~CUserManager();

public:
    BOOL    Init();
    BOOL    UnInit();

    INT32   LoginUser(UINT32 dwTLSessionID, UINT32 dwIP, const char *pcszName, const char *pcszPwd);
    BOOL    LogoutUser(UINT32 dwTLUserID);

    CTLUser* FindUserByID(UINT32 dwTLUserID) { return m_UserPool.Find(dwTLUserID); }

    INT32   GetLDNum()      { return m_nLDNum; }
    CTLUser*GetLD(INT32 nIndex)     { LOG_PROCESS_ERROR(nIndex < m_nLDNum); return m_LDUserList[nIndex]; Exit0: return NULL; }

protected:
    BOOL    _IsExistLD(CTLUser *pTLUser);
    void    _AddLDUser(CTLUser *pTLUser);
    void    _DelLDUser(CTLUser *pTLUser);

private:
    INT32       m_nLDNum;
    CTLUser*    m_LDUserList[MAX_GM_USER];

    CIDObjectPool<CTLUser, UINT32>      m_UserPool;
};








#endif //_H_TL_MANAGER_H_


