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

    CCircleList m_MemList;      //所有用过的内存列表
    DB_ROLE_DATA* m_pCurMem;    //当前有效的内存
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
        LOCK_STATE_INVALID,                 //无有效数据，默认状态，创建角色前，创建角色失败后，属于此状态
        LOCK_STATE_UNLOCKED,                //含有效数据，创建角色成功后，上锁前/解锁后，属于此状态
        LOCK_STATE_LOCKING,                 //正在上锁，包括从数据库中读取数据也属于这一状态
        LOCK_STATE_LOCKED,                  //已上锁，角色正在游戏中
        LOCK_STATE_UNLOCKING,               //正在解锁
        LOCK_STATE_LOCKING_AND_UNLOCKING,   //正在上锁时遭遇解锁请求
        LOCK_STATE_UNLOCKING_AND_LOCKING    //正在解锁时遭遇上锁请求
    };
    LOCK_STATE m_lockstate;

    //以下数据用于读取完成后发送回包
    INT32 m_nResult;                //数据库操作结果成功或失败
    UINT32 m_dwGSSessionID;         //请求数据的服务器的session id，用于发送回复

    //以下数据用于创建新角色
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

    //以下数据用于工作线程存盘时排序
    UINT64 m_qwLastSaveTime;

    CDBUser* m_dbuser;
};


#endif // _DBROLE_H_
