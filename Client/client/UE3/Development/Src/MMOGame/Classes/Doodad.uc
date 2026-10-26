//=============================
// MMODoodad 
//场景中简单交互物件 类似于DropItem
//=============================

class Doodad extends Object implements(IExcelable, IReferenceID, IMMOActor)
	dependson(TypeDefine)
	dependson(AvatarData)
	dependson(ServerEnum)
	dependson(NPC)
	hidecategories(Object,Debug,Advanced,Physics,CollisionChanged,Attachment,DisplayDebug,Display,Movement,Collision)
	native;

//InstanceID 
//暂留 实际用DropItemActor的Id 
var int DoodadID; 
var SkeletalMeshComponent SkelComponent;
//TemplateID
//var(Item) int DoodadTemplateID; 
var(DoodadCollision) bool EnableCollision <DisplayName="开启阻挡" | ExportExcel="Client">;
var() Texture2D DisplayIcon				                        <DisplayName="DisplayIcon" | ExportExcel="Client">;
var() name DoodadName				                            <DisplayName="DoodadName" | ExportExcel="Client">;
var() name AnimIdle				                                <DisplayName="AnimIdle" | ExportExcel="Client">;
var() name AnimOpen				                                <DisplayName="AnimOpen" | ExportExcel="Client">;
var() name AnimClose				                            <DisplayName="AnimClose" | ExportExcel="Client">;
var() name AnimDie				                                <DisplayName="AnimDie" | ExportExcel="Client">;

var() init string Description				                    <DisplayName="Description" | ExportExcel="Client">;
var() ParticleSystem ActiveEffectTemplate                       <ExportExcel="Client">;
var() float ActiveEffectScale                                   <ExportExcel="Client">;
//var() SkeletalMesh DoodadMesh				                    <DisplayName="DoodadMesh">;
var() bool IsDelay					                            <DisplayName="IsDelay" | ExportExcel="Client">;
var() float Delay					                            <DisplayName="Delay" | ExportExcel="Client">;
var bool IsDestroy;
var(AvatarData) AvatarData DoodadAvatar			                <DisplayName="DoodadAvatar" | ExportExcel="Client">;

var() float DurationBeforeDestroy                               <ExportExcel="Client">;
var() float DestructForceScale                                  <ExportExcel="Client">;
//Avatar Data

var(Actions) editinline array<AbilityComponent> DeathEffectList;
var(Actions) editinline array<AbilityComponent> HitEffectList;
var(Actions) editinline array<AbilityComponent> OnSpawnEffectList;

var(MMOServer) int ID				                            <DisplayName="ID" | ExportExcel="Both">;
var(MMOServer) int Level <ExportExcel="Both">;
var(MMOServer) string DisplayName		                        <DisplayName="Name" | ExportExcel="Client">;
var(MMOServer) EDOODAD_TYPE DoodadType		                    <DisplayName="DoodadType" | ExportExcel="Both">;
var(MMOServer) EDOODAD_SUB_TYPE	DoodadSubType	                <DisplayName="DoodadSubType" | ExportExcel="Both">;
var(MMOServer) int OperateDuration                              <DisplayName="OperateDuration" | ExportExcel="Both">;
var(MMOServer) int MinOperateCount                              <DisplayName="MinOperateCount" | ExportExcel="Both">;
var(MMOServer) int MaxOperateCount                              <DisplayName="MaxOperateCount" | ExportExcel="Both">;
var(MMOServer) string ScriptName		                        <DisplayName="ScriptName" | ExportExcel="Server">;

var(MMOServer) int RequireItemID                                <ExportExcel="Server">;
var(MMOServer) bool CostItem                                    <ExportExcel="Server">;
//var(MMOServer) Quest RequireQuestID                           <ExportExcel="23">;
var(MMOServer) init string RequireVarID                         <ExportExcel="Both">;
var(MMOServer) init string RequireVarValue                      <ExportExcel="Both">;
var(MMOServer) NPCTemplate SpawnNpcID                           <ExportExcel="Server">;
var(MMOServer) int SpawnNpcChance                               <ExportExcel="Server" | ClampMin=0 | ClampMax=10000>;
var(MMOServer) int AuraID                                       <ExportExcel="Server">;
var(MMOServer) float LifeTime                                   <ExportExcel="Server"|Convert="1000">;
var(MMOServer) int Radius                                       <ExportExcel="Both">;
var(MMOServer) init string   BodyType                           <ExportExcel="Both">;


