//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_SyncEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_SyncEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo SyncEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "changeList", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "changeList", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    SyncEvent::SyncEvent(ClassTraits::Traits& t)
    : Class(t)
    , SYNC("sync")
    {
//##protect##"class_::SyncEvent::SyncEvent()"
//##protect##"class_::SyncEvent::SyncEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SyncEvent::mi[SyncEvent::MemberInfoNum] = {
        {"SYNC", OFFSETOF(Classes::SyncEvent, SYNC), SlotInfo::BT_ConstChar, 1},
    };

    SyncEvent::SyncEvent(VM& vm)
    : Traits(vm, SyncEventCI)
    {
//##protect##"ClassTraits::SyncEvent::SyncEvent()"
//##protect##"ClassTraits::SyncEvent::SyncEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, SyncEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SyncEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SyncEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SyncEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SyncEventCI = {
    ClassInfo::CompileTime,
    "SyncEvent", "flash.events", &EventCI,
    ClassTraits::SyncEvent::MakeClassTraits,
    0,
    ClassTraits::SyncEvent::MemberInfoNum,
    4,
    0,
    NULL,
    ClassTraits::SyncEvent::mi,
    InstanceTraits::SyncEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

