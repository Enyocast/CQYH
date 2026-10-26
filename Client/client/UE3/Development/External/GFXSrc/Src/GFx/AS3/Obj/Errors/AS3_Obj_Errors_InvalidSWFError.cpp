//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Errors_InvalidSWFError.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Errors_InvalidSWFError.h"
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
    InvalidSWFError::InvalidSWFError(VM& vm)
    : Traits(vm, InvalidSWFErrorCI)
    {
//##protect##"ClassTraits::InvalidSWFError::InvalidSWFError()"
//##protect##"ClassTraits::InvalidSWFError::InvalidSWFError()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Error(vm, InvalidSWFErrorCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> InvalidSWFError::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) InvalidSWFError(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo InvalidSWFErrorCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "InvalidSWFError", "flash.errors", &ErrorCI,
    ClassTraits::InvalidSWFError::MakeClassTraits,
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

