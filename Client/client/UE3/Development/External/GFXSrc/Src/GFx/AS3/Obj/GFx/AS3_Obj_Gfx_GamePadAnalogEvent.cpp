//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_GamePadAnalogEvent.cpp
Content     :   
Created     :   Jun, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_GamePadAnalogEvent.h"
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
typedef ThunkFunc0<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_codeGet, UInt32> TFunc_Instances_GamePadAnalogEvent_codeGet;
typedef ThunkFunc1<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_codeSet, Value, UInt32> TFunc_Instances_GamePadAnalogEvent_codeSet;
typedef ThunkFunc0<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_controllerIdxGet, UInt32> TFunc_Instances_GamePadAnalogEvent_controllerIdxGet;
typedef ThunkFunc1<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_controllerIdxSet, Value, UInt32> TFunc_Instances_GamePadAnalogEvent_controllerIdxSet;
typedef ThunkFunc0<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_xvalueGet, Value::Number> TFunc_Instances_GamePadAnalogEvent_xvalueGet;
typedef ThunkFunc1<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_xvalueSet, Value, Value::Number> TFunc_Instances_GamePadAnalogEvent_xvalueSet;
typedef ThunkFunc0<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_yvalueGet, Value::Number> TFunc_Instances_GamePadAnalogEvent_yvalueGet;
typedef ThunkFunc1<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_yvalueSet, Value, Value::Number> TFunc_Instances_GamePadAnalogEvent_yvalueSet;
typedef ThunkFunc0<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_clone, Value> TFunc_Instances_GamePadAnalogEvent_clone;
typedef ThunkFunc0<Instances::GamePadAnalogEvent, Instances::GamePadAnalogEvent::mid_toString, ASString> TFunc_Instances_GamePadAnalogEvent_toString;

template <> const TFunc_Instances_GamePadAnalogEvent_codeGet::TMethod TFunc_Instances_GamePadAnalogEvent_codeGet::Method = &Instances::GamePadAnalogEvent::codeGet;
template <> const TFunc_Instances_GamePadAnalogEvent_codeSet::TMethod TFunc_Instances_GamePadAnalogEvent_codeSet::Method = &Instances::GamePadAnalogEvent::codeSet;
template <> const TFunc_Instances_GamePadAnalogEvent_controllerIdxGet::TMethod TFunc_Instances_GamePadAnalogEvent_controllerIdxGet::Method = &Instances::GamePadAnalogEvent::controllerIdxGet;
template <> const TFunc_Instances_GamePadAnalogEvent_controllerIdxSet::TMethod TFunc_Instances_GamePadAnalogEvent_controllerIdxSet::Method = &Instances::GamePadAnalogEvent::controllerIdxSet;
template <> const TFunc_Instances_GamePadAnalogEvent_xvalueGet::TMethod TFunc_Instances_GamePadAnalogEvent_xvalueGet::Method = &Instances::GamePadAnalogEvent::xvalueGet;
template <> const TFunc_Instances_GamePadAnalogEvent_xvalueSet::TMethod TFunc_Instances_GamePadAnalogEvent_xvalueSet::Method = &Instances::GamePadAnalogEvent::xvalueSet;
template <> const TFunc_Instances_GamePadAnalogEvent_yvalueGet::TMethod TFunc_Instances_GamePadAnalogEvent_yvalueGet::Method = &Instances::GamePadAnalogEvent::yvalueGet;
template <> const TFunc_Instances_GamePadAnalogEvent_yvalueSet::TMethod TFunc_Instances_GamePadAnalogEvent_yvalueSet::Method = &Instances::GamePadAnalogEvent::yvalueSet;
template <> const TFunc_Instances_GamePadAnalogEvent_clone::TMethod TFunc_Instances_GamePadAnalogEvent_clone::Method = &Instances::GamePadAnalogEvent::clone;
template <> const TFunc_Instances_GamePadAnalogEvent_toString::TMethod TFunc_Instances_GamePadAnalogEvent_toString::Method = &Instances::GamePadAnalogEvent::toString;

