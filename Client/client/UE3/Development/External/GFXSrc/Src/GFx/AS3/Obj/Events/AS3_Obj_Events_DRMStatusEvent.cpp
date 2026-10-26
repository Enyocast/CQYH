//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMStatusEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_DRMStatusEvent.h"
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
    const ThunkInfo DRMStatusEvent_ti[8] = {
        {ThunkInfo::EmptyFunc, &StringCI, "detail", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isAnonymous", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isAvailableOffline", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "offlineLeasePeriod", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &ObjectCI, "policies", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &DateCI, "voucherEndDate", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    DRMStatusEvent::DRMStatusEvent(ClassTraits::Traits& t)
    : Class(t)
    , DRM_STATUS("drmStatus")
    {
//##protect##"class_::DRMStatusEvent::DRMStatusEvent()"
//##protect##"class_::DRMStatusEvent::DRMStatusEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo DRMStatusEvent::mi[DRMStatusEvent::MemberInfoNum] = {
        {"DRM_STATUS", OFFSETOF(Classes::DRMStatusEvent, DRM_STATUS), SlotInfo::BT_ConstChar, 1},
    };

    DRMStatusEvent::DRMStatusEvent(VM& vm)
    : Traits(vm, DRMStatusEventCI)
    {
//##protect##"ClassTraits::DRMStatusEvent::DRMStatusEvent()"
//##protect##"ClassTraits::DRMStatusEvent::DRMStatusEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, DRMStatusEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::DRMStatusEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DRMStatusEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DRMStatusEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DRMStatusEventCI = {
    ClassInfo::CompileTime,
    "DRMStatusEvent", "flash.events", &EventCI,
    ClassTraits::DRMStatusEvent::MakeClassTraits,
    0,
    ClassTraits::DRMStatusEvent::MemberInfoNum,
    8,
    0,
    NULL,
    ClassTraits::DRMStatusEvent::mi,
    InstanceTraits::DRMStatusEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

