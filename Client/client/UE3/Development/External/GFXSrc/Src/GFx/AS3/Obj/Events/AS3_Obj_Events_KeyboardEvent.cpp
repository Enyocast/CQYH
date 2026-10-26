//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_KeyboardEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_KeyboardEvent.h"
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
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_altKeyGet, bool> TFunc_Instances_KeyboardEvent_altKeyGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_altKeySet, Value, bool> TFunc_Instances_KeyboardEvent_altKeySet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_charCodeGet, UInt32> TFunc_Instances_KeyboardEvent_charCodeGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_charCodeSet, Value, UInt32> TFunc_Instances_KeyboardEvent_charCodeSet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_commandKeyGet, bool> TFunc_Instances_KeyboardEvent_commandKeyGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_commandKeySet, Value, bool> TFunc_Instances_KeyboardEvent_commandKeySet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_controlKeyGet, bool> TFunc_Instances_KeyboardEvent_controlKeyGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_controlKeySet, Value, bool> TFunc_Instances_KeyboardEvent_controlKeySet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_ctrlKeyGet, bool> TFunc_Instances_KeyboardEvent_ctrlKeyGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_ctrlKeySet, Value, bool> TFunc_Instances_KeyboardEvent_ctrlKeySet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_keyCodeGet, UInt32> TFunc_Instances_KeyboardEvent_keyCodeGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_keyCodeSet, Value, UInt32> TFunc_Instances_KeyboardEvent_keyCodeSet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_keyLocationGet, UInt32> TFunc_Instances_KeyboardEvent_keyLocationGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_keyLocationSet, Value, UInt32> TFunc_Instances_KeyboardEvent_keyLocationSet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_shiftKeyGet, bool> TFunc_Instances_KeyboardEvent_shiftKeyGet;
typedef ThunkFunc1<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_shiftKeySet, Value, bool> TFunc_Instances_KeyboardEvent_shiftKeySet;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_clone, Value> TFunc_Instances_KeyboardEvent_clone;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_toString, ASString> TFunc_Instances_KeyboardEvent_toString;
typedef ThunkFunc0<Instances::KeyboardEvent, Instances::KeyboardEvent::mid_updateAfterEvent, Value> TFunc_Instances_KeyboardEvent_updateAfterEvent;

