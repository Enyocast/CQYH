//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMErrorEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_DRMErrorEvent.h"
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
    const ThunkInfo DRMErrorEvent_ti[3] = {
        {ThunkInfo::EmptyFunc, &int_CI, "subErrorID", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    DRMErrorEvent::DRMErrorEvent(ClassTraits::Traits& t)
    : Class(t)
    , DRM_ERROR("drmError")
    {
//##protect##"class_::DRMErrorEvent::DRMErrorEvent()"
//##protect##"class_::DRMErrorEvent::DRMErrorEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo DRMErrorEvent::mi[DRMErrorEvent::MemberInfoNum] = {
        {"DRM_ERROR", OFFSETOF(Classes::DRMErrorEvent, DRM_ERROR), SlotInfo::BT_ConstChar, 1},
    };

    DRMErrorEvent::DRMErrorEvent(VM& vm)
    : Traits(vm, DRMErrorEventCI)
    {
//##protect##"ClassTraits::DRMErrorEvent::DRMErrorEvent()"
//##protect##"ClassTraits::DRMErrorEvent::DRMErrorEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ErrorEvent(vm, DRMErrorEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::DRMErrorEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DRMErrorEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DRMErrorEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DRMErrorEventCI = {
    ClassInfo::CompileTime,
    "DRMErrorEvent", "flash.events", &ErrorEventCI,
    ClassTraits::DRMErrorEvent::MakeClassTraits,
    0,
    ClassTraits::DRMErrorEvent::MemberInfoNum,
    3,
    0,
    NULL,
    ClassTraits::DRMErrorEvent::mi,
    InstanceTraits::DRMErrorEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

