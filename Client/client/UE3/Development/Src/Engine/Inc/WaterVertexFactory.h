#ifndef _WATERVERTEXFACTORY_H_
#define _WATERVERTEXFACTORY_H_

#include "WaterConfig.h"

#if WITH_WATER
//------------------------------------------------------------------------
// FWaterVertexFactory
//------------------------------------------------------------------------

#define DISABLE_WATER_VF 0

class FWaterVertexFactory : public FVertexFactory, public FRefCountedObject
{

#if !DISABLE_WATER_VF
	DECLARE_VERTEX_FACTORY_TYPE(FWaterVertexFactory);
#else

public:
	virtual FVertexFactoryType* GetType() const;

#endif

public:

	FWaterVertexFactory()
	{
	}

	virtual ~FWaterVertexFactory()
	{
		ReleaseResource();
	}

	static FVertexFactoryShaderParameters* ConstructShaderParameters(EShaderFrequency ShaderFrequency);

	struct DataType
	{
		/** The stream to read the vertex position from. */
		FVertexStreamComponent PositionComponent;
	};

	/**
	* Should we cache the material's shadertype on this platform with this vertex factory? 
	*/
	static UBOOL ShouldCache(EShaderPlatform Platform, const class FMaterial* Material, const class FShaderType* ShaderType)
	{
#if MOBILE
		return FALSE;
#endif

		if ( appStrstr(ShaderType->GetShaderFilename(),TEXT("WaterShader")) )
		{
			return TRUE;
		}

		return FALSE;
		// only compile landscape materials for landscape vertex factory
		// The special engine materials must be compiled for the landscape vertex factory because they are used with it for wireframe, etc.
		//return (Platform==SP_PCD3D_SM3 || Platform==SP_PCD3D_SM4 || Platform==SP_PCD3D_SM5 || Platform==SP_PCOGL || Platform==SP_XBOXD3D || Platform==SP_PS3) && (Material->IsUsedWithLandscape() || Material->IsSpecialEngineMaterial()); // && !Material->IsUsedWithDecals();
	}

	/**
	* Can be overridden by FVertexFactory subclasses to modify their compile environment just before compilation occurs.
	*/
	static void ModifyCompilationEnvironment(EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment)
	{
		if(Platform ==	SP_PCD3D_SM5)
		{
			OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));
		}
	}
	
	/**
	* Copy the data from another vertex factory
	* @param Other - factory to copy from
	*/
	void Copy(const FWaterVertexFactory& Other);

	/**
	* Vertex factory interface for creating a corresponding decal vertex factory
	* Copies the data from this existing vertex factory.
	*
	* @return new allocated decal vertex factory
	*/
	virtual class FDecalVertexFactoryBase* CreateDecalVertexFactory() const;

	// FRenderResource interface.
	virtual void InitRHI();

	static UBOOL SupportsTessellationShaders() { return TRUE; }

#if !PS3
	virtual void GetStaticBatchElementVisibility( const class FSceneView& View, const struct FMeshBatch* Batch, TArray<INT>& BatchesToRender ) const;
#endif

	/** stream component data bound to this vertex factory */
	DataType Data;  
};


#endif

#endif // WITH_WATER