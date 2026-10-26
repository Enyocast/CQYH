#include "EnginePrivate.h"
#include "EngineClasses.h"
#include "ScenePrivate.h"
#include "WaterRendering.h"
#include "WaterVertexFactory.h"
#include "WaterShader.h"


IMPLEMENT_CLASS(UWaterComponent)

//------------------------------------------------------------------------
// UWaterComponent
//------------------------------------------------------------------------
FPrimitiveSceneProxy* UWaterComponent::CreateSceneProxy()
{
#if WITH_WATER
	return new WaterComponentSceneProxy(this);
#else
	return 0;
#endif
}

#if WITH_WATER

//FWaterVertexFactory* WaterComponentSceneProxy::SharedVertexFactory = NULL;
//FWaterIndexBuffer** WaterComponentSceneProxy::SharedIndexBuffers = NULL;
//FWaterVertexBuffer* WaterComponentSceneProxy::SharedVertexBuffer = NULL;

#define WaterFieldSize 512


//------------------------------------------------------------------------
// FWaterVertexBuffer
//------------------------------------------------------------------------
void FWaterVertexBuffer::InitRHI()
{
	// create a static vertex buffer
	VertexBufferRHI = RHICreateVertexBuffer(Square(SizeVerts) * sizeof(FWaterVertex), NULL, RUF_Static);
	FWaterVertex* Vertex = (FWaterVertex*)RHILockVertexBuffer(VertexBufferRHI, 0, Square(SizeVerts) * sizeof(FWaterVertex),FALSE);

	for( INT y=0;y<SizeVerts;y++ )
	{
		for( INT x=0;x<SizeVerts;x++ )
		{
			Vertex->Position.X = x * WaterFieldSize * WaterSizeScale / WATER_MAX_COMPONENT_SIZE;
			Vertex->Position.Y = y * WaterFieldSize * WaterSizeScale / WATER_MAX_COMPONENT_SIZE;
			Vertex->Position.Z = WaterFieldSize * WaterSizeScale / WATER_MAX_COMPONENT_SIZE; // TODO:
			Vertex++;
		}
	}

	RHIUnlockVertexBuffer(VertexBufferRHI);
}

//------------------------------------------------------------------------
// FWaterVertexBuffer_NoTess
//------------------------------------------------------------------------
void FWaterVertexBuffer_NoTess::InitRHI()
{
	// create a static vertex buffer
	// todo: optimize to use index
	int buffSize = 6 * Square(SizeVerts) * sizeof( FWaterVertex );
	VertexBufferRHI = RHICreateVertexBuffer(buffSize, NULL, RUF_Static);
	FWaterVertex* Vertex = (FWaterVertex*)RHILockVertexBuffer(VertexBufferRHI, 0, buffSize,FALSE);

	FLOAT QuadSize = WaterFieldSize * WaterSizeScale / WATER_MAX_COMPONENT_SIZE;
	FLOAT HalfSize = QuadSize / 2.f;
	FLOAT cy = HalfSize;
	for( INT y=0;y<SizeVerts;y++ )
	{
		FLOAT cx = HalfSize;
		for( INT x=0;x<SizeVerts;x++ )
		{
			// vert_0
			Vertex->Position.X = cx - HalfSize;
			Vertex->Position.Y = cy - HalfSize;
			Vertex->Position.Z = 0.f;
			Vertex++;
			// vert_1
			Vertex->Position.X = cx - HalfSize;
			Vertex->Position.Y = cy + HalfSize;
			Vertex->Position.Z = 0.f;
			Vertex++;
			// vert_2
			Vertex->Position.X = cx + HalfSize;
			Vertex->Position.Y = cy - HalfSize;
			Vertex->Position.Z = 0.f;
			Vertex++;
			// vert_3
			Vertex->Position.X = cx + HalfSize;
			Vertex->Position.Y = cy - HalfSize;
			Vertex->Position.Z = 0.f;
			Vertex++;
			// vert_4
			Vertex->Position.X = cx - HalfSize;
			Vertex->Position.Y = cy + HalfSize;
			Vertex->Position.Z = 0.f;
			Vertex++;
			// vert_5
			Vertex->Position.X = cx + HalfSize;
			Vertex->Position.Y = cy + HalfSize;
			Vertex->Position.Z = 0.f;
			Vertex++;

			cx += QuadSize;
		}
		cy += QuadSize;
	}

	RHIUnlockVertexBuffer(VertexBufferRHI);
}



//------------------------------------------------------------------------
// FWaterIndexBuffer
//------------------------------------------------------------------------
FWaterIndexBuffer::FWaterIndexBuffer( INT SizeQuads, INT VBSizeVertices )
{
	TArray<WORD> NewIndices;
	NewIndices.Empty(SizeQuads*SizeQuads*6);
	for( INT y=0;y<SizeQuads;y++ )
	{
		for( INT x=0;x<SizeQuads;x++ )
		{
			NewIndices.AddItem( (x+0) + (y+0) * VBSizeVertices );
			NewIndices.AddItem( (x+1) + (y+1) * VBSizeVertices );
			NewIndices.AddItem( (x+1) + (y+0) * VBSizeVertices );
			NewIndices.AddItem( (x+0) + (y+0) * VBSizeVertices );
			NewIndices.AddItem( (x+0) + (y+1) * VBSizeVertices );
			NewIndices.AddItem( (x+1) + (y+1) * VBSizeVertices );
		}
	}
	Indices = NewIndices;

	InitResource();
}




