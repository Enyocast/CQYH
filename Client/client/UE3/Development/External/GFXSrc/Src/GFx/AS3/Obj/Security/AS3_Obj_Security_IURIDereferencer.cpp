//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_IURIDereferencer.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_IURIDereferencer.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class IDataInput;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo IURIDereferencer_ti[1] = {
        {ThunkInfo::EmptyFunc, &IDataInputCI, "dereference", "flash.security:IURIDereferencer", CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    IURIDereferencer::IURIDereferencer(VM& vm)
    : Traits(vm, IURIDereferencerCI)
    {
//##protect##"ClassTraits::IURIDereferencer::IURIDereferencer()"
//##protect##"ClassTraits::IURIDereferencer::IURIDereferencer()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, IURIDereferencerCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IURIDereferencer::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IURIDereferencer(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IURIDereferencerCI = {
    ClassInfo::CompileTime,
    "IURIDereferencer", "flash.security", NULL,
    ClassTraits::IURIDereferencer::MakeClassTraits,
    0,
    0,
    1,
    0,
    NULL,
    NULL,
    InstanceTraits::IURIDereferencer_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

