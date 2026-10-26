#ifndef _GS_INFO_MGR_H_
#define _GS_INFO_MGR_H_

#include "server_def.h"

#define MAX_INIT_SCENE_PER_GS   (256)

struct SCENE_DATA;

struct INIT_SCENE_INFO
{
    INT32 nServerGroupID;
    INT32 nSceneTempID;
};

struct GS_INFO
{
    BOOL              bConnected;
	UINT32            dwInitGSSessionID;
	INT32             nInitSceneCount;
    INIT_SCENE_INFO   nInitSceneList[MAX_INIT_SCENE_PER_GS];
	INT32			  nInitMaxSceneRoleCount;
};

class CGSInfoMgr
{
public:
    CGSInfoMgr();
    virtual ~CGSInfoMgr();

    BOOL Init(void);
    BOOL UnInit(void);

    static CGSInfoMgr& GetInstance(void);

    GS_INFO* NewGSInfo( UINT32 dwGSSessionID );
    BOOL  DelGSInfo(UINT32 dwGSSessionID);

private:
    struct CTraverseSceneData
    {
        INT32           m_nGSIndex;		  // mod g_ServerConfig.MS.nInitGSCount
        GS_INFO*        m_pGSInfoList;    // MAX_GS_SESSION_COUNT
		BOOL operator()(const SCENE_DATA* pSceneData);
		BOOL _AssignGS(INT32 nTargetGSIndex, const SCENE_DATA* pSceneData, INT32 nGroupID);
		BOOL AssignGSInTurn(const SCENE_DATA* pSceneData, INT32 nGroupID);
		BOOL AssignGSByInitMaxRoleCount(const SCENE_DATA* pSceneData, INT32 nGroupID);
    };

private:
    static CGSInfoMgr   ms_Instance;
    GS_INFO             m_GSInfoList[MAX_GS_SESSION_COUNT];
};

#endif  // _GS_INFO_MGR_H_