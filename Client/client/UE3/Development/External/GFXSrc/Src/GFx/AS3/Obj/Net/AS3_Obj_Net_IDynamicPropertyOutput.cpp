//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_IDynamicPropertyOutput.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_IDynamicPropertyOutput.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
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
    const ThunkInfo IDynamicPropertyOutput_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "writeDynamicProperty", "flash.net:IDynamicPropertyOutput", CT_Method, 2, 2},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    IDynamicPropertyOutput::IDynamicPropertyOutput(VM& vm)
    : Traits(vm, IDynamicPropertyOutputCI)
    {
//##protect##"ClassTraits::IDynamicPropertyOutput::IDynamicPropertyOutput()"
//##protect##"ClassTraits::IDynamicPropertyOutput::IDynamicPropertyOutput()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, IDynamicPropertyOutputCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IDynamicPropertyOutput::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IDynamicPropertyOutput(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IDynamicPropertyOutputCI = {
    ClassInfo::CompileTime,
    "IDynamicPropertyOutput", "flash.net", NULL,
    ClassTraits::IDynamicPropertyOutput::MakeClassTraits,
    0,
    0,
    1,
    0,
    NULL,
    NULL,
    InstanceTraits::IDynamicPropertyOutput_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

