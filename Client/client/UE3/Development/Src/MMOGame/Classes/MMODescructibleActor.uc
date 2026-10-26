//
// 用于实现场景中可破坏的物体
//
class MMODescructibleActor extends FracturedStaticMeshActor implements(IAbilityDamageable, IMMOActorHUD, IServerTrigger)
	placeable
	dependson(WorldInfo, ActorAttribute)
	config(Game)
	native;

// 低血量范围参考值
var(MMO) float LowHealthParticlePercentThreshold <DisplayName="LowHealthParticlePercentThreshold">;

// 健康时的血条颜色
var(MMO) Vector HealthyColor <DisplayName="HealthyColor">;

// 受伤时的血条颜色
var(MMO) Vector UnhealthyColor <DisplayName="UnhealthyColor">;

// 被击中时的特效模板
var(MMO) Emitter HurtEffectTemplate <DisplayName="HurtEffectTemplate">;

// 死亡时的特效模板
var(MMO) Emitter DiedEffectTemplate <DisplayName="DiedEffectTemplate">;

// 粒子组件
var(MMO) ParticleSystemComponent LowHealthParticleEffect <DisplayName="LowHealthParticleEffect">;

// 血条的材质模板
var(MMO) MaterialInstanceConstant TheHealthHUDMatTemplate <DisplayName="TheHealthHUDMatTemplate">;

// 血条材质
var transient MaterialInstanceConstant MyHealthHUDMatInstance;

// 是否绘制血条
var(MMO) bool EnableDrawHealthBar <DisplayName="EnableDrawHealthBar">;

// 血条缩放大小
var(MMO) float HealthBarScale <DisplayName="HealthBarScale">;

// 血条偏移
var(MMO) Vector HealthBarPositionOffset <DisplayName="HealthBarPositionOffset">;

// 最后一次被攻击的时间
var float LastTakeDamageTime;


// 阵营标识, 两阵营标识做 AND 操作，不为0是友好
var int FriendlyMask;

// 角色属性
var(MMO) ActorAttribute ActorAttributes <DisplayName="ActorAttributes">;

// 消失时间
var(MMO) float FadeOutTime <DisplayName="FadeOutTime">;
var float FadeLife;

var(MMOServer) int TriggerID;
var(MMOServer) ETriggerType TriggerType;
// 关联的阻挡框
var(MMOServer) array<DynamicBlockingVolume> AssociatedBlockingVolume;
var(MMOServer) ETriggerInitState InitTriggerState;
var(MMOServer) array<NPCSpawnPoint> NPCSpawnPoints;
var(MMOServer_NPCDead) NPCDeadEvent NPCDeadEvent;
var(MMOServer) array<IServerTrigger> LinkedTrigger;
var(MMOServer) int DelayTime;
var(MMOServer) array<AbilityEvent> AbilityList;
var(MMOServer) TeleportEvent TeleportEvent;

var(MMOServer) ETrapEventType TrapEventType;

var(MMOServer_EventArea) array<IServerArea> LinkedEventArea;
var(MMOServer_LoadingTrigger) int LoadingTime;

var(MMOServer_OpenTeleport) array<TeleportOrig> LinkedTeleportList;
// 取得攻击防御属属性
function ActorAttribute GetActorAttribute()
{
	return ActorAttributes;
}

// 初始化函数
simulated event PostBeginPlay()
{
	super.PostBeginPlay();

	RegisterToFacade();

	ActorAttributes = new(self) class'ActorAttribute'(ActorAttributes);

	//create a new MIC of the healthbar for this object, so that it can uniquely set the MIC's parameters to its own values.
	MyHealthHUDMatInstance = new(self) class'MaterialInstanceConstant';
	MyHealthHUDMatInstance.SetParent(TheHealthHUDMatTemplate);
}

// 计算血量的百分比
native function float GetHealthPercent();
//{
//	return float(ActorAttributes.HP) / float(ActorAttributes.MaxHP);
//}

//---------------------------------------------------------------
// IMMOActorHUD
//---------------------------------------------------------------

