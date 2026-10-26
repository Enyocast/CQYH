
class ArmorActor extends Actor
	native;

var EquipMesh Template;

var Pawn BaseActor;
var MeshComponent MainMesh;
var MeshComponent SubMesh;
var name CurrentAttachedSocketName;

var AnimTree              AnimTree;
var MMOActorAT    AnimationController;
var AnimNodeBlend WeaponActionLoopBlendNode;
var AnimNodeSequence ActionNode;
var AnimNodeSequence LoopNode;
var int CurrentAnimKey;

event Destroyed()
{
	DestroyAttachment();
}

native final function UpdatePosition();
native final function SwitchAttachSocket(int InIndex);
native final function OnTakeOn(Pawn InActor, EquipMesh InData);
native final function OnTakeOff();

native final function DestroyAttachment();

native final function SetVisible(bool bVisible);
native function float PlayAnimation(name Anim, optional int InKey = 0, optional float Rate = 1.0f, optional bool bLoop = false, optional ERootBoneAxis RootBoneAxisX = RBA_Discard,optional ERootBoneAxis RootBoneAxisY = RBA_Discard,optional ERootBoneAxis RootBoneAxisZ = RBA_Discard, optional EAnimBlendType BlendType = EABT_FullBody, optional float Position = 0.f, optional float InBlendIn=0.1, optional float InBlendOut=0.1, optional EAnimLevel InAnimLevel = EAL_Action);
native function PlayAnim(name Anim, bool bLoop, float InRate, float InStartTime);
native function PlayAnimByKey(name Anim, bool bLoop, float InRate, float InStartTime, int InKey);
native function StopAnimByKey(int InKey);
native function OnAnimEnd(AnimNodeSequence SeqNode, float PlayedTime, float ExcessTime);
native function RefreshAnim();
native function SetIdleAnim(name NewIdleLoopAnim);
native function SetMoveAnim(name NewMoveLoopAnim);






DefaultProperties
{
	bCollideActors=false
	bBlockActors=false
	bCollideWorld=false
	Physics=PHYS_None
	AnimTree=AnimTree'AT_Common.AT_Common'
}
