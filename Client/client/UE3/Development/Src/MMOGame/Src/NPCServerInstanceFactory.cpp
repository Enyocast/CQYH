#include "stdafx.h"

IMPLEMENT_CLASS(UNPCServerInstanceFactory)


AActor* UNPCServerInstanceFactory::CreateActor( const FVector* const Location, const FRotator* const Rotation, const USeqAct_ActorFactory* const ActorFactoryData )
{
	AActor* NewActor = Super::CreateActor( Location, Rotation, ActorFactoryData );
	if(!NewActor)
	{
		return NULL;
	}

	ANPCServerInstance* NewSMActor = CastChecked<ANPCServerInstance>(NewActor);
#if 0
	if( NPCTemplate )
	{
		// Term Component
		NewSMActor->ClearComponents();

		// Change properties
		NewSMActor->Template = NPCTemplate;
		NewSMActor->RefresAvatarInEditor();

		// propagate the actor
		GObjectPropagator->PropagateActor(NewActor);
	}
#else
	if( NPCTemplateNew )
	{
		// Term Component
		NewSMActor->ClearComponents();

		// Change properties
		NewSMActor->TemplateNew = NPCTemplateNew;
		NewSMActor->RefresAvatarInEditor();

		// propagate the actor
		GObjectPropagator->PropagateActor(NewActor);
	}
#endif

	return NewSMActor;
}

/**
 * If the ActorFactory thinks it could create an Actor with the current settings.
 * Can Used to determine if we should add to context menu or if the factory can be used for drag and drop.
 *
 * @param	OutErrorMsg		Receives localized error string name if returning FALSE.
 * @param	bFromAssetOnly	If true, the actor factory will check that a valid asset has been assigned from selection.  If the factory always requires an asset to be selected, this param does not matter
 * @return	True if the actor can be created with this factory
 */
UBOOL UNPCServerInstanceFactory::CanCreateActor( FString& OutErrorMsg, UBOOL bFromAssetOnly ) 
{ 
	if(NPCTemplateNew)
	{	
		return TRUE;
	}
	else 
	{
		OutErrorMsg = TEXT("Error_CouldNotCreateActor_NoNPCTemplateSelected");
		return FALSE;
	}
}

void UNPCServerInstanceFactory::AutoFillFields(USelection* Selection)
{
	//NPCTemplate = Selection->GetTop<ANPC>();
	NPCTemplateNew = Selection->GetTop<UNPCTemplate>();
}

FString UNPCServerInstanceFactory::GetMenuName()
{
	if(NPCTemplateNew)
	{
		return FString::Printf( TEXT("%s: %s"), *MenuName, *NPCTemplateNew->GetPathName() );
	}
	else
	{
		return MenuName;
	}
}
