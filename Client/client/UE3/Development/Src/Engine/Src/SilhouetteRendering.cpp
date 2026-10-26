/*=============================================================================
	SilhouetteRendering.cpp: Mesh silhouettes rendering definitions.
	ming@snda
=============================================================================*/

#include "EnginePrivate.h"
#include "EngineParticleClasses.h"
#include "ScenePrivate.h"
#include "UnSkeletalRender.h"

// vertex shader
class FSilhouetteVertexShader : public FMeshMaterialVertexShader
{
	DECLARE_SHADER_TYPE(FSilhouetteVertexShader,MeshMaterial);

public:

	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
	{
		//Only compile the velocity shaders for the default material or if it's masked,
		return (Material->IsSpecialEngineMaterial() || Material->IsMasked() 
			//or if the material is opaque and two-sided,
			|| (Material->IsTwoSided() && !IsTranslucentBlendMode(Material->GetBlendMode()))
			// or if the material modifies meshes
			|| Material->MaterialModifiesMeshPosition()) 
			//and exclude decal materials.
			&& !Material->IsDecalMaterial();
	}

	void SetParameters( 
		const FVertexFactory* VertexFactory, 
		const FMaterialRenderProxy* MaterialRenderProxy, 
		const FViewInfo& View )
	{
		FMaterialRenderContext MaterialRenderContext( MaterialRenderProxy, 
			*MaterialRenderProxy->GetMaterial(),
			View.Family->CurrentWorldTime,
			View.Family->CurrentRealTime, &View );
		MaterialParameters.Set( this, MaterialRenderContext );

		VertexFactoryParameters.Set( this, VertexFactory, View );
	}

	void SetMesh(
		const FPrimitiveSceneInfo* PrimitiveSceneInfo,
		const FMeshBatch& Mesh, 
		INT BatchElementIndex,
		const FViewInfo& View )
	{
		VertexFactoryParameters.SetMesh(this,Mesh,BatchElementIndex,View);
		MaterialParameters.SetMesh( this, PrimitiveSceneInfo, Mesh, BatchElementIndex, View );
	}

protected:
	FSilhouetteVertexShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer ):
		 FMeshMaterialVertexShader( Initializer )
	{
		MaterialParameters.Bind( Initializer.ParameterMap );
	}

	FSilhouetteVertexShader() {}

	virtual UBOOL Serialize( FArchive& Ar )
	{
		UBOOL bShaderHasOutdatedParameters = FShader::Serialize( Ar );
		bShaderHasOutdatedParameters |= Ar << VertexFactoryParameters;
		Ar << MaterialParameters;
		return bShaderHasOutdatedParameters;
	}

private:
	FMaterialVertexShaderParameters	MaterialParameters;
};

IMPLEMENT_MATERIAL_SHADER_TYPE(,FSilhouetteVertexShader,TEXT("SilhouetteShader"),TEXT("MainVertexShader"),SF_Vertex,0,0);

#if 0 && WITH_D3D11_TESSELLATION

// hull shader
class FSilhouetteHullShader : public FBaseHullShader
{
	DECLARE_SHADER_TYPE(FSilhouetteHullShader,MeshMaterial);

protected:
	FSilhouetteHullShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer ) :
		 FBaseHullShader( Initializer )
	{}

	FSilhouetteHullShader() {}

	static UBOOL ShouldCache( 
		EShaderPlatform Platform, 
		const FMaterial* Material, 
		const FVertexFactoryType* VertexFactoryType )
	{
		return FBaseHullShader::ShouldCache( Platform, Material, VertexFactoryType )
			&& FSilhouetteVertexShader::ShouldCache( Platform, Material, VertexFactoryType );
	}
};

IMPLEMENT_MATERIAL_SHADER_TYPE(,FSilhouetteHullShader,TEXT("SilhouetteShader"),TEXT("MainHull"),SF_Hull,0,0);

