//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_BlendMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_BlendMode.h"
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
    BlendMode::BlendMode(ClassTraits::Traits& t)
    : Class(t)
    , ADD("add")
    , ALPHA("alpha")
    , DARKEN("darken")
    , DIFFERENCE("difference")
    , ERASE("erase")
    , HARDLIGHT("hardlight")
    , INVERT("invert")
    , LAYER("layer")
    , LIGHTEN("lighten")
    , MULTIPLY("multiply")
    , NORMAL("normal")
    , OVERLAY("overlay")
    , SCREEN("screen")
    , SUBTRACT("subtract")
    {
//##protect##"class_::BlendMode::BlendMode()"
//##protect##"class_::BlendMode::BlendMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo BlendMode::mi[BlendMode::MemberInfoNum] = {
        {"ADD", OFFSETOF(Classes::BlendMode, ADD), SlotInfo::BT_ConstChar, 1},
        {"ALPHA", OFFSETOF(Classes::BlendMode, ALPHA), SlotInfo::BT_ConstChar, 1},
        {"DARKEN", OFFSETOF(Classes::BlendMode, DARKEN), SlotInfo::BT_ConstChar, 1},
        {"DIFFERENCE", OFFSETOF(Classes::BlendMode, DIFFERENCE), SlotInfo::BT_ConstChar, 1},
        {"ERASE", OFFSETOF(Classes::BlendMode, ERASE), SlotInfo::BT_ConstChar, 1},
        {"HARDLIGHT", OFFSETOF(Classes::BlendMode, HARDLIGHT), SlotInfo::BT_ConstChar, 1},
        {"INVERT", OFFSETOF(Classes::BlendMode, INVERT), SlotInfo::BT_ConstChar, 1},
        {"LAYER", OFFSETOF(Classes::BlendMode, LAYER), SlotInfo::BT_ConstChar, 1},
        {"LIGHTEN", OFFSETOF(Classes::BlendMode, LIGHTEN), SlotInfo::BT_ConstChar, 1},
        {"MULTIPLY", OFFSETOF(Classes::BlendMode, MULTIPLY), SlotInfo::BT_ConstChar, 1},
        {"NORMAL", OFFSETOF(Classes::BlendMode, NORMAL), SlotInfo::BT_ConstChar, 1},
        {"OVERLAY", OFFSETOF(Classes::BlendMode, OVERLAY), SlotInfo::BT_ConstChar, 1},
        {"SCREEN", OFFSETOF(Classes::BlendMode, SCREEN), SlotInfo::BT_ConstChar, 1},
        {"SUBTRACT", OFFSETOF(Classes::BlendMode, SUBTRACT), SlotInfo::BT_ConstChar, 1},
    };

    BlendMode::BlendMode(VM& vm)
    : Traits(vm, BlendModeCI)
    {
//##protect##"ClassTraits::BlendMode::BlendMode()"
//##protect##"ClassTraits::BlendMode::BlendMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, BlendModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::BlendMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BlendMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BlendMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BlendModeCI = {
    ClassInfo::CompileTime,
    "BlendMode", "flash.display", &ObjectCI,
    ClassTraits::BlendMode::MakeClassTraits,
    0,
    ClassTraits::BlendMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::BlendMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

