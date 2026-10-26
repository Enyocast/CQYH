#ifndef _NPC_FORCE_MGR_H_
#define _NPC_FORCE_MGR_H_

#include "npc_def.h"

class CNpcForceMgr
{
public:
    CNpcForceMgr();
    ~CNpcForceMgr();

    BOOL Init(void);
    BOOL UnInit(void);
    static CNpcForceMgr& GetInstance(void);

    INT32 GetRelation(INT32 nForce1, INT32 nForce2);

private:
    static CNpcForceMgr ms_Instance;
    INT32   m_nForceRelation[MAX_NPC_FORCE_ID][MAX_NPC_FORCE_ID];
};

#endif  // _NPC_FORCE_MGR_H_