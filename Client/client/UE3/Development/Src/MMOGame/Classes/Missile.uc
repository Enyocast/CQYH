
class Missile extends Object implements(IExcelable)
	hidecategories(Object)
	native;

var() int Id									<ExportExcel="Both"|DisplayName="Id">;
var() ESPELL_LOCK_TYPE LockType					<ExportExcel="Both"|DisplayName="LockType">;
var() EMISSILE_MOVE_TYPE MoveType				<ExportExcel="Both"|DisplayName="MoveType">;
var() int Speed									<ExportExcel="Both"|DisplayName="Speed">;
var() float LifeTime							<ExportExcel="Both"|Convert="1000"|DisplayName="LifeTime">;
var() int MaxCollisionCount						<ExportExcel="Both"|DisplayName="MaxCollisionCount">;
var() int MaxTargetCountPerCollision			<ExportExcel="Both"|DisplayName="MaxTargetCountPerCollision">;
var() ESPELL_RANGE_TYPE RangeType				<ExportExcel="Both"|DisplayName="RangeType">;
var() int RangeParam1							<ExportExcel="Both"|DisplayName="RangeParam1">;
var() int RangeParam2							<ExportExcel="Both"|DisplayName="RangeParam2">;
var() int RangeParam3							<ExportExcel="Both"|DisplayName="RangeParam3">;
var() int OffsetDirection						<ExportExcel="Both"|DisplayName="OffsetDirection">;
var() int OffsetDistance						<ExportExcel="Both"|DisplayName="OffsetDistance">;

var() int HOffsetGrids							<ExportExcel="Both"|DisplayName="HOffsetGrids">;
var() int VOffsetGrids							<ExportExcel="Both"|DisplayName="VOffsetGrids">;

var() float Delay	    						<ExportExcel="Both"|Convert="1000"|DisplayName="Delay">;
var() float Interval							<ExportExcel="Both"|Convert="1000"|DisplayName="Interval">;
var() int Height    							<ExportExcel="Both"|DisplayName="Height">;
var() bool NotMultiEffeect						<ExportExcel="Both"|DisplayName="NotMultiEffeect">;
var() bool NotHitLastTarget						<ExportExcel="Both"|DisplayName="NotHitLastTarget">;

var() SeqAct_Modifier OnCollision				<DisplayName="OnCollision">; //OnScan
var() SeqAct_Modifier OnRemove					<DisplayName="OnRemove">;
var() SeqAct_Modifier OnInit					<DisplayName="OnInit">;
var() SeqAct_Modifier OnCreate					<DisplayName="OnCreate">;
var() SeqAct_Modifier OnTimeup					<DisplayName="OnTimeup">;
var() SeqAct_Modifier OnCharEnter				<DisplayName="OnCharEnter">;
var() SeqAct_Modifier OnCharLeave				<DisplayName="OnCharLeave">;

var int OnCollisionID							<ExportExcel="Both">;
var int OnRemoveID								<ExportExcel="Both">;
var int OnInitID								<ExportExcel="Both">;
var int OnCreateID								<ExportExcel="Both">;
var int OnTimeupID								<ExportExcel="Both">;
var int OnCharEnterID							<ExportExcel="Both">;
var int OnCharLeaveID							<ExportExcel="Both">;


var(Client) float DelayTime										<DisplayName="DelayTime">;
var(Client) name SocketName <DynamicList="SocketList">;

var(Emitter) ParticleSystem ParticleSystemTemplate				<DisplayName="ParticleSystemTemplate">;
var(Emitter) float Scale;

var(Sound) SoundCue FlySoundCue;

/** Light from the Emitter */
var(Light) editinline PointLightComponent MyPointLightComponent	<DisplayName="MyPointLightComponent">;
/** How long the light should stay in existance, if enabled. 
 *  Zero keeps it active for the entire lifetime of the emitter. */
var(Light) float LightLifeSpan									<DisplayName="LightLifeSpan">;
/** How long after spawning the Light should take to interpolate up to full brightness. */
var(Light) float LightFadeUpTime								<DisplayName="LightFadeUpTime">;
/** How long BEFORE lifespan expires the Light should take to interpolate down to zero brightness. */
var(Light) float LightFadeOutTime								<DisplayName="LightFadeOutTime">;

var(Effect) editinline array<AbilityComponent> EffectComponents;


event SetDataToProjectile(MMOEmitter ProActor)
{
	if(ProActor == none)
	{
		return;
	}
	if(ParticleSystemTemplate != none)
	{
		ProActor.SetTemplate(ParticleSystemTemplate, false);
	}

	if(MyPointLightComponent != none)
	{
		ProActor.MyPointLightComponent = new MyPointLightComponent.Class(MyPointLightComponent);
		ProActor.LightFadeUpTime = LightFadeUpTime;
		ProActor.LightFadeOutTime = LightFadeOutTime;
		ProActor.LightLifeSpan = LightLifeSpan;
	}
}



event ScriptExportExcelHeaders(out array<string> Header, out array<string> DefaultValues)
{
}

event ScriptDataToExcel(out array<string> Row)
{
}

event ScriptImportFromExcel(array<string> Values)
{
}

native function ImportFromExcel(array<string> values);
native function ExportExcelHeaders(out array<string> Header, out array<string> DefaultValues);
native function DataToExcel(out array<string> Row);
native function bool IsNeedArchetype();
native function InitDataToExcel();

cpptext
{	
	virtual FString GetDetailedDescription( INT InIndex )
	{
		switch( InIndex )
		{
		case 0:
			return FString::Printf(TEXT("%d"), Id);
			break;
		}

		return TEXT("");
	}
}

DefaultProperties
{
	LightLifeSpan=1.0
	LightFadeUpTime=0.1
	LightFadeOutTime=0.1
	DelayTime=0.2
	Scale=1.0
	SocketName=None
}
