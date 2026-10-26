#include "stdafx.h"
#include "role_faction_mgr.h"

#include "role_relation_data.h"

CRoleFactionMgr CRoleFactionMgr::ms_Instance;

CRoleFactionMgr::CRoleFactionMgr()
{
    memset(m_nFactionRelation, 0, sizeof(m_nFactionRelation));
}

CRoleFactionMgr::~CRoleFactionMgr()
{

}

BOOL CRoleFactionMgr::Init(void)
{
    for (INT32 i = 0; i < MAX_ROLE_FRACTION_ID; i++)
    {
        const ROLE_RELATION_DATA* pcRelation = CDataManager<ROLE_RELATION_DATA>::GetInstance().GetData(i);
        LOG_PROCESS_ERROR(pcRelation);

        for (INT32 j = 0; j < MAX_ROLE_FRACTION_ID; j++)
        {
            m_nFactionRelation[i][j] = pcRelation->nRelation[j];
        }
    }

    for (INT32 i = 0; i < MAX_ROLE_FRACTION_ID; i++)
    {
        for (INT32 j = 0; j < MAX_ROLE_FRACTION_ID; j++)
        {
            LOG_PROCESS_ERROR(m_nFactionRelation[i][j] == m_nFactionRelation[j][i]);
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CRoleFactionMgr::UnInit(void)
{

    return TRUE;
}

CRoleFactionMgr& CRoleFactionMgr::GetInstance(void)
{
    return ms_Instance;
}

INT32 CRoleFactionMgr::GetRelation(INT32 nFaction1, INT32 nFaction2)
{
    LOG_PROCESS_ERROR(nFaction1 >= 0 && nFaction1 < MAX_ROLE_FRACTION_ID);
    LOG_PROCESS_ERROR(nFaction2 >= 0 && nFaction2 < MAX_ROLE_FRACTION_ID);

    return m_nFactionRelation[nFaction1][nFaction2];
Exit0:
    return 0;
}