// domain shader
class FSilhouetteDomainShader : public FBaseDomainShader
{
	DECLARE_SHADER_TYPE(FSilhouetteDomainShader,MeshMaterial);

public:
	void SetParameters( const FMaterialRenderProxy* MaterialRenderProxy, const FViewInfo& View )
	{
		FBaseDomainShader::SetParameters( MaterialRenderProxy, View );
	}

protected:
	FSilhouetteDomainShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer ) :
		 FBaseDomainShader( Initializer )
	{}

	FSilhouetteDomainShader() {}

	virtual UBOOL Serialize( FArchive& Ar )
	{
		return FBaseDomainShader::Serialize( Ar );
	}

	static UBOOL ShouldCache( 
		EShaderPlatform Platform,
		const FMaterial* Material,
		const FVertexFactoryType* VertexFactoryType )
	{
		return FBaseDomainShader::ShouldCache( Platform, Material, VertexFactoryType )
			&& FSilhouetteVertexShader::ShouldCache( Platform, Material, VertexFactoryType );
	}
};

IMPLEMENT_MATERIAL_SHADER_TYPE(,FSilhouetteDomainShader,TEXT("SilhouetteShader"),TEXT("MainDomain"),SF_Domain,0,0);

#endif

// pixel shader
class FSilhouettePixelShader : public FShader
{
	DECLARE_SHADER_TYPE(FSilhouettePixelShader,MeshMaterial);

public:
	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
	{
		//Only compile the velocity shaders for the default material or if it's masked,
		return (Material->IsSpecialEngineMaterial() || Material->IsMasked() 
			//or if the material is opaque and two-sided,
			|| (Material->IsTwoSided() && !IsTranslucentBlendMode(Material->GetBlendMode()))
			// or if the material modifies meshes
			|| Material->MaterialModifiesMeshPosition()) 
			//and exclude decal materials.
			&& !Material->IsDecalMaterial();
	}

	FSilhouettePixelShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer ) : FShader( Initializer )
	{
		MaterialParameters.Bind( Initializer.ParameterMap );
		SilhouetteColor.Bind( Initializer.ParameterMap, TEXT("SilhouetteColor"), FALSE );
	}

	FSilhouettePixelShader() {}

	void SetParameters(const FVertexFactory* VertexFactory,const FMaterialRenderProxy* MaterialRenderProxy,const FViewInfo& View)
	{
		FMaterialRenderContext MaterialRenderContext(MaterialRenderProxy, *MaterialRenderProxy->GetMaterial(), View.Family->CurrentWorldTime, View.Family->CurrentRealTime, &View);
		MaterialParameters.Set( this, MaterialRenderContext );
	}

	void SetMesh(const FPrimitiveSceneInfo* PrimitiveSceneInfo,const FMeshBatch& Mesh,INT BatchElementIndex,const FViewInfo& View,UBOOL bBackFace)
	{
		MaterialParameters.SetMesh( this, PrimitiveSceneInfo, Mesh, BatchElementIndex, View, bBackFace );
	}

	void SetColor( const FPrimitiveSceneInfo* PrimitiveSceneInfo )
	{
		SetShaderValue( GetPixelShader(), SilhouetteColor, PrimitiveSceneInfo->Proxy->GetSilhouetteColor() );
	}

	virtual UBOOL Serialize( FArchive& Ar )
	{
		UBOOL bShaderHasOutdatedParameters = FShader::Serialize( Ar );
		Ar << MaterialParameters;
		Ar << SilhouetteColor;
		return bShaderHasOutdatedParameters;
	}

private:
	FMaterialPixelShaderParameters	MaterialParameters;
	FShaderParameter	SilhouetteColor;
};

IMPLEMENT_MATERIAL_SHADER_TYPE(,FSilhouettePixelShader,TEXT("SilhouetteShader"),TEXT("MainPixelShader"),SF_Pixel,VER_IMPROVED_MOTIONBLUR2,0);

