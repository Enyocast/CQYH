//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_InvokeEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_InvokeEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class File;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo InvokeEvent_ti[3] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "arguments", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "currentDirectory", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    InvokeEvent::InvokeEvent(ClassTraits::Traits& t)
    : Class(t)
    , INVOKE("invoke")
    {
//##protect##"class_::InvokeEvent::InvokeEvent()"
//##protect##"class_::InvokeEvent::InvokeEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo InvokeEvent::mi[InvokeEvent::MemberInfoNum] = {
        {"INVOKE", OFFSETOF(Classes::InvokeEvent, INVOKE), SlotInfo::BT_ConstChar, 1},
    };

    InvokeEvent::InvokeEvent(VM& vm)
    : Traits(vm, InvokeEventCI)
    {
//##protect##"ClassTraits::InvokeEvent::InvokeEvent()"
//##protect##"ClassTraits::InvokeEvent::InvokeEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, InvokeEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::InvokeEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> InvokeEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) InvokeEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo InvokeEventCI = {
    ClassInfo::CompileTime,
    "InvokeEvent", "flash.events", &EventCI,
    ClassTraits::InvokeEvent::MakeClassTraits,
    0,
    ClassTraits::InvokeEvent::MemberInfoNum,
    3,
    0,
    NULL,
    ClassTraits::InvokeEvent::mi,
    InstanceTraits::InvokeEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

