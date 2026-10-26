#include "EnginePrivate.h"
#include "EngineClasses.h"
#include "WaterRendering.h"
#include "TessellationRendering.h"

//#include "SceneRenderTargets.h"

IMPLEMENT_CLASS(AWaterActor)

/**
 * Init the helper components 
 */
void AWaterActor::Init()
{
	if( GEngine->SceneCaptureReflectActorMaterial && !ReflectMaterialInst )
	{
		// create new instance
		// note that it has to be RF_Transient or the map won't save
		ReflectMaterialInst = ConstructObject<UMaterialInstanceConstant>( 
			UMaterialInstanceConstant::StaticClass(),
			INVALID_OBJECT, 
			NAME_None, 
			RF_Transient, 
			NULL );

		// init with the parent material
		ReflectMaterialInst->SetParent( GEngine->SceneCaptureReflectActorMaterial );		
	}

	if( StaticMesh && ReflectMaterialInst )
	{
		// assign the material instance to the static mesh plane
		if( StaticMesh->Materials.Num() == 0 )
		{
			// add a slot if needed
			StaticMesh->Materials.Add();
		}
		// only one material entry
		StaticMesh->Materials(0) = ReflectMaterialInst;
	}
}

/**
 * Called when the actor is loaded
 */
void AWaterActor::PostLoad()
{
	Super::PostLoad();

	// initialize components
    Init();	

	// update
	SyncComponents();
}

/**
 * Called when the actor is spawned
 */
void AWaterActor::Spawned()
{
	Super::Spawned();

	// initialize components
    Init();	

	// update
	SyncComponents();
}

/**
 * Called when the actor is destroyed
 */
void AWaterActor::FinishDestroy()
{
	// clear the references to the reflect material instance
	if( StaticMesh )
	{
        for( INT i=0; i < StaticMesh->Materials.Num(); i++ )
		{
			if( StaticMesh->Materials(i) == ReflectMaterialInst )
			{
				StaticMesh->Materials(i) = NULL;
			}
		}
	}
	ReflectMaterialInst = NULL;

	Super::FinishDestroy();
}

/**
 * Sync updated properties
 */
void AWaterActor::SyncComponents()
{
	USceneCaptureReflectComponent* SceneCaptureReflect = Cast<USceneCaptureReflectComponent>(SceneCapture);	

	if( !SceneCaptureReflect )
		return;

	if( ReflectMaterialInst )
	{
		// update the material instance texture parameter
        ReflectMaterialInst->SetTextureParameterValue( FName(TEXT("ScreenTex")), SceneCaptureReflect->TextureTarget );        
	}
}