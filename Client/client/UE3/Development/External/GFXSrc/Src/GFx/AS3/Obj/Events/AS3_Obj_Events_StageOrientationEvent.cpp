//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_StageOrientationEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_StageOrientationEvent.h"
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
typedef ThunkFunc0<Instances::StageOrientationEvent, Instances::StageOrientationEvent::mid_afterOrientationGet, Value> TFunc_Instances_StageOrientationEvent_afterOrientationGet;
typedef ThunkFunc0<Instances::StageOrientationEvent, Instances::StageOrientationEvent::mid_beforeOrientationGet, Value> TFunc_Instances_StageOrientationEvent_beforeOrientationGet;
typedef ThunkFunc0<Instances::StageOrientationEvent, Instances::StageOrientationEvent::mid_clone, Value> TFunc_Instances_StageOrientationEvent_clone;
typedef ThunkFunc0<Instances::StageOrientationEvent, Instances::StageOrientationEvent::mid_toString, ASString> TFunc_Instances_StageOrientationEvent_toString;

template <> const TFunc_Instances_StageOrientationEvent_afterOrientationGet::TMethod TFunc_Instances_StageOrientationEvent_afterOrientationGet::Method = &Instances::StageOrientationEvent::afterOrientationGet;
template <> const TFunc_Instances_StageOrientationEvent_beforeOrientationGet::TMethod TFunc_Instances_StageOrientationEvent_beforeOrientationGet::Method = &Instances::StageOrientationEvent::beforeOrientationGet;
template <> const TFunc_Instances_StageOrientationEvent_clone::TMethod TFunc_Instances_StageOrientationEvent_clone::Method = &Instances::StageOrientationEvent::clone;
template <> const TFunc_Instances_StageOrientationEvent_toString::TMethod TFunc_Instances_StageOrientationEvent_toString::Method = &Instances::StageOrientationEvent::toString;

namespace Instances
{
    StageOrientationEvent::StageOrientationEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::StageOrientationEvent::StageOrientationEvent()$data"
//##protect##"instance::StageOrientationEvent::StageOrientationEvent()$data"
    {
//##protect##"instance::StageOrientationEvent::StageOrientationEvent()$code"
        BeforeOrientation.SetNull();
        AfterOrientation.SetNull();
//##protect##"instance::StageOrientationEvent::StageOrientationEvent()$code"
    }

    void StageOrientationEvent::afterOrientationGet(Value& result)
    {
//##protect##"instance::StageOrientationEvent::afterOrientationGet()"
        SF_UNUSED1(result);
        result = AfterOrientation;
//##protect##"instance::StageOrientationEvent::afterOrientationGet()"
    }
    void StageOrientationEvent::beforeOrientationGet(Value& result)
    {
//##protect##"instance::StageOrientationEvent::beforeOrientationGet()"
        SF_UNUSED1(result);
        result = BeforeOrientation;
//##protect##"instance::StageOrientationEvent::beforeOrientationGet()"
    }
    void StageOrientationEvent::clone(Value& result)
    {
//##protect##"instance::StageOrientationEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::StageOrientationEvent::clone()"
    }
    void StageOrientationEvent::toString(ASString& result)
    {
//##protect##"instance::StageOrientationEvent::toString()"
        SF_UNUSED1(result);
        //example: [StageOrientationEvent type="sss" bubbles=false cancelable=false beforeOrientation=null afterOrientation=null]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("StageOrientationEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("beforeOrientation"),
            vm.GetStringManager().CreateConstString("afterOrientation")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::StageOrientationEvent::toString()"
    }

//##protect##"instance$methods"
    void StageOrientationEvent::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Event::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC(prcc, BeforeOrientation, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, AfterOrientation, op SF_DEBUG_ARG(*this));
    }
    // public function StageOrientationEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false, 
    //                                       beforeOrientation:String = null, afterOrientation:String = null)
    void StageOrientationEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        if (argc >= 4)
        {
            BeforeOrientation = argv[3];
            if (!argv[3].IsNull())
            {
                BeforeOrientation.ToStringValue(vm.GetStringManager()).DoNotCheck();
            }
        }
        if (argc >= 5)
        {
            AfterOrientation = argv[4];
            if (!argv[3].IsNull())
            {
                AfterOrientation.ToStringValue(vm.GetStringManager()).DoNotCheck();
            }
        }
    }
    AS3::Object* StageOrientationEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).StageOrientationEventClass; 
    }

    SPtr<Instances::Event> StageOrientationEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        StageOrientationEvent* pe = static_cast<StageOrientationEvent*>(p.GetPtr());
        pe->BeforeOrientation = BeforeOrientation;
        pe->AfterOrientation  = AfterOrientation;
        return p;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo StageOrientationEvent::ti[StageOrientationEvent::ThunkInfoNum] = {
        {TFunc_Instances_StageOrientationEvent_afterOrientationGet::Func, &ObjectCI, "afterOrientation", NULL, CT_Get, 0, 0},
        {TFunc_Instances_StageOrientationEvent_beforeOrientationGet::Func, &ObjectCI, "beforeOrientation", NULL, CT_Get, 0, 0},
        {TFunc_Instances_StageOrientationEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_StageOrientationEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    StageOrientationEvent::StageOrientationEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::StageOrientationEvent::StageOrientationEvent()"
//##protect##"InstanceTraits::StageOrientationEvent::StageOrientationEvent()"
        SetMemSize(sizeof(Instances::StageOrientationEvent));

    }

    Pickable<Instances::StageOrientationEvent> StageOrientationEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::StageOrientationEvent>(new(t.Alloc()) Instances::StageOrientationEvent(t));
    }

    void StageOrientationEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    StageOrientationEvent::StageOrientationEvent(ClassTraits::Traits& t)
    : Class(t)
    , ORIENTATION_CHANGE("orientationChange")
    , ORIENTATION_CHANGING("orientationChanging")
    {
//##protect##"class_::StageOrientationEvent::StageOrientationEvent()"
//##protect##"class_::StageOrientationEvent::StageOrientationEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo StageOrientationEvent::mi[StageOrientationEvent::MemberInfoNum] = {
        {"ORIENTATION_CHANGE", OFFSETOF(Classes::StageOrientationEvent, ORIENTATION_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"ORIENTATION_CHANGING", OFFSETOF(Classes::StageOrientationEvent, ORIENTATION_CHANGING), SlotInfo::BT_ConstChar, 1},
    };

    StageOrientationEvent::StageOrientationEvent(VM& vm)
    : Traits(vm, StageOrientationEventCI)
    {
//##protect##"ClassTraits::StageOrientationEvent::StageOrientationEvent()"
//##protect##"ClassTraits::StageOrientationEvent::StageOrientationEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::StageOrientationEvent(vm, StageOrientationEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::StageOrientationEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StageOrientationEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StageOrientationEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StageOrientationEventCI = {
    ClassInfo::CompileTime,
    "StageOrientationEvent", "flash.events", &EventCI,
    ClassTraits::StageOrientationEvent::MakeClassTraits,
    0,
    ClassTraits::StageOrientationEvent::MemberInfoNum,
    InstanceTraits::StageOrientationEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::StageOrientationEvent::mi,
    InstanceTraits::StageOrientationEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

