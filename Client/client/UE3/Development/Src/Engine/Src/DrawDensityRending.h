/*=============================================================================
	DrawDensityRendering.h: Definitions for draw density(over draw).
	Copyright 1998-2013 Shanda Games, Inc. All Rights Reserved.
=============================================================================*/

/**
 * 
 */
class FDrawDensityDrawingPolicy : public FMeshDrawingPolicy
{
public:
	FDrawDensityDrawingPolicy(
		const FVertexFactory* InVertexFactory,
		const FMaterialRenderProxy* InMaterialRenderProxy,
		const FMaterialRenderProxy* InOriginalRenderProxy
		);

	// FMeshDrawingPolicy interface.
	UBOOL Matches(const FDrawDensityDrawingPolicy& Other) const
	{
		return FMeshDrawingPolicy::Matches(Other) &&
#if WITH_D3D11_TESSELLATION
			HullShader == Other.HullShader &&
			DomainShader == Other.DomainShader &&
#endif
			VertexShader == Other.VertexShader &&
			PixelShader == Other.PixelShader;
	}
	void DrawShared( const FSceneView* View, FBoundShaderStateRHIRef ShaderState ) const;
	void SetMeshRenderState(
		const FSceneView& View,
		const FPrimitiveSceneInfo* PrimitiveSceneInfo,
		const FMeshBatch& Mesh,
		INT BatchElementIndex,
		UBOOL bBackFace,
		const ElementDataType& ElementData
		) const;

	FBoundShaderStateRHIRef CreateBoundShaderState(DWORD DynamicStride = 0);

	friend INT Compare(const FDrawDensityDrawingPolicy& A,const FDrawDensityDrawingPolicy& B);

private:
	class FDrawDensityVertexShader*	VertexShader;
	class FDrawDensityPixelShader*	PixelShader;

#if WITH_D3D11_TESSELLATION
	class FTextureDensityHullShader* HullShader;
	class FTextureDensityDomainShader* DomainShader;
#endif

	const FMaterialRenderProxy*			OriginalRenderProxy;
};

/**
 * A drawing policy factory for rendering texture density.
 */
class FDrawDensityDrawingPolicyFactory
{
public:
	enum { bAllowSimpleElements = FALSE };
	struct ContextType {};

	static UBOOL DrawDynamicMesh(
		const FViewInfo& View,
		ContextType DrawingContext,
		const FMeshBatch& Mesh,
		UBOOL bBackFace,
		UBOOL bPreFog,
		const FPrimitiveSceneInfo* PrimitiveSceneInfo,
		FHitProxyId HitProxyId
		);
	static UBOOL IsMaterialIgnored(const FMaterialRenderProxy* MaterialRenderProxy)
	{
		return FALSE;
	}
};
