/*
* MMOCrowdRendererSM.uc
*/
class MMOCrowdRendererSM extends Emitter
	native
	hidecategories(Object)
	ClassGroup(__Crowd__);

var(Crowd) MMOCrowdSystem	CrowdSystem;

var ParticleModuleLocationCrowdSystem	PSModule;

native function Init();

simulated function PostBeginPlay()
{
//	local ParticleLODLevel pll;
//	local ParticleModule pm;

	super.PostBeginPlay();

	if( CrowdSystem == none )
	{
		`log( "[MMO Debug] Crowd system renderer has no system assigned." );
		return;
	}

	Init();

	if( PSModule == none )
	{
		`log( "[MMO Deubg] Failed to find crowd system module in emitter"@self );
		return;
	}

	if( PSModule.ParticleLocations.Length != CrowdSystem.CrowdInstanceData.Length )
	{
		`Log( "[MMO Debug] Crowd system has different instance number than its renderer." );
	}
}

event Tick( float DeltaTime )
{
	local MMOCrowdInstance inst;
	local int i;

	//if( PSModule != none && CrowdSystem != none )
	//{
		i = 0;
		foreach CrowdSystem.CrowdInstanceData( inst )
		{
			//if( i < PSModule.ParticleLocations.Length )
			//{
				PSModule.ParticleLocations[i] = inst.Location;
			//}
			++i;
		}
	//}
}

defaultproperties
{
}