//------------------------------------------------------------------------
// FWaterDrawingPolicy
//------------------------------------------------------------------------
FWaterDrawingPolicy::FWaterDrawingPolicy( 
	const FVertexFactory*		InVertexFactory,
	const FMaterialRenderProxy*	InMaterialRenderProxy,
	const FMaterial&			InMaterialResource ) :
	FMeshDrawingPolicy( InVertexFactory, InMaterialRenderProxy, InMaterialResource )
{
	const FMaterialShaderMap* MaterialShaderIndex = InMaterialResource.GetShaderMap();
	const FMeshMaterialShaderMap* MeshShaderIndex = MaterialShaderIndex->GetMeshShaderMap( InVertexFactory->GetType() );

	UBOOL HasVertexShader = MeshShaderIndex->HasShader( &FWaterVertexShader::StaticType );
	VertexShader = HasVertexShader ? MeshShaderIndex->GetShader<FWaterVertexShader>() : NULL;

	UBOOL HasPixelShader = MeshShaderIndex->HasShader( & FWaterPixelShader::StaticType );
	PixelShader = HasPixelShader ? MeshShaderIndex->GetShader<FWaterPixelShader>() : NULL;

#if WITH_D3D11_TESSELLATION
	HullShader = NULL;
	DomainShader = NULL;

	const EMaterialTessellationMode MaterialTessellationMode = InMaterialResource.GetD3D11TessellationMode();
	if( GRHIShaderPlatform == SP_PCD3D_SM5
		&& InVertexFactory->GetType()->SupportsTessellationShaders()
		&& MaterialTessellationMode != MTM_NoTessellation )
	{
		UBOOL HasHullShader = MeshShaderIndex->HasShader( &FWaterHullShader::StaticType );
		if( HasHullShader )
			HullShader = MeshShaderIndex->GetShader< FWaterHullShader >();

		UBOOL HasDomainShader = MeshShaderIndex->HasShader( &FWaterDomainShader::StaticType );
		if( HasDomainShader )
			DomainShader = MeshShaderIndex->GetShader< FWaterDomainShader >();
	}
#endif
}
//------------------------------------------------------------------------
void FWaterDrawingPolicy::DrawShared( const FSceneView* SceneView, FBoundShaderStateRHIRef ShaderState ) const
{
	FViewInfo* View = (FViewInfo*)SceneView;
	RHISetBoundShaderState( ShaderState );

	VertexShader->SetParameters( VertexFactory, MaterialRenderProxy, *View );
	PixelShader->SetParameters( VertexFactory, MaterialRenderProxy, *View );

#if WITH_D3D11_TESSELLATION
	if( HullShader && DomainShader )
	{
		HullShader->SetParameters( MaterialRenderProxy, *View );
		DomainShader->SetParameters( MaterialRenderProxy, *View );
	}
#endif

	FMeshDrawingPolicy::DrawShared( SceneView );
}
//------------------------------------------------------------------------
void FWaterDrawingPolicy::SetMeshRenderState( 
	const FViewInfo& View,
	const FPrimitiveSceneInfo* PrimitiveSceneInfo,
	const FMeshBatch& Mesh,
	INT BatchElementIndex,
	UBOOL bBackFace,
	const ElementDataType& ElementData ) const
{
	VertexShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View );

#if WITH_D3D11_TESSELLATION
	if( HullShader && DomainShader )
	{
		DomainShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View );
		HullShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View );
	}
#endif

	PixelShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View, bBackFace );
	//PixelShader->SetupParameters( PrimitiveSceneInfo );

	FMeshDrawingPolicy::SetMeshRenderState( View, PrimitiveSceneInfo, Mesh, BatchElementIndex, bBackFace, ElementData );
}
//------------------------------------------------------------------------
FBoundShaderStateRHIRef FWaterDrawingPolicy::CreateBoundShaderState( DWORD DynamicStride )
{
	FVertexDeclarationRHIRef VertexDeclaration;
	DWORD StreamStrides[MaxVertexElementCount];

	FMeshDrawingPolicy::GetVertexDeclarationInfo(VertexDeclaration, StreamStrides);
	if( DynamicStride )
	{
		StreamStrides[0] = DynamicStride;
	}

	FBoundShaderStateRHIRef BoundShaderState;

#if WITH_D3D11_TESSELLATION
	BoundShaderState = RHICreateBoundShaderStateD3D11(
		VertexDeclaration,
		StreamStrides,
		VertexShader->GetVertexShader(),
		GETSAFERHISHADER_HULL(HullShader),
		GETSAFERHISHADER_DOMAIN(DomainShader),
		PixelShader->GetPixelShader(),
		FGeometryShaderRHIRef(),
		EGST_None );
#else
	BoundShaderState = RHICreateBoundShaderState( VertexDeclaration, StreamStrides, VertexShader->GetVertexShader(), PixelShader->GetPixelShader() );
#endif

	return BoundShaderState;
}
//------------------------------------------------------------------------
UBOOL FWaterDrawingPolicy::SupportsWater() const
{
#if WITH_D3D11_TESSELLATION
	return ( VertexShader && PixelShader ) ? TRUE : FALSE;
#else
	return ( VertexShader && PixelShader ) ? TRUE : FALSE;
#endif
}




