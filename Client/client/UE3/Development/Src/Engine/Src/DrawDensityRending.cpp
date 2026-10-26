/*=============================================================================
	DrawDensityRendering.h: Definitions for draw density(over draw).
	Copyright 1998-2013 Shanda Games, Inc. All Rights Reserved.
=============================================================================*/

#include "EnginePrivate.h"
#include "ScenePrivate.h"

// This define must match the corresponding one in DrawDensityShader.usf
#define MAX_LOOKUPS 16

/**
 * A vertex shader for rendering texture density.
 */
class FDrawDensityVertexShader : public FMeshMaterialVertexShader
{
	DECLARE_SHADER_TYPE(FDrawDensityVertexShader,MeshMaterial);

public:

	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
	{
		// Only compile the shaders for the default material or if it's masked.
		return Material->GetUserTexCoordsUsed() > 0 
			&& (Material->IsSpecialEngineMaterial() || Material->IsMasked() || Material->MaterialModifiesMeshPosition())
			&& AllowDebugViewmodes(Platform);
	}

	FDrawDensityVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer):
		FMeshMaterialVertexShader(Initializer)
	{
		MaterialParameters.Bind(Initializer.ParameterMap);
	}

	FDrawDensityVertexShader() 
	{

	}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		UBOOL bShaderHasOutdatedParameters = FShader::Serialize(Ar);
		bShaderHasOutdatedParameters |= Ar << VertexFactoryParameters;
		Ar << MaterialParameters;
		return bShaderHasOutdatedParameters;
	}

	void SetParameters(const FVertexFactory* VertexFactory,const FMaterialRenderProxy* MaterialRenderProxy,const FSceneView& View)
	{
		VertexFactoryParameters.Set(this,VertexFactory,View);
		FMaterialRenderContext MaterialRenderContext(MaterialRenderProxy,*MaterialRenderProxy->GetMaterial(),View.Family->CurrentWorldTime,View.Family->CurrentRealTime,&View);
		MaterialParameters.Set( this, MaterialRenderContext);
	}

	void SetMesh(const FPrimitiveSceneInfo* PrimitiveSceneInfo, const FMeshBatch& Mesh, INT BatchElementIndex,const FSceneView& View)
	{
		VertexFactoryParameters.SetMesh(this,Mesh,BatchElementIndex,View);
		MaterialParameters.SetMesh(this,PrimitiveSceneInfo,Mesh,BatchElementIndex,View);
	}

	virtual UBOOL IsUniformExpressionSetValid(const FUniformExpressionSet& UniformExpressionSet) const 
	{ 
		return MaterialParameters.IsUniformExpressionSetValid(UniformExpressionSet); 
	}

private:
	FMaterialVertexShaderParameters MaterialParameters;
};

IMPLEMENT_MATERIAL_SHADER_TYPE(,FDrawDensityVertexShader,TEXT("DrawDensityShader"),TEXT("MainVertexShader"),SF_Vertex,0,0); 

//#if WITH_D3D11_TESSELLATION
//
///**
// * A hull shader for rendering texture density.
// */
//class FDrawDensityHullShader : public FBaseHullShader
//{
//	DECLARE_SHADER_TYPE(FDrawDensityHullShader,MeshMaterial);
//public:
//
//	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
//	{
//		return FBaseHullShader::ShouldCache(Platform, Material, VertexFactoryType)
//			&& FDrawDensityVertexShader::ShouldCache(Platform,Material,VertexFactoryType);
//	}
//
//	FDrawDensityHullShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer):
//		FBaseHullShader(Initializer)
//	{}
//
//	FDrawDensityHullShader() {}
//};
//
///**
// * A domain shader for rendering texture density.
// */
//class FDrawDensityDomainShader : public FBaseDomainShader
//{
//	DECLARE_SHADER_TYPE(FDrawDensityDomainShader,MeshMaterial);
//public:
//
//	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
//	{
//		return FBaseDomainShader::ShouldCache(Platform, Material, VertexFactoryType)
//			&& FDrawDensityVertexShader::ShouldCache(Platform,Material,VertexFactoryType);		
//	}
//
//	FDrawDensityDomainShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer):
//		FBaseDomainShader(Initializer)
//	{}
//
//	FDrawDensityDomainShader() {}
//};
//
//IMPLEMENT_MATERIAL_SHADER_TYPE(,FDrawDensityHullShader,TEXT("DrawDensityShader"),TEXT("MainHull"),SF_Hull,0,0); 
//IMPLEMENT_MATERIAL_SHADER_TYPE(,FDrawDensityDomainShader,TEXT("DrawDensityShader"),TEXT("MainDomain"),SF_Domain,0,0);
//
//#endif

