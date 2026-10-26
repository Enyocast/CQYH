//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Errors_IllegalOperationError.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Errors_IllegalOperationError.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"


namespace ClassTraits
{
    IllegalOperationError::IllegalOperationError(VM& vm)
    : Traits(vm, IllegalOperationErrorCI)
    {
//##protect##"ClassTraits::IllegalOperationError::IllegalOperationError()"
//##protect##"ClassTraits::IllegalOperationError::IllegalOperationError()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Error(vm, IllegalOperationErrorCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IllegalOperationError::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IllegalOperationError(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IllegalOperationErrorCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "IllegalOperationError", "flash.errors", &ErrorCI,
    ClassTraits::IllegalOperationError::MakeClassTraits,
    0,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