function bool OnlyDrawHUDForOwner(){return false;}

native function DrawHUDPostGFx( HUD H);


native function bool DrawMyHUD( MMOHud H );
//{
//	local Vector screenPos;
//	local float healthPercent;
//	local LinearColor healthColor;
//	local Vector healthColorVec;
//	local Vector objectIconWorldPos;
//	local float cameraDistFromPos;
//	local float iconWidth, iconHeight;
//	local float IconDistanceScale;

//	if(!EnableDrawHealthBar)
//		return false;

//	objectIconWorldPos = Location+(HealthBarPositionOffset>>Rotation);
//	screenPos = H.Canvas.Project(objectIconWorldPos);
//	cameraDistFromPos = VSize(objectIconWorldPos - H.PlayerOwner.PlayerCamera.ViewTarget.POV.Location);
//	IconDistanceScale = FClamp(1.0 - cameraDistFromPos/4000,0.25,1)*(H.Canvas.ClipY / 768.0f)*HealthBarScale;

//	iconWidth = 166*IconDistanceScale;
//	iconHeight = 18*IconDistanceScale;

//	if(!H.IsOnCanvas(screenPos,iconWidth,iconHeight))
//		return false;

//	healthPercent = GetHealthPercent();
//	healthColorVec = VLerp(UnhealthyColor,HealthyColor,healthPercent);
	
//	if(`TimeSince(LastTakeDamageTime) < 2)
//		healthColorVec *= 1 + 13.0*Abs(sin(WorldInfo.TimeSeconds*7));

//	healthColor.R=healthColorVec.X;
//	healthColor.G=healthColorVec.Y;
//	healthColor.B=healthColorVec.Z;

//	MyHealthHUDMatInstance.SetScalarParameterValue('Percent',healthPercent);
//	MyHealthHUDMatInstance.SetVectorParameterValue('BarColor',healthColor);

//	H.Canvas.SetPos(screenPos.x-iconWidth/2,screenPos.y-iconHeight/2);
//	H.Canvas.DrawMaterialTile(MyHealthHUDMatInstance,iconWidth,iconHeight);

//	return true;
//}

event int GetFriendlyMask()
{
	return FriendlyMask;
}

// if processed return true, else false
event ProcessDamage(DamageData Damage)
{
	ActorAttributes.HP -= Damage.DamageValue;

	if(ActorAttributes.HP <= 0)
	{
		ActorDied(none, vect(0,0,0), none, Damage.BaseActor);
	}
	else if(HurtEffectTemplate != none)
	{
		Spawn(HurtEffectTemplate.Class,,,Location,Rotator(Damage.BaseActor.Location-Location),HurtEffectTemplate,true);
		if(GetHealthPercent() < LowHealthParticlePercentThreshold && !LowHealthParticleEffect.bIsActive)
		{
			LowHealthParticleEffect.ActivateSystem();
		}
	}

	//super.TakeDamage( Damage.DamageValue, (Damage.Attacker!=none)?Damage.Attacker.Controller:none, Damage.HitLocation, Damage.HitMomention, none);
}

