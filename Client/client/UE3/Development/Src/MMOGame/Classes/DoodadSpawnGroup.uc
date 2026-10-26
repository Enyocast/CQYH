// MMONPCSpwanGroup
//NPC出生点群组
//hemu@snda 120424

class DoodadSpawnGroup extends Actor	
	placeable
	native
	hidecategories(Object,Debug,Advanced,Physics,CollisionChanged,Attachment,DisplayDebug)
	ClassGroup(__Server__);

//具体模板信息
struct native DoodadData
{
	var() Doodad  Doodad;
	var() int     nWeight;
};


//var Texture2D SpawnGroupSpriteTex;
var(MMOServer_DoodadSpawn) editoronly int GroupID;
// 自动编号的服务器用ID
var(MMOServer_DoodadSpawn) editoronly editconst int AutoServerID;

// 自动出生，如果要由Kismet控制需要设置为false
var(MMOServer_DoodadSpawn) editoronly bool IsAutoSpawn;
//自动重生，同样， 如果要由Kismet控制需要设置为false
var(MMOServer_DoodadSpawn) editoronly bool IsAutoReSpawn;

// 手动配置的出生组ID，NPC将归组到这个ID上
//var(MMOServer_NPCSpawn) int NPCSpawnGroupId;
var(MMOServer_DoodadSpawn) editoronly int   RespawnInterval;
//手动配置怪物出生几率
var(MMOServer_DoodadSpawn) editoronly int MaxConcurrentPoint;

// Doodad模板引用
var(MMOServer_DoodadSpawn)  editoronly array<DoodadData> DoodadList;

//关联的出生点
var(MMOServer_DoodadSpawn) editoronly array<DoodadSpawnPoint> DoodadSpawnPoints;

//显示组件
var(MMOClient) editoronly CylinderComponent CollisionCylinder;
var(MMOClient) editoronly DrawCylinderComponent EditorCollisionCylinder;
var(MMOClient) editoronly StaticMeshComponent EditorStaticMeshComponent;

var editoronly MMONpcSpawnGroupEditorComponent EditorComponent;

// 取得关联的NPC出生点
native function array<DoodadSpawnPoint> GetDoodadSpawnPoints();
// 取得物体位置
native function vector GetObjectServerPosition();

cpptext
{
	
	virtual INT GetServerID(){ return AutoServerID; }
	virtual INT GetObjectServerType() const { return (INT)kotSpawnGroup; }
	virtual UBOOL NeedsLoadForClient() const { return FALSE; } // oscar@snda 永远不在游戏中加载
}
native function    IniSpirite();
simulated event PostBeginPlay()
{
	super.PostBeginPlay();
	IniSpirite();
}
DefaultProperties
{
//	SpawnGroupSpriteTex=Texture2D'MMOEditor.ServerTrigger'

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
		Sprite=Texture2D'MMOEditor.DoodadSpawnGroup'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="Server"
		//Scale=0.2
	End Object
	Components.Add(Sprite);

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
	End Object
	Components.Add(StaticMeshComponent0)
	EditorStaticMeshComponent=StaticMeshComponent0

	Begin Object Class=MMONpcSpawnGroupEditorComponent  Name=EditorComponent0
	End Object
	EditorComponent=EditorComponent0
	Components.Add(EditorComponent0)

	IsAutoSpawn=true
	//NPCSpawnGroupId=1

}