//------------------------------------------------------------------------
// WaterComponentSceneProxy
//------------------------------------------------------------------------
WaterComponentSceneProxy::WaterComponentSceneProxy( UWaterComponent* InComponent )
	: FPrimitiveSceneProxy(InComponent)
	,	VertexFactory(NULL)
	,	VertexBuffer(NULL)
	,	VertexBuffer_NoTess(NULL)
	,	IndexBuffers(NULL)
	,	IndexBuffer(NULL)
	,	FrustumCullInHS(InComponent->FrustumCullInHS)
	,	UseDynamicLOD(InComponent->UseDynamicLOD)
	,	RenderFoam(InComponent->RenderFoam)
	,	RenderCaustics(InComponent->RenderCaustics)
	,	RenderReflection(InComponent->RenderReflection)
	,	RenderRefraction(InComponent->RenderRefraction)
	,	RenderFog(InComponent->RenderFog)
	,	DoTessellation(((AWaterActor*)InComponent->GetOwner())->DoTessellation)
	,	DynamicTessFactor(InComponent->DynamicTessFactor)
	,	StaticTessFactor(InComponent->StaticTessFactor)
	,	WaterBumpTexcoordShiftX(InComponent->WaterBumpTexcoordShiftX)
	,	WaterBumpTexcoordShiftY(InComponent->WaterBumpTexcoordShiftY)
	,	WaterMicroBumpTexcoordScaleX(InComponent->WaterMicroBumpTexcoordScaleX)
	,	WaterMicroBumpTexcoordScaleY(InComponent->WaterMicroBumpTexcoordScaleY)
	,	WaterBumpTexcoordScaleX(InComponent->WaterBumpTexcoordScaleX)
	,	WaterBumpTexcoordScaleY(InComponent->WaterBumpTexcoordScaleY)
	,	WaterHeightBumpScale(((AWaterActor*)InComponent->GetOwner())->WaterHeightBumpScale)
	,	HeightFieldSize(((AWaterActor*)InComponent->GetOwner())->HeightFieldSize)
	,	WaterDeepColor(((AWaterActor*)InComponent->GetOwner())->WaterDeepColor)
	,	WaterColorIntensityX(((AWaterActor*)InComponent->GetOwner())->WaterColorIntensityX)
	,	WaterColorIntensityY(((AWaterActor*)InComponent->GetOwner())->WaterColorIntensityY)
	,	WaterScatterColor(((AWaterActor*)InComponent->GetOwner())->WaterScatterColor)
	,	WaterScatterColorPower(((AWaterActor*)InComponent->GetOwner())->WaterScatterColorPower)
	,	WaterSpecularColor(((AWaterActor*)InComponent->GetOwner())->WaterSpecularColor)
	,	WaterSpecularIntensity(((AWaterActor*)InComponent->GetOwner())->WaterSpecularIntensity)
	,	WaterSpecularPower(((AWaterActor*)InComponent->GetOwner())->WaterSpecularPower)
	,	WaterBumpTexture(InComponent->WaterBumpTexture)
	,	WaterDepthMap(InComponent->WaterDepthMap)
	// 	class UTexture2D* FoamTexture(InComponent->WaterHeightBumpScale)
	// 	class UTexture2D* CausticsTexture(InComponent->WaterHeightBumpScale)
	// 	class UTextureCube* ReflectionCube(InComponent->WaterHeightBumpScale)
	,	FogDensity(InComponent->FogDensity)
	,	AtmosphereBrightColor(InComponent->AtmosphereBrightColor)
	,	AtmosphereDarkColor(InComponent->AtmosphereDarkColor)
	,	Origin(InComponent->GetOwner()->LocalToWorld().GetOrigin())
	,	DrawScale3D(InComponent->GetOwner()->DrawScale3D)
{
	WaterComponent = InComponent;
}
//------------------------------------------------------------------------
WaterComponentSceneProxy::~WaterComponentSceneProxy()
{
	if(VertexFactory)
	{
		//check(SharedVertexFactory == VertexFactory);
		//if(SharedVertexFactory->Release() == 0)
		//{
		//	SharedVertexFactory = NULL;
		//}

		//VertexFactory = NULL;
		VertexFactory->Release();
	}

	if( VertexBuffer )
	{
		//check( SharedVertexBuffer == VertexBuffer );
		//if( SharedVertexBuffer->Release() == 0 )
		//{
		//	SharedVertexBuffer = NULL;
		//}
		//VertexBuffer = NULL;
		VertexBuffer->Release();
	}
	if( VertexBuffer_NoTess )
	{
		VertexBuffer_NoTess->Release();
	}

	if( IndexBuffer )
	{
		delete IndexBuffer;
		IndexBuffer = NULL;
	}

// 	if( IndexBuffers )
// 	{
// 		check( SharedIndexBuffers == IndexBuffers );
// 		UBOOL bCanDeleteArray = TRUE;
// 		for( INT i=0;i<WATER_LOD_LEVELS;i++ )
// 		{
// 			if( SharedIndexBuffers[i]->Release() == 0 )
// 			{
// 				SharedIndexBuffers[i] = NULL;
// 			}
// 			else
// 			{
// 				bCanDeleteArray = FALSE;
// 			}
// 		}
// 		if( bCanDeleteArray )
// 		{
// 			delete[] SharedIndexBuffers;
// 			SharedIndexBuffers = NULL;
// 		}
// 		IndexBuffers = NULL;
// 	}
}
//------------------------------------------------------------------------
UBOOL WaterComponentSceneProxy::CreateRenderThreadResources()
{
	if( DoTessellation )
	{
		if( VertexBuffer == NULL )
		{
			VertexBuffer = new FWaterVertexBuffer(WATER_MAX_COMPONENT_SIZE);
			VertexBuffer->AddRef();
		}
	}
	else
	{
		if( VertexBuffer_NoTess == NULL )
		{
			VertexBuffer_NoTess = new FWaterVertexBuffer_NoTess(WATER_MAX_COMPONENT_SIZE);
			VertexBuffer_NoTess->AddRef();
		}
	}

	if(IndexBuffer == NULL)
	{
		// TODO: LOD
		IndexBuffer = new FWaterIndexBuffer(((WATER_MAX_COMPONENT_SIZE) >> 0)-1, WATER_MAX_COMPONENT_SIZE);
	}

	//if( SharedIndexBuffers == NULL )
	//{
	//	SharedIndexBuffers = new FWaterIndexBuffer*[WATER_LOD_LEVELS];
	//	for( INT i=0;i<WATER_LOD_LEVELS;i++ )
	//	{
	//		SharedIndexBuffers[i] = new FWaterIndexBuffer(((WATER_MAX_COMPONENT_SIZE+1) >> i)-1, WATER_MAX_COMPONENT_SIZE+1);
	//	}
	//}
	//for( INT i=0;i<WATER_LOD_LEVELS;i++ )
	//{
	//	SharedIndexBuffers[i]->AddRef();
	//}
	//IndexBuffers = SharedIndexBuffers;



	if(VertexFactory == NULL)
	{
		VertexFactory = new FWaterVertexFactory();
		if( DoTessellation )
			VertexFactory->Data.PositionComponent = FVertexStreamComponent(VertexBuffer, 0, sizeof(FWaterVertexBuffer::FWaterVertex), VET_Float3);
		else
			VertexFactory->Data.PositionComponent = FVertexStreamComponent(VertexBuffer_NoTess, 0, sizeof(FWaterVertexBuffer_NoTess::FWaterVertex), VET_Float3);
		VertexFactory->InitResource();
		VertexFactory->AddRef();
	}

	return TRUE;
}
//------------------------------------------------------------------------
void WaterComponentSceneProxy::SetIndexSource( INT LODIndex, INT ElementIndex, INT FragmentIndex, FMeshBatch& OutMeshElement, UBOOL bWireframe, UBOOL bRequiresAdjacencyInformation ) const
{
	FMeshBatchElement& OutElement = OutMeshElement.Elements(0);
	const FStaticMeshRenderData& LODModel = WaterComponent->StaticMesh->LODModels(LODIndex);
	if (bWireframe)
	{
		if( LODModel.WireframeIndexBuffer.IsInitialized()
#if WITH_D3D11_TESSELLATION
			&& !(GRHIShaderPlatform == SP_PCD3D_SM5 && OutMeshElement.VertexFactory->GetType()->SupportsTessellationShaders())
#endif
			)
		{
			OutMeshElement.Type = PT_LineList;
			OutElement.FirstIndex = 0;
			OutElement.IndexBuffer = &LODModel.WireframeIndexBuffer;
			OutElement.NumPrimitives = LODModel.WireframeIndexBuffer.Indices.Num() / 2;
		}
		else
		{
			OutMeshElement.Type = PT_TriangleList;
			OutElement.FirstIndex = 0;
			OutElement.IndexBuffer = &LODModel.IndexBuffer;
			OutElement.NumPrimitives = LODModel.IndexBuffer.Indices.Num() / 3;
			OutMeshElement.bWireframe = TRUE;
			OutMeshElement.bDisableBackfaceCulling = TRUE;
		}
	}
	else
	{
		const FStaticMeshElement& Element = LODModel.Elements(ElementIndex);
		OutMeshElement.Type = PT_TriangleList;
		OutElement.IndexBuffer = &LODModel.IndexBuffer;
		OutElement.FirstIndex = Element.FirstIndex;
		OutElement.NumPrimitives = Element.NumTriangles;
	}

#if WITH_D3D11_TESSELLATION
	if ( bRequiresAdjacencyInformation )
	{
		check( LODModel.AdjacencyIndexBuffer.Indices.Num() > 0 );
		OutElement.IndexBuffer = &LODModel.AdjacencyIndexBuffer;
		OutMeshElement.Type = PT_12_ControlPointPatchList;
		OutElement.FirstIndex *= 4;
	}
#endif // #if WITH_D3D11_TESSELLATION
}
//------------------------------------------------------------------------
UBOOL WaterComponentSceneProxy::GetMeshElement( INT LODIndex,INT ElementIndex,INT FragmentIndex,BYTE InDepthPriorityGroup,const FMatrix& WorldToLocal,FMeshBatch& OutMeshElement, const UBOOL bUseSelectedMaterial, const UBOOL bUseHoveredMaterial ) const
{
	const FStaticMeshRenderData& LODModel = WaterComponent->StaticMesh->LODModels(LODIndex);
	const FStaticMeshElement& Element = LODModel.Elements(ElementIndex);

	//const FLODInfo& ProxyLODInfo = LODs( LODIndex );
	UMaterialInterface* Material = GEngine->DefaultMaterial;//ProxyLODInfo.Elements(ElementIndex).Material;

	//FColoredMaterialRenderProxy WireframeMaterialInstance(
	//	GEngine->DefaultMaterial->GetRenderProxy(WaterComponent->IsSelected(), FALSE),
	//	FLinearColor(128, 0, 0));

	OutMeshElement.MaterialRenderProxy =
		GEngine->DefaultMaterial->GetRenderProxy(WaterComponent->IsSelected(), FALSE), FLinearColor(128, 0, 0);
	//Material->GetRenderProxy(bUseSelectedMaterial,bUseHoveredMaterial);

	OutMeshElement.VertexFactory = &LODModel.VertexFactory;

	const UBOOL bWireframe = FALSE;
#if WITH_D3D11_TESSELLATION
	const UBOOL bRequiresAdjacencyInformation = FTessellationMaterialPolicy::RequiresAdjacencyInformation( Material, OutMeshElement.VertexFactory->GetType() );
#else
	const UBOOL bRequiresAdjacencyInformation = FALSE;
#endif

	SetIndexSource(LODIndex, ElementIndex, FragmentIndex, OutMeshElement, bWireframe, bRequiresAdjacencyInformation );

	FMeshBatchElement& OutBatchElement = OutMeshElement.Elements(0);

	if(OutBatchElement.NumPrimitives > 0)
	{
		OutMeshElement.DynamicVertexData = NULL;
		OutMeshElement.LCI = NULL;
		OutBatchElement.LocalToWorld = LocalToWorld;
		OutBatchElement.WorldToLocal = WorldToLocal;
		OutBatchElement.MinVertexIndex = Element.MinVertexIndex;
		OutBatchElement.MaxVertexIndex = Element.MaxVertexIndex;
		OutMeshElement.LODIndex = LODIndex;//FMeshBatch::QuantizeLODIndex(LODs.Num() > 1 ? LODIndex : INDEX_NONE);
		OutMeshElement.UseDynamicData = FALSE;
		OutMeshElement.ReverseCulling = LocalToWorldDeterminant < 0.0f ? TRUE : FALSE;
		OutMeshElement.CastShadow = FALSE;//bCastShadow && Element.bEnableShadowCasting;
		OutMeshElement.DepthPriorityGroup = (ESceneDepthPriorityGroup)InDepthPriorityGroup;
		OutMeshElement.bUsePreVertexShaderCulling = TRUE;
		OutMeshElement.PlatformMeshData = Element.PlatformData;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//------------------------------------------------------------------------
void WaterComponentSceneProxy::DrawStaticElements( FStaticPrimitiveDrawInterface* PDI )
{
	SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("D3D11 Render Water DrawStaticElements")); // oscar@snda
	//Super::Drawstaticme
}
//------------------------------------------------------------------------
void WaterComponentSceneProxy::DrawDynamicElements( FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex,DWORD Flags /*= 0*/ )
{
	const FViewInfo& SView = *((const FViewInfo*)View);
	if(!WaterComponent)
	{
		return;
	}
	
	if(View->Family->bScreenCaptureRenderTarget)
	{
		return;
	}

	const FMatrix WorldToLocal = WaterComponent->LocalToWorld.Inverse();

	SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("D3D11 Render Water")); // oscar@snda

	FMeshBatch Mesh;
	Mesh.MaterialRenderProxy = WaterComponent->DefaultMaterial->GetRenderProxy(bSelected);
	Mesh.DepthPriorityGroup = (ESceneDepthPriorityGroup)DPGIndex;
	Mesh.Type = PT_TriangleList;
	Mesh.CastShadow = FALSE;
	Mesh.ReverseCulling = WaterComponent->LocalToWorldDeterminant < 0.0f ? TRUE : FALSE;
	Mesh.VertexFactory = VertexFactory;
	Mesh.bWireframe = FALSE;

	FMeshBatchElement* BatchElement = &Mesh.Elements(0);

	BatchElement->LocalToWorld = WaterComponent->LocalToWorld;
	BatchElement->WorldToLocal = WorldToLocal;
	BatchElement->IndexBuffer = IndexBuffer;
	BatchElement->NumPrimitives = IndexBuffer->Indices.Num() / 3;// Square(((SubsectionSizeVerts >> BatchParams->CurrentLOD) - 1)) * 2;

	BatchElement->FirstIndex = 0;
	BatchElement->MinVertexIndex = 0;
	BatchElement->MaxVertexIndex =  IndexBuffer->Indices.Num();//(WATER_MAX_COMPONENT_SIZE+1) * (SubsectionSizeVerts >> BatchParams->CurrentLOD) - 1;

	//DrawWithOnlyVSPS(Mesh, SView);
	
	if((View->Family->ShowFlags & SHOW_ViewMode_Mask) == SHOW_ViewMode_Wireframe)
	{
		RHISetRasterizerState(TStaticRasterizerState<FM_Wireframe,CM_None>::GetRHI());
	}
	else
	{
		RHISetRasterizerState(TStaticRasterizerState<FM_Solid, CM_CW>::GetRHI());
	}

	//RHISetBlendState(TStaticBlendState<BO_Add,BF_SourceAlpha,BF_InverseSourceAlpha,BO_Add,BF_Zero,BF_One,CF_Greater,0>::GetRHI());
	//RHISetColorWriteMask( CW_RGBA );
	RHISetDepthState(TStaticDepthState<TRUE>::GetRHI());
	RHISetBlendState(TStaticBlendState<>::GetRHI());

	if( DoTessellation )
		DrawManualWithTessellation(Mesh, SView);
	else
		DrawWithOnlyVSPS(Mesh,SView);
	
//	PDI->DrawLine(FVector(0, 0, 0), FVector(10000,10000,6000), FLinearColor(1,0,0), SDPG_World);

//	PDI->DrawLine(FVector(0, 0, 0), SView.ViewOrigin, FLinearColor(1,1,0), SDPG_World);

	
	//PDI->DrawLine(FVector(0, 0, 0), FVector(1000, 1000, 100), FLinearColor(1,0,0), SDPG_World);
	//PDI->DrawLine(FVector(0, 0, 0), WaterComponent->GetOwner()->Location, FLinearColor(1,0,0), SDPG_World);
	//DrawStaticWaterMesh(SView, DPGIndex);
	//DrawWithDrawingPolicy(Mesh, SView);
}
//------------------------------------------------------------------------
FPrimitiveViewRelevance WaterComponentSceneProxy::GetViewRelevance( const FSceneView* View )
{
	FPrimitiveViewRelevance Result;
	Result.bDynamicRelevance = TRUE;
	Result.bOpaqueRelevance = FALSE;
	Result.bTranslucentRelevance = TRUE;
	Result.bSceneTextureRenderBehindTranslucency = TRUE;
	Result.bUsesSceneColor = TRUE;
	Result.bWorldDPG = TRUE;
	Result.SetDPG( SDPG_World,TRUE );
	return Result;
}
//------------------------------------------------------------------------
void WaterComponentSceneProxy::DrawStaticWaterMesh(const FViewInfo& SView, INT DPGIndex)
{
	const FMatrix WorldToLocal = WaterComponent->LocalToWorld.Inverse();

	const INT LODIndex = 0;//GetLOD(View);
	// Draw polygon mesh if we are either not in a collision view, or are drawing it as collision.
	//if((View->Family->ShowFlags & SHOW_StaticMeshes) && bDrawMesh )
	//{
	//const UBOOL bLevelColorationEnabled = (View->Family->ShowFlags & SHOW_LevelColoration) ? TRUE : FALSE;
	//const UBOOL bPropertyColorationEnabled = (View->Family->ShowFlags & SHOW_PropertyColoration) ? TRUE : FALSE;

	const FStaticMeshRenderData& LODModel = WaterComponent->StaticMesh->LODModels(LODIndex);
	//const FLODInfo& ProxyLODInfo = LODs( LODIndex );

	for(INT ElementIndex = 0;ElementIndex < LODModel.Elements.Num();ElementIndex++)
	{
		//for(INT FragmentIndex = 0;FragmentIndex < LODs(LODIndex).Elements(ElementIndex).NumFragments;FragmentIndex++)
		{
			FMeshBatch Mesh;
			if(GetMeshElement(LODIndex,ElementIndex,0,DPGIndex,WorldToLocal,Mesh, bSelected, bHovered))
			{
				const FMaterialRenderProxy* MaterialRenderProxy = WaterComponent->DefaultMaterial->GetRenderProxy(bSelected);//Mesh.MaterialRenderProxy;
				const FMaterial* Material = MaterialRenderProxy->GetMaterial();
				EBlendMode BlendMode = Material->GetBlendMode();

				FWaterDrawingPolicy DrawingPolicy(  VertexFactory, MaterialRenderProxy, *MaterialRenderProxy->GetMaterial() );
				if( DrawingPolicy.SupportsWater() )
				{
					DrawingPolicy.DrawShared( &SView, DrawingPolicy.CreateBoundShaderState( Mesh.GetDynamicVertexStride() ) );
					for( INT BatchElementIndex=0;BatchElementIndex < Mesh.Elements.Num();BatchElementIndex++ )
					{
						DrawingPolicy.SetMeshRenderState( SView, PrimitiveSceneInfo, Mesh, BatchElementIndex, false, FMeshDrawingPolicy::ElementDataType() );
						DrawingPolicy.DrawMesh( Mesh, BatchElementIndex );
					}
				}
			} // MeshElement
		} // for FragmentIndex
	} // for ElementIndex
	//}
}
//------------------------------------------------------------------------
void WaterComponentSceneProxy::DrawWithDrawingPolicy( FMeshBatch &Mesh, const FViewInfo& SView )
{
	FWaterDrawingPolicy DrawingPolicy(  VertexFactory, Mesh.MaterialRenderProxy, *Mesh.MaterialRenderProxy->GetMaterial() );
	if( DrawingPolicy.SupportsWater() )
	{
		DrawingPolicy.DrawShared( &SView, DrawingPolicy.CreateBoundShaderState( Mesh.GetDynamicVertexStride() ) );
		for( INT BatchElementIndex=0;BatchElementIndex < Mesh.Elements.Num();BatchElementIndex++ )
		{
			DrawingPolicy.SetMeshRenderState( SView, PrimitiveSceneInfo, Mesh, BatchElementIndex, false, FMeshDrawingPolicy::ElementDataType() );
			DrawingPolicy.DrawMesh( Mesh, BatchElementIndex );
		}
	}
}
//------------------------------------------------------------------------
void WaterComponentSceneProxy::DrawManualWithTessellation( FMeshBatch &Mesh, const FViewInfo& SView )
{
	INT BatchElementIndex = 0;
	Mesh.Type = (GRHIShaderPlatform == SP_PCD3D_SM5) ? PT_1_ControlPointPatchList : PT_TriangleList;


	FVertexDeclarationRHIRef VertexDeclaration;
	DWORD StreamStrides[MaxVertexElementCount];

	check(VertexFactory && VertexFactory->IsInitialized());
	VertexFactory->GetStreamStrides(StreamStrides);
	VertexDeclaration = VertexFactory->GetDeclaration();
	check(IsValidRef(VertexDeclaration));

	StreamStrides[0] = sizeof(FWaterVertexBuffer::FWaterVertex);

	FBoundShaderStateRHIRef BoundShaderState;

	const FMaterialRenderProxy* MaterialRenderProxy = WaterComponent->DefaultMaterial->GetRenderProxy(bSelected);
	const FMaterial* InMaterialResource = MaterialRenderProxy->GetMaterial();
	const FMaterialShaderMap* MaterialShaderIndex = InMaterialResource->GetShaderMap();
	const FMeshMaterialShaderMap* MeshShaderIndex = MaterialShaderIndex->GetMeshShaderMap( VertexFactory->GetType() );

	UBOOL HasVertexShader = MeshShaderIndex->HasShader( &FWaterVertexShader::StaticType );
	FWaterVertexShader* VertexShader = HasVertexShader ? MeshShaderIndex->GetShader<FWaterVertexShader>() : NULL;

	UBOOL HasPixelShader = MeshShaderIndex->HasShader( & FWaterPixelShader::StaticType );
	FWaterPixelShader* PixelShader = HasPixelShader ? MeshShaderIndex->GetShader<FWaterPixelShader>() : NULL;

	{
		SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("Water setup VS"));
		VertexShader->SetParameters( VertexFactory, MaterialRenderProxy, SView );
		VertexShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, SView);
	}
	
	{	
		SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("Water setup PS"));
		PixelShader->SetParameters( VertexFactory, MaterialRenderProxy, SView );
		PixelShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, SView, FALSE );
	}

