//*******************
// player teleport to another map
//*******************

class SeqAct_MapTeleport extends SequenceAction;

event Activated( )
{
	local SeqVar_String TargetMap;
	local SeqVar_String StartPoint;
	local SeqVar_Object TargetObject;
	local MMOPlayer instigator;
	foreach LinkedVariables( class'SeqVar_Object', TargetObject, "Instigator" )
	{
		instigator = MMOPlayer( TargetObject.GetObjectValue( ) );
		if( instigator != none )
		{
			break;
		}
	}
	foreach LinkedVariables( class'SeqVar_String', StartPoint, "StartPoint" )
	{
		if( StartPoint.StrValue != "" )
			break;
	}
	if( instigator != none )
	{
		foreach LinkedVariables( class'SeqVar_String', TargetMap, "Target Map" )
		{
			if( StartPoint != none )
				MMOPlayerController(instigator.Controller).TeleportToMap( false, TargetMap.StrValue, StartPoint.StrValue );
			else
				MMOPlayerController(instigator.Controller).TeleportToMap( false, TargetMap.StrValue );
			return;
		}
	}
}

DefaultProperties
{
	ObjName="Map Teleport"
	ObjCategory="MMO Client"

	InputLinks.Empty
	InputLinks(0)=( LinkDesc="In" )

	OutputLinks.Empty
	OutputLinks(0)=( LinkDesc="Out" )

	VariableLinks.Empty
	VariableLinks(0)=( ExpectedType=class'SeqVar_String', LinkDesc="Target Map" )
	VariableLinks(1)=( ExpectedType=class'SeqVar_Object', LinkDesc="Instigator" )
	VariableLinks(2)=( ExpectedType=class'SeqVar_String', LinkDesc="StartPoint" )
}
