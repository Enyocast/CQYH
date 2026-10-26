//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DataEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_DataEvent.h"
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

namespace InstanceTraits
{
    const ThunkInfo DataEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &StringCI, "data", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "data", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    DataEvent::DataEvent(ClassTraits::Traits& t)
    : Class(t)
    , DATA("data")
    , UPLOAD_COMPLETE_DATA("uploadCompleteData")
    {
//##protect##"class_::DataEvent::DataEvent()"
//##protect##"class_::DataEvent::DataEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo DataEvent::mi[DataEvent::MemberInfoNum] = {
        {"DATA", OFFSETOF(Classes::DataEvent, DATA), SlotInfo::BT_ConstChar, 1},
        {"UPLOAD_COMPLETE_DATA", OFFSETOF(Classes::DataEvent, UPLOAD_COMPLETE_DATA), SlotInfo::BT_ConstChar, 1},
    };

    DataEvent::DataEvent(VM& vm)
    : Traits(vm, DataEventCI)
    {
//##protect##"ClassTraits::DataEvent::DataEvent()"
//##protect##"ClassTraits::DataEvent::DataEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TextEvent(vm, DataEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::DataEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DataEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DataEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DataEventCI = {
    ClassInfo::CompileTime,
    "DataEvent", "flash.events", &TextEventCI,
    ClassTraits::DataEvent::MakeClassTraits,
    0,
    ClassTraits::DataEvent::MemberInfoNum,
    4,
    0,
    NULL,
    ClassTraits::DataEvent::mi,
    InstanceTraits::DataEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

