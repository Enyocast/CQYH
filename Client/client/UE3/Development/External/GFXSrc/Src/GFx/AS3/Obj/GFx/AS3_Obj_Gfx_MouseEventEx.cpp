//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_MouseEventEx.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_MouseEventEx.h"
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
    MouseEventEx::MouseEventEx(InstanceTraits::Traits& t)
    : Instances::MouseEvent(t)
    , mouseIdx()
    , buttonIdx()
    , nestingIdx()
//##protect##"instance::MouseEventEx::MouseEventEx()$data"
//##protect##"instance::MouseEventEx::MouseEventEx()$data"
    {
//##protect##"instance::MouseEventEx::MouseEventEx()$code"
//##protect##"instance::MouseEventEx::MouseEventEx()$code"
    }


//##protect##"instance$methods"
    AS3::Object* MouseEventEx::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).MouseEventExClass;
    }

    SPtr<Instances::Event> MouseEventEx::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        MouseEventEx* pe = static_cast<MouseEventEx*>(p.GetPtr());
        pe->AltKey          = AltKey;
        pe->CtrlKey         = CtrlKey;
        pe->ShiftKey        = ShiftKey;
        pe->Delta           = Delta;
        pe->RelatedObj      = RelatedObj;
        pe->LocalX          = LocalX;
        pe->LocalY          = LocalY;
        pe->StageX          = StageX;
        pe->StageY          = StageY;
        pe->ButtonsMask     = ButtonsMask;
        pe->LocalInitialized= LocalInitialized;
        pe->mouseIdx        = mouseIdx;
        return p;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo MouseEventEx::mi[MouseEventEx::MemberInfoNum] = {
        {"mouseIdx", OFFSETOF(Instances::MouseEventEx, mouseIdx), SlotInfo::BT_UInt, 0},
        {"buttonIdx", OFFSETOF(Instances::MouseEventEx, buttonIdx), SlotInfo::BT_UInt, 0},
        {"nestingIdx", OFFSETOF(Instances::MouseEventEx, nestingIdx), SlotInfo::BT_UInt, 0},
    };


    MouseEventEx::MouseEventEx(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::MouseEventEx::MouseEventEx()"
//##protect##"InstanceTraits::MouseEventEx::MouseEventEx()"
        SetMemSize(sizeof(Instances::MouseEventEx));

    }

    Pickable<Instances::MouseEventEx> MouseEventEx::MakeInstance(Traits& t)
    {
        return Pickable<Instances::MouseEventEx>(new(t.Alloc()) Instances::MouseEventEx(t));
    }

    void MouseEventEx::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    MouseEventEx::MouseEventEx(ClassTraits::Traits& t)
    : Class(t)
    , LEFT_BUTTON(0)
    , RIGHT_BUTTON(1)
    , MIDDLE_BUTTON(2)
    {
//##protect##"class_::MouseEventEx::MouseEventEx()"
//##protect##"class_::MouseEventEx::MouseEventEx()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo MouseEventEx::mi[MouseEventEx::MemberInfoNum] = {
        {"LEFT_BUTTON", OFFSETOF(Classes::MouseEventEx, LEFT_BUTTON), SlotInfo::BT_UInt, 1},
        {"RIGHT_BUTTON", OFFSETOF(Classes::MouseEventEx, RIGHT_BUTTON), SlotInfo::BT_UInt, 1},
        {"MIDDLE_BUTTON", OFFSETOF(Classes::MouseEventEx, MIDDLE_BUTTON), SlotInfo::BT_UInt, 1},
    };

    MouseEventEx::MouseEventEx(VM& vm)
    : Traits(vm, MouseEventExCI)
    {
//##protect##"ClassTraits::MouseEventEx::MouseEventEx()"
//##protect##"ClassTraits::MouseEventEx::MouseEventEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::MouseEventEx(vm, MouseEventExCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::MouseEventEx(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> MouseEventEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MouseEventEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MouseEventExCI = {
    ClassInfo::CompileTime,
    "MouseEventEx", "scaleform.gfx", &MouseEventCI,
    ClassTraits::MouseEventEx::MakeClassTraits,
    0,
    ClassTraits::MouseEventEx::MemberInfoNum,
    0,
    InstanceTraits::MouseEventEx::MemberInfoNum,
    NULL,
    ClassTraits::MouseEventEx::mi,
    NULL,
    InstanceTraits::MouseEventEx::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

