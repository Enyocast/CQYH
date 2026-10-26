//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_ObjectEncoding.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_ObjectEncoding.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_IDynamicPropertyWriter.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo ObjectEncoding_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "dynamicPropertyWriter", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits

namespace Classes
{
    ObjectEncoding::ObjectEncoding(ClassTraits::Traits& t)
    : Class(t)
    , AMF0(0)
    , AMF3(3)
    , DEFAULT(3)
    {
//##protect##"class_::ObjectEncoding::ObjectEncoding()"
//##protect##"class_::ObjectEncoding::ObjectEncoding()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo ObjectEncoding::mi[ObjectEncoding::MemberInfoNum] = {
        {"AMF0", OFFSETOF(Classes::ObjectEncoding, AMF0), SlotInfo::BT_UInt, 1},
        {"AMF3", OFFSETOF(Classes::ObjectEncoding, AMF3), SlotInfo::BT_UInt, 1},
        {"DEFAULT", OFFSETOF(Classes::ObjectEncoding, DEFAULT), SlotInfo::BT_UInt, 1},
    };

    ObjectEncoding::ObjectEncoding(VM& vm)
    : Traits(vm, ObjectEncodingCI)
    {
//##protect##"ClassTraits::ObjectEncoding::ObjectEncoding()"
//##protect##"ClassTraits::ObjectEncoding::ObjectEncoding()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, ObjectEncodingCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ObjectEncoding(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ObjectEncoding::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ObjectEncoding(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ObjectEncodingCI = {
    ClassInfo::CompileTime,
    "ObjectEncoding", "flash.net", &ObjectCI,
    ClassTraits::ObjectEncoding::MakeClassTraits,
    0,
    ClassTraits::ObjectEncoding::MemberInfoNum,
    1,
    0,
    NULL,
    ClassTraits::ObjectEncoding::mi,
    InstanceTraits::ObjectEncoding_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

