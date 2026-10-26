#include "stdafx.h"

IMPLEMENT_CLASS(UDoodadSpawnPointFactory)


AActor* UDoodadSpawnPointFactory::CreateActor( const FVector* const Location, const FRotator* const Rotation, const USeqAct_ActorFactory* const ActorFactoryData )
{
	AActor* NewActor = Super::CreateActor( Location, Rotation, ActorFactoryData );
	if(!NewActor)
	{
		return NULL;
	}

	ADoodadSpawnPoint* NewSMActor = CastChecked<ADoodadSpawnPoint>(NewActor);

	if( DoodadTemplate )
	{
		if(DoodadTemplate->DoodadAvatar && DoodadTemplate->DoodadAvatar->SkeletalMesh)
		{
			NewSMActor->SkelComponent->Scale = (DoodadTemplate->DoodadAvatar->MeshScale * DoodadTemplate->DoodadAvatar->AvatarDrawScale);
			NewSMActor->SkelComponent->SetSkeletalMesh(DoodadTemplate->DoodadAvatar->SkeletalMesh);
		}

		// propagate the actor
		GObjectPropagator->PropagateActor(NewActor);
	}

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
UBOOL UDoodadSpawnPointFactory::CanCreateActor( FString& OutErrorMsg, UBOOL bFromAssetOnly ) 
{ 
	if(DoodadTemplate)
	{	
		return TRUE;
	}
	else 
	{
		OutErrorMsg = TEXT("Error_CouldNotCreateActor_NoDoodadTemplateSelected");
		return FALSE;
	}
}

void UDoodadSpawnPointFactory::AutoFillFields(USelection* Selection)
{
	DoodadTemplate = Selection->GetTop<UDoodad>();
}

FString UDoodadSpawnPointFactory::GetMenuName()
{
	if(DoodadTemplate)
	{
		return FString::Printf( TEXT("%s: %s"), *MenuName, *DoodadTemplate->GetPathName() );
	}
	else
	{
		return MenuName;
	}
}