#if WITH_D3D11_TESSELLATION
	FWaterHullShader* HullShader = NULL;
	FWaterDomainShader* DomainShader = NULL;

	const EMaterialTessellationMode MaterialTessellationMode = InMaterialResource->GetD3D11TessellationMode();
	if( GRHIShaderPlatform == SP_PCD3D_SM5
	// 		&& VertexFactory->GetType()->SupportsTessellationShaders()
	// 		&& MaterialTessellationMode != MTM_NoTessellation 
	)
	{
		SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("Water get hull & domain shader"));
		UBOOL HasHullShader = MeshShaderIndex->HasShader( &FWaterHullShader::StaticType );
		if( HasHullShader )
			HullShader = MeshShaderIndex->GetShader< FWaterHullShader >();

		UBOOL HasDomainShader = MeshShaderIndex->HasShader( &FWaterDomainShader::StaticType );
		if( HasDomainShader )
			DomainShader = MeshShaderIndex->GetShader< FWaterDomainShader >();
	}

	BoundShaderState = RHICreateBoundShaderStateD3D11(
		VertexDeclaration,
		StreamStrides,
		VertexShader->GetVertexShader(),
		GETSAFERHISHADER_HULL(HullShader),
		GETSAFERHISHADER_DOMAIN(DomainShader),
		PixelShader->GetPixelShader(),
		FGeometryShaderRHIRef(),
		EGST_None );
