//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ErrorEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_ErrorEvent.h"
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
typedef ThunkFunc0<Instances::ErrorEvent, Instances::ErrorEvent::mid_errorIDGet, SInt32> TFunc_Instances_ErrorEvent_errorIDGet;
typedef ThunkFunc0<Instances::ErrorEvent, Instances::ErrorEvent::mid_clone, Value> TFunc_Instances_ErrorEvent_clone;
typedef ThunkFunc0<Instances::ErrorEvent, Instances::ErrorEvent::mid_toString, ASString> TFunc_Instances_ErrorEvent_toString;

template <> const TFunc_Instances_ErrorEvent_errorIDGet::TMethod TFunc_Instances_ErrorEvent_errorIDGet::Method = &Instances::ErrorEvent::errorIDGet;
template <> const TFunc_Instances_ErrorEvent_clone::TMethod TFunc_Instances_ErrorEvent_clone::Method = &Instances::ErrorEvent::clone;
template <> const TFunc_Instances_ErrorEvent_toString::TMethod TFunc_Instances_ErrorEvent_toString::Method = &Instances::ErrorEvent::toString;

namespace Instances
{
    ErrorEvent::ErrorEvent(InstanceTraits::Traits& t)
    : Instances::TextEvent(t)
//##protect##"instance::ErrorEvent::ErrorEvent()$data"
//##protect##"instance::ErrorEvent::ErrorEvent()$data"
    {
//##protect##"instance::ErrorEvent::ErrorEvent()$code"
//##protect##"instance::ErrorEvent::ErrorEvent()$code"
    }

    void ErrorEvent::errorIDGet(SInt32& result)
    {
//##protect##"instance::ErrorEvent::errorIDGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("ErrorEvent::errorIDGet()");
//##protect##"instance::ErrorEvent::errorIDGet()"
    }
    void ErrorEvent::clone(Value& result)
    {
//##protect##"instance::ErrorEvent::clone()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("ErrorEvent::clone()");
//##protect##"instance::ErrorEvent::clone()"
    }
    void ErrorEvent::toString(ASString& result)
    {
//##protect##"instance::ErrorEvent::toString()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("ErrorEvent::toString()");
//##protect##"instance::ErrorEvent::toString()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo ErrorEvent::ti[ErrorEvent::ThunkInfoNum] = {
        {TFunc_Instances_ErrorEvent_errorIDGet::Func, &int_CI, "errorID", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ErrorEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ErrorEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    ErrorEvent::ErrorEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ErrorEvent::ErrorEvent()"
//##protect##"InstanceTraits::ErrorEvent::ErrorEvent()"
        SetMemSize(sizeof(Instances::ErrorEvent));

    }

    Pickable<Instances::ErrorEvent> ErrorEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ErrorEvent>(new(t.Alloc()) Instances::ErrorEvent(t));
    }

    void ErrorEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    ErrorEvent::ErrorEvent(ClassTraits::Traits& t)
    : Class(t)
    , ERROR("error")
    {
//##protect##"class_::ErrorEvent::ErrorEvent()"
//##protect##"class_::ErrorEvent::ErrorEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo ErrorEvent::mi[ErrorEvent::MemberInfoNum] = {
        {"ERROR", OFFSETOF(Classes::ErrorEvent, ERROR), SlotInfo::BT_ConstChar, 1},
    };

    ErrorEvent::ErrorEvent(VM& vm)
    : Traits(vm, ErrorEventCI)
    {
//##protect##"ClassTraits::ErrorEvent::ErrorEvent()"
//##protect##"ClassTraits::ErrorEvent::ErrorEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ErrorEvent(vm, ErrorEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ErrorEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ErrorEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ErrorEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ErrorEventCI = {
    ClassInfo::CompileTime,
    "ErrorEvent", "flash.events", &TextEventCI,
    ClassTraits::ErrorEvent::MakeClassTraits,
    0,
    ClassTraits::ErrorEvent::MemberInfoNum,
    InstanceTraits::ErrorEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::ErrorEvent::mi,
    InstanceTraits::ErrorEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

