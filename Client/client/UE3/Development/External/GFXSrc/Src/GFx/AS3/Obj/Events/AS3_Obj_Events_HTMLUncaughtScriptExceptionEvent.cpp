//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_HTMLUncaughtScriptExceptionEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_HTMLUncaughtScriptExceptionEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace Instances
{
    HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
    , exceptionValue()
    , stackTrace()
//##protect##"instance::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()$data"
//##protect##"instance::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()$data"
    {
//##protect##"instance::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()$code"
//##protect##"instance::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo HTMLUncaughtScriptExceptionEvent::ti[HTMLUncaughtScriptExceptionEvent::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
    };
    const MemberInfo HTMLUncaughtScriptExceptionEvent::mi[HTMLUncaughtScriptExceptionEvent::MemberInfoNum] = {
        {"exceptionValue", OFFSETOF(Instances::HTMLUncaughtScriptExceptionEvent, exceptionValue), SlotInfo::BT_Value, 0},
        {"stackTrace", OFFSETOF(Instances::HTMLUncaughtScriptExceptionEvent, stackTrace), SlotInfo::BT_ObjectCpp, 0},
    };


    HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()"
//##protect##"InstanceTraits::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()"
        SetMemSize(sizeof(Instances::HTMLUncaughtScriptExceptionEvent));

    }

    Pickable<Instances::HTMLUncaughtScriptExceptionEvent> HTMLUncaughtScriptExceptionEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::HTMLUncaughtScriptExceptionEvent>(new(t.Alloc()) Instances::HTMLUncaughtScriptExceptionEvent(t));
    }

    void HTMLUncaughtScriptExceptionEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()"
//##protect##"class_::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo HTMLUncaughtScriptExceptionEvent::mi[HTMLUncaughtScriptExceptionEvent::MemberInfoNum] = {
        {"UNCAUGHT_SCRIPT_EXCEPTION", OFFSETOF(Classes::HTMLUncaughtScriptExceptionEvent, UNCAUGHT_SCRIPT_EXCEPTION), SlotInfo::BT_Value, 1},
    };

    HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent(VM& vm)
    : Traits(vm, HTMLUncaughtScriptExceptionEventCI)
    {
//##protect##"ClassTraits::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()"
//##protect##"ClassTraits::HTMLUncaughtScriptExceptionEvent::HTMLUncaughtScriptExceptionEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::HTMLUncaughtScriptExceptionEvent(vm, HTMLUncaughtScriptExceptionEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::HTMLUncaughtScriptExceptionEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> HTMLUncaughtScriptExceptionEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTMLUncaughtScriptExceptionEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo HTMLUncaughtScriptExceptionEventCI = {
    ClassInfo::CompileTime,
    "HTMLUncaughtScriptExceptionEvent", "flash.events", &EventCI,
    ClassTraits::HTMLUncaughtScriptExceptionEvent::MakeClassTraits,
    0,
    ClassTraits::HTMLUncaughtScriptExceptionEvent::MemberInfoNum,
    InstanceTraits::HTMLUncaughtScriptExceptionEvent::ThunkInfoNum,
    InstanceTraits::HTMLUncaughtScriptExceptionEvent::MemberInfoNum,
    NULL,
    ClassTraits::HTMLUncaughtScriptExceptionEvent::mi,
    InstanceTraits::HTMLUncaughtScriptExceptionEvent::ti,
    InstanceTraits::HTMLUncaughtScriptExceptionEvent::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

