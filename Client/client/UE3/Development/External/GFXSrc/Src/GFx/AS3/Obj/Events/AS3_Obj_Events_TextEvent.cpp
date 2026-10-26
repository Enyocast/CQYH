//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TextEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_TextEvent.h"
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
typedef ThunkFunc0<Instances::TextEvent, Instances::TextEvent::mid_textGet, ASString> TFunc_Instances_TextEvent_textGet;
typedef ThunkFunc1<Instances::TextEvent, Instances::TextEvent::mid_textSet, Value, const ASString&> TFunc_Instances_TextEvent_textSet;
typedef ThunkFunc0<Instances::TextEvent, Instances::TextEvent::mid_clone, Value> TFunc_Instances_TextEvent_clone;
typedef ThunkFunc0<Instances::TextEvent, Instances::TextEvent::mid_toString, ASString> TFunc_Instances_TextEvent_toString;

template <> const TFunc_Instances_TextEvent_textGet::TMethod TFunc_Instances_TextEvent_textGet::Method = &Instances::TextEvent::textGet;
template <> const TFunc_Instances_TextEvent_textSet::TMethod TFunc_Instances_TextEvent_textSet::Method = &Instances::TextEvent::textSet;
template <> const TFunc_Instances_TextEvent_clone::TMethod TFunc_Instances_TextEvent_clone::Method = &Instances::TextEvent::clone;
template <> const TFunc_Instances_TextEvent_toString::TMethod TFunc_Instances_TextEvent_toString::Method = &Instances::TextEvent::toString;

namespace Instances
{
    TextEvent::TextEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::TextEvent::TextEvent()$data"
    , Text(GetVM().GetStringManager().CreateEmptyString())
//##protect##"instance::TextEvent::TextEvent()$data"
    {
//##protect##"instance::TextEvent::TextEvent()$code"
//##protect##"instance::TextEvent::TextEvent()$code"
    }

    void TextEvent::textGet(ASString& result)
    {
//##protect##"instance::TextEvent::textGet()"
        SF_UNUSED1(result);
        result = Text;
//##protect##"instance::TextEvent::textGet()"
    }
    void TextEvent::textSet(Value& result, const ASString& value)
    {
//##protect##"instance::TextEvent::textSet()"
        SF_UNUSED2(result, value);
        Text = value;
//##protect##"instance::TextEvent::textSet()"
    }
    void TextEvent::clone(Value& result)
    {
//##protect##"instance::TextEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::TextEvent::clone()"
    }
    void TextEvent::toString(ASString& result)
    {
//##protect##"instance::TextEvent::toString()"
        SF_UNUSED1(result);
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("TextEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("text")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::TextEvent::toString()"
    }

//##protect##"instance$methods"
    AS3::Object* TextEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).TextEventClass; 
    }

    SPtr<Instances::Event> TextEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        TextEvent* pe = static_cast<TextEvent*>(p.GetPtr());
        pe->Text = Text;
        return p;
    }
    void TextEvent::SetText(wchar_t ch)
    {
        Text = GetVM().GetStringManager().CreateString(&ch, 1);
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo TextEvent::ti[TextEvent::ThunkInfoNum] = {
        {TFunc_Instances_TextEvent_textGet::Func, &StringCI, "text", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextEvent_textSet::Func, NULL, "text", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_TextEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    TextEvent::TextEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TextEvent::TextEvent()"
//##protect##"InstanceTraits::TextEvent::TextEvent()"
        SetMemSize(sizeof(Instances::TextEvent));

    }

    Pickable<Instances::TextEvent> TextEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TextEvent>(new(t.Alloc()) Instances::TextEvent(t));
    }

    void TextEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    TextEvent::TextEvent(ClassTraits::Traits& t)
    : Class(t)
    , LINK("link")
    , TEXT_INPUT("textInput")
    {
//##protect##"class_::TextEvent::TextEvent()"
//##protect##"class_::TextEvent::TextEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TextEvent::mi[TextEvent::MemberInfoNum] = {
        {"LINK", OFFSETOF(Classes::TextEvent, LINK), SlotInfo::BT_ConstChar, 1},
        {"TEXT_INPUT", OFFSETOF(Classes::TextEvent, TEXT_INPUT), SlotInfo::BT_ConstChar, 1},
    };

    TextEvent::TextEvent(VM& vm)
    : Traits(vm, TextEventCI)
    {
//##protect##"ClassTraits::TextEvent::TextEvent()"
//##protect##"ClassTraits::TextEvent::TextEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TextEvent(vm, TextEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextEventCI = {
    ClassInfo::CompileTime,
    "TextEvent", "flash.events", &EventCI,
    ClassTraits::TextEvent::MakeClassTraits,
    0,
    ClassTraits::TextEvent::MemberInfoNum,
    InstanceTraits::TextEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::TextEvent::mi,
    InstanceTraits::TextEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

