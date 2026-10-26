#include "stdafx.h"
#include "post_process_data.h"

#include "id_def.h"
#include "modifier_tree.h"
#include "char_modifier.h"
#include "aura.h"
#include "spell_config.h"
#include "circle_quest_mgr.h"
#include "daily_quest_mgr.h"
#include "spell.h"
#include "attribute_data.h"
#include "item_data.h"
#include "set_data.h"
#include "soul_data.h"
#include "refine_data.h"
#include "shop_data.h"
#include "aura_data.h"
#include "missile_data.h"
#include "quest_data.h"
#include "title_data.h"
#include "spell_data.h"
#include "ai_data.h"
#include "doodad_data.h"
#include "npc_data.h"
#include "adventure_data.h"
#include "attr_conversion_data.h"
#include "money_def.h"
#include "guild_building_data.h"
#include "guild_dungeon_data.h"
#include "guild_welfare_data.h"
#include "scene_data.h"
#include "drop_manager.h"
#include "achievement_data.h"
#include "npc.h"
#include "spirit_data.h"
#include "rune_data.h"
#include "item_mgr.h"
#include "kill_npc_quest_data.h"

BOOL g_ProcessAttributeData(ATTRIBUTE_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        if (pData->m_nKey)
        {
            ModifierNode* node = CModifierTree::GetInstance().GetExtraNode(pData->m_nNodeID);
            LOG_PROCESS_ERROR(node);
            LOG_PROCESS_ERROR(pData->m_nNodeID);

            memset(node, 0, sizeof(ModifierNode));
            node->nType = mttCharacter;
            node->nKey = pData->m_nKey;

            node->Param[0].nParam = pData->m_nParam[0];
            node->Param[1].nParam = pData->m_nParam[1];
            node->Param[2].nParam = pData->m_nParam[2];
        }
        else
        {
            pData->m_nNodeID = 0;
        }
    }
    else
    {
        if (pData->m_nNodeID > 0)
        {
            CModifierTree::GetInstance().DelExtraNode(pData->m_nNodeID);
        }
        pData->m_nNodeID = 0;
    }

    return TRUE;

Exit0:
    pData->m_nNodeID = 0;
    return FALSE;
}

