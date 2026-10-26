//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_GestureEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_GestureEvent.h"
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
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_altKeyGet, bool> TFunc_Instances_GestureEvent_altKeyGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_altKeySet, Value, bool> TFunc_Instances_GestureEvent_altKeySet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_commandKeyGet, bool> TFunc_Instances_GestureEvent_commandKeyGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_commandKeySet, Value, bool> TFunc_Instances_GestureEvent_commandKeySet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_controlKeyGet, bool> TFunc_Instances_GestureEvent_controlKeyGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_controlKeySet, Value, bool> TFunc_Instances_GestureEvent_controlKeySet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_ctrlKeyGet, bool> TFunc_Instances_GestureEvent_ctrlKeyGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_ctrlKeySet, Value, bool> TFunc_Instances_GestureEvent_ctrlKeySet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_localXGet, Value::Number> TFunc_Instances_GestureEvent_localXGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_localXSet, Value, Value::Number> TFunc_Instances_GestureEvent_localXSet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_localYGet, Value::Number> TFunc_Instances_GestureEvent_localYGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_localYSet, Value, Value::Number> TFunc_Instances_GestureEvent_localYSet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_phaseGet, Value> TFunc_Instances_GestureEvent_phaseGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_phaseSet, Value, const Value&> TFunc_Instances_GestureEvent_phaseSet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_shiftKeyGet, bool> TFunc_Instances_GestureEvent_shiftKeyGet;
typedef ThunkFunc1<Instances::GestureEvent, Instances::GestureEvent::mid_shiftKeySet, Value, bool> TFunc_Instances_GestureEvent_shiftKeySet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_stageXGet, Value::Number> TFunc_Instances_GestureEvent_stageXGet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_stageYGet, Value::Number> TFunc_Instances_GestureEvent_stageYGet;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_clone, Value> TFunc_Instances_GestureEvent_clone;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_toString, ASString> TFunc_Instances_GestureEvent_toString;
typedef ThunkFunc0<Instances::GestureEvent, Instances::GestureEvent::mid_updateAfterEvent, Value> TFunc_Instances_GestureEvent_updateAfterEvent;

template <> const TFunc_Instances_GestureEvent_altKeyGet::TMethod TFunc_Instances_GestureEvent_altKeyGet::Method = &Instances::GestureEvent::altKeyGet;
template <> const TFunc_Instances_GestureEvent_altKeySet::TMethod TFunc_Instances_GestureEvent_altKeySet::Method = &Instances::GestureEvent::altKeySet;
template <> const TFunc_Instances_GestureEvent_commandKeyGet::TMethod TFunc_Instances_GestureEvent_commandKeyGet::Method = &Instances::GestureEvent::commandKeyGet;
template <> const TFunc_Instances_GestureEvent_commandKeySet::TMethod TFunc_Instances_GestureEvent_commandKeySet::Method = &Instances::GestureEvent::commandKeySet;
template <> const TFunc_Instances_GestureEvent_controlKeyGet::TMethod TFunc_Instances_GestureEvent_controlKeyGet::Method = &Instances::GestureEvent::controlKeyGet;
template <> const TFunc_Instances_GestureEvent_controlKeySet::TMethod TFunc_Instances_GestureEvent_controlKeySet::Method = &Instances::GestureEvent::controlKeySet;
template <> const TFunc_Instances_GestureEvent_ctrlKeyGet::TMethod TFunc_Instances_GestureEvent_ctrlKeyGet::Method = &Instances::GestureEvent::ctrlKeyGet;
template <> const TFunc_Instances_GestureEvent_ctrlKeySet::TMethod TFunc_Instances_GestureEvent_ctrlKeySet::Method = &Instances::GestureEvent::ctrlKeySet;
template <> const TFunc_Instances_GestureEvent_localXGet::TMethod TFunc_Instances_GestureEvent_localXGet::Method = &Instances::GestureEvent::localXGet;
template <> const TFunc_Instances_GestureEvent_localXSet::TMethod TFunc_Instances_GestureEvent_localXSet::Method = &Instances::GestureEvent::localXSet;
template <> const TFunc_Instances_GestureEvent_localYGet::TMethod TFunc_Instances_GestureEvent_localYGet::Method = &Instances::GestureEvent::localYGet;
template <> const TFunc_Instances_GestureEvent_localYSet::TMethod TFunc_Instances_GestureEvent_localYSet::Method = &Instances::GestureEvent::localYSet;
template <> const TFunc_Instances_GestureEvent_phaseGet::TMethod TFunc_Instances_GestureEvent_phaseGet::Method = &Instances::GestureEvent::phaseGet;
template <> const TFunc_Instances_GestureEvent_phaseSet::TMethod TFunc_Instances_GestureEvent_phaseSet::Method = &Instances::GestureEvent::phaseSet;
template <> const TFunc_Instances_GestureEvent_shiftKeyGet::TMethod TFunc_Instances_GestureEvent_shiftKeyGet::Method = &Instances::GestureEvent::shiftKeyGet;
template <> const TFunc_Instances_GestureEvent_shiftKeySet::TMethod TFunc_Instances_GestureEvent_shiftKeySet::Method = &Instances::GestureEvent::shiftKeySet;
template <> const TFunc_Instances_GestureEvent_stageXGet::TMethod TFunc_Instances_GestureEvent_stageXGet::Method = &Instances::GestureEvent::stageXGet;
template <> const TFunc_Instances_GestureEvent_stageYGet::TMethod TFunc_Instances_GestureEvent_stageYGet::Method = &Instances::GestureEvent::stageYGet;
template <> const TFunc_Instances_GestureEvent_clone::TMethod TFunc_Instances_GestureEvent_clone::Method = &Instances::GestureEvent::clone;
template <> const TFunc_Instances_GestureEvent_toString::TMethod TFunc_Instances_GestureEvent_toString::Method = &Instances::GestureEvent::toString;
template <> const TFunc_Instances_GestureEvent_updateAfterEvent::TMethod TFunc_Instances_GestureEvent_updateAfterEvent::Method = &Instances::GestureEvent::updateAfterEvent;

