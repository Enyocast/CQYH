
// qin@snda
class MMOWeatherHelper extends WeatherManager
	native;

struct native WeatherParameters
{
	var float PrecipitationIntensity;

	var float RayleighFactor;
	var float MieFactor;
	var float RayleighScale;
	var float MieScale;

	var Vector WindDirection;
	var float WindStrength;

	structcpptext
	{
	void Interpolate(const FWeatherParameters& SourceParameters, const FWeatherParameters& DestParameters, FLOAT Factor);
	}

	structdefaultproperties
	{
		PrecipitationIntensity=1.0

		RayleighFactor=1.0
		MieFactor=1.0
		RayleighScale=1.0
		MieScale=1.0

		WindStrength=1.0
	}
};

var ParticleSystem RainEffect;
var ParticleSystem SnowEffect;

var transient bool bEnableWeather;
var transient bool bRaining;
var transient bool bSnowing;
var transient bool bStorming;
var transient bool bLightning;

// rain
var transient ParticleSystemComponent RainParticleSystem;
var transient WeatherParameters CurRainParameters;
var transient WeatherParameters SrcRainParameters;
var transient WeatherParameters DstRainParameters;
var transient int MaxRainCount;

// snow
var transient ParticleSystemComponent SnowParticleSystem;
var transient WeatherParameters CurSnowParameters;
var transient WeatherParameters SrcSnowParameters;
var transient WeatherParameters DstSnowParameters;
var transient int MaxSnowCount;

// thunder
var transient DominantDirectionalLight MainLight;
var transient Color MainLightColor;
var transient float MainLightIntensity;
var transient init array<DirectionalLightToggleable> DirectionalLights;
var transient init array<Color> DirectionalLightColors;
var transient init array<float> DirectionalLightIntensities;

var transient Color OldLightmapScale;

var transient int	LightningState;	// 0: no lightning; 1: start; 2: stay; 3: finish.
var transient float	LightningTimer;	// initerval from the beginning of the current state
var transient float	NextLightningInterval;	// 
var transient float NextLightningBrightness;
var transient int	NextLightningNumber;	// number of continous lightnings
var transient float LightningFadeRate;
var transient int	LightningLevel;	// control the lightning frequency, not used yet
var transient int	LightningCount;	// counter of the current continous lightning
var transient float	LightningBrightness;	// current brightness

var() float	LightningStartTime;		// time for the lightning to fadein
var() float LightningHoldTime;		// time for the lightning to stay at the brightest state
var() float LightningFinishTime;	// time for the lightning to fadeout
var() float	LightningIntervalMin;	// min interval between 2 lightnings
var() float LightningIntervalMax;	// max interval between 2 lightnings
var() float	LightningBrightnessMin;	// min lightning brightness
var() float LightningBrightnessMax;	// max lightning brightness
var() Color	LightningColor;			// 

// storm
var transient MaterialEffect StormMaterialEffect;
var transient MaterialInstance StormMaterialInstance;
var transient bool bStormFadingIn;
var transient bool bStormFadingOut;
var transient float StormStartTime;
var transient float StormTransitionTime;
var transient float StormIntensity;
var transient float StormOpacity;
var string SandEffectName;

var transient float WeatherStartTime;
var transient float WeatherTransitionTime;

var transient init array<InstancedFoliageActor>	InstancedFoliages;

cpptext
{
	BOOL IsRaining() const;
	void StartRain(INT level);
	void StopRain();

	BOOL IsSnowing() const;
	void StartSnow(INT level);
	void StopSnow();

	BOOL IsStorming() const;
	void StartStorm(INT level);
	void StopStorm();

	BOOL IsLightning() const;
	void StartLightning(INT level);
	void StopLightning();

	void EnableWeather();
	void DisableWeather();

	void PostBeginPlay();
	void TickSpecial(FLOAT DeltaTime);

	void TickLightning( FLOAT DeltaTime );

	void KeepOldLightingValues();

	void SetFire( const FVector& Center, FLOAT Radius );
}

defaultproperties
{
	RainEffect=ParticleSystem'RainStreakTest.RainStreakPS'
	SnowEffect=ParticleSystem'RainStreakTest.PS_Snow'
	//LightningMaterialTemplate=Material'PPMatEffect.PPlight'
	SandEffectName="SandEffect"

	LightningStartTime=0.02f
	LightningHoldTime=0.05f
	LightningFinishTime=0.15f
	LightningIntervalMin=2.f
	LightningIntervalMax=5.f
	LightningBrightnessMin=5.f
	LightningBrightnessMax=7.f
	LightningColor=(R=190,G=205,B=220)
}
