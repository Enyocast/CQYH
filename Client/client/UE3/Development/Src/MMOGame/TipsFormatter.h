#ifndef _TIPSFORMATTER_H_
#define _TIPSFORMATTER_H_

#include "MMOPrerequisites.h"
#include "MMOFacade.h"
#include "MMOUtil.h"
#include "MMOAttrListener.h"

class ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel) = 0;
};

class TipsFormatter
{
	typedef std::map<ItemSlotType, ITipsFormatter*, M_UE3_STL_ALLOC_MAP(ItemSlotType, ITipsFormatter*) > TipsFormatterMap;
	static TipsFormatterMap _tipsFormatterMap;

public:

	static void RegTipsFormatter( ItemSlotType TipsType, ITipsFormatter* fmt );
	static ITipsFormatter* GetTipsFormatter( ItemSlotType TipsType );

	static void FormatTips(ItemSlotType TipsType, class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_Item
//------------------------------------------------------------------------
class TipsFormatter_Item : public ITipsFormatter
{
public:
    virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
	static void FormatItemTip( UGFxMoviePlayer* pGFXPlayer, UGFxObject* data, UItem* itemTemplate, ItemInfo* itemInfo = NULL, INT ItemId = 0, INT SlotType = 0, UBOOL isCompareTip = false);
	UBOOL IsItemTipsNeedCompareToCurEquipped( INT tipsFromSlotType );
};

//------------------------------------------------------------------------
//TipsFormatter_ItemBar
//------------------------------------------------------------------------
class TipsFormatter_ItemBar : public TipsFormatter_Item
{
public:
	//static void FormatItemTip(UGFxObject* data, UItem* itemTemplate, ItemInfo* itemInfo = NULL);
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_LinkTips
//------------------------------------------------------------------------
class TipsFormatter_LinkTips : public TipsFormatter_Item
{
public:
	//static void FormatItemTip(UGFxObject* data, UItem* itemTemplate, ItemInfo* itemInfo = NULL);
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_SkillEquipped
//------------------------------------------------------------------------
class TipsFormatter_SkillEquipped : public ITipsFormatter
{
public:
    virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_SkillTemplate
//------------------------------------------------------------------------
class TipsFormatter_SkillTemplate : public ITipsFormatter
{
public:
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);

public:
	static void FormatSkillTips(class UMMOAbility* skill,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
	static void FormatSkillTipsWithNoMainSkillLevel(class UMMOAbility* skill, class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
	static void FormatSkillTipsWithEquippedSkillInfo(class UMMOAbility* skill, class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
	static void FormatAppendSkillTipsForSkillNextLv(class UMMOAbility* originSkill, class UMMOUITips* TipsPanel, class UGFxObject* SubPanel );
	static void FormatAppendSkillTipsWithNoMainSkillLevel(class UMMOAbility* skill, class UMMOUITips* TipsPanel, class UGFxObject* SubPanel );

private:
	static void _FormatTipsText( UGFxObject* dataObj, class UMMOAbility* skill, class UMMOAbility* originSkill = NULL );
	static FString _ParseAttackRange( FString attackRange );
};

class TipsFormatter_SkillTemplateWithNext:public ITipsFormatter
{
public:
virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_SkillTemplate
//------------------------------------------------------------------------
class TipsFormatter_SkillSlotTemplate : public ITipsFormatter
{
public:
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};


class TipsFormatter_SkillOfMyWithNext:public ITipsFormatter
{
public:
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};
//------------------------------------------------------------------------
//TipsFormatter_LockedSlot
//------------------------------------------------------------------------
class TipsFormatter_LockedSlot : public ITipsFormatter
{
public:

    virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};



//------------------------------------------------------------------------
//TipsFormatter_Tab
//------------------------------------------------------------------------
class TipsFormatter_Tab : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

class TipsFormatter_Attribute : public ITipsFormatter
{
public:
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

class TipsFormatter_GoldStore : public ITipsFormatter
{
public:
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_MenuBar
//------------------------------------------------------------------------
class TipsFormatter_MenuBar : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_AwardIcon
//------------------------------------------------------------------------
class TipsFormatter_AwardIcon : public TipsFormatter_Item
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_Other
//------------------------------------------------------------------------
class TipsFormatter_Other : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_BuffSlot
//------------------------------------------------------------------------
class TipsFormatter_BuffSlot : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_MountSlot
//------------------------------------------------------------------------
class TipsFormatter_MountSlot : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

class TipsFormatter_RepairAll: public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_RuneActive
//------------------------------------------------------------------------
class TipsFormatter_RuneActive : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_RuneButton
//------------------------------------------------------------------------
class TipsFormatter_RuneButton : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_AvartaRuneButton
//------------------------------------------------------------------------
class TipsFormatter_AvartaRuneButton : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};


//------------------------------------------------------------------------
//TipsFormatter_PlainText
//------------------------------------------------------------------------
class TipsFormatter_PlainText : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

class TipsFormatter_NormalText : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};



//------------------------------------------------------------------------
//TipsFormatter_FreeStyle
//------------------------------------------------------------------------
class TipsFormatter_FreeStyle : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

//------------------------------------------------------------------------
//TipsFormatter_AutoSizeTips
//------------------------------------------------------------------------
class TipsFormatter_AutoSizeTips : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};
//------------------------------------------------------------------------
//TipsFormatter_HeavenGasSlot
//------------------------------------------------------------------------
class TipsFormatter_HeavenGasSlot : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};


//------------------------------------------------------------------------
//TipsFormatter_EquipSlotEnhance
//------------------------------------------------------------------------
class TipsFormatter_EquipSlotEnhance : public ITipsFormatter
{
public:

	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);

	FString FormatEnhanceProp( const struct EquipSlotEnhancePropCfgData* pEhcProp, const FString &profixStr, const FString &fontFormat );
};

//------------------------------------------------------------------------
//TipsFormatter_EquipDurability
//------------------------------------------------------------------------
class TipsFormatter_EquipDurability : public ITipsFormatter
{
public:
	virtual void FormatTips(class UGFxObject* SrcObj,  class UMMOUITips* TipsPanel, class UGFxObject* SubPanel);
};

#endif
