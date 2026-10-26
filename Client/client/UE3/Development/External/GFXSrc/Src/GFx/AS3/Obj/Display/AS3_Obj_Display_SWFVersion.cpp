//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_SWFVersion.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_SWFVersion.h"
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
    SWFVersion::SWFVersion(ClassTraits::Traits& t)
    : Class(t)
    , FLASH1(1)
    , FLASH2(2)
    , FLASH3(3)
    , FLASH4(4)
    , FLASH5(5)
    , FLASH6(6)
    , FLASH7(7)
    , FLASH8(8)
    , FLASH9(9)
    {
//##protect##"class_::SWFVersion::SWFVersion()"
//##protect##"class_::SWFVersion::SWFVersion()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SWFVersion::mi[SWFVersion::MemberInfoNum] = {
        {"FLASH1", OFFSETOF(Classes::SWFVersion, FLASH1), SlotInfo::BT_UInt, 1},
        {"FLASH2", OFFSETOF(Classes::SWFVersion, FLASH2), SlotInfo::BT_UInt, 1},
        {"FLASH3", OFFSETOF(Classes::SWFVersion, FLASH3), SlotInfo::BT_UInt, 1},
        {"FLASH4", OFFSETOF(Classes::SWFVersion, FLASH4), SlotInfo::BT_UInt, 1},
        {"FLASH5", OFFSETOF(Classes::SWFVersion, FLASH5), SlotInfo::BT_UInt, 1},
        {"FLASH6", OFFSETOF(Classes::SWFVersion, FLASH6), SlotInfo::BT_UInt, 1},
        {"FLASH7", OFFSETOF(Classes::SWFVersion, FLASH7), SlotInfo::BT_UInt, 1},
        {"FLASH8", OFFSETOF(Classes::SWFVersion, FLASH8), SlotInfo::BT_UInt, 1},
        {"FLASH9", OFFSETOF(Classes::SWFVersion, FLASH9), SlotInfo::BT_UInt, 1},
    };

    SWFVersion::SWFVersion(VM& vm)
    : Traits(vm, SWFVersionCI)
    {
//##protect##"ClassTraits::SWFVersion::SWFVersion()"
//##protect##"ClassTraits::SWFVersion::SWFVersion()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SWFVersionCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SWFVersion(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SWFVersion::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SWFVersion(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SWFVersionCI = {
    ClassInfo::CompileTime,
    "SWFVersion", "flash.display", &ObjectCI,
    ClassTraits::SWFVersion::MakeClassTraits,
    0,
    ClassTraits::SWFVersion::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::SWFVersion::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

