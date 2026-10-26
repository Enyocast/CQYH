//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_AppLifecycleEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_AppLifecycleEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::AppLifecycleEvent, Instances::AppLifecycleEvent::mid_statusGet, Value> TFunc_Instances_AppLifecycleEvent_statusGet;
typedef ThunkFunc0<Instances::AppLifecycleEvent, Instances::AppLifecycleEvent::mid_clone, Value> TFunc_Instances_AppLifecycleEvent_clone;
typedef ThunkFunc0<Instances::AppLifecycleEvent, Instances::AppLifecycleEvent::mid_toString, ASString> TFunc_Instances_AppLifecycleEvent_toString;

template <> const TFunc_Instances_AppLifecycleEvent_statusGet::TMethod TFunc_Instances_AppLifecycleEvent_statusGet::Method = &Instances::AppLifecycleEvent::statusGet;
template <> const TFunc_Instances_AppLifecycleEvent_clone::TMethod TFunc_Instances_AppLifecycleEvent_clone::Method = &Instances::AppLifecycleEvent::clone;
template <> const TFunc_Instances_AppLifecycleEvent_toString::TMethod TFunc_Instances_AppLifecycleEvent_toString::Method = &Instances::AppLifecycleEvent::toString;

namespace Instances
{
    AppLifecycleEvent::AppLifecycleEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::AppLifecycleEvent::AppLifecycleEvent()$data"
//##protect##"instance::AppLifecycleEvent::AppLifecycleEvent()$data"
    {
//##protect##"instance::AppLifecycleEvent::AppLifecycleEvent()$code"
        Status.SetNull();
//##protect##"instance::AppLifecycleEvent::AppLifecycleEvent()$code"
    }

    void AppLifecycleEvent::statusGet(Value& result)
    {
//##protect##"instance::AppLifecycleEvent::statusGet()"
        SF_UNUSED1(result);
        result = Status;
//##protect##"instance::AppLifecycleEvent::statusGet()"
    }
    void AppLifecycleEvent::clone(Value& result)
    {
//##protect##"instance::AppLifecycleEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::AppLifecycleEvent::clone()"
    }
    void AppLifecycleEvent::toString(ASString& result)
    {
//##protect##"instance::AppLifecycleEvent::toString()"
        SF_UNUSED1(result);
        //example: [AppLifecycleEvent type="sss" bubbles=false cancelable=false status=null]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("AppLifecycleEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("status")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::AppLifecycleEvent::toString()"
    }

//##protect##"instance$methods"
    void AppLifecycleEvent::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Event::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC(prcc, Status, op SF_DEBUG_ARG(*this));
    }
    // public function AppLifecycleEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false, 
    //                                   status:String = null)
    void AppLifecycleEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        if (argc >= 4)
        {
            Status = argv[3];
            if (!argv[3].IsNull())
            {
                Status.ToStringValue(vm.GetStringManager()).DoNotCheck();
            }
        }
    }
    AS3::Object* AppLifecycleEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).AppLifecycleEventClass; 
    }

    SPtr<Instances::Event> AppLifecycleEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        AppLifecycleEvent* pe = static_cast<AppLifecycleEvent*>(p.GetPtr());
        pe->Status  = Status;
        return p;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo AppLifecycleEvent::ti[AppLifecycleEvent::ThunkInfoNum] = {
        {TFunc_Instances_AppLifecycleEvent_statusGet::Func, &ObjectCI, "status", NULL, CT_Get, 0, 0},
        {TFunc_Instances_AppLifecycleEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_AppLifecycleEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    AppLifecycleEvent::AppLifecycleEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::AppLifecycleEvent::AppLifecycleEvent()"
//##protect##"InstanceTraits::AppLifecycleEvent::AppLifecycleEvent()"
        SetMemSize(sizeof(Instances::AppLifecycleEvent));

    }

    Pickable<Instances::AppLifecycleEvent> AppLifecycleEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::AppLifecycleEvent>(new(t.Alloc()) Instances::AppLifecycleEvent(t));
    }

    void AppLifecycleEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    AppLifecycleEvent::AppLifecycleEvent(ClassTraits::Traits& t)
    : Class(t)
    , ONPAUSE("onPause")
    , ONRESUME("onResume")
    {
//##protect##"class_::AppLifecycleEvent::AppLifecycleEvent()"
//##protect##"class_::AppLifecycleEvent::AppLifecycleEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo AppLifecycleEvent::mi[AppLifecycleEvent::MemberInfoNum] = {
        {"ONPAUSE", OFFSETOF(Classes::AppLifecycleEvent, ONPAUSE), SlotInfo::BT_ConstChar, 1},
        {"ONRESUME", OFFSETOF(Classes::AppLifecycleEvent, ONRESUME), SlotInfo::BT_ConstChar, 1},
    };

    AppLifecycleEvent::AppLifecycleEvent(VM& vm)
    : Traits(vm, AppLifecycleEventCI)
    {
//##protect##"ClassTraits::AppLifecycleEvent::AppLifecycleEvent()"
//##protect##"ClassTraits::AppLifecycleEvent::AppLifecycleEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::AppLifecycleEvent(vm, AppLifecycleEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::AppLifecycleEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> AppLifecycleEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AppLifecycleEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo AppLifecycleEventCI = {
    ClassInfo::CompileTime,
    "AppLifecycleEvent", "flash.events", &EventCI,
    ClassTraits::AppLifecycleEvent::MakeClassTraits,
    0,
    ClassTraits::AppLifecycleEvent::MemberInfoNum,
    InstanceTraits::AppLifecycleEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::AppLifecycleEvent::mi,
    InstanceTraits::AppLifecycleEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

