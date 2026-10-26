/*=============================================================================
	SilhouetteRendering.h: Mesh silhouettes rendering definitions.
	ming@snda
=============================================================================*/

#define SILHOUETTE_USE_POSTPROCESS 1

class FSilhouetteDrawingPolicy : public FMeshDrawingPolicy
{
public:
	FSilhouetteDrawingPolicy(
		const FVertexFactory* InVertexFactory,
		const FMaterialRenderProxy* InMaterialRenderProxy,
		const FMaterial& InMaterialResource
		);

	UBOOL Matches( const FSilhouetteDrawingPolicy& Other ) const
	{
		return FMeshDrawingPolicy::Matches( Other ) &&
#if 0 && WITH_D3D11_TESSELLATION
			HullShader == Other.HullShader &&
			DomainShader == Other.DomainShader &&
#endif
			VertexShader == Other.VertexShader &&
			PixelShader == Other.PixelShader;
	}

	void DrawShared( const FSceneView* View, FBoundShaderStateRHIRef ShaderState ) const;
	void SetMeshRenderState(
		const FViewInfo&			View,
		const FPrimitiveSceneInfo*	PrimitiveSceneInfo,
		const FMeshBatch&			Mesh,
		INT							BatchElementIndex,
		UBOOL						bBackFace,
		const ElementDataType&		ElementData ) const;

	FBoundShaderStateRHIRef CreateBoundShaderState( DWORD DynamicStride = 0 );

	UBOOL SupportsSilhouette() const;

private:
	class FSilhouetteVertexShader*	VertexShader;
	class FSilhouettePixelShader*	PixelShader;

#if 0 && WITH_D3D11_TESSELLATION
	class FSilhouetteHullShader*	HullShader;
	class FSilhouetteDomainShader*	DomainShader;
#endif
};

class FSilhouetteDrawingPolicyFactory : public FDepthDrawingPolicyFactory
{
public:
	static	void	AddStaticMesh( 
		FScene*			Scene, 
		FStaticMesh*	StaticMesh, 
		ContextType		= ContextType( DDM_AllOccluders ) );
	
	static	UBOOL	DrawDynamicMesh(
		const FViewInfo&			View,
		ContextType					DrawingContext,
		const FMeshBatch&			Mesh,
		UBOOL						bBackFace,
		UBOOL						bPreFog,
		const FPrimitiveSceneInfo*	PrimitiveSceneInfo,
		FHitProxyId					HidProxyId
		);
};