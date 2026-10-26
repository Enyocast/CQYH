//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_AsyncErrorEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_AsyncErrorEvent.h"
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

namespace Instances
{
    AsyncErrorEvent::AsyncErrorEvent(InstanceTraits::Traits& t)
    : Instances::ErrorEvent(t)
    , error()
//##protect##"instance::AsyncErrorEvent::AsyncErrorEvent()$data"
//##protect##"instance::AsyncErrorEvent::AsyncErrorEvent()$data"
    {
//##protect##"instance::AsyncErrorEvent::AsyncErrorEvent()$code"
//##protect##"instance::AsyncErrorEvent::AsyncErrorEvent()$code"
    }


//##protect##"instance$methods"
    AsyncErrorEvent::~AsyncErrorEvent()
    {
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo AsyncErrorEvent::ti[AsyncErrorEvent::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo AsyncErrorEvent::mi[AsyncErrorEvent::MemberInfoNum] = {
        {"error", OFFSETOF(Instances::AsyncErrorEvent, error), SlotInfo::BT_ObjectCpp, 0},
    };


    AsyncErrorEvent::AsyncErrorEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::AsyncErrorEvent::AsyncErrorEvent()"
//##protect##"InstanceTraits::AsyncErrorEvent::AsyncErrorEvent()"
        SetMemSize(sizeof(Instances::AsyncErrorEvent));

    }

    Pickable<Instances::AsyncErrorEvent> AsyncErrorEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::AsyncErrorEvent>(new(t.Alloc()) Instances::AsyncErrorEvent(t));
    }

    void AsyncErrorEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    AsyncErrorEvent::AsyncErrorEvent(ClassTraits::Traits& t)
    : Class(t)
    , ASYNC_ERROR("asyncError")
    {
//##protect##"class_::AsyncErrorEvent::AsyncErrorEvent()"
//##protect##"class_::AsyncErrorEvent::AsyncErrorEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo AsyncErrorEvent::mi[AsyncErrorEvent::MemberInfoNum] = {
        {"ASYNC_ERROR", OFFSETOF(Classes::AsyncErrorEvent, ASYNC_ERROR), SlotInfo::BT_ConstChar, 1},
    };

    AsyncErrorEvent::AsyncErrorEvent(VM& vm)
    : Traits(vm, AsyncErrorEventCI)
    {
//##protect##"ClassTraits::AsyncErrorEvent::AsyncErrorEvent()"
//##protect##"ClassTraits::AsyncErrorEvent::AsyncErrorEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::AsyncErrorEvent(vm, AsyncErrorEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::AsyncErrorEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> AsyncErrorEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AsyncErrorEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo AsyncErrorEventCI = {
    ClassInfo::CompileTime,
    "AsyncErrorEvent", "flash.events", &ErrorEventCI,
    ClassTraits::AsyncErrorEvent::MakeClassTraits,
    0,
    ClassTraits::AsyncErrorEvent::MemberInfoNum,
    InstanceTraits::AsyncErrorEvent::ThunkInfoNum,
    InstanceTraits::AsyncErrorEvent::MemberInfoNum,
    NULL,
    ClassTraits::AsyncErrorEvent::mi,
    InstanceTraits::AsyncErrorEvent::ti,
    InstanceTraits::AsyncErrorEvent::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

