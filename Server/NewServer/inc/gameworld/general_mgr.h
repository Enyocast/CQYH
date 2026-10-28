//////////////////////////////////////////////////////////////////////////
//  Allan Tao[10.10.2014] 
// General data storage for asimov
// 1. Store data for performance cases: randomly select a character on this server
//////////////////////////////////////////////////////////////////////////

#ifndef _H_GENERAL_MGR_H_
#define _H_GENERAL_MGR_H_

#ifdef _ROBOT

#include "string_def.h"
struct RAND_ROLE_DATA
{
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
};

class CGeneralMgr
{
protected:
    CGeneralMgr();
    ~CGeneralMgr();

public:
    static CGeneralMgr     m_Instance;
    static CGeneralMgr&     GetInstance();

    BOOL    Init();
    BOOL    UnInit();

    // rand user
    BOOL    IsValidRandRoleExist();
    RAND_ROLE_DATA* GetRandRole(UINT32 dwRoleID);
    void AddRandRole(UINT32 dwRoleID, const char *pcszName);

    const char* GetRandomGuild();

private:



    ///////////////////////// rand user //////////////////////////////////////
#define MAX_RAND_USER_NUM (128)
    INT32               m_nRandRoleNum;
    RAND_ROLE_DATA      m_arrRandRole[MAX_RAND_USER_NUM];
    ////////////////////// rand user end /////////////////////////////////////
};

#endif //_ROBOT





#endif //_H_GENERAL_MGR_H_





