class MMOSceneInteractableObj extends Actor
	placeable;

var( MMOSceneObj )  SkeletalMeshComponent   SceneObj        <DisplayName="SceneObj">;
var( MMOSceneObj )  float                   StandTime       <DisplayName="StandTime">;
var( MMOSceneObj )  float                   TriggerInterval <DisplayName="TriggerInterval">;   // can't be less than 1.f
var( MMOSceneObj )  int                     TriggerNum      <DisplayName="TriggerNum">;
var( MMOSceneObj )  bool                    AlwaysStand     <DisplayName="AlwaysStand">;   // conflict with TriggerInterval

var( MMOSceneObj )  MMOVolume_Interactable   RefVolume       <DisplayName="RefVolume">;

var     bool                    TriggerBack;
var     float                   AnimTime;

var( MMOSceneObj )  name        AnimNameIdle;
var( MMOSceneObj )  name        AnimNamePrepare;
var( MMOSceneObj )  name        AnimNameActivate;
var( MMOSceneObj )  name        AnimNameStand;
var( MMOSceneObj )  name        AnimNameBack;

simulated event PostBeginPlay( )
{
	super.PostBeginPlay( );
	
	if( !AlwaysStand && TriggerInterval > 1.f )
		SetTimer( TriggerInterval, true, 'TimerProc' );
}

function TimerProc( )
{
	Start( );
}

function Start( )
{
	if( TriggerNum == -1 || TriggerNum > 0 )
	{
		if( IsInState( 'Idle' ) )
		{
			GotoState( 'Prepare' );
		}
	}
}

function TriggerObjBack( )
{
	TriggerBack = true;
}

function float PlayAnimation( name animName, optional float rate = 1.f, optional bool loop = false )
{
	local AnimNodeSequence AnimNode;
	local AnimSequence sequence;
	local bool hasAnim;

	if( SceneObj == none )
		return 0.f;

	hasAnim = false;
	foreach SceneObj.AnimSets[0].Sequences( sequence )
	{
		if( sequence.SequenceName == animName )
		{
			hasAnim = true;
			break;
		}
	}

	if( !hasAnim )
		return 0.f;

	AnimNode = AnimNodeSequence(SceneObj.Animations);
	if (AnimNode == None && SceneObj.Animations.IsA('AnimTree'))
	{
		AnimNode = AnimNodeSequence(AnimTree(SceneObj.Animations).Children[0].Anim);
	}
	if (AnimNode == None)
	{
		return 0.f;	
	}
	else
	{
		if (AnimNode.AnimSeq == None || AnimNode.AnimSeqName != animName)
		{
			AnimNode.SetAnim(animName);
		}
		AnimNode.PlayAnim( loop, rate, 0.f );
		return AnimNode.GetAnimPlaybackLength();
	}
}

auto state Idle
{
Begin:
}

state Prepare
{

Begin:
	Sleep( PlayAnimation( AnimNamePrepare ) );

	GotoState( 'Activate' );
}

state Activate
{
	event Tick( float DeltaTime )
	{
		if( RefVolume != none )
			RefVolume.Update( DeltaTime );
	}

Begin:
	if( RefVolume != none )
		RefVolume.EnableVolume( );
	Sleep( PlayAnimation( AnimNameActivate ) );
	GotoState( 'Stand' );
}

state Stand
{
	event Tick( float DeltaTime )
	{
		if( RefVolume != none )
		{
			RefVolume.Update( DeltaTime );
		}
	}

Begin:
	//TimeDiff = 0.f;
	if( AlwaysStand )
	{
		TriggerBack = false;
	}

	AnimTime = PlayAnimation( AnimNameStand );
	if( AlwaysStand )
	{
		while( !TriggerBack )
		{
			Sleep( 1.f );
		}
	}
	else
	{
		if( AnimTime > StandTime )
			Sleep( AnimTime );
		else
			Sleep( StandTime );
	}

	GotoState( 'Back' );
}

state Back
{

Begin:
	if( RefVolume != none )
		RefVolume.DisableVolume( );
	PlayAnimation( AnimNameBack );
	if( TriggerNum > 0 )
		--TriggerNum;
	GotoState( 'Idle' );
}

DefaultProperties
{
	Begin Object Class=SkeletalMeshComponent Name=SceneObj0
	//	SkeletalMesh=SkeletalMesh'Monster_SpiderModel.Spider_SkeletonMesh'
	End Object
	SceneObj=SceneObj0
	Components.Add(SceneObj0)

	TriggerInterval=5.f
	TriggerNum=-1
	AlwaysStand=false

	AnimNameIdle=Idle
	AnimNamePrepare=Prepare
	AnimNameActivate=Activate
	AnimNameStand=Stand
	AnimNameBack=Back
}
