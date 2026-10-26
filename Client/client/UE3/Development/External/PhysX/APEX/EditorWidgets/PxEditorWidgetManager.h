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

#ifndef PX_EDITOR_WIDGET_MANAGER_H
#define PX_EDITOR_WIDGET_MANAGER_H

#include "foundation/Px.h"
#include <NxParameterized.h>

PX_PUSH_PACK_DEFAULT

namespace physx
{

class PxEditorPanelDesc;
class PxGenericPropertiesEditorPanel;
class PxGenericPropertiesEditorPanelDesc;
class PxCurveEditorPanel;

class PxEditorWidgetManager
{
protected:
	virtual ~PxEditorWidgetManager(void) {}

public:
	//! release this object.
	virtual void release(void) = 0;

	//! call this somewhat frequently as its used for executing cleanup code.
	virtual void update(void) = 0;

	//! creates a widget inside a panel that is capable of editing any type of NxParameterized object.
	virtual PxGenericPropertiesEditorPanel* createGenericPropertiesEditor(const PxGenericPropertiesEditorPanelDesc& desc) = 0;

	//! creates a curve editor widget.
	virtual PxCurveEditorPanel*             createCurveEditor(const PxEditorPanelDesc& desc) = 0;

	virtual NxParameterized::Interface*	 createCustomInterface(const char* interfaceName, NxParameterized::Traits* traits) = 0;

	virtual void setSupportHidden(bool state) = 0;
	virtual void setSupportReadOnly(bool state) = 0;

	virtual const char * getChoice(const char *choiceTitle,physx::PxU32 choiceCount,const char **choiceNames,physx::PxU32 &choiceIndex) = 0;

};

} // namespace physx


#if defined(PX_VC)
#if defined(PX_EDITOR_EXPORT_DLL)
#define PX_EDITOR_DLL_API __declspec(dllexport)
#else
#define PX_EDITOR_DLL_API __declspec(dllimport)
#endif
#endif


typedef physx::PxEditorWidgetManager* (*PxCreateEditorWidgetManagerPROC)();
PX_C_EXPORT PX_EDITOR_DLL_API physx::PxEditorWidgetManager* PxCreateEditorWidgetManager();

PX_POP_PACK

#endif