namespace Instances
{
    GestureEvent::GestureEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::GestureEvent::GestureEvent()$data"
//##protect##"instance::GestureEvent::GestureEvent()$data"
    {
//##protect##"instance::GestureEvent::GestureEvent()$code"
        AltKey = CtrlKey    = ShiftKey = CommandKey = ControlKey = false;
        LocalX = LocalY     = 0;
        StageX = StageY     = 0;
        Phase               = Phase_All;
        LocalInitialized    = false;
//##protect##"instance::GestureEvent::GestureEvent()$code"
    }

    void GestureEvent::altKeyGet(bool& result)
    {
//##protect##"instance::GestureEvent::altKeyGet()"
        SF_UNUSED1(result);
        result = AltKey;
//##protect##"instance::GestureEvent::altKeyGet()"
    }
    void GestureEvent::altKeySet(Value& result, bool value)
    {
//##protect##"instance::GestureEvent::altKeySet()"
        SF_UNUSED2(result, value);
        AltKey = value;
//##protect##"instance::GestureEvent::altKeySet()"
    }
    void GestureEvent::commandKeyGet(bool& result)
    {
//##protect##"instance::GestureEvent::commandKeyGet()"
        SF_UNUSED1(result);
        result = CommandKey;
//##protect##"instance::GestureEvent::commandKeyGet()"
    }
    void GestureEvent::commandKeySet(Value& result, bool value)
    {
//##protect##"instance::GestureEvent::commandKeySet()"
        SF_UNUSED2(result, value);
        CommandKey = value;
//##protect##"instance::GestureEvent::commandKeySet()"
    }
    void GestureEvent::controlKeyGet(bool& result)
    {
//##protect##"instance::GestureEvent::controlKeyGet()"
        SF_UNUSED1(result);
        result = ControlKey;
//##protect##"instance::GestureEvent::controlKeyGet()"
    }
    void GestureEvent::controlKeySet(Value& result, bool value)
    {
//##protect##"instance::GestureEvent::controlKeySet()"
        SF_UNUSED2(result, value);
        ControlKey = value;
//##protect##"instance::GestureEvent::controlKeySet()"
    }
    void GestureEvent::ctrlKeyGet(bool& result)
    {
//##protect##"instance::GestureEvent::ctrlKeyGet()"
        SF_UNUSED1(result);
        result = CtrlKey;
//##protect##"instance::GestureEvent::ctrlKeyGet()"
    }
    void GestureEvent::ctrlKeySet(Value& result, bool value)
    {
//##protect##"instance::GestureEvent::ctrlKeySet()"
        SF_UNUSED2(result, value);
        CtrlKey = value;
//##protect##"instance::GestureEvent::ctrlKeySet()"
    }
    void GestureEvent::localXGet(Value::Number& result)
    {
//##protect##"instance::GestureEvent::localXGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalX);
//##protect##"instance::GestureEvent::localXGet()"
    }
    void GestureEvent::localXSet(Value& result, Value::Number value)
    {
//##protect##"instance::GestureEvent::localXSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalX = PixelsToTwips(value);
//##protect##"instance::GestureEvent::localXSet()"
    }
    void GestureEvent::localYGet(Value::Number& result)
    {
//##protect##"instance::GestureEvent::localYGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalY);
//##protect##"instance::GestureEvent::localYGet()"
    }
    void GestureEvent::localYSet(Value& result, Value::Number value)
    {
//##protect##"instance::GestureEvent::localYSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalY = PixelsToTwips(value);
//##protect##"instance::GestureEvent::localYSet()"
    }
    void GestureEvent::phaseGet(Value& result)
    {
//##protect##"instance::GestureEvent::phaseGet()"
        SF_UNUSED1(result);
        static const char* phases[] = { 0, "all", "begin", "end", "update" };
        SF_ASSERT(sizeof(phases)/sizeof(phases[0]) == Phase_Count);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        if (phases[Phase])
            result = vm.GetStringManager().CreateConstString(phases[Phase]);
        else
            result.SetNull();
//##protect##"instance::GestureEvent::phaseGet()"
    }
    void GestureEvent::phaseSet(Value& result, const Value& value)
    {
//##protect##"instance::GestureEvent::phaseSet()"
        SF_UNUSED2(result, value);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        ASString asstr(vm.GetBuiltin(AS3Builtin_empty_));
        value.Convert2String(asstr).DoNotCheck();
        if (asstr == "all")
            Phase = Phase_All;
        else if (asstr == "begin")
            Phase = Phase_Begin;
        else if (asstr == "end")
            Phase = Phase_End;
        else if (asstr == "update")
            Phase = Phase_Update;
        else
            Phase = Phase_Null;
//##protect##"instance::GestureEvent::phaseSet()"
    }
    void GestureEvent::shiftKeyGet(bool& result)
    {
//##protect##"instance::GestureEvent::shiftKeyGet()"
        SF_UNUSED1(result);
        result = ShiftKey;
//##protect##"instance::GestureEvent::shiftKeyGet()"
    }
    void GestureEvent::shiftKeySet(Value& result, bool value)
    {
//##protect##"instance::GestureEvent::shiftKeySet()"
        SF_UNUSED2(result, value);
        ShiftKey = value;
//##protect##"instance::GestureEvent::shiftKeySet()"
    }
    void GestureEvent::stageXGet(Value::Number& result)
    {
//##protect##"instance::GestureEvent::stageXGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageX);
//##protect##"instance::GestureEvent::stageXGet()"
    }
    void GestureEvent::stageYGet(Value::Number& result)
    {
//##protect##"instance::GestureEvent::stageYGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageY);
//##protect##"instance::GestureEvent::stageYGet()"
    }
    void GestureEvent::clone(Value& result)
    {
//##protect##"instance::GestureEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::GestureEvent::clone()"
    }
    void GestureEvent::toString(ASString& result)
    {
//##protect##"instance::GestureEvent::toString()"
        SF_UNUSED1(result);
        //example: [GestureEvent type="gestureZoom" bubbles=true cancelable=false phase=null localX=0 localY=0 
        // stageX=0 stageY=0 ctrlKey=false altKey=false shiftKey=false commandKey=false controlKey=false]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("GestureEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("phase"),
            vm.GetStringManager().CreateConstString("localX"),
            vm.GetStringManager().CreateConstString("localY"),
            vm.GetStringManager().CreateConstString("stageX"),
            vm.GetStringManager().CreateConstString("stageY"),
            vm.GetStringManager().CreateConstString("ctrlKey"),
            vm.GetStringManager().CreateConstString("altKey"),
            vm.GetStringManager().CreateConstString("shiftKey"),
            vm.GetStringManager().CreateConstString("commandKey"),
            vm.GetStringManager().CreateConstString("controlKey")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::GestureEvent::toString()"
    }
    void GestureEvent::updateAfterEvent(Value& result)
    {
//##protect##"instance::GestureEvent::updateAfterEvent()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::GestureEvent::updateAfterEvent()");
//##protect##"instance::GestureEvent::updateAfterEvent()"
    }

//##protect##"instance$methods"
    void GestureEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            Value r;
            phaseSet(r, argv[3]);
        }
        if (argc >= 5)
        {
            Value::Number v;
            argv[4].Convert2Number(v).DoNotCheck();
            LocalX = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 6)
        {
            Value::Number v;
            argv[5].Convert2Number(v).DoNotCheck();
            LocalY = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 7)
        {
            CtrlKey = argv[6].Convert2Boolean();
        }
        if (argc >= 8)
        {
            AltKey = argv[7].Convert2Boolean();
        }
        if (argc >= 9)
        {
            ShiftKey = argv[8].Convert2Boolean();
        }
        if (argc >= 10)
        {
            CommandKey = argv[9].Convert2Boolean();
        }
        if (argc >= 11)
        {
            ControlKey = argv[10].Convert2Boolean();
        }
    }
    AS3::Object* GestureEvent::GetEventClass() const 
    { 
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
		return static_cast<ASVM&>(GetVM()).GestureEventClass; 
#else
		return NULL;
#endif
    }

    SPtr<Instances::Event> GestureEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        GestureEvent* pe = static_cast<GestureEvent*>(p.GetPtr());
        pe->AltKey          = AltKey;
        pe->CtrlKey         = CtrlKey;
        pe->ShiftKey        = ShiftKey;
        pe->CommandKey      = CommandKey;
        pe->ControlKey      = ControlKey;
        pe->LocalX          = LocalX;
        pe->LocalY          = LocalY;
        pe->StageX          = StageX;
        pe->StageY          = StageY;
        pe->Phase           = Phase;
        pe->LocalInitialized= LocalInitialized;
        return p;
    }

    void GestureEvent::InitLocalCoords()
    {
        if (!LocalInitialized)
        {
            if (Target && GetVM().IsOfType(Value(Target), "flash.display.DisplayObject"))
            {
                Instances::DisplayObject* dobj = static_cast<Instances::DisplayObject*>(Target.GetPtr());
                SF_ASSERT(dobj->pDispObj);
                Matrix2F m = dobj->pDispObj->GetWorldMatrix();

                PointF p((float)StageX, (float)StageY);
                p = m.TransformByInverse(p);
                LocalX = p.x;
                LocalY = p.y;
            }
            else
            {
                LocalX = LocalY = 0;
            }
            LocalInitialized = true;
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo GestureEvent::ti[GestureEvent::ThunkInfoNum] = {
        {TFunc_Instances_GestureEvent_altKeyGet::Func, &BooleanCI, "altKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_altKeySet::Func, NULL, "altKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_commandKeyGet::Func, &BooleanCI, "commandKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_commandKeySet::Func, NULL, "commandKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_controlKeyGet::Func, &BooleanCI, "controlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_controlKeySet::Func, NULL, "controlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_ctrlKeyGet::Func, &BooleanCI, "ctrlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_ctrlKeySet::Func, NULL, "ctrlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_localXGet::Func, &NumberCI, "localX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_localXSet::Func, NULL, "localX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_localYGet::Func, &NumberCI, "localY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_localYSet::Func, NULL, "localY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_phaseGet::Func, &ObjectCI, "phase", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_phaseSet::Func, NULL, "phase", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_shiftKeyGet::Func, &BooleanCI, "shiftKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_shiftKeySet::Func, NULL, "shiftKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GestureEvent_stageXGet::Func, &NumberCI, "stageX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_stageYGet::Func, &NumberCI, "stageY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GestureEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_GestureEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_GestureEvent_updateAfterEvent::Func, NULL, "updateAfterEvent", NULL, CT_Method, 0, 0},
    };

    GestureEvent::GestureEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::GestureEvent::GestureEvent()"
//##protect##"InstanceTraits::GestureEvent::GestureEvent()"
        SetMemSize(sizeof(Instances::GestureEvent));

    }

    Pickable<Instances::GestureEvent> GestureEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::GestureEvent>(new(t.Alloc()) Instances::GestureEvent(t));
    }

    void GestureEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    GestureEvent::GestureEvent(ClassTraits::Traits& t)
    : Class(t)
    , GESTURE_TWO_FINGER_TAP("gestureTwoFingerTap")
    {
//##protect##"class_::GestureEvent::GestureEvent()"
//##protect##"class_::GestureEvent::GestureEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo GestureEvent::mi[GestureEvent::MemberInfoNum] = {
        {"GESTURE_TWO_FINGER_TAP", OFFSETOF(Classes::GestureEvent, GESTURE_TWO_FINGER_TAP), SlotInfo::BT_ConstChar, 1},
    };

    GestureEvent::GestureEvent(VM& vm)
    : Traits(vm, GestureEventCI)
    {
//##protect##"ClassTraits::GestureEvent::GestureEvent()"
//##protect##"ClassTraits::GestureEvent::GestureEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::GestureEvent(vm, GestureEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::GestureEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GestureEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GestureEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GestureEventCI = {
    ClassInfo::CompileTime,
    "GestureEvent", "flash.events", &EventCI,
    ClassTraits::GestureEvent::MakeClassTraits,
    0,
    ClassTraits::GestureEvent::MemberInfoNum,
    InstanceTraits::GestureEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::GestureEvent::mi,
    InstanceTraits::GestureEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