// drawing policy
FSilhouetteDrawingPolicy::FSilhouetteDrawingPolicy( 
	const FVertexFactory*		InVertexFactory,
	const FMaterialRenderProxy*	InMaterialRenderProxy,
	const FMaterial&			InMaterialResource ) :
	FMeshDrawingPolicy( InVertexFactory, InMaterialRenderProxy, InMaterialResource )
{
	const FMaterialShaderMap* MaterialShaderIndex = InMaterialResource.GetShaderMap();
	const FMeshMaterialShaderMap* MeshShaderIndex = MaterialShaderIndex->GetMeshShaderMap( InVertexFactory->GetType() );

	UBOOL HasVertexShader = MeshShaderIndex->HasShader( &FSilhouetteVertexShader::StaticType );
	VertexShader = HasVertexShader ? MeshShaderIndex->GetShader<FSilhouetteVertexShader>() : NULL;

	UBOOL HasPixelShader = MeshShaderIndex->HasShader( & FSilhouettePixelShader::StaticType );
	PixelShader = HasPixelShader ? MeshShaderIndex->GetShader<FSilhouettePixelShader>() : NULL;

#if 0 && WITH_D3D11_TESSELLATION
	HullShader = NULL;
	DomainShader = NULL;

	const EMaterialTessellationMode MaterialTessellationMode = InMaterialResource.GetD3D11TessellationMode();
	if( GRHIShaderPlatform == SP_PCD3D_SM5
		&& InVertexFactory->GetType()->SupportsTessellationShaders()
		&& MaterialTessellationMode != MTM_NoTessellation )
	{
		UBOOL HasHullShader = MeshShaderIndex->HasShader( &FSilhouetteHullShader::StaticType );
		if( HasHullShader )
			HullShader = MeshShaderIndex->GetShader< FSilhouetteHullShader >();

		UBOOL HasDomainShader = MeshShaderIndex->HasShader( &FSilhouetteDomainShader::StaticType );
		if( HasDomainShader )
			DomainShader = MeshShaderIndex->GetShader< FSilhouetteDomainShader >();
	}
#endif
}

void FSilhouetteDrawingPolicy::DrawShared( const FSceneView* SceneView, FBoundShaderStateRHIRef ShaderState ) const
{
	FViewInfo* View = (FViewInfo*)SceneView;
	RHISetBoundShaderState( ShaderState );

	VertexShader->SetParameters( VertexFactory, MaterialRenderProxy, *View );
	PixelShader->SetParameters( VertexFactory, MaterialRenderProxy, *View );

#if 0 && WITH_D3D11_TESSELLATION
	if( HullShader && DomainShader )
	{
		HullShader->SetParameters( MaterialRenderProxy, *View );
		DomainShader->SetParameters( MaterialRenderProxy, *View );
	}
#endif

	FMeshDrawingPolicy::DrawShared( SceneView );
}

void FSilhouetteDrawingPolicy::SetMeshRenderState( 
	const FViewInfo& View,
	const FPrimitiveSceneInfo* PrimitiveSceneInfo,
	const FMeshBatch& Mesh,
	INT BatchElementIndex,
	UBOOL bBackFace,
	const ElementDataType& ElementData ) const
{
	VertexShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View );

#if 0 && WITH_D3D11_TESSELLATION
	if( HullShader && DomainShader )
	{
		DomainShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View );
		HullShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View );
	}
#endif

	PixelShader->SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View, bBackFace );
	PixelShader->SetColor( PrimitiveSceneInfo );

	FMeshDrawingPolicy::SetMeshRenderState( View, PrimitiveSceneInfo, Mesh, BatchElementIndex, bBackFace, ElementData );
}

FBoundShaderStateRHIRef FSilhouetteDrawingPolicy::CreateBoundShaderState( DWORD DynamicStride )
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
		NULL,//GETSAFERHISHADER_HULL(HullShader),
		NULL,//GETSAFERHISHADER_DOMAIN(DomainShader),
		PixelShader->GetPixelShader(),
		FGeometryShaderRHIRef(),
		EGST_None );
#else
	BoundShaderState = RHICreateBoundShaderState( VertexDeclaration, StreamStrides, VertexShader->GetVertexShader(), PixelShader->GetPixelShader(), EGST_None); // oscar@snda
#endif

	return BoundShaderState;
}

UBOOL FSilhouetteDrawingPolicy::SupportsSilhouette() const
{
	return ( VertexShader && PixelShader ) ? TRUE : FALSE;
}

