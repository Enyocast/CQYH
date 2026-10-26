#ifndef _SESSION_MGR_H_
#define _SESSION_MGR_H_

#include <list>

#include "id_object_pool.h"

#include "server_def.h"
#include "statis_info_def.h"

#define MAX_ALL_SESSION_COUNT   (64)

class INet;
class ISocketSession;

struct SProcessInfo
{
	UINT8               byType;
	UINT32              dwProcessID;
	UINT32				dwSessionID;
	BOOL                bAuto;
	INT32				nState;

	FILE*				poHibernateStatisFileHandle;
};

const INT32 ACCUMU_MAX_TIMES = 100;
struct stProcessStatisInfo : stStatisInfo
{
    stStatisInfo    oAccumuStatis[ACCUMU_MAX_TIMES];
    INT32           nAccumuIndex; 
    struct STAT_DATA
    {
        UINT64          qwMin;
        UINT64          qwMax;
        UINT64          qwTotal;
    };
    STAT_DATA       StatDataList[MAX_STATIS_PROCESS_COUNT][statTotal];
};

struct SRemoteGuardSession
{
	ISocketSession*     pSocketSession;
	UINT32              dwTimer;
	UINT32				dwArea;
	UINT32				dwIp;
	UINT16				wPort;
	BOOL				bConnected;
    SProcessInfo		lstProcess[MAX_REMOTE_SESSION_COUNT];

    stProcessStatisInfo* poStatisInfo;
};

class CSessionMgr
{
public:
    CSessionMgr();
    ~CSessionMgr();

    BOOL Init(INet* pNet);
    BOOL UnInit(void);
	static CSessionMgr& GetInstance(void);
	BOOL Reload();

	SRemoteGuardSession* GetRemoteGDSession(INT32 nAreaID, UINT32 dwIp);

	BOOL CloseAllSession();
	BOOL DoAllPing();
    BOOL MainLoop(void);
private:

    static CSessionMgr							ms_Instance;
	INet*										m_pNet;
    UINT32                                      m_dwLastPingTick;

	SRemoteGuardSession							m_RemoteGDSession[MAX_AREA_COUNT][MAX_GUARD_COUNT_PER_AREA];
};
#endif  // _GUARD_SESSION_MGR_H_