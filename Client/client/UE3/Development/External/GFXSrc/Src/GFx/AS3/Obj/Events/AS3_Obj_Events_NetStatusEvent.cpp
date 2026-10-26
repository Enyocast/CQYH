//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NetStatusEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_NetStatusEvent.h"
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
typedef ThunkFunc0<Instances::NetStatusEvent, Instances::NetStatusEvent::mid_infoGet, Value> TFunc_Instances_NetStatusEvent_infoGet;
typedef ThunkFunc1<Instances::NetStatusEvent, Instances::NetStatusEvent::mid_infoSet, Value, const Value&> TFunc_Instances_NetStatusEvent_infoSet;
typedef ThunkFunc0<Instances::NetStatusEvent, Instances::NetStatusEvent::mid_clone, Value> TFunc_Instances_NetStatusEvent_clone;
typedef ThunkFunc0<Instances::NetStatusEvent, Instances::NetStatusEvent::mid_toString, ASString> TFunc_Instances_NetStatusEvent_toString;

template <> const TFunc_Instances_NetStatusEvent_infoGet::TMethod TFunc_Instances_NetStatusEvent_infoGet::Method = &Instances::NetStatusEvent::infoGet;
template <> const TFunc_Instances_NetStatusEvent_infoSet::TMethod TFunc_Instances_NetStatusEvent_infoSet::Method = &Instances::NetStatusEvent::infoSet;
template <> const TFunc_Instances_NetStatusEvent_clone::TMethod TFunc_Instances_NetStatusEvent_clone::Method = &Instances::NetStatusEvent::clone;
template <> const TFunc_Instances_NetStatusEvent_toString::TMethod TFunc_Instances_NetStatusEvent_toString::Method = &Instances::NetStatusEvent::toString;

namespace Instances
{
    NetStatusEvent::NetStatusEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::NetStatusEvent::NetStatusEvent()$data"
    , Code( GetVM().GetStringManager().CreateEmptyString())
    , Level(GetVM().GetStringManager().CreateEmptyString())
//##protect##"instance::NetStatusEvent::NetStatusEvent()$data"
    {
//##protect##"instance::NetStatusEvent::NetStatusEvent()$code"
//##protect##"instance::NetStatusEvent::NetStatusEvent()$code"
    }

    void NetStatusEvent::infoGet(Value& result)
    {
//##protect##"instance::NetStatusEvent::infoGet()"
        SPtr<Instances::Object> pobj = GetVM().MakeObject();
        StringManager& sm = GetVM().GetStringManager();
        pobj->AddDynamicSlotValuePair(sm.CreateString("code"),  Code);
        pobj->AddDynamicSlotValuePair(sm.CreateString("level"), Level);
        result = pobj;
//##protect##"instance::NetStatusEvent::infoGet()"
    }
    void NetStatusEvent::infoSet(Value& result, const Value& value)
    {
//##protect##"instance::NetStatusEvent::infoSet()"
        SF_UNUSED(result);
        Instances::Object* pobj = static_cast<Instances::Object*>(value.GetObject());
        StringManager& sm = GetVM().GetStringManager();

        Multiname mnCode( GetVM().GetPublicNamespace(), sm.CreateString("code"));
        Multiname mnLevel(GetVM().GetPublicNamespace(), sm.CreateString("level"));
        Value prop;
        if (pobj->GetProperty(mnCode, prop))
            prop.Convert2String(Code);
        if (pobj->GetProperty(mnLevel, prop))
            prop.Convert2String(Level);
//##protect##"instance::NetStatusEvent::infoSet()"
    }
    void NetStatusEvent::clone(Value& result)
    {
//##protect##"instance::NetStatusEvent::clone()"
        SF_UNUSED(result);
        result = Clone().GetPtr();
//##protect##"instance::NetStatusEvent::clone()"
    }
    void NetStatusEvent::toString(ASString& result)
    {
//##protect##"instance::NetStatusEvent::toString()"
        StringManager& sm = GetVM().GetStringManager();
        Value params[] = {
            sm.CreateConstString(GetEventName()),
            sm.CreateConstString("type"),
            sm.CreateConstString("bubbles"),
            sm.CreateConstString("cancelable"),
            sm.CreateConstString("info"),
            sm.CreateConstString("target")
        };
        Value v;
        formatToString(v, sizeof(params)/sizeof(params[0]), params);
        v.Convert2String(result).DoNotCheck();
//##protect##"instance::NetStatusEvent::toString()"
    }

//##protect##"instance$methods"
    void NetStatusEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
            argv[3].Convert2String(Code).DoNotCheck();
        if (argc >= 5)
            argv[4].Convert2String(Level).DoNotCheck();
    }

    SPtr<Instances::Event> NetStatusEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        NetStatusEvent* pe = static_cast<NetStatusEvent*>(p.GetPtr());
        pe->Code  = Code;
        pe->Level = Level;
        return p;
    }
    const char* NetStatusEvent::GetEventName() const
    {
        return "NetStatusEvent";
    }
    AS3::Object* NetStatusEvent::GetEventClass() const
    { 
        Class* result = GetVM().GetClass("flash.events.NetStatusEvent");
        SF_ASSERT(result);
        return result;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo NetStatusEvent::ti[NetStatusEvent::ThunkInfoNum] = {
        {TFunc_Instances_NetStatusEvent_infoGet::Func, &ObjectCI, "info", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStatusEvent_infoSet::Func, NULL, "info", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStatusEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_NetStatusEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    NetStatusEvent::NetStatusEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::NetStatusEvent::NetStatusEvent()"
//##protect##"InstanceTraits::NetStatusEvent::NetStatusEvent()"
        SetMemSize(sizeof(Instances::NetStatusEvent));

    }

    Pickable<Instances::NetStatusEvent> NetStatusEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::NetStatusEvent>(new(t.Alloc()) Instances::NetStatusEvent(t));
    }

    void NetStatusEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    NetStatusEvent::NetStatusEvent(ClassTraits::Traits& t)
    : Class(t)
    , NET_STATUS("netStatus")
    {
//##protect##"class_::NetStatusEvent::NetStatusEvent()"
//##protect##"class_::NetStatusEvent::NetStatusEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NetStatusEvent::mi[NetStatusEvent::MemberInfoNum] = {
        {"NET_STATUS", OFFSETOF(Classes::NetStatusEvent, NET_STATUS), SlotInfo::BT_ConstChar, 1},
    };

    NetStatusEvent::NetStatusEvent(VM& vm)
    : Traits(vm, NetStatusEventCI)
    {
//##protect##"ClassTraits::NetStatusEvent::NetStatusEvent()"
//##protect##"ClassTraits::NetStatusEvent::NetStatusEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::NetStatusEvent(vm, NetStatusEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NetStatusEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NetStatusEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NetStatusEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NetStatusEventCI = {
    ClassInfo::CompileTime,
    "NetStatusEvent", "flash.events", &EventCI,
    ClassTraits::NetStatusEvent::MakeClassTraits,
    0,
    ClassTraits::NetStatusEvent::MemberInfoNum,
    InstanceTraits::NetStatusEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::NetStatusEvent::mi,
    InstanceTraits::NetStatusEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