template <> const TFunc_Instances_KeyboardEvent_altKeyGet::TMethod TFunc_Instances_KeyboardEvent_altKeyGet::Method = &Instances::KeyboardEvent::altKeyGet;
template <> const TFunc_Instances_KeyboardEvent_altKeySet::TMethod TFunc_Instances_KeyboardEvent_altKeySet::Method = &Instances::KeyboardEvent::altKeySet;
template <> const TFunc_Instances_KeyboardEvent_charCodeGet::TMethod TFunc_Instances_KeyboardEvent_charCodeGet::Method = &Instances::KeyboardEvent::charCodeGet;
template <> const TFunc_Instances_KeyboardEvent_charCodeSet::TMethod TFunc_Instances_KeyboardEvent_charCodeSet::Method = &Instances::KeyboardEvent::charCodeSet;
template <> const TFunc_Instances_KeyboardEvent_commandKeyGet::TMethod TFunc_Instances_KeyboardEvent_commandKeyGet::Method = &Instances::KeyboardEvent::commandKeyGet;
template <> const TFunc_Instances_KeyboardEvent_commandKeySet::TMethod TFunc_Instances_KeyboardEvent_commandKeySet::Method = &Instances::KeyboardEvent::commandKeySet;
template <> const TFunc_Instances_KeyboardEvent_controlKeyGet::TMethod TFunc_Instances_KeyboardEvent_controlKeyGet::Method = &Instances::KeyboardEvent::controlKeyGet;
template <> const TFunc_Instances_KeyboardEvent_controlKeySet::TMethod TFunc_Instances_KeyboardEvent_controlKeySet::Method = &Instances::KeyboardEvent::controlKeySet;
template <> const TFunc_Instances_KeyboardEvent_ctrlKeyGet::TMethod TFunc_Instances_KeyboardEvent_ctrlKeyGet::Method = &Instances::KeyboardEvent::ctrlKeyGet;
template <> const TFunc_Instances_KeyboardEvent_ctrlKeySet::TMethod TFunc_Instances_KeyboardEvent_ctrlKeySet::Method = &Instances::KeyboardEvent::ctrlKeySet;
template <> const TFunc_Instances_KeyboardEvent_keyCodeGet::TMethod TFunc_Instances_KeyboardEvent_keyCodeGet::Method = &Instances::KeyboardEvent::keyCodeGet;
template <> const TFunc_Instances_KeyboardEvent_keyCodeSet::TMethod TFunc_Instances_KeyboardEvent_keyCodeSet::Method = &Instances::KeyboardEvent::keyCodeSet;
template <> const TFunc_Instances_KeyboardEvent_keyLocationGet::TMethod TFunc_Instances_KeyboardEvent_keyLocationGet::Method = &Instances::KeyboardEvent::keyLocationGet;
template <> const TFunc_Instances_KeyboardEvent_keyLocationSet::TMethod TFunc_Instances_KeyboardEvent_keyLocationSet::Method = &Instances::KeyboardEvent::keyLocationSet;
template <> const TFunc_Instances_KeyboardEvent_shiftKeyGet::TMethod TFunc_Instances_KeyboardEvent_shiftKeyGet::Method = &Instances::KeyboardEvent::shiftKeyGet;
template <> const TFunc_Instances_KeyboardEvent_shiftKeySet::TMethod TFunc_Instances_KeyboardEvent_shiftKeySet::Method = &Instances::KeyboardEvent::shiftKeySet;
template <> const TFunc_Instances_KeyboardEvent_clone::TMethod TFunc_Instances_KeyboardEvent_clone::Method = &Instances::KeyboardEvent::clone;
template <> const TFunc_Instances_KeyboardEvent_toString::TMethod TFunc_Instances_KeyboardEvent_toString::Method = &Instances::KeyboardEvent::toString;
template <> const TFunc_Instances_KeyboardEvent_updateAfterEvent::TMethod TFunc_Instances_KeyboardEvent_updateAfterEvent::Method = &Instances::KeyboardEvent::updateAfterEvent;

namespace Instances
{
    KeyboardEvent::KeyboardEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::KeyboardEvent::KeyboardEvent()$data"
    , KeyLocation(-1)
//##protect##"instance::KeyboardEvent::KeyboardEvent()$data"
    {
//##protect##"instance::KeyboardEvent::KeyboardEvent()$code"
//##protect##"instance::KeyboardEvent::KeyboardEvent()$code"
    }