// policy factory
void FSilhouetteDrawingPolicyFactory::AddStaticMesh( FScene* Scene, FStaticMesh* StaticMesh, ContextType )
{
	if( StaticMesh->PrimitiveSceneInfo->Proxy->GetSilhouette() )
	{
		const FMaterialRenderProxy* MaterialRenderProxy = StaticMesh->MaterialRenderProxy;
		const FMaterial* Material = MaterialRenderProxy->GetMaterial();
		EBlendMode BlendMode = Material->GetBlendMode();

		if ( (BlendMode == BLEND_Opaque || BlendMode == BLEND_Masked || BlendMode == BLEND_SoftMasked || BlendMode == BLEND_DitheredTranslucent) && !Material->IsDecalMaterial() )
		{
			if( !Material->IsMasked() && !Material->IsTwoSided() && !Material->MaterialModifiesMeshPosition() )
			{
				MaterialRenderProxy = GEngine->DefaultMaterial->GetRenderProxy(FALSE);
			}
			FSilhouetteDrawingPolicy DrawingPolicy( StaticMesh->VertexFactory, MaterialRenderProxy, *MaterialRenderProxy->GetMaterial() );
			if( DrawingPolicy.SupportsSilhouette() )
			{
				Scene->DPGs[StaticMesh->DepthPriorityGroup].SilhouetteDrawList.AddMesh(
					StaticMesh,
					FSilhouetteDrawingPolicy::ElementDataType(),
					DrawingPolicy
					);
			}
		}
	}
}

UBOOL FSilhouetteDrawingPolicyFactory::DrawDynamicMesh(
	const FViewInfo&		View,
	ContextType				DrawingContext,
	const FMeshBatch&		Mesh,
	UBOOL					bBackFace,
	UBOOL					bPreFog,
	const FPrimitiveSceneInfo*	PrimitiveSceneInfo,
	FHitProxyId				HitProxyId )
{
	const FMaterialRenderProxy* MaterialRenderProxy = Mesh.MaterialRenderProxy;
	const FMaterial* Material = MaterialRenderProxy->GetMaterial();
	EBlendMode BlendMode = Material->GetBlendMode();

	if ( ( BlendMode == BLEND_Translucent || BlendMode == BLEND_Opaque || BlendMode == BLEND_Masked || BlendMode == BLEND_SoftMasked || BlendMode == BLEND_DitheredTranslucent) && !Material->IsDecalMaterial() )
	{
		if( !Material->IsMasked() /*&& !Material->IsTwoSided()*/ && !Material->MaterialModifiesMeshPosition() )
		{
			MaterialRenderProxy = GEngine->DefaultMaterial->GetRenderProxy(FALSE);
		}
		FSilhouetteDrawingPolicy DrawingPolicy( Mesh.VertexFactory, MaterialRenderProxy, *MaterialRenderProxy->GetMaterial() );
		if( DrawingPolicy.SupportsSilhouette() )
		{
			DrawingPolicy.DrawShared( &View, DrawingPolicy.CreateBoundShaderState( Mesh.GetDynamicVertexStride() ) );
			for( INT BatchElementIndex=0;BatchElementIndex < Mesh.Elements.Num();BatchElementIndex++ )
			{
				DrawingPolicy.SetMeshRenderState( View, PrimitiveSceneInfo, Mesh, BatchElementIndex, bBackFace, FMeshDrawingPolicy::ElementDataType() );
				DrawingPolicy.DrawMesh( Mesh, BatchElementIndex );
			}
			return TRUE;
		}
	}
	return FALSE;
}


