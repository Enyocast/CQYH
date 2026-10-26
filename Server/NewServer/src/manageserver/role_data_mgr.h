#ifndef _ROLE_DATA_MGR_H_
#define _ROLE_DATA_MGR_H_

#include "id_object_pool.h"
#include "role_data.h"

#define ROLE_NAME_HASH_TABLE_SIZE   (1024 * 64)

class CRoleDataMgr
{
public:
    CRoleDataMgr();
    ~CRoleDataMgr();

    BOOL Init(void);
    BOOL UnInit(void);
    static CRoleDataMgr& GetInstance(void);

    MS_ROLE_DATA* CreateRole(UINT32 dwRoleID, const char* pcszRoleName);
    MS_ROLE_DATA* FindRole(UINT32 dwRoleID);
    MS_ROLE_DATA* FindRoleByName(const char* pcszRoleName);
    BOOL DestroyRole(MS_ROLE_DATA* pRoleData);

    void CheckFence(void) {m_RoleDataPool.CheckFence();}

private:
    static BOOL _Load(std::list<void*>& rResult, void* pUserData);
    static BOOL _LoadGM(std::list<void*>& rResult, void* pUserData);

    BOOL _LoadRole(UINT32 dwRoleID,
        char* szRoleName,
        char* szUserName,
        UINT32 dwLoginTime,
		UINT8 byServerGroup,
        UINT32 dwBaseDataBufferLen,
        char* BaseDataBuffer);

    inline UINT16 _GetHashValue(ROLE_NAME_KEY& rRoleNameKey);

    struct CDeleteAllRole
    {
        bool operator()(UINT32 dwRoleID, MS_ROLE_DATA* pRoleData);
    };

    struct CTestRoleName
    {
        bool operator()(UINT32 dwRoleID, MS_ROLE_DATA* pRoleData);
    };

    static CRoleDataMgr ms_Instance;

    CIDObjectPool<MS_ROLE_DATA, UINT32> m_RoleDataPool;
    LM_MAP_NODE<ROLE_NAME_KEY>*         m_pRoot[ROLE_NAME_HASH_TABLE_SIZE];
    INT32 m_nLoadedCount;
};

#endif  // _ROLE_DATA_MGR_H_