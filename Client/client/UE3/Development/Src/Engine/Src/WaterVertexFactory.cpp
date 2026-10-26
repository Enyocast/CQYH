#include "EnginePrivate.h"
#include "WaterVertexFactory.h"

#if WITH_WATER

class FWaterVertexFactoryShaderParameters : public FVertexFactoryShaderParameters
{
public:

	virtual void Bind(const FShaderParameterMap& ParameterMap)
	{
		WorldToLocalParameter.Bind(ParameterMap,TEXT("WorldToLocal"), TRUE);
		LocalToWorldParameter.Bind(ParameterMap,TEXT("LocalToWorld"), TRUE);
	}

	virtual void Serialize(FArchive& Ar)
	{
		Ar << WorldToLocalParameter;
		Ar << LocalToWorldParameter;
	}

	virtual void Set(FShader* VertexShader,const FVertexFactory* VertexFactory,const FSceneView& View) const
	{
	}

	virtual void SetMesh(FShader* VertexShader, const FMeshBatch& Mesh, INT BatchElementIndex, const FSceneView& View) const
	{
//		SCOPE_CYCLE_COUNTER(STAT_LandscapeVFDrawTime);
		const FMeshBatchElement& BatchElement = Mesh.Elements(BatchElementIndex);
		//const FLandscapeBatchElementParams* BatchElementParams = (FLandscapeBatchElementParams*)BatchElement.ElementUserData;
		//const FLandscapeSubsectionParams* SubsectionParam = BatchElementParams ? BatchElementParams->SubsectionParam : NULL;
//		check(SubsectionParam);

		SetVertexShaderValue(VertexShader->GetVertexShader(), WorldToLocalParameter, BatchElement.WorldToLocal);
		SetVertexShaderValue(VertexShader->GetVertexShader(), LocalToWorldParameter, BatchElement.LocalToWorld);
	}

private:
	INT	TessellationLevel;
	FShaderParameter WorldToLocalParameter;
	FShaderParameter LocalToWorldParameter;
};





//------------------------------------------------------------------------
// FWaterVertexFactory
//------------------------------------------------------------------------
void FWaterVertexFactory::InitRHI()
{
	// list of declaration items
	FVertexDeclarationElementList Elements;

	// position decls
	Elements.AddItem(AccessStreamComponent(Data.PositionComponent, VEU_Position));

	// create the actual device decls
	InitDeclaration(Elements,FVertexFactory::DataType(),FALSE,FALSE, FALSE);
}
//------------------------------------------------------------------------
FVertexFactoryShaderParameters* FWaterVertexFactory::ConstructShaderParameters(EShaderFrequency ShaderFrequency)
{
	//switch( ShaderFrequency )
	//{
	////case SF_Vertex:
	////	return new FWaterVertexFactoryShaderParameters();
	////	break;
	////case SF_Pixel:
	////	return new FWaterVertexFactoryPixelShaderParameters();
	////	break;
	//default:
	//	return NULL;
	//}

	return new FWaterVertexFactoryShaderParameters();
}
//------------------------------------------------------------------------
void FWaterVertexFactory::Copy( const FWaterVertexFactory& Other )
{
	//SetSceneProxy(Other.GetSceneProxy());
	ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
		FWaterVertexFactoryCopyData,
		FWaterVertexFactory*,VertexFactory,this,
		const DataType*,DataCopy,&Other.Data,
	{
		VertexFactory->Data = *DataCopy;
	});	
	BeginUpdateResourceRHI(this);
}
//------------------------------------------------------------------------
class FDecalVertexFactoryBase* FWaterVertexFactory::CreateDecalVertexFactory() const
{
	return NULL;
}
//------------------------------------------------------------------------
void FWaterVertexFactory::GetStaticBatchElementVisibility( const class FSceneView& View, const struct FMeshBatch* Batch, TArray<INT>& BatchesToRender ) const
{
	// 	const WaterComponentSceneProxy* SceneProxy = ((WaterComponentSceneProxy*)Batch->Elements(0).ElementUserData)->SceneProxy;
	// 	SceneProxy->GetStaticBatchElementVisibility( View, Batch, BatchesToRender );
}
//------------------------------------------------------------------------

#if !DISABLE_WATER_VF

IMPLEMENT_VERTEX_FACTORY_TYPE(FWaterVertexFactory, "WaterVertexFactory", TRUE, TRUE, TRUE, FALSE, TRUE, VER_WATER_SHADER, 0);

#else

FVertexFactoryType* FWaterVertexFactory::GetType() const
{
	return 0;
}

#endif

#endif // WITH_WATER