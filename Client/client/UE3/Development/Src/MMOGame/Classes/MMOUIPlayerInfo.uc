class MMOUIPlayerInfo extends MMOUIBase
	native(UI);


var int _RoleId;

event CallUpdateBattlePoint( GFxObject data )
{
	ActionScriptVoid("UpdateBattlePoint");
}

event CallUpdateBaseInfo( GFxObject data )
{
	ActionScriptVoid("UpdateBaseInfo");
}

event CallSetAttributeData( GFxObject data )
{
	ActionScriptVoid("SetAttributeData");
}

event CallSetAttributeItem( GFxObject data )
{
	ActionScriptVoid("SetAttributeItem");
}

event CallUpdateRefineData( GFxObject data )
{
	ActionScriptVoid("UpdateRefineData");
}

event CallUpdateSkillData( GFxObject data )
{
	ActionScriptVoid("UpdateSkillData");
}

event CallUCSetHeavenViewGasData( GFxObject data )
{
	ActionScriptVoid("UCSetHeavenViewGasData");
}

event CallUCSetHeavenViewBloodData( GFxObject data )
{
	ActionScriptVoid("UCSetHeavenViewBloodData");
}

event CallUCUpdateInfoState( bool show)
{
	ActionScriptVoid("UCUpdateInfoState");
}

event CallUCSetWindowTitle(string s)
{
	ActionScriptVoid("UCSetWindowTitle");
}
//--------------------moved---------------------------
native function ASOnPanelClose( string PanelName );

native function ASShow_HeavenGasViewTips(GFxObject obj);
native function ASShow_HeavenGasPowerViewTips(GFxObject obj);
native function ASShowTips_HeavenBloodViewSlot(GFxObject obj,int nIndex,int nPanel);
native function ASShowTips_SkillTreeActiveSkillView(GFxObject obj);
native function ASHideTips_SkillTreeActiveSkillView();

DefaultProperties
{
	//DefaultVisible=true
	CloseOnEsc=true
	_RoleId=-1
}
