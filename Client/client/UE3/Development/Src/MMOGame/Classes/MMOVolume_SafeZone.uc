//
// 安全区，进入此区后玩家动作需要变化
//

class MMOVolume_SafeZone extends PhysicsVolume
	native
	dependson(MMOActor)
	placeable;

simulated event PawnEnteredVolume(Pawn P)
{
	//local MMOActor actor;

	super.PawnEnteredVolume(P);

	//actor = MMOActor(P);

	//if(actor != none)
	//{
	//	actor.OnEnterSafeZone();
	//}
}

simulated event PawnLeavingVolume(Pawn P)
{
	//	local MMOActor actor;

	super.PawnLeavingVolume(P);

	//actor = MMOActor(P);

	//if(actor != none)
	//{
	//	actor.OnLeavingSafeZone();
	//}
}

simulated event PhysicsChangedFor(Actor Other)
{
	super.PhysicsChangedFor(Other);
}

defaultproperties
{
}