BOOL g_ProcessEquipData(EQUIP_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        LOG_PROCESS_ERROR(pData->m_byIdentified == IDENTIFY_TYPE_NO || pData->m_byIdentified == IDENTIFY_TYPE_YES);
        LOG_PROCESS_ERROR(pData->m_bySocketCountMin <= pData->m_bySocketCountMax);
        LOG_PROCESS_ERROR(pData->m_bySocketCountMax <= MAX_SOCKET_COUNT);

        pData->m_nNodeCount = 0;
        memset(pData->m_nNodeIDs, 0, sizeof(pData->m_nNodeIDs));
        for (INT32 i = 0; i < FixAttrTableSize; i++)
        {
            if (pData->m_nFixAttr[i])
            {
                ModifierNode* node = CModifierTree::GetInstance().GetExtraNode(pData->m_nNodeIDs[pData->m_nNodeCount]);
                LOG_PROCESS_ERROR(node);

                node->nType = mttCharacter;
                node->nKey = cmi_A;

                node->Param[0].nParam = FixAttrTable[i];
                node->Param[1].nParam = pData->m_nFixAttr[i];

                pData->m_nNodeCount++;
            }
        }

        if (pData->m_nWeatherAttrID)
        {
            pData->m_pWeatherAttrData = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->m_nWeatherAttrID);
            LOG_PROCESS_ERROR(pData->m_pWeatherAttrData);
        }
        else
        {
            pData->m_pWeatherAttrData = NULL;
        }

        if (pData->m_nSpecialAttrID)
        {
            pData->m_pSpecialAttrData = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->m_nSpecialAttrID);
            LOG_PROCESS_ERROR(pData->m_pSpecialAttrData);
        }
        else
        {
            pData->m_pSpecialAttrData = NULL;
        }
    }
    else
    {
        for (INT32 i = 0; i < pData->m_nNodeCount; i++)
        {
            if (pData->m_nNodeIDs[i] != 0)
            {
                CModifierTree::GetInstance().DelExtraNode(pData->m_nNodeIDs[i]);
                pData->m_nNodeIDs[i] = 0;
            }
        }

        pData->m_nNodeCount = 0;
        memset(pData->m_nNodeIDs, 0, sizeof(pData->m_nNodeIDs));

        pData->m_pWeatherAttrData = NULL;
        pData->m_pSpecialAttrData = NULL;
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessSetData(SET_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        for (INT32 i = 0; i < MAX_SET_PART_COUNT; i++)
        {
            if (pData->m_nItemID[i])
            {
                EQUIP_DATA* equip_data = CDataManager<EQUIP_DATA>::GetInstance().GetWritableData(pData->m_nItemID[i]);
                LOG_PROCESS_ERROR(equip_data);
                LOG_PROCESS_ERROR(equip_data->m_SetData == NULL);
                equip_data->m_SetData = pData;
            }
            else
            {
                break;
            }
        }

        for (INT32 i = 0; i < MAX_SET_ATTR_COUNT; i++)
        {
            if (pData->m_nCount[i] == 0 || pData->m_nAttrID[i] == 0)
            {
                break;
            }
            else
            {
                pData->m_pAttrData[i] = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->m_nAttrID[i]);
                LOG_PROCESS_ERROR(pData->m_pAttrData[i]);
            }
        }
    }
    else
    {

    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessSoulData(SOUL_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        pData->m_pAttrData = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->m_nAttrID);
        LOG_PROCESS_ERROR(pData->m_pAttrData);
    }
    else
    {

    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessRefineAttrData(REFINE_ATTR_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        pData->m_nNodeCount = 0;
        memset(pData->m_pAttrData, 0, sizeof(pData->m_pAttrData));
        for (INT32 i = 0; i < MAX_REFINE_ATTR_COUNT; i++)
        {
            if (pData->m_nAttrID[i])
            {
                pData->m_pAttrData[i] = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->m_nAttrID[i]);
                LOG_PROCESS_ERROR(pData->m_pAttrData[i]);
                pData->m_nNodeCount++;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        pData->m_nNodeCount = 0;
        memset(pData->m_pAttrData, 0, sizeof(pData->m_pAttrData));
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessShopData(SHOP_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        pData->m_pItemTemplate = GetItemData(pData->m_nItemID);
        LOG_PROCESS_ERROR(pData->m_pItemTemplate);

        if (pData->m_nCostItemID1 == MONEYTYPE_02)
            LOG_PROCESS_ERROR(pData->m_nCostValue1 >= pData->m_pItemTemplate->m_nSellPrice);

        if (pData->m_nCostItemID2 == MONEYTYPE_02)
            LOG_PROCESS_ERROR(pData->m_nCostValue2 >= pData->m_pItemTemplate->m_nSellPrice);
    }
    else
    {

    }

    return TRUE;
Exit0:
    WRN("failed to post process shop %s item %d",
        pData->m_szShopName, pData->m_nItemID);
    return FALSE;
}

BOOL g_ProcessAuraData(AURA_ENTRY* pData, BOOL bInit)
{
    if (bInit)
    {
        INT32 nNodeType = 0;
        CAuraTemplate* t = NULL;

        if (pData->m_nAttrTable[aatOnAppend] != 0)
        {
            nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttrTable[aatOnAppend]);
            LOG_PROCESS_ERROR(nNodeType == mttCharacter);
        }
        if (pData->m_nAttrTable[aatOnTimeup] != 0)
        {
            //		ModifierNode* pNode = CModifierTree::GetInstance().GetGlobalNode(pData->m_nAttrTable[aatOnTimeup]);
            //		LOG_PROCESS_ERROR(pNode);
            //
            //		if(pNode->nKey == 63)
            //		{
            //			SPL("Aura %d used Key 63");
            //		}

            nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttrTable[aatOnTimeup]);
            LOG_PROCESS_ERROR(nNodeType == mttCharacter);
        }
        if (pData->m_nAttrTable[aatOnDispel] != 0)
        {
            nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttrTable[aatOnDispel]);
            LOG_PROCESS_ERROR(nNodeType == mttCharacter);
        }
        if (pData->m_nAttrTable[aatOnRemove] != 0)
        {
            nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttrTable[aatOnRemove]);
            LOG_PROCESS_ERROR(nNodeType == mttCharacter);
        }
        if (pData->m_ExEvtPoint[0].m_nExOnEvt != 0)
        {
            nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_ExEvtPoint[0].m_nExOnEvt);
            LOG_PROCESS_ERROR(nNodeType == mttCharacter);
        }
        if (pData->m_ExEvtPoint[1].m_nExOnEvt != 0)
        {
            nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_ExEvtPoint[1].m_nExOnEvt);
            LOG_PROCESS_ERROR(nNodeType == mttCharacter);
        }

        t = CSpellConfig::GetInstance().FindAuraTemplate(pData->m_nID);

        if (t == NULL)
            t = CSpellConfig::GetInstance().NewAuraTemplate(pData->m_nID);

        LOG_PROCESS_ERROR(t);

        t->InitWithData(pData);
    }
    else
    {
        // todo: delete aura template
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessMissileData(MISSILE_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        if (pData->m_nAttr[matOnInit] != 0)
        {
            INT32 nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttr[matOnInit]);
            LOG_PROCESS_ERROR(nNodeType == mttMissile);
        }
        if (pData->m_nAttr[matOnCreate] != 0)
        {
            INT32 nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttr[matOnCreate]);
            LOG_PROCESS_ERROR(nNodeType == mttMissile);
        }
        if (pData->m_nAttr[matOnScan] != 0)
        {
            INT32 nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttr[matOnScan]);
            LOG_PROCESS_ERROR(nNodeType == mttMissile);
        }
        if (pData->m_nAttr[matOnRemove] != 0)
        {
            INT32 nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttr[matOnRemove]);
            LOG_PROCESS_ERROR(nNodeType == mttMissile);
        }
        if (pData->m_nAttr[matOnTimeup] != 0)
        {
            INT32 nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttr[matOnTimeup]);
            LOG_PROCESS_ERROR(nNodeType == mttMissile);
        }
    }
    else
    {

    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessQuestData(QUEST_DATA* pData, BOOL bInit)
{
    INT32 nRetCode = 0;
    const TITLE_TEMPLATE* pTitleData = NULL;

    if (bInit)
    {
        switch (pData->nQuestType)
        {
            case qtCircle:
            {
                nRetCode = CCIRCLE_QUEST_MGR::GetInstance().AddCircleQuest(pData);
                LOG_PROCESS_ERROR(nRetCode);
            }
            break;
            case qtReward:
            {
                nRetCode = CDailyQuestMgr::GetInstance().AddDailyQuest(pData);
                LOG_PROCESS_ERROR(nRetCode);
            }
            break;
            default:
                break;
        }

        // check title
        if (pData->stRewardData.nAwardTitleID != 0)
        {
            pTitleData = GetTitleTemplate(pData->stRewardData.nAwardTitleID);
            LOG_PROCESS_ERROR(pTitleData);
        }
    }
    else
    {

    }

    return TRUE;
Exit0:

    return FALSE;
}

BOOL g_ProcessSpellProgressData(SPELL_PROGRESS_DATA* pData, BOOL bInit)
{
    INT32 nRetCode = 0;

    if (bInit)
    {
        PROCESS_SUCCESS(pData->m_nID == 0 && pData->m_nLevel == 0);

        nRetCode = CSpellConfig::GetInstance().SetSpellMaxProgress(pData->m_nID, pData->m_nLevel, pData->m_nConsumePts);
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {

    }

Exit1:
    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessSpellVar(SPELL_VAR* pData, BOOL bInit)
{
    INT32 nRetCode = 0;
    CSpellTemplate* t = NULL;
    static const char* szXName[] = { "X1", "X2", "X3", "X4" };

    if (bInit)
    {
        SPELL_ENTRY* e = (SPELL_ENTRY*)CDataManager<SPELL_ENTRY>::GetInstance().GetData((pData->m_nID << 16) + pData->m_nRuneSlotID);
        PROCESS_ERROR(e);

        t = CSpellConfig::GetInstance().SetSpellTemplate(pData->m_nID, pData->m_nLevel, pData->m_nRuneSlotID, e);
        LOG_PROCESS_ERROR(t);

        e->m_bInited = TRUE;

        // 默认代码
        for (INT32 i = 0; i < MAX_EX_PARAM_COUNT; i++)
        {
            t->SetX(i, pData->m_nX[i]);

            if (pData->m_nVariableTable[i][0] != 0)
                t->InitAttr(pData->m_nVariableTable[i][0], pData->m_nVariableTable[i][1]);
        }
    }
    else
    {

    }

    return TRUE;
Exit0:
    CRI("ID: %d, Level: %d, Rune: %d.", pData->m_nID, pData->m_nLevel, pData->m_nRuneSlotID);
    return FALSE;

}

#define CHECK_NODE_TYPE(__id__, __type__)														\
if(pData->m_nAttrTable[__id__] != 0)															\
{																								\
	nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_nAttrTable[__id__]);		\
	LOG_PROCESS_ERROR(nNodeType == __type__);												\
}


BOOL g_ProcessSpellEntry(SPELL_ENTRY* pData, BOOL bInit)
{
    CSpellTemplate* t = NULL;
    INT32 nNodeType = 0;

    if (bInit)
    {
        LOG_PROCESS_ERROR(pData->m_nAttrTable[satCastType] > spctInvalid && pData->m_nAttrTable[satCastType] < spctTotal);
        LOG_PROCESS_ERROR(pData->m_nAttrTable[satJudgeType] > spjtInvalid && pData->m_nAttrTable[satJudgeType] < spjtTotal);
        LOG_PROCESS_ERROR(pData->m_nAttrTable[satAttackType] > spatInvalid && pData->m_nAttrTable[satAttackType] < spatTotal);
        LOG_PROCESS_ERROR(pData->m_nAttrTable[satQteType] > spqteInvalid && pData->m_nAttrTable[satQteType] < spqteTotal);
        LOG_PROCESS_ERROR(pData->m_nAttrTable[satLockType] > spltInvalid && pData->m_nAttrTable[satLockType] < spltTotal);
        LOG_PROCESS_ERROR(pData->m_nAttrTable[satRangeType] > sprtInvalid && pData->m_nAttrTable[satRangeType] < sprtTotal);

        CHECK_NODE_TYPE(satCasterCheckNode, mttCharacter)
            CHECK_NODE_TYPE(satTargetCheckNode, mttCharacter)
            CHECK_NODE_TYPE(satOnLearn, mttCharacter)
            CHECK_NODE_TYPE(satOnForget, mttCharacter)
            CHECK_NODE_TYPE(satOnEquip, mttCharacter)
            CHECK_NODE_TYPE(satOnUnEquip, mttCharacter)
            CHECK_NODE_TYPE(satOnPrepare, mttCharacter)
            CHECK_NODE_TYPE(satOnCast, mttCharacter)
            CHECK_NODE_TYPE(satOnBreak, mttCharacter)
            CHECK_NODE_TYPE(satOnCreateBullet, mttBullet)
            CHECK_NODE_TYPE(satBeforeRoll, mttBullet)
            CHECK_NODE_TYPE(satAfterRoll, mttBullet)
            CHECK_NODE_TYPE(satBeforeEffect, mttBullet)
            CHECK_NODE_TYPE(satAfterEffect, mttBullet)

            for (INT32 i = 0; i < MAX_EX_CAST; i++)
            {
                if (pData->m_ExCastPoint[i].m_nExOnCast != 0)
                {
                    nNodeType = CModifierTree::GetInstance().GetGlobalNodeType(pData->m_ExCastPoint[i].m_nExOnCast);
                    LOG_PROCESS_ERROR(nNodeType == mttCharacter);
                }
            }
    }
    else
    {

    }

    return TRUE;
Exit0:
    CRI("ID: %d, Rune: %d.", pData->m_nID, pData->m_nRuneSlotID);
    return FALSE;
}

BOOL g_ProcessAdventureData(ADVENTURE_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        switch (pData->nTriggerType)
        {
            case attKillNpc:
            {
                NPC_DATA* pNpcData = CDataManager<NPC_DATA>::GetInstance().GetWritableData(pData->KillNpc.nNpcTemplateID);
                LOG_PROCESS_ERROR(pNpcData);

                pNpcData->pAdventureData = pData;
            }
            break;
            case attDestoryDoodad:
            {
                DOODAD_DATA* pDoodadData = CDataManager<DOODAD_DATA>::GetInstance().GetWritableData(pData->DestoryDoodad.nDoodadTemplateID);
                LOG_PROCESS_ERROR(pDoodadData);

                pDoodadData->pAdventureData = pData;
            }
            break;
            case attServerTime:
                pData->ServerTime.nMaxDuration = CONVERT_TIME(pData->ServerTime.nMaxDuration);
                break;
        }
    }
    else
    {

    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessGuildBuilding(GUILD_BUILDING_DATA* pData, BOOL bInit)
{
    const GUILD_BUILDING_DATA* pBuildingTemplate = NULL;
    const NPC_DATA* pNpcTemplate = NULL;
    CSpellTemplate* pSpellTemplate = NULL;
    const DOODAD_DATA* pDoodadTemplate = NULL;

    if (bInit)
    {
        LOG_PROCESS_ERROR(pData->nLevel <= pData->nMaxLevel);

        if (pData->dwCdtnBaseNpcID)
        {
            pNpcTemplate = CDataManager<NPC_DATA>::GetInstance().GetData(pData->dwCdtnBaseNpcID);
            LOG_PROCESS_ERROR(pNpcTemplate);
        }

        if (pData->dwNpcTemplateID > 0)
        {
            pNpcTemplate = CDataManager<NPC_DATA>::GetInstance().GetData(pData->dwNpcTemplateID);
            LOG_PROCESS_ERROR(pNpcTemplate);
        }

        if (pData->dwID > GUILD_B_NONE && pData->dwID < GUILD_B_FUNATIONAL_NUM)
        {
            LOG_PROCESS_ERROR(pData->nMaxNum == 1);
        }

        //pBuildingTemplate = GetGuildBuildingData(pData->dwConditionBuildingID, pData->nConditionBuildingLvl);
        //LOG_PROCESS_ERROR(pBuildingTemplate);

        pSpellTemplate = CSpellConfig::GetInstance().FindSpellTemplate(pData->dwUpgradingSpellID, 1, 0);
        LOG_PROCESS_ERROR(pSpellTemplate);

        // skip msg id check

        if (pData->dwFewMembersReward > 0)
        {
            pDoodadTemplate = CDataManager<DOODAD_DATA>::GetInstance().GetData(pData->dwFewMembersReward);
            LOG_PROCESS_ERROR(pDoodadTemplate);
        }
        if (pData->dwSomeMembersReward > 0)
        {
            pDoodadTemplate = CDataManager<DOODAD_DATA>::GetInstance().GetData(pData->dwSomeMembersReward);
            LOG_PROCESS_ERROR(pDoodadTemplate);
        }
        if (pData->dwManyMembersReward > 0)
        {
            pDoodadTemplate = CDataManager<DOODAD_DATA>::GetInstance().GetData(pData->dwManyMembersReward);
            LOG_PROCESS_ERROR(pDoodadTemplate);
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessGuildDungeon(GUILD_DUNGEON_DATA* pData, BOOL bInit)
{
    const SCENE_DATA* pSceneTemplate = NULL;
    const GUILD_BUILDING_DATA* pBuildingTemplate = NULL;
    const DROP_GROUP_DATA* pDropTemplate = NULL;

    if (bInit)
    {
        if (pData->dwSceneTemplateID > 0)
        {
            pSceneTemplate = CDataManager<SCENE_DATA>::GetInstance().GetData(pData->dwSceneTemplateID);
            LOG_PROCESS_ERROR(pSceneTemplate);
        }

        if (pData->dwConditionBuildingID > 0)
        {
            pBuildingTemplate = GetGuildBuildingData(pData->dwConditionBuildingID, pData->nConditionBuildingLevel);
            LOG_PROCESS_ERROR(pBuildingTemplate);
        }

        for (INT32 i = 0; i < GuildDungeonDropGroupCount; ++i)
        {
            if (pData->arrDropGroup[i].dwGroupID > 0)
            {
                pDropTemplate = CDropManager::GetInstance().GetData(pData->arrDropGroup[i].dwGroupID);
                LOG_PROCESS_ERROR(pDropTemplate);
            }
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessGuildWelfare(GUILD_WELFARE_DATA* pData, BOOL bInit)
{
    CAura* pAura = NULL;
    const GUILD_BUILDING_DATA* pBuildingTemplate = NULL;

    if (bInit)
    {
        if (pData->dwAuraID > 0)
        {
            pAura = CSpellConfig::GetInstance().FindAuraTemplate(pData->dwAuraID);
            LOG_PROCESS_ERROR(pAura);
        }

        if (pData->dwConditionBuildingID > 0)
        {
            pBuildingTemplate = GetGuildBuildingData(pData->dwConditionBuildingID, pData->nConditionBuildingLvl);
            LOG_PROCESS_ERROR(pBuildingTemplate);
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}


BOOL g_ProcessAchievementData(ACHIEVEMENT_DATA* pData, BOOL bInit)
{
    const TITLE_TEMPLATE* pTitleTemplate = NULL;

    if (bInit)
    {
        for (INT32 nIndex = 0; nIndex < MAX_CON_PER_ACHIEVEMENT; ++nIndex)
        {
            if (adTitle == pData->vecAchievementType[nIndex])
            {
                LOG_PROCESS_ERROR(0 != pData->vecAchievementValue1[nIndex]);
                pTitleTemplate = GetTitleTemplate(pData->vecAchievementValue1[nIndex]);
                LOG_PROCESS_ERROR(pTitleTemplate);
            }

            switch (pData->vecAchievementType[nIndex])
            {
                case adKillNpcIDCount:				// 玩家杀死指定ID怪物
                {
                    LOG_PROCESS_ERROR(pData->vecAchievementValue1[nIndex] >= 0 && pData->vecAchievementValue1[nIndex] < MAX_ROLE_VARIABLE_COUNT);

                    NPC_DATA* pNpcData = CDataManager<NPC_DATA>::GetInstance().GetWritableData(pData->vecAchievementValue3[nIndex]);
                    LOG_PROCESS_ERROR(pNpcData);

                    pNpcData->nBeKilledVarIndex = pData->vecAchievementValue1[nIndex];

                    break;
                }
                case adKillNpcGroupIDCount:
                {
                    LOG_PROCESS_ERROR(pData->vecAchievementValue1[nIndex] >= 0 && pData->vecAchievementValue1[nIndex] < MAX_ROLE_VARIABLE_COUNT);

                    const NPC_DATA* pcNpcData = CDataManager<NPC_DATA>::GetInstance().GetFirstData();
                    while (pcNpcData)
                    {
                        if (pcNpcData->nGroupID == pData->vecAchievementValue3[nIndex])
                        {
                            NPC_DATA* pNpcData = (NPC_DATA*)pcNpcData;
                            pNpcData->nBeKilledVarIndex = pData->vecAchievementValue1[nIndex];
                        }
                        pcNpcData = CDataManager<NPC_DATA>::GetInstance().GetNextData();
                    }

                    break;
                }
                case adKilledByNpcIDCount:			// 指定ID怪物杀死玩家
                {
                    LOG_PROCESS_ERROR(pData->vecAchievementValue1[nIndex] >= 0 && pData->vecAchievementValue1[nIndex] < MAX_ROLE_VARIABLE_COUNT);

                    NPC_DATA* pNpcData = CDataManager<NPC_DATA>::GetInstance().GetWritableData(pData->vecAchievementValue3[nIndex]);
                    LOG_PROCESS_ERROR(pNpcData);

                    pNpcData->nKillPlayerVarIndex = pData->vecAchievementValue1[nIndex];

                    break;
                }
                case adUseItemIDCount:						// 使用指定ID物品						
                {
                    LOG_PROCESS_ERROR(pData->vecAchievementValue1[nIndex] >= 0 && pData->vecAchievementValue1[nIndex] < MAX_ROLE_VARIABLE_COUNT);

                    ITEM_DATA* pItemData = CDataManager<ITEM_DATA>::GetInstance().GetWritableData(pData->vecAchievementValue3[nIndex]);
                    LOG_PROCESS_ERROR(pItemData);

                    pItemData->m_nVarIndex = pData->vecAchievementValue1[nIndex];

                    break;
                }
                default:
                    break;
            }

        }

        for (INT32 nIndex = 0; nIndex < MAX_REWARD_PER_ACHIEVEMENT; ++nIndex)
        {
            if (adtTitle == pData->nRewardType[nIndex])
            {
                LOG_PROCESS_ERROR(0 != pData->nRewardID[nIndex]);
                pTitleTemplate = GetTitleTemplate(pData->nRewardID[nIndex]);
                LOG_PROCESS_ERROR(pTitleTemplate);
            }
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessHandbookData(HANDBOOK_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        PROCESS_SUCCESS(pData->nHandbookType <= htInvalid || pData->nHandbookType >= htTotal);
        LOG_PROCESS_ERROR(pData->nIndex >= 0 && pData->nIndex < MAX_HANKBOOK_COUNT_PER_TYPE);

        switch (pData->nHandbookType)
        {
            case htNpc_Normal:
            case htNpc_Elite:
            case htNPc_Boss:
            case htNpc_Story:
            case htNpc_Function:
            {
                for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
                {
                    if (pData->nID[i] != 0)
                    {
                        NPC_DATA* pNpc = CDataManager<NPC_DATA>::GetInstance().GetWritableData(pData->nID[i]);
                        LOG_PROCESS_ERROR(pNpc);

                        pNpc->nHandbookType = pData->nHandbookType;
                        pNpc->nHandbookIndex = pData->nIndex;
                    }
                }
            }
            break;
            case htItem_Compose:
            case htItem_Stone:
            case htItem_Story:
            {
                for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
                {
                    if (pData->nID[i] != 0)
                    {
                        ITEM_DATA* pItem = CDataManager<ITEM_DATA>::GetInstance().GetWritableData(pData->nID[i]);
                        LOG_PROCESS_ERROR(pItem);

                        pItem->m_nHandbookType = pData->nHandbookType;
                        pItem->m_nHandbookIndex = pData->nIndex;
                    }
                }
            }
            break;
            case htRune_Warrior:
            case htRune_Mage:
            case htRune_Rogue:
            case htRune_Archer:
            case htRune_Taoist:
            {
                for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
                {
                    if (pData->nID[i] != 0)
                    {
                        RUNE_DATA* pRuneData = CDataManager<RUNE_DATA>::GetInstance().GetWritableData(pData->nID[i]);
                        LOG_PROCESS_ERROR(pRuneData);

                        pRuneData->nHandbookType = pData->nHandbookType;
                        pRuneData->nHandbookIndex = pData->nIndex;
                    }
                }
            }
            break;
            case htEquip_Set:
            {
                for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
                {
                    if (pData->nID[i] != 0)
                    {
                        EQUIP_DATA* pEquip = CDataManager<EQUIP_DATA>::GetInstance().GetWritableData(pData->nID[i]);
                        LOG_PROCESS_ERROR(pEquip);
                        LOG_PROCESS_ERROR(pEquip->m_SetData);


                        pEquip->m_SetData->m_nHandbookType = pData->nHandbookType;
                        pEquip->m_SetData->m_nHankbookIndex = pData->nIndex;
                    }
                }
            }
            break;
            case htEquip_Weapon:
            case htEquip_Jewelry:
            case htEquip_Armor:
            {
                for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
                {
                    if (pData->nID[i] != 0)
                    {
                        EQUIP_DATA* pItem = CDataManager<EQUIP_DATA>::GetInstance().GetWritableData(pData->nID[i]);
                        LOG_PROCESS_ERROR(pItem);

                        pItem->m_nHandbookType = pData->nHandbookType;
                        pItem->m_nHandbookIndex = pData->nIndex;
                    }
                }
            }
            break;
            case htMap_Wild:
            case htMap_Dungeon:
            case htMap_Activity:
            {
                for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
                {
                    if (pData->nID[i] != 0)
                    {
                        SCENE_DATA* pScene = CDataManager<SCENE_DATA>::GetInstance().GetWritableData(pData->nID[i]);
                        LOG_PROCESS_ERROR(pScene);

                        pScene->nHandbookType = pData->nHandbookType;
                        pScene->nHandbookIndex = pData->nIndex;
                    }
                }
            }
            break;
            //		case htRune_Warrior:
            //		case htRune_Mage:
            //		case htRune_Rogue:
            //		case htRune_Archer:
            //		{
            //			for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
            //			{
            //				if (pData->nID[i] != 0)
            //				{
            //					RUNE_DATA* pRune = CDataManager<RUNE_DATA>::GetInstance().GetWritableData(pData->nID[i]);
            //					LOG_PROCESS_ERROR(pRune);
            //
            //					pRune->nHandbookType = pData->nHandbookType;
            //					pRune->nHandbookIndex = pData->nIndex;
            //				}
            //			}
            //		}
            //			break;
            case htAir_Green:
            case htAir_Blue:
            case htAir_Purple:
            {
                for (INT32 i = 0; i < MAX_HANDBOOKITEM_COUNT; i++)
                {
                    if (pData->nID[i] != 0)
                    {
                        AIR_DATA* pAir = CDataManager<AIR_DATA>::GetInstance().GetWritableData(pData->nID[i]);
                        LOG_PROCESS_ERROR(pAir);

                        pAir->nHandbookType = pData->nHandbookType;
                        pAir->nHandbookIndex = pData->nIndex;
                    }
                }

            }
            break;
            default:
            {
                LOG_PROCESS_ERROR(FALSE);
            }
            break;
        }
    }

Exit1:
    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessRuneData(RUNE_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        BOOL bRet = FALSE;

        LOG_PROCESS_ERROR(pData->nRuneID >= 0);
        LOG_PROCESS_ERROR(pData->nRuneID <= 65535);

        bRet = CItemMgr::GetInstance().RegisterRuneData(pData);
        LOG_PROCESS_ERROR(bRet);
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessKillNpcQuestData(KILL_NPC_QUEST_DATA* pData, BOOL bInit)
{
    if (bInit)
    {
        if (pData->nNpcTemplateID != INVALID_OBJECT_ID)
        {
            NPC_DATA* pNpcData = CDataManager<NPC_DATA>::GetInstance().GetWritableData(pData->nNpcTemplateID);
            LOG_PROCESS_ERROR(pNpcData);

            pNpcData->nKillNpcQuestID = pData->nQuestID;
        }

        if (pData->nNpcGroupID != INVALID_OBJECT_ID)
        {
            const NPC_DATA* pcNpcData = CDataManager<NPC_DATA>::GetInstance().GetFirstData();
            while (pcNpcData)
            {
                if (pcNpcData->nGroupID == pData->nNpcGroupID)
                {
                    NPC_DATA* pNpcData = (NPC_DATA*)pcNpcData;
                    pNpcData->nKillNpcQuestID = pData->nQuestID;
                }

                pcNpcData = CDataManager<NPC_DATA>::GetInstance().GetNextData();
            }

        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL g_ProcessTitleTemplate(TITLE_TEMPLATE* pData, BOOL bInit)
{
    pData->m_nNodeCount = 0;
    for (INT32 i = 0; i < TitleAttrTableSize; ++i)
    {
        if (pData->m_nAttrID[i] > 0)
        {
            const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(pData->m_nAttrID[i]);
            LOG_PROCESS_ERROR(attr_data);

            pData->m_nNodeIDs[i] = attr_data->m_nNodeID;

            ++pData->m_nNodeCount;
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

