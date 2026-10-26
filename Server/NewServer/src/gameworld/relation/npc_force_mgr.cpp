#include "stdafx.h"
#include "npc_force_mgr.h"

#include "npc_relation_data.h"

CNpcForceMgr CNpcForceMgr::ms_Instance;

CNpcForceMgr::CNpcForceMgr()
{
    memset(m_nForceRelation, 0, sizeof(m_nForceRelation));
}

CNpcForceMgr::~CNpcForceMgr()
{

}

BOOL CNpcForceMgr::Init(void)
{
    for (INT32 i = 0; i < MAX_NPC_FORCE_ID; i++)
    {
        const NPC_RELATION_DATA* pcRelation = CDataManager<NPC_RELATION_DATA>::GetInstance().GetData(i);
        LOG_PROCESS_ERROR(pcRelation);

        for (INT32 j = 0; j < MAX_NPC_FORCE_ID; j++)
        {
            m_nForceRelation[i][j] = pcRelation->nRelation[j];
        }
    }

    for (INT32 i = 0; i < MAX_NPC_FORCE_ID; i++)
    {
        for (INT32 j = 0; j < MAX_NPC_FORCE_ID; j++)
        {
            LOG_PROCESS_ERROR(m_nForceRelation[i][j] == m_nForceRelation[j][i]);
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CNpcForceMgr::UnInit(void)
{

    return TRUE;
}

CNpcForceMgr& CNpcForceMgr::GetInstance(void)
{
    return ms_Instance;
}

INT32 CNpcForceMgr::GetRelation(INT32 nForce1, INT32 nForce2)
{
    LOG_PROCESS_ERROR(nForce1 >= 0 && nForce1 < MAX_NPC_FORCE_ID);
    LOG_PROCESS_ERROR(nForce2 >= 0 && nForce2 < MAX_NPC_FORCE_ID);

    return m_nForceRelation[nForce1][nForce2];
Exit0:
    return 0;
}
