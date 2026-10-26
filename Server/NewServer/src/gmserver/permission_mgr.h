/********************************************************************
	created:	17:12:2013   18:11
	file:		permission_mgr.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_PERMISSION_MGR_H_
#define _H_PERMISSION_MGR_H_

#include <map>
#include <string>

enum GM_COMMAND;

class CPermissionMgr
{
public:
    static  CPermissionMgr  &GetInstance();
protected:
    static CPermissionMgr       m_Instance;

    CPermissionMgr();
    ~CPermissionMgr();

public:
    BOOL    Init();
    BOOL    UnInit();

    BOOL    CheckIP(UINT32 dwIP);
    INT32   GetUserPermission(const char *pcszName, const char *pcszPwd);
    UINT32  GetUserID(const char *pcszName, const char *pcszPwd);
    BOOL    IsLD(const char *pcszName, const char *pcszPwd);

    BOOL    CheckExecutePermission(GM_COMMAND eCmd, INT32 nTLUserPermission);

protected:
    INT32   _GetCmdPermission(GM_COMMAND eCmd);


private:
    CLuaScript      m_LuaScript;
    UINT64          m_qwReloadGlobalConfigTime;


};




#endif //_H_PERMISSION_MGR_H_


