#ifndef _STATIS_INFO_DEF_H_
#define _STATIS_INFO_DEF_H_

#define MAX_STATIS_PROCESS_COUNT  64            // the same as MAX_REMOTE_SESSION_COUNT

// update corresponding description config in maintianareaconfig.lua 
enum statEnum
{
    statInvalid, 

    statMemUsage,
    statCpuUsage,

    statInternalPacketIncome,
    statInternalPacketOutgoing,
    statInternalNetflowIncome,
    statInternalNetflowOutgoing,

    statExternalPacketIncome,
    statExternalPacketOutgoing,
    statExternalNetflowIncome,
    statExternalNetflowOutgoing,

    statFindPathCount,               // in CSceneStaticData::FindPath()
    statFindPathSamePolyReturnCount,
    statFindPathNormalReturnCount,

    statIsObstacledCount,           // in CScene::IsObstacled()

    statRoleCount,
    statNpcCount,
    statDoodadCount,
    statMissileCount,
    statSceneCount,
    statDropCount,
    statItemCount,

    statTotal
};

#pragma pack(push, 1)

struct stStatisProcess 
{
    volatile BOOL   bUsed;
    UINT32          dwProcessID;
    UINT64          qwStatisEntry[statTotal];
};

struct stStatisInfo
{
    stStatisProcess    ProcessInfo[MAX_STATIS_PROCESS_COUNT];
};

#pragma pack(pop)

#endif  //_STATIS_INFO_DEF_H_