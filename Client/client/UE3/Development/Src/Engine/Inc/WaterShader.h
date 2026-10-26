#ifndef _WATERSHADER_H_
#define _WATERSHADER_H_

#include "WaterConfig.h"
#include "TessellationRendering.h"

#if WITH_WATER
//------------------------------------------------------------------------
// pixel shader
//------------------------------------------------------------------------
class FWaterPixelShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FWaterPixelShader,MeshMaterial);

public:
	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType);

	FWaterPixelShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer );

	FWaterPixelShader();

	void SetParameters(const FVertexFactory* VertexFactory,const FMaterialRenderProxy* MaterialRenderProxy,const FViewInfo& View);

	void SetMesh(const FPrimitiveSceneInfo* PrimitiveSceneInfo,const FMeshBatch& Mesh,INT BatchElementIndex,const FViewInfo& View,UBOOL bBackFace);

	// setup the pixel shader parameters
	//void SetupParameters( const FPrimitiveSceneInfo* PrimitiveSceneInfo );

	virtual UBOOL Serialize( FArchive& Ar );

	static void ModifyCompilationEnvironment(EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment)
	{
		if(Platform == SP_PCD3D_SM5)
		{
			OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));
		}
	}

private:
	FMaterialPixelShaderParameters	MaterialParameters;
//	FShaderParameter	GameTime;
	FShaderParameter	WaterDeepColor;
	FShaderParameter	WaterScatterColor;
	FShaderParameter	WaterScatterColorPower;
	FShaderParameter	WaterSpecularColor;
	FShaderParameter	WaterSpecularIntensity;
	FShaderParameter	WaterSpecularPower;
	FShaderParameter	WaterScatterColorIntensity;

	FShaderParameter	WaterBumpTexcoordShift;

	FShaderParameter	LightPosition;
	FShaderParameter	CameraPosition;
	FShaderParameter	CameraDirection;

	FShaderParameter	ScreenSizeInv;
	FShaderParameter	ZNear;
	FShaderParameter	ZFar;

	FShaderParameter	WaterColorIntensity;
	
	FShaderParameter	ModelViewMatrix;	
	FShaderParameter	ModelViewProjectionMatrix;

	FShaderParameter	LightModelViewMatrix;
	FShaderParameter	ReflectionIntensity;

	// fog parameters
	FShaderParameter	FogDensity;
	FShaderParameter	AtmosphereBrightColor;
	FShaderParameter	AtmosphereDarkColor;

	FShaderResourceParameter WaterBumpTexture;
	FShaderResourceParameter FoamTexture;
	FShaderResourceParameter DepthTexture;

	FShaderResourceParameter DepthMapTexture;

	FSceneTextureShaderParameters SceneTextureParameters;
	//FShaderResourceParameter ReflectionCubeTexture;
	FShaderResourceParameter ReflectionTexture;
	FShaderResourceParameter RefractionTexture;
	FShaderResourceParameter RefractionDepthTextureResolved;
};





//------------------------------------------------------------------------
// vertex shader
//------------------------------------------------------------------------
class FWaterVertexShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FWaterVertexShader,MeshMaterial);

public:

	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType);

	void SetParameters( 
		const FVertexFactory* VertexFactory, 
		const FMaterialRenderProxy* MaterialRenderProxy, 
		const FViewInfo& View );

	void SetMesh(
		const FPrimitiveSceneInfo* PrimitiveSceneInfo,
		const FMeshBatch& Mesh, 
		INT BatchElementIndex,
		const FViewInfo& View );

	static void ModifyCompilationEnvironment(EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment)
	{
		if(Platform == SP_PCD3D_SM5)
		{
			OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));
		}
	}

protected:
	FWaterVertexShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer );

	FWaterVertexShader();

	virtual UBOOL Serialize( FArchive& Ar );

private:
	FMaterialVertexShaderParameters	MaterialParameters;

	FShaderParameter	LocalToWorld;
};

#if WITH_D3D11_TESSELLATION
class FWaterVertexShader_NoTess : public FWaterVertexShader
{
	DECLARE_SHADER_TYPE(FWaterVertexShader_NoTess,MeshMaterial);

public:
	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType);

	void SetMesh(
		const FPrimitiveSceneInfo* PrimitiveSceneInfo,
		const FMeshBatch& Mesh,
		INT BatchElementIndex,
		const FViewInfo& View );

	static void ModifyCompilationEnvironment(EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment)
	{
		//if(Platform == SP_PCD3D_SM5)
		//{
			OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));
		//}
	}

protected:
	FWaterVertexShader_NoTess( const ShaderMetaType::CompiledShaderInitializerType& Initializer );

	FWaterVertexShader_NoTess()
	{
	}

	virtual UBOOL Serialize( FArchive& Ar );

private:
	FShaderParameter	WaterBumpTexcoordShift;
	FShaderParameter	WaterMicroBumpTexcoordScale;
	FShaderParameter	WaterBumpTexcoordScale;
	FShaderParameter	WaterHeightBumpScale;
	FShaderParameter	HeightFieldSize;
	FShaderParameter	ModelViewProjectionMatrix;

	FShaderResourceParameter	SamplerLinearWrap;
	FShaderResourceParameter	WaterBumpTexture;
};

//------------------------------------------------------------------------
// hull shader
//------------------------------------------------------------------------
class FWaterHullShader : public FBaseHullShader
{
	DECLARE_SHADER_TYPE(FWaterHullShader,MeshMaterial);
public:

	void SetParameters( const FMaterialRenderProxy* MaterialRenderProxy, const FViewInfo& View );
	
	void SetMesh(
		const FPrimitiveSceneInfo* PrimitiveSceneInfo,
		const FMeshBatch& Mesh, 
		INT BatchElementIndex,
		const FViewInfo& View );

	static void ModifyCompilationEnvironment(EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment)
	{
		if(Platform == SP_PCD3D_SM5)
		{
			OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));
		}
		//new(OutEnvironment.CompilerFlags) ECompilerFlags(CFLAG_Debug);
	}

protected:
	FWaterHullShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer );

	FWaterHullShader();

	virtual UBOOL Serialize( FArchive& Ar );


	static UBOOL ShouldCache( 
		EShaderPlatform Platform, 
		const FMaterial* Material, 
		const FVertexFactoryType* VertexFactoryType );

	//FShaderParameter	GameTime;

	FShaderParameter	FrustumCullInHS;

	FShaderParameter	UseDynamicLOD;
	FShaderParameter	DynamicTessFactor;
	FShaderParameter	StaticTessFactor;

	FShaderParameter	CameraPosition;
	FShaderParameter	CameraDirection;
	FShaderParameter	ModelViewProjectionMatrix;

	//FShaderParameter	LocalToWorld;
};





//------------------------------------------------------------------------
// domain shader
//------------------------------------------------------------------------
class FWaterDomainShader : public FBaseDomainShader
{
	DECLARE_SHADER_TYPE(FWaterDomainShader,MeshMaterial);

public:
	void SetParameters( const FMaterialRenderProxy* MaterialRenderProxy, const FViewInfo& View );
	
	void SetMesh(
		const FPrimitiveSceneInfo* PrimitiveSceneInfo,
		const FMeshBatch& Mesh, 
		INT BatchElementIndex,
		const FViewInfo& View );

	static void ModifyCompilationEnvironment(EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment)
	{
		if(Platform == SP_PCD3D_SM5)
		{
			OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));
		}
	}

protected:
	FWaterDomainShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer );

	FWaterDomainShader();

	virtual UBOOL Serialize( FArchive& Ar );

	static UBOOL ShouldCache( 
		EShaderPlatform Platform,
		const FMaterial* Material,
		const FVertexFactoryType* VertexFactoryType );

	//FShaderParameter	GameTime;

	FShaderParameter	WaterBumpTexcoordShift;

	FShaderParameter	CameraPosition;
	FShaderParameter	ModelViewProjectionMatrix;

	//FShaderParameter	UseDynamicLOD;
	//FShaderParameter	DynamicTessFactor;
	//FShaderParameter	StaticTessFactor;

	FShaderParameter	WaterMicroBumpTexcoordScale;
	FShaderParameter	WaterBumpTexcoordScale;
	FShaderParameter	WaterHeightBumpScale;

	FShaderParameter	HeightFieldSize;

	//FShaderParameter	WaterSizeScale;

	FShaderResourceParameter	SamplerLinearWrap;

	FShaderResourceParameter WaterBumpTexture;
	FShaderResourceParameter DepthMapTexture;

	//FShaderParameter	LocalToWorld;

};


#endif


#endif

#endif // WITH_WATER
