//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLPDFCapability.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Html_HTMLPDFCapability.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    HTMLPDFCapability::HTMLPDFCapability(ClassTraits::Traits& t)
    : Class(t)
    , ERROR_CANNOT_LOAD_READER(3204)
    , ERROR_INSTALLED_READER_NOT_FOUND(3201)
    , ERROR_INSTALLED_READER_TOO_OLD(3202)
    , ERROR_PREFERRED_READER_TOO_OLD(3203)
    , STATUS_OK(0)
    {
//##protect##"class_::HTMLPDFCapability::HTMLPDFCapability()"
//##protect##"class_::HTMLPDFCapability::HTMLPDFCapability()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo HTMLPDFCapability::mi[HTMLPDFCapability::MemberInfoNum] = {
        {"ERROR_CANNOT_LOAD_READER", OFFSETOF(Classes::HTMLPDFCapability, ERROR_CANNOT_LOAD_READER), SlotInfo::BT_Int, 1},
        {"ERROR_INSTALLED_READER_NOT_FOUND", OFFSETOF(Classes::HTMLPDFCapability, ERROR_INSTALLED_READER_NOT_FOUND), SlotInfo::BT_Int, 1},
        {"ERROR_INSTALLED_READER_TOO_OLD", OFFSETOF(Classes::HTMLPDFCapability, ERROR_INSTALLED_READER_TOO_OLD), SlotInfo::BT_Int, 1},
        {"ERROR_PREFERRED_READER_TOO_OLD", OFFSETOF(Classes::HTMLPDFCapability, ERROR_PREFERRED_READER_TOO_OLD), SlotInfo::BT_Int, 1},
        {"STATUS_OK", OFFSETOF(Classes::HTMLPDFCapability, STATUS_OK), SlotInfo::BT_Int, 1},
    };

    HTMLPDFCapability::HTMLPDFCapability(VM& vm)
    : Traits(vm, HTMLPDFCapabilityCI)
    {
//##protect##"ClassTraits::HTMLPDFCapability::HTMLPDFCapability()"
//##protect##"ClassTraits::HTMLPDFCapability::HTMLPDFCapability()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, HTMLPDFCapabilityCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::HTMLPDFCapability(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> HTMLPDFCapability::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTMLPDFCapability(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo HTMLPDFCapabilityCI = {
    ClassInfo::CompileTime,
    "HTMLPDFCapability", "flash.html", &ObjectCI,
    ClassTraits::HTMLPDFCapability::MakeClassTraits,
    0,
    ClassTraits::HTMLPDFCapability::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::HTMLPDFCapability::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

