//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filesystem_FileMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filesystem_FileMode.h"
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
    FileMode::FileMode(ClassTraits::Traits& t)
    : Class(t)
    , APPEND("append")
    , READ("read")
    , UPDATE("update")
    , WRITE("write")
    {
//##protect##"class_::FileMode::FileMode()"
//##protect##"class_::FileMode::FileMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo FileMode::mi[FileMode::MemberInfoNum] = {
        {"APPEND", OFFSETOF(Classes::FileMode, APPEND), SlotInfo::BT_ConstChar, 1},
        {"READ", OFFSETOF(Classes::FileMode, READ), SlotInfo::BT_ConstChar, 1},
        {"UPDATE", OFFSETOF(Classes::FileMode, UPDATE), SlotInfo::BT_ConstChar, 1},
        {"WRITE", OFFSETOF(Classes::FileMode, WRITE), SlotInfo::BT_ConstChar, 1},
    };

    FileMode::FileMode(VM& vm)
    : Traits(vm, FileModeCI)
    {
//##protect##"ClassTraits::FileMode::FileMode()"
//##protect##"ClassTraits::FileMode::FileMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, FileModeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FileMode(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FileMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FileModeCI = {
    ClassInfo::CompileTime,
    "FileMode", "flash.filesystem", &ObjectCI,
    ClassTraits::FileMode::MakeClassTraits,
    0,
    ClassTraits::FileMode::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::FileMode::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