// rendering
void FSceneRenderer::RenderSilhouettes( UINT DPGIndex )
{
	SCOPED_DRAW_EVENT(EventSilhouettes)(DEC_SCENE_ITEMS,TEXT("RenderSilhouettes"));
	SCOPE_CONDITIONAL_CYCLE_COUNTER(STAT_SilhouetteDrawTime, !bIsSceneCapture );

#if SILHOUETTE_USE_POSTPROCESS
	GSceneRenderTargets.BeginRenderingSilhouettes();
#endif
	for( INT ViewIndex = 0; ViewIndex < Views.Num(); ++ViewIndex )
	{
		UBOOL bDirty = FALSE;

		FViewInfo& view = Views( ViewIndex );
		const UINT MinX = view.RenderTargetX;	// todo: deal with different resolutions
		//const UINT MaxX = view.RenderTargetX + GSceneRenderTargets.GetSilhouetteBufferSizeX();
		const UINT MaxX = view.RenderTargetX + view.RenderTargetSizeX;
		const UINT MinY = view.RenderTargetY;
		//const UINT MaxY = view.RenderTargetY + GSceneRenderTargets.GetSilhouetteBufferSizeY();
		const UINT MaxY = view.RenderTargetY + view.RenderTargetSizeY;
		RHISetViewport( MinX, MinY, 0.f, MaxX, MaxY, 1.f );
		RHISetViewParameters( view );

#if SILHOUETTE_USE_POSTPROCESS
		//RHIClear( TRUE, FLinearColor( 0.f, 0.f, 0.f, 0.f ), FALSE, 1.f, TRUE, 0 );
		RHIClear( TRUE, FLinearColor( 0.f, 0.f, 0.f, 0.f ), FALSE, 1.f, FALSE, 0 );

		RHISetBlendState( TStaticBlendState< BO_Add, BF_One, BF_Zero, BO_Add, BF_One, BF_Zero, CF_Greater, 50 >::GetRHI() );
		RHISetDepthState( TStaticDepthState<FALSE,CF_LessEqual>::GetRHI() );
		//RHISetStencilState( TStaticStencilState<TRUE,CF_Always,SO_Keep,SO_Keep,SO_SaturatedIncrement>::GetRHI() );
		static FLOAT DepthBias = 0.f;
		const FRasterizerStateInitializerRHI RasterState = {
			FM_Solid, CM_CCW, DepthBias, 0.f, TRUE };
		RHISetRasterizerStateImmediate( RasterState );
#else
		RHISetBlendState( TStaticBlendState<>::GetRHI() );
		RHISetDepthState( TStaticDepthState<>::GetRHI() );
		static FLOAT DepthBias = 0.f;
		const FRasterizerStateInitializerRHI RasterState = {
			FM_Solid, CM_CW, DepthBias, 0.f, TRUE };
		RHISetRasterizerStateImmediate( RasterState );
#endif

		bDirty |= Scene->DPGs[DPGIndex].SilhouetteDrawList.DrawVisible( view, view.StaticMeshVisibilityMap );

		TDynamicPrimitiveDrawer< FSilhouetteDrawingPolicyFactory > Drawer(
			&view, DPGIndex, FSilhouetteDrawingPolicyFactory::ContextType(DDM_AllOccluders), TRUE );
		for( INT PrimitiveIndex = 0; PrimitiveIndex < view.VisibleDynamicPrimitives.Num(); ++PrimitiveIndex )
		{
			const FPrimitiveSceneInfo* PrimitiveSceneInfo = view.VisibleDynamicPrimitives(PrimitiveIndex);
			const FPrimitiveViewRelevance& PrimitiveViewRelevance = view.PrimitiveViewRelevanceMap(PrimitiveSceneInfo->Id);
			const UBOOL bVisible = view.PrimitiveVisibilityMap(PrimitiveSceneInfo->Id);

			if( bVisible && 
				PrimitiveSceneInfo->Proxy->GetSilhouette() &&
				//Cast<USkeletalMeshComponent>( PrimitiveSceneInfo->Component ) &&
				( PrimitiveViewRelevance.bOpaqueRelevance || PrimitiveViewRelevance.bTranslucentRelevance ) && 
				PrimitiveViewRelevance.GetDPG( DPGIndex ) )
			{
				#if !SILHOUETTE_USE_POSTPROCESS
					float oldScale = PrimitiveSceneInfo->Component->Scale;
					PrimitiveSceneInfo->Component->Scale *= 1.5f;
					PrimitiveSceneInfo->Component->BeginDeferredUpdateTransform();
				#endif

				Drawer.SetPrimitive( PrimitiveSceneInfo );
				PrimitiveSceneInfo->Proxy->DrawDynamicElements( &Drawer, &view, DPGIndex );

				bDirty |= Drawer.IsDirty();

				#if !SILHOUETTE_USE_POSTPROCESS
					PrimitiveSceneInfo->Component->Scale = oldScale;
					PrimitiveSceneInfo->Component->BeginDeferredUpdateTransform();
				#endif
			}
		}

		if( bDirty )
		{
			// tell the post process effect to draw silhouette
			view.bRenderedToSilhouetteBuffer = TRUE;
		}
		else
		{
			view.bRenderedToSilhouetteBuffer = FALSE;
		}
	}
#if SILHOUETTE_USE_POSTPROCESS
	GSceneRenderTargets.FinishRenderingSilhouettes();
#endif
}