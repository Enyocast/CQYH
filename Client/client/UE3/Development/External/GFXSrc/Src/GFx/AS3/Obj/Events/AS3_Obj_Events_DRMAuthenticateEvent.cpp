//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMAuthenticateEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_DRMAuthenticateEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NetStream;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo DRMAuthenticateEvent_ti[7] = {
        {ThunkInfo::EmptyFunc, &StringCI, "authenticationType", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "header", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "passwordPrompt", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "urlPrompt", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "usernamePrompt", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    DRMAuthenticateEvent::DRMAuthenticateEvent(ClassTraits::Traits& t)
    : Class(t)
    , AUTHENTICATION_TYPE_DRM("drm")
    , AUTHENTICATION_TYPE_PROXY("proxy")
    , DRM_AUTHENTICATE("drmAuthenticate")
    {
//##protect##"class_::DRMAuthenticateEvent::DRMAuthenticateEvent()"
//##protect##"class_::DRMAuthenticateEvent::DRMAuthenticateEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo DRMAuthenticateEvent::mi[DRMAuthenticateEvent::MemberInfoNum] = {
        {"AUTHENTICATION_TYPE_DRM", OFFSETOF(Classes::DRMAuthenticateEvent, AUTHENTICATION_TYPE_DRM), SlotInfo::BT_ConstChar, 1},
        {"AUTHENTICATION_TYPE_PROXY", OFFSETOF(Classes::DRMAuthenticateEvent, AUTHENTICATION_TYPE_PROXY), SlotInfo::BT_ConstChar, 1},
        {"DRM_AUTHENTICATE", OFFSETOF(Classes::DRMAuthenticateEvent, DRM_AUTHENTICATE), SlotInfo::BT_ConstChar, 1},
    };

    DRMAuthenticateEvent::DRMAuthenticateEvent(VM& vm)
    : Traits(vm, DRMAuthenticateEventCI)
    {
//##protect##"ClassTraits::DRMAuthenticateEvent::DRMAuthenticateEvent()"
//##protect##"ClassTraits::DRMAuthenticateEvent::DRMAuthenticateEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, DRMAuthenticateEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::DRMAuthenticateEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DRMAuthenticateEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DRMAuthenticateEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DRMAuthenticateEventCI = {
    ClassInfo::CompileTime,
    "DRMAuthenticateEvent", "flash.events", &EventCI,
    ClassTraits::DRMAuthenticateEvent::MakeClassTraits,
    0,
    ClassTraits::DRMAuthenticateEvent::MemberInfoNum,
    7,
    0,
    NULL,
    ClassTraits::DRMAuthenticateEvent::mi,
    InstanceTraits::DRMAuthenticateEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

