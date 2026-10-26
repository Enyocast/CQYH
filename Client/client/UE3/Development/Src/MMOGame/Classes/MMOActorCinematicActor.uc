
class MMOActorCinematicActor extends MMOActor
	native
	placeable;


var(MMO) editconst EWeaponType CurrentCinematicWeaponType;


/** Array of Slots */
//var transient Array<AnimNodeSlot>	SlotNodes;

/** Update AnimTree from track weights */
native function MAT_SetAnimWeights(Array<AnimSlotInfo> SlotInfos);

native function MAT_SetMorphWeight(name MorphNodeName, float MorphWeight);

native function MAT_SetSkelControlScale(name SkelControlName, float Scale);

native function MAT_SetSkelControlStrength(name SkelControlName, float ControlStrength);

native function SetSilhouetteEx( bool show, Vector sc = vect( 0.f, 0.f, 0.f ) );

native function RegistToCharacterMap(bool bAdd);


native function EWeaponType GetWeaponType();

simulated event PostBeginPlay()
{
	super.PostBeginPlay();

	if(Mesh==none )
	{
		Mesh =  new() class'SkeletalMeshComponent';
	}

	Mesh.SetLightEnvironment(LightEnvironment);

	RegistToCharacterMap(true);

	RefreshAvatar();

	InitAnimNodes();

	RefreshAnim();
}

simulated event Destroyed()
{
	// Clear AnimNode references.
	ClearAnimNodes();

	Super.Destroyed();

	RegistToCharacterMap(false);
}

simulated event PostInitAnimTree(SkeletalMeshComponent SkelComp)
{
	Super.PostInitAnimTree(SkelComp);

	ClearAnimNodes();
	CacheAnimNodes();
}

simulated function CacheAnimNodes()
{
	local AnimNodeSlot SlotNode;

	// Cache all AnimNodeSlots.
	foreach Mesh.AllAnimNodes(class'AnimNodeSlot', SlotNode)
	{
		SlotNodes[SlotNodes.Length] = SlotNode;
	}
}

simulated function ClearAnimNodes()
{
	SlotNodes.Length = 0;
}

/** Called each from while the Matinee action is running, with the desired sequence name and position we want to be at. */
simulated event SetAnimPosition(name SlotName, int ChannelIndex, name InAnimSeqName, float InPosition, bool bFireNotifies, bool bLooping, bool bEnableRootMotion)
{
	MAT_SetAnimPosition(SlotName, ChannelIndex, InAnimSeqName, InPosition, bFireNotifies, bLooping, bEnableRootMotion);
}
/** Update AnimTree from track info */
native function MAT_SetAnimPosition(name SlotName, int ChannelIndex, name InAnimSeqName, float InPosition, bool bFireNotifies, bool bLooping, bool bEnableRootMotion);

/** Called when we are done with the AnimControl track. */
simulated event FinishAnimControl(InterpGroup InInterpGroup)
{
	MAT_FinishAnimControl(InInterpGroup);
}

/** Called each frame by Matinee to update the weight of a particular MorphNodeWeight. */
simulated event SetMorphWeight(name MorphNodeName, float MorphWeight)
{
	MAT_SetMorphWeight(MorphNodeName, MorphWeight);
}

/** Called each frame by Matinee to update the scaling on a SkelControl. */
simulated event SetSkelControlScale(name SkelControlName, float Scale)
{
	MAT_SetSkelControlScale(SkelControlName, Scale);
}


defaultproperties
{
	Begin Object Name=MyLightEnvironment
		bSynthesizeSHLight=TRUE
		bUseBooleanEnvironmentShadowing=FALSE
		bIsCharacterLightEnvironment=TRUE
		bAllowDynamicShadowsOnTranslucency=TRUE
	End Object

	Begin Object Class=SkeletalMeshComponent Name=SkeletalMeshComponent0
		// Keep expensive defaults that are almost always needed on cinematic skeletal mesh actors
		MinDistFactorForKinematicUpdate=0
		bUpdateSkelWhenNotRendered=TRUE
		bIgnoreControllersWhenNotRendered=FALSE
		bTickAnimNodesWhenNotRendered=TRUE
		bAcceptsStaticDecals=TRUE
		bAcceptsDynamicDecals=TRUE
		// Nice translucent lighting for hair
		bUseOnePassLightingOnTranslucency=TRUE
		// Enable the more proper skinned mesh motion blur
		bPerBoneMotionBlur=TRUE
		Animations=None
		LightEnvironment=MyLightEnvironment
		LightingChannels=(Dynamic=TRUE,Gameplay_1=TRUE)
	End Object
	Mesh=SkeletalMeshComponent0
	Components.Add(SkeletalMeshComponent0)
}
