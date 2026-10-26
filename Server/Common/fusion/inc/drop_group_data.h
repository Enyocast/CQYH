#ifndef _DROP_GROUP_DATA_H_
#define _DROP_GROUP_DATA_H_

#include "item_def.h"
#include "data_manager.h"

#define MAX_DROP_DATA_COUNT     (64)
#define MAX_NPC_DROP_CHANCE     (128)
#define MAX_DOODAD_DROP_CHANCE  (16)

extern INT32 dummy_id;

struct DROP_GROUP_DATA_RAW
{
    INT32 m_nDropGroupID;
    BOOL m_bEnabled;

    // Mod： 是 Modify 的缩写，意为“修改”、“调整”。Chance： 意为“几率”、“概率”。ByLevel： 意为“根据等级”。
    BOOL m_bModChanceByLevel;    // 猜测功能 - 根据（玩家或怪物）的等级来调整（掉落组内各个物品的）掉落概率。

    BOOL m_bRandomDur;
    INT32 m_nDropLimitType;
    BOOL m_bCheckDropLimit;
    INT32 m_nItemID;
    INT32 m_nWeight;
    INT32 m_nCountMin;
    INT32 m_nCountMax;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, DROP_GROUP_DATA_RAW* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct NPC_DROP_DATA
{
    INT32 nNpcTemplateID;
    INT32 nChanceCount;
    DROP_CHANCE_DATA DropChanceData[MAX_NPC_DROP_CHANCE];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, NPC_DROP_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct DOODAD_DROP_DATA
{
    INT32 nDoodadTemplateID;
    INT32 nChanceCount;
    DROP_CHANCE_DATA DropChanceData[MAX_DOODAD_DROP_CHANCE];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, DOODAD_DROP_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _DROP_GROUP_DATA_H_
