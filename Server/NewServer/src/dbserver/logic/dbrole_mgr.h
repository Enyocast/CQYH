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

    CDBRole* Pop(void);             //Acquire a free DBRole object; called by the main thread
    BOOL Pop(CDBRole* dbrole);      //Acquire a specified DBRole object; called by the main thread
    BOOL Push(CDBRole* dbrole);     //Return a used DBRole object; called by the main thread

private:
    CBaseList m_freerolelist;
    typedef std::map<UINT32, CDBRole*> ROLEMAP;
    ROLEMAP m_rolemap;
};


#endif // _DBROLE_MGR_H_
