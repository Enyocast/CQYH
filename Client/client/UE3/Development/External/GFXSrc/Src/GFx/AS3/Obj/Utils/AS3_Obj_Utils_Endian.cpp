//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_Endian.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_Endian.h"
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
    Endian::Endian(ClassTraits::Traits& t)
    : Class(t)
    , BIG_ENDIAN("bigEndian")
    , LITTLE_ENDIAN("littleEndian")
    {
//##protect##"class_::Endian::Endian()"
//##protect##"class_::Endian::Endian()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo Endian::mi[Endian::MemberInfoNum] = {
        {"BIG_ENDIAN", OFFSETOF(Classes::Endian, BIG_ENDIAN), SlotInfo::BT_ConstChar, 1},
        {"LITTLE_ENDIAN", OFFSETOF(Classes::Endian, LITTLE_ENDIAN), SlotInfo::BT_ConstChar, 1},
    };

    Endian::Endian(VM& vm)
    : Traits(vm, EndianCI)
    {
//##protect##"ClassTraits::Endian::Endian()"
//##protect##"ClassTraits::Endian::Endian()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, EndianCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Endian(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Endian::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Endian(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo EndianCI = {
    ClassInfo::CompileTime,
    "Endian", "flash.utils", &ObjectCI,
    ClassTraits::Endian::MakeClassTraits,
    0,
    ClassTraits::Endian::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::Endian::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