event bool IsDead()
{
	if(LifeSpan < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// 摧毁事件
event Destroyed()
{
	super.Destroyed();
	//OnDestroy_RemoveFromTargetableList();
}

// 死亡
function ActorDied(Controller EventInstigator, vector HitLocation, class<DamageType> DamageType, Actor DamageCauser)
{
//	local MMOEmitterSpawnable sfx;

	LifeSpan = -1;
	EnableDrawHealthBar = false;

	if(DiedEffectTemplate != none)
	{
		Spawn(DiedEffectTemplate.Class,,,Location,Rotation,DiedEffectTemplate,true);
	}

	Explode();

	PushState('FadeOut');
	//if(LowHealthSound.IsPlaying())
	//	LowHealthSound.Stop();
}

//---------------------------------------------------------------
// 技能碰撞事件
//---------------------------------------------------------------
event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	//super.Touching(Other, OtherComp, HitLocation, HitNormal);
	
	//`log("$$$$$--------$$$$$$$$$ Touch" @Other @HitLocation);

	//if(MMOEmitter(Other) != none)
	//{
	//	self.Move(-HitNormal * 100);
	//}
}

// called for PendingTouch actor after physics completes
event PostTouch( Actor Other )
{
	//`log("$$$$$$--------$$$$$$$$ PostTouch" @Other);
}

event UnTouch( Actor Other )
{
	//`log("$$$$$--------$$$$$$$$$ UnTouch" @Other);
}

event Bump( Actor Other, PrimitiveComponent OtherComp, Vector HitNormal )
{
	//"ActorCollision", 
	//`log("$$$$$--------$$$$$$$$$ Bump" @Other);
}

// 消失碎片
state FadeOut
{
	event PushedState( )
	{
		super.PushedState( );

		FadeLife = 0.0f;
		//`log("$$$$$--------$$$$$$$$$ PushedState");
	}

	event BeginState( Name PreviousStateName )
	{
		super.BeginState(PreviousStateName);

		FadeLife = 0.0f;

		//`log("$$$$$--------$$$$$$$$$ BeginState");
	}

	simulated event Tick( float deltaTime )
	{
		FadeLife += deltaTime;
		if(FadeLife >= FadeOutTime)
		{
			//`log("$$$$$--------$$$$$$$$$ Destroy();");
			
			Destroy();
			PopState();
		}
	}
}

// 注册到Facade中以便查找
native function RegisterToFacade();

native function ETriggerType GetTriggerType();
native function ETrapEventType GetTrapEventType();

native function int GetTriggerID();
native function SetAutoID(int id);

// 取得关联的阻挡框
native function array<DynamicBlockingVolume> GetBlockingVolumes();

// 取得物体大小
native function Box GetObjectServerBounds();

// 取得物体位置
native function vector GetObjectServerPosition();

// 开始状态是否是，开启、关闭、不可用
native function ETriggerInitState GetServerInitState();

// 返回一个调试用的标识名
native function string GetClientName();

// 取得关联的NPC出生点
native function array<NPCSpawnPoint> GetNPCSpawnPoints();

// 取得关联的机关，以便在当前事件区域完成后，激活这些机关
native function array<IServerTrigger> GetLinkedTrigger();

native function int GetDelayTime();

// 触发技能列表
native function array<AbilityEvent> GetAbilityList();

// 触发技能列表
native function TeleportEvent GetTeleportEvent();

native function array<IServerArea> GetLinkedEventArea();

native function int GetLoadingTime();

native function NPCDeadEvent GetNPCDeadEvent();

native function array<TeleportOrig> GetLinkedTeleportList();

defaultproperties
{
	FriendlyMask = 4

	// 添加受伤的粒子组件
	Begin Object Class=ParticleSystemComponent Name=ParticleSystemComponent2
	bAutoActivate=false
	End Object
	Components.Add(ParticleSystemComponent2)
	LowHealthParticleEffect=ParticleSystemComponent2

	//HurtEffectTemplate=MMOEmitterSpawnable'MMOArchetTypes.Emitter_HitStone'
	//DiedEffectTemplate=MMOEmitterSpawnable'MMOArchetTypes.Emitter_StoneExplosion'
	//ActorAttributes = ActorAttribute'MMO_ActorAttribute.DestructibleActor_Stone'


//	TheHealthHUDMatTemplate=MaterialInstanceConstant'DunDefMisc.Menus.TowerHealthBarMat_INST'

	EnableDrawHealthBar=true
	HealthBarScale=0.65
	HealthBarPositionOffset=(Z=10)
	//Physics = PHYS_None
	//bBlockActors=true
	//bCollideActors=true
	//bCollideWorld=true
	//BlockRigidBody=true
	LowHealthParticlePercentThreshold=0.375
	UnhealthyColor=(X=1.5)
	HealthyColor=(Y=1.0)
	LastTakeDamageTime=-10000
	FadeOutTime = 3
}