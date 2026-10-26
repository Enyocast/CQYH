#ifndef _ITEM_H_
#define _ITEM_H_

#include "item_data.h"
#include "attribute_def.h"

static const UINT8 ITEM_VERSION = 3;

class CCharacter;

struct ItemInfo
{
    UINT64 m_llGuid;
    INT32 m_nTemplateID;
    UINT8 m_byConSlot;
    UINT8 m_byItemSlot;
    INT32 m_nCurDur;
    INT32 m_nMaxDur;
    UINT8 m_byBindType;
    UINT8 m_Exclusive;    // 客户端里有这个字段, 不知道干啥用的, 也没有调用

    //以下属性仅限装备
    //是否已鉴定
    UINT8 m_byIdentified;
    //随机属性
    UINT16 m_wRandomAttrID[MAX_RANDOM_ATTR_COUNT];
    //签名
    UINT32 m_dwRoleID;
    //已消费金币
    UINT32 m_dwCostMoney;

    //以下属性仅限武器
    INT8 m_byLuck;  //幸运值

    //武器升级
    UINT8 m_byLevelupTimes;        // 武器升级次数
    UINT8 m_byLevelupPhyPoint;     // 攻击点数
    UINT8 m_byLevelupMagPoint;     // 魔法点数
    UINT8 m_byLevelupTaoPoint;     // 道术点数
    UINT8 m_byLevelupTypeHidden;   // 隐藏点数类型
    UINT8 m_byLevelupPointHidden;  // 隐藏点数数值

    //铭文
    UINT16 m_wRune[MAX_RUNE_COUNT];

    //以下属性仅限防具
    //融灵
    UINT32 m_dwSocketCombination;       // 孔位颜色
    INT32 m_nSoulID[MAX_SOCKET_COUNT];  // 孔位镶嵌灵石

    ItemInfo()
    {
        memset(this, 0, sizeof(ItemInfo));
    }

    UINT8 GetSocketType(UINT8 socketindex) const
    {
        switch (socketindex)
        {
        case 0: return (m_dwSocketCombination & 0x000000FF);
        case 1: return (m_dwSocketCombination & 0x0000FF00) >> 8;
        case 2: return (m_dwSocketCombination & 0x00FF0000) >> 16;
        default: return SOCKET_NONE;
        }
    }

    template<typename T>
    void ReadBuf(T& t, UINT32& s, const char* pData)
    {
        memcpy(&t, pData+s, sizeof(T));
        s += sizeof(T);
    }

    template<typename T>
    void WriteBuf(T t, UINT32& s, char* pData) const
    {
        memcpy(pData+s, &t, sizeof(T));
        s += sizeof(T);
    }

    static const UINT32 HAS_IDENTIFIED      = 0x1;
    static const UINT32 HAS_RANDOM_ATTR_0   = 0x2;
    static const UINT32 HAS_RANDOM_ATTR_1   = 0x4;
    static const UINT32 HAS_RANDOM_ATTR_2   = 0x8;
    static const UINT32 HAS_RANDOM_ATTR_3   = 0x10;
    static const UINT32 HAS_RUNE0           = 0x20;
    static const UINT32 HAS_RUNE1           = 0x40;
    static const UINT32 HAS_RUNE2           = 0x80;
    static const UINT32 HAS_RUNE3           = 0x100;
    static const UINT32 HAS_RUNE4           = 0x200;
    static const UINT32 HAS_RUNE5           = 0x400;
    static const UINT32 HAS_LUCK            = 0x800;
    static const UINT32 HAS_LEVELUP         = 0x1000;
    static const UINT32 HAS_SOCKETS         = 0x2000;
    static const UINT32 HAS_SOUL0           = 0x4000;
    static const UINT32 HAS_SOUL1           = 0x8000;
    static const UINT32 HAS_SOUL2           = 0x10000;
    static const UINT32 HAS_ROLEID          = 0x20000;
    static const UINT32 HAS_COST_MONEY      = 0x40000;

