
class MMOUIMasterInvite extends MMOUIBase
	native(UI);

var int roleId;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallUCUpdateHelloMasterInfo(GFxObject Provider)
{
	ActionScriptVoid("UCUpdateHelloMasterInfo");
}

event CallUCUpdateHelloMasterName(GFxObject Provider)
{
	ActionScriptVoid("UCUpdateHelloMasterName");
}

native function ASMasterInviteCheckBox(bool v);
native function ASMasterInviteSummit(int id);
native function ASOnMasterInvitePanelClose(int id);

DefaultProperties
{
	
}
