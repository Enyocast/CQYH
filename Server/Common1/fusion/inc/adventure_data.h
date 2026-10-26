#ifndef _ADVENTURE_DATA_H_
#define _ADVENTURE_DATA_H_

#include "adventure_def.h"
#include "data_manager.h"

struct ADVENTURE_DATA
{
    INT32   nID;

    INT32   nTriggerType;
    INT32   nVariableID;
    UINT32  dwStartTime;
    UINT32  dwEndTime;
    UINT32  dwStartDate;
    UINT32  dwEndDate;
    union
    {
        INT32   nTriggerParam[MAX_ADVENTURE_TRIGGER_PARAM];
        struct
        {
            INT32   nNpcTemplateID;
            INT32   nChance;
            INT32   nMaxCount;
        }   KillNpc;

        struct  
        {
            INT32   nDoodadTemplateID;
            INT32   nChance;
            INT32   nMaxCount;
        }   DestoryDoodad;

        struct 
        {
            INT32   nChance;
            INT32   nMaxCount;
        }   RoleRefineEquip;

        struct
        {
            INT32   nChance;
            INT32   nMaxCount;
        }   RoleAddSoul;

        struct
        {
            INT32   nChance;
            INT32   nMaxCount;
        }   RoleRandomizeEquip;

        struct 
        {
            INT32   nChance;
            INT32   nMaxCount;
        }   Role5MinOnlineTime;

        struct 
        {
            INT32   nChance;
            INT32   nMaxDuration;
        }   ServerTime;
    };

    INT32   nRewardType;
    union
    {
        INT32   nRewardParam[MAX_ADVENTURE_REWARD_PARAM];
        struct 
        {
            INT32   nNpcTemplateID;
            INT32   nSceneTemplateID;
            INT32   nX;
            INT32   nY;
            INT32   nZ;
            INT32   nRange;
        }   SpawnNpcAtPoint;

        struct 
        {
            INT32   nNpcTemplateID;
            INT32   nMinRange;
            INT32   nMaxRange;
        }   SpawnNpcNearby;

        struct 
        {
            INT32   nNpcTemplateID;
            INT32   nNpcCount;
            INT32   nDistance;
        }   SpawnNpcSurround;

        struct 
        {
            INT32   nDoodadTemplateID;
            INT32   nSceneTemplateID;
            INT32   nX;
            INT32   nY;
            INT32   nZ;
            INT32   nRange;
        }   SpawnDoodadAtPoint;

        struct 
        {
            INT32   nDoodadTemplateID;
            INT32   nMinRange;
            INT32   nMaxRange;
        }   SpawnDoodadNearby;

        struct 
        {
            INT32   nMailTemplateID;
        }   MailTemplate;
    };
    BOOL    bNeedNotification;
    UINT32  dwNotificationStringID;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ADVENTURE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif  // _ADVENTURE_DATA_H_