/****
****
* @todo
* 需要去除这一块
*****/
class MMOServerTrigger extends Actor implements(IServerTrigger, IAbilityDamageable)
	placeable
	native
	ClassGroup(__Server_Old__)
	hidecategories(Object,Debug,Advanced,Physics,CollisionChanged,Attachment,DisplayDebug);

var(MMOServer) editconst int TriggerID;
var(MMOServer) ETriggerType TriggerType;
var(MMOServer) ETrapEventType TrapEventType;

var(MMOServer) ETriggerInitState InitTriggerState;
//var(MMOServer) float CollisionRadius;
//var(MMOServer) float CollisionHeight;

var(MMOServer) array<IServerTrigger> LinkedTrigger;

var(MMOServer_Delay) int DelayTime;

// 关联的阻挡框
var(MMOServer_Blocking) array<DynamicBlockingVolume> AssociatedBlockingVolume;

var(MMOServer_NPCSpawn) array<NPCSpawnPoint> NPCSpawnPoints;

var(MMOServer_NPCDead) NPCDeadEvent NPCDeadEvent;

var(MMOServer_EventArea) array<IServerArea> LinkedEventArea;

var(MMOServer_Skill) array<AbilityEvent> AbilityList;

var(MMOServer_Teleport) TeleportEvent TeleportEvent;
var(MMOServer_LoadingTrigger) int LoadingTime;
var(MMOServer_OpenTeleport) array<TeleportOrig> LinkedTeleportList;

var(MMOClient) CylinderComponent CollisionCylinder;
var(MMOClient) DrawCylinderComponent EditorCollisionCylinder;
var(MMOClient) StaticMeshComponent EditorStaticMeshComponent;

simulated event PostBeginPlay()
{
	super.PostBeginPlay();

	RegisterToFacade();

	//CollisionCylinder.SetCylinderSize(CollisionRadius, CollisionHeight);

	//EditorCollisionCylinder.CylinderRadius = CollisionRadius;
	//EditorCollisionCylinder.CylinderTopRadius = CollisionRadius;
	//EditorCollisionCylinder.CylinderHeight = CollisionHeight;

}

event TakeDamage(int DamageAmount, Controller EventInstigator, vector HitLocation, vector Momentum, class<DamageType> DamageType, optional TraceHitInfo HitInfo, optional Actor DamageCauser)
{
	super.TakeDamage(DamageAmount, EventInstigator, HitLocation, Momentum, DamageType, HitInfo, DamageCauser); 
	`log("_________ MMOServerTriggerObject: TakeDamage" @DamageCauser);
}

// 取得阵营标识，以计算伤害
event int GetFriendlyMask()
{
	return 0;
}

// if processed return true, else false
event ProcessDamage(DamageData Damage)
{
	TakeDamage(Damage.DamageValue, none, vect(0,0,0), vect(0,0,0), none);
}

event bool IsDead()
{
	return false;
}

native function ETriggerType GetTriggerType();
native function ETrapEventType GetTrapEventType();

// 注册到Facade中以便查找
native function RegisterToFacade();

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

cpptext
{
	virtual void MarkPackageDirty( UBOOL InDirty = 1 ) const;
}

DefaultProperties
{
	Begin Object Class=CylinderComponent Name=CollisionCylinder0
		CollisionRadius=40
		CollisionHeight=200
		BlockNonZeroExtent=true
		BlockZeroExtent=true
		BlockActors=true
		CollideActors=true
		LightingChannels=()
		CastShadow=false
		bCastDynamicShadow=false
		bCastHiddenShadow=false
		bCastShadowAsTwoSided=false
		bCastStaticShadow=false
		bAcceptsDecals=false
		bAcceptsDecalsDuringGameplay=false
		bAcceptsDynamicDecals=false
		bAcceptsDynamicDominantLightShadows=false
		bAcceptsDynamicLights=false
		bAcceptsLights=false
		bAcceptsStaticDecals=false
		RBChannel=RBCC_Nothing
	End Object
	CollisionComponent=CollisionCylinder0
	Components.Add(CollisionCylinder0)
	CollisionCylinder=CollisionCylinder0

	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'MMOEditor.ServerTrigger'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="Server"
		//Scale=0.2
	End Object
	Components.Add(Sprite);

	// 添加调试用范围线框 - 远程攻击范围
	Begin Object Class=DrawCylinderComponent  Name=DebugRangeFar0
		CylinderColor=(R=0,G=255,B=0,A=255)
		CylinderRadius=40.0
		CylinderTopRadius=40.0
		CylinderHeight=200.0
		CylinderHeightOffset=0.0
		CylinderSides=32
		bDrawWireCylinder=true
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		HiddenGame=true
		LightingChannels=()
		CastShadow=false
		bCastDynamicShadow=false
		bCastHiddenShadow=false
		bCastShadowAsTwoSided=false
		bCastStaticShadow=false
		bAcceptsDecals=false
		bAcceptsDecalsDuringGameplay=false
		bAcceptsDynamicDecals=false
		bAcceptsDynamicDominantLightShadows=false
		bAcceptsDynamicLights=false
		bAcceptsLights=false
		bAcceptsStaticDecals=false
	End Object
	Components.Add(DebugRangeFar0)
	EditorCollisionCylinder=DebugRangeFar0

	//CollisionHeight=300
	//CollisionRadius=400

	//DrawScale=0.2
	//bCollideActors=TRUE
	//bBlockActors=true
	Begin Object Class=StaticMeshComponent  Name=StaticMeshComponent0
		StaticMesh=FracturedStaticMesh'GamePlayNodeBuddies.3D_Icons.NodeBuddy__BASE_TALL_FRACTURED'	
		BlockNonZeroExtent=true
		BlockZeroExtent=true
		BlockActors=true
		CollideActors=true
		LightingChannels=()
		CastShadow=false
		bCastDynamicShadow=false
		bCastHiddenShadow=false
		bCastShadowAsTwoSided=false
		bCastStaticShadow=false
		bAcceptsDecals=false
		bAcceptsDecalsDuringGameplay=false
		bAcceptsDynamicDecals=false
		bAcceptsDynamicDominantLightShadows=false
		bAcceptsDynamicLights=false
		bAcceptsLights=false
		bAcceptsStaticDecals=false
		RBChannel=RBCC_Nothing
	End Object
	Components.Add(StaticMeshComponent0)
	EditorStaticMeshComponent=StaticMeshComponent0

	Begin Object Class=ServerTriggerEditorComponent  Name=EditorComponent0
	End Object
	Components.Add(EditorComponent0)
	
}
