//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NativeDragEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_NativeDragEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Desktop/AS3_Obj_Desktop_NativeDragOptions.h"
#include "../Desktop/AS3_Obj_Desktop_Clipboard.h"
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
    NativeDragEvent::NativeDragEvent(InstanceTraits::Traits& t)
    : Instances::MouseEvent(t)
    , allowedActions()
    , clipboard()
    , dropAction(AS3::DefaultValue<ASString>(GetStringManager()))
//##protect##"instance::NativeDragEvent::NativeDragEvent()$data"
//##protect##"instance::NativeDragEvent::NativeDragEvent()$data"
    {
//##protect##"instance::NativeDragEvent::NativeDragEvent()$code"
//##protect##"instance::NativeDragEvent::NativeDragEvent()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo NativeDragEvent::ti[NativeDragEvent::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo NativeDragEvent::mi[NativeDragEvent::MemberInfoNum] = {
        {"allowedActions", OFFSETOF(Instances::NativeDragEvent, allowedActions), SlotInfo::BT_ObjectCpp, 0},
        {"clipboard", OFFSETOF(Instances::NativeDragEvent, clipboard), SlotInfo::BT_ObjectCpp, 0},
        {"dropAction", OFFSETOF(Instances::NativeDragEvent, dropAction), SlotInfo::BT_String, 0},
    };


    NativeDragEvent::NativeDragEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::NativeDragEvent::NativeDragEvent()"
//##protect##"InstanceTraits::NativeDragEvent::NativeDragEvent()"
        SetMemSize(sizeof(Instances::NativeDragEvent));

    }

    Pickable<Instances::NativeDragEvent> NativeDragEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::NativeDragEvent>(new(t.Alloc()) Instances::NativeDragEvent(t));
    }

    void NativeDragEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    NativeDragEvent::NativeDragEvent(ClassTraits::Traits& t)
    : Class(t)
    , NATIVE_DRAG_COMPLETE("nativeDragComplete")
    , NATIVE_DRAG_DROP("nativeDragDrop")
    , NATIVE_DRAG_ENTER("nativeDragEnter")
    , NATIVE_DRAG_EXIT("nativeDragExit")
    , NATIVE_DRAG_OVER("nativeDragOver")
    , NATIVE_DRAG_START("nativeDragStart")
    , NATIVE_DRAG_UPDATE("nativeDragUpdate")
    {
//##protect##"class_::NativeDragEvent::NativeDragEvent()"
//##protect##"class_::NativeDragEvent::NativeDragEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo NativeDragEvent::mi[NativeDragEvent::MemberInfoNum] = {
        {"NATIVE_DRAG_COMPLETE", OFFSETOF(Classes::NativeDragEvent, NATIVE_DRAG_COMPLETE), SlotInfo::BT_ConstChar, 1},
        {"NATIVE_DRAG_DROP", OFFSETOF(Classes::NativeDragEvent, NATIVE_DRAG_DROP), SlotInfo::BT_ConstChar, 1},
        {"NATIVE_DRAG_ENTER", OFFSETOF(Classes::NativeDragEvent, NATIVE_DRAG_ENTER), SlotInfo::BT_ConstChar, 1},
        {"NATIVE_DRAG_EXIT", OFFSETOF(Classes::NativeDragEvent, NATIVE_DRAG_EXIT), SlotInfo::BT_ConstChar, 1},
        {"NATIVE_DRAG_OVER", OFFSETOF(Classes::NativeDragEvent, NATIVE_DRAG_OVER), SlotInfo::BT_ConstChar, 1},
        {"NATIVE_DRAG_START", OFFSETOF(Classes::NativeDragEvent, NATIVE_DRAG_START), SlotInfo::BT_ConstChar, 1},
        {"NATIVE_DRAG_UPDATE", OFFSETOF(Classes::NativeDragEvent, NATIVE_DRAG_UPDATE), SlotInfo::BT_ConstChar, 1},
    };

    NativeDragEvent::NativeDragEvent(VM& vm)
    : Traits(vm, NativeDragEventCI)
    {
//##protect##"ClassTraits::NativeDragEvent::NativeDragEvent()"
//##protect##"ClassTraits::NativeDragEvent::NativeDragEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::NativeDragEvent(vm, NativeDragEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeDragEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeDragEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeDragEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeDragEventCI = {
    ClassInfo::CompileTime,
    "NativeDragEvent", "flash.events", &MouseEventCI,
    ClassTraits::NativeDragEvent::MakeClassTraits,
    0,
    ClassTraits::NativeDragEvent::MemberInfoNum,
    InstanceTraits::NativeDragEvent::ThunkInfoNum,
    InstanceTraits::NativeDragEvent::MemberInfoNum,
    NULL,
    ClassTraits::NativeDragEvent::mi,
    InstanceTraits::NativeDragEvent::ti,
    InstanceTraits::NativeDragEvent::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

