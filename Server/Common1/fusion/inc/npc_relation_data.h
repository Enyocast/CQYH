#ifndef _NPC_RELATION_H_
#define _NPC_RELATION_H_

#include "data_manager.h"
#include "npc_def.h"

//tolua_begin
struct NPC_RELATION_DATA
{
    INT32 nForceID;
    INT32 nRelation[MAX_NPC_FORCE_ID];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, NPC_RELATION_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};
//tolua_end

#endif  // _NPC_RELATION_H_