//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_HTTPStatusEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_HTTPStatusEvent.h"
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
    const ThunkInfo HTTPStatusEvent_ti[7] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "responseHeaders", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "responseHeaders", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "responseURL", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "responseURL", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "status", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    HTTPStatusEvent::HTTPStatusEvent(ClassTraits::Traits& t)
    : Class(t)
    , HTTP_RESPONSE_STATUS("httpResponseStatus")
    , HTTP_STATUS("httpStatus")
    {
//##protect##"class_::HTTPStatusEvent::HTTPStatusEvent()"
//##protect##"class_::HTTPStatusEvent::HTTPStatusEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo HTTPStatusEvent::mi[HTTPStatusEvent::MemberInfoNum] = {
        {"HTTP_RESPONSE_STATUS", OFFSETOF(Classes::HTTPStatusEvent, HTTP_RESPONSE_STATUS), SlotInfo::BT_ConstChar, 1},
        {"HTTP_STATUS", OFFSETOF(Classes::HTTPStatusEvent, HTTP_STATUS), SlotInfo::BT_ConstChar, 1},
    };

    HTTPStatusEvent::HTTPStatusEvent(VM& vm)
    : Traits(vm, HTTPStatusEventCI)
    {
//##protect##"ClassTraits::HTTPStatusEvent::HTTPStatusEvent()"
//##protect##"ClassTraits::HTTPStatusEvent::HTTPStatusEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, HTTPStatusEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::HTTPStatusEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> HTTPStatusEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTTPStatusEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo HTTPStatusEventCI = {
    ClassInfo::CompileTime,
    "HTTPStatusEvent", "flash.events", &EventCI,
    ClassTraits::HTTPStatusEvent::MakeClassTraits,
    0,
    ClassTraits::HTTPStatusEvent::MemberInfoNum,
    7,
    0,
    NULL,
    ClassTraits::HTTPStatusEvent::mi,
    InstanceTraits::HTTPStatusEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

