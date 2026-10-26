/**
* MMORenderOnlyActor.cpp
* a rendering-only clone of MMOActors
*/

#include "MMOPrerequisites.h"
#include "MMOGameClasses.h"

IMPLEMENT_CLASS(AMMORenderOnlyActor)

// todo: iterate through all equipments to fetch texture layer information
void AMMORenderOnlyActor::Clone( AMMOActor* baseActor )
{
	if( baseActor == NULL )
		return;

	// create main mesh component if not exist yet
	if( MainMesh == NULL )
	{
		MainMesh = Cast<USkeletalMeshComponent>( StaticConstructObject(
			USkeletalMeshComponent::StaticClass(), GetTransientPackage(), NAME_None, RF_Transient ) );
		if( MainMesh == NULL )
		{
			return;
		}
	}

	// set main mesh
	MainMesh->SetSkeletalMesh( baseActor->Mesh->SkeletalMesh );

	// init mesh list if needs
	if( EquipMeshList.Num() == 0 )
	{
		EquipMeshList.AddZeroed( EBMT_None );
	}
	else
	{
		// clear mesh list
		for( INT i = 0; i < EquipMeshList.Num(); ++i )
			EquipMeshList(i) = NULL;
	}

	// clone equip mesh list
	if( baseActor->ItemManager != NULL )
	{
		INT count = baseActor->ItemManager->CurrentMeshList.Num();
		//Check( count == EBMT_None );
		for( INT i = 0; i < count; ++i )
		{
			if( i >= EBMT_None )
				break;
			EquipMeshList(i) = baseActor->ItemManager->CurrentMeshList(i);
		}

		// merge body parts
		if( count > 0 )
			MergeEquipMeshes();

		// put on other parts
		for( INT i = EBMT_NoMerge + 1; i < EBMT_None; ++i )
		{
			TakeOn( EquipMeshList(i) );
		}
	}
}

void AMMORenderOnlyActor::AddEquipMeshByTemplate( UEquipMesh* temp, INT idx )
{
	if( idx < 0 || idx >= EBMT_None )
		return;

	UEquipMesh* pNewMesh = Cast<UEquipMesh>( StaticConstructObject(
			UEquipMesh::StaticClass(), GetTransientPackage(), NAME_None, RF_Transient, temp ) );

	EquipMeshList(idx) = pNewMesh;
}

void AMMORenderOnlyActor::MergeEquipMeshes()
{
}

void AMMORenderOnlyActor::TakeOn( UEquipMesh* em )
{
	//if( em == NULL || em->PrimComponent == NULL )
	//	return;

	//if( em->ResourceType == ECRT_SkeletalMesh )
	//{

	//}
	//else if( em->ResourceType == ECRT_StaticMesh )
	//{
	//}
}

void AMMORenderOnlyActor::TakeOff( UEquipMesh* em )
{
	//if( em == NULL || em->PrimComponent == NULL )
	//	return;
}