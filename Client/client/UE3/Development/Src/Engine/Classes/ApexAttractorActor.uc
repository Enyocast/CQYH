// NVCHANGE_BEGIN: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor
/*=============================================================================
	ApexAttractorActor.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexAttractorActor extends Actor
	native(ApexFieldSampler)
	placeable
	dependson(ApexAttractorComponent);
	
var() ApexAttractorComponent AttractorComponent;

cpptext
{
	virtual void PreEditChange(UProperty *PropertyAboutToChange);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	virtual void Spawned();

	virtual void InitRBPhys();
	virtual void InitRBPhysEditor();

private:
	void AttachAttractorComponent();
	void DetachAttractorComponent();
}

/** Handling Toggle event from Kismet. */
simulated function OnToggle(SeqAct_Toggle inAction)
{
	if (inAction.InputLinks[0].bHasImpulse)
	{
		AttractorComponent.setEnabled(TRUE);
	}
	else if (inAction.InputLinks[1].bHasImpulse)
	{
		AttractorComponent.setEnabled(FALSE);
	}
	else if (inAction.InputLinks[2].bHasImpulse)
	{
		AttractorComponent.setEnabled(!AttractorComponent.bEnabled);
	}
}

defaultproperties
{
	TickGroup=TG_PreAsyncWork

	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'EditorResources.S_RadForce'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
	End Object
	Components.Add(Sprite)

	Begin Object Class=ApexAttractorComponent Name=NewAttractorComponent
	End Object
	AttractorComponent = NewAttractorComponent

	bEdShouldSnap=True
	bStatic=false
	bNoDelete=false
}
// NVCHANGE_END: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor

