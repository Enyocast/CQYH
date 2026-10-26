//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_Event.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_Event.h"
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
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_bubblesGet, bool> TFunc_Instances_Event_bubblesGet;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_cancelableGet, bool> TFunc_Instances_Event_cancelableGet;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_currentTargetGet, Value> TFunc_Instances_Event_currentTargetGet;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_eventPhaseGet, UInt32> TFunc_Instances_Event_eventPhaseGet;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_targetGet, Value> TFunc_Instances_Event_targetGet;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_typeGet, ASString> TFunc_Instances_Event_typeGet;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_clone, Value> TFunc_Instances_Event_clone;
typedef ThunkFunc2<Instances::Event, Instances::Event::mid_formatToString, Value, unsigned, const Value*> TFunc_Instances_Event_formatToString;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_isDefaultPrevented, bool> TFunc_Instances_Event_isDefaultPrevented;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_preventDefault, Value> TFunc_Instances_Event_preventDefault;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_stopImmediatePropagation, Value> TFunc_Instances_Event_stopImmediatePropagation;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_stopPropagation, Value> TFunc_Instances_Event_stopPropagation;
typedef ThunkFunc0<Instances::Event, Instances::Event::mid_toString, ASString> TFunc_Instances_Event_toString;

template <> const TFunc_Instances_Event_bubblesGet::TMethod TFunc_Instances_Event_bubblesGet::Method = &Instances::Event::bubblesGet;
template <> const TFunc_Instances_Event_cancelableGet::TMethod TFunc_Instances_Event_cancelableGet::Method = &Instances::Event::cancelableGet;
template <> const TFunc_Instances_Event_currentTargetGet::TMethod TFunc_Instances_Event_currentTargetGet::Method = &Instances::Event::currentTargetGet;
template <> const TFunc_Instances_Event_eventPhaseGet::TMethod TFunc_Instances_Event_eventPhaseGet::Method = &Instances::Event::eventPhaseGet;
template <> const TFunc_Instances_Event_targetGet::TMethod TFunc_Instances_Event_targetGet::Method = &Instances::Event::targetGet;
template <> const TFunc_Instances_Event_typeGet::TMethod TFunc_Instances_Event_typeGet::Method = &Instances::Event::typeGet;
template <> const TFunc_Instances_Event_clone::TMethod TFunc_Instances_Event_clone::Method = &Instances::Event::clone;
template <> const TFunc_Instances_Event_formatToString::TMethod TFunc_Instances_Event_formatToString::Method = &Instances::Event::formatToString;
template <> const TFunc_Instances_Event_isDefaultPrevented::TMethod TFunc_Instances_Event_isDefaultPrevented::Method = &Instances::Event::isDefaultPrevented;
template <> const TFunc_Instances_Event_preventDefault::TMethod TFunc_Instances_Event_preventDefault::Method = &Instances::Event::preventDefault;
template <> const TFunc_Instances_Event_stopImmediatePropagation::TMethod TFunc_Instances_Event_stopImmediatePropagation::Method = &Instances::Event::stopImmediatePropagation;
template <> const TFunc_Instances_Event_stopPropagation::TMethod TFunc_Instances_Event_stopPropagation::Method = &Instances::Event::stopPropagation;
template <> const TFunc_Instances_Event_toString::TMethod TFunc_Instances_Event_toString::Method = &Instances::Event::toString;

namespace Instances
{
    Event::Event(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::Event::Event()$data"
    , Type(GetVM().GetStringManager().CreateEmptyString())
    , Phase(Phase_Target)
    , Bubbles(false)
    , Cancelable(false)
    , DefaultPrevented(false)
    , PropagationStopped(false)
    , ImmPropagationStopped(false)
//##protect##"instance::Event::Event()$data"
    {
//##protect##"instance::Event::Event()$code"
//##protect##"instance::Event::Event()$code"
    }

    void Event::bubblesGet(bool& result)
    {
//##protect##"instance::Event::bubblesGet()"
        result = Bubbles;
//##protect##"instance::Event::bubblesGet()"
    }
    void Event::cancelableGet(bool& result)
    {
//##protect##"instance::Event::cancelableGet()"
        result = Cancelable;
//##protect##"instance::Event::cancelableGet()"
    }
    void Event::currentTargetGet(Value& result)
    {
//##protect##"instance::Event::currentTargetGet()"
        result = CurrentTarget.GetPtr();
//##protect##"instance::Event::currentTargetGet()"
    }
    void Event::eventPhaseGet(UInt32& result)
    {
//##protect##"instance::Event::eventPhaseGet()"
        result = Phase;
//##protect##"instance::Event::eventPhaseGet()"
    }
    void Event::targetGet(Value& result)
    {
//##protect##"instance::Event::targetGet()"
        result = Target.GetPtr();
//##protect##"instance::Event::targetGet()"
    }
    void Event::typeGet(ASString& result)
    {
//##protect##"instance::Event::typeGet()"
        result = Type;
//##protect##"instance::Event::typeGet()"
    }
    void Event::clone(Value& result)
    {
//##protect##"instance::Event::clone()"
        SF_UNUSED1(result);
        SPtr<Event> e = Clone();
        result = e;
//##protect##"instance::Event::clone()"
    }
    void Event::formatToString(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Event::formatToString()"
        SF_UNUSED3(result, argc, argv);
        if (argc < 1)
        {
            GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM() SF_DEBUG_ARG("Event::formatToString") SF_DEBUG_ARG(1) SF_DEBUG_ARG(1) SF_DEBUG_ARG(argc)));
            return;
        }
        StringBuffer sb(GetVM().GetMemoryHeap());
        char str[1024];

        ASVM& vm = static_cast<ASVM&>(GetVM());
        ASString asstr(vm.GetBuiltin(AS3Builtin_empty_));
        argv[0].Convert2String(asstr).DoNotCheck();

        SFsprintf(str, sizeof(str), "[%s", asstr.ToCStr());
        sb.AppendString(str);

        for (unsigned i = 1; i < argc; ++i)
        {
            argv[i].Convert2String(asstr).DoNotCheck();
            AS3::Multiname mn(vm.GetPublicNamespace(), asstr);
            AS3::PropRef   prop;
            
            FindProperty(prop, mn);
            if (!prop)
            {
                SFsprintf(str, sizeof(str), "Property %s not found on flash.events.Event and there is no default value.",
                    asstr.ToCStr());

                vm.ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, vm SF_DEBUG_ARG(str)));
                return;
            }

            AS3::Value asval;
            if (!prop.GetSlotValueUnsafe(vm, asval))
            {
                return; //?
            }
            
            SFsprintf(str, sizeof(str), " %s=", asstr.ToCStr());
            sb.AppendString(str);

            bool quotes = asval.IsString();

            asval.Convert2String(asstr).DoNotCheck();
            if (quotes)
                sb.AppendChar('"');
            SFsprintf(str, sizeof(str), "%s", asstr.ToCStr());
            sb.AppendString(str);
            if (quotes)
                sb.AppendChar('"');
        }

        sb.AppendString("]", 2); // incl trailing zero
        result = vm.GetStringManager().CreateString(sb.ToCStr());
//##protect##"instance::Event::formatToString()"
    }
    void Event::isDefaultPrevented(bool& result)
    {
//##protect##"instance::Event::isDefaultPrevented()"
        SF_UNUSED1(result);
        result = DefaultPrevented;
//##protect##"instance::Event::isDefaultPrevented()"
    }
    void Event::preventDefault(Value& result)
    {
//##protect##"instance::Event::preventDefault()"
        SF_UNUSED1(result);
        if (Cancelable)
            DefaultPrevented = true;
//##protect##"instance::Event::preventDefault()"
    }
    void Event::stopImmediatePropagation(Value& result)
    {
//##protect##"instance::Event::stopImmediatePropagation()"
        SF_UNUSED1(result);
        ImmPropagationStopped = true;
//##protect##"instance::Event::stopImmediatePropagation()"
    }
    void Event::stopPropagation(Value& result)
    {
//##protect##"instance::Event::stopPropagation()"
        SF_UNUSED1(result);
        PropagationStopped = true;
//##protect##"instance::Event::stopPropagation()"
    }
    void Event::toString(ASString& result)
    {
//##protect##"instance::Event::toString()"
        SF_UNUSED1(result);
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString(GetEventName()),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::Event::toString()"
    }

//##protect##"instance$methods"
    // AS3 ctor of Event class
    void Event::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc < 1)
        {
            GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM() SF_DEBUG_ARG("Event::AS3Constructor") SF_DEBUG_ARG(1) SF_DEBUG_ARG(1) SF_DEBUG_ARG(argc)));
            return;
        }
        argv[0].Convert2String(Type).DoNotCheck();
        if (argc >= 2)
        {
            Bubbles = argv[1].Convert2Boolean();
        }
        if (argc >= 3)
        {
            Cancelable = argv[2].Convert2Boolean();
        }
    }

    SPtr<Instances::Event> Event::Clone() const
    {
        SPtr<Instances::Event> e;
        Value params[] = { Value(Type), Value(Bubbles), Value(Cancelable) };
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        asvm.ConstructInstance(e, GetEventClass(), 3, params);

        e->CurrentTarget            = CurrentTarget;
        e->Target                   = Target;
        e->DefaultPrevented         = DefaultPrevented;
        e->PropagationStopped       = PropagationStopped;
        e->ImmPropagationStopped    = ImmPropagationStopped;
        return e;
    }

    void Event::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC<Object, Mem_Stat>(prcc, CurrentTarget, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC<Object, Mem_Stat>(prcc, Target, op SF_DEBUG_ARG(*this));
    }

    AS3::Object* Event::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).EventClass; 
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Event::ti[Event::ThunkInfoNum] = {
        {TFunc_Instances_Event_bubblesGet::Func, &BooleanCI, "bubbles", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Event_cancelableGet::Func, &BooleanCI, "cancelable", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Event_currentTargetGet::Func, &ObjectCI, "currentTarget", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Event_eventPhaseGet::Func, &uintCI, "eventPhase", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Event_targetGet::Func, &ObjectCI, "target", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Event_typeGet::Func, &StringCI, "type", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Event_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Event_formatToString::Func, &StringCI, "formatToString", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_Event_isDefaultPrevented::Func, &BooleanCI, "isDefaultPrevented", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Event_preventDefault::Func, NULL, "preventDefault", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Event_stopImmediatePropagation::Func, NULL, "stopImmediatePropagation", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Event_stopPropagation::Func, NULL, "stopPropagation", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Event_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    Event::Event(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Event::Event()"
//##protect##"InstanceTraits::Event::Event()"
        SetMemSize(sizeof(Instances::Event));

    }

    Pickable<Instances::Event> Event::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Event>(new(t.Alloc()) Instances::Event(t));
    }

    void Event::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    Event::Event(ClassTraits::Traits& t)
    : Class(t)
    , ACTIVATE("activate")
    , ADDED("added")
    , ADDED_TO_STAGE("addedToStage")
    , CANCEL("cancel")
    , CHANGE("change")
    , CLOSE("close")
    , CLOSING("closing")
    , COMPLETE("complete")
    , CONNECT("connect")
    , DEACTIVATE("deactivate")
    , DISPLAYING("displaying")
    , ENTER_FRAME("enterFrame")
    , EXITING("exiting")
    , EXIT_FRAME("exitFrame")
    , FRAME_CONSTRUCTED("frameConstructed")
    , FULLSCREEN("fullScreen")
    , HTML_BOUNDS_CHANGE("htmlBoundsChange")
    , HTML_DOM_INITIALIZE("htmlDOMInitialize")
    , HTML_RENDER("htmlRender")
    , ID3("id3")
    , INIT("init")
    , LOCATION_CHANGE("locationChange")
    , MOUSE_LEAVE("mouseLeave")
    , NETWORK_CHANGE("networkChange")
    , OPEN("open")
    , REMOVED("removed")
    , REMOVED_FROM_STAGE("removedFromStage")
    , RENDER("render")
    , RESIZE("resize")
    , SCROLL("scroll")
    , SELECT("select")
    , SOUND_COMPLETE("soundComplete")
    , TAB_CHILDREN_CHANGE("tabChildrenChange")
    , TAB_ENABLED_CHANGE("tabEnabledChange")
    , TAB_INDEX_CHANGE("tabIndexChange")
    , UNLOAD("unload")
    , USER_IDLE("userIdle")
    , USER_PRESENT("userPresent")
    {
//##protect##"class_::Event::Event()"
//##protect##"class_::Event::Event()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo Event::mi[Event::MemberInfoNum] = {
        {"ACTIVATE", OFFSETOF(Classes::Event, ACTIVATE), SlotInfo::BT_ConstChar, 1},
        {"ADDED", OFFSETOF(Classes::Event, ADDED), SlotInfo::BT_ConstChar, 1},
        {"ADDED_TO_STAGE", OFFSETOF(Classes::Event, ADDED_TO_STAGE), SlotInfo::BT_ConstChar, 1},
        {"CANCEL", OFFSETOF(Classes::Event, CANCEL), SlotInfo::BT_ConstChar, 1},
        {"CHANGE", OFFSETOF(Classes::Event, CHANGE), SlotInfo::BT_ConstChar, 1},
        {"CLOSE", OFFSETOF(Classes::Event, CLOSE), SlotInfo::BT_ConstChar, 1},
        {"CLOSING", OFFSETOF(Classes::Event, CLOSING), SlotInfo::BT_ConstChar, 1},
        {"COMPLETE", OFFSETOF(Classes::Event, COMPLETE), SlotInfo::BT_ConstChar, 1},
        {"CONNECT", OFFSETOF(Classes::Event, CONNECT), SlotInfo::BT_ConstChar, 1},
        {"DEACTIVATE", OFFSETOF(Classes::Event, DEACTIVATE), SlotInfo::BT_ConstChar, 1},
        {"DISPLAYING", OFFSETOF(Classes::Event, DISPLAYING), SlotInfo::BT_ConstChar, 1},
        {"ENTER_FRAME", OFFSETOF(Classes::Event, ENTER_FRAME), SlotInfo::BT_ConstChar, 1},
        {"EXITING", OFFSETOF(Classes::Event, EXITING), SlotInfo::BT_ConstChar, 1},
        {"EXIT_FRAME", OFFSETOF(Classes::Event, EXIT_FRAME), SlotInfo::BT_ConstChar, 1},
        {"FRAME_CONSTRUCTED", OFFSETOF(Classes::Event, FRAME_CONSTRUCTED), SlotInfo::BT_ConstChar, 1},
        {"FULLSCREEN", OFFSETOF(Classes::Event, FULLSCREEN), SlotInfo::BT_ConstChar, 1},
        {"HTML_BOUNDS_CHANGE", OFFSETOF(Classes::Event, HTML_BOUNDS_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"HTML_DOM_INITIALIZE", OFFSETOF(Classes::Event, HTML_DOM_INITIALIZE), SlotInfo::BT_ConstChar, 1},
        {"HTML_RENDER", OFFSETOF(Classes::Event, HTML_RENDER), SlotInfo::BT_ConstChar, 1},
        {"ID3", OFFSETOF(Classes::Event, ID3), SlotInfo::BT_ConstChar, 1},
        {"INIT", OFFSETOF(Classes::Event, INIT), SlotInfo::BT_ConstChar, 1},
        {"LOCATION_CHANGE", OFFSETOF(Classes::Event, LOCATION_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_LEAVE", OFFSETOF(Classes::Event, MOUSE_LEAVE), SlotInfo::BT_ConstChar, 1},
        {"NETWORK_CHANGE", OFFSETOF(Classes::Event, NETWORK_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"OPEN", OFFSETOF(Classes::Event, OPEN), SlotInfo::BT_ConstChar, 1},
        {"REMOVED", OFFSETOF(Classes::Event, REMOVED), SlotInfo::BT_ConstChar, 1},
        {"REMOVED_FROM_STAGE", OFFSETOF(Classes::Event, REMOVED_FROM_STAGE), SlotInfo::BT_ConstChar, 1},
        {"RENDER", OFFSETOF(Classes::Event, RENDER), SlotInfo::BT_ConstChar, 1},
        {"RESIZE", OFFSETOF(Classes::Event, RESIZE), SlotInfo::BT_ConstChar, 1},
        {"SCROLL", OFFSETOF(Classes::Event, SCROLL), SlotInfo::BT_ConstChar, 1},
        {"SELECT", OFFSETOF(Classes::Event, SELECT), SlotInfo::BT_ConstChar, 1},
        {"SOUND_COMPLETE", OFFSETOF(Classes::Event, SOUND_COMPLETE), SlotInfo::BT_ConstChar, 1},
        {"TAB_CHILDREN_CHANGE", OFFSETOF(Classes::Event, TAB_CHILDREN_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"TAB_ENABLED_CHANGE", OFFSETOF(Classes::Event, TAB_ENABLED_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"TAB_INDEX_CHANGE", OFFSETOF(Classes::Event, TAB_INDEX_CHANGE), SlotInfo::BT_ConstChar, 1},
        {"UNLOAD", OFFSETOF(Classes::Event, UNLOAD), SlotInfo::BT_ConstChar, 1},
        {"USER_IDLE", OFFSETOF(Classes::Event, USER_IDLE), SlotInfo::BT_ConstChar, 1},
        {"USER_PRESENT", OFFSETOF(Classes::Event, USER_PRESENT), SlotInfo::BT_ConstChar, 1},
    };

    Event::Event(VM& vm)
    : Traits(vm, EventCI)
    {
//##protect##"ClassTraits::Event::Event()"
//##protect##"ClassTraits::Event::Event()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, EventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Event(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Event::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Event(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo EventCI = {
    ClassInfo::CompileTime,
    "Event", "flash.events", &ObjectCI,
    ClassTraits::Event::MakeClassTraits,
    0,
    ClassTraits::Event::MemberInfoNum,
    InstanceTraits::Event::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::Event::mi,
    InstanceTraits::Event::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

