class MMOUIWeaponSkill extends MMOUIBaseSlotContainer
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

enum WeaponSkillPanelSlotType
{
	EWpSkill_Invalid,
	EWpSkill_WepSkillCusm1,
	EWpSkill_WepSkillCusm2,
	EWpSkill_WeaponOp
};

//var config int WeaponSkillUnlockMoney;

var bool _IsAutoChangeSkill;
var int _CurOperationSkillSlot;
var int _IsUnlockingSkillSlot;
//
var bool _IsSealMode;
var bool _IsNoOpMode;
var bool _IsGuildMode;
//
var int WEAPON_SKILL_CONSUME_ITEM_ID;
var int WEAPON_SKILL_LIMIT_CONSUME_ITEM_ID;
var int _CurConsumeItemTemplateID;
//
var GFxObject _WeaponSlotMc;
var array<int> _CurWeaponCurSkill;
var GFxObject _ConsumeItemSlotMc;

var GFxObject _ConfirmTryGetSkillBtn;

var GFxObject _AutoChangeSkillChkBtn;
//
var OperationItemBagPos _ToOpWeapon;

var GFxObject _ConfirmBox;

//const MAX_WeaponSkill_CnsmItem = 2;
//var GFxObject _WepSkillConsItemMc[MAX_WeaponSkill_CnsmItem];
//var OperationItemBagPos _WepSkillConsItem[MAX_WeaponSkill_CnsmItem];

//
native function NativeInitLoad();
//
native function BagSlotChange( int bagId, int slotId );
native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);
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
//
native function ConfirmChangeWeaponSkill( GFxObject pMc );
native function CancelChangeWeaponSkill( GFxObject pMc );

event CallSetWeaponSkillTotalCount( int cnt )
{
	ActionScriptVoid( "UCSetWeaponSkillTotalCount" );
}

event CallASUpdateSkillInfoOfWeapon( GFxObject dataArray )
{
	ActionScriptVoid( "UCUpdateSkillInfoOfWeapon" );
}

event CallASSetMoneyNeed( string moneyNeed )
{
	ActionScriptVoid( "UCSetMoneyNeed" );
}

event CallASSetIsGuildEdition( bool isOrNot )
{
	ActionScriptVoid( "UCSetIsGuildEdition" );
}

event CallASSetGuildNeeds( string moneyNeed )
{
	ActionScriptVoid( "UCSetGuildNeeds" );
}
event CallASSetConsumeItem( int itemTemplateID, string iconName, int itemColor, int slotType )
{
	ActionScriptVoid( "UCSetItemData" );
}

event CallASSetConsumeItemCnt( int needCnt, int curCnt )
{
	ActionScriptVoid( "UCUpdateItemNum" );
}

event CallASPlayNewSkillGainEffect( int idx )
{
	ActionScriptVoid( "UCUpdateEffect" );
}
//===============================================================================================================
//===============================================================================================================
//var MMOUIWeaponSkill _WeaponSkillPanel;
//
//function RegisterWeaponSkill( MMOUIWeaponSkill mc )
//{
//	_WeaponSkillPanel = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_WeaponSkill);
//}
//
final native function ASClickToTryGetWeaponSkill();

final native function ASShowTips_WeaponSkill( GFxObject mc );
final native function ASHideTips_WeaponSkill();

final native function ASShowTips_ConsumeItem( GFxObject mc );
final native function ASHideTips_ConsumeItem();

final native function ASOnClickAutoChangeSkillChkBtn();
//===============================================================================================================
//===============================================================================================================
	
DefaultProperties
{
	//FriendlyName=WeaponSkill
	_CurConsumeItemTemplateID=-1
	WEAPON_SKILL_CONSUME_ITEM_ID=21001
	WEAPON_SKILL_LIMIT_CONSUME_ITEM_ID=21011
	_CurOperationSkillSlot=-1
	_IsUnlockingSkillSlot=-1
	_IsNoOpMode=false
	_IsSealMode=false
	_IsGuildMode=false
}
