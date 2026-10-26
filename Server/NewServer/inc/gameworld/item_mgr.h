#ifndef _ITEM_MGR_H_
#define _ITEM_MGR_H_

#include "char_def.h"
#include "attribute_def.h"
#include <item_def.h>

struct Item;
struct ITEM_DATA;
struct EQUIP_DATA;
struct RUNE_DATA;
struct ItemInfo;
struct ItemAttr;
class CItemMgr
{
public:
    static CItemMgr& GetInstance(void);
    Item* GenerateItem(INT32 nTemplateID, INT32 nItemCount);
    Item* GenerateItem(const ITEM_DATA* itemdata, INT32 nItemCount, BOOL bRandomDur = FALSE);
    Item* LoadItem(const ItemInfo& iteminfo);
    Item* CopyItem(const Item* item);
    BOOL DestroyItem(Item* item);

    void GenerateRandomAttributes(Item* item, INT32 modifyrate = RATE_MAX, INT32 nServerGroup = 0);
    void GenerateRandomSockets(Item* item, INT32 modifyrate = RATE_MAX);

    BOOL RegisterRuneData(const RUNE_DATA* data);
    INT32 GenerateRandomRuneData(INT32 nServerGroup, Item* item, INT32 cls, INT32 level, INT32 runegroup);
    INT32 GenerateRandomRuneDataAdvanced(INT32 nServerGroup, Item* item, INT32 cls, INT32 level, INT32 runegroup);

    // 自定义新增代码
    BOOL CheckEquipIsLuck2Item(INT32 itemID);
    Item* GenerateItem(INT32 nServerGroup, const ITEM_DATA* itemdata, INT32 nItemCount, BOOL bRandomDur = FALSE);
    //void GenerateRandomAttributes(INT32 nServerGroup, Item* item, INT32 modifyrate = RATE_MAX);


private:
    void _GenerateSockets(ItemInfo& iteminfo, INT32 chance, UINT8 countmin, UINT8 countmax, INT32 colorrate);
    UINT16 _GenerateRuneID(INT32 cls, INT32 level, INT32 runegroup);

    std::vector<const RUNE_DATA*> m_vec_rune_data[clsPlayerTotal];

    CItemMgr();
};

#endif // _ITEM_MGR_H_
