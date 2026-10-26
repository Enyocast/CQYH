//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ActivityEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_ActivityEvent.h"
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
    const ThunkInfo ActivityEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "activating", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "activating", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    ActivityEvent::ActivityEvent(ClassTraits::Traits& t)
    : Class(t)
    , ACTIVITY("activity")
    {
//##protect##"class_::ActivityEvent::ActivityEvent()"
//##protect##"class_::ActivityEvent::ActivityEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo ActivityEvent::mi[ActivityEvent::MemberInfoNum] = {
        {"ACTIVITY", OFFSETOF(Classes::ActivityEvent, ACTIVITY), SlotInfo::BT_ConstChar, 1},
    };

    ActivityEvent::ActivityEvent(VM& vm)
    : Traits(vm, ActivityEventCI)
    {
//##protect##"ClassTraits::ActivityEvent::ActivityEvent()"
//##protect##"ClassTraits::ActivityEvent::ActivityEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, ActivityEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ActivityEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ActivityEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ActivityEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ActivityEventCI = {
    ClassInfo::CompileTime,
    "ActivityEvent", "flash.events", &EventCI,
    ClassTraits::ActivityEvent::MakeClassTraits,
    0,
    ClassTraits::ActivityEvent::MemberInfoNum,
    4,
    0,
    NULL,
    ClassTraits::ActivityEvent::mi,
    InstanceTraits::ActivityEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

