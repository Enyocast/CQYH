class MMOGFXPlayer_BattleTeam extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIBattleTeamCreate _BattleTeamCreate;
var MMOUIBattleTeam _BattleTeam;

function RegisterBattleTeamCreate( MMOUIBattleTeamCreate mc )
{
	`log("RegisterBattleTeamCreate!!");
	_BattleTeamCreate = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_BattleTeam_BattleTeamCreate);
}

function RegisterBattleTeam( MMOUIBattleTeam mc )
{
	_BattleTeam = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_BattleTeam);
	
	
}

native function ASBattleTeamTurnOneToOne();


native function ASBattleTeamTurnFiveToFive();


native function ASBattleTeamRightClickMember( int roleId , int x , int y );

native function ASBattleTeamCheckName( string teamName );

native function ASBattleTeamAddMember();

function ASBattleTeamCreateOk()
{
	_BattleTeamCreate.CreateTeam();
}
//
function ASBattleTeamClickFlagBg( int index )
{
	_BattleTeamCreate.FlagBgChange( index );
}
//
function ASBattleTeamClickFlagIcon( int index )
{
	_BattleTeamCreate.FlagIconChange( index );
}

native function ASBattleTeamLeave();

//native function ASBattleTeamRightClick( int x , int y , GFxObject mc , int index );

DefaultProperties
{
	MovieInfoStr="UI_BattleTeam.BattleTeam"
	Priority=5
}