    void KeyboardEvent::altKeyGet(bool& result)
    {
//##protect##"instance::KeyboardEvent::altKeyGet()"
        result = EvtId.KeysState.IsAltPressed();
//##protect##"instance::KeyboardEvent::altKeyGet()"
    }
    void KeyboardEvent::altKeySet(Value& result, bool value)
    {
//##protect##"instance::KeyboardEvent::altKeySet()"
        SF_UNUSED(result);
        EvtId.KeysState.SetAltPressed(value);
//##protect##"instance::KeyboardEvent::altKeySet()"
    }
    void KeyboardEvent::charCodeGet(UInt32& result)
    {
//##protect##"instance::KeyboardEvent::charCodeGet()"
        result = (UInt32)EvtId.AsciiCode;
//##protect##"instance::KeyboardEvent::charCodeGet()"
    }
    void KeyboardEvent::charCodeSet(Value& result, UInt32 value)
    {
//##protect##"instance::KeyboardEvent::charCodeSet()"
        SF_UNUSED(result);
        EvtId.AsciiCode = (UByte)value;
//##protect##"instance::KeyboardEvent::charCodeSet()"
    }
    void KeyboardEvent::commandKeyGet(bool& result)
    {
//##protect##"instance::KeyboardEvent::commandKeyGet()"
        result = EvtId.KeysState.IsCtrlPressed();
//##protect##"instance::KeyboardEvent::commandKeyGet()"
    }
    void KeyboardEvent::commandKeySet(Value& result, bool value)
    {
//##protect##"instance::KeyboardEvent::commandKeySet()"
        SF_UNUSED1(result);
        EvtId.KeysState.SetCtrlPressed(value);
//##protect##"instance::KeyboardEvent::commandKeySet()"
    }
    void KeyboardEvent::controlKeyGet(bool& result)
    {
//##protect##"instance::KeyboardEvent::controlKeyGet()"
        result = EvtId.KeysState.IsCtrlPressed();
//##protect##"instance::KeyboardEvent::controlKeyGet()"
    }
    void KeyboardEvent::controlKeySet(Value& result, bool value)
    {
//##protect##"instance::KeyboardEvent::controlKeySet()"
        SF_UNUSED1(result);
        EvtId.KeysState.SetCtrlPressed(value);
//##protect##"instance::KeyboardEvent::controlKeySet()"
    }
    void KeyboardEvent::ctrlKeyGet(bool& result)
    {
//##protect##"instance::KeyboardEvent::ctrlKeyGet()"
        result = EvtId.KeysState.IsCtrlPressed();
//##protect##"instance::KeyboardEvent::ctrlKeyGet()"
    }
    void KeyboardEvent::ctrlKeySet(Value& result, bool value)
    {
//##protect##"instance::KeyboardEvent::ctrlKeySet()"
        SF_UNUSED1(result);
        EvtId.KeysState.SetCtrlPressed(value);
//##protect##"instance::KeyboardEvent::ctrlKeySet()"
    }
    void KeyboardEvent::keyCodeGet(UInt32& result)
    {
//##protect##"instance::KeyboardEvent::keyCodeGet()"
        result = (UInt32)EvtId.KeyCode;
//##protect##"instance::KeyboardEvent::keyCodeGet()"
    }
    void KeyboardEvent::keyCodeSet(Value& result, UInt32 value)
    {
//##protect##"instance::KeyboardEvent::keyCodeSet()"
        SF_UNUSED(result);
        EvtId.KeyCode = value;
//##protect##"instance::KeyboardEvent::keyCodeSet()"
    }
    void KeyboardEvent::keyLocationGet(UInt32& result)
    {
//##protect##"instance::KeyboardEvent::keyLocationGet()"
        SF_UNUSED1(result);
        if (KeyLocation < 0) // not initialized yet
        {
            if (EvtId.KeysState.IsSpecialKeyPressed())
                KeyLocation = (EvtId.KeysState.IsExtendedKey() ? 2 : 1);
            else
                KeyLocation = 0;
        }
        result = (UInt32)KeyLocation;
//##protect##"instance::KeyboardEvent::keyLocationGet()"
    }
    void KeyboardEvent::keyLocationSet(Value& result, UInt32 value)
    {
//##protect##"instance::KeyboardEvent::keyLocationSet()"
        SF_UNUSED2(result, value);
        KeyLocation = value;
//##protect##"instance::KeyboardEvent::keyLocationSet()"
    }
    void KeyboardEvent::shiftKeyGet(bool& result)
    {
//##protect##"instance::KeyboardEvent::shiftKeyGet()"
        result = EvtId.KeysState.IsShiftPressed();
//##protect##"instance::KeyboardEvent::shiftKeyGet()"
    }
    void KeyboardEvent::shiftKeySet(Value& result, bool value)
    {
//##protect##"instance::KeyboardEvent::shiftKeySet()"
        SF_UNUSED1(result);
        EvtId.KeysState.SetShiftPressed(value);
//##protect##"instance::KeyboardEvent::shiftKeySet()"
    }
    void KeyboardEvent::clone(Value& result)
    {
//##protect##"instance::KeyboardEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::KeyboardEvent::clone()"
    }
    void KeyboardEvent::toString(ASString& result)
    {
//##protect##"instance::KeyboardEvent::toString()"
        SF_UNUSED1(result);
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("KeyboardEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("charCode"),
            vm.GetStringManager().CreateConstString("keyCode"),
            vm.GetStringManager().CreateConstString("keyLocation"),
            vm.GetStringManager().CreateConstString("ctrlKey"),
            vm.GetStringManager().CreateConstString("altKey"),
            vm.GetStringManager().CreateConstString("shiftKey")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
        
//##protect##"instance::KeyboardEvent::toString()"
    }
    void KeyboardEvent::updateAfterEvent(Value& result)
    {
//##protect##"instance::KeyboardEvent::updateAfterEvent()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("KeyboardEvent::updateAfterEvent()");
//##protect##"instance::KeyboardEvent::updateAfterEvent()"
    }

//##protect##"instance$methods"
    void KeyboardEvent::SetEventId(const EventId& eid)
    {
        EvtId = eid;
        if (EvtId.AsciiCode == 0)
        {
            EvtId.AsciiCode = EvtId.ConvertKeyCodeToAscii();
        }
    }

    AS3::Object* KeyboardEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).KeyboardEventClass; 
    }

    SPtr<Instances::Event> KeyboardEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        KeyboardEvent* pe   = static_cast<KeyboardEvent*>(p.GetPtr());
        pe->EvtId           = EvtId;
        pe->KeyLocation     = KeyLocation;
        return p;
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo KeyboardEvent::ti[KeyboardEvent::ThunkInfoNum] = {
        {TFunc_Instances_KeyboardEvent_altKeyGet::Func, &BooleanCI, "altKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_altKeySet::Func, NULL, "altKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_charCodeGet::Func, &uintCI, "charCode", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_charCodeSet::Func, NULL, "charCode", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_commandKeyGet::Func, &BooleanCI, "commandKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_commandKeySet::Func, NULL, "commandKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_controlKeyGet::Func, &BooleanCI, "controlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_controlKeySet::Func, NULL, "controlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_ctrlKeyGet::Func, &BooleanCI, "ctrlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_ctrlKeySet::Func, NULL, "ctrlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_keyCodeGet::Func, &uintCI, "keyCode", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_keyCodeSet::Func, NULL, "keyCode", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_keyLocationGet::Func, &uintCI, "keyLocation", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_keyLocationSet::Func, NULL, "keyLocation", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_shiftKeyGet::Func, &BooleanCI, "shiftKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_KeyboardEvent_shiftKeySet::Func, NULL, "shiftKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_KeyboardEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_KeyboardEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_KeyboardEvent_updateAfterEvent::Func, NULL, "updateAfterEvent", NULL, CT_Method, 0, 0},
    };

    KeyboardEvent::KeyboardEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::KeyboardEvent::KeyboardEvent()"
//##protect##"InstanceTraits::KeyboardEvent::KeyboardEvent()"
        SetMemSize(sizeof(Instances::KeyboardEvent));

    }

    Pickable<Instances::KeyboardEvent> KeyboardEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::KeyboardEvent>(new(t.Alloc()) Instances::KeyboardEvent(t));
    }

    void KeyboardEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    KeyboardEvent::KeyboardEvent(ClassTraits::Traits& t)
    : Class(t)
    , KEY_DOWN("keyDown")
    , KEY_UP("keyUp")
    {
//##protect##"class_::KeyboardEvent::KeyboardEvent()"
//##protect##"class_::KeyboardEvent::KeyboardEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo KeyboardEvent::mi[KeyboardEvent::MemberInfoNum] = {
        {"KEY_DOWN", OFFSETOF(Classes::KeyboardEvent, KEY_DOWN), SlotInfo::BT_ConstChar, 1},
        {"KEY_UP", OFFSETOF(Classes::KeyboardEvent, KEY_UP), SlotInfo::BT_ConstChar, 1},
    };

    KeyboardEvent::KeyboardEvent(VM& vm)
    : Traits(vm, KeyboardEventCI)
    {
//##protect##"ClassTraits::KeyboardEvent::KeyboardEvent()"
//##protect##"ClassTraits::KeyboardEvent::KeyboardEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::KeyboardEvent(vm, KeyboardEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::KeyboardEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> KeyboardEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) KeyboardEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo KeyboardEventCI = {
    ClassInfo::CompileTime,
    "KeyboardEvent", "flash.events", &EventCI,
    ClassTraits::KeyboardEvent::MakeClassTraits,
    0,
    ClassTraits::KeyboardEvent::MemberInfoNum,
    InstanceTraits::KeyboardEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::KeyboardEvent::mi,
    InstanceTraits::KeyboardEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

