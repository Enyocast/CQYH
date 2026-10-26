class MMOUIEquipRemakeAdvancePanel extends MMOUIBase
	dependson(TypeDefine)
	native(UI)
	config(UIVisibleMask);

var int _CurSelectEquipType;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event InitOnce()
{
	super.InitOnce();
}

native function NativeInitOnce();

native final function ASOnSelectEquipType_Advanced(int itemSlot );
native final function ASOnEquipRemake_Advanced(int itemSlot );

event CallUpdateMaterialInfo(GFxObject dataProvider , int cost)
{
	ActionScriptVoid("UCUpdateAdvancedMaterialInfo");
}

event CallEquipRemakeResult(bool isSuccess, GFxObject dataProvider)
{
	ActionScriptVoid("UCAdvancedEquipRemakeResult");
}

DefaultProperties
{
	IsDynamicLoad=true
}