    UINT32 Load(const char* pData)
    {
        UINT8 itemver = 0;
        UINT32 bufsize = 0;
        ReadBuf(itemver, bufsize, pData);

        memset(this, 0, sizeof(ItemInfo));

        switch (itemver)
        {
        case 1:
            return bufsize + Load_v1(pData + bufsize);
        case 2:
            return bufsize + Load_v2(pData + bufsize);
        case 3:
            return bufsize + Load_v3(pData + bufsize);
        default:
            WRN("Wrong Item Version: %d, Correct Item Version: %d", itemver, ITEM_VERSION);
            return 0;
        }
    }

    UINT32 Load_v1(const char* pData)
    {
        UINT32 bufsize = 0;
        UINT32 field_bits = 0;
        
        ReadBuf(m_llGuid, bufsize, pData);
        ReadBuf(m_nTemplateID, bufsize, pData);
        ReadBuf(m_byConSlot, bufsize, pData);
        ReadBuf(m_byItemSlot, bufsize, pData);
        ReadBuf((INT16&)m_nCurDur, bufsize, pData);
        ReadBuf((INT16&)m_nMaxDur, bufsize, pData);
        ReadBuf(m_byBindType, bufsize, pData);

        ReadBuf(field_bits, bufsize, pData);

        if (field_bits & HAS_IDENTIFIED)
        {
            ReadBuf(m_byIdentified, bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_0)
        {
            ReadBuf(m_wRandomAttrID[0], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_1)
        {
            ReadBuf(m_wRandomAttrID[1], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_2)
        {
            ReadBuf(m_wRandomAttrID[2], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_3)
        {
            ReadBuf(m_wRandomAttrID[3], bufsize, pData);
        }

        if (field_bits & HAS_RUNE0)
        {
            ReadBuf(m_wRune[0], bufsize, pData);
        }

        if (field_bits & HAS_RUNE1)
        {
            ReadBuf(m_wRune[1], bufsize, pData);
        }

        if (field_bits & HAS_RUNE2)
        {
            ReadBuf(m_wRune[2], bufsize, pData);
        }

        if (field_bits & HAS_RUNE3)
        {
            ReadBuf(m_wRune[3], bufsize, pData);
        }

        if (field_bits & HAS_RUNE4)
        {
            ReadBuf(m_wRune[4], bufsize, pData);
        }

        if (field_bits & HAS_RUNE5)
        {
            ReadBuf(m_wRune[5], bufsize, pData);
        }

        if (field_bits & HAS_LUCK)
        {
            ReadBuf(m_byLuck, bufsize, pData);
        }

        if (field_bits & HAS_LEVELUP)
        {
            UINT8 use_less;
            ReadBuf(use_less, bufsize, pData);
            ReadBuf(use_less, bufsize, pData);
        }

        if (field_bits & HAS_SOCKETS)
        {
            ReadBuf(m_dwSocketCombination, bufsize, pData);
        }

        if (field_bits & HAS_SOUL0)
        {
            ReadBuf(m_nSoulID[0], bufsize, pData);
        }

        if (field_bits & HAS_SOUL1)
        {
            ReadBuf(m_nSoulID[1], bufsize, pData);
        }

        if (field_bits & HAS_SOUL2)
        {
            ReadBuf(m_nSoulID[2], bufsize, pData);
        }

        if (field_bits & HAS_ROLEID)
        {
            ReadBuf(m_dwRoleID, bufsize, pData);
        }

        if (field_bits & HAS_COST_MONEY)
        {
            ReadBuf(m_dwCostMoney, bufsize, pData);
        }

        return bufsize;
    }

    UINT32 Load_v2(const char* pData)
    {
        UINT32 bufsize = 0;
        UINT32 field_bits = 0;

        ReadBuf(m_llGuid, bufsize, pData);
        ReadBuf(m_nTemplateID, bufsize, pData);
        ReadBuf(m_byConSlot, bufsize, pData);
        ReadBuf(m_byItemSlot, bufsize, pData);
        ReadBuf((INT16&)m_nCurDur, bufsize, pData);
        ReadBuf((INT16&)m_nMaxDur, bufsize, pData);
        ReadBuf(m_byBindType, bufsize, pData);

        ReadBuf(field_bits, bufsize, pData);

        if (field_bits & HAS_IDENTIFIED)
        {
            ReadBuf(m_byIdentified, bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_0)
        {
            ReadBuf(m_wRandomAttrID[0], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_1)
        {
            ReadBuf(m_wRandomAttrID[1], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_2)
        {
            ReadBuf(m_wRandomAttrID[2], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_3)
        {
            ReadBuf(m_wRandomAttrID[3], bufsize, pData);
        }

        if (field_bits & HAS_RUNE0)
        {
            ReadBuf(m_wRune[0], bufsize, pData);
        }

        if (field_bits & HAS_RUNE1)
        {
            ReadBuf(m_wRune[1], bufsize, pData);
        }

        if (field_bits & HAS_RUNE2)
        {
            ReadBuf(m_wRune[2], bufsize, pData);
        }

        if (field_bits & HAS_RUNE3)
        {
            ReadBuf(m_wRune[3], bufsize, pData);
        }

        if (field_bits & HAS_RUNE4)
        {
            ReadBuf(m_wRune[4], bufsize, pData);
        }

        if (field_bits & HAS_RUNE5)
        {
            ReadBuf(m_wRune[5], bufsize, pData);
        }

        if (field_bits & HAS_LUCK)
        {
            ReadBuf(m_byLuck, bufsize, pData);
        }

        if (field_bits & HAS_LEVELUP)
        {
            ReadBuf(m_byLevelupTimes, bufsize, pData);
            ReadBuf(m_byLevelupPhyPoint, bufsize, pData);
            ReadBuf(m_byLevelupMagPoint, bufsize, pData);
            ReadBuf(m_byLevelupTaoPoint, bufsize, pData);
            ReadBuf(m_byLevelupTypeHidden, bufsize, pData);
            ReadBuf(m_byLevelupPointHidden, bufsize, pData);
        }

        if (field_bits & HAS_SOCKETS)
        {
            ReadBuf(m_dwSocketCombination, bufsize, pData);
        }

        if (field_bits & HAS_SOUL0)
        {
            ReadBuf(m_nSoulID[0], bufsize, pData);
        }

        if (field_bits & HAS_SOUL1)
        {
            ReadBuf(m_nSoulID[1], bufsize, pData);
        }

        if (field_bits & HAS_SOUL2)
        {
            ReadBuf(m_nSoulID[2], bufsize, pData);
        }

        if (field_bits & HAS_ROLEID)
        {
            ReadBuf(m_dwRoleID, bufsize, pData);
        }

        if (field_bits & HAS_COST_MONEY)
        {
            ReadBuf(m_dwCostMoney, bufsize, pData);
        }

        return bufsize;
    }

    UINT32 Load_v3(const char* pData)
    {
        UINT32 bufsize = 0;
        UINT32 field_bits = 0;

        ReadBuf(m_llGuid, bufsize, pData);
        ReadBuf(m_nTemplateID, bufsize, pData);
        ReadBuf(m_byConSlot, bufsize, pData);
        ReadBuf(m_byItemSlot, bufsize, pData);
        ReadBuf(m_nCurDur, bufsize, pData);
        ReadBuf(m_nMaxDur, bufsize, pData);
        ReadBuf(m_byBindType, bufsize, pData);

        ReadBuf(field_bits, bufsize, pData);

        if (field_bits & HAS_IDENTIFIED)
        {
            ReadBuf(m_byIdentified, bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_0)
        {
            ReadBuf(m_wRandomAttrID[0], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_1)
        {
            ReadBuf(m_wRandomAttrID[1], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_2)
        {
            ReadBuf(m_wRandomAttrID[2], bufsize, pData);
        }

        if (field_bits & HAS_RANDOM_ATTR_3)
        {
            ReadBuf(m_wRandomAttrID[3], bufsize, pData);
        }

        if (field_bits & HAS_RUNE0)
        {
            ReadBuf(m_wRune[0], bufsize, pData);
        }

        if (field_bits & HAS_RUNE1)
        {
            ReadBuf(m_wRune[1], bufsize, pData);
        }

        if (field_bits & HAS_RUNE2)
        {
            ReadBuf(m_wRune[2], bufsize, pData);
        }

        if (field_bits & HAS_RUNE3)
        {
            ReadBuf(m_wRune[3], bufsize, pData);
        }

        if (field_bits & HAS_RUNE4)
        {
            ReadBuf(m_wRune[4], bufsize, pData);
        }

        if (field_bits & HAS_RUNE5)
        {
            ReadBuf(m_wRune[5], bufsize, pData);
        }

        if (field_bits & HAS_LUCK)
        {
            ReadBuf(m_byLuck, bufsize, pData);
        }

        if (field_bits & HAS_LEVELUP)
        {
            ReadBuf(m_byLevelupTimes, bufsize, pData);
            ReadBuf(m_byLevelupPhyPoint, bufsize, pData);
            ReadBuf(m_byLevelupMagPoint, bufsize, pData);
            ReadBuf(m_byLevelupTaoPoint, bufsize, pData);
            ReadBuf(m_byLevelupTypeHidden, bufsize, pData);
            ReadBuf(m_byLevelupPointHidden, bufsize, pData);
        }

        if (field_bits & HAS_SOCKETS)
        {
            ReadBuf(m_dwSocketCombination, bufsize, pData);
        }

        if (field_bits & HAS_SOUL0)
        {
            ReadBuf(m_nSoulID[0], bufsize, pData);
        }

        if (field_bits & HAS_SOUL1)
        {
            ReadBuf(m_nSoulID[1], bufsize, pData);
        }

        if (field_bits & HAS_SOUL2)
        {
            ReadBuf(m_nSoulID[2], bufsize, pData);
        }

        if (field_bits & HAS_ROLEID)
        {
            ReadBuf(m_dwRoleID, bufsize, pData);
        }

        if (field_bits & HAS_COST_MONEY)
        {
            ReadBuf(m_dwCostMoney, bufsize, pData);
        }

        return bufsize;
    }

    UINT32 Save(char* pData) const
    {
        UINT32 bufsize = 0;
        UINT32* field_bits = NULL;

        WriteBuf(ITEM_VERSION, bufsize, pData);
        WriteBuf(m_llGuid, bufsize, pData);
        WriteBuf(m_nTemplateID, bufsize, pData);
        WriteBuf(m_byConSlot, bufsize, pData);
        WriteBuf(m_byItemSlot, bufsize, pData);
        WriteBuf(m_nCurDur, bufsize, pData);
        WriteBuf(m_nMaxDur, bufsize, pData);
        WriteBuf(m_byBindType, bufsize, pData);

        field_bits = (UINT32*)(pData+bufsize);
        bufsize += sizeof(UINT32);

        *field_bits = 0;

        if (m_byIdentified)
        {
            *field_bits |= HAS_IDENTIFIED;
            WriteBuf(m_byIdentified, bufsize, pData);
        }

        if (m_wRandomAttrID[0])
        {
            *field_bits |= HAS_RANDOM_ATTR_0;
            WriteBuf(m_wRandomAttrID[0], bufsize, pData);
        }

        if (m_wRandomAttrID[1])
        {
            *field_bits |= HAS_RANDOM_ATTR_1;
            WriteBuf(m_wRandomAttrID[1], bufsize, pData);
        }

        if (m_wRandomAttrID[2])
        {
            *field_bits |= HAS_RANDOM_ATTR_2;
            WriteBuf(m_wRandomAttrID[2], bufsize, pData);
        }

        if (m_wRandomAttrID[3])
        {
            *field_bits |= HAS_RANDOM_ATTR_3;
            WriteBuf(m_wRandomAttrID[3], bufsize, pData);
        }

        if (m_wRune[0])
        {
            *field_bits |= HAS_RUNE0;
            WriteBuf(m_wRune[0], bufsize, pData);
        }

        if (m_wRune[1])
        {
            *field_bits |= HAS_RUNE1;
            WriteBuf(m_wRune[1], bufsize, pData);
        }

        if (m_wRune[2])
        {
            *field_bits |= HAS_RUNE2;
            WriteBuf(m_wRune[2], bufsize, pData);
        }

        if (m_wRune[3])
        {
            *field_bits |= HAS_RUNE3;
            WriteBuf(m_wRune[3], bufsize, pData);
        }

        if (m_wRune[4])
        {
            *field_bits |= HAS_RUNE4;
            WriteBuf(m_wRune[4], bufsize, pData);
        }

        if (m_wRune[5])
        {
            *field_bits |= HAS_RUNE5;
            WriteBuf(m_wRune[5], bufsize, pData);
        }

        if (m_byLuck)
        {
            *field_bits |= HAS_LUCK;
            WriteBuf(m_byLuck, bufsize, pData);
        }

        if (m_byLevelupTimes)
        {
            *field_bits |= HAS_LEVELUP;
            WriteBuf(m_byLevelupTimes, bufsize, pData);
            WriteBuf(m_byLevelupPhyPoint, bufsize, pData);
            WriteBuf(m_byLevelupMagPoint, bufsize, pData);
            WriteBuf(m_byLevelupTaoPoint, bufsize, pData);
            WriteBuf(m_byLevelupTypeHidden, bufsize, pData);
            WriteBuf(m_byLevelupPointHidden, bufsize, pData);
        }

        if (m_dwSocketCombination)
        {
            *field_bits |= HAS_SOCKETS;
            WriteBuf(m_dwSocketCombination, bufsize, pData);
        }

        if (m_nSoulID[0])
        {
            *field_bits |= HAS_SOUL0;
            WriteBuf(m_nSoulID[0], bufsize, pData);
        }

        if (m_nSoulID[1])
        {
            *field_bits |= HAS_SOUL1;
            WriteBuf(m_nSoulID[1], bufsize, pData);
        }

        if (m_nSoulID[2])
        {
            *field_bits |= HAS_SOUL2;
            WriteBuf(m_nSoulID[2], bufsize, pData);
        }

        if (m_dwRoleID)
        {
            *field_bits |= HAS_ROLEID;
            WriteBuf(m_dwRoleID, bufsize, pData);
        }

        if (m_dwCostMoney)
        {
            *field_bits |= HAS_COST_MONEY;
            WriteBuf(m_dwCostMoney, bufsize, pData);
        }

        return bufsize;
    }

    void SaveString(char* buff, UINT32 bufflen) const;
};

struct Item
{
    Item();
    ~Item();

    void SetPos(UINT8 conslot, UINT8 itemslot);

    //如果是装备替换，必须先脱再穿！
    void OnEquip(CCharacter* c, UINT16 refine, UINT8 cls, UINT8 slot);
    void OnUnEquip(CCharacter* c, UINT16 refine, UINT8 cls, UINT8 slot);

    INT32 GetWeight() const
    {
        if (m_pTemplate->m_byDurType == DURTYPE_STACK)
            return m_pTemplate->m_nWeight * m_iteminfo.m_nCurDur;
        else
            return m_pTemplate->m_nWeight;
    }

    const ITEM_DATA* m_pTemplate;
    ItemInfo m_iteminfo;
    BOOL m_bAttrEffective;

    //调试功能
    BOOL SetAttribute(INT32 index, UINT16 attrid);
    BOOL SetSocketColor(INT32 index, UINT8 color);
    BOOL SetSoul(INT32 index, INT32 soulid);
};

#endif // _ITEM_H_
