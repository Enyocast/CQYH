class MMOSceneItem_Arena extends MMOSceneInteractableObj;

var(MMOArena) StaticMeshComponent   InnerRing1;
var(MMOArena) StaticMeshComponent   InnerRing2;
var(MMOArena) StaticMeshComponent   OuterRing1;
var(MMOArena) StaticMeshComponent   OuterRing2;
var(MMOArena) StaticMeshComponent   Center;
var(MMOArena) name      InnerSocketName1 <DynamicList="SocketList">;
var(MMOArena) name      InnerSocketName2 <DynamicList="SocketList">;
var(MMOArena) name      OuterSocketName1 <DynamicList="SocketList">;
var(MMOArena) name      OuterSocketName2 <DynamicList="SocketList">;
var(MMOArena) name      CenterSocketName <DynamicList="SocketList">;

var(MMOArena) array< name >     InnerRingSockets0 <DynamicList="SocketList">;
var(MMOArena) array< name >     InnerRingSockets1 <DynamicList="SocketList">;
var(MMOArena) array< name >     InnerRingSockets2 <DynamicList="SocketList">;
var(MMOArena) array< name >     OuterRingSockets0 <DynamicList="SocketList">;
var(MMOArena) array< name >     OuterRingSockets1 <DynamicList="SocketList">;
var(MMOArena) array< name >     OuterRingSockets2 <DynamicList="SocketList">;

var(MMOArena) ParticleSystemComponent   InnerFire0;

var int     RandNumber;     // 0 three, 1 six, 2 nine
var int     RandLevel;      // 0 low, 1 medium, 2 high

simulated event PostBeginPlay()
{
	super.PostBeginPlay();

	SceneObj.AttachComponentToSocket( InnerRing1, InnerSocketName1 );
	SceneObj.AttachComponentToSocket( InnerRing2, InnerSocketName2 );
	SceneObj.AttachComponentToSocket( OuterRing1, OuterSocketName1 );
	SceneObj.AttachComponentToSocket( OuterRing2, OuterSocketName2 );
	SceneObj.AttachComponentToSocket( Center, CenterSocketName );
}

function Start()
{
	RandNumber = Rand( 3 );
	RandLevel = Rand( 3 );

	super.Start();
}

event SetFinalResult()
{
	local Rotator innerRot, outerRot;

	switch( RandNumber )
	{
	case 0:
		innerRot.Pitch = 0;
		break;
	case 1:
		innerRot.Pitch = 30;
		break;
	case 2:
		innerRot.Pitch = 60;
		break;
	default:
		break;
	}
	InnerRing1.SetRotation( innerRot );
	InnerRing2.SetRotation( innerRot );

	switch( RandLevel )
	{
	case 0:
		outerRot.Pitch = 0;
		break;
	case 1:
		outerRot.Pitch = 30;
		break;
	case 2:
		outerRot.Pitch = 60;
		break;
	default:
		break;
	}
	OuterRing1.SetRotation( outerRot );
	OuterRing2.SetRotation( outerRot );
}

event SetupFire()
{
	switch( RandNumber )
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	switch( RandLevel )
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}

DefaultProperties
{
	//Begin Object Class=CylinderComponent Name=CollisionCylinder
	//	CollisionRadius=+0034.000000
	//	CollisionHeight=+0078.000000
	//	BlockNonZeroExtent=true
	//	BlockZeroExtent=true
	//	BlockActors=true
	//	CollideActors=true
	//End Object
	//CollisionComponent=CollisionCylinder
	//Components.Add(CollisionCylinder)

	begin object class=ParticleSystemComponent name=InnerFireComp0
	end object
	InnerFire0=InnerFireComp0
	Components.Add(InnerFireComp0) 
}
