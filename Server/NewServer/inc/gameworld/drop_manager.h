#ifndef _DROP_MANAGER_H_
#define _DROP_MANAGER_H_

#include "drop_group_data.h"

struct ITEM_DATA;

struct DropData
{
    INT32               m_nItemID;
    const ITEM_DATA*    m_pItemData;
    INT32               m_nCountMin;
    INT32               m_nCountMax;
    INT32               m_nWeight;
};

struct DROP_GROUP_DATA
{
    INT32 m_nDropGroupID;
    BOOL m_bEnabled;
    BOOL m_bModChanceByLevel;
    BOOL m_bRandomDur;
    INT32 m_nDataCount;
    INT32 m_nTotalWeight;
    DropData m_DropData[MAX_DROP_DATA_COUNT];

    DROP_GROUP_DATA() { memset(this, 0, sizeof(DROP_GROUP_DATA)); }
};

class CDropManager
{
public:
    static CDropManager& GetInstance(void) { return ms_Instance; }
    BOOL Init();
    BOOL UnInit();
    BOOL Reload();
    BOOL IsBigDrop(INT32 templateid);

    const DROP_GROUP_DATA* GetData(INT32 nDropGroupID);

private:
    BOOL InitDropGroupData();

    static CDropManager ms_Instance;

    typedef std::map<INT32, DROP_GROUP_DATA> DROP_GROUP_DATA_MAP;
    DROP_GROUP_DATA_MAP m_datamap;

    std::map<INT32, INT32> m_npc_die_time_map;
};

#endif // _DROP_MANAGER_H_
