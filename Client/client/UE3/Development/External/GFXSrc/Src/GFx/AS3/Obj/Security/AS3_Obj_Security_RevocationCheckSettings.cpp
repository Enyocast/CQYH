//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_RevocationCheckSettings.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_RevocationCheckSettings.h"
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
    RevocationCheckSettings::RevocationCheckSettings(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::RevocationCheckSettings::RevocationCheckSettings()"
//##protect##"class_::RevocationCheckSettings::RevocationCheckSettings()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo RevocationCheckSettings::mi[RevocationCheckSettings::MemberInfoNum] = {
        {"ALWAYS_REQUIRED", OFFSETOF(Classes::RevocationCheckSettings, ALWAYS_REQUIRED), SlotInfo::BT_Value, 1},
        {"BEST_EFFORT", OFFSETOF(Classes::RevocationCheckSettings, BEST_EFFORT), SlotInfo::BT_Value, 1},
        {"NEVER", OFFSETOF(Classes::RevocationCheckSettings, NEVER), SlotInfo::BT_Value, 1},
        {"REQUIRED_IF_AVAILABLE", OFFSETOF(Classes::RevocationCheckSettings, REQUIRED_IF_AVAILABLE), SlotInfo::BT_Value, 1},
    };

    RevocationCheckSettings::RevocationCheckSettings(VM& vm)
    : Traits(vm, RevocationCheckSettingsCI)
    {
//##protect##"ClassTraits::RevocationCheckSettings::RevocationCheckSettings()"
//##protect##"ClassTraits::RevocationCheckSettings::RevocationCheckSettings()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, RevocationCheckSettingsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::RevocationCheckSettings(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> RevocationCheckSettings::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) RevocationCheckSettings(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo RevocationCheckSettingsCI = {
    ClassInfo::CompileTime,
    "RevocationCheckSettings", "flash.security", &ObjectCI,
    ClassTraits::RevocationCheckSettings::MakeClassTraits,
    0,
    ClassTraits::RevocationCheckSettings::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::RevocationCheckSettings::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