#else
	BoundShaderState = RHICreateBoundShaderState( VertexDeclaration, StreamStrides,
		VertexShader->GetVertexShader(), PixelShader->GetPixelShader() );
#endif

	//FViewInfo* View = (FViewInfo*)SceneView;
	RHISetBoundShaderState( BoundShaderState );


#if WITH_D3D11_TESSELLATION
	if( GRHIShaderPlatform == SP_PCD3D_SM5 && HullShader )
	{
		SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("Water setup hull"));
		HullShader->SetParameters( MaterialRenderProxy, SView );
		HullShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, SView );
	}

	if( GRHIShaderPlatform == SP_PCD3D_SM5 && DomainShader )
	{
		SCOPED_DRAW_EVENT(Event)(DEC_SCENE_ITEMS,TEXT("Water setup domain"));

		DomainShader->SetParameters( MaterialRenderProxy, SView );
		DomainShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, SView );
	}
#endif

	//VertexFactory->Set();

	RHISetStreamSource(0, VertexBuffer->VertexBufferRHI, sizeof(FWaterVertexBuffer::FWaterVertex), 0, 0, 0, 0);
	if( GRHIShaderPlatform == SP_PCD3D_SM5)
	{
		RHIDrawPrimitive(PT_1_ControlPointPatchList, 0, WATER_MAX_COMPONENT_SIZE * WATER_MAX_COMPONENT_SIZE);
	}
	else
	{

	}
}
//------------------------------------------------------------------------
void WaterComponentSceneProxy::DrawWithOnlyVSPS( const FMeshBatch& Mesh, const FViewInfo& SView )
{
	INT BatchElementIndex = 0;

	const FMaterialRenderProxy* MaterialRenderProxy = WaterComponent->DefaultMaterial->GetRenderProxy(bSelected);
	const FMaterial* InMaterialResource = MaterialRenderProxy->GetMaterial();
	const FMaterialShaderMap* MaterialShaderIndex = InMaterialResource->GetShaderMap();
	const FMeshMaterialShaderMap* MeshShaderIndex = MaterialShaderIndex->GetMeshShaderMap( VertexFactory->GetType() );


	UBOOL HasVertexShader = MeshShaderIndex->HasShader( &FWaterVertexShader_NoTess::StaticType );
	FWaterVertexShader_NoTess* VertexShader = HasVertexShader ? MeshShaderIndex->GetShader<FWaterVertexShader_NoTess>() : NULL;

	UBOOL HasPixelShader = MeshShaderIndex->HasShader( & FWaterPixelShader::StaticType );
	FWaterPixelShader* PixelShader = HasPixelShader ? MeshShaderIndex->GetShader<FWaterPixelShader>() : NULL;


	FVertexDeclarationRHIRef VertexDeclaration;
	DWORD StreamStrides[MaxVertexElementCount];

	check(VertexFactory && VertexFactory->IsInitialized());
	VertexFactory->GetStreamStrides(StreamStrides);
	VertexDeclaration = VertexFactory->GetDeclaration();
	check(IsValidRef(VertexDeclaration));

	StreamStrides[0] = sizeof(FWaterVertexBuffer_NoTess::FWaterVertex);

	FBoundShaderStateRHIRef BoundShaderState;


	BoundShaderState = RHICreateBoundShaderStateD3D11(
		VertexDeclaration,
		StreamStrides,
		VertexShader->GetVertexShader(),
		NULL,
		NULL,
		PixelShader->GetPixelShader(),
		FGeometryShaderRHIRef(),
		EGST_None );

	RHISetBoundShaderState( BoundShaderState );

	VertexShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, SView);
	PixelShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, SView, FALSE );

	VertexShader->SetParameters( VertexFactory, MaterialRenderProxy, SView );
	PixelShader->SetParameters( VertexFactory, MaterialRenderProxy, SView );

	//RHISetBlendState(TStaticBlendState<BO_Add, BF_One, BF_One, BO_Add, BF_One, BF_One>::GetRHI());
	//RHISetDepthState(TStaticDepthState<TRUE, CF_Always>::GetRHI());
	
	//RHISetRasterizerState(TStaticRasterizerState<FM_Solid, CM_None>::GetRHI());

	RHISetStreamSource(0, VertexBuffer_NoTess->VertexBufferRHI, sizeof(FWaterVertexBuffer_NoTess::FWaterVertex), 0, FALSE, 3, 1);
	RHIDrawPrimitive(PT_TriangleList, 0, WATER_MAX_COMPONENT_SIZE * WATER_MAX_COMPONENT_SIZE * 2);
}

//------------------------------------------------------------------------

#endif // WITH_WATER