class MMOUIAssistPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

function InitWidget()
{
}

// UC->AS
event CallUpdateAssistDropClassList(GFxObject dataProvider)
{
	ActionScriptVoid("SetHangMenuData");
}

event CallUpdateAssistDropList(GFxObject dataProvider)
{
	ActionScriptVoid("SetHangItemConfig");
}

event CallUpdateAssistHelp(string content)
{
	ActionScriptVoid("SetConfigHelpData");
}

event CallUpdateAssistSkillData(GFxObject dataProvider)
{
	ActionScriptVoid("SetConfigSkillData");
}
	
event CallUpdateAssistItemData(GFxObject dataProvider)
{
	ActionScriptVoid("SetProtectData");
}

event CallUpdateAssistItemList(GFxObject dataProvider)
{
	ActionScriptVoid("setProtectItemData");
}

event CallUpdateAssistGameData(GFxObject dataProvider)
{
	ActionScriptVoid("SetConfigGameData");
}

event UCShowWarning(string warning)
{
	ActionScriptVoid("UCShowWarning");
}

event CallUpdatePlayerHpMp(int maxHp, int maxMp)
{
	ActionScriptVoid("UCSetMaxHMP");
}

// AS->UC
final native function ASApplyHangItemConfig(GFxObject dataProvider);
final native function ASHangConfigItemData(int page);

final native function ASApplyHangSkillConfig(GFxObject dataProvider);
final native function ASHangConfigSkillData();

final native function ASApplyProtectConfig(GFxObject dataProvider);
final native function ASProtectConfiglData();

final native function ASApplyGameConfig(GFxObject dataProvider);
function ASMdfFunction(int func)
{
    class'MMOKeyManager'.static.ASMdfFunction(func);
}

function ASDefaultInput(int input_config)
{
    class'MMOKeyManager'.static.ASDefaultInput(input_config);
}

function ASSetContralType(int ctrlType)
{
    class'MMOKeyManager'.static.ASSetContralType(ctrlType);
}

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}