/**
 * A pixel shader for rendering texture density.
 */
class FDrawDensityPixelShader : public FShader
{
	DECLARE_SHADER_TYPE(FDrawDensityPixelShader,MeshMaterial);
public:

	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
	{
		// Only compile the shaders for the default material or if it's masked.
		return Material->GetUserTexCoordsUsed() > 0 
			&& (Material->IsSpecialEngineMaterial() || Material->IsMasked() || Material->MaterialModifiesMeshPosition())
			&& AllowDebugViewmodes(Platform);
	}

	FDrawDensityPixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer):
		FShader(Initializer)
	{
		MaterialParameters.Bind(Initializer.ParameterMap);
		//DrawDensityParameters.Bind(Initializer.ParameterMap,TEXT("DrawDensityParameters"));
		//DrawLookupInfo.Bind(Initializer.ParameterMap,TEXT("DrawLookupInfo"));
	}

	FDrawDensityPixelShader() {}

	void SetParameters(const FVertexFactory* VertexFactory,const FMaterialRenderProxy* MaterialRenderProxy,const FSceneView& View, const FMaterialRenderProxy* OriginalRenderProxy)
	{
		//FMaterialRenderContext MaterialRenderContext(MaterialRenderProxy, *MaterialRenderProxy->GetMaterial(), View.Family->CurrentWorldTime, View.Family->CurrentRealTime, &View);
		//const FMaterial* OriginalMaterial = OriginalRenderProxy->GetMaterial();
		//const TArray<FMaterial::FDrawLookup> &LookupInfo = OriginalMaterial->GetDrawLookupInfo();
		//INT NumLookups = Min( LookupInfo.Num(), MAX_LOOKUPS );

		//FVector4 LookupParameters[ MAX_LOOKUPS ];
		//FVector4 DensityParameters(
		//	NumLookups,
		//	GEngine->MinDrawDensity * GEngine->MinDrawDensity,
		//	GEngine->IdealDrawDensity * GEngine->IdealDrawDensity,
		//	GEngine->MaxDrawDensity * GEngine->MaxDrawDensity );

		//for( INT LookupIndex=0; LookupIndex < NumLookups; ++LookupIndex )
		//{
		//	const FMaterial::FDrawLookup &Lookup = LookupInfo( LookupIndex );
		//	if (OriginalMaterial->GetUniform2DDrawExpressions().IsValidIndex(Lookup.DrawIndex))
		//	{
		//		const FDraw* Draw = NULL;
		//		OriginalMaterial->GetUniform2DDrawExpressions()( Lookup.DrawIndex )->GetDrawValue( MaterialRenderContext, *OriginalMaterial, Draw );
		//		check( Draw );
		//		LookupParameters[LookupIndex][0] = FLOAT(Draw->GetSizeX()) * Lookup.UScale;
		//		LookupParameters[LookupIndex][1] = FLOAT(Draw->GetSizeY()) * Lookup.VScale;
		//	}
		//	else
		//	{
		//		LookupParameters[LookupIndex][0] = 0;
		//		LookupParameters[LookupIndex][1] = 0;
		//	}
		//	
		//	LookupParameters[LookupIndex][2] = Lookup.TexCoordIndex;
		//}

		//SetPixelShaderValues( GetPixelShader(), DrawLookupInfo, LookupParameters, NumLookups );
		//SetPixelShaderValue( GetPixelShader(), DrawDensityParameters, DensityParameters );

		//MaterialParameters.Set( this, MaterialRenderContext);
	}

	void SetMesh(const FPrimitiveSceneInfo* PrimitiveSceneInfo, const FMeshBatch& Mesh, INT BatchElementIndex, const FSceneView& View,UBOOL bBackFace)
	{
		//MaterialParameters.SetMesh( this, PrimitiveSceneInfo, Mesh, BatchElementIndex, View, bBackFace);
	}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		UBOOL bShaderHasOutdatedParameters = FShader::Serialize(Ar);
		Ar << MaterialParameters;
		//Ar << DrawDensityParameters;
		//Ar << DrawLookupInfo;
		return bShaderHasOutdatedParameters;
	}

	virtual UBOOL IsUniformExpressionSetValid(const FUniformExpressionSet& UniformExpressionSet) const 
	{ 
		return MaterialParameters.IsUniformExpressionSetValid(UniformExpressionSet); 
	}

private:

	FMaterialPixelShaderParameters MaterialParameters;
	//FShaderParameter DrawDensityParameters;
	//FShaderParameter DrawLookupInfo;
};

IMPLEMENT_MATERIAL_SHADER_TYPE(,FDrawDensityPixelShader,TEXT("DrawDensityShader"),TEXT("MainPixelShader"),SF_Pixel,VER_CONTENT_RESAVE_AUGUST_2007_QA_BUILD,0);


