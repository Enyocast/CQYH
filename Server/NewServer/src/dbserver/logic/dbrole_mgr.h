#ifndef _DBROLE_MGR_H_
#define _DBROLE_MGR_H_

#include "base_list.h"

class CDBRole;

class CDBRoleMgr
{
public:
    CDBRoleMgr();
    ~CDBRoleMgr();

    BOOL Init(UINT32 dwRoleCount);
    BOOL UnInit();

    BOOL AddDBRole(CDBRole* dbrole);
    BOOL DelDBRole(CDBRole* dbrole);
    CDBRole* GetDBRoleByID(UINT32 dwRoleID);

    CDBRole* Pop(void);             //申请一个空闲的DBRole对象，主线程调用
    BOOL Pop(CDBRole* dbrole);      //申请一个指定的DBRole对象，主线程调用
    BOOL Push(CDBRole* dbrole);     //归还一个用完的DBRole对象，主线程调用

private:
    CBaseList m_freerolelist;
    typedef std::map<UINT32, CDBRole*> ROLEMAP;
    ROLEMAP m_rolemap;
};


#endif // _DBROLE_MGR_H_
