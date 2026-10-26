// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2012 NVIDIA Corporation. All rights reserved.

#ifndef PX_GENERIC_PROPERTIES_EDITOR_PANEL_H
#define PX_GENERIC_PROPERTIES_EDITOR_PANEL_H

#include <PxEditorPanel.h>
#include "foundation/PxSimpleTypes.h"

using namespace physx;

namespace NxParameterized
{
class Interface;
}

PX_PUSH_PACK_DEFAULT

namespace physx
{

class PxCurveEditorPanel;

class PxGenericPanel
{
public:
	virtual void * getHWND(void) = 0;
	virtual void addButton(PxU32 buttonId,const char *text,PxU32 xloc,PxU32 yloc) = 0;
};

class PxGenericPropertiesEditorPanel : public PxEditorPanel
{
protected:
	virtual ~PxGenericPropertiesEditorPanel(void) {}

public:

	virtual void beginProgressListener(void) = 0;
	virtual void endProgressListener(void) = 0;
	virtual void updateProgressListener(const char *msg,PxU32 percent) = 0;

	// api methods to create the menu bar.
	virtual bool beginMenu(const char *name) = 0;
	virtual bool addMenuItem(PxU32 id,const char *menuItem,const char *help,bool isCheckable) = 0;
	virtual bool addMenuSeperator(void) = 0;
	virtual bool endMenu(void) = 0;
	virtual void finalizeMenuBar(void) = 0;

	virtual PxGenericPanel * addGenericPanel(const char *tabName) = 0;
	virtual void resetRememberStates(void) = 0;
	virtual void rememberStates(void) = 0;
	virtual void refreshWindow(void) = 0;
	virtual void refreshReferences(NxParameterized::Interface& object) = 0; // indicates that the application has made internal modifications to the NxParameterized data that the properties panel doesn't know about.  Therefore, the properties panel needs to be refreshed.
	virtual void refreshParams(NxParameterized::Interface& object) = 0; // indicates that the application has made internal modifications to the NxParameterized data that the properties panel doesn't know about.  Therefore, the properties panel needs to be refreshed.
	virtual void refreshArrays(const char *refreshArrayName) = 0; // indicates that the application has made internal modifications to the NxParameterized data that the properties panel doesn't know about.  Therefore, the properties panel needs to be refreshed.
	//! appends an object to the property editor.
	virtual size_t addObject(const char *tabName,NxParameterized::Interface& object, const char* customParamsDisplayString = NULL,size_t propGridIndex=0xFFFFFFFF) = 0;

	virtual const char* SaveExpandedState(void) = 0;
	virtual void RestoreExpandedState(const char* label) = 0;

	//! removes an object from the property editor.
	virtual void removeObject(NxParameterized::Interface& object) = 0;

	//! clears all properties from the editor.
	virtual void clearObjects(void) = 0;

	virtual void clearObject(size_t index) = 0;

	//! sets of clears the curve editor to use when selecting curve properties.
	virtual void setCurveEditor(PxCurveEditorPanel* curveEditorPanel) = 0;


	//! sets a custom hint within an NxParameterized class
	virtual void addCustomHint(const char* paramClassName,
	                           const char* fullParamName,
	                           const char* hintName,
	                           const char* hintValue) = 0;

	//! gets a custom hint value within an NxParameterized class
	virtual const char* getCustomHint(const char* paramClassName,
	                                  const char* fullParamName,
	                                  const char* hintName) = 0;

	virtual void setObjectReadOnly(bool isReadOnly) = 0;
};

} // namespace physx

PX_POP_PACK

#endif
