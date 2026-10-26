class MMOUIEquipRemakePanel extends MMOUIBase
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

native final function ASOnSelectEquipType(int itemSlot );
native final function ASOnEquipRemake(int itemSlot );

event CallUpdateMaterialInfo(GFxObject dataProvider , int cost)
{
	ActionScriptVoid("UCUpdateMaterialInfo");
}

event CallEquipRemakeResult(bool isSuccess, GFxObject dataProvider)
{
	ActionScriptVoid("UCEquipRemakeResult");
}

DefaultProperties
{
	IsDynamicLoad=true
}
