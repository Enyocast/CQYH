// NVCHANGE_BEGIN: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor
/*=============================================================================
	ApexJetActor.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexJetActor extends Actor
	native(ApexFieldSampler)
	placeable
	dependson(ApexJetComponent);

var() ApexJetComponent JetComponent;

cpptext
{
	virtual void PreEditChange(UProperty *PropertyAboutToChange);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	virtual void Spawned();

	virtual void InitRBPhys();
	virtual void InitRBPhysEditor();

private:
	void AttachJetComponent();
	void DetachJetComponent();
}

/** Handling Toggle event from Kismet. */
simulated function OnToggle(SeqAct_Toggle inAction)
{
	if (inAction.InputLinks[0].bHasImpulse)
	{
		JetComponent.setEnabled(TRUE);
	}
	else if (inAction.InputLinks[1].bHasImpulse)
	{
		JetComponent.setEnabled(FALSE);
	}
	else if (inAction.InputLinks[2].bHasImpulse)
	{
		JetComponent.setEnabled(!JetComponent.bEnabled);
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

	Begin Object Class=ApexJetComponent Name=NewJetComponent
	End Object
	JetComponent = NewJetComponent

	bEdShouldSnap=True
	bStatic=false
	bNoDelete=false
}
// NVCHANGE_END: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor
