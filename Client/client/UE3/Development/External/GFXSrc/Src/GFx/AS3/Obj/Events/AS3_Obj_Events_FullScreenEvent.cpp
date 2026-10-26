//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_FullScreenEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_FullScreenEvent.h"
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
    const ThunkInfo FullScreenEvent_ti[3] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "fullScreen", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    FullScreenEvent::FullScreenEvent(ClassTraits::Traits& t)
    : Class(t)
    , FULL_SCREEN("fullScreen")
    {
//##protect##"class_::FullScreenEvent::FullScreenEvent()"
//##protect##"class_::FullScreenEvent::FullScreenEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo FullScreenEvent::mi[FullScreenEvent::MemberInfoNum] = {
        {"FULL_SCREEN", OFFSETOF(Classes::FullScreenEvent, FULL_SCREEN), SlotInfo::BT_ConstChar, 1},
    };

    FullScreenEvent::FullScreenEvent(VM& vm)
    : Traits(vm, FullScreenEventCI)
    {
//##protect##"ClassTraits::FullScreenEvent::FullScreenEvent()"
//##protect##"ClassTraits::FullScreenEvent::FullScreenEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, FullScreenEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FullScreenEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FullScreenEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FullScreenEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FullScreenEventCI = {
    ClassInfo::CompileTime,
    "FullScreenEvent", "flash.events", &ActivityEventCI,
    ClassTraits::FullScreenEvent::MakeClassTraits,
    0,
    ClassTraits::FullScreenEvent::MemberInfoNum,
    3,
    0,
    NULL,
    ClassTraits::FullScreenEvent::mi,
    InstanceTraits::FullScreenEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

