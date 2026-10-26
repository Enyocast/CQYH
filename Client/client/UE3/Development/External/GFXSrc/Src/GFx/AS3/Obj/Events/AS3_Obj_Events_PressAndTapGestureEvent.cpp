//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_PressAndTapGestureEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_PressAndTapGestureEvent.h"
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
typedef ThunkFunc0<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_tapLocalXGet, Value::Number> TFunc_Instances_PressAndTapGestureEvent_tapLocalXGet;
typedef ThunkFunc1<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_tapLocalXSet, Value, Value::Number> TFunc_Instances_PressAndTapGestureEvent_tapLocalXSet;
typedef ThunkFunc0<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_tapLocalYGet, Value::Number> TFunc_Instances_PressAndTapGestureEvent_tapLocalYGet;
typedef ThunkFunc1<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_tapLocalYSet, Value, Value::Number> TFunc_Instances_PressAndTapGestureEvent_tapLocalYSet;
typedef ThunkFunc0<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_tapStageXGet, Value::Number> TFunc_Instances_PressAndTapGestureEvent_tapStageXGet;
typedef ThunkFunc0<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_tapStageYGet, Value::Number> TFunc_Instances_PressAndTapGestureEvent_tapStageYGet;
typedef ThunkFunc0<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_clone, Value> TFunc_Instances_PressAndTapGestureEvent_clone;
typedef ThunkFunc0<Instances::PressAndTapGestureEvent, Instances::PressAndTapGestureEvent::mid_toString, ASString> TFunc_Instances_PressAndTapGestureEvent_toString;

template <> const TFunc_Instances_PressAndTapGestureEvent_tapLocalXGet::TMethod TFunc_Instances_PressAndTapGestureEvent_tapLocalXGet::Method = &Instances::PressAndTapGestureEvent::tapLocalXGet;
template <> const TFunc_Instances_PressAndTapGestureEvent_tapLocalXSet::TMethod TFunc_Instances_PressAndTapGestureEvent_tapLocalXSet::Method = &Instances::PressAndTapGestureEvent::tapLocalXSet;
template <> const TFunc_Instances_PressAndTapGestureEvent_tapLocalYGet::TMethod TFunc_Instances_PressAndTapGestureEvent_tapLocalYGet::Method = &Instances::PressAndTapGestureEvent::tapLocalYGet;
template <> const TFunc_Instances_PressAndTapGestureEvent_tapLocalYSet::TMethod TFunc_Instances_PressAndTapGestureEvent_tapLocalYSet::Method = &Instances::PressAndTapGestureEvent::tapLocalYSet;
template <> const TFunc_Instances_PressAndTapGestureEvent_tapStageXGet::TMethod TFunc_Instances_PressAndTapGestureEvent_tapStageXGet::Method = &Instances::PressAndTapGestureEvent::tapStageXGet;
template <> const TFunc_Instances_PressAndTapGestureEvent_tapStageYGet::TMethod TFunc_Instances_PressAndTapGestureEvent_tapStageYGet::Method = &Instances::PressAndTapGestureEvent::tapStageYGet;
template <> const TFunc_Instances_PressAndTapGestureEvent_clone::TMethod TFunc_Instances_PressAndTapGestureEvent_clone::Method = &Instances::PressAndTapGestureEvent::clone;
template <> const TFunc_Instances_PressAndTapGestureEvent_toString::TMethod TFunc_Instances_PressAndTapGestureEvent_toString::Method = &Instances::PressAndTapGestureEvent::toString;

namespace Instances
{
    PressAndTapGestureEvent::PressAndTapGestureEvent(InstanceTraits::Traits& t)
    : Instances::GestureEvent(t)
//##protect##"instance::PressAndTapGestureEvent::PressAndTapGestureEvent()$data"
//##protect##"instance::PressAndTapGestureEvent::PressAndTapGestureEvent()$data"
    {
//##protect##"instance::PressAndTapGestureEvent::PressAndTapGestureEvent()$code"
        TapLocalX = TapLocalY = 0;
        TapStageX = TapStageY = 0;
        LocalInitialized = false;
		TapStageSet = false;
//##protect##"instance::PressAndTapGestureEvent::PressAndTapGestureEvent()$code"
    }

