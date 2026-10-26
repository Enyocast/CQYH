#include "stdafx.h"
#include "drop_group_data.h"

INT32 dummy_id;

BOOL DROP_GROUP_DATA_RAW::ReadLine(INT32& rnID, const char*& rpcszName, DROP_GROUP_DATA_RAW* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("DropGroupID", m_nDropGroupID);
    READ_INT("Enabled", m_bEnabled);
    READ_INT("ModChanceByLevel", m_bModChanceByLevel);
    READ_INT("RandomDur", m_bRandomDur);
    READ_INT("DropLimitType", m_nDropLimitType);
    READ_INT("CheckDropLimit", m_bCheckDropLimit);
    READ_INT("Item", m_nItemID);
    READ_INT("Weight", m_nWeight);
    READ_INT("CountMin", m_nCountMin);
    READ_INT("CountMax", m_nCountMax);

    rnID = dummy_id++;
    return TRUE;

Exit0:
    rnID = dummy_id++;
    return FALSE;
}

BOOL NPC_DROP_DATA::ReadLine(INT32& rnID, const char*& rpcszName, NPC_DROP_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();
    char column_name[256];

    READ_INT("NpcTemplateID", nNpcTemplateID);

    for (INT32 i = 0; i < MAX_NPC_DROP_CHANCE; i++)
    {
        snprintf(column_name, 256, "DropGroupID%d", i + 1);
        READ_INT(column_name, DropChanceData[i].nDropGroupID);

        snprintf(column_name, 256, "DropChance%d", i + 1);
        READ_INT(column_name, DropChanceData[i].nDropChance);
    }

    for (pData->nChanceCount = MAX_NPC_DROP_CHANCE; pData->nChanceCount > 0; pData->nChanceCount--)
    {
        if (pData->DropChanceData[pData->nChanceCount-1].nDropGroupID > 0 && pData->DropChanceData[pData->nChanceCount-1].nDropChance > 0)
            break;
    }

    READ_END(nNpcTemplateID);
}

BOOL DOODAD_DROP_DATA::ReadLine(INT32& rnID, const char*& rpcszName, DOODAD_DROP_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();
    char column_name[256];

    READ_INT("DoodadTemplateID", nDoodadTemplateID);

    for (INT32 i = 0; i < MAX_DOODAD_DROP_CHANCE; i++)
    {
        snprintf(column_name, 256, "DropGroupID%d", i + 1);
        READ_INT(column_name, DropChanceData[i].nDropGroupID);

        snprintf(column_name, 256, "DropChance%d", i + 1);
        READ_INT(column_name, DropChanceData[i].nDropChance);
    }

    for (pData->nChanceCount = MAX_DOODAD_DROP_CHANCE; pData->nChanceCount > 0; pData->nChanceCount--)
    {
        if (pData->DropChanceData[pData->nChanceCount - 1].nDropGroupID > 0 && pData->DropChanceData[pData->nChanceCount - 1].nDropChance > 0)
            break;
    }

    READ_END(nDoodadTemplateID);
}
