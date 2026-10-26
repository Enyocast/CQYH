//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NativeWindowDisplayStateEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_NativeWindowDisplayStateEvent.h"
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
    const ThunkInfo NativeWindowDisplayStateEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &StringCI, "afterDisplayState", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "beforeDisplayState", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    NativeWindowDisplayStateEvent::NativeWindowDisplayStateEvent(ClassTraits::Traits& t)
    : Class(t)
    , DISPLAY_STATE_CHANGE("displayStateChange")
    , DISPLAY_STATE_CHANGING("displayStateChanging")
    {
//##protect##"class_::NativeWindowDisplayStateEvent::NativeWindowDisplayStateEvent()"
//##protect##"class_::NativeWindowDisplayStateEvent::NativeWindowDisplayStateEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeWindowDisplayStateEvent::mi[NativeWindowDisplayStateEvent::MemberInfoNum] = {
        {"DISPLAY_STATE_CHANGE", OFFSETOF(Classes::NativeWindowDisplayStateEvent, DISPLAY_STATE_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"DISPLAY_STATE_CHANGING", OFFSETOF(Classes::NativeWindowDisplayStateEvent, DISPLAY_STATE_CHANGING), SlotInfo::BT_ConstChar, 1},
    };

    NativeWindowDisplayStateEvent::NativeWindowDisplayStateEvent(VM& vm)
    : Traits(vm, NativeWindowDisplayStateEventCI)
    {
//##protect##"ClassTraits::NativeWindowDisplayStateEvent::NativeWindowDisplayStateEvent()"
//##protect##"ClassTraits::NativeWindowDisplayStateEvent::NativeWindowDisplayStateEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, NativeWindowDisplayStateEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeWindowDisplayStateEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindowDisplayStateEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowDisplayStateEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowDisplayStateEventCI = {
    ClassInfo::CompileTime,
    "NativeWindowDisplayStateEvent", "flash.events", &EventCI,
    ClassTraits::NativeWindowDisplayStateEvent::MakeClassTraits,
    0,
    ClassTraits::NativeWindowDisplayStateEvent::MemberInfoNum,
    4,
    0,
    NULL,
    ClassTraits::NativeWindowDisplayStateEvent::mi,
    InstanceTraits::NativeWindowDisplayStateEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

