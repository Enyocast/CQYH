//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_SecurityErrorEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_SecurityErrorEvent.h"
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
    const ThunkInfo SecurityErrorEvent_ti[2] = {
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    SecurityErrorEvent::SecurityErrorEvent(ClassTraits::Traits& t)
    : Class(t)
    , SECURITY_ERROR("securityError")
    {
//##protect##"class_::SecurityErrorEvent::SecurityErrorEvent()"
//##protect##"class_::SecurityErrorEvent::SecurityErrorEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SecurityErrorEvent::mi[SecurityErrorEvent::MemberInfoNum] = {
        {"SECURITY_ERROR", OFFSETOF(Classes::SecurityErrorEvent, SECURITY_ERROR), SlotInfo::BT_ConstChar, 1},
    };

    SecurityErrorEvent::SecurityErrorEvent(VM& vm)
    : Traits(vm, SecurityErrorEventCI)
    {
//##protect##"ClassTraits::SecurityErrorEvent::SecurityErrorEvent()"
//##protect##"ClassTraits::SecurityErrorEvent::SecurityErrorEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ErrorEvent(vm, SecurityErrorEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SecurityErrorEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SecurityErrorEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SecurityErrorEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SecurityErrorEventCI = {
    ClassInfo::CompileTime,
    "SecurityErrorEvent", "flash.events", &ErrorEventCI,
    ClassTraits::SecurityErrorEvent::MakeClassTraits,
    0,
    ClassTraits::SecurityErrorEvent::MemberInfoNum,
    2,
    0,
    NULL,
    ClassTraits::SecurityErrorEvent::mi,
    InstanceTraits::SecurityErrorEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

