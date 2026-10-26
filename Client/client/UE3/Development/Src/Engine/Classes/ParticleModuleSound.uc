/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class ParticleModuleSound extends ParticleModuleSoundBase
	native(Particle)
	editinlinenew
	hidecategories(Object);

var(Sound) SoundCue SoundFX;
var()   rawdistributionfloat      StartPlayTimeEdit;
var(Sound) float StartPlayTime;

var(Sound)	bool		bLoop;
var(Sound)	bool		bFollowActor;

var(Sound)	bool		bIgnoreIfActorHidden;

/** This is the percent to play this Sound.  Defaults to 100% (aka 1.0f) **/
var(Sound)   float	    PercentToPlay;
var(Sound)   float		VolumeMultiplier;
var(Sound)	float		PitchMultiplier;

var AudioComponent AudioComp;

var float SoundLifeTime;
var bool bCanPlaySound;

cpptext
{
	virtual void	PostLoad();
	virtual	void	PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	virtual	void	AddModuleCurvesToEditor(UInterpCurveEdSetup* EdSetup);
	virtual void	Spawn(FParticleEmitterInstance* Owner, INT Offset, FLOAT SpawnTime);
	virtual void	Update(FParticleEmitterInstance* Owner, INT Offset, FLOAT DeltaTime);

	/**
	 *	Called when the module is created, this function allows for setting values that make
	 *	sense for the type of emitter they are being used in.
	 *
	 *	@param	Owner			The UParticleEmitter that the module is being added to.
	 */
	virtual void SetToSensibleDefaults(UParticleEmitter* Owner);

	virtual void ProcessSound(UParticleSystemComponent* ParComponent, UBOOL Play);
	void PlaySoundCue();
	void UpdateCurveValue(UDistributionFloatConstantCurve* StartPlayTimeDist);
	virtual void OnCurveKeyMoved();
}

defaultproperties
{
	bSpawnModule=true
	bUpdateModule=true
	bCurvesAsColor=true

	Begin Object Class=DistributionFloatConstantCurve Name=DistributionStartPlayTime
		//ConstantCurve=0.0f;
	End Object
	StartPlayTimeEdit=(Distribution=DistributionStartPlayTime)

	bLoop=false
	bFollowActor=true
	bIgnoreIfActorHidden=true
	PercentToPlay=0
	VolumeMultiplier=1.0
	PitchMultiplier=1.0
}