//=============================================================================
/** FDrawDensityDrawingPolicy - Policy to wrap FMeshDrawingPolicy with new shaders. */

FDrawDensityDrawingPolicy::FDrawDensityDrawingPolicy(
	const FVertexFactory* InVertexFactory,
	const FMaterialRenderProxy* InMaterialRenderProxy,
	const FMaterialRenderProxy* InOriginalRenderProxy
	)
	:	FMeshDrawingPolicy(InVertexFactory,InMaterialRenderProxy,*InMaterialRenderProxy->GetMaterial())
	,	OriginalRenderProxy(InOriginalRenderProxy)
{
	const FMaterialShaderMap* MaterialShaderIndex = InMaterialRenderProxy->GetMaterial()->GetShaderMap();
	const FMeshMaterialShaderMap* MeshShaderIndex = MaterialShaderIndex->GetMeshShaderMap(InVertexFactory->GetType());
	const FMaterial* MaterialResource = InMaterialRenderProxy->GetMaterial();

	UBOOL HasVertexShader = MeshShaderIndex->HasShader(&FDrawDensityVertexShader::StaticType);
	VertexShader = HasVertexShader ? MeshShaderIndex->GetShader<FDrawDensityVertexShader>() : NULL;
	
	UBOOL HasPixelShader = MeshShaderIndex->HasShader(&FDrawDensityPixelShader::StaticType);
	PixelShader = HasPixelShader ? MeshShaderIndex->GetShader<FDrawDensityPixelShader>() : NULL;
}

void FDrawDensityDrawingPolicy::DrawShared( const FSceneView* SceneView, FBoundShaderStateRHIRef ShaderState ) const
{
	// NOTE: Assuming this cast is always safe!
	FViewInfo* View = (FViewInfo*) SceneView;

	// Set the depth-only shader parameters for the material.
	RHISetBoundShaderState( ShaderState );
	VertexShader->SetParameters( VertexFactory, MaterialRenderProxy, *View );
	PixelShader->SetParameters( VertexFactory, MaterialRenderProxy, *View, OriginalRenderProxy );

	// Set the shared mesh resources.
	FMeshDrawingPolicy::DrawShared( View );
}

void FDrawDensityDrawingPolicy::SetMeshRenderState(
	const FSceneView& View,
	const FPrimitiveSceneInfo* PrimitiveSceneInfo,
	const FMeshBatch& Mesh,
	INT BatchElementIndex,
	UBOOL bBackFace,
	const ElementDataType& ElementData
	) const
{
	VertexShader->SetMesh(PrimitiveSceneInfo, Mesh, BatchElementIndex, View);
	PixelShader->SetMesh(PrimitiveSceneInfo, Mesh, BatchElementIndex, View, bBackFace);

	FMeshDrawingPolicy::SetMeshRenderState(View, PrimitiveSceneInfo, Mesh, BatchElementIndex, bBackFace, ElementData);
}

/** 
 * Create bound shader state using the vertex decl from the mesh draw policy
 * as well as the shaders needed to draw the mesh
 * @param DynamicStride - optional stride for dynamic vertex data
 * @return new bound shader state object
 */
FBoundShaderStateRHIRef FDrawDensityDrawingPolicy::CreateBoundShaderState(DWORD DynamicStride)
{
	FVertexDeclarationRHIRef VertexDeclaration;
	DWORD StreamStrides[MaxVertexElementCount];

	FMeshDrawingPolicy::GetVertexDeclarationInfo(VertexDeclaration, StreamStrides);
	if (DynamicStride)
	{
		StreamStrides[0] = DynamicStride;
	}

	FBoundShaderStateRHIRef BoundShaderState;

	BoundShaderState = RHICreateBoundShaderState(VertexDeclaration, StreamStrides, VertexShader->GetVertexShader(), PixelShader->GetPixelShader(), EGST_None);

	return BoundShaderState;
}

INT Compare(const FDrawDensityDrawingPolicy& A,const FDrawDensityDrawingPolicy& B)
{
	COMPAREDRAWINGPOLICYMEMBERS(VertexShader);
	COMPAREDRAWINGPOLICYMEMBERS(PixelShader);

	COMPAREDRAWINGPOLICYMEMBERS(VertexFactory);
	COMPAREDRAWINGPOLICYMEMBERS(MaterialRenderProxy);
	return 0;
}


//=============================================================================
/** Policy to wrap FMeshDrawingPolicy with new shaders. */