// 此对象被打开时角色播放的动作组，引用动作组Doodad_RoleAnimGroup.upk，需先加载该UPK
//var() init string	RoleAnimGroup                               <DisplayName="Doodad RoleAnimGroup" | DynamicList="Doodad_RoleAnimGroup" | ExportExcel="Client">;

var() name BeginAnimOpener;
var() name LoopAnimOpener;
var() name EndAnimOpener;

var() bool bNeedPlayDoodadLoopSound;

// 是否在鼠标移上去的时候显示名字
var() bool DoododNameDisplay                                    <ExportExcel="Client">;

// 鼠标移上去后的指针类型及打开后释放特效
var() EMMOCursorType DoododCursorType                           <ExportExcel="Client">;

// 此对象被采后播放的特效
var() ParticleSystem DoodadEndEffect                            <ExportExcel="Client">;

var(UI) edittextbox init string TipsText                        <ExportExcel="Client">;
var(UI) Vector TipsPosOffset;
// 此对象被摧毁时的音效类型（需要设置gameplaydata中的DoodadSndList与此匹配）
//var(Sound) EItemMaterialType DoodadSoundType;

native function EActorClassType GetActorType() const;
event ScriptExportExcelHeaders(out array<string> Header, out array<string> DefaultValues){}
event ScriptDataToExcel(out array<string> Row){}

native function ExportExcelHeaders(out array<string> Header, out array<string> DefaultValues);
native function DataToExcel(out array<string> Row);
native function ImportFromExcel(array<string> values);
event ScriptImportFromExcel(array<string> Values){}
native function InitDataToExcel();

native function int GetTemplateID() const;

cpptext
{	
	virtual FString GetDetailedDescription( INT InIndex )
	{
		switch( InIndex )
		{
		case 0:
			return FString::Printf(TEXT("%d"), ID);
			break;

		case 1:
			return FString::Printf(TEXT("%s"), *DoodadName.ToString());
			break;

		case 2:
			return FString::Printf(TEXT("%s"), *Description);
			break;
		}

		return TEXT("");
	}
	//virtual void GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values);
}


defaultproperties
{
	AnimIdle="Idle"
	AnimOpen="Open"
	AnimClose="Close"
	AnimDie="Death"
	IsDelay=false
	Delay=1.0
	IsDestroy=false
	ActiveEffectScale=1.0
	BeginAnimOpener=OpenDoodadStart
	LoopAnimOpener=OpenDoodadLoop
	EndAnimOpener=OpenDoodadEnd
	bNeedPlayDoodadLoopSound=false
	EnableCollision=true
	/*
	Begin Object Class=StaticMeshComponent Name=StaticMeshComponent0
		StaticMesh=StaticMesh'Pickups.jump_pad.S_Pickups_Jump_Pad'
		CollideActors=false
		CastShadow=FALSE
		bCastDynamicShadow=FALSE
		bAcceptsLights=TRUE
		bForceDirectLightMap=TRUE
		LightingChannels=(BSP=TRUE,Dynamic=FALSE,Static=TRUE,CompositeDynamic=TRUE)
		//LightEnvironment=JumpPadLightEnvironment
	End Object
 	Components.Add(StaticMeshComponent0)
	*/
	/*
	Begin Object Class=UTParticleSystemComponent Name=ParticleSystemComponent1
		Translation=(X=0.0,Y=0.0,Z=-35.0)
		Template=particleSystem'Pickups.jump_pad.P_Pickups_Jump_Pad_FX'
		bAutoActivate=true
		SecondsBeforeInactive=1.0f
	End Object
	Components.Add(ParticleSystemComponent1)
	*/
    DoododNameDisplay = true;
    DoododCursorType=EMC_Pick;

	DurationBeforeDestroy=5.0f
	DestructForceScale=1.0f

	TipsPosOffset=(x=0,y=0,z=100)
	Begin Object Class=AbilityComp_MaterialEffect Name=DefaultHitMatEffect
		EffectType=EMET_ChangeMaterialProperty
		EffectTemplateId=2
	End Object
	HitEffectList(0)=DefaultHitMatEffect

	BodyType="E_body_0x0"

}