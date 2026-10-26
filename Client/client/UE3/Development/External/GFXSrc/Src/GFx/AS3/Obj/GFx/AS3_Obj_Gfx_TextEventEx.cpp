//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_TextEventEx.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_TextEventEx.h"
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

namespace Instances
{
    TextEventEx::TextEventEx(InstanceTraits::Traits& t)
    : Instances::TextEvent(t)
    , controllerIdx()
    , buttonIdx()
//##protect##"instance::TextEventEx::TextEventEx()$data"
//##protect##"instance::TextEventEx::TextEventEx()$data"
    {
//##protect##"instance::TextEventEx::TextEventEx()$code"
//##protect##"instance::TextEventEx::TextEventEx()$code"
    }


//##protect##"instance$methods"
    AS3::Object* TextEventEx::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).TextEventExClass; 
    }

    SPtr<Instances::Event> TextEventEx::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        TextEventEx* pe = static_cast<TextEventEx*>(p.GetPtr());
        pe->Text = Text;
        pe->controllerIdx = controllerIdx;
        pe->buttonIdx = buttonIdx;
        return p;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo TextEventEx::mi[TextEventEx::MemberInfoNum] = {
        {"controllerIdx", OFFSETOF(Instances::TextEventEx, controllerIdx), SlotInfo::BT_UInt, 0},
        {"buttonIdx", OFFSETOF(Instances::TextEventEx, buttonIdx), SlotInfo::BT_UInt, 0},
    };


    TextEventEx::TextEventEx(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TextEventEx::TextEventEx()"
//##protect##"InstanceTraits::TextEventEx::TextEventEx()"
        SetMemSize(sizeof(Instances::TextEventEx));

    }

    Pickable<Instances::TextEventEx> TextEventEx::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TextEventEx>(new(t.Alloc()) Instances::TextEventEx(t));
    }

    void TextEventEx::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    TextEventEx::TextEventEx(ClassTraits::Traits& t)
    : Class(t)
    , LINK_MOUSE_OVER("linkMouseOver")
    , LINK_MOUSE_OUT("linkMouseOut")
    {
//##protect##"class_::TextEventEx::TextEventEx()"
//##protect##"class_::TextEventEx::TextEventEx()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TextEventEx::mi[TextEventEx::MemberInfoNum] = {
        {"LINK_MOUSE_OVER", OFFSETOF(Classes::TextEventEx, LINK_MOUSE_OVER), SlotInfo::BT_ConstChar, 1},
        {"LINK_MOUSE_OUT", OFFSETOF(Classes::TextEventEx, LINK_MOUSE_OUT), SlotInfo::BT_ConstChar, 1},
    };

    TextEventEx::TextEventEx(VM& vm)
    : Traits(vm, TextEventExCI)
    {
//##protect##"ClassTraits::TextEventEx::TextEventEx()"
//##protect##"ClassTraits::TextEventEx::TextEventEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TextEventEx(vm, TextEventExCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextEventEx(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextEventEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextEventEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextEventExCI = {
    ClassInfo::CompileTime,
    "TextEventEx", "scaleform.gfx", &TextEventCI,
    ClassTraits::TextEventEx::MakeClassTraits,
    0,
    ClassTraits::TextEventEx::MemberInfoNum,
    0,
    InstanceTraits::TextEventEx::MemberInfoNum,
    NULL,
    ClassTraits::TextEventEx::mi,
    NULL,
    InstanceTraits::TextEventEx::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

