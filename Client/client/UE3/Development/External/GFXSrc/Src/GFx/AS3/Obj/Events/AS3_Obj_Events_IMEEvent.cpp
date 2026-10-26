//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IMEEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_IMEEvent.h"
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
typedef ThunkFunc0<Instances::IMEEvent, Instances::IMEEvent::mid_clone, Value> TFunc_Instances_IMEEvent_clone;
typedef ThunkFunc0<Instances::IMEEvent, Instances::IMEEvent::mid_toString, ASString> TFunc_Instances_IMEEvent_toString;

template <> const TFunc_Instances_IMEEvent_clone::TMethod TFunc_Instances_IMEEvent_clone::Method = &Instances::IMEEvent::clone;
template <> const TFunc_Instances_IMEEvent_toString::TMethod TFunc_Instances_IMEEvent_toString::Method = &Instances::IMEEvent::toString;

namespace Instances
{
    IMEEvent::IMEEvent(InstanceTraits::Traits& t)
    : Instances::TextEvent(t)
//##protect##"instance::IMEEvent::IMEEvent()$data"
//##protect##"instance::IMEEvent::IMEEvent()$data"
    {
//##protect##"instance::IMEEvent::IMEEvent()$code"
//##protect##"instance::IMEEvent::IMEEvent()$code"
    }

    void IMEEvent::clone(Value& result)
    {
//##protect##"instance::IMEEvent::clone()"
        SF_UNUSED1(result);
        // Interface methods have empty implementations.
//##protect##"instance::IMEEvent::clone()"
    }
    void IMEEvent::toString(ASString& result)
    {
//##protect##"instance::IMEEvent::toString()"
        SF_UNUSED1(result);
        // Interface methods have empty implementations.
//##protect##"instance::IMEEvent::toString()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo IMEEvent::ti[IMEEvent::ThunkInfoNum] = {
        {TFunc_Instances_IMEEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_IMEEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    IMEEvent::IMEEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::IMEEvent::IMEEvent()"
//##protect##"InstanceTraits::IMEEvent::IMEEvent()"
        SetMemSize(sizeof(Instances::IMEEvent));

    }

    Pickable<Instances::IMEEvent> IMEEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::IMEEvent>(new(t.Alloc()) Instances::IMEEvent(t));
    }

    void IMEEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    IMEEvent::IMEEvent(ClassTraits::Traits& t)
    : Class(t)
    , IME_COMPOSITION("imeComposition")
    {
//##protect##"class_::IMEEvent::IMEEvent()"
//##protect##"class_::IMEEvent::IMEEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo IMEEvent::mi[IMEEvent::MemberInfoNum] = {
        {"IME_COMPOSITION", OFFSETOF(Classes::IMEEvent, IME_COMPOSITION), SlotInfo::BT_ConstChar, 1},
    };

    IMEEvent::IMEEvent(VM& vm)
    : Traits(vm, IMEEventCI)
    {
//##protect##"ClassTraits::IMEEvent::IMEEvent()"
//##protect##"ClassTraits::IMEEvent::IMEEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::IMEEvent(vm, IMEEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::IMEEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IMEEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IMEEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IMEEventCI = {
    ClassInfo::CompileTime,
    "IMEEvent", "flash.events", &TextEventCI,
    ClassTraits::IMEEvent::MakeClassTraits,
    0,
    ClassTraits::IMEEvent::MemberInfoNum,
    InstanceTraits::IMEEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::IMEEvent::mi,
    InstanceTraits::IMEEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

