#ifndef _DBUSER_H_
#define _DBUSER_H_

#include "role_def.h"
#include "role_db_def.h"
#include "base_list.h"
#include "string_def.h"

class CDBRole;

#define USER_KEY_STRING "%02d_%s^%s"

class CDBUser : public BASE_LIST_NODE
{
public:
    CDBUser();
    ~CDBUser();

    char m_szUserName[USER_NAME_LEN];

    UINT8 m_byRoleCount;
    UINT32 m_dwRoleID[MAX_ROLE_PER_USER];
    ROLE_DB_BASE_DATA m_BaseData[MAX_ROLE_PER_USER];
    BOOL m_bRoleListCached;
    CDBRole* m_pDBRole[MAX_ROLE_PER_USER];

    CDBRole* m_pPlayingRole;

    void OnListRole();
    BOOL RemoveRole(CDBRole* pRole, BOOL bDelete);
    BOOL RemoveAllRoles();

    enum DB_USER_STATE
    {
        dusInvalid, 

        dusLogout,
        dusAuthed,
        dusPlaying,

        dusTotal
    };
    DB_USER_STATE m_state;

    enum DB_TASK_STATE
    {
        dtsInvalid,
        dtsFree,
        dtsListing,
        dtsLoading,
        dtsCreating,
        dtsUpdatingRoleDeleteTime,
        dtsDeleting,

        dtsTotal
    };
    DB_TASK_STATE m_dbstate;

    BOOL	m_nResult;
    UINT32	m_dwClientSessionID;
	INT32	m_nServerGroup;
};


#endif // _DBUSER_H_
