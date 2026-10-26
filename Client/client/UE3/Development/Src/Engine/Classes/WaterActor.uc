class WaterActor extends Actor
	placeable
	native
	//hidecategories(Object,Debug,Advanced,Physics,CollisionChanged,Attachment,DisplayDebug)
	ClassGroup(__MMO__);

var() const editconst WaterComponent WaterComponent;

/** component that renders the scene to a texture */
var() const SceneCaptureComponent SceneCapture;

/** material instance used to apply the target texture to the static mesh */
var transient MaterialInstanceConstant ReflectMaterialInst;

/** draws the face using a static mesh */
var() const StaticMeshComponent StaticMesh;

var(Mesh) interp float WaterHeightBumpScale<UIMin=0 | UIMax=100>;
var(Mesh) interp float HeightFieldSize<UIMin=12800 | UIMax=819200>;

var(WaterColor) interp LinearColor WaterDeepColor;
var(WaterColor) interp float WaterColorIntensityX<UIMin=0 | UIMax=1>;
var(WaterColor) interp float WaterColorIntensityY<UIMin=0 | UIMax=1>;

var(WaterColor) interp LinearColor WaterScatterColor;
var(WaterColor) interp float WaterScatterColorPower<UIMin=1 | UIMax=64>;

var(WaterColor) interp LinearColor WaterSpecularColor;
var(WaterColor) interp float WaterSpecularIntensity<UIMin=0 | UIMax=10>;
var(WaterColor) interp float WaterSpecularPower<UIMin=1 | UIMax=4096>;

var(WaterColor) interp LinearColor ReflectionIntensity;
var(WaterColor) interp float WaterScatterColorIntensity;

var() bool	DoTessellation;

simulated event PostBeginPlay()
{
	super.PostBeginPlay();
}

cpptext
{
	// SceneCaptureActor interface

	/**
	* Update any components used by this actor
	*/
	virtual void SyncComponents();

	// AActor interface

	virtual void Spawned();

	// UObject interface

	virtual void FinishDestroy();
	virtual void PostLoad();

private:

	/**
	* Init the helper components
	*/
	virtual void Init();

}

DefaultProperties
{
	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'MMOEditor.ServerTrigger'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="MMO"
		//Scale=0.2
	End Object
	Components.Add(Sprite);
	

	Begin Object Class=WaterComponent  Name=WaterComponent0
	End Object
	WaterComponent=WaterComponent0;
	Components.Add(WaterComponent0)

	// uses reflection scene capture component
	// this is needed to actually capture the scene to a texture
 	Begin Object Class=SceneCaptureReflectComponent Name=SceneCaptureReflectComponent0
 		bSkipUpdateIfTextureUsersOccluded=true
 	End Object
 	SceneCapture=SceneCaptureReflectComponent0
 	Components.Add(SceneCaptureReflectComponent0)

	// used to apply the reflection material for visualization
	Begin Object Class=StaticMeshComponent Name=StaticMeshComponentR
		HiddenGame=true
		HiddenEditor=true
		CastShadow=false
		bAcceptsLights=false
		CollideActors=false
		Scale3D=(X=4.0,Y=4.0,Z=4.0)
		StaticMesh=StaticMesh'EditorMeshes.TexPropPlane'
	End Object
	StaticMesh=StaticMeshComponentR
	Components.Add(StaticMeshComponentR)

	Rotation=(Pitch=16384,Roll=0,Yaw=0)

	WaterDeepColor=(R=0.1,G=0.4,B=0.7,A=1)
	WaterScatterColor=(R=0.3,G=0.7,B=0.6,A=1)
	WaterScatterColorPower=8

	WaterSpecularColor=(R=1,G=1,B=1,A=1)
	WaterSpecularIntensity=100
	WaterSpecularPower=1000

	WaterColorIntensityX=0.1
	WaterColorIntensityY=0.2

	WaterHeightBumpScale=1
	HeightFieldSize=512
	ReflectionIntensity=(R=0.6,G=0.6,B=1,A=1)
	WaterScatterColorIntensity=0.7

	DoTessellation=true
}