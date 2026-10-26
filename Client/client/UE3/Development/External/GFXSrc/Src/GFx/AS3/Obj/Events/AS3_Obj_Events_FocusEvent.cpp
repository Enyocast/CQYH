//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_FocusEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_FocusEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
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
typedef ThunkFunc0<Instances::FocusEvent, Instances::FocusEvent::mid_directionGet, ASString> TFunc_Instances_FocusEvent_directionGet;
typedef ThunkFunc1<Instances::FocusEvent, Instances::FocusEvent::mid_directionSet, Value, const ASString&> TFunc_Instances_FocusEvent_directionSet;
typedef ThunkFunc0<Instances::FocusEvent, Instances::FocusEvent::mid_keyCodeGet, UInt32> TFunc_Instances_FocusEvent_keyCodeGet;
typedef ThunkFunc1<Instances::FocusEvent, Instances::FocusEvent::mid_keyCodeSet, Value, UInt32> TFunc_Instances_FocusEvent_keyCodeSet;
typedef ThunkFunc0<Instances::FocusEvent, Instances::FocusEvent::mid_relatedObjectGet, Value> TFunc_Instances_FocusEvent_relatedObjectGet;
typedef ThunkFunc1<Instances::FocusEvent, Instances::FocusEvent::mid_relatedObjectSet, Value, Instances::InteractiveObject*> TFunc_Instances_FocusEvent_relatedObjectSet;
typedef ThunkFunc0<Instances::FocusEvent, Instances::FocusEvent::mid_shiftKeyGet, bool> TFunc_Instances_FocusEvent_shiftKeyGet;
typedef ThunkFunc1<Instances::FocusEvent, Instances::FocusEvent::mid_shiftKeySet, Value, bool> TFunc_Instances_FocusEvent_shiftKeySet;
typedef ThunkFunc0<Instances::FocusEvent, Instances::FocusEvent::mid_clone, Value> TFunc_Instances_FocusEvent_clone;
typedef ThunkFunc0<Instances::FocusEvent, Instances::FocusEvent::mid_toString, ASString> TFunc_Instances_FocusEvent_toString;

template <> const TFunc_Instances_FocusEvent_directionGet::TMethod TFunc_Instances_FocusEvent_directionGet::Method = &Instances::FocusEvent::directionGet;
template <> const TFunc_Instances_FocusEvent_directionSet::TMethod TFunc_Instances_FocusEvent_directionSet::Method = &Instances::FocusEvent::directionSet;
template <> const TFunc_Instances_FocusEvent_keyCodeGet::TMethod TFunc_Instances_FocusEvent_keyCodeGet::Method = &Instances::FocusEvent::keyCodeGet;
template <> const TFunc_Instances_FocusEvent_keyCodeSet::TMethod TFunc_Instances_FocusEvent_keyCodeSet::Method = &Instances::FocusEvent::keyCodeSet;
template <> const TFunc_Instances_FocusEvent_relatedObjectGet::TMethod TFunc_Instances_FocusEvent_relatedObjectGet::Method = &Instances::FocusEvent::relatedObjectGet;
template <> const TFunc_Instances_FocusEvent_relatedObjectSet::TMethod TFunc_Instances_FocusEvent_relatedObjectSet::Method = &Instances::FocusEvent::relatedObjectSet;
template <> const TFunc_Instances_FocusEvent_shiftKeyGet::TMethod TFunc_Instances_FocusEvent_shiftKeyGet::Method = &Instances::FocusEvent::shiftKeyGet;
template <> const TFunc_Instances_FocusEvent_shiftKeySet::TMethod TFunc_Instances_FocusEvent_shiftKeySet::Method = &Instances::FocusEvent::shiftKeySet;
template <> const TFunc_Instances_FocusEvent_clone::TMethod TFunc_Instances_FocusEvent_clone::Method = &Instances::FocusEvent::clone;
template <> const TFunc_Instances_FocusEvent_toString::TMethod TFunc_Instances_FocusEvent_toString::Method = &Instances::FocusEvent::toString;

namespace Instances
{
    FocusEvent::FocusEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::FocusEvent::FocusEvent()$data"
    , ShiftKey(false)
    , KeyCode(0)
//##protect##"instance::FocusEvent::FocusEvent()$data"
    {
//##protect##"instance::FocusEvent::FocusEvent()$code"
//##protect##"instance::FocusEvent::FocusEvent()$code"
    }

