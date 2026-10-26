//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_StatusEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_StatusEvent.h"
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
    const ThunkInfo StatusEvent_ti[6] = {
        {ThunkInfo::EmptyFunc, &StringCI, "code", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "code", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "level", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "level", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    StatusEvent::StatusEvent(ClassTraits::Traits& t)
    : Class(t)
    , STATUS("status")
    {
//##protect##"class_::StatusEvent::StatusEvent()"
//##protect##"class_::StatusEvent::StatusEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo StatusEvent::mi[StatusEvent::MemberInfoNum] = {
        {"STATUS", OFFSETOF(Classes::StatusEvent, STATUS), SlotInfo::BT_ConstChar, 1},
    };

    StatusEvent::StatusEvent(VM& vm)
    : Traits(vm, StatusEventCI)
    {
//##protect##"ClassTraits::StatusEvent::StatusEvent()"
//##protect##"ClassTraits::StatusEvent::StatusEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, StatusEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::StatusEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StatusEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StatusEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StatusEventCI = {
    ClassInfo::CompileTime,
    "StatusEvent", "flash.events", &EventCI,
    ClassTraits::StatusEvent::MakeClassTraits,
    0,
    ClassTraits::StatusEvent::MemberInfoNum,
    6,
    0,
    NULL,
    ClassTraits::StatusEvent::mi,
    InstanceTraits::StatusEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

