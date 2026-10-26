#ifndef __ONLINE_ROLE_DATA_MGR_H_
#define __ONLINE_ROLE_DATA_MGR_H_

#include "server_def.h"

#include "online_role_data.h"
#include "id_object_pool.h"
#include <map>

struct MS_USER;
struct SCENE_INFO;
class COnlineRoleDataMgr
{
public:
    COnlineRoleDataMgr();
    virtual ~COnlineRoleDataMgr();

    BOOL        Init(UINT32 dwMaxOnlineRole);
    BOOL        UnInit(void);
    static COnlineRoleDataMgr& GetInstance(void);

    MS_ONLINE_ROLE_DATA*    NewOnlineRole(MS_USER* poUser);
    BOOL                    DelOnlineRole(MS_ONLINE_ROLE_DATA* poRoleData);

    BOOL                    PreEnterScene(MS_ONLINE_ROLE_DATA* pstRoleData, SCENE_INFO* pstSceneInfo);
    BOOL                    EnterScene(MS_ONLINE_ROLE_DATA* pstRoleData, SCENE_INFO* pstSceneInfo);
    BOOL                    LeaveScene(MS_ONLINE_ROLE_DATA* pstRoleData, INT32 nSceneTempID, INT32 nSceneID, BOOL bNormalLeave);

	MS_ONLINE_ROLE_DATA*    FindOnlineRoleByName(const char* pcszRoleName);
    MS_ONLINE_ROLE_DATA*    FindOnlineRoleByRoleID(UINT32 dwRoleID);

    MS_ONLINE_ROLE_DATA*    FindOnlineRoleByNameInGroup(const char* pcszRoleName, UINT8 byGroupID);
    MS_ONLINE_ROLE_DATA*    FindOnlineRoleByRoleIDInGroup(UINT32 dwRoleID, UINT8 byGroupID);

	UINT32					GetRoleNumberCount(UINT8 byGroupIndex);
    UINT32					GetRoleNumberCount(void);

    template<class TFunc>
    inline BOOL TraverseOnlineRole(TFunc& rFunc);

    template<class TFunc>
    inline BOOL TraverseOnlineRoleInGroup(TFunc& rFunc, UINT8 byGroupID);

private:
    static COnlineRoleDataMgr                                     ms_Instance;
    CIDObjectPool<MS_ONLINE_ROLE_DATA, UINT32>                    m_oOnlineRolePool;

    struct ltstr
    {
        bool operator()(const CHAR* s1, const CHAR* s2) const
        {
            return strncmp(s1, s2, ROLE_NAME_LEN) < 0;
        }
    };
    typedef std::map<const char*, MS_ONLINE_ROLE_DATA*, ltstr>    CName2RoleDataMap;
    typedef CName2RoleDataMap::iterator                           CName2RoleDataMapItr;

    typedef std::map<UINT32, MS_ONLINE_ROLE_DATA*>                CID2RoleDataMap;
    typedef CID2RoleDataMap::iterator                             CID2RoleDataMapItr;

    CID2RoleDataMap       m_mapID2RoleData[MAX_SERVER_GROUP_COUNT];
    CName2RoleDataMap     m_mapName2RoleData[MAX_SERVER_GROUP_COUNT];
};

template<class TFunc>
inline BOOL COnlineRoleDataMgr::TraverseOnlineRole(TFunc& rFunc)
{
    return m_oOnlineRolePool.Traverse(rFunc);
}

template<class TFunc>
inline BOOL COnlineRoleDataMgr::TraverseOnlineRoleInGroup(TFunc& rFunc, UINT8 byGroupID)
{
    INT32 nRetCode = 0;
    LOG_PROCESS_ERROR(byGroupID < MAX_SERVER_GROUP_COUNT);

    for(CID2RoleDataMapItr itr = m_mapID2RoleData[byGroupID].begin(); itr != m_mapID2RoleData[byGroupID].end(); ++itr)
    {
        nRetCode = rFunc(itr->first, itr->second);
        PROCESS_ERROR(nRetCode);
    }

    return TRUE;
Exit0:
    return FALSE;
}

#endif 


