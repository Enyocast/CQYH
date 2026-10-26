//
// Doodad
//
class MMODoodadActor extends MMOActor implements (IInteractableActor)
	native;

//var transient SkeletalMeshComponentEx Mesh;
var transient ParticleSystemComponent ParticleEffect;
//var transient AvatarData AvatarDataTemplate;
var transient Doodad DoodadTemplate;
//var transient CylinderComponent CylinderComponent;

var private{private} transient byte RemainOpenCount;

var transient bool IsDead;
var transient float DelayDestroyTime;

var transient bool IsQuestActive;

//-1, 0, 1, 2
var transient int OperatorStateIndex;
var transient float FirstStateLastTime;
var transient float SecondStateLastTime;
var transient float CurrentTime;
var transient int OperatorId;

native function EActorClassType GetActorType() const;
native function EPickPriority GetPickPriority();
native function EMMOCursorType GetMouseCursor();

native function vector GetInteractActorLocation();
native function float GetMaxInteractRadius();
native function DoInteract();
native function bool CanInteract() const;
native function SetSilhouette( bool show, Vector sc = vect( 1.f, 1.f, 0.f ) );

native final function FinalDestroy();

native function float PlayAnimation(
	name Anim, 
	optional int InKey = 0, 
	optional float Rate = 1.0f, 
	optional bool bLoop = false, 
	optional ERootBoneAxis RootBoneAxisX = RBA_Discard,
	optional ERootBoneAxis RootBoneAxisY = RBA_Discard,
	optional ERootBoneAxis RootBoneAxisZ = RBA_Discard, 
	optional EAnimBlendType BlendType = EABT_FullBody, 
	optional float Position = 0.f, 
	optional float InBlendIn=0.1, 
	optional float InBlendOut=0.1,
	optional EAnimLevel InLevel = EAL_Action
	);


simulated event PostBeginPlay()
{
	super.PostBeginPlay();

	OperatorStateIndex = -1;
	FirstStateLastTime = 0.f;
	SecondStateLastTime = 0.f;
	CurrentTime = 0.f;
	OperatorID = 0;
}

DefaultProperties
{
 	Begin Object Class=SkeletalMeshComponentEx Name=InitialSkeletalMesh
 		Animations=None
 		AnimTreeTemplate=AnimTree'Player_AnimTree.AT_Player'
 		//LightingChannels=(Gameplay_2=TRUE)
 		BlockZeroExtent=true
 		RBChannel=RBCC_Untitled3
		bUpdateSkelWhenNotRendered=false
 	End Object
 	Mesh=InitialSkeletalMesh;
 	Components.Add(InitialSkeletalMesh);

	Begin Object Class=ParticleSystemComponent Name=ParEffect0
		bAutoActivate=false
		bIsActive=false
	End Object
	Components.Add(ParEffect0)
	ParticleEffect=ParEffect0

//  	Begin Object Class=CylinderComponent Name=CollisionCylinder
//  		CollisionRadius=+0034.000000
//  		CollisionHeight=+0078.000000
//  		BlockNonZeroExtent=true
//  		BlockZeroExtent=true
//  		BlockActors=true
//  		CollideActors=true
//  	End Object
//  	CollisionComponent=CollisionCylinder
//  	CylinderComponent=CollisionCylinder
 	//Components.Add(CollisionCylinder)

	//bCollideWorld=true
	//bCollideWhenPlacing=false
	//Physics=PHYS_None

	bBlockActors=false
	bCollideActors=true
	bCollideWorld=false
	BlockRigidBody=false
}