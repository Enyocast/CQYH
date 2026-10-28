#ifndef _ADVENTURE_DEF_H_
#define _ADVENTURE_DEF_H_

/// @file adventure_def.h 
/// @brief adventure definition

#define MAX_ADVENTURE_TRIGGER_PARAM (4)
#define MAX_ADVENTURE_REWARD_PARAM  (8)

enum ADVENTURE_TRIGGER_TYPE
{
    attInvalid,                 ///< @line

    attKillNpc,                 ///< @line
    attDestoryDoodad,           ///< @line
    attRefineEquip,             ///< @line
    attAddSoul,                 ///< @line
    attRandomizeEquip,          ///< @line
    att5MinOnlineTime,          ///< @line
    attServerTime,              ///< @line

    attTotal                    ///< @line
};

enum ADVENTURE_REWARD_TYPE
{
    adrInvalid,                 ///< @line

    adrSpawnNpcAtPoint,         ///< @line
    adrSpawnNpcNearby,          ///< @line
    adrSpawnNpcSurround,        ///< @line
    adrSpawnDoodadAtPoint,      ///< @line
    adrSpawnDoodadNearby,       ///< @line
    adrSendMail,                ///< @line

    adrTotal                    ///< @line
};
#endif  // _ADVENTURE_DEF_H_