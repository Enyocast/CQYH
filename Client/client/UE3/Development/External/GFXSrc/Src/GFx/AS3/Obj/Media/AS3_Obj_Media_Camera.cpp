//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Camera.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_Camera.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo Camera_ti[19] = {
        {ThunkInfo::EmptyFunc, &NumberCI, "activityLevel", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "bandwidth", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "currentFPS", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "fps", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "height", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "index", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "keyFrameInterval", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "loopback", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "motionLevel", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "motionTimeout", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "muted", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "name", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "quality", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "width", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "setKeyFrameInterval", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "setLoopback", NULL, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "setMode", NULL, CT_Method, 3, 4},
        {ThunkInfo::EmptyFunc, NULL, "setMotionLevel", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "setQuality", NULL, CT_Method, 2, 2},
    };

} // namespace InstanceTraits

namespace Classes
{
    Camera::Camera(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Camera::Camera()"
//##protect##"class_::Camera::Camera()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo Camera_ti[1] = {
        {ThunkInfo::EmptyFunc, &CameraCI, "getCamera", NULL, CT_Method, 0, 1},
    };
    Camera::Camera(VM& vm)
    : Traits(vm, CameraCI)
    {
//##protect##"ClassTraits::Camera::Camera()"
//##protect##"ClassTraits::Camera::Camera()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, CameraCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Camera(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Camera::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Camera(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo CameraCI = {
    ClassInfo::CompileTime,
    "Camera", "flash.media", &EventDispatcherCI,
    ClassTraits::Camera::MakeClassTraits,
    1,
    0,
    19,
    0,
    ClassTraits::Camera_ti,
    NULL,
    InstanceTraits::Camera_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

