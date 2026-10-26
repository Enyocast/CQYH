//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_SignatureStatus.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_SignatureStatus.h"
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
    SignatureStatus::SignatureStatus(ClassTraits::Traits& t)
    : Class(t)
    , INVALID("invalid")
    , UNKNOWN("")
    , VALID("valid")
    {
//##protect##"class_::SignatureStatus::SignatureStatus()"
//##protect##"class_::SignatureStatus::SignatureStatus()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SignatureStatus::mi[SignatureStatus::MemberInfoNum] = {
        {"INVALID", OFFSETOF(Classes::SignatureStatus, INVALID), SlotInfo::BT_ConstChar, 1},
        {"UNKNOWN", OFFSETOF(Classes::SignatureStatus, UNKNOWN), SlotInfo::BT_ConstChar, 1},
        {"VALID", OFFSETOF(Classes::SignatureStatus, VALID), SlotInfo::BT_ConstChar, 1},
    };

    SignatureStatus::SignatureStatus(VM& vm)
    : Traits(vm, SignatureStatusCI)
    {
//##protect##"ClassTraits::SignatureStatus::SignatureStatus()"
//##protect##"ClassTraits::SignatureStatus::SignatureStatus()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SignatureStatusCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SignatureStatus(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SignatureStatus::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SignatureStatus(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SignatureStatusCI = {
    ClassInfo::CompileTime,
    "SignatureStatus", "flash.security", &ObjectCI,
    ClassTraits::SignatureStatus::MakeClassTraits,
    0,
    ClassTraits::SignatureStatus::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::SignatureStatus::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

