class MMOGFXPlayer_PlayerInfo extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIPlayerInfo             PlayerInfo;
var MMOUISimplePlayerInfo       SimplePlayerInfo;

function RegisterPlayerInfo( MMOUIPlayerInfo mc )
{
	PlayerInfo = mc;
	RegisterUI( mc , class'MMOUIManager'.default.Panel_PlayerInfo );
}

function RegisterSimplePlayerInfo( MMOUISimplePlayerInfo mc )
{
	SimplePlayerInfo = mc;
	RegisterUI( mc , class'MMOUIManager'.default.Panel_SimplePlayerInfo );
}
//native function PostAdvance(float DeltaTime );

native function ASOnPanelClose( string PanelName );//moved

native function ASShow_HeavenGasViewTips(GFxObject obj);//moved
native function ASShow_HeavenGasPowerViewTips(GFxObject obj);//moved
native function ASShowTips_HeavenBloodViewSlot(GFxObject obj,int nIndex,int nPanel);//moved
native function ASShowTips_SkillTreeActiveSkillView(GFxObject obj);//moved
native function ASHideTips_SkillTreeActiveSkillView();//moved

DefaultProperties
{
	MovieInfoStr="UI_PlayerInfoWidget.PlayerInfoWidget"
	Priority=5
	//bAllowFocus=false
	//bAllowInput=false
}
