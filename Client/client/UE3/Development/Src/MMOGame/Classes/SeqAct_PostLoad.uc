class SeqAct_PostLoad extends  SequenceAction;

event Activated( )
{

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
	//MMOGame(GetWorldInfo().Game).LevelLoaded = true;

}

DefaultProperties
{
	ObjName="Load InGame UI"
	ObjCategory="MMO Client"

	InputLinks.Empty
	InputLinks(0)=( LinkDesc="In" )

	OutputLinks.Empty
	OutputLinks(0)=( LinkDesc="Out" )

	VariableLinks.Empty
	VariableLinks(0)=( ExpectedType=class'SeqVar_Object', LinkDesc="Instigator" )
}
