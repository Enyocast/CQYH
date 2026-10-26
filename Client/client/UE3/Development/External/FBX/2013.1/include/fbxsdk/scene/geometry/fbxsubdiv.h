/****************************************************************************************
 
   Copyright (C) 2011 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxsubdiv.h
#ifndef _FBXSDK_SCENE_GEOMETRY_SUB_DIV_H_
#define _FBXSDK_SCENE_GEOMETRY_SUB_DIV_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/scene/geometry/fbxgeometry.h>

#include <fbxsdk/core/math/fbxvector4.h>
#include <fbxsdk/core/math/fbxvector2.h>

#include <fbxsdk/core/base/fbxarray.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxMesh;
class FbxManager;

///////////////////////////////////////////////////////////////////////////////
//  WARNING!
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS

class FBXSDK_DLL FbxSubDiv : public FbxGeometry
{
    FBXSDK_OBJECT_DECLARE(FbxSubDiv,FbxGeometry);

public:

    enum SubdivScheme
    {
        CATMULL_CLARK,  //Catmull¨CClark subdivision surface
        DOO_SABIN,      //Doo¨CSabin subdivision surface
        LOOP,           //Loop subdivision surface
        LINEAR,         //Linear subdivision surface 
    };

    enum TessPattern
    {
        ODD_FRACTIONAL,
        EVEN_FRACTIONAL,
        INTEGER,
        POWER2,      //Max, Maya use this one
    };

	enum SubdivDisplaySmoothness
	{
		HULL,
		ROUGH,
		MEDIUM,
		FINE,
	};

    /** InitSubdivLevel Initialize the subdiv
      * \param pLevelCount  number of levels
      * \param pScheme      subdivision scheme
      * \param pPattern     Tessellation pattern
      */
    void InitSubdivLevel(int pLevelCount, 
        SubdivScheme pScheme = CATMULL_CLARK, 
        TessPattern pPattern = POWER2);

    FbxSubDiv(FbxManager& pManager, char const* pName);

    virtual void Destruct(bool pRecursive, bool pDependents);

    virtual FbxNodeAttribute::EAttributeType GetAttributeType() const;


    //max subdivision level number
    static const int MAX_SUBDIV_LEVEL = 16;

    //subdiv levels in subdivision, including the base mesh and each subdiv levels
    FbxArray<FbxMesh*> mSubDivLevel;

    //Get the base mesh
    FbxMesh* GetBaseMesh() const; 

    //Get the mesh from finest level
    FbxMesh* GetFinestMesh() const;

    //Set the finest mesh
    bool SetFinestMesh(FbxMesh* pMesh);

    //Set the finest mesh
    bool SetBaseMesh(FbxMesh* pMesh);

    //Get the mesh from specific level
    FbxMesh* GetMesh(int pLevel) const;

    /** SetSubdivLevelMesh Set certain subdivision mesh
      * \param pLevel   working level
      * \param pMesh    new level mesh. pLevel = 0 means base mesh, 
      pLevel = MaxLevel -1 means finest mesh
      */
    void SetSubdivLevelMesh(int pLevel, FbxMesh* pMesh);

    int GetLevelCount() const;
    void SetLevelCount(int pLevelCount);

    int GetCurrentLevel() const;
    void SetCurrentLevel(int pCurrentLevel);

	FbxMesh* GetCurrentMesh() const;

    FbxSubDiv::SubdivScheme GetSubdivScheme() const;

    FbxSubDiv::TessPattern GetTessPattern() const;

    void SetSubdivScheme(FbxSubDiv::SubdivScheme pScheme);

    void SetTessPattern(FbxSubDiv::TessPattern pPattern);

	FbxSubDiv::SubdivDisplaySmoothness GetDisplaySmoothness() const;

	void SetDisplaySmoothness(FbxSubDiv::SubdivDisplaySmoothness pSmoothness);

private:

    //base geometry mesh for subdivision
    FbxMesh* mBaseMesh;

    //finest geometry mesh for subdivision
    FbxMesh* mFinestMesh;

    //current operating subdivision level
    int mCurrLevel;

    //number of subdiv level
    int mLevelCount;

    //scheme of subdiv
    SubdivScheme mScheme;

    //pattern of subdiv
    TessPattern mPattern;

	//display smoothness of subdiv
	SubdivDisplaySmoothness mSmoothness;
};

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_GEOMETRY_SUB_DIV_H_ */
