#include "stdafx.h"
#include "item.h"
#include "character.h"
#include "modifier_tree.h"
#include "modifier_file_def.h"
#include "char_modifier.h"
#include "soul_data.h"
#include "refine_data.h"
#include "attribute_data.h"
#include "set_data.h"
#include "rune_data.h"
#include "id_def.h"
#include "role.h"
#include "hero.h"

Item::Item()
{
    m_pTemplate = NULL;
    memset(&m_iteminfo, 0, sizeof(ItemInfo));
    m_bAttrEffective = FALSE;
};

Item::~Item()
{
}

void Item::SetPos(UINT8 conslot, UINT8 itemslot)
{
    m_iteminfo.m_byConSlot = conslot;
    m_iteminfo.m_byItemSlot = itemslot;
}

void Item::OnEquip(CCharacter* c, UINT16 refine, UINT8 cls, UINT8 slot)
{
    const EQUIP_DATA* equip_data = NULL;
    LOG_PROCESS_ERROR(m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    LOG_PROCESS_ERROR(!m_bAttrEffective);

    equip_data = (const EQUIP_DATA*)m_pTemplate;

    c->SetPendingItem(this);
    c->SetPendingItemSlot(slot);

    //Base attributes
    for (INT32 i = 0; i < equip_data->m_nNodeCount; i++)
    {
        CModifierTree::GetInstance().ApplyExtraNode(equip_data->m_nNodeIDs[i], c, NULL);
    }

    //Weather attributes
    if (equip_data->m_pWeatherAttrData)
    {
        CModifierTree::GetInstance().ApplyExtraNode(equip_data->m_pWeatherAttrData->m_nNodeID, c, NULL);
    }

    //Special skills
    if (equip_data->m_pSpecialAttrData)
    {
        CModifierTree::GetInstance().ApplyExtraNode(equip_data->m_pSpecialAttrData->m_nNodeID, c, NULL);
    }

    //Random attributes
    for (INT32 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
    {
        if (m_iteminfo.m_wRandomAttrID[i])
        {
            const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(m_iteminfo.m_wRandomAttrID[i]);
            LOG_PROCESS_ERROR(attr_data);
            CModifierTree::GetInstance().ApplyExtraNode(attr_data->m_nNodeID, c, NULL);
        }
    }

    //Soul fusion attributes
    for (INT32 i = 0; i < MAX_SOCKET_COUNT; i++)
    {
        if (m_iteminfo.m_nSoulID[i])
        {
            const SOUL_DATA* soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(m_iteminfo.m_nSoulID[i]);
            LOG_PROCESS_ERROR(soul_data && soul_data->m_pAttrData);
            CModifierTree::GetInstance().ApplyExtraNode(soul_data->m_pAttrData->m_nNodeID, c, NULL);
        }
    }

    //Enhancement attributes
    if (c->GetObjType() == otRole)
    {
        if (refine > 0)
        {
            const REFINE_ATTR_DATA* refine_attr_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(REFINE_ATTR_DATA::MakeKey(refine, cls, slot));
            LOG_PROCESS_ERROR(refine_attr_data);

            for (INT32 i = 0; i < refine_attr_data->m_nNodeCount; i++)
                CModifierTree::GetInstance().ApplyExtraNode(refine_attr_data->m_pAttrData[i]->m_nNodeID, c, NULL);
        }
    }

    //Set attributes
    if (equip_data->m_SetData && c->GetObjType() == otRole)
    {
        CRole* role = (CRole*)c;
        INT32 before = role->GetItemBag()->GetSetItemCountBefore(equip_data->m_SetData, 0, slot);
        INT32 after = role->GetItemBag()->GetSetItemCountAfter(equip_data->m_SetData);

        if (after > before)
        {
            //            DBG("Set %d Attr %d Apply", equip_data->m_SetData->m_nSetID, after);

            for (INT32 i = 0; i < MAX_SET_ATTR_COUNT; i++)
            {
                if (equip_data->m_SetData->m_nCount[i] == 0)
                    break;

                if (equip_data->m_SetData->m_nCount[i] == after)
                {
                    LOG_PROCESS_ERROR(equip_data->m_SetData->m_pAttrData[i]);
                    CModifierTree::GetInstance().ApplyExtraNode(equip_data->m_SetData->m_pAttrData[i]->m_nNodeID, c, NULL);
                }
            }
        }
    }

    //Soul forging attributes
    for (UINT32 i = 0; i < MAX_RUNE_COUNT; i++)
    {
        if (m_iteminfo.m_wRune[i])
        {
            const RUNE_DATA* rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(m_iteminfo.m_wRune[i]);
            LOG_PROCESS_ERROR(rune_data);
            c->EquipRune(rune_data, this);
        }
    }

    //Luck value
    if (m_iteminfo.m_byLuck)
        c->GetAttrList().SetAttrBase(c, catLuck, m_iteminfo.m_byLuck);

    //Upgrade attributes
    if (m_iteminfo.m_byLevelupPhyPoint)
        c->GetAttrList().AddAttrA(c, catMaxPhyAtk, m_iteminfo.m_byLevelupPhyPoint);
    if (m_iteminfo.m_byLevelupMagPoint)
        c->GetAttrList().AddAttrA(c, catMaxMagAtk, m_iteminfo.m_byLevelupMagPoint);
    if (m_iteminfo.m_byLevelupTaoPoint)
        c->GetAttrList().AddAttrA(c, catMaxTaoAtk, m_iteminfo.m_byLevelupTaoPoint);


    c->TrigEvent(meoOnEquipItem, NULL);

    m_bAttrEffective = TRUE;
Exit0:
    c->SetPendingItem(NULL);
    c->SetPendingItem(0);
    return;
}

void Item::OnUnEquip(CCharacter* c, UINT16 refine, UINT8 cls, UINT8 slot)
{
    const EQUIP_DATA* equip_data = NULL;
    LOG_PROCESS_ERROR(m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    LOG_PROCESS_ERROR(m_bAttrEffective);

    equip_data = (const EQUIP_DATA*)m_pTemplate;

    c->SetPendingItem(this);
    c->SetPendingItemSlot(slot);

    c->TrigEvent(meoOnEquipItem, NULL);

    //Base attributes
    for (INT32 i = 0; i < equip_data->m_nNodeCount; i++)
    {
        CModifierTree::GetInstance().RollBackExtraNode(equip_data->m_nNodeIDs[i], c, NULL);
    }

    //Weather attributes
    if (equip_data->m_pWeatherAttrData)
    {
        CModifierTree::GetInstance().RollBackExtraNode(equip_data->m_pWeatherAttrData->m_nNodeID, c, NULL);
    }

    //Special skills
    if (equip_data->m_pSpecialAttrData)
    {
        CModifierTree::GetInstance().RollBackExtraNode(equip_data->m_pSpecialAttrData->m_nNodeID, c, NULL);
    }

    //Random attributes
    for (INT32 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
    {
        if (m_iteminfo.m_wRandomAttrID[i])
        {
            const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(m_iteminfo.m_wRandomAttrID[i]);
            LOG_PROCESS_ERROR(attr_data);
            CModifierTree::GetInstance().RollBackExtraNode(attr_data->m_nNodeID, c, NULL);
        }
    }

    //Soul fusion attributes
    for (INT32 i = 0; i < MAX_SOCKET_COUNT; i++)
    {
        if (m_iteminfo.m_nSoulID[i])
        {
            const SOUL_DATA* soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(m_iteminfo.m_nSoulID[i]);
            LOG_PROCESS_ERROR(soul_data && soul_data->m_pAttrData);
            CModifierTree::GetInstance().RollBackExtraNode(soul_data->m_pAttrData->m_nNodeID, c, NULL);
        }
    }

    //Enhancement attributes
    if (c->GetObjType() == otRole)
    {
        if (refine > 0)
        {
            const REFINE_ATTR_DATA* refine_attr_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(REFINE_ATTR_DATA::MakeKey(refine, cls, slot));
            LOG_PROCESS_ERROR(refine_attr_data);

            for (INT32 i = 0; i < refine_attr_data->m_nNodeCount; i++)
                CModifierTree::GetInstance().RollBackExtraNode(refine_attr_data->m_pAttrData[i]->m_nNodeID, c, NULL);
        }
    }

    //Set attributes
    if (equip_data->m_SetData && c->GetObjType() == otRole)
    {
        CRole* role = (CRole*)c;
        INT32 before = role->GetItemBag()->GetSetItemCountBefore(equip_data->m_SetData, m_pTemplate->m_nTemplateID, slot);
        INT32 after = role->GetItemBag()->GetSetItemCountAfter(equip_data->m_SetData);

        if (before > after)
        {
            //            DBG("Set %d Attr %d Rollback", equip_data->m_SetData->m_nSetID, before);

            for (INT32 i = 0; i < MAX_SET_ATTR_COUNT; i++)
            {
                if (equip_data->m_SetData->m_nCount[i] == 0)
                    break;

                if (equip_data->m_SetData->m_nCount[i] == before)
                {
                    LOG_PROCESS_ERROR(equip_data->m_SetData->m_pAttrData[i]);
                    CModifierTree::GetInstance().RollBackExtraNode(equip_data->m_SetData->m_pAttrData[i]->m_nNodeID, c, NULL);
                }
            }
        }
    }

    //Soul forging attributes
    for (UINT32 i = 0; i < MAX_RUNE_COUNT; i++)
    {
        if (m_iteminfo.m_wRune[i])
        {
            const RUNE_DATA* rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(m_iteminfo.m_wRune[i]);
            LOG_PROCESS_ERROR(rune_data);
            c->UnEquipRune(rune_data, this);
        }
    }

    //Luck value
    if (m_iteminfo.m_byLuck)
        c->GetAttrList().SetAttrBase(c, catLuck, 0);

    //Upgrade attributes
    if (m_iteminfo.m_byLevelupPhyPoint)
        c->GetAttrList().AddAttrA(c, catMaxPhyAtk, -m_iteminfo.m_byLevelupPhyPoint);
    if (m_iteminfo.m_byLevelupMagPoint)
        c->GetAttrList().AddAttrA(c, catMaxMagAtk, -m_iteminfo.m_byLevelupMagPoint);
    if (m_iteminfo.m_byLevelupTaoPoint)
        c->GetAttrList().AddAttrA(c, catMaxTaoAtk, -m_iteminfo.m_byLevelupTaoPoint);

    m_bAttrEffective = FALSE;
Exit0:
    c->SetPendingItem(NULL);
    c->SetPendingItem(0);

    return;
}

//Debug function
BOOL Item::SetAttribute(INT32 index, UINT16 attrid)
{
    LOG_PROCESS_ERROR(m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    LOG_PROCESS_ERROR(!m_bAttrEffective);
    LOG_PROCESS_ERROR(index < MAX_RANDOM_ATTR_COUNT);
    LOG_PROCESS_ERROR(CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(attrid));

    m_iteminfo.m_wRandomAttrID[index] = attrid;

    return TRUE;

Exit0:
    return FALSE;
}

BOOL Item::SetSocketColor(INT32 index, UINT8 color)
{
    LOG_PROCESS_ERROR(m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    LOG_PROCESS_ERROR(!m_bAttrEffective);
    LOG_PROCESS_ERROR(index < MAX_SOCKET_COUNT);
    LOG_PROCESS_ERROR(color < SOCKET_TYPE_COUNT);

    ((UINT8*)&m_iteminfo.m_dwSocketCombination)[index] = color;

    return TRUE;

Exit0:
    return FALSE;
}

BOOL Item::SetSoul(INT32 index, INT32 soulid)
{
    LOG_PROCESS_ERROR(m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    LOG_PROCESS_ERROR(!m_bAttrEffective);
    LOG_PROCESS_ERROR(index < MAX_SOCKET_COUNT);
    LOG_PROCESS_ERROR(CDataManager<SOUL_DATA>::GetInstance().GetData(soulid));

    m_iteminfo.m_nSoulID[index] = soulid;

    return TRUE;

Exit0:
    return FALSE;
}

const char* GetSocketTypeName(UINT8 sockettype)
{
    switch (sockettype)
    {
        case SOCKET_NONE: return "N";
        case SOCKET_RED: return "R";
        case SOCKET_YELLOW: return "Y";
        case SOCKET_BLUE: return "B";
        case SOCKET_GREEN: return "G";
        case SOCKET_PURPLE: return "P";
        case SOCKET_COLORFUL: return "C";
        default: return "X";
    }
}

void ItemInfo::SaveString(char* buff, UINT32 bufflen) const
{
    UINT32 curlen = 0;
    memset(buff, 0, bufflen);
    static const INT32 templen = 128;
    char tempstr[templen];

    snprintf(tempstr, templen, "ver=%d", ITEM_VERSION);
    strncat(buff, tempstr, bufflen);

    snprintf(tempstr, templen, ",guid=%I64u", m_llGuid);
    strncat(buff, tempstr, bufflen);

    snprintf(tempstr, templen, ",templateid=%d", m_nTemplateID);
    strncat(buff, tempstr, bufflen);

    snprintf(tempstr, templen, ",dur=%d/%d", m_nCurDur, m_nMaxDur);
    strncat(buff, tempstr, bufflen);

    snprintf(tempstr, templen, ",bindtype=%d", m_byBindType);
    strncat(buff, tempstr, bufflen);

    if (m_byIdentified == 0)
    {
        snprintf(tempstr, templen, ",unidentified");
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRandomAttrID[0])
    {
        const ATTRIBUTE_DATA* attrdata = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(m_wRandomAttrID[0]);
        if (attrdata)
            snprintf(tempstr, templen, ",randomattr0=%d(%s)", m_wRandomAttrID[0], attrdata->m_szDesc);
        else
            snprintf(tempstr, templen, ",randomattr0=%d(%s)", m_wRandomAttrID[0]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRandomAttrID[1])
    {
        const ATTRIBUTE_DATA* attrdata = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(m_wRandomAttrID[1]);
        if (attrdata)
            snprintf(tempstr, templen, ",randomattr1=%d(%s)", m_wRandomAttrID[1], attrdata->m_szDesc);
        else
            snprintf(tempstr, templen, ",randomattr1=%d(%s)", m_wRandomAttrID[1]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRandomAttrID[2])
    {
        const ATTRIBUTE_DATA* attrdata = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(m_wRandomAttrID[2]);
        if (attrdata)
            snprintf(tempstr, templen, ",randomattr2=%d(%s)", m_wRandomAttrID[2], attrdata->m_szDesc);
        else
            snprintf(tempstr, templen, ",randomattr2=%d(%s)", m_wRandomAttrID[2]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRandomAttrID[3])
    {
        const ATTRIBUTE_DATA* attrdata = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(m_wRandomAttrID[3]);
        if (attrdata)
            snprintf(tempstr, templen, ",randomattr3=%d(%s)", m_wRandomAttrID[3], attrdata->m_szDesc);
        else
            snprintf(tempstr, templen, ",randomattr3=%d(unknown)", m_wRandomAttrID[3]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRune[0])
    {
        const RUNE_DATA* runedata = CDataManager<RUNE_DATA>::GetInstance().GetData(m_wRune[0]);
        if (runedata)
            snprintf(tempstr, templen, ",rune0=%d(%s)", m_wRune[0], runedata->szRuneName);
        else
            snprintf(tempstr, templen, ",rune0=%d(unknown)", m_wRune[0]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRune[1])
    {
        const RUNE_DATA* runedata = CDataManager<RUNE_DATA>::GetInstance().GetData(m_wRune[1]);
        if (runedata)
            snprintf(tempstr, templen, ",rune1=%d(%s)", m_wRune[1], runedata->szRuneName);
        else
            snprintf(tempstr, templen, ",rune1=%d(unknown)", m_wRune[1]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRune[2])
    {
        const RUNE_DATA* runedata = CDataManager<RUNE_DATA>::GetInstance().GetData(m_wRune[2]);
        if (runedata)
            snprintf(tempstr, templen, ",rune2=%d(%s)", m_wRune[2], runedata->szRuneName);
        else
            snprintf(tempstr, templen, ",rune2=%d(unknown)", m_wRune[2]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRune[3])
    {
        const RUNE_DATA* runedata = CDataManager<RUNE_DATA>::GetInstance().GetData(m_wRune[3]);
        if (runedata)
            snprintf(tempstr, templen, ",rune3=%d(%s)", m_wRune[3], runedata->szRuneName);
        else
            snprintf(tempstr, templen, ",rune3=%d(unknown)", m_wRune[3]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRune[4])
    {
        const RUNE_DATA* runedata = CDataManager<RUNE_DATA>::GetInstance().GetData(m_wRune[4]);
        if (runedata)
            snprintf(tempstr, templen, ",rune4=%d(%s)", m_wRune[4], runedata->szRuneName);
        else
            snprintf(tempstr, templen, ",rune4=%d(unknown)", m_wRune[4]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_wRune[5])
    {
        const RUNE_DATA* runedata = CDataManager<RUNE_DATA>::GetInstance().GetData(m_wRune[5]);
        if (runedata)
            snprintf(tempstr, templen, ",rune5=%d(%s)", m_wRune[5], runedata->szRuneName);
        else
            snprintf(tempstr, templen, ",rune5=%d(unknown)", m_wRune[5]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_byLuck)
    {
        snprintf(tempstr, templen, ",luck=%d", m_byLuck);
        strncat(buff, tempstr, bufflen);
    }

    if (m_byLevelupTimes)
    {
        snprintf(tempstr, templen, ",leveluptimes=%d", m_byLevelupTimes);
        strncat(buff, tempstr, bufflen);

        snprintf(tempstr, templen, ",levelupvalue=%d/%d/%d/%d/%d",
            m_byLevelupPhyPoint, m_byLevelupMagPoint, m_byLevelupTaoPoint, m_byLevelupTypeHidden, m_byLevelupPointHidden);
        strncat(buff, tempstr, bufflen);
    }

    if (m_dwSocketCombination)
    {
        snprintf(tempstr, templen, ",sockets=%d(%s/%s/%s)", m_dwSocketCombination,
            GetSocketTypeName(GetSocketType(0)), GetSocketTypeName(GetSocketType(1)), GetSocketTypeName(GetSocketType(2)));
        strncat(buff, tempstr, bufflen);
    }

    if (m_nSoulID[0])
    {
        const SOUL_DATA* souldata = CDataManager<SOUL_DATA>::GetInstance().GetData(m_nSoulID[0]);
        const ATTRIBUTE_DATA* attrdata = NULL;

        if (souldata)
            attrdata = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(souldata->m_nAttrID);

        if (attrdata)
            snprintf(tempstr, templen, ",soul0=%d(%s)", m_nSoulID[0], attrdata->m_szDesc);
        else
            snprintf(tempstr, templen, ",soul0=%d(unknown)", m_nSoulID[0]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_nSoulID[1])
    {
        const SOUL_DATA* souldata = CDataManager<SOUL_DATA>::GetInstance().GetData(m_nSoulID[1]);
        const ATTRIBUTE_DATA* attrdata = NULL;

        if (souldata)
            attrdata = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(souldata->m_nAttrID);

        if (attrdata)
            snprintf(tempstr, templen, ",soul1=%d(%s)", m_nSoulID[1], attrdata->m_szDesc);
        else
            snprintf(tempstr, templen, ",soul1=%d(unknown)", m_nSoulID[1]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_nSoulID[2])
    {
        const SOUL_DATA* souldata = CDataManager<SOUL_DATA>::GetInstance().GetData(m_nSoulID[2]);
        const ATTRIBUTE_DATA* attrdata = NULL;

        if (souldata)
            attrdata = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(souldata->m_nAttrID);

        if (attrdata)
            snprintf(tempstr, templen, ",soul2=%d(%s)", m_nSoulID[2], attrdata->m_szDesc);
        else
            snprintf(tempstr, templen, ",soul2=%d(unknown)", m_nSoulID[2]);
        strncat(buff, tempstr, bufflen);
    }

    if (m_dwRoleID)
    {
        snprintf(tempstr, templen, ",roleid=%u", m_dwRoleID);
        strncat(buff, tempstr, bufflen);
    }

    if (m_dwCostMoney)
    {
        snprintf(tempstr, templen, ",costmoney=%d", m_dwCostMoney);
        strncat(buff, tempstr, bufflen);
    }
}
