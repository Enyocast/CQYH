/*=============================================================================
	ParticleRainStreakVertexFactory.h
	ming@snda
=============================================================================*/

/**
 *	
 */
class FParticleRainStreakVertexFactory : public FParticleVertexFactory
{
	DECLARE_VERTEX_FACTORY_TYPE(FParticleRainStreakVertexFactory);

public:
	/**
	 * Should we cache the material's shadertype on this platform with this vertex factory? 
	 */
	static UBOOL ShouldCache(EShaderPlatform Platform, const class FMaterial* Material, const class FShaderType* ShaderType);

	// FRenderResource interface.
	virtual void InitRHI();

	static FVertexFactoryShaderParameters* ConstructShaderParameters(EShaderFrequency ShaderFrequency);

	static void ModifyCompilationEnvironment(EShaderPlatform Platform,
		FShaderCompilerEnvironment& OutEnvironment)
	{
		FParticleVertexFactory::ModifyCompilationEnvironment(Platform, OutEnvironment);
		OutEnvironment.Definitions.Set(TEXT("USE_PARTICLE_CAMERA_OFFSET"),TEXT("1"));

		// shader debug
		//if( Platform == SP_PCD3D_SM5 )
		//	new(OutEnvironment.CompilerFlags) ECompilerFlags(CFLAG_Debug);
	}

	FORCEINLINE void SetOffset( const FVector& offset )
	{
		Offset = offset;
	}

	FORCEINLINE void SetBound( const FVector& bound )
	{
		Bound = bound;
	}

	FORCEINLINE void SetHalfBound( const FVector& halfBound )
	{
		HalfBound = halfBound;
	}

	FORCEINLINE void SetForwardOffset( const FVector& forwardOffset )
	{
		ForwardOffset = forwardOffset;
	}

	//FORCEINLINE void SetLifeTime( FLOAT time )
	//{
	//	LifeTime = time;
	//}

	FORCEINLINE const FVector& GetOffset() const
	{
		return Offset;
	}

	FORCEINLINE const FVector& GetBound() const
	{
		return Bound;
	}

	FORCEINLINE const FVector& GetHalfBound() const
	{
		return HalfBound;
	}

	FORCEINLINE const FVector& GetForwardOffset() const
	{
		return ForwardOffset;
	}

	//FORCEINLINE FLOAT GetLifeTime() const
	//{
	//	return LifeTime;
	//}

private:
	FVector	Offset;
	FVector	Bound;
	FVector	HalfBound;
	FVector	ForwardOffset;
	//FLOAT	LifeTime;
};

class FParticleRainStreakVertexFactoryShaderParameters : public FParticleVertexFactoryShaderParameters
{
public:
	virtual void Bind(const FShaderParameterMap& ParameterMap)
	{
		// Dump all the parameters...
		FParticleVertexFactoryShaderParameters::Bind( ParameterMap );

		CameraSpaceOffsetParameter.Bind(ParameterMap,TEXT("CameraSpaceOffset"),TRUE);
		BoundParameter.Bind(ParameterMap,TEXT("Bound"),TRUE);
		HalfBoundParameter.Bind(ParameterMap,TEXT("HalfBound"),TRUE);
		ForwardOffsetParameter.Bind(ParameterMap,TEXT("ForwardOffset"),TRUE);
		//LifeTimeParameter.Bind(ParameterMap,TEXT("LifeTime"),TRUE);
	}

	virtual void Serialize(FArchive& Ar)
	{
		FParticleVertexFactoryShaderParameters::Serialize(Ar);

		Ar << CameraSpaceOffsetParameter;
		Ar << BoundParameter;
		Ar << HalfBoundParameter;
		Ar << ForwardOffsetParameter;
		//Ar << LifeTimeParameter;

		CameraSpaceOffsetParameter.SetShaderParamName(TEXT("CameraSpaceOffset"));
		BoundParameter.SetShaderParamName(TEXT("Bound"));
		HalfBoundParameter.SetShaderParamName(TEXT("HalfBound"));
		ForwardOffsetParameter.SetShaderParamName(TEXT("ForwardOffset"));
		//LifeTimeParameter.SetShaderParamName(TEXT("LifeTime"));
	}

	virtual void Set(FShader* VertexShader,const FVertexFactory* VertexFactory,const FSceneView& View) const;

	virtual void SetMesh(FShader* VertexShader, const FMeshBatch& Mesh, INT BatchElementIndex, const FSceneView& View) const;

private:
	FShaderParameter CameraSpaceOffsetParameter;	// cpu calculated offset
	FShaderParameter BoundParameter;				// unit quad size of the original particles
	FShaderParameter HalfBoundParameter;			// for saving calculation time
	FShaderParameter ForwardOffsetParameter;		// view quad offset
	//FShaderParameter LifeTimeParameter;				// particle life time
};