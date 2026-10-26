class SeqAct_APEX extends SequenceAction/*SeqAct_Latent*/;

event Activated()
{
	//local MMOPlayerController playerController;
	//local PathNode target;
	//local SeqVar_Player playerObj;
	local SeqVar_Object targetObj;
	//local MMOActor _actor;
	local ApexDestructibleActor _apex;
	local TraceHitInfo HitInfo;

	foreach LinkedVariables( class'SeqVar_Object', targetObj, "Explode_ApexDestructibleActor" )
	{
		`log("testApexDestructibleActor");
		_apex = ApexDestructibleActor(targetObj.GetObjectValue());
		_apex.TakeDamage(10000, None, _apex.Location, vect(1,0,0), class'DmgType_Crushed', HitInfo, _apex);
		`log("testApexDestructibleActor");
		//target = PathNode( targetObj.GetObjectValue() );
		//if( target != none )
		//{
		//	break;
		//}
	}
	//{
	//}
	//foreach LinkedVariables( class'SeqVar_Player', playerObj, "Player" )
	//{
	//	_actor = MMOActor( playerObj.GetObjectValue() );
	//	if( _actor != none )
	//	{
	//		playerController = MMOPlayerController( _actor.controller );
	//		if( playerController != none )
	//		{
	//			break;
	//		}
	//	}
	//}
	//if( target != none && playerController != none )
	//{
	//	//PlayerController.MouseHitWorldLocation = target.Location;
	//	PlayerController.MoveToPoint(target.Location);
	//	//PlayerController.StopLatentExecution();
	//	//PlayerController.StartMoveToTargetPosition();
	//	playerController.EnableKeyboardMove = false;
	//}
}
//ApexDestructibleAsset
DefaultProperties
{ 
	ObjName="Explode_ApexDestructibleActor"
	ObjCategory="MMO Client"

	VariableLinks.empty
	VariableLinks(0)=( ExpectedType=class'SeqVar_Object', LinkDesc="Explode_ApexDestructibleActor" )
}
