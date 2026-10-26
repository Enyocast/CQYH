/*=============================================================================
// LadderVolumes, when touched, cause ladder supporting actors to use Phys_Ladder.
// note that underwater ladders won't be waterzones (no breathing problems)
// Copyright 1998-2010 Epic Games, Inc. All Rights Reserved.
============================================================================= */

class MMOVolume_Teleport extends PhysicsVolume
	native
	placeable;

var(MMO) PathNode TeleportTarget;

simulated event PawnEnteredVolume(Pawn P)
{
	P.SetLocation(TeleportTarget.Location);
	P.SetRotation(TeleportTarget.Rotation);
}

simulated event PawnLeavingVolume(Pawn P)
{
	//`log("@@@@@@@@@@@@@ Pawn -- LeavingVolume !!!");
	//super.PawnLeavingVolume(P);
}

simulated event PhysicsChangedFor(Actor Other)
{
	//`log("@@@@@@@@@@@@@ PhysicsChangedFor == " @Other.Physics);
	//super.PhysicsChangedFor(Other);
}

defaultproperties
{
}
