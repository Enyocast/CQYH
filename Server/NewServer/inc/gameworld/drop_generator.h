#ifndef _DROP_GENERATOR_H_
#define _DROP_GENERATOR_H_

#include "drop_manager.h"
#include "npc_data.h"
#include "drop.h"

struct Item;
struct DropContent;
class CScene;

class CDropGenerator
{
public:
    static CDropGenerator& GetInstance(void);

    BOOL GenerateGuildDungeonDrops(INT32 nServerGroup, const DROP_CHANCE_DATA chances[], INT32 chance_count,
                            UINT32 itemID[], INT32 itemCount[], INT32 &nDropCount);

    BOOL GenerateDrop(INT32 nServerGroup, INT32 itemid, INT32 itemcount, CScene* scene, INT64 llX, INT64 llY, INT64 llZ, UINT32 srcid, BOOL instantpick);

    BOOL GenerateDrops(INT32 nServerGroup, const DROP_CHANCE_DATA chances[], INT32 chance_count,
                       CScene* scene, INT64 llX, INT64 llY, INT64 llZ,
                       UINT32 ownerid, UINT32 srcid, INT32 srclevel,
                       BOOL bUniqueOrBoss, BOOL bBigDrop);

    BOOL GeneratePKDrops(Item* items[], INT32 itemcount,
                         CScene* scene, INT64 llX, INT64 llY, INT64 llZ,
                         UINT32 ownerid);
    
    BOOL GenerateDropContentFromDropGroupData(INT32 nServerGroup, const DROP_GROUP_DATA* data, DropContent& content);
    BOOL GenerateDropContentFromDropChanceData(INT32 nServerGroup, const DROP_CHANCE_DATA* pcDropChance, DropContent& rDropContent, INT32 nModifiedRate);

    void SetDropLimit(INT32 itemid, INT32 itemcount);

    void ToggleGlobalDropMax();

private:
    CDropGenerator();
    ~CDropGenerator();

    typedef std::map<INT32, INT32> DROP_LIMIT_MAP;
    DROP_LIMIT_MAP m_drop_limit_map;
    BOOL m_bDropMax;

    CDrop* _GenerateOneDrop(INT32 nServerGroup, const DROP_CHANCE_DATA* pcDropChance, INT32 nModifiedRate);
    BOOL _CheckDropLimit(INT32 nServerGroup, INT32 itemid, INT32 itemcount);
    BOOL _GenerateDrop(DropContent& content, CScene* scene, INT64 llX, INT64 llY, INT64 llZ, UINT32 srcid, CDrop::DropState state);
};

#endif // _DROP_GENERATOR_H_
