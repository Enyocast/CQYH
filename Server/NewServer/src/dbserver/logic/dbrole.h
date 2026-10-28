#ifndef _DBROLE_H_
#define _DBROLE_H_

#include "circle_list.h"
#include "base_list.h"
#include "string_def.h"
#include "role_db_def.h"

struct DB_ROLE_DATA;

class CDBUser;

class CDBRole : public BASE_LIST_NODE
{
public:
    CDBRole();
    ~CDBRole();

    BOOL SaveData(const char* data, UINT32 len);
    BOOL LoadData();

    void OnCreateRole();
    void OnUpdateRoleDeleteTime();
    void OnDeleteRole();
    void OnLoadRole();
    void SendCreateAck();

    ROLE_DB_BASE_DATA* RefreshBaseData();

    UINT32 m_dwRoleID;
    UINT32 m_dwDeleteTime;

    CCircleList m_MemList;      //List of all previously used memory
    DB_ROLE_DATA* m_pCurMem;    //Currently active memory
    BOOL ClearCache(BOOL include_current);

    enum DB_TASK
    {
        DB_TASK_INVALID,
        DB_TASK_LOAD_ROLE,
        DB_TASK_CREATE_ROLE,
        DB_TASK_UPDATE_ROLE_DELETE_TIME,
        DB_TASK_UPDATE_ROLE_DELETE_TIME_WITHOUT_DATA,
        DB_TASK_DELETE_ROLE,
        DB_TASK_DELETE_ROLE_WITHOUT_DATA,
        DB_TASK_FREE
    };
    DB_TASK m_dbtask;

    enum LOCK_STATE
    {
        LOCK_STATE_INVALID,                 //No valid data: default state before character creation or after a creation failure
        LOCK_STATE_UNLOCKED,                //Contains valid data: state after character creation and before locking or after unlocking
        LOCK_STATE_LOCKING,                 //Locking in progress, including reading data from the database
        LOCK_STATE_LOCKED,                  //Locked; character is in the game
        LOCK_STATE_UNLOCKING,               //Unlocking in progress
        LOCK_STATE_LOCKING_AND_UNLOCKING,   //Unlock requested while locking
        LOCK_STATE_UNLOCKING_AND_LOCKING    //Lock requested while unlocking
    };
    LOCK_STATE m_lockstate;

    //The following data is used to send a reply after reading completes
    INT32 m_nResult;                //Database operation result: success or failure
    UINT32 m_dwGSSessionID;         //Session ID of the server requesting the data, used for the reply

    //The following data is used to create a character
    struct CreateRoleParam
    {
        CHAR szUserName[USER_NAME_LEN];
        CHAR szRoleName[ROLE_NAME_LEN];
        UINT8 byClass;
        UINT8 bySex;
        UINT8 byHairType;
        UINT8 byHairColor;
        UINT8 byFaceType;
        UINT8 bySkinColor;
    };
    CreateRoleParam m_CreateRoleParam;

    //The following data is used for sorting when the worker thread saves
    UINT64 m_qwLastSaveTime;

    CDBUser* m_dbuser;
};


#endif // _DBROLE_H_
