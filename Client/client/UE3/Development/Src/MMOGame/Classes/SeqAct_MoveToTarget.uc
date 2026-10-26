class SeqAct_MoveToTarget extends SequenceAction/*SeqAct_Latent*/;

event Activated()
{
	local MMOPlayerController playerController;
	local PathNode target;
	local SeqVar_Player playerObj;
	local SeqVar_Object targetObj;
	local MMOActor _actor;

	foreach LinkedVariables( class'SeqVar_Object', targetObj, "Target" )
	{
		target = PathNode( targetObj.GetObjectValue() );
		if( target != none )
		{
			break;
		}
	}
	foreach LinkedVariables( class'SeqVar_Player', playerObj, "Player" )
	{
		_actor = MMOActor( playerObj.GetObjectValue() );
		if( _actor != none )
		{
			playerController = MMOPlayerController( _actor.controller );
			if( playerController != none )
			{
				break;
			}
		}
	}
	if( target != none && playerController != none )
	{
		//PlayerController.MouseHitWorldLocation = target.Location;
		PlayerController.MoveToPoint(target.Location);
		//PlayerController.StopLatentExecution();
		//PlayerController.StartMoveToTargetPosition();
		playerController.EnableKeyboardMove = false;
	}
}

DefaultProperties
{ 
	ObjName="Move To Target"
	ObjCategory="MMO Client"

	VariableLinks.empty
	VariableLinks(0)=( ExpectedType=class'SeqVar_Player', LinkDesc="Player" )
	VariableLinks(1)=( ExpectedType=class'SeqVar_Object', LinkDesc="Target" )
}
