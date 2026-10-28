#ifndef _DBUSER_MGR_H_
#define _DBUSER_MGR_H_

#include "base_list.h"
#include "string_def.h"
#include "server_def.h"

class CDBUser;

class CDBUserMgr
{
public:
    CDBUserMgr();
    ~CDBUserMgr();

    BOOL Init(UINT32 dwUserCount);
    BOOL UnInit();

    BOOL AddToUserNameMap(CDBUser* dbuser);
    BOOL DelFromUserNameMap(CDBUser* dbuser);
    CDBUser* GetDBUserByName(const char* pcszUserName, INT32 nGroupID);

    BOOL AddToSessionIDMap(CDBUser* dbuser);
    BOOL DelFromSessionIDMap(CDBUser* dbuser);
    CDBUser* GetDBUserBySessionID(UINT32 dwSessionID);

    CDBUser* Pop();                  //Acquire a free DBUser object; called by the main thread
    BOOL Pop(CDBUser* dbuser);       //Acquire a specified DBRole object; called by the main thread
    void Push(CDBUser* dbuser);      //Return a used DBUser object; called by the main thread

private:

    CBaseList m_freeuserlist;
    
    struct ltstr
    {
        bool operator()(const CHAR* s1, const CHAR* s2) const
        {
            return strncmp(s1, s2, USER_NAME_LEN) < 0;
        }
    };
    typedef std::map<const char*, CDBUser*, ltstr> USERNAMEMAP;
    typedef USERNAMEMAP::iterator  USERNAMEMAP_ITR;
    
    USERNAMEMAP m_usernamemap[MAX_SERVER_GROUP_COUNT];
    typedef std::map<UINT32, CDBUser*> SESSIONIDMAP;
    SESSIONIDMAP m_sessionidmap;
};


#endif // _DBUSER_MGR_H_