UBOOL FDrawDensityDrawingPolicyFactory::DrawDynamicMesh(
	const FViewInfo& View,
	ContextType DrawingContext,
	const FMeshBatch& Mesh,
	UBOOL bBackFace,
	UBOOL bPreFog,
	const FPrimitiveSceneInfo* PrimitiveSceneInfo,
	FHitProxyId HitProxyId
	)
{
	// Only draw opaque materials in the depth pass.
	const FMaterialRenderProxy* OriginalRenderProxy = Mesh.MaterialRenderProxy;
	const FMaterialRenderProxy* MaterialRenderProxy = OriginalRenderProxy;
	const FMaterial* Material = MaterialRenderProxy->GetMaterial();
	
	if ( Material != NULL )
	{
		if ( !Material->IsMasked() && !Material->MaterialModifiesMeshPosition() )
		{
			// Default material doesn't handle masked.
			//shan@snda[
			//MaterialRenderProxy = GEngine->DefaultMaterial->GetRenderProxy(FALSE);
			MaterialRenderProxy = GEngine->TextrueDensityMaterial->GetRenderProxy(FALSE);
			//shan@snda]
		}

		FDrawDensityDrawingPolicy DrawingPolicy( Mesh.VertexFactory, MaterialRenderProxy, OriginalRenderProxy );
		DrawingPolicy.DrawShared(&View,DrawingPolicy.CreateBoundShaderState(Mesh.GetDynamicVertexStride()));
		for( INT BatchElementIndex = 0; BatchElementIndex < Mesh.Elements.Num(); BatchElementIndex++)
		{
			DrawingPolicy.SetMeshRenderState(View,PrimitiveSceneInfo,Mesh,BatchElementIndex,bBackFace,FMeshDrawingPolicy::ElementDataType());
			DrawingPolicy.DrawMesh(Mesh,BatchElementIndex);
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/** Renders world-space texture density instead of the normal color. */
UBOOL FSceneRenderer::RenderDrawDensities(UINT DPGIndex)
{
	SCOPED_DRAW_EVENT(EventDrawDensity)(DEC_SCENE_ITEMS,TEXT("RenderDrawDensity"));

	UBOOL bWorldDpg = (DPGIndex == SDPG_World);
	UBOOL bDirty = FALSE;

	// Opaque blending, enable depth tests and writes.
	RHISetBlendState(TStaticBlendState<BO_Add,BF_SourceAlpha,BF_DestAlpha, BO_Add, BF_One, BF_One>::GetRHI());
	RHISetDepthState(TStaticDepthState<TRUE,CF_LessEqual>::GetRHI());

	for(INT ViewIndex = 0;ViewIndex < Views.Num();ViewIndex++)
	{
		// SCOPED_CONDITIONAL_DRAW_EVENT(EventView,Views.Num() > 1)(DEC_SCENE_ITEMS,TEXT("View%d"),ViewIndex); // oscar@snda
		SCOPED_DRAW_EVENT(EventView)(DEC_SCENE_ITEMS,TEXT("View%d"),ViewIndex); // oscar@snda

		FViewInfo& View = Views(ViewIndex);
		const FSceneViewState* ViewState = (FSceneViewState*)View.State;

		// Set the device viewport for the view.
		RHISetViewport(View.RenderTargetX,View.RenderTargetY,0.0f,View.RenderTargetX + View.RenderTargetSizeX,View.RenderTargetY + View.RenderTargetSizeY,1.0f);
		RHISetViewParameters(View);
		RHISetMobileHeightFogParams(View.HeightFogParams);

		// Draw texture density for dynamic meshes.
		TDynamicPrimitiveDrawer<FDrawDensityDrawingPolicyFactory> Drawer(&View,DPGIndex,FDrawDensityDrawingPolicyFactory::ContextType(),TRUE);
		for(INT PrimitiveIndex = 0;PrimitiveIndex < View.VisibleDynamicPrimitives.Num();PrimitiveIndex++)
		{
			const FPrimitiveSceneInfo* PrimitiveSceneInfo = View.VisibleDynamicPrimitives(PrimitiveIndex);
			const FPrimitiveViewRelevance& PrimitiveViewRelevance = View.PrimitiveViewRelevanceMap(PrimitiveSceneInfo->Id);

			const UBOOL bVisible = View.PrimitiveVisibilityMap(PrimitiveSceneInfo->Id);
			if( bVisible &&		PrimitiveViewRelevance.GetDPG(DPGIndex) )
			{
				Drawer.SetPrimitive(PrimitiveSceneInfo);
				PrimitiveSceneInfo->Proxy->DrawDynamicElements(
					&Drawer,
					&View,
					DPGIndex
					);
			}
		}
		bDirty |= Drawer.IsDirty();
	}

	return bDirty;
}