    void PressAndTapGestureEvent::tapLocalXGet(Value::Number& result)
    {
//##protect##"instance::PressAndTapGestureEvent::tapLocalXGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(TapLocalX);
//##protect##"instance::PressAndTapGestureEvent::tapLocalXGet()"
    }
    void PressAndTapGestureEvent::tapLocalXSet(Value& result, Value::Number value)
    {
//##protect##"instance::PressAndTapGestureEvent::tapLocalXSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        TapLocalX = PixelsToTwips(value);
//##protect##"instance::PressAndTapGestureEvent::tapLocalXSet()"
    }
    void PressAndTapGestureEvent::tapLocalYGet(Value::Number& result)
    {
//##protect##"instance::PressAndTapGestureEvent::tapLocalYGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(TapLocalY);
//##protect##"instance::PressAndTapGestureEvent::tapLocalYGet()"
    }
    void PressAndTapGestureEvent::tapLocalYSet(Value& result, Value::Number value)
    {
//##protect##"instance::PressAndTapGestureEvent::tapLocalYSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        TapLocalY = PixelsToTwips(value);
//##protect##"instance::PressAndTapGestureEvent::tapLocalYSet()"
    }
    void PressAndTapGestureEvent::tapStageXGet(Value::Number& result)
    {
//##protect##"instance::PressAndTapGestureEvent::tapStageXGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(TapStageX);
//##protect##"instance::PressAndTapGestureEvent::tapStageXGet()"
    }
    void PressAndTapGestureEvent::tapStageYGet(Value::Number& result)
    {
//##protect##"instance::PressAndTapGestureEvent::tapStageYGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(TapStageY);
//##protect##"instance::PressAndTapGestureEvent::tapStageYGet()"
    }
    void PressAndTapGestureEvent::clone(Value& result)
    {
//##protect##"instance::PressAndTapGestureEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::PressAndTapGestureEvent::clone()"
    }
    void PressAndTapGestureEvent::toString(ASString& result)
    {
//##protect##"instance::PressAndTapGestureEvent::toString()"
        SF_UNUSED1(result);
        //example: [PressAndTapGestureEvent type="gesturePressAndTap" bubbles=true cancelable=false phase=null 
        // localX=0 localY=0 tapLocalX=0 tapLocalY=0 ctrlKey=false altKey=false shiftKey=false 
        // commandKey=false controlKey=false]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("PressAndTapGestureEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("phase"),
            vm.GetStringManager().CreateConstString("localX"),
            vm.GetStringManager().CreateConstString("localY"),
            vm.GetStringManager().CreateConstString("tapLocalX"),
            vm.GetStringManager().CreateConstString("tapLocalY"),
            vm.GetStringManager().CreateConstString("ctrlKey"),
            vm.GetStringManager().CreateConstString("altKey"),
            vm.GetStringManager().CreateConstString("shiftKey"),
            vm.GetStringManager().CreateConstString("commandKey"),
            vm.GetStringManager().CreateConstString("controlKey")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::PressAndTapGestureEvent::toString()"
    }

//##protect##"instance$methods"
    void PressAndTapGestureEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            Value r;
            phaseSet(r, argv[3]);
        }
        if (argc >= 5)
        {
            Value r;
            localXSet(r, argv[4]);
        }
        if (argc >= 6)
        {
            Value r;
            localYSet(r, argv[5]);
        }
        if (argc >= 7)
        {
            Value r;
            tapLocalXSet(r, argv[6]);
        }
        if (argc >= 8)
        {
            Value r;
            tapLocalYSet(r, argv[7]);
        }
        if (argc >= 9)
        {
            CtrlKey = argv[8].Convert2Boolean();
        }
        if (argc >= 10)
        {
            AltKey = argv[9].Convert2Boolean();
        }
        if (argc >= 11)
        {
            ShiftKey = argv[10].Convert2Boolean();
        }
        if (argc >= 12)
        {
            CommandKey = argv[11].Convert2Boolean();
        }
        if (argc >= 13)
        {
            ControlKey = argv[12].Convert2Boolean();
        }
    }
    AS3::Object* PressAndTapGestureEvent::GetEventClass() const 
    { 
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
        return static_cast<ASVM&>(GetVM()).PressAndTapGestureEventClass; 
#else
        return NULL;
#endif
    }

    SPtr<Instances::Event> PressAndTapGestureEvent::Clone() const
    {
        SPtr<Instances::Event> p = GestureEvent::Clone();
        PressAndTapGestureEvent* pe = static_cast<PressAndTapGestureEvent*>(p.GetPtr());
        pe->TapLocalX       = TapLocalX;
        pe->TapLocalY       = TapLocalY;
        pe->TapStageX       = TapStageX;
        pe->TapStageY       = TapStageY;
        pe->LocalInitialized= LocalInitialized;
		pe->TapStageSet     = TapStageSet;
        return p;
    }

    void PressAndTapGestureEvent::InitLocalCoords()
    {
        if (!LocalInitialized)
        {
            if (TapStageSet && Target && GetVM().IsOfType(Value(Target), "flash.display.DisplayObject"))
            {
                Instances::DisplayObject* dobj = static_cast<Instances::DisplayObject*>(Target.GetPtr());
                SF_ASSERT(dobj->pDispObj);
                Matrix2F m = dobj->pDispObj->GetWorldMatrix();

                PointF p((float)TapStageX, (float)TapStageY);
                p = m.TransformByInverse(p);
                TapLocalX = p.x;
                TapLocalY = p.y;
            }
            else
            {
                TapLocalX = TapLocalY = 0;
            }
            LocalInitialized = true;
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo PressAndTapGestureEvent::ti[PressAndTapGestureEvent::ThunkInfoNum] = {
        {TFunc_Instances_PressAndTapGestureEvent_tapLocalXGet::Func, &NumberCI, "tapLocalX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_PressAndTapGestureEvent_tapLocalXSet::Func, NULL, "tapLocalX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_PressAndTapGestureEvent_tapLocalYGet::Func, &NumberCI, "tapLocalY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_PressAndTapGestureEvent_tapLocalYSet::Func, NULL, "tapLocalY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_PressAndTapGestureEvent_tapStageXGet::Func, &NumberCI, "tapStageX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_PressAndTapGestureEvent_tapStageYGet::Func, &NumberCI, "tapStageY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_PressAndTapGestureEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_PressAndTapGestureEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    PressAndTapGestureEvent::PressAndTapGestureEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::PressAndTapGestureEvent::PressAndTapGestureEvent()"
//##protect##"InstanceTraits::PressAndTapGestureEvent::PressAndTapGestureEvent()"
        SetMemSize(sizeof(Instances::PressAndTapGestureEvent));

    }

    Pickable<Instances::PressAndTapGestureEvent> PressAndTapGestureEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::PressAndTapGestureEvent>(new(t.Alloc()) Instances::PressAndTapGestureEvent(t));
    }

    void PressAndTapGestureEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    PressAndTapGestureEvent::PressAndTapGestureEvent(ClassTraits::Traits& t)
    : Class(t)
    , GESTURE_PRESS_AND_TAP("gesturePressAndTap")
    {
//##protect##"class_::PressAndTapGestureEvent::PressAndTapGestureEvent()"
//##protect##"class_::PressAndTapGestureEvent::PressAndTapGestureEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo PressAndTapGestureEvent::mi[PressAndTapGestureEvent::MemberInfoNum] = {
        {"GESTURE_PRESS_AND_TAP", OFFSETOF(Classes::PressAndTapGestureEvent, GESTURE_PRESS_AND_TAP), SlotInfo::BT_ConstChar, 1},
    };

    PressAndTapGestureEvent::PressAndTapGestureEvent(VM& vm)
    : Traits(vm, PressAndTapGestureEventCI)
    {
//##protect##"ClassTraits::PressAndTapGestureEvent::PressAndTapGestureEvent()"
//##protect##"ClassTraits::PressAndTapGestureEvent::PressAndTapGestureEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::PressAndTapGestureEvent(vm, PressAndTapGestureEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::PressAndTapGestureEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> PressAndTapGestureEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PressAndTapGestureEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo PressAndTapGestureEventCI = {
    ClassInfo::CompileTime,
    "PressAndTapGestureEvent", "flash.events", &GestureEventCI,
    ClassTraits::PressAndTapGestureEvent::MakeClassTraits,
    0,
    ClassTraits::PressAndTapGestureEvent::MemberInfoNum,
    InstanceTraits::PressAndTapGestureEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::PressAndTapGestureEvent::mi,
    InstanceTraits::PressAndTapGestureEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

