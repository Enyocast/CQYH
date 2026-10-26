//##protect##"disclaimer"
/**********************************************************************

Filename    :   .cpp
Content     :   
Created     :   Jul, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_MouseCursorEvent.h"
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

namespace Instances
{
    MouseCursorEvent::MouseCursorEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
    , cursor(AS3::DefaultValue<ASString>(GetStringManager()))
    , mouseIdx(0)
//##protect##"instance::MouseCursorEvent::MouseCursorEvent()$data"
//##protect##"instance::MouseCursorEvent::MouseCursorEvent()$data"
    {
//##protect##"instance::MouseCursorEvent::MouseCursorEvent()$code"
        Bubbles    = false;
        Cancelable = true;
//##protect##"instance::MouseCursorEvent::MouseCursorEvent()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo MouseCursorEvent::mi[MouseCursorEvent::MemberInfoNum] = {
        {"cursor", OFFSETOF(Instances::MouseCursorEvent, cursor), SlotInfo::BT_String, 0},
        {"mouseIdx", OFFSETOF(Instances::MouseCursorEvent, mouseIdx), SlotInfo::BT_UInt, 0},
    };


    MouseCursorEvent::MouseCursorEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::MouseCursorEvent::MouseCursorEvent()"
//##protect##"InstanceTraits::MouseCursorEvent::MouseCursorEvent()"
        SetMemSize(sizeof(Instances::MouseCursorEvent));

    }

    Pickable<Instances::MouseCursorEvent> MouseCursorEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::MouseCursorEvent>(new(t.Alloc()) Instances::MouseCursorEvent(t));
    }

    void MouseCursorEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    MouseCursorEvent::MouseCursorEvent(ClassTraits::Traits& t)
    : Class(t)
    , CURSOR_CHANGE("mouseCursorChange")
    {
//##protect##"class_::MouseCursorEvent::MouseCursorEvent()"
//##protect##"class_::MouseCursorEvent::MouseCursorEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo MouseCursorEvent::mi[MouseCursorEvent::MemberInfoNum] = {
        {"CURSOR_CHANGE", OFFSETOF(Classes::MouseCursorEvent, CURSOR_CHANGE), SlotInfo::BT_ConstChar, 1},
    };

    MouseCursorEvent::MouseCursorEvent(VM& vm)
    : Traits(vm, MouseCursorEventCI)
    {
//##protect##"ClassTraits::MouseCursorEvent::MouseCursorEvent()"
//##protect##"ClassTraits::MouseCursorEvent::MouseCursorEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::MouseCursorEvent(vm, MouseCursorEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::MouseCursorEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> MouseCursorEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MouseCursorEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MouseCursorEventCI = {
    ClassInfo::CompileTime,
    "MouseCursorEvent", "scaleform.gfx", &EventCI,
    ClassTraits::MouseCursorEvent::MakeClassTraits,
    0,
    ClassTraits::MouseCursorEvent::MemberInfoNum,
    0,
    InstanceTraits::MouseCursorEvent::MemberInfoNum,
    NULL,
    ClassTraits::MouseCursorEvent::mi,
    NULL,
    InstanceTraits::MouseCursorEvent::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

