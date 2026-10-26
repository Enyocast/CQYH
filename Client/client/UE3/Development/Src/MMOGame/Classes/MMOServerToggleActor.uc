//MMOServerToggleActor
//hemu@snda
//用于场景交互中 机关及门

class MMOServerToggleActor extends SkeletalMeshActor
	placeable
	native;

/*
使用一个Anim来解决四个状态+
第一帧 Closed
正放 Opening
最后一帧 Opened
反放 Closing
*/
enum EToggleActorState
{
	ETAS_Closed,
	ETAS_Opening,
	ETAS_Opened,
	ETAS_Closing
};

//动画名
var( )  name                       AnimName         <DisplayName="AnimName">;
//关联的Trigger
var()   MMOServerToggleDoorTrigger DoorTrigger      <DisplayName="DoorTrigger">;
//当前状态
var()   EToggleActorState          CurState         <DisplayName="ToggleActorState">;; 

//动画时长 
var     float               AnimTime;
var     AnimNodeSequence    AnimNodeSeq;
var     AnimSequence        AnimSeq;

simulated event PostBeginPlay()
{
	super.PostBeginPlay();
	IniData();
}


native final function  IniData();
native final function  SetState(EToggleActorState inState );
native final function  TriggerEvent( );

//可以使用Notify自由控制
/*
//打开时的声音 
var() array<SoundCue>          Sound_Close    <DisplayName="Sound_Close">;
//关闭时的声音
var() array<SoundCue>          Sound_Open     <DisplayName="Sound_Open">;
//相关特效
var( ) PointLightComponent     SourceLight    <DisplayName="SourceLight">;
var( ) ParticleSystemComponent Effect         <DisplayName="Effect">;
*/

DefaultProperties
{
	bBlockActors=true
	bCollideActors=true
	bCollideWorld=false
	Begin Object Name=SkeletalMeshComponent0
		SkeletalMesh=SkeletalMesh'MMOEditorMeshes.SkeletalMesh.DefaultSkeletalMesh'
	End Object
	SkeletalMeshComponent=SkeletalMeshComponent0

	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'MMOEditor.ServerTrigger'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="Triggers"
		Translation=(X=0,Y=0,Z=400);
	End Object
	Components.Add(Sprite)
}