    void FocusEvent::directionGet(ASString& result)
    {
//##protect##"instance::FocusEvent::directionGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("FocusEvent::directionGet()");
//##protect##"instance::FocusEvent::directionGet()"
    }
    void FocusEvent::directionSet(Value& result, const ASString& value)
    {
//##protect##"instance::FocusEvent::directionSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("FocusEvent::directionSet()");
//##protect##"instance::FocusEvent::directionSet()"
    }
    void FocusEvent::keyCodeGet(UInt32& result)
    {
//##protect##"instance::FocusEvent::keyCodeGet()"
        SF_UNUSED1(result);
        result = KeyCode;
//##protect##"instance::FocusEvent::keyCodeGet()"
    }
    void FocusEvent::keyCodeSet(Value& result, UInt32 value)
    {
//##protect##"instance::FocusEvent::keyCodeSet()"
        SF_UNUSED2(result, value);
        KeyCode = value;
//##protect##"instance::FocusEvent::keyCodeSet()"
    }
    void FocusEvent::relatedObjectGet(Value& result)
    {
//##protect##"instance::FocusEvent::relatedObjectGet()"
        SF_UNUSED1(result);
        result = RelatedObj;
//##protect##"instance::FocusEvent::relatedObjectGet()"
    }
    void FocusEvent::relatedObjectSet(Value& result, Instances::InteractiveObject* value)
    {
//##protect##"instance::FocusEvent::relatedObjectSet()"
        SF_UNUSED2(result, value);
        RelatedObj = value;
//##protect##"instance::FocusEvent::relatedObjectSet()"
    }
    void FocusEvent::shiftKeyGet(bool& result)
    {
//##protect##"instance::FocusEvent::shiftKeyGet()"
        SF_UNUSED1(result);
        result = ShiftKey;
//##protect##"instance::FocusEvent::shiftKeyGet()"
    }
    void FocusEvent::shiftKeySet(Value& result, bool value)
    {
//##protect##"instance::FocusEvent::shiftKeySet()"
        SF_UNUSED2(result, value);
        ShiftKey = value;
//##protect##"instance::FocusEvent::shiftKeySet()"
    }
    void FocusEvent::clone(Value& result)
    {
//##protect##"instance::FocusEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::FocusEvent::clone()"
    }
    void FocusEvent::toString(ASString& result)
    {
//##protect##"instance::FocusEvent::toString()"
        SF_UNUSED1(result);
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("FocusEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("relatedObject"),
            vm.GetStringManager().CreateConstString("shiftKey"),
            vm.GetStringManager().CreateConstString("keyCode")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::FocusEvent::toString()"
    }

//##protect##"instance$methods"
    void FocusEvent::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<InteractiveObject, Mem_Stat>(prcc, RelatedObj, op SF_DEBUG_ARG(*this));
    }
    AS3::Object* FocusEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).FocusEventClass; 
    }

    SPtr<Instances::Event> FocusEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        FocusEvent* pe = static_cast<FocusEvent*>(p.GetPtr());
        pe->RelatedObj = RelatedObj;
        pe->ShiftKey   = ShiftKey;
        pe->KeyCode    = KeyCode;
        return p;
    }
    void FocusEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            RelatedObj = NULL;
            AS3::Object* ptr = argv[3].GetObject();
            if (ptr)
            {
                if (GetVM().IsOfType(argv[3], "flash.display.InteractiveObject"))
                {
                    RelatedObj = static_cast<InteractiveObject*>(ptr);
                }
            }
        }
        if (argc >= 5)
        {
            ShiftKey = argv[4].Convert2Boolean();
        }
        if (argc >= 6)
        {
            UInt32 v;
            argv[5].Convert2UInt32(v).DoNotCheck();
            KeyCode = v;
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo FocusEvent::ti[FocusEvent::ThunkInfoNum] = {
        {TFunc_Instances_FocusEvent_directionGet::Func, &StringCI, "direction", NULL, CT_Get, 0, 0},
        {TFunc_Instances_FocusEvent_directionSet::Func, NULL, "direction", NULL, CT_Set, 1, 1},
        {TFunc_Instances_FocusEvent_keyCodeGet::Func, &uintCI, "keyCode", NULL, CT_Get, 0, 0},
        {TFunc_Instances_FocusEvent_keyCodeSet::Func, NULL, "keyCode", NULL, CT_Set, 1, 1},
        {TFunc_Instances_FocusEvent_relatedObjectGet::Func, &InteractiveObjectCI, "relatedObject", NULL, CT_Get, 0, 0},
        {TFunc_Instances_FocusEvent_relatedObjectSet::Func, NULL, "relatedObject", NULL, CT_Set, 1, 1},
        {TFunc_Instances_FocusEvent_shiftKeyGet::Func, &BooleanCI, "shiftKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_FocusEvent_shiftKeySet::Func, NULL, "shiftKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_FocusEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_FocusEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    FocusEvent::FocusEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::FocusEvent::FocusEvent()"
//##protect##"InstanceTraits::FocusEvent::FocusEvent()"
        SetMemSize(sizeof(Instances::FocusEvent));

    }

    Pickable<Instances::FocusEvent> FocusEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::FocusEvent>(new(t.Alloc()) Instances::FocusEvent(t));
    }

    void FocusEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    FocusEvent::FocusEvent(ClassTraits::Traits& t)
    : Class(t)
    , FOCUS_IN("focusIn")
    , FOCUS_OUT("focusOut")
    , KEY_FOCUS_CHANGE("keyFocusChange")
    , MOUSE_FOCUS_CHANGE("mouseFocusChange")
    {
//##protect##"class_::FocusEvent::FocusEvent()"
//##protect##"class_::FocusEvent::FocusEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo FocusEvent::mi[FocusEvent::MemberInfoNum] = {
        {"FOCUS_IN", OFFSETOF(Classes::FocusEvent, FOCUS_IN), SlotInfo::BT_ConstChar, 1},
        {"FOCUS_OUT", OFFSETOF(Classes::FocusEvent, FOCUS_OUT), SlotInfo::BT_ConstChar, 1},
        {"KEY_FOCUS_CHANGE", OFFSETOF(Classes::FocusEvent, KEY_FOCUS_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_FOCUS_CHANGE", OFFSETOF(Classes::FocusEvent, MOUSE_FOCUS_CHANGE), SlotInfo::BT_ConstChar, 1},
    };

    FocusEvent::FocusEvent(VM& vm)
    : Traits(vm, FocusEventCI)
    {
//##protect##"ClassTraits::FocusEvent::FocusEvent()"
//##protect##"ClassTraits::FocusEvent::FocusEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::FocusEvent(vm, FocusEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FocusEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FocusEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FocusEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FocusEventCI = {
    ClassInfo::CompileTime,
    "FocusEvent", "flash.events", &EventCI,
    ClassTraits::FocusEvent::MakeClassTraits,
    0,
    ClassTraits::FocusEvent::MemberInfoNum,
    InstanceTraits::FocusEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::FocusEvent::mi,
    InstanceTraits::FocusEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

