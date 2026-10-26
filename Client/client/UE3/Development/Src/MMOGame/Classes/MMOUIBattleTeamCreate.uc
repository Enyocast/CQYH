class MMOUIBattleTeamCreate extends MMOUIBase
	native(UI);

var GFxObject InputText;
var int FlagBgIndex;
var int FlagIconIndex;

event InitOnce()
{

	InputText = GetObject("TeamNameInput");
	super.InitOnce();
}

native function NativeInitOnce();
native function CreateTeam( );


native function FlagBgChange( int index );


native function FlagIconChange( int index );

//===============================================================================================================
//===============================================================================================================
function ASBattleTeamCreateOk()
{
	CreateTeam();
}
//
function ASBattleTeamClickFlagBg( int index )
{
	FlagBgChange( index );
}
//
function ASBattleTeamClickFlagIcon( int index )
{
	FlagIconChange( index );
}

//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=BattleTeamCreate
	IsDynamicLoad=true
}
