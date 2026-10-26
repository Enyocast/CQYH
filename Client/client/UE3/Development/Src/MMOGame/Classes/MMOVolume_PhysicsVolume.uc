/**
 * This is a movable physics volume. It can be moved by matinee, being based on
 * dynamic objects, etc.
 */
class MMOVolume_PhysicsVolume extends PhysicsVolume
	showcategories(Movement)
	placeable;

/** Is the volume enabled by default? */
var() bool bEnabled;

/**
 * Overriden to set the default collision state. 
 */
simulated event PostBeginPlay()
{
	Super.PostBeginPlay();

	SetCollision(bEnabled, bBlockActors);
}

simulated function OnToggle( SeqAct_Toggle inAction )
{
	// don't allow this action to modify the collision of static volumes as we won't be able to update the client
	if (!bStatic || RemoteRole > ROLE_None)
	{
		Super.OnToggle(inAction);
	}

	if (inAction.InputLinks[0].bHasImpulse)
	{
		// Turn on pain if that was it's original state
		bPainCausing = BACKUP_bPainCausing;
	}
	else if (inAction.InputLinks[1].bHasImpulse)
	{
		// Turn off pain
		bPainCausing = FALSE;
	}
	else if (inAction.InputLinks[2].bHasImpulse)
	{
		// Toggle pain off, or on if original state caused pain
		bPainCausing = !bPainCausing && BACKUP_bPainCausing;
	}

	if(!bCollideActors)
	{
		SetCollision(true, bBlockActors);
		bVelocityAffectsWalking = false;
	}
	else
	{
		bVelocityAffectsWalking = true;
	}
}

defaultproperties
{
	Physics=PHYS_Interpolating
	bStatic=false

	bAlwaysRelevant=true
	bReplicateMovement=true
	bOnlyDirtyReplication=true
	RemoteRole=ROLE_None

	bColored=true
	BrushColor=(R=100,G=255,B=255,A=255)

	bEnabled=true
}
