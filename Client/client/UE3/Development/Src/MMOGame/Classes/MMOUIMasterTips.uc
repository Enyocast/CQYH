
class MMOUIMasterTips extends MMOUIBase
	native(UI);

var int roleId;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallUCUpdatePlayerInfo(GFxObject Provider)
{
	ActionScriptVoid("UCUpdatePlayerInfo");
}

event CallUCUpdatePlayerName(GFxObject Provider)
{
	ActionScriptVoid("UCUpdatePlayerName");
}



native function ASRectivedMaster(int id);
native function ASHideStudentTwitter(int id);

DefaultProperties
{
	
}
