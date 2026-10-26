/********************************************************************
	created:	24:12:2013   14:53
	file:		gm_role_mgr.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_GM_ROLE_MGR_H_
#define _H_GM_ROLE_MGR_H_


struct GM_LOCK_DATA 
{
    UINT32      dwRoleID;
    UINT32      dwTLUserID;
};

class CGMRoleMgr
{
protected:
    CGMRoleMgr();
    ~CGMRoleMgr();

    static CGMRoleMgr   m_Instance;


public:
    static CGMRoleMgr&     GetInstance();

public:
    BOOL Init();
    BOOL UnInit();

    BOOL CheckRoleExist(UINT32 dwRoleID);
    BOOL CheckRoleLock(UINT32 dwRoleID, UINT32 dwTLUserID);
    BOOL AddRole(UINT32 dwRoleID, UINT32 dwTLUserID);           // 跨cmd的锁定，防止其他TL操作
    BOOL DelRole(UINT32 dwRoleID, UINT32 dwTLUserID);
    BOOL DelRoleByUserID(UINT32 dwTLUserID);

private:
    typedef std::map<UINT32, GM_LOCK_DATA>    ROLE_MAP;
    ROLE_MAP        m_RoleMap;

};













#endif //_H_GM_ROLE_MGR_H_
