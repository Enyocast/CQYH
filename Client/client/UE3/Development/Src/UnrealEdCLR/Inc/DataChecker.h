#ifndef __DATACHECKER_H__
#define __DATACHECKER_H__

#ifdef _MSC_VER
#pragma once
#endif

class DataChecker
{
	enum
	{
		LEVEL1 = 1,
		LEVEL2,
	};
public:
	DataChecker();
	~DataChecker();

public:
	virtual bool IsValid(UObject* DataAsset, FString &Error, int nLevel = 1);
	void Init();
	FString GetAllErrorMsg();
private:
	//level1
	int nMaxTriangleCount1;
	int nMaxTextureWidth1;
	int nMaxTextureHeight1;
	int nMaxVertexShader1;
	int nMaxBasepassShaderWithLightmap1;
	int nMaxPointLightShader1;
	int nMaxSamplerUsage1;
	//level2
	int nMaxTriangleCount2;
	int nMaxTextureWidth2;
	int nMaxTextureHeight2;
	int nMaxVertexShader2;
	int nMaxBasepassShaderWithLightmap2;
	int nMaxPointLightShader2;
	int nMaxSamplerUsage2;

	int nStaticMeshCount;
	int nStaticMeshErrorCount;
	int nMaterialCount;
	int nMaterialErrorCount;
	int nMaterialInstanceCount;
	int nMaterialInstanceErrorCount;
	int nTextureCount;
	int nTextureErrorCount;

};


#endif //__DATACHECKER_H__