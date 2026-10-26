//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NativeWindowBoundsEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_NativeWindowBoundsEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Rectangle;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo NativeWindowBoundsEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &RectangleCI, "afterBounds", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &RectangleCI, "beforeBounds", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    NativeWindowBoundsEvent::NativeWindowBoundsEvent(ClassTraits::Traits& t)
    : Class(t)
    , MOVE("move")
    , MOVING("moving")
    , RESIZE("resize")
    , RESIZING("resizing")
    {
//##protect##"class_::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
//##protect##"class_::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeWindowBoundsEvent::mi[NativeWindowBoundsEvent::MemberInfoNum] = {
        {"MOVE", OFFSETOF(Classes::NativeWindowBoundsEvent, MOVE), SlotInfo::BT_ConstChar, 1},
        {"MOVING", OFFSETOF(Classes::NativeWindowBoundsEvent, MOVING), SlotInfo::BT_ConstChar, 1},
        {"RESIZE", OFFSETOF(Classes::NativeWindowBoundsEvent, RESIZE), SlotInfo::BT_ConstChar, 1},
        {"RESIZING", OFFSETOF(Classes::NativeWindowBoundsEvent, RESIZING), SlotInfo::BT_ConstChar, 1},
    };

    NativeWindowBoundsEvent::NativeWindowBoundsEvent(VM& vm)
    : Traits(vm, NativeWindowBoundsEventCI)
    {
//##protect##"ClassTraits::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
//##protect##"ClassTraits::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, NativeWindowBoundsEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeWindowBoundsEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindowBoundsEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowBoundsEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowBoundsEventCI = {
    ClassInfo::CompileTime,
    "NativeWindowBoundsEvent", "flash.events", &EventCI,
    ClassTraits::NativeWindowBoundsEvent::MakeClassTraits,
    0,
    ClassTraits::NativeWindowBoundsEvent::MemberInfoNum,
    4,
    0,
    NULL,
    ClassTraits::NativeWindowBoundsEvent::mi,
    InstanceTraits::NativeWindowBoundsEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

