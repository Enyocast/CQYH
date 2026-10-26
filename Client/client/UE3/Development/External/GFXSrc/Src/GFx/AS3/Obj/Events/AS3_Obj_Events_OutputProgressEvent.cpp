//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_OutputProgressEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_OutputProgressEvent.h"
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
    const ThunkInfo OutputProgressEvent_ti[6] = {
        {ThunkInfo::EmptyFunc, &NumberCI, "bytesPending", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bytesPending", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "bytesTotal", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bytesTotal", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    OutputProgressEvent::OutputProgressEvent(ClassTraits::Traits& t)
    : Class(t)
    , OUTPUT_PROGRESS("outputProgress")
    {
//##protect##"class_::OutputProgressEvent::OutputProgressEvent()"
//##protect##"class_::OutputProgressEvent::OutputProgressEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo OutputProgressEvent::mi[OutputProgressEvent::MemberInfoNum] = {
        {"OUTPUT_PROGRESS", OFFSETOF(Classes::OutputProgressEvent, OUTPUT_PROGRESS), SlotInfo::BT_ConstChar, 1},
    };

    OutputProgressEvent::OutputProgressEvent(VM& vm)
    : Traits(vm, OutputProgressEventCI)
    {
//##protect##"ClassTraits::OutputProgressEvent::OutputProgressEvent()"
//##protect##"ClassTraits::OutputProgressEvent::OutputProgressEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, OutputProgressEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::OutputProgressEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> OutputProgressEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) OutputProgressEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo OutputProgressEventCI = {
    ClassInfo::CompileTime,
    "OutputProgressEvent", "flash.events", &EventCI,
    ClassTraits::OutputProgressEvent::MakeClassTraits,
    0,
    ClassTraits::OutputProgressEvent::MemberInfoNum,
    6,
    0,
    NULL,
    ClassTraits::OutputProgressEvent::mi,
    InstanceTraits::OutputProgressEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

