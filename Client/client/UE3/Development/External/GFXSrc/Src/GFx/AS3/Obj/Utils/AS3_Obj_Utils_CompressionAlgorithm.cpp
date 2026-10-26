//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_CompressionAlgorithm.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_CompressionAlgorithm.h"
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
    CompressionAlgorithm::CompressionAlgorithm(ClassTraits::Traits& t)
    : Class(t)
    , DEFLATE("deflate")
    , ZLIB("zlib")
    {
//##protect##"class_::CompressionAlgorithm::CompressionAlgorithm()"
//##protect##"class_::CompressionAlgorithm::CompressionAlgorithm()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo CompressionAlgorithm::mi[CompressionAlgorithm::MemberInfoNum] = {
        {"DEFLATE", OFFSETOF(Classes::CompressionAlgorithm, DEFLATE), SlotInfo::BT_ConstChar, 1},
        {"ZLIB", OFFSETOF(Classes::CompressionAlgorithm, ZLIB), SlotInfo::BT_ConstChar, 1},
    };

    CompressionAlgorithm::CompressionAlgorithm(VM& vm)
    : Traits(vm, CompressionAlgorithmCI)
    {
//##protect##"ClassTraits::CompressionAlgorithm::CompressionAlgorithm()"
//##protect##"ClassTraits::CompressionAlgorithm::CompressionAlgorithm()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, CompressionAlgorithmCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::CompressionAlgorithm(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> CompressionAlgorithm::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) CompressionAlgorithm(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo CompressionAlgorithmCI = {
    ClassInfo::CompileTime,
    "CompressionAlgorithm", "flash.utils", &ObjectCI,
    ClassTraits::CompressionAlgorithm::MakeClassTraits,
    0,
    ClassTraits::CompressionAlgorithm::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::CompressionAlgorithm::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

