//***
//	MMORainStreakActor.uc
//	rain effect actor, could also be used for snow effect
//***

class MMORainStreakActor extends Emitter
	config(Rain)
	hidecategories(Object)
	placeable;

var() Vector	WindDirAndStrength;

defaultproperties
{
	Begin Object Class=ParticleSystemComponent Name=ParticleSystemComponent1
		Template=ParticleSystem'RainStreakTest.RainStreakPS'
		SecondsBeforeInactive=1
	End Object
	ParticleSystemComponent=ParticleSystemComponent1
	Components.Add(ParticleSystemComponent1)
}