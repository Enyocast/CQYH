//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_BrowserInvokeEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_BrowserInvokeEvent.h"
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
    const ThunkInfo BrowserInvokeEvent_ti[6] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "arguments", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isHTTPS", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isUserEvent", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "sandboxType", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "securityDomain", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    BrowserInvokeEvent::BrowserInvokeEvent(ClassTraits::Traits& t)
    : Class(t)
    , BROWSER_INVOKE("browserInvoke")
    {
//##protect##"class_::BrowserInvokeEvent::BrowserInvokeEvent()"
//##protect##"class_::BrowserInvokeEvent::BrowserInvokeEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo BrowserInvokeEvent::mi[BrowserInvokeEvent::MemberInfoNum] = {
        {"BROWSER_INVOKE", OFFSETOF(Classes::BrowserInvokeEvent, BROWSER_INVOKE), SlotInfo::BT_ConstChar, 1},
    };

    BrowserInvokeEvent::BrowserInvokeEvent(VM& vm)
    : Traits(vm, BrowserInvokeEventCI)
    {
//##protect##"ClassTraits::BrowserInvokeEvent::BrowserInvokeEvent()"
//##protect##"ClassTraits::BrowserInvokeEvent::BrowserInvokeEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, BrowserInvokeEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::BrowserInvokeEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BrowserInvokeEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BrowserInvokeEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BrowserInvokeEventCI = {
    ClassInfo::CompileTime,
    "BrowserInvokeEvent", "flash.events", &EventCI,
    ClassTraits::BrowserInvokeEvent::MakeClassTraits,
    0,
    ClassTraits::BrowserInvokeEvent::MemberInfoNum,
    6,
    0,
    NULL,
    ClassTraits::BrowserInvokeEvent::mi,
    InstanceTraits::BrowserInvokeEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

