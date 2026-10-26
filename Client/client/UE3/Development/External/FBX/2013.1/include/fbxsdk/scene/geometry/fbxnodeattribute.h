/****************************************************************************************
 
   Copyright (C) 2011 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxnodeattribute.h
#ifndef _FBXSDK_SCENE_GEOMETRY_NODE_ATTRIBUTE_H_
#define _FBXSDK_SCENE_GEOMETRY_NODE_ATTRIBUTE_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxarray.h>
#include <fbxsdk/core/base/fbxstringlist.h>
#include <fbxsdk/core/fbxobject.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxNode;
class FbxManager;

/** \brief This class is the base class to all types of node attributes.
  * \nosubgrouping
  *    A node attribute is the content of a node. A \c NULL node attribute is set 
  * by calling function FbxNode::SetNodeAttribute() with a \c NULL pointer.
  */
class FBXSDK_DLL FbxNodeAttribute : public FbxObject
{
    FBXSDK_OBJECT_DECLARE(FbxNodeAttribute, FbxObject);

public:
    //! Property Names
    static const char* sColor;

    //! Property Default Values
    static const FbxDouble3 sDefaultColor;

    /** This property handles the color.
      *
      * Default value is (0.8, 0.8, 0.8)
      */
    FbxPropertyT<FbxDouble3> Color;

    /** \enum EAttributeType Node attribute types.
      * - \e eUnknown
      * - \e eNULL
      * - \e eMARKER
      * - \e eSKELETON
      * - \e eMESH
      * - \e eNURB
      * - \e ePATCH
      * - \e eCAMERA
      * - \e eCAMERA_STEREO,
      * - \e eCAMERA_SWITCHER
      * - \e eLIGHT
      * - \e eOPTICAL_REFERENCE
      * - \e eOPTICAL_MARKER
      * - \e eNURBS_CURVE
      * - \e eTRIM_NURBS_SURFACE
      * - \e eBOUNDARY
      * - \e eNURBS_SURFACE
      * - \e eSHAPE
      * - \e eLODGROUP
      * - \e eSUBDIV
      * - \e eCACHED_EFFECT
      * - \e eLINE
      */
    typedef enum 
    {   
        eUnknown,
        eNULL,
        eMARKER,
        eSKELETON, 
        eMESH, 
        eNURB, 
        ePATCH,
        eCAMERA, 
        eCAMERA_STEREO,
        eCAMERA_SWITCHER,
        eLIGHT,
        eOPTICAL_REFERENCE,
        eOPTICAL_MARKER,
        eNURBS_CURVE,
        eTRIM_NURBS_SURFACE,
        eBOUNDARY,
        eNURBS_SURFACE,
        eSHAPE,
        eLODGROUP,
        eSUBDIV,
        eCACHED_EFFECT,
        eLINE
    } EAttributeType;

    /** Return the type of node attribute.
      * This class is pure virtual.
      */
    virtual EAttributeType GetAttributeType() const;

	/** Return the node count using this attribute.
	  * \return  The count of nodes with this attribute set.
	  */
	int GetNodeCount() const;

    /** Return the node this attribute is set to.
	  * \param pIndex	The index of the node to retrieve
      * \return			Pointer to the node, or \c NULL if the current attribute is not set to a node.
      */
    FbxNode* GetNode(int pIndex=0) const;

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//    Anything beyond these lines may not be documented accurately and is 
//     subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    FbxNodeAttribute(FbxManager& pManager, char const* pName);
    virtual bool ConstructProperties(bool pForceSet);

    friend class FbxNode;
    friend class FbxScene;
#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_GEOMETRY_NODE_ATTRIBUTE_H_ */