namespace Instances
{
    GamePadAnalogEvent::GamePadAnalogEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::GamePadAnalogEvent::GamePadAnalogEvent()$data"
//##protect##"instance::GamePadAnalogEvent::GamePadAnalogEvent()$data"
    {
//##protect##"instance::GamePadAnalogEvent::GamePadAnalogEvent()$code"
//##protect##"instance::GamePadAnalogEvent::GamePadAnalogEvent()$code"
    }

    void GamePadAnalogEvent::codeGet(UInt32& result)
    {
//##protect##"instance::GamePadAnalogEvent::codeGet()"

        result = Code;

//##protect##"instance::GamePadAnalogEvent::codeGet()"
    }
    void GamePadAnalogEvent::codeSet(Value& result, UInt32 value)
    {
//##protect##"instance::GamePadAnalogEvent::codeSet()"

        SF_UNUSED1(result);
        Code = value;

//##protect##"instance::GamePadAnalogEvent::codeSet()"
    }
    void GamePadAnalogEvent::controllerIdxGet(UInt32& result)
    {
//##protect##"instance::GamePadAnalogEvent::controllerIdxGet()"
        
        result = ControllerIdx;

//##protect##"instance::GamePadAnalogEvent::controllerIdxGet()"
    }
    void GamePadAnalogEvent::controllerIdxSet(Value& result, UInt32 value)
    {
//##protect##"instance::GamePadAnalogEvent::controllerIdxSet()"
        
        SF_UNUSED1(result);
        ControllerIdx = value;

//##protect##"instance::GamePadAnalogEvent::controllerIdxSet()"
    }
    void GamePadAnalogEvent::xvalueGet(Value::Number& result)
    {
//##protect##"instance::GamePadAnalogEvent::xvalueGet()"
        
        result = XValue;

//##protect##"instance::GamePadAnalogEvent::xvalueGet()"
    }
    void GamePadAnalogEvent::xvalueSet(Value& result, Value::Number value)
    {
//##protect##"instance::GamePadAnalogEvent::xvalueSet()"
        
        SF_UNUSED1(result);
        XValue = value;

//##protect##"instance::GamePadAnalogEvent::xvalueSet()"
    }
    void GamePadAnalogEvent::yvalueGet(Value::Number& result)
    {
//##protect##"instance::GamePadAnalogEvent::yvalueGet()"
        
        result = YValue;

//##protect##"instance::GamePadAnalogEvent::yvalueGet()"
    }
    void GamePadAnalogEvent::yvalueSet(Value& result, Value::Number value)
    {
//##protect##"instance::GamePadAnalogEvent::yvalueSet()"
        
        SF_UNUSED1(result);
        YValue = value;

//##protect##"instance::GamePadAnalogEvent::yvalueSet()"
    }
    void GamePadAnalogEvent::clone(Value& result)
    {
//##protect##"instance::GamePadAnalogEvent::clone()"

        SF_UNUSED1(result);
        result = Clone().GetPtr();

//##protect##"instance::GamePadAnalogEvent::clone()"
    }
    void GamePadAnalogEvent::toString(ASString& result)
    {
//##protect##"instance::GamePadAnalogEvent::toString()"

        SF_UNUSED1(result);
        //example: [GamePadAnalogEvent type="gamePadAnalogChange" bubbles=true cancelable=false eventPhase=2 
        // code=27 controllerIdx=0 xvalue=0.3 yvalue=-0.2]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("GamePadAnalogEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("code"),
            vm.GetStringManager().CreateConstString("controllerIdx"),
            vm.GetStringManager().CreateConstString("xvalue"),
            vm.GetStringManager().CreateConstString("yvalue")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();

//##protect##"instance::GamePadAnalogEvent::toString()"
    }

//##protect##"instance$methods"
    void GamePadAnalogEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            UInt32 v;
            argv[3].Convert2UInt32(v).DoNotCheck();
            Code = v;
        }
        if (argc >= 5)
        {
            UInt32 v;
            argv[4].Convert2UInt32(v).DoNotCheck();
            ControllerIdx = v;
        }
        if (argc >= 6)
        {
            Value::Number v;
            argv[5].Convert2Number(v).DoNotCheck();
            XValue = v;
        }
        if (argc >= 7)
        {
            Value::Number v;
            argv[6].Convert2Number(v).DoNotCheck();
            YValue = v;
        }
    }
    AS3::Object* GamePadAnalogEvent::GetEventClass() const
    { 
#if defined(GFX_ENABLE_ANALOG_GAMEPAD)
        return static_cast<ASVM&>(GetVM()).GamePadAnalogEventClass; 
#else
        return NULL;
#endif
    }

    SPtr<Instances::Event> GamePadAnalogEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        GamePadAnalogEvent* pe = static_cast<GamePadAnalogEvent*>(p.GetPtr());
        pe->ControllerIdx   = ControllerIdx;
        pe->XValue          = XValue;
        pe->YValue          = YValue;
        return p;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo GamePadAnalogEvent::ti[GamePadAnalogEvent::ThunkInfoNum] = {
        {TFunc_Instances_GamePadAnalogEvent_codeGet::Func, &uintCI, "code", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GamePadAnalogEvent_codeSet::Func, NULL, "code", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GamePadAnalogEvent_controllerIdxGet::Func, &uintCI, "controllerIdx", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GamePadAnalogEvent_controllerIdxSet::Func, NULL, "controllerIdx", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GamePadAnalogEvent_xvalueGet::Func, &NumberCI, "xvalue", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GamePadAnalogEvent_xvalueSet::Func, NULL, "xvalue", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GamePadAnalogEvent_yvalueGet::Func, &NumberCI, "yvalue", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GamePadAnalogEvent_yvalueSet::Func, NULL, "yvalue", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GamePadAnalogEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_GamePadAnalogEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    GamePadAnalogEvent::GamePadAnalogEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::GamePadAnalogEvent::GamePadAnalogEvent()"
//##protect##"InstanceTraits::GamePadAnalogEvent::GamePadAnalogEvent()"
        SetMemSize(sizeof(Instances::GamePadAnalogEvent));

    }

    Pickable<Instances::GamePadAnalogEvent> GamePadAnalogEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::GamePadAnalogEvent>(new(t.Alloc()) Instances::GamePadAnalogEvent(t));
    }

    void GamePadAnalogEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    GamePadAnalogEvent::GamePadAnalogEvent(ClassTraits::Traits& t)
    : Class(t)
    , CHANGE("gamePadAnalogChange")
    {
//##protect##"class_::GamePadAnalogEvent::GamePadAnalogEvent()"
//##protect##"class_::GamePadAnalogEvent::GamePadAnalogEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo GamePadAnalogEvent::mi[GamePadAnalogEvent::MemberInfoNum] = {
        {"CHANGE", OFFSETOF(Classes::GamePadAnalogEvent, CHANGE), SlotInfo::BT_ConstChar, 1},
    };

    GamePadAnalogEvent::GamePadAnalogEvent(VM& vm)
    : Traits(vm, GamePadAnalogEventCI)
    {
//##protect##"ClassTraits::GamePadAnalogEvent::GamePadAnalogEvent()"
//##protect##"ClassTraits::GamePadAnalogEvent::GamePadAnalogEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::GamePadAnalogEvent(vm, GamePadAnalogEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::GamePadAnalogEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GamePadAnalogEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GamePadAnalogEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GamePadAnalogEventCI = {
    ClassInfo::CompileTime,
    "GamePadAnalogEvent", "scaleform.gfx", &EventCI,
    ClassTraits::GamePadAnalogEvent::MakeClassTraits,
    0,
    ClassTraits::GamePadAnalogEvent::MemberInfoNum,
    InstanceTraits::GamePadAnalogEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::GamePadAnalogEvent::mi,
    InstanceTraits::GamePadAnalogEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

