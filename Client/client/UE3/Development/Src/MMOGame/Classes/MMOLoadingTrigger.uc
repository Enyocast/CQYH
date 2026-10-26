class MMOLoadingTrigger extends MMOServerTrigger
	placeable
	native;
// Trigger模型组件
var() StaticMeshComponent TriggerMesh;
// Trigger特效
var(EmitterComp) ParticleSystem             TriggerParticleSystem;
var transient EmitterSpawnable                 NewEmitter;
var transient ParticleSystemComponent   EmitterComponent;
//相关音效

//关联的MMOActor
var()  MMOActor        TriggerUser;
//本地计时时间
var()   float                   fLoadingTime;


//设置关联的MMOActor
/*
 两者对应关系
	UINT32           dwTrapID;
	UINT32           dwObjID;
*/
function SetUser( MMOActor User )
{
	if(!User.IsA('MMOActor'))
	{
		return;
	}
	TriggerUser = User;
}
//向服务器发送打开Trigger消息
native function OpenTriggerReq();
//服务器通知打开
event OnTriggerOpen(int iLoadingTime);
//服务器通知打断
event OnTriggerLoadingStop();
//向服务通知本地计时结束
native function OpenTriggerCompleteReq();

function SwitchState(ETriggerInitState newState)
{
	//name newName;
	switch(newState)
	{

	}
	if(!IsInState('MouseClickMove'))
	{
		 GotoState( 'MouseClickMove' );
	}
}
simulated event PostBeginPlay()
{
	super.PostBeginPlay();

	RegisterToFacade();
}
// 注册到Facade中以便查找
native function RegisterToFacade();
//隐藏
function Hide()
{
	TriggerMesh.SetHidden(true);
}
//显示
function Show()
{
	TriggerMesh.SetHidden(false);
}
event Tick(float deltaTime)
{
	super.Tick(deltaTime);

}
//机关消失，需要一定时间后刷新
state() Invisible
{


Begin:
	InitTriggerState=eTIS_Invisible;
}
//默认的关闭状态，只显示Mesh
auto state() Off
{


Begin:
	InitTriggerState=eTIS_Off;
}
//激活状态 显示Mesh和Particle
state() On
{

Begin:
	InitTriggerState=eTIS_On;
}
//打开状态
//1，倒计时，结束后通知服务器，特效
//2，调用User，显示User相关动画 /播放音效 /UI相关
state() Loading
{
	event Tick(float deltaTime)
	{
		super.Tick(deltaTime);

	}
Begin:
	InitTriggerState=eTIS_Loading;
}
DefaultProperties
{
/*
	//覆盖上一层中的默认图标
	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'MMOEditor.ServerTrigger'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="Server"
		//Scale=0.2
	End Object
	Components.Add(Sprite);*/
	TriggerType=eTT_TRAPTYPE_LOADING
	Begin Object Class=StaticMeshComponent Name=tTriggerMesh
		//模型文件
		StaticMesh=StaticMesh'MMO_Player.Mesh.TargetLocationMark'
		Rotation=(Pitch=16384, Yaw=0, Roll=0)
		RBChannel=RBCC_Nothing
	End Object
	TriggerMesh = tTriggerMesh
	CollisionComponent=tTriggerMesh
	//tTriggerMesh.SetActorCollision( true,false )
	//tTriggerMesh.SetTraceBlocking( true, true )
	//CollisionComponent.AddRadialForce( vect(0,0,0), 200, 50, 0 )
	Components.Add( tTriggerMesh )
}
