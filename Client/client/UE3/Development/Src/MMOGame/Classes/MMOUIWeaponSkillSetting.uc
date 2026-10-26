class MMOUIWeaponSkillSetting extends MMOUIBaseSlotContainer
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

enum WeaponSkillSettingPanelSlotType
{
	EWpSkillSetting_Invalid,
	EWpSkillSetting_Skill,
	EWpSkillSetting_SkillLeveUpItem,
};

//var config int WeaponSkillLevelUpItem1ID;
//var config array<int> WeaponSkillLevelUpItemCnt;

var OperationItemBagPos _ToOpWeapon;
var OperationItemBagPos _SkillLevelUpItem;
var int _CurLevelUpItemID;
var array<OperationItemBagPos> _SkillLevelUpItems;

var int _CurOperationSkillSlot;
var bool _CurLevelUpRequireOK;
var bool _CurLevelUpConsumeRequireOK;

var OperationItemBagPos _SkillReplaceItem;
//
var GFxObject _CurWeaponSkillSlot;
var GFxObject _WeaponSkillNameTf;

var GFxObject _StaticTextContainerMc;
var GFxObject _WeaponSkillLevelUpCntTf;
var GFxObject _MaxLevelTf;
var GFxObject _CurSkillLvTf;
var GFxObject _NextSkillLvTf;
		
var GFxObject _RequireConditionTf;
var GFxObject _CurConditionTf;
var GFxObject _LevelUpBtn;

var GFxObject _RequireMoneyConditionTf;
var GFxObject _RequireMoneyCurConditionTf;

var GFxObject _WeaponSkillLevelUpSlot;
var GFxObject _PanelHintTf;
//
var GFxObject _ReplaceWSkillConfirmBox;
//
native function NativeInitLoad();
//
native function BagSlotChange( int bagId, int slotId );
//native function OnItemDeleted( int containerID, int slotID );
//native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int Money, int OldMoney);
//
native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject srcSlotMC, GFxObject destSlotMC, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int SrcSlotID, ESlotPanelType destSlotType, ECONTAINER_SLOT destContainerID, int destSlotID);
//event OnSubscribeItemSlotAction()
//{
//}

//event OnUnSubscribeItemSlotAction()
//{
//}

native function OnFocusGained();
native function OnFocusLost();

//
final native function ResetUI();

final native function ShowWeaponSkillInfoPanel( bool isShow, int skillSlotIdx, int containerID, int slotID );
final native function UpdateWeaponSkillInfoPanel( int skillSlotIdx );
final native function string SetWeaponSkillLevelUpItem( int containerID, int slotID );
final native function UnSetWeaponSkillLevelUpItem();

final native function LevleUpWeaponSkill( int skillSlotIdx );
final native function NotifyLevleUpWeaponSkill( INT result );

final native function ReplaceWeaponSkill( int skillSlotIdx, int containerID, int slotID );
final native function OnConfirmReplaceWeaponSkill( GFxObject mc );
final native function OnCancelReplaceWeaponSkill( GFxObject mc );

final native function NotifyReplaceWeaponSkill( INT result );

//
final native function bool UpdateLevelUpStateAndHint( int skillSlotIdx );
final native function UpdateLevelUpBtnState();

//===============================================================================================================
//===============================================================================================================
//var MMOUIWeaponSkillSetting _WeaponSkillSettingPanel;

//
//function RegisterWeaponSkillSetting( MMOUIWeaponSkillSetting mc )
//{
//	_WeaponSkillSettingPanel = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_WeaponSkillSetting);
//}
//

final native function ASLevleUpWeaponSkill( int skillSlotIdx );
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=WeaponSkillSetting
	_CurOperationSkillSlot=-1
	_CurLevelUpRequireOK=false
}
