//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Printing_PrintJobOrientation.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Printing_PrintJobOrientation.h"
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
    PrintJobOrientation::PrintJobOrientation(ClassTraits::Traits& t)
    : Class(t)
    , LANDSCAPE("landscape")
    , PORTRAIT("portrait")
    {
//##protect##"class_::PrintJobOrientation::PrintJobOrientation()"
//##protect##"class_::PrintJobOrientation::PrintJobOrientation()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo PrintJobOrientation::mi[PrintJobOrientation::MemberInfoNum] = {
        {"LANDSCAPE", OFFSETOF(Classes::PrintJobOrientation, LANDSCAPE), SlotInfo::BT_ConstChar, 1},
        {"PORTRAIT", OFFSETOF(Classes::PrintJobOrientation, PORTRAIT), SlotInfo::BT_ConstChar, 1},
    };

    PrintJobOrientation::PrintJobOrientation(VM& vm)
    : Traits(vm, PrintJobOrientationCI)
    {
//##protect##"ClassTraits::PrintJobOrientation::PrintJobOrientation()"
//##protect##"ClassTraits::PrintJobOrientation::PrintJobOrientation()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, PrintJobOrientationCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::PrintJobOrientation(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> PrintJobOrientation::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PrintJobOrientation(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo PrintJobOrientationCI = {
    ClassInfo::CompileTime,
    "PrintJobOrientation", "flash.printing", &ObjectCI,
    ClassTraits::PrintJobOrientation::MakeClassTraits,
    0,
    ClassTraits::PrintJobOrientation::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::PrintJobOrientation::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

