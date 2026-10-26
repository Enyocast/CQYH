//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_IMEConversionMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_IMEConversionMode.h"
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
    IMEConversionMode::IMEConversionMode(ClassTraits::Traits& t)
    : Class(t)
    , ALPHANUMERIC_FULL("ALPHANUMERIC_FULL")
    , ALPHANUMERIC_HALF("ALPHANUMERIC_HALF")
    , CHINESE("CHINESE")
    , JAPANESE_HIRAGANA("JAPANESE_HIRAGANA")
    , JAPANESE_KATAKANA_FULL("JAPANESE_KATAKANA_FULL")
    , JAPANESE_KATAKANA_HALF("JAPANESE_KATAKANA_HALF")
    , KOREAN("KOREAN")
    , UNKNOWN("UNKNOWN")
    {
//##protect##"class_::IMEConversionMode::IMEConversionMode()"
//##protect##"class_::IMEConversionMode::IMEConversionMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo IMEConversionMode::mi[IMEConversionMode::MemberInfoNum] = {
        {"ALPHANUMERIC_FULL", OFFSETOF(Classes::IMEConversionMode, ALPHANUMERIC_FULL), SlotInfo::BT_ConstChar, 1},
        {"ALPHANUMERIC_HALF", OFFSETOF(Classes::IMEConversionMode, ALPHANUMERIC_HALF), SlotInfo::BT_ConstChar, 1},
        {"CHINESE", OFFSETOF(Classes::IMEConversionMode, CHINESE), SlotInfo::BT_ConstChar, 1},
        {"JAPANESE_HIRAGANA", OFFSETOF(Classes::IMEConversionMode, JAPANESE_HIRAGANA), SlotInfo::BT_ConstChar, 1},
        {"JAPANESE_KATAKANA_FULL", OFFSETOF(Classes::IMEConversionMode, JAPANESE_KATAKANA_FULL), SlotInfo::BT_ConstChar, 1},
        {"JAPANESE_KATAKANA_HALF", OFFSETOF(Classes::IMEConversionMode, JAPANESE_KATAKANA_HALF), SlotInfo::BT_ConstChar, 1},
        {"KOREAN", OFFSETOF(Classes::IMEConversionMode, KOREAN), SlotInfo::BT_ConstChar, 1},
        {"UNKNOWN", OFFSETOF(Classes::IMEConversionMode, UNKNOWN), SlotInfo::BT_ConstChar, 1},
    };

    IMEConversionMode::IMEConversionMode(VM& vm)
    : Traits(vm, IMEConversionModeCI)
    {
//##protect##"ClassTraits::IMEConversionMode::IMEConversionMode()"
//##protect##"ClassTraits::IMEConversionMode::IMEConversionMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, IMEConversionModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::IMEConversionMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IMEConversionMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IMEConversionMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IMEConversionModeCI = {
    ClassInfo::CompileTime,
    "IMEConversionMode", "flash.system", &ObjectCI,
    ClassTraits::IMEConversionMode::MakeClassTraits,
    0,
    ClassTraits::IMEConversionMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::IMEConversionMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

