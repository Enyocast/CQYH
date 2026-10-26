//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IOErrorEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_IOErrorEvent.h"
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
typedef ThunkFunc0<Instances::IOErrorEvent, Instances::IOErrorEvent::mid_textGet, ASString> TFunc_Instances_IOErrorEvent_textGet;
typedef ThunkFunc1<Instances::IOErrorEvent, Instances::IOErrorEvent::mid_textSet, Value, const ASString&> TFunc_Instances_IOErrorEvent_textSet;
typedef ThunkFunc0<Instances::IOErrorEvent, Instances::IOErrorEvent::mid_clone, Value> TFunc_Instances_IOErrorEvent_clone;
typedef ThunkFunc0<Instances::IOErrorEvent, Instances::IOErrorEvent::mid_toString, ASString> TFunc_Instances_IOErrorEvent_toString;

template <> const TFunc_Instances_IOErrorEvent_textGet::TMethod TFunc_Instances_IOErrorEvent_textGet::Method = &Instances::IOErrorEvent::textGet;
template <> const TFunc_Instances_IOErrorEvent_textSet::TMethod TFunc_Instances_IOErrorEvent_textSet::Method = &Instances::IOErrorEvent::textSet;
template <> const TFunc_Instances_IOErrorEvent_clone::TMethod TFunc_Instances_IOErrorEvent_clone::Method = &Instances::IOErrorEvent::clone;
template <> const TFunc_Instances_IOErrorEvent_toString::TMethod TFunc_Instances_IOErrorEvent_toString::Method = &Instances::IOErrorEvent::toString;

namespace Instances
{
    IOErrorEvent::IOErrorEvent(InstanceTraits::Traits& t)
    : Instances::ErrorEvent(t)
//##protect##"instance::IOErrorEvent::IOErrorEvent()$data"
    , Text(GetStringManager().GetBuiltin(AS3Builtin_empty_))
//##protect##"instance::IOErrorEvent::IOErrorEvent()$data"
    {
//##protect##"instance::IOErrorEvent::IOErrorEvent()$code"
//##protect##"instance::IOErrorEvent::IOErrorEvent()$code"
    }

    void IOErrorEvent::textGet(ASString& result)
    {
//##protect##"instance::IOErrorEvent::textGet()"
        SF_UNUSED1(result);
        result = Text;
//##protect##"instance::IOErrorEvent::textGet()"
    }
    void IOErrorEvent::textSet(Value& result, const ASString& value)
    {
//##protect##"instance::IOErrorEvent::textSet()"
        SF_UNUSED2(result, value);
        Text = value;
//##protect##"instance::IOErrorEvent::textSet()"
    }
    void IOErrorEvent::clone(Value& result)
    {
//##protect##"instance::IOErrorEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::IOErrorEvent::clone()"
    }
    void IOErrorEvent::toString(ASString& result)
    {
//##protect##"instance::IOErrorEvent::toString()"
        SF_UNUSED1(result);
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("IOErrorEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("text")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::IOErrorEvent::toString()"
    }

//##protect##"instance$methods"
    AS3::Object* IOErrorEvent::GetEventClass() const 
    { 
        Class* result = GetVM().GetClass("flash.events.IOErrorEvent");

        SF_ASSERT(result);
        return result;
    }

    SPtr<Instances::Event> IOErrorEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        IOErrorEvent* pe = static_cast<IOErrorEvent*>(p.GetPtr());
        pe->Text = Text;
        return p;
    }
    void IOErrorEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            argv[3].Convert2String(Text).DoNotCheck();
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo IOErrorEvent::ti[IOErrorEvent::ThunkInfoNum] = {
        {TFunc_Instances_IOErrorEvent_textGet::Func, &StringCI, "text", NULL, CT_Get, 0, 0},
        {TFunc_Instances_IOErrorEvent_textSet::Func, NULL, "text", NULL, CT_Set, 1, 1},
        {TFunc_Instances_IOErrorEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_IOErrorEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    IOErrorEvent::IOErrorEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::IOErrorEvent::IOErrorEvent()"
//##protect##"InstanceTraits::IOErrorEvent::IOErrorEvent()"
        SetMemSize(sizeof(Instances::IOErrorEvent));

    }

    Pickable<Instances::IOErrorEvent> IOErrorEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::IOErrorEvent>(new(t.Alloc()) Instances::IOErrorEvent(t));
    }

    void IOErrorEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    IOErrorEvent::IOErrorEvent(ClassTraits::Traits& t)
    : Class(t)
    , IO_ERROR("ioError")
    {
//##protect##"class_::IOErrorEvent::IOErrorEvent()"
//##protect##"class_::IOErrorEvent::IOErrorEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo IOErrorEvent::mi[IOErrorEvent::MemberInfoNum] = {
        {"IO_ERROR", OFFSETOF(Classes::IOErrorEvent, IO_ERROR), SlotInfo::BT_ConstChar, 1},
    };

    IOErrorEvent::IOErrorEvent(VM& vm)
    : Traits(vm, IOErrorEventCI)
    {
//##protect##"ClassTraits::IOErrorEvent::IOErrorEvent()"
//##protect##"ClassTraits::IOErrorEvent::IOErrorEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::IOErrorEvent(vm, IOErrorEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::IOErrorEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IOErrorEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IOErrorEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IOErrorEventCI = {
    ClassInfo::CompileTime,
    "IOErrorEvent", "flash.events", &ErrorEventCI,
    ClassTraits::IOErrorEvent::MakeClassTraits,
    0,
    ClassTraits::IOErrorEvent::MemberInfoNum,
    InstanceTraits::IOErrorEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::IOErrorEvent::mi,
    InstanceTraits::IOErrorEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

