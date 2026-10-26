// NVCHANGE_BEGIN: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor
/*=============================================================================
	ApexGridActor.uc: APEX integration.
	Copyright 2008-2011 NVIDIA Corporation.
=============================================================================*/

class ApexGridActor extends Actor
	native(ApexFieldSampler)
	placeable
	dependson(ApexGridComponent);
	
var() ApexGridComponent GridComponent;

cpptext
{
	virtual void PreEditChange(UProperty *PropertyAboutToChange);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	virtual void Spawned();

	virtual void InitRBPhys();
	virtual void InitRBPhysEditor();

private:
	void AttachGridComponent();
	void DetachGridComponent();
}

/** Handling Toggle event from Kismet. */
simulated function OnToggle(SeqAct_Toggle inAction)
{
	if (inAction.InputLinks[0].bHasImpulse)
	{
		GridComponent.setEnabled(TRUE);
	}
	else if (inAction.InputLinks[1].bHasImpulse)
	{
		GridComponent.setEnabled(FALSE);
	}
	else if (inAction.InputLinks[2].bHasImpulse)
	{
		GridComponent.setEnabled(!GridComponent.bEnabled);
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

	Begin Object Class=ApexGridComponent Name=NewGridComponent
	End Object
	GridComponent = NewGridComponent

	bEdShouldSnap=True
	bStatic=false
	bNoDelete=false
}
// NVCHANGE_END: JCAO - US10286 Add ApexAttactorActor, ApexJetActor and ApexGridActor
