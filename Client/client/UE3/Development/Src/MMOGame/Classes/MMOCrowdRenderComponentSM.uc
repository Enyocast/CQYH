// crowd renderer for SMs
class MMOCrowdRenderComponentSM extends ParticleSystemComponent
	native
	//editinlinenew
	hidecategories(Object)
	hidecategories(Physics)
	hidecategories(Collision)
	ClassGroup(__Crowd__);
	//dependson(ParticleSystemComponent);

var transient ParticleModuleLocationCrowdSystem	PSModule;
var MMOCrowdSystem	OwnerSystem;

cpptext
{
	virtual void Attach();
	virtual void Tick( FLOAT DeltaTime );

	void Init( const AMMOCrowdSystem* cs );
}

//defaultproperties
//{
//}