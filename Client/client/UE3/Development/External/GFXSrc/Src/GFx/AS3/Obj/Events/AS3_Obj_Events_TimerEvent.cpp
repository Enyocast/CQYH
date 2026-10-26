//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TimerEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_TimerEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::TimerEvent, Instances::TimerEvent::mid_clone, Value> TFunc_Instances_TimerEvent_clone;
typedef ThunkFunc0<Instances::TimerEvent, Instances::TimerEvent::mid_toString, ASString> TFunc_Instances_TimerEvent_toString;
typedef ThunkFunc0<Instances::TimerEvent, Instances::TimerEvent::mid_updateAfterEvent, Value> TFunc_Instances_TimerEvent_updateAfterEvent;

template <> const TFunc_Instances_TimerEvent_clone::TMethod TFunc_Instances_TimerEvent_clone::Method = &Instances::TimerEvent::clone;
template <> const TFunc_Instances_TimerEvent_toString::TMethod TFunc_Instances_TimerEvent_toString::Method = &Instances::TimerEvent::toString;
template <> const TFunc_Instances_TimerEvent_updateAfterEvent::TMethod TFunc_Instances_TimerEvent_updateAfterEvent::Method = &Instances::TimerEvent::updateAfterEvent;

namespace Instances
{
    TimerEvent::TimerEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::TimerEvent::TimerEvent()$data"
//##protect##"instance::TimerEvent::TimerEvent()$data"
    {
//##protect##"instance::TimerEvent::TimerEvent()$code"
//##protect##"instance::TimerEvent::TimerEvent()$code"
    }

    void TimerEvent::clone(Value& result)
    {
//##protect##"instance::TimerEvent::clone()"
        SF_UNUSED1(result);
        // GetEventClass returns a correct event class for the clone
        Event::clone(result);
//##protect##"instance::TimerEvent::clone()"
    }
    void TimerEvent::toString(ASString& result)
    {
//##protect##"instance::TimerEvent::toString()"
        SF_UNUSED1(result);
        // GetEventName will return a correct name for the event
        Event::toString(result);
//##protect##"instance::TimerEvent::toString()"
    }
    void TimerEvent::updateAfterEvent(Value& result)
    {
//##protect##"instance::TimerEvent::updateAfterEvent()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("TimerEvent::updateAfterEvent()");
//##protect##"instance::TimerEvent::updateAfterEvent()"
    }

//##protect##"instance$methods"
    AS3::Object*     TimerEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).TimerEventClass.GetPtr(); 
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo TimerEvent::ti[TimerEvent::ThunkInfoNum] = {
        {TFunc_Instances_TimerEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_TimerEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_TimerEvent_updateAfterEvent::Func, NULL, "updateAfterEvent", NULL, CT_Method, 0, 0},
    };

    TimerEvent::TimerEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TimerEvent::TimerEvent()"
//##protect##"InstanceTraits::TimerEvent::TimerEvent()"
        SetMemSize(sizeof(Instances::TimerEvent));

    }

    Pickable<Instances::TimerEvent> TimerEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TimerEvent>(new(t.Alloc()) Instances::TimerEvent(t));
    }

    void TimerEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    TimerEvent::TimerEvent(ClassTraits::Traits& t)
    : Class(t)
    , TIMER("timer")
    , TIMER_COMPLETE("timerComplete")
    {
//##protect##"class_::TimerEvent::TimerEvent()"
//##protect##"class_::TimerEvent::TimerEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TimerEvent::mi[TimerEvent::MemberInfoNum] = {
        {"TIMER", OFFSETOF(Classes::TimerEvent, TIMER), SlotInfo::BT_ConstChar, 1},
        {"TIMER_COMPLETE", OFFSETOF(Classes::TimerEvent, TIMER_COMPLETE), SlotInfo::BT_ConstChar, 1},
    };

    TimerEvent::TimerEvent(VM& vm)
    : Traits(vm, TimerEventCI)
    {
//##protect##"ClassTraits::TimerEvent::TimerEvent()"
//##protect##"ClassTraits::TimerEvent::TimerEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TimerEvent(vm, TimerEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TimerEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TimerEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TimerEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TimerEventCI = {
    ClassInfo::CompileTime,
    "TimerEvent", "flash.events", &EventCI,
    ClassTraits::TimerEvent::MakeClassTraits,
    0,
    ClassTraits::TimerEvent::MemberInfoNum,
    InstanceTraits::TimerEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::TimerEvent::mi,
    InstanceTraits::TimerEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